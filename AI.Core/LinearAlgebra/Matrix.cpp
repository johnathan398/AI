#include "../Stdafx.h"
#include "Matrix.h"

namespace AI {
	namespace Core {
		namespace LinearAlgebra {

#ifdef DEBUG

			template<class T>
			void InitializeMatrix(Matrix<T>* m)
			{
				Matrix<T>* eye = m->Eye(4);
				Matrix<T> e2(eye);
				delete e2.Inverse();
				delete eye;
				delete m;
			};

			void InitializeMatrixTypes()
			{
				InitializeMatrix<double>(new Matrix<double>());
				InitializeMatrix<int>(new Matrix<int>());
			}

#endif


		}
	}
}