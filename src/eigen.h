#pragma once
#include "types.h"
#include <iostream>

//
// Auxiliares
//

// Obtiene el autovalor asociado
double get_eigenvalue(Matrix &A, Vector &v);
// Para experimentación
double RayleighQuotientIteration(const Matrix &A, unsigned num_iter);

/*
Calcula el autovalor (y autovector correspondiente) de módulo máximo

Parámetros:
----------

mat: const Matrix& mat
    Matriz sobre la que queremos calcular el autovalor

num_iter: unsigned (=5000 por defecto)
    Cantidad de iteraciones a correr

eps: double
    Tolerancia a residuo (opcional)

Devuelve:
--------

pair<double, Vector> donde el primer valor es el autovalor
y el segundo el autovector asociado
*/
std::pair<double, Vector> power_iteration(const Matrix& mat, unsigned num_iter=10000, double eps=1e-6);


/*
Calcula

Parámetros:
----------

mat: const Matrix& mat
    Matriz sobre la que queremos calcular el autovalor

num: unsigned (=5000 por defecto)
    Cantidad de autovectores/autovalores a calcular

num_iter: unsigned (=5000 por defecto)
    Cantidad de iteraciones a correr

eps: double
    Tolerancia a residuo (opcional)
Devuelve:
--------

pair<Vector, Matrix> donde:
    - El primero elemento es un vector de los autovalores
    - El segundo elemento es una matriz cuyas columnas son los autovectores
      correspondientes
*/
std::pair<Eigen::VectorXd, Matrix>
    get_first_eigenvalues(const Matrix& mat, unsigned alpha, unsigned num_iter=10000, double epsilon=1e-6);
