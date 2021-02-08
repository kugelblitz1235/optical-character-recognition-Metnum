#include <algorithm>
//#include <chrono>
#include <iostream>
#include <vector>
#include "knn.h"

using namespace std;

// Minkowski distance measures

double euclideanDistance(Matrix &training_matrix, int train, Matrix &targetMatrix, int target) { //Euclidea
    return (training_matrix.row(train).transpose() - targetMatrix.row(target).transpose()).norm();
}

double euclideanDistance2(Matrix &training_matrix, int train, Matrix &targetMatrix, int target) { //Euclidea Mala
    double sum = 0;

    for(unsigned int i = 0 ; i < training_matrix.cols() ; i++)
        sum+= pow((training_matrix(train, i) - targetMatrix(target, i)),2);

    return sqrt(sum);

}

double ManhattanDistance(Matrix &training_matrix, int train, Matrix &targetMatrix, int target) { //ManhattanDistance
    double sum = 0;

    for(unsigned int i = 0 ; i < training_matrix.cols() ; i++)
        sum+= abs(training_matrix(train, i) - targetMatrix(target, i));

    return sum;
}

double chebyshevDistance(Matrix &training_matrix, int train, Matrix &targetMatrix, int target) { //chebyshevDistance
    double max = 0;

    for(unsigned int i = 0 ; i < training_matrix.cols() ; i++)
        if(max < abs(training_matrix(train, i) - targetMatrix(target, i)))
            max = abs(training_matrix(train, i) - targetMatrix(target, i));

    return max;
}

KNNClassifier::KNNClassifier(unsigned int n_neighbors) {
    this->k_neighbors = n_neighbors;
}

void KNNClassifier::fit (Matrix X, Matrix y) {
    this->training_matrix = X;
    this->label_matrix = y;
}

Vector KNNClassifier::predict(Matrix X) {
    auto targetLabels = Vector(X.rows());
    auto k = k_neighbors;

    // Un arreglo que va a contener k distancias mas cercanas entre mi elemento y todos los elementos de la matriz de entrenamiento
    vector< pair<double, int> > squaredDistances(k, make_pair(0,0));

    for (unsigned int target = 0; target < X.rows(); target++) {
        // Completo con las distancias y la etiqueta correspondientes
        for (unsigned int i = 0; i < k; i++) {
            squaredDistances[i].first = euclideanDistance(training_matrix, i, X, target);
            squaredDistances[i].second = label_matrix(i,0);
        }

        // Ordenar el vector de acuerdo a las distancias y tomar los primeros k elementos
        sort(squaredDistances.begin(), squaredDistances.end());

        // Recorro los elementos que faltan de la matriz de entrenamiento
        for(unsigned int j = k; j < training_matrix.rows(); j++){
            // Si el elemento tiene distancia menor al más grande de los k más cercanos, lo sobreescribo.
            if(squaredDistances[k-1].first > euclideanDistance(training_matrix, j, X, target)){
                squaredDistances[k-1] = make_pair(euclideanDistance(training_matrix, j, X, target), label_matrix(j,0));
                // Inserto ordenado el elemento que quedó en la última posición.
                int i = k - 1;
                while(i != 0 && squaredDistances[i].first < squaredDistances[i-1].first){
                    swap(squaredDistances[i-1], squaredDistances[i]);
                    i--;
                }
            }
        }

        // Inicializo un Vector para contar la cantidad de representantes de cada label
        vector<int> labelCounter(10,0);

        // Cuento la cantidad de repeticiones que tiene cada digito
        for (unsigned int m = 0; m < k; ++m) {
            labelCounter[squaredDistances[m].second]++;
        }

        // Obtengo la moda
        int labelMode = max_element(labelCounter.begin(), labelCounter.end()) - labelCounter.begin();

        // Defino el label del elemento target
        targetLabels(target) = labelMode;
    }

    return targetLabels;
}