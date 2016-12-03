#ifndef H2O_MODELMOJOFACTORY_H
#define H2O_MODELMOJOFACTORY_H 1

#include "h2o/ModelMojoReader.h"
#include "h2o/GbmMojoReader.h"
#include <cassert>

namespace h2o {

ModelMojoReader getMojoReader(const std::string &algo) {
    if (algo == "Gradient Boosting Machine") {
        return GbmMojoReader();
    }

    throw std::invalid_argument("Unsupported MOJO algorithm: " + algo);
}

}

#endif
