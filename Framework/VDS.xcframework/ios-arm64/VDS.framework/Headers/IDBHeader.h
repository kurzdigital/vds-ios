#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface IDBHeader : NSObject

@property (nonatomic, copy) NSString *countryId;
@property (nonatomic, assign) uint8_t signatureAlgorithm;
@property (nonatomic, copy) NSData *certificateReference;
@property (nonatomic, strong) NSDate * _Nullable signatureCreationDate;

- (instancetype)initWithCountryId:(NSString *)countryId
               signatureAlgorithm:(uint8_t)signatureAlgorithm
             certificateReference:(NSData *)certificateReference
            signatureCreationDate:(NSDate * _Nullable)signatureCreationDate;

@end

NS_ASSUME_NONNULL_END
