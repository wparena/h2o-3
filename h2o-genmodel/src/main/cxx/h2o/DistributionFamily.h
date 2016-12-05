#ifndef H2O_DISTRIBUTIONFAMILY_H
#define H2O_DISTRIBUTIONFAMILY_H 1

#include <cmath>

namespace h2o {

enum DistributionFamilyType {
    unknown = 0,
    bernoulli = 1,
    modified_huber = 2,
    multinomial = 3,
    gaussian = 4,
    poisson = 5,
    gamma = 6,
    tweedie = 7,
    huber = 8,
    laplace = 9,
    quantile = 10
};

class DistributionFamily {
public:
    virtual ~DistributionFamily() {}

    static DistributionFamily *valueOf(const std::string &name);

    virtual DistributionFamilyType family() = 0;
    virtual double linkInv(double f) {
        return f;
    }
};

class BernoulliDistributionFamily : public DistributionFamily {
public:
    virtual ~BernoulliDistributionFamily() {}

    virtual DistributionFamilyType family() {
        return bernoulli;
    }

    virtual double linkInv(double f) {
        return 1 / (1 + exp(-f));
    }
};

inline DistributionFamily *DistributionFamily::valueOf(const std::string &name) {
    if (name == "bernoulli") {
        return new BernoulliDistributionFamily();
    }

    throw std::invalid_argument("DistributionFamily::valueOf: invalid family name: " + name);
}

}

#endif
