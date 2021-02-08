#include <iostream>
#include "pca.h"
#include "eigen.h"

using namespace std;

PCA::PCA(unsigned int n_components) {
    this->alpha = n_components;
}

void PCA::fit(Matrix X) {
    _V = get_eigenvectorMatrix(X);
}

MatrixXd PCA::transform(Matrix X) {
    return (X*_V);
}

MatrixXd PCA::get_eigenvectorMatrix(Matrix X) {
    // Armo Matriz de Covarianza
    Vector meanValue(X.cols());
    Matrix covMat = X;

    // Calculo mediana de cada columna y se la resto
    for (int i = 0; i < X.cols(); ++i) {
        meanValue[i] = X.col(i).mean();
    }

    for (int i = 0; i < X.rows(); ++i) {
        covMat.row(i) = covMat.row(i) - meanValue;
    }

    // Armo matriz de covarianza
    Matrix covMatT = covMat.transpose();
    covMat = (covMatT*covMat)/double(covMat.cols()-1);

    // Obtenego los primeros alpha autovectores y autovalores correspondientes
    Matrix V = get_first_eigenvalues(covMat, alpha).second;
    // Devuelvo la matriz con dimension reducida
    return V;
}


Vector PCA::get_eigenvaluesMatrix(Matrix X) {
    // Armo Matriz de Covarianza
    Vector meanValue(X.cols());
    Matrix covMat = X;

    // Calculo mediana de cada columna y se la resto
    for (int i = 0; i < X.cols(); ++i) {
        meanValue[i] = X.col(i).mean();
    }

    for (int i = 0; i < X.rows(); ++i) {
        covMat.row(i) = covMat.row(i) - meanValue;
    }

    // Armo matriz de covarianza
    Matrix covMatT = covMat.transpose();
    covMat = (covMatT*covMat)/(covMat.cols()-1);

    // Obtenego los primeros alpha autovectores y autovalores correspondientes
    Vector res = get_first_eigenvalues(covMat, alpha).first;
    // Devuelvo la matriz con dimension reducida
    return res;
}
