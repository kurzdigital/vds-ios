#import <Foundation/Foundation.h>

#import "Doc2DHeader.h"
#import "VDSFeature.h"

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface Doc2DResult : NSObject

@property (nonatomic, strong) Doc2DHeader *header;
@property (nonatomic, copy) NSArray<VDSFeature *> *features;
@property (nonatomic, copy, nullable) NSArray<VDSFeature *> *annex;
@property (nonatomic, copy) NSData *sha256;
@property (nonatomic, copy) NSData *signature;
@property (nonatomic, copy) NSData *derSignature;
@property (nonatomic, copy) NSString *name;

- (instancetype)initWithHeader:(Doc2DHeader *)header
                      features:(NSArray<VDSFeature *> *)features
                         annex:(nullable NSArray<VDSFeature *> *)annex
                        sha256:(NSData *)sha256
                     signature:(NSData *)signature
                  derSignature:(NSData *)derSignature
                          name:(NSString *)name;

- (BOOL)verify:(NSData *)certificate;

- (BOOL)verify:(NSData *)certificate
            now:(nullable NSDate *)now;

@end

NS_ASSUME_NONNULL_END
