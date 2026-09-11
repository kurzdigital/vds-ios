#import <Foundation/Foundation.h>

#import "Seal.h"

NS_ASSUME_NONNULL_BEGIN

// One decoder for all proprietary seal formats. A new format is added in
// the native library only, so nothing here has to change for it.
__attribute__((visibility("default")))
@interface SealDecoder : NSObject

+ (nullable SealResult *)decode:(NSString *)string;

+ (nullable SealResult *)decodeBytes:(NSData *)bytes;

+ (SealVerification)verifyWithTrust:(NSData *)trust
                        requirement:(SealTrustRequirement)requirement
                          signature:(NSData *)signature
                             digest:(NSData *)digest
                                now:(nullable NSDate *)now;

@end

NS_ASSUME_NONNULL_END
