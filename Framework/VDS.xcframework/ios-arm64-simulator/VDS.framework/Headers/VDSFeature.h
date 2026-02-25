#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface VDSFeature : NSObject

@property (nonatomic, assign) uint8_t tag;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, strong, nullable) id value;
@property (nonatomic, copy, nullable) NSArray<VDSFeature *> *children;

- (instancetype)initWithTag:(uint8_t)tag
                       name:(NSString *)name
                      value:(nullable id)value
                   children:(nullable NSArray<VDSFeature *> *)children;

- (NSDictionary<NSString *, id> *)toJSON;

+ (NSArray<NSDictionary<NSString *, id> *> *)toJSONArray:(NSArray<VDSFeature *> *)features;

@end

NS_ASSUME_NONNULL_END
