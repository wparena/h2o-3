#ifndef H2O_FOLDERMOJOREADERBACKEND_H
#define H2O_FOLDERMOJOREADERBACKEND_H 1

#include "h2o/util.h"
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

    virtual void getBinaryFile(const std::string &filename, VectorOfBytes &v) {
        std::string path = root + separator() + filename;
        if (! fileExists(path.c_str())) {
            throw std::invalid_argument("getBinaryFile: file does not exist: " + path);
        }
        off_t numBytes = fileSize(path.c_str());
        v.resize(numBytes);
        FILE *f = fopen(path.c_str(), "rb");
        if (! f) {
            int tmp = errno;
            throw std::invalid_argument("getBinaryFile: fopen failed: " + filename + ": " + strerrorString(tmp));
        }
        size_t n = fread(v.data(), v.size(), 1, f);
        if (n != 1) {
            int rv = fclose(f);
            if (rv) {
                int tmp = errno;
                throw std::invalid_argument("getBinaryFile: fclose failed: " + filename + ": " + strerrorString(tmp));
            }

            throw std::invalid_argument("getBinaryFile: fread failed to return 1 element: " + filename);
        }
        int rv = fclose(f);
        if (rv) {
            int tmp = errno;
            throw std::invalid_argument("getBinaryFile: fclose failed: " + filename + ": " + strerrorString(tmp));
        }
    }
};

}

#endif
