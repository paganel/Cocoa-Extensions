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

@interface NSObject (CSObjectHelper)
/* Default implementation uses -isEqual: */
/* Expected to be replaced in subclass */
- (BOOL)isEqualIgnoringCase:(id)other;
@end

@interface NSObject (CSObjectPerformHelper)
- (void)cancelPerformRequests;
- (void)cancelPerformRequestsWithSelector:(SEL)aSelector;
- (void)cancelPerformRequestsWithSelector:(SEL)aSelector object:(nullable id)anArgument;

// ---

- (void)performBlockOnMainThread:(DISPATCH_NOESCAPE dispatch_block_t)block; // Performs a block synchronously (blocks) on the main thread
- (void)performBlockOnMainThread:(dispatch_block_t)block afterDelay:(NSTimeInterval)delay;

- (void)performBlockOnGlobalQueue:(dispatch_block_t)block; // Performs a block asynchronously on a global queue with a normal priority. Does not block.
- (void)performBlockOnGlobalQueue:(dispatch_block_t)block afterDelay:(NSTimeInterval)delay;

- (void)performSelectorInCommonModes:(SEL)aSelector afterDelay:(NSTimeInterval)delay;
- (void)performSelectorInCommonModes:(SEL)aSelector withObject:(nullable id)anArgument afterDelay:(NSTimeInterval)delay;

// ---

+ (void)performBlockOnMainThread:(DISPATCH_NOESCAPE dispatch_block_t)block;
+ (void)performBlockOnMainThread:(dispatch_block_t)block afterDelay:(NSTimeInterval)delay;

+ (void)performBlockOnGlobalQueue:(dispatch_block_t)block;
+ (void)performBlockOnGlobalQueue:(dispatch_block_t)block afterDelay:(NSTimeInterval)delay;
@end

NS_ASSUME_NONNULL_END
