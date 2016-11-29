#ifndef H2O_ROWDATA_H
#define H2O_ROWDATA_H

#include <map>
#include <string>

namespace h2o {

class RowDataEntry {
private:
    typedef enum {
        RDT_UNKNOWN = 0,
        RDT_STRING = 1,
        RDT_DOUBLE = 2
    } RowDataEntryType_t;

    RowDataEntryType_t _t;
    std::string _s;
    double _d;

public:
    RowDataEntry() {
        _t = RDT_UNKNOWN;
    }
    void put(const std::string &value) {
        _t = RDT_STRING;
        _s = value;
    }
    void put(double value) {
        _t = RDT_DOUBLE;
        _d = value;
    }
};

class RowData {
private:
    std::map<std::string,RowDataEntry> _map;

public:
    void put(const std::string &name, const std::string &value) {
        RowDataEntry tmp;
        tmp.put(value);
        _map[name] = tmp;
    }

    void put(const std::string &name, double value) {
        RowDataEntry tmp;
        tmp.put(value);
        _map[name] = tmp;
    }

    bool erase(const std::string &name) {
        std::map<std::string,RowDataEntry>::const_iterator it = _map.find(name);
        if (it == _map.end()) {
            return false;
        }

        _map.erase(it);
        return true;
    }
};

}

#endif