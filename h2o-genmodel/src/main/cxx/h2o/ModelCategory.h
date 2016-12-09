#ifndef H2O_MODELCATEGORY_H
#define H2O_MODELCATEGORY_H 1

namespace h2o {

class ModelCategory {
public:
    /**
     * Must stay in sync with Java version of ModelCategory!
     */
    enum ModelCategoryType {
        Unknown      = 0,
        Binomial     = 1,
        Multinomial  = 2,
        Regression   = 3,
        Clustering   = 4,
        AutoEncoder  = 5,
        DimReduction = 6
    };

private:
    ModelCategoryType _category;

public:
    ModelCategory() :
        _category(Unknown)
    {}

    ModelCategory(ModelCategoryType c) :
        _category(c)
    {}

    static inline ModelCategory valueOf(const std::string &name) {
        if (name == "Binomial") {
            return ModelCategory(Binomial);
        }

        throw std::invalid_argument("ModelCategory::valueOf: invalid category name: " + name);
    }

    ModelCategoryType category() const {
        return _category;
    }
};

}

#endif
