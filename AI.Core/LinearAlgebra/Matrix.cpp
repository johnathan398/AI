#include "Matrix.h"

namespace AI {
	namespace Core {
		namespace LinearAlgebra {

#ifdef DEBUG

			template<class T>
			void TextMatrix(Matrix<T>* m, bool floating_point_type)
			{
				delete m;

				//test 2x2 determinant
				m = new Matrix<T>(gcnew array<T, 2>{{3,8},{4,6}});
				T a1 = (*m)[0][0];
				T b1 = (*m)[0][1];
				T a2 = (*m)[1][0];
				T b2 = (*m)[1][1];
				T d1 = m->Determinant();
				delete m;
				if(d1 != -14) throw gcnew Exception("Determinant not correct.");

				//test multiplication
				m = new Matrix<T>(gcnew array<T, 2>{{1,2,3},{3,2,1},{2,1,3}});
				Matrix<T>* n = new Matrix<T>(gcnew array<T, 2>{{4,5,6},{6,5,4},{4,6,5}});
				Matrix<T>* mul_true = new Matrix<T>(gcnew array<T, 2>{{28,33,29},{28,31,31},{26,33,31}});
				Matrix<T>* mul_test = *m * *n;
				if (*mul_true != *mul_test) throw gcnew Exception("Multiplication not working correctly.");
				delete m; delete n; delete mul_true; delete mul_test;

				//test 3x3 determinant
				m = new Matrix<T>(gcnew array<T, 2>{{1,2,3},{0,4,5},{1,0,6}});
				a1 = (*m)[0][0];
				T c3 = (*m)[2][2];
				T d2 = m->Determinant();
				if (d2 != 22) throw gcnew Exception("Determinant not correct.");

				//test 3x3 inversion
				if (floating_point_type)
				{
					Matrix<T>* eye = Matrix<T>::Eye(3);
					Matrix<T>* i = m->Inverse();
					a1 = (*i)[0][0];
					Matrix<T>* eye2 = *i * *m;
					a1 = (*eye)[0][0];
					a2 = (*eye2)[0][0];
					if (!eye->ApproxEquals(*eye2)) throw gcnew Exception("Inverse not correct.");
					delete eye;
					delete eye2;
					delete i;
				}

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
				TextMatrix<double>(new Matrix<double>(), true);
				TextMatrix<int>(new Matrix<int>(), false);
				TextMatrix<float>(new Matrix<float>(), true);
				TextMatrix<short>(new Matrix<short>(), false);
				TextMatrix<char>(new Matrix<char>(), false);
			}

#endif


		}
	}
}