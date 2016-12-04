#ifndef H2O_GBMMOJOMODEL_H
#define H2O_GBMMOJOMODEL_H 1

#include "h2o/MojoModel.h"
#include "h2o/MojoReaderBackend.h"

#include <cassert>

namespace h2o {

class GbmMojoModel : public MojoModel {
private:

public:
    virtual void read(MojoReaderBackend &be) {
        readCommon(be);

        // _family = DistributionFamily.valueOf((String)readkv("distribution"));
        // _init_f = readkv("init_f");

        assert(0);
    }
};

}

#endif