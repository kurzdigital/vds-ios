#import <Foundation/Foundation.h>

#import "Doc2DResult.h"

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface Doc2DDecoder : NSObject

+ (nullable Doc2DResult *)decode:(NSString *)string;

+ (nullable Doc2DResult *)decodeBytes:(NSData *)bytes;

+ (bool)verifyWithCert:(NSData *)cert
             signature:(NSData *)signature
                digest:(NSData *)digest;

+ (bool)verifyWithCert:(NSData *)cert
             signature:(NSData *)signature
                digest:(NSData *)digest
                   now:(nullable NSDate *)now;

@end

NS_ASSUME_NONNULL_END
