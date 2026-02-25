#import <Foundation/Foundation.h>

#import "VDSResult.h"
#import "VDSMRZInfo.h"

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface VDSDecoder : NSObject

+ (nullable VDSResult *)decode:(nonnull NSData *)bytes;

+ (nullable VDSResult *)decode:(nonnull NSData *)bytes
                  withProfiles:(nonnull NSString *)json;

+ (bool)verifyWithCert:(nonnull NSData *)cert
             signature:(nonnull NSData *)signature
                digest:(nonnull NSData *)digest;

+ (bool)verifyWithCert:(nonnull NSData *)cert
             signature:(nonnull NSData *)signature
                digest:(nonnull NSData *)digest
                   now:(nullable NSDate *)now;

@end

NS_ASSUME_NONNULL_END
