import metnum
import numpy as np
import unittest

from numpy import linalg as la


class TestTp2(unittest.TestCase):
    def testPotencia(self):
        diagonal = np.diagflat([1,2,3,4,5])

        autoval, autovec = metnum.get_first_eigenvalues(diagonal, 5, 100)
        expectedAutoVal = np.array([[5,4,3,2,1]])
        expectedResult = np.array([])

        self.assertEqual(True, np.allclose(autoval, expectedAutoVal, 1e-6))

        #para cada autovector chequeo que valga que Av=av siendo lambda el autovalor asociado
        for i in range(autovec[0].size) :
            self.assertEqual(True, np.allclose(diagonal.dot(autovec[i]), autovec[i] * autoval[i], 1e-6))
        


#==============TEST CON MATRIZ DIAGONALIZADA
        #vector con unos
        v = np.ones((diagonal.shape[0], 1))
        #lo normalizo
        v = v / np.linalg.norm(v)

        # genero la matriz de house holder
        B = np.eye(giagonal.shape[0]) - 2 * (v @ v.T)

        # diagonalizo la matriz
        matrixTest = B.T @ D @ B

        eigen = metnum.power_iteration(matrixTest,1000)

        autoval, autovec = metnum.get_first_eigenvalues(matrixTest, 5, 1000)
        
        #chequeo que sean los mismos autovalores
        self.assertEqual(True, np.allclose(autoval, expectedAutoVal, 1e-6))
        
        #para cada autovector chequeo que valga que Av=av siendo lambda el autovalor asociado
        for i in range(autovec[0].size) :
            print(str(np.round(matrixTest.dot(autovec[i]),2)) + ' = ' +  str(np.round(autovec[i] * autoval[i],2)))
            self.assertEqual(True, np.allclose(matrixTest.dot(autovec[i]), autovec[i] * autoval[i], 1e-6))
        

if __name__ == '__main__':
    unittest.main()
