#ifndef H2O_MOJO_H
#define H2O_MOJO_H 1

#include "h2o/MojoModel.h"
#include "h2o/GbmMojoModel.h"
#include "h2o/FolderMojoReaderBackend.h"
#include "h2o/EasyPredictModelWrapper.h"
#include <string>
#include <sys/stat.h>

namespace h2o {

inline int fileExists(const char *path)
{
    struct stat fileStat;
    if (stat(path, &fileStat)) {
        return 0;
    }
    if (!S_ISREG(fileStat.st_mode)) {
        return 0;
    }
    return 1;
}

inline int dirExists(const char *path) {
    struct stat fileStat;
    if (stat(path, &fileStat)) {
        return 0;
    }
    if (!S_ISDIR(fileStat.st_mode)) {
        return 0;
    }
    return 1;
}

MojoModel *loadMojoModel(const std::string &filename) {
    if (! dirExists(filename.c_str())) {
        throw std::invalid_argument("Directory does not exist (" + filename + ")");
    }

    FolderMojoReaderBackend reader(filename);

    // Determine what kind of model we have.
    MojoModel *model = NULL;
    BufferedReader br = reader.getTextFile("model.ini");
    std::string algo;
    while (true) {
        std::string line;
        bool eof = br.readLine(line);
        if (eof) {
            throw std::invalid_argument("loadMojoModel: No algorithm found");
        }

        std::string lookFor = "algorithm = ";
        if (line.find(lookFor) == 0) {
            algo = line.substr(lookFor.length());
            break;
        }
    }

    // Create a model object.
    if (algo == "Gradient Boosting Machine") {
        model = new GbmMojoModel();
    }
    else {
        throw std::invalid_argument("loadMojoModel: Unsupported MOJO algorithm: " + algo);
    }

    // Fill in the model object.
    model->read(reader);
    return model;
}

}

#endif
