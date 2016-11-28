#include "h2o/GenModel.h"
#include <cassert>

using namespace h2o;

EasyPredictModelWrapper::EasyPredictModelWrapper(const GenModel &model) :
    _model(model)
{
}

BinomialModelPrediction
EasyPredictModelWrapper::predictBinomial(const RowData &row) const {
    assert(0);
    BinomialModelPrediction p;
    return p;
}