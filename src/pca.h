#pragma once
#include "types.h"

class PCA {
    public:
        PCA(unsigned int n_components);

        void fit(Matrix X);

        Eigen::MatrixXd transform(Matrix X);
        Eigen::MatrixXd get_eigenvectorMatrix(Matrix X);
        Eigen::VectorXd get_eigenvaluesMatrix(Matrix X);
    private:
        Matrix _V;
        unsigned int alpha;
};
