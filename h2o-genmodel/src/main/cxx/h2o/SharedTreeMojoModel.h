#ifndef H2O_SHAREDTREEMOJOMODEL_H
#define H2O_SHAREDTREEMOJOMODEL_H 1

#include "h2o/util.h"
#include "h2o/MojoModel.h"

namespace h2o {

class SharedTreeMojoModel : public MojoModel {
private:
    int _ntree_groups;
    int _ntrees_per_group;
    std::vector<VectorOfBytes> _compressed_trees;

    int treeIndex(int groupIndex, int classIndex) {
        return classIndex * _ntree_groups + groupIndex;
    }

protected:
    void readTreeCommon(MojoReaderBackend &be) {
        MojoModel::readCommon(be);

        _ntree_groups = safeGetIntProperty("n_trees");
        _ntrees_per_group = safeGetIntProperty("n_trees_per_class");
        _compressed_trees.resize(_ntree_groups);

        for (int j = 0; j < _ntree_groups; j++) {
            for (int i = 0; i < _ntrees_per_group; i++) {
                char buf[1024];
                snprintf(buf, sizeof(buf)-1, "trees/t%02d_%03d.bin", i, j);
                VectorOfBytes &one_compressed_tree = _compressed_trees[treeIndex(j, i)];
                be.getBinaryFile(buf, one_compressed_tree);
            }
        }
    }

    void scoreAllTrees(double *row, double *preds) {
        assert(0);
    }

public:
    virtual ~SharedTreeMojoModel() {}
};

}

#endif