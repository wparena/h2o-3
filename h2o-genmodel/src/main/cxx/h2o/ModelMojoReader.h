#ifndef H2O_MODELMOJOREADER_H
#define H2O_MODELMOJOREADER_H 1

#include "h2o/MojoModel.h"
#include "h2o/MojoReaderBackend.h"

#include <string>
#include <cassert>
#include <map>

namespace h2o {

class ModelMojoReader;

ModelMojoReader getMojoReader(const std::string &algo);

typedef std::map<std::string, std::string> MojoModelInfo;

class ModelMojoReader {
private:
    static MojoModel *readAll(MojoReaderBackend &reader, MojoModelInfo &info) {
        assert(0);
        return NULL;
    }

public:
    static MojoModel* readFrom(MojoReaderBackend &reader) {
        std::map<std::string, std::string> info = parseModelInfo(reader);
        std::string algo = info["algorithm"];
        ModelMojoReader mmr = getMojoReader(algo);
        MojoModel* model = readAll(reader, info);
        return model;
    }

    static std::map<std::string, std::string> parseModelInfo(MojoReaderBackend &reader) {
        assert(0);
    }
};

}

#endif
