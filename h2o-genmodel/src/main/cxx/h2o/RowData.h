#ifndef H2O_ROWDATA_H
#define H2O_ROWDATA_H

#include <map>

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
    RowDataEntry();
    void put(const std::string &value);
    void put(double value);
};

class RowData {
private:
    std::map<std::string,RowDataEntry> _map;

public:
    void put(const std::string &name, const std::string &value);
    void put(const std::string &name, double value);
    bool erase(const std::string &name);
};

}

#endif