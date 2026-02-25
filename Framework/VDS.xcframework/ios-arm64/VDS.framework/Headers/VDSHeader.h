#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface VDSHeader : NSObject

@property (nonatomic, assign) uint8_t version;
@property (nonatomic, copy) NSString *countryId;
@property (nonatomic, copy) NSString *signerIdentifier;
@property (nonatomic, copy) NSString *certificateReference;
@property (nonatomic, strong) NSDate * _Nullable documentIssueDate;
@property (nonatomic, strong) NSDate * _Nullable signatureCreationDate;
@property (nonatomic, assign) uint8_t docFeatureDefRef;
@property (nonatomic, assign) uint8_t docTypeCategory;

- (instancetype)initWithVersion:(uint8_t)version
                      countryId:(NSString *)countryId
               signerIdentifier:(NSString *)signerIdentifier
           certificateReference:(NSString *)certificateReference
              documentIssueDate:(NSDate * _Nullable)documentIssueDate
          signatureCreationDate:(NSDate * _Nullable)signatureCreationDate
               docFeatureDefRef:(uint8_t)docFeatureDefRef
                docTypeCategory:(uint8_t)docTypeCategory;

@end

NS_ASSUME_NONNULL_END
