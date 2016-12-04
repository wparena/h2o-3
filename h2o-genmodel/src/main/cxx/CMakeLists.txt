cmake_minimum_required(VERSION 3.6)
project(cxx)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

set(SOURCE_FILES
        h2o/BinomialModelPrediction.h
        h2o/BufferedReader.h
        h2o/EasyPredictModelWrapper.h
        h2o/GenModel.h
        h2o/MojoModel.h
        h2o/MojoReaderBackend.h
        h2o/RowData.h

        example.cxx
        )

add_executable(cxx ${SOURCE_FILES})