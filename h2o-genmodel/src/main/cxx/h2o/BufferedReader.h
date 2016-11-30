#ifndef H2O_BUFFEREDREADER_H
#define H2O_BUFFEREDREADER_H

#include <fstream>
#include <vector>
#include <string>

namespace h2o {

class BufferedReader {
private:
    int nextLineToRead = 0;
    std::vector<std::string> lines;

public:
    BufferedReader(const std::string &filename) {
        std::ifstream infile(filename);
        std::string line;
        while (std::getline(infile, line)) {
            lines.push_back(line);
        }
    }

    /**
     * Get the next line from a buffer.
     * @param s [output] The next line.
     * @return true if eof; false otherwise.
     */
    bool readLine(std::string &s) {
        if (nextLineToRead >= lines.size()) {
            return true;
        }

        s = lines[nextLineToRead];
        nextLineToRead++;
        return false;
    }
};

}

#endif
