#import <Foundation/Foundation.h>

#import "VDSFeature.h"

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface BESealResult : NSObject

@property (nonatomic, copy) NSString *version;
@property (nonatomic, copy) NSString *algorithm;
@property (nonatomic, copy) NSArray<VDSFeature *> *features;
@property (nonatomic, copy) NSData *keyId;
@property (nonatomic, copy) NSData *signedData;
@property (nonatomic, copy) NSData *signature;

- (instancetype)initWithVersion:(NSString *)version
                      algorithm:(NSString *)algorithm
                       features:(NSArray<VDSFeature *> *)features
                          keyId:(NSData *)keyId
                     signedData:(NSData *)signedData
                      signature:(NSData *)signature;

@end

NS_ASSUME_NONNULL_END
