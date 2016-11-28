#ifndef H2O_EASYPREDICTMODELWRAPPER_H
#define H2O_EASYPREDICTMODELWRAPPER_H 1

namespace h2o {

class GenModel;

class EasyPredictModelWrapper {
public:
    const GenModel &_model;

public:
    EasyPredictModelWrapper(const GenModel &m);

    BinomialModelPrediction predictBinomial(const RowData &row) const;
};

}

#endif
