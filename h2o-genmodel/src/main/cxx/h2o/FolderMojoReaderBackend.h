#ifndef H2O_FOLDERMOJOREADERBACKEND_H
#define H2O_FOLDERMOJOREADERBACKEND_H 1

#include "h2o/MojoReaderBackend.h"
#include <cassert>

namespace h2o {

class FolderMojoReaderBackend : public MojoReaderBackend {
private:
    std::string root;

public:
    FolderMojoReaderBackend(const std::string &folder) {
        root = folder;
    }

    virtual BufferedReader getTextFile(const std::string &filename) {
        assert(0);
    }

    virtual std::vector<uint8_t> getBinaryFile(const std::string &filename) {
        assert(0);
    }
};

}

#endif
