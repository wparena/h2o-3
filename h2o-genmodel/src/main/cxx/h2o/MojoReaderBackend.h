#ifndef H2O_MOJOREADERBACKEND_H
#define H2O_MOJOREADERBACKEND_H 1

#include "h2o/BufferedReader.h"
#include <string>
#include <vector>

namespace h2o {

class MojoReaderBackend {
public:
    virtual BufferedReader getTextFile(const std::string &filename) = 0;
    virtual std::vector<uint8_t> getBinaryFile(const std::string &filename) = 0;
};

}

#endif
