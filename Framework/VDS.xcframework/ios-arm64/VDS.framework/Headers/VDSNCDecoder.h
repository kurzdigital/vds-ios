#import <Foundation/Foundation.h>

#import "VDSNC.h"

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface VDSNCDecoder : NSObject

+ (nullable VDSNC *)decode:(NSString *)json;

+ (VDSNCVerificationResult)verifyWithCmsFilePath:(NSString *)cmsFilePath
                                     certificate:(NSData *)certificate
                                       signature:(NSData *)signature
                                          digest:(NSData *)digest;

+ (VDSNCVerificationResult)verifyWithCmsFilePath:(NSString *)cmsFilePath
                                     certificate:(NSData *)certificate
                                       signature:(NSData *)signature
                                          digest:(NSData *)digest
                                             now:(nullable NSDate *)now;

@end

NS_ASSUME_NONNULL_END
