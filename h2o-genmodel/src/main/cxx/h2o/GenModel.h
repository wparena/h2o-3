#ifndef H2O_GENMODEL_H
#define H2O_GENMODEL_H 1

#include <string>
#include <vector>
#include <map>

namespace h2o {

class GenModel {
private:
    std::vector<std::string> _names;
    std::vector<bool> _isCategorical;
    std::map<int, std::vector<std::string> > _domains;
    // int _offsetColumnIdx;

public:
    GenModel()
    //    :
    //    _offsetColumnIdx(-1)
    {}

    virtual ~GenModel() {}

    virtual int nfeatures() = 0;
    virtual int nclasses() = 0;
    virtual void score0(double *row, double *preds) = 0;
};

}

#endif