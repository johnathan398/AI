
#pragma once

#include "../Stdafx.h"

using namespace System;

namespace AI {
	namespace Core {
		namespace LinearAlgebra {

			template<class T>
			class Matrix
			{
			public:
				Matrix();
				Matrix(int rows);
				Matrix(int rows, int cols);
				Matrix(Matrix& copy);
				Matrix(Matrix* copy);
				~Matrix();

				static Matrix* Eye(int size);
				static Matrix* Zeros(int rows);
				static Matrix* Zeros(int rows, int cols);
				static Matrix* Ones(int rows);
				static Matrix* Ones(int rows, int cols);

				Matrix* Inverse();
				void Invert();

				Matrix* operator+(double operand);
			private:
				int _rows;
				int _cols;
				
			};

		}
	}
}
