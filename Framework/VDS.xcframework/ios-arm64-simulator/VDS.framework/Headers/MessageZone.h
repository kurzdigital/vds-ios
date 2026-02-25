#ifndef MessageZone_h
#define MessageZone_h

#import <Foundation/Foundation.h>

#import "VDSFeature.h"
#include <vds/vds.h>

namespace vds {
NSArray<VDSFeature *> *createFeatures(const vds::MessageZone::Features &);
};

#endif
