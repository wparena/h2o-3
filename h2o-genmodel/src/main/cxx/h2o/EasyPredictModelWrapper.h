#ifndef H2O_EASYPREDICTMODELWRAPPER_H
#define H2O_EASYPREDICTMODELWRAPPER_H 1

#include "h2o/BinomialModelPrediction.h"
#include "h2o/RowData.h"
#include <cassert>

namespace h2o {

class GenModel;

class EasyPredictModelWrapper {
private:
    GenModel *_model;

    // Disable copy constructor for now since _model is a pointer.
    EasyPredictModelWrapper(const EasyPredictModelWrapper &rhs);

public:
    EasyPredictModelWrapper(GenModel *model) : _model(model) {
    }

    ~EasyPredictModelWrapper() {
        if (_model != NULL) {
            delete _model;  _model = NULL;
        }
    }

    BinomialModelPrediction predictBinomial(const RowData &row) const {
        assert(0);
        BinomialModelPrediction p;
        return p;
    }
};

}

#endif
