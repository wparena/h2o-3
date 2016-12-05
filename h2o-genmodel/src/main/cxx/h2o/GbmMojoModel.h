#ifndef H2O_GBMMOJOMODEL_H
#define H2O_GBMMOJOMODEL_H 1

#include "h2o/SharedTreeMojoModel.h"
#include "h2o/DistributionFamily.h"
#include "h2o/MojoReaderBackend.h"

#include <cassert>

namespace h2o {

class GbmMojoModel : public SharedTreeMojoModel {
public:

private:
    DistributionFamily *_family;
    double _init_f;

    // Disable copy constructor for now since _family is a pointer.
    GbmMojoModel (const GbmMojoModel &rhs);

public:
    GbmMojoModel() :
        _family(NULL)
    {}

    virtual ~GbmMojoModel() {
        if (_family != NULL) {
            delete _family;  _family = NULL;
        }
    }

    virtual void read(MojoReaderBackend &be) {
        SharedTreeMojoModel::readTreeCommon(be);
        std::string familyName = safeGetStringProperty("distribution");
        _family = DistributionFamily::valueOf(familyName);
        _init_f = safeGetDoubleProperty("init_f");
    }
};

}

#endif