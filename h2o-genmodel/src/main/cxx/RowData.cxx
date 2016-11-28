#include <string>
#include "h2o/RowData.h"

using namespace h2o;

RowDataEntry::RowDataEntry() {
    _t = RDT_UNKNOWN;
}

void RowDataEntry::put(const std::string &value) {
    _t = RDT_STRING;
    _s = value;
}

void RowDataEntry::put(double value) {
    _t = RDT_DOUBLE;
    _d = value;
}

void RowData::put(const std::string &name, const std::string &value) {
    RowDataEntry tmp;
    tmp.put(value);
    _map[name] = tmp;
}

void RowData::put(const std::string &name, double value) {
    RowDataEntry tmp;
    tmp.put(value);
    _map[name] = tmp;
}

bool RowData::erase(const std::string &name) {
    std::map<std::string,RowDataEntry>::const_iterator it = _map.find(name);
    if (it == _map.end()) {
        return false;
    }

    _map.erase(it);
    return true;
}
