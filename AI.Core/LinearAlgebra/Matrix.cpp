#include "Matrix.h"

namespace AI {
	namespace Core {
		namespace LinearAlgebra {

#ifdef DEBUG

			template<class T>
			void TextMatrix(Matrix<T>* m)
			{
				delete m;
				//test 2x2 determinant
				m = Matrix<T>::Build(2, 2, (T)3, (T)8, (T)4, (T)6);
				T a1 = (*m)[0][0];
				T b1 = (*m)[0][1];
				T a2 = (*m)[1][0];
				T b2 = (*m)[1][1];
				T d1 = m->Determinant();
				delete m;
				if(d1 != -14) throw gcnew Exception("Determinant not correct.");

				//test multiplication
				m = Matrix<T>::Build(3, 3, (T)1, (T)2, (T)3, (T)3, (T)2, (T)1, (T)2, (T)1, (T)3);
				Matrix<T>* n = Matrix<T>::Build(3, 3, (T)4, (T)5, (T)6, (T)6, (T)5, (T)4, (T)4, (T)6, (T)5);
				Matrix<T>* mul_true = Matrix<T>::Build(3, 3, (T)28, (T)33, (T)29, (T)28, (T)31, (T)31, (T)26, (T)33, (T)31);
				Matrix<T>* mul_test = *m * *n;
				if (*mul_true != *mul_test) throw gcnew Exception("Multiplication not working correctly.");
				delete m; delete n; delete mul_true; delete mul_test;

				//test 3x3 determinant
				m = Matrix<T>::Build(3, 3, (T)1, (T)2, (T)3, (T)0, (T)4, (T)5, (T)1, (T)0, (T)6);
				a1 = (*m)[0][0];
				T c3 = (*m)[2][2];
				T d2 = m->Determinant();
				if (d2 != 22) throw gcnew Exception("Determinant not correct.");

				//test 3x3 inversion
				Matrix<T>* eye = Matrix<T>::Eye(3);
				Matrix<T>* i = m->Inverse();
				a1 = (*i)[0][0];
				Matrix<T>* eye2 = *i * *m;
				a1 = (*eye)[0][0];
				a2 = (*eye2)[0][0];
				if (*eye != *eye2) throw gcnew Exception("Inverse not correct.");
				delete eye;
				delete eye2;
				delete i;

				//test single value operations
				*m += 3;
				*m -=3;
				*m *= 3;
				*m /= 3;
				*m ^= 3;
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