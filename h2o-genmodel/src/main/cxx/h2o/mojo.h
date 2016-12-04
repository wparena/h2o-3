#ifndef H2O_MOJO_H
#define H2O_MOJO_H 1

#include "h2o/util.h"
#include "h2o/MojoModel.h"
#include "h2o/GbmMojoModel.h"
#include "h2o/FolderMojoReaderBackend.h"
#include "h2o/EasyPredictModelWrapper.h"
#include <string>

namespace h2o {

MojoModel *loadMojoModel(const std::string &filename) {
    if (! dirExists(filename.c_str())) {
        throw std::invalid_argument("Directory does not exist (" + filename + ")");
    }

    FolderMojoReaderBackend reader(filename);

    // Determine what kind of model we have.
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
    MojoModel *model = NULL;
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
