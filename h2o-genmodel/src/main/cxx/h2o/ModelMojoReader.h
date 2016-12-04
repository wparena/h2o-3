#ifndef H2O_MODELMOJOREADER_H
#define H2O_MODELMOJOREADER_H 1

#include "h2o/MojoModel.h"
#include "h2o/MojoReaderBackend.h"

#include <string>
#include <cassert>
#include <map>
#include <deque>

namespace h2o {

class ModelMojoReader;

ModelMojoReader getMojoReader(const std::string &algo);

class DomainInfo {
public:
    int numLevels;
    std::string filename;

    DomainInfo() {}
    DomainInfo(int v1, const std::string &v2) :
            numLevels(v1),
            filename(v2)
            {}
};

class MojoModelInfo {
public:
    std::map<std::string, std::string> properties;
    std::deque<std::string> columns;
    std::map<int, DomainInfo> domains;
};

// http://stackoverflow.com/questions/25829143/c-trim-whitespace-from-a-string
inline std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

class ModelMojoReader {
private:
    MojoModel *readAll(MojoReaderBackend &reader, MojoModelInfo &info) {
        assert(0);
        return NULL;
    }

public:
    static MojoModel *readFrom(MojoReaderBackend &reader) {
        MojoModelInfo info = parseModelInfo(reader);
        std::string algo = info.properties["algorithm"];
        ModelMojoReader mmr = getMojoReader(algo);
        MojoModel *model = mmr.readAll(reader, info);
        return model;
    }

    static MojoModelInfo parseModelInfo(MojoReaderBackend &reader) {
        BufferedReader br = reader.getTextFile("model.ini");
        MojoModelInfo info;
        std::string line;

        enum Section {
            NONE,
            INFO,
            COLUMNS,
            DOMAINS
        };

        Section section = NONE;
        while (true) {
            bool eof = br.readLine(line);
            if (eof) {
                break;
            }

            line = trim(line);
            if (line.empty()) {
                continue;
            } else if (line[0] == '#') {
                continue;
            } else if (line == "[info]") {
                section = INFO;
            } else if (line == "[columns]") {
                section = COLUMNS;
                int n_columns = std::stoi(info.properties["n_columns"]);
                if (n_columns == 0) {
                    throw std::invalid_argument("parseModelInfo: `n_columns` variable is missing in the model info.");
                }
            } else if (line == "[domains]") {
                section = DOMAINS;
            } else {
                switch (section) {
                    case INFO: {
                        std::string::size_type idx = line.find(" = ");
                        if (idx == std::string::npos) {
                            throw std::invalid_argument("parseModelInfo: invalid line in INFO section.");
                        }
                        std::string name = line.substr(0, idx);
                        std::string value = line.substr(idx + 3, line.length());
                        info.properties[name] = value;
                        break;
                    }
                    case COLUMNS: {
                        info.columns.push_back(line);
                        break;
                    }
                    case DOMAINS: {
                        std::string::size_type idx = line.find(": ");
                        if (idx == std::string::npos) {
                            throw std::invalid_argument("parseModelInfo: invalid line in DOMAINS section (1).");
                        }
                        std::string columnNumStr = line.substr(0, idx);
                        int columnNum = std::stoi(columnNumStr);

                        std::string line2 = line.substr(idx + 2);
                        idx = line2.find(" ");
                        if (idx == std::string::npos) {
                            throw std::invalid_argument("parseModelInfo: invalid line in DOMAINS section (2).");
                        }
                        std::string numLevelsStr = line2.substr(0, idx);
                        int numLevels = std::stoi(numLevelsStr);
                        std::string filename = line2.substr(idx + 1);

                        DomainInfo di;
                        di.numLevels = numLevels;
                        di.filename = filename;
                        info.domains[columnNum] = di;
                        break;
                    }
                    default: {
                        throw std::invalid_argument("parseModelInfo: Invalid section.");
                    }
                }
            }
        }

        return info;
    }
};

}

#endif
