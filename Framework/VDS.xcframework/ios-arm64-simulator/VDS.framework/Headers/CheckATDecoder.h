#import <Foundation/Foundation.h>

#import "CheckATResult.h"

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface CheckATDecoder : NSObject

+ (nullable CheckATResult *)decode:(NSString *)string;

+ (bool)verifyWithPublicKey:(NSData *)publicKey
                  signature:(NSData *)signature
                     digest:(NSData *)digest;

@end

NS_ASSUME_NONNULL_END
