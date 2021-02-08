#pragma once

#include "types.h"

class KNNClassifier {
    public:
        KNNClassifier(unsigned int n_neighbors);

        void fit(Matrix X, Matrix y);
        Vector predict(Matrix X);
private:
    Matrix training_matrix;
    Matrix label_matrix;
    unsigned int k_neighbors;
};
