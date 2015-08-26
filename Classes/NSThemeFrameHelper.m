/* *********************************************************************

        Copyright (c) 2010 - 2015 Codeux Software, LLC
     Please see ACKNOWLEDGEMENT for additional information.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 * Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
 * Neither the name of "Codeux Software, LLC", nor the names of its 
   contributors may be used to endorse or promote products derived 
   from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 SUCH DAMAGE.

 *********************************************************************** */

#import "CocoaExtensions.h"

#import <objc/message.h>
#import <objc/runtime.h>

@implementation NSObject (CSCEFThemeFrameHelper)

static void *_internalUsesCustomTitlebarTitlePositioning = nil;

+ (void)load
{
	static dispatch_once_t onceToken;

	dispatch_once(&onceToken, ^{
		XRExchangeImplementation(@"NSThemeFrame", @"_defaultTitlebarTitleRect", @"ce_priv_defaultTitlebarTitleRect");
	});
}

/* -ce_priv_defaultTitlebarTitleRect is an extremely dirty bug fix. */
/* This fix will break titles if the titlebar contains an autosave button
 or a document icon so do not use this method unless you know its purpose. */
- (NSRect)ce_priv_defaultTitlebarTitleRect
{
	/* This method can only be used within an NSThemeFrame instance. */
	if (NSObjectsAreEqual([self className], @"NSThemeFrame") == NO) {
		return NSZeroRect;
	}

	/* Return default value depending on configuration. */
	NSRect defaultTitlebarTitleRect = [self ce_priv_defaultTitlebarTitleRect];

	if ([self usesCustomTitlebarTitlePositioning] == NO) {
		return defaultTitlebarTitleRect;
	}

	if (NSIsEmptyRect(defaultTitlebarTitleRect)) {
		return defaultTitlebarTitleRect;
	}

	/* Use private method to calculate the maximum possible size for rect. */
	/* NSSelectorFromString() is used to try to hide the fact we are calling out
	 to private APIs when using this within the Mac App Store. */
	SEL maximumTitlebarTitleRectSelector = NSSelectorFromString(@"_maxTitlebarTitleRect");

	if ([self respondsToSelector:maximumTitlebarTitleRectSelector] == NO) {
		return defaultTitlebarTitleRect;
	}

	NSRect (*retrieveRectFunction)(id receiver, SEL operation);
	retrieveRectFunction = (NSRect(*)(id, SEL))objc_msgSend_stret;

	NSRect maximumTitleRect = retrieveRectFunction(self, maximumTitlebarTitleRectSelector);

	if (NSIsEmptyRect(maximumTitleRect)) {
		return defaultTitlebarTitleRect;
	}

	/* Given a maximum frame and the default, we fudge the values a bit. */
	NSRect finalTitleRect = NSZeroRect;

	finalTitleRect.size = defaultTitlebarTitleRect.size;

	finalTitleRect.origin.x = (NSMidX(maximumTitleRect) - (defaultTitlebarTitleRect.size.width / 2.0)); // Center the piont

	finalTitleRect.origin.y = defaultTitlebarTitleRect.origin.y;

	return finalTitleRect;
}

- (BOOL)usesCustomTitlebarTitlePositioning
{
	/* This object is only assignable in an NSThemeFrame instance. */
	if (NSObjectsAreEqual([self className], @"NSThemeFrame") == NO) {
		return NO;
	}

	/* This fix is not necessary prior to OS X Yosemite. */
	if ([XRSystemInformation isUsingOSXYosemiteOrLater] == NO) {
		return NO;
	}

	/* This fix is not necessary unless we have custom views. */
	SEL titlebarAccessoryViewControllersSelector = NSSelectorFromString(@"titlebarAccessoryViewControllers");

	if ([self respondsToSelector:titlebarAccessoryViewControllersSelector]) {
		id viewControllers = objc_msgSend(self, titlebarAccessoryViewControllersSelector);

		if (viewControllers && [viewControllers isKindOfClass:[NSArray class]]) {
			BOOL allViewControllersHidden = YES;

			for (NSViewController *viewController in viewControllers) {
				if ([[viewController view] isHidden] == NO) {
					allViewControllersHidden = NO;

					break;
				}
			}

			if (allViewControllersHidden) {
				return NO;
			}
		}
	} else {
		return NO;
	}

	/* Assigned object is an NSNumber which means we have to translate to BOOL */
	NSNumber *customPositioning = objc_getAssociatedObject(self, _internalUsesCustomTitlebarTitlePositioning);

	if (customPositioning) {
		return [customPositioning boolValue];
	} else {
		return NO;
	}
}

- (void)setUsesCustomTitlebarTitlePositioning:(BOOL)usesCustomTitlebarTitlePositioning
{
	/* This object is only assignable in an NSThemeFrame instance. */
	if (NSObjectsAreEqual([self className], @"NSThemeFrame") == NO) {
		return;
	}

	/* Assigned as an NSNumber that is copied. */
	objc_setAssociatedObject(self,
							 _internalUsesCustomTitlebarTitlePositioning,
							 [NSNumber numberWithBool:usesCustomTitlebarTitlePositioning],
							 OBJC_ASSOCIATION_COPY);
}

@end
