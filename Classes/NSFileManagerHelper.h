/* *********************************************************************
 *
 *         Copyright (c) 2015 - 2018 Codeux Software, LLC
 *     Please see ACKNOWLEDGEMENT for additional information.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of "Codeux Software, LLC", nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *********************************************************************** */

NS_ASSUME_NONNULL_BEGIN

@interface NSFileManager (CSFileManagerHelper)
@property (readonly, strong, nullable) id<NSObject, NSCopying, NSCoding> cloudUbiquityIdentityToken;

- (BOOL)fileExistsAtURL:(NSURL *)url;

- (BOOL)directoryExistsAtPath:(NSString *)path;

- (BOOL)lockItemAtPath:(NSString *)path error:(NSError **)error;
- (BOOL)unlockItemAtPath:(NSString *)path error:(NSError **)error;

- (NSArray<NSString *> *)buildPathArray:(NSString *)path, ...;

- (BOOL)isUbiquitousItemAtPathDownloaded:(NSString *)path;

// The following methods default to moving destination to trash + copying source
- (BOOL)replaceItemAtPath:(NSString *)destinationPath
		   withItemAtPath:(NSString *)sourcePath;

- (BOOL)replaceItemAtPath:(NSString *)destinationPath
		   withItemAtPath:(NSString *)sourcePath
   moveDestinationToTrash:(BOOL)moveDestinationToTrash;

- (BOOL)replaceItemAtPath:(NSString *)destinationPath
		   withItemAtPath:(NSString *)sourcePath
		moveToDestination:(BOOL)moveToDestination
   moveDestinationToTrash:(BOOL)moveDestinationToTrash;

- (BOOL)replaceItemAtURL:(NSURL *)destinationURL
		   withItemAtURL:(NSURL *)sourceURL;

- (BOOL)replaceItemAtURL:(NSURL *)destinationURL
		   withItemAtURL:(NSURL *)sourceURL
  moveDestinationToTrash:(BOOL)moveDestinationToTrash;

- (BOOL)replaceItemAtURL:(NSURL *)destinationURL
		   withItemAtURL:(NSURL *)sourceURL
	   moveToDestination:(BOOL)moveToDestination
  moveDestinationToTrash:(BOOL)moveDestinationToTrash;
@end

NS_ASSUME_NONNULL_END
