#ifndef H2O_BINOMIALMODELPREDICTION_H
#define H2O_BINOMIALMODELPREDICTION_H 1

#include <string>
#include <vector>

namespace h2o {

class BinomialModelPrediction {
public:
    std::string label;
    std::vector<double> classProbabilities;

    BinomialModelPrediction() {
        classProbabilities.resize(2);
    }
};

}

#endif