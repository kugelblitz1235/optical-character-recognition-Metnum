#include <algorithm>
#include <chrono>
#include <iostream>
#include "eigen.h"

using namespace std;

// Devuelve el autovalor asociado al autovector
double get_eigenvalue(const Matrix &A, Vector &v) {
    // eigenValue = v^t A v / v^t * v
    double lambda = v.transpose() * (A * v);
    lambda /= v.transpose() * v;

    return lambda;
}

// Es un algoritmo iterativo que converge muy rapido a el autovalor dominante y con mejor precision numerica
double RayleighQuotientIteration(const Matrix &A, unsigned num_iter) {
    Matrix I = Matrix::Identity(A.rows(),A.cols());
    Vector b_0 = Vector::Random(A.cols());
    Vector b_k;

    b_0 = b_0 / b_0.norm();
    double lambda = b_0.transpose() * (A * b_0);

    for(unsigned int i = 0; i < num_iter ; i++) {
        b_0 = (lambda * I - A).inverse() * b_0;
        b_0 /= b_0.norm();
        lambda = b_0.transpose() * (A * b_0);
        lambda /= b_0.transpose() * b_0;
    }

    return lambda;
}

pair<double, Vector> power_iteration(const Matrix& X, unsigned num_iter, double epsilon) {
    Vector b(X.cols()); b.fill(1);
    Vector b_previous;
    double eigenvalue;
    bool isClose = false;

    for (unsigned int i = 0; i < num_iter && !isClose; i++ ) {
        b_previous = b;
        b = X * b;
        b /= b.norm();
        isClose = true;

        for (int i = 0; i < b.size() && isClose; i++) {
            if (abs(b[i] - b_previous[i]) > epsilon) {
                isClose = false;
            }
        }
    }
    eigenvalue = get_eigenvalue(X, b);
    return make_pair(eigenvalue, b / b.norm());
}

pair<Vector, Matrix> get_first_eigenvalues(const Matrix& X, unsigned alpha, unsigned num_iter, double epsilon) {
    Matrix A(X);
    Vector eigenvalues(alpha);
    Matrix eigenvectors(A.rows(), alpha);
    
    std::pair<double, Vector> eigenv;

    for (unsigned int i = 0; i < alpha; i++) {
        // Las iteraciones y el epsilon van por default
        eigenv = power_iteration(A, num_iter, epsilon);
        eigenvalues[i] = eigenv.first;
        eigenvectors.col(i) = eigenv.second;

        // Calculo la siguiente matriz
        A -= eigenv.first * eigenv.second * eigenv.second.transpose();
    }

    return make_pair(eigenvalues, eigenvectors);
}
