#ifndef H2O_MOJOREADERBACKEND_H
#define H2O_MOJOREADERBACKEND_H 1

#include "h2o/util.h"
#include "h2o/BufferedReader.h"
#include <string>

namespace h2o {

class MojoReaderBackend {
public:
    virtual BufferedReader getTextFile(const std::string &filename) = 0;
    virtual void getBinaryFile(const std::string &filename, VectorOfBytes &v) = 0;
};

}

#endif
