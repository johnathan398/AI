
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
				Matrix()
				{
					_rows = 0;
					_cols = 0;
					_data = 0;
				}
				Matrix(int rows)
				{
					_rows = rows;
					_cols = 1;
					if(rows > 0)
					{
						_data = new T[rows];
						for(int i = 0; i < rows; ++i)
							_data[i] = 0;
					}
					else
						_data = 0;
				}
				Matrix(int rows, int cols)
				{
					_rows = rows;
					_cols = cols;
					int c = _rows * _cols;
					if(c > 0)
					{
						_data = new T[c];
						for(int i = 0; i < c; ++i)
							_data[i] = 0;
					}
					else
						_data = 0;
				}
				Matrix(int rows, int cols, T defval)
				{
					_rows = rows;
					_cols = cols;
					int c = _rows * _cols;
					if(c > 0)
					{
						_data = new T[c];
						for(int i = 0; i < c; ++i)
							_data[i] = defval;
					}
					else
						_data = 0;
				}
				Matrix(T* data, int rows, int cols)
				{
					_data = data;
					_rows = rows;
					_cols = cols;
				}
				Matrix(Matrix& copy)
				{
					_rows = copy._rows;
					_cols = copy._cols;
					int c = _rows * _cols;
					if(c > 0)
					{
						_data = new T[c];
						for(int i = 0; i < c; ++i)
							_data[i] = copy._data[i];
					}
					else
						_data = 0;
				}
				Matrix(Matrix* copy)
				{
					_rows = copy->_rows;
					_cols = copy->_cols;
					int c = _rows * _cols;
					if(c > 0)
					{
						_data = new T[c];
						for(int i = 0; i < c; ++i)
							_data[i] = copy->_data[i];
					}
					else
						_data = 0;
				}
				~Matrix()
				{
					if(_data != 0)
						delete[] _data;
					_data = 0;
				}

				static Matrix* Eye(int size)
				{
					Matrix* ret = new Matrix(size, size);
					for(int r = 0; r < size; ++r)
						for(int c = 0; c < size; ++c)
							if(r == c)
								ret->_data[r * size + c] = 1;
					return ret;
				}
				static Matrix* Zeros(int rows)
				{
					return new Matrix(rows);
				}
				static Matrix* Zeros(int rows, int cols)
				{
					return new Matrix(rows, cols);
				}
				static Matrix* Ones(int rows)
				{
					return new Matrix(rows, 1, (T)1);
				}
				static Matrix* Ones(int rows, int cols)
				{
					return new Matrix(rows, cols, (T)1);
				}

			private:
				static T Determinant(T* a, int size) {
					T s = 1;
					T det = 0;
					if (size == 1) {
						return a[0];
					} else {
						T* b = new T[size * size];
						for (int c = 0; c < size; c++) {
							int m = 0;
							int n = 0;
							for (int i = 0; i < size; i++) {
								for (int j = 0; j < size; j++) {
									b[i * size + j] = 0;
									if (i != 0 && j != c) {
										b[m * size + n] = a[i * size + j];
										if (n < (size - 2))
											n++;
										else {
											n = 0;
											m++;
										}
									}
								}
							}
							det = det + s * (a[c] * Determinant(b, size - 1));
							s = -1 * s;
						}
						delete[] b;
					}
					return (det);
				}

			public:
				T Determinant()
				{
					if(_rows != _cols)
						throw gcnew System::Exception("Cannot calculate determinant on non-square matrix.");
					if(_rows == 0)
						throw gcnew System::Exception("Cannot calculate determinant on empty matrix.");
					return Determinant(_data, _rows);
				}

				
				Matrix* trans(T* num, T* fac, int r)
				{
					int c = r * r;
					int i, j;
					T* b = new T[c];
					T* inv = new T[c];
					for (i = 0; i < r; i++) {
						for (j = 0; j < r; j++) {
							b[i * r + j] = fac[j * r + i];
						}
					}

					T d = Determinant(num, r);
					inv[i * r + j] = 0;
					for (i = 0; i < r; i++) {
						for (j = 0; j < r; j++) {
							inv[i * r + j] = b[i * r + j] / d;
						}
					}

					return new Matrix(inv, r, r);
				}

				Matrix* Cofactors() {
					int c = _rows * _cols;
					T* b = new T[c];
					T* fac = new T[c];
					for (int q = 0; q < _rows; q++) {
						for (int p = 0; p < _rows; p++) {
							int m = 0;
							int n = 0;
							for (int i = 0; i < _rows; i++) {
								for (int j = 0; j < _rows; j++) {
									b[i * _rows + j] = 0;
									if (i != q && j != p) {
										b[m * _rows + n] = _data[i * _rows + j];
										if (n < (_rows - 2))
											n++;
										else {
											n = 0;
											m++;
										}
									}
								}
							}
							fac[q * _rows + p] = (T)pow((double)-1, q + p) * Determinant(b, _rows - 1);
						}
					}
					delete b;
					return new Matrix(fac, _rows, _cols);
				}

				Matrix* Inverse()
				{
					T d = Determinant();
					if (d == 0)
						throw gcnew System::Exception("A matrix with a zero determinant cannot be inverted.");
					Matrix* cofac = Cofactors();
					Matrix* ret = trans(_data, cofac->_data, _rows);
					delete cofac;
					return ret;
				}

				Matrix* operator+(double operand)
				{
					Matrix* ret = new Matrix(this);
					for(int i = 0; i < _rows; ++i)
						for(int j = 0; j < _cols; ++j)
							ret->_data[i * _rows + j] += operand;
					return ret;
				}
			private:
				int _rows;
				int _cols;
				T* _data;
			};

		}
	}
}
