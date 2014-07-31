#include "Matrix.h"

namespace AI {
	namespace Core {
		namespace LinearAlgebra {

#ifdef DEBUG

			template<class T>
			void TextMatrix(Matrix<T>* m)
			{
				delete m;
				m = Matrix<T>::Build(2, 2, (T)3, (T)8, (T)4, (T)6);
				T d = m->Determinant();
				delete m;
				if(d != -14) throw gcnew Exception("Determinant not correct.");
				m = Matrix<T>::Build(3, 3, (T)1, (T)2, (T)3, (T)0, (T)4, (T)5, (T)1, (T)0, (T)6);
				Matrix<T>* eye = Matrix<T>::Eye(3);
				Matrix<T>* i = m->Inverse();
				Matrix<T>* x = *i * *eye;
				if(*x != *m) throw gcnew Exception("Inverse not correct.");

				*x += 3;
				*x -=3;
				*x *= 3;
				*x /= 3;
				*x ^= 3;
				delete x;
				delete eye;
				delete m;
			}

			void InitializeMatrixTypes()
			{
			}

			void MatrixTester::Test()
			{
				TextMatrix<double>(new Matrix<double>());
				TextMatrix<int>(new Matrix<int>());
				TextMatrix<float>(new Matrix<float>());
				TextMatrix<short>(new Matrix<short>());
			}

#endif


		}
	}
}