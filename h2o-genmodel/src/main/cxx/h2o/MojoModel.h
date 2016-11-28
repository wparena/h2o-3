#ifndef H2O_MOJOMODEL_H
#define H2O_MOJOMODEL_H 1

namespace h2o {

class GenModel;

class MojoModel {
public:
    static GenModel load(const std::string &filename);
};

}

#endif