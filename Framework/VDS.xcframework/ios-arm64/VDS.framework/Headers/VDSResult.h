#import <Foundation/Foundation.h>

#import "VDSHeader.h"
#import "VDSFeature.h"

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface VDSResult : NSObject

@property (nonatomic, strong) VDSHeader *header;
@property (nonatomic, strong) NSArray<VDSFeature *> *features;
@property (nonatomic, strong) NSData *sha256;
@property (nonatomic, strong) NSData *signature;
@property (nonatomic, copy) NSString *name;

- (instancetype)initWithHeader:(VDSHeader *)header
                      features:(NSArray<VDSFeature *> *)features
                        sha256:(NSData *)sha256
                     signature:(NSData *)signature
                          name:(NSString *)name;

- (BOOL)verify:(NSData *)certificate;

- (BOOL)verify:(NSData *)certificate
            now:(nullable NSDate *)now;

@end

NS_ASSUME_NONNULL_END
