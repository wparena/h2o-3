#ifndef H2O_FOLDERMOJOREADERBACKEND_H
#define H2O_FOLDERMOJOREADERBACKEND_H 1

#include "h2o/MojoReaderBackend.h"
#include <cassert>

namespace h2o {

inline char separator()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

class FolderMojoReaderBackend : public MojoReaderBackend {
private:
    std::string root;

public:
    FolderMojoReaderBackend(const std::string &folder) {
        root = folder;
    }

    virtual BufferedReader getTextFile(const std::string &filename) {
        BufferedReader br(root + separator() + filename);
        return br;
    }

    virtual std::vector<uint8_t> getBinaryFile(const std::string &filename) {
        assert(0);
    }
};

}

#endif
