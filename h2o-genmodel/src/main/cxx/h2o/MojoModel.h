#ifndef H2O_MOJOMODEL_H
#define H2O_MOJOMODEL_H 1

#include "h2o/util.h"
#include "h2o/GenModel.h"
#include "h2o/MojoReaderBackend.h"

#include <string>
#include <vector>
#include <deque>
#include <cassert>

namespace h2o {

/**
 * Must stay in sync with Java version of ModelCategory!
 */
enum ModelCategory {
    Unknown      = 0,
    Binomial     = 1,
    Multinomial  = 2,
    Regression   = 3,
    Clustering   = 4,
    AutoEncoder  = 5,
    DimReduction = 6
};

class DomainInfo {
public:
    int numLevels;
    std::string filename;
    std::vector<std::string> levels;

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

class MojoModel : public GenModel {
private:
    MojoModelInfo _info;

    /*
    ModelCategory _category;
    std::string _uuid;
    bool _supervised;
    int _nfeatures;
    int _nclasses;
    bool _balanceClasses;
    double _defaultThreshold;
    std::vector<double> _priorClassDistrib;
    std::vector<double> _modelClassDistrib;
     */

    void parseModelInfo(MojoReaderBackend &be) {
        BufferedReader br = be.getTextFile("model.ini");
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
                int n_columns = std::stoi(_info.properties["n_columns"]);
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
                        _info.properties[name] = value;
                        break;
                    }
                    case COLUMNS: {
                        _info.columns.push_back(line);
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

                        // Read domain levels.
                        {
                            BufferedReader domBr = be.getTextFile("domains/" + filename);
                            while (true) {
                                std::string domLine;
                                bool domEof = domBr.readLine(domLine);
                                domLine = trim(domLine);
                                if (domEof) {
                                    break;
                                }
                                di.levels.push_back(domLine);
                            }

                            if (di.numLevels != di.levels.size()) {
                                throw std::invalid_argument("Mismatching number of levels for column: " + _info.columns[columnNum]);
                            }
                        }

                        _info.domains[columnNum] = di;
                        break;
                    }
                    default: {
                        throw std::invalid_argument("parseModelInfo: Invalid section.");
                    }
                }
            }
        }
    }

    void safeCheckPropertyExists(const std::string &name) {
        if (! mapContains(_info.properties, name)) {
            throw std::invalid_argument("Property does not exist: " + name);
        }
    }

protected:
    void readCommon(MojoReaderBackend &be) {
        parseModelInfo(be);
    }

    int safeGetIntProperty(const std::string &name) {
        safeCheckPropertyExists(name);
        std::string stringValue = _info.properties[name];
        int value = std::stoi(stringValue);
        return value;
    }

    double safeGetDoubleProperty(const std::string &name) {
        safeCheckPropertyExists(name);
        std::string stringValue = _info.properties[name];
        double value = std::stod(stringValue);
        return value;
    }

    std::string safeGetStringProperty(const std::string &name) {
        safeCheckPropertyExists(name);
        return _info.properties[name];
    }

public:
    virtual void read(MojoReaderBackend &be) = 0;
    virtual ~MojoModel() {}
};

}

#endif