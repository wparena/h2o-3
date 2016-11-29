#ifndef H2O_MOJO_H
#define H2O_MOJO_H 1

#include "h2o/MojoModel.h"
#include "h2o/FolderMojoReaderBackend.h"
#include "h2o/ModelMojoFactory.h"
#include "h2o/EasyPredictModelWrapper.h"
#include <string>
#include <sys/stat.h>

namespace h2o {

//int fileExists(const char *path)
//{
//    struct stat fileStat;
//    if ( stat(path, &fileStat) )
//    {
//        return 0;
//    }
//    if ( !S_ISREG(fileStat.st_mode) )
//    {
//        return 0;
//    }
//    return 1;
//}

static int dirExists(const char *path) {
    struct stat fileStat;
    if ( stat(path, &fileStat) ) {
        return 0;
    }
    if ( !S_ISDIR(fileStat.st_mode) ) {
        return 0;
    }
    return 1;
}

MojoModel *loadMojoModel(const std::string &filename) {
    if (!dirExists(filename.c_str())) {
        throw std::invalid_argument("Directory does not exist (" + filename + ")");
    }

    FolderMojoReaderBackend cr(filename);
    MojoModel *rv = ModelMojoReader::readFrom(cr);
    return rv;
}

}

#endif
