#ifndef MessageZone_h
#define MessageZone_h

#import <Foundation/Foundation.h>

#import "VDSFeature.h"
#include <vds/vds.h>

NS_ASSUME_NONNULL_BEGIN

namespace vds {
NSArray<VDSFeature *> *createFeatures(const vds::MessageZone::Features &);
};

NS_ASSUME_NONNULL_END

#endif
