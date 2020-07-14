/**
 * Copyright (c) 2016-present Invertase Limited & Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this library except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Firebase/Firebase.h>

NS_ASSUME_NONNULL_BEGIN

@protocol RNFBDynamicLinksAppDelegateInterceptorDelegate;

static NSString *const LINK_RECEIVED_EVENT = @"dynamic_links_link_received";

@interface RNFBDynamicLinksAppDelegateInterceptor : NSObject <UIApplicationDelegate>
@property (strong, readwrite) NSString *_Nullable initialLinkUrl;
@property (strong, readwrite) NSString *_Nullable initialLinkMinimumAppVersion;
@property (weak, nonatomic) id<RNFBDynamicLinksAppDelegateInterceptorDelegate> _Nullable delegate;

+ (instancetype)sharedInstance;

@end

@protocol RNFBDynamicLinksAppDelegateInterceptorDelegate<NSObject>
@optional

// willOpenURL -> shouldOpenURL? -(Y)-> didOpenURL
//                               -(N)-> X
- (NSURL *)dynamicLinksAppDelegateInterceptor:(RNFBDynamicLinksAppDelegateInterceptor *)interceptor
                                  willOpenURL:(NSURL *)url
                            sourceApplication:(NSString *)sourceApplication
                                   annotation:(id)annotation;

- (BOOL)dynamicLinksAppDelegateInterceptor:(RNFBDynamicLinksAppDelegateInterceptor *)interceptor
                             shouldOpenURL:(NSURL *)url
                         sourceApplication:(NSString *)sourceApplication
                                annotation:(id)annotation;

- (void)dynamicLinksAppDelegateInterceptor:(RNFBDynamicLinksAppDelegateInterceptor *)interceptor
                                didOpenURL:(NSURL *)url
                         sourceApplication:(NSString *)sourceApplication
                                annotation:(id)annotation
                               dynamicLink:(FIRDynamicLink * _Nullable)dynamicLink;

// willContinueUserActivity -> shouldContinueUserActivity? -(Y)-> didContinueUserActivity
//                                                         -(N)-> X
- (NSUserActivity *)dynamicLinksAppDelegateInterceptor:(RNFBDynamicLinksAppDelegateInterceptor *)interceptor
                              willContinueUserActivity:(NSUserActivity *)userActivity;

- (BOOL)dynamicLinksAppDelegateInterceptor:(RNFBDynamicLinksAppDelegateInterceptor *)interceptor
                shouldContinueUserActivity:(NSUserActivity *)userActivity;

- (void)dynamicLinksAppDelegateInterceptor:(RNFBDynamicLinksAppDelegateInterceptor *)interceptor
                   didContinueUserActivity:(NSUserActivity *)userActivity
                                   handled:(BOOL)handled;

@end

NS_ASSUME_NONNULL_END
