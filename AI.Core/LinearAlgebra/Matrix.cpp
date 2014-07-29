#include "../Stdafx.h"
#include "Matrix.h"

namespace AI {
	namespace Core {
		namespace LinearAlgebra {

			template<class T>
			void InitializeMatrix(Matrix<T>* m)
			{
				delete m;
			};

			void InitializeMatrixTypes()
			{
				InitializeMatrix<double>(new Matrix<double>());
				InitializeMatrix<int>(new Matrix<int>());
			}


		}
	}
}