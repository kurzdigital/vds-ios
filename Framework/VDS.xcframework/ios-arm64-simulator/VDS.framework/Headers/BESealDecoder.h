#import <Foundation/Foundation.h>

#import "BESealResult.h"

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface BESealDecoder : NSObject

// There is no verification because the certificate the seal references
// with its keyId is not publicly available.
+ (nullable BESealResult *)decode:(NSString *)string;

@end

NS_ASSUME_NONNULL_END
