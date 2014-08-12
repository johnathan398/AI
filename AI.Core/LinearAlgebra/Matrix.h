#pragma once

#include "../Stdafx.h"
#include <stdarg.h>

using namespace System;

namespace AI {
	namespace Core {
		namespace LinearAlgebra {

			template<class T>
			class Matrix;

			template<class T>
			class MatrixRow
			{
			public:
				MatrixRow<T>(Matrix<T>* m, int row_index)
				{
					_matrix = m;
					_row_index = row_index;
				}

				T& operator[](int col_index)
				{
					return _matrix->_data[_row_index * _matrix->_cols + col_index];
				}
			private:
				Matrix<T>* _matrix;
				int _row_index;
			};

			template<class T>
			class Matrix
			{
				friend class MatrixRow<T>;
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
				Matrix(Matrix<T>& copy)
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
				Matrix(Matrix<T>* copy)
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
				Matrix(array<T, 2>^ copy)
				{
					_rows = copy->GetLength(0);
					_cols = copy->GetLength(1);
					int c = _rows * _cols;
					if(c > 0)
					{
						_data = new T[c];
						for(int i = 0; i < _rows; ++i)
							for(int j = 0; j < _cols; ++j)
								_data[i * _cols + j] = copy[i, j];
					}
					else
						_data = 0;
				}
				const Matrix<T>& operator=(Matrix<T>& copy)
				{
					if(_data != 0)
						delete[] _data;
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
				~Matrix()
				{
					if(_data != 0)
						delete[] _data;
					_data = 0;
				}

				MatrixRow<T> operator[](int row_index)
				{
					return MatrixRow<T>(this, row_index);
				}

				static Matrix<T>* Eye(int size)
				{
					Matrix<T>* ret = new Matrix<T>(size, size);
					for(int r = 0; r < size; ++r)
						for(int c = 0; c < size; ++c)
							if(r == c)
								ret->_data[r * size + c] = 1;
					return ret;
				}
				static Matrix<T>* Zeros(int rows)
				{
					return new Matrix<T>(rows);
				}
				static Matrix<T>* Zeros(int rows, int cols)
				{
					return new Matrix<T>(rows, cols);
				}
				static Matrix<T>* Ones(int rows)
				{
					return new Matrix<T>(rows, 1, (T)1);
				}
				static Matrix<T>* Ones(int rows, int cols)
				{
					return new Matrix<T>(rows, cols, (T)1);
				}

				bool operator==(Matrix<T>& operand)
				{
					if(_rows != operand._rows || _cols != operand._cols)
						return false;
					for(int i = 0; i < _rows; ++i)
						for(int j = 0; j < _cols; ++j)
							if (_data[i * _cols + j] != operand._data[i * operand._cols + j])
								return false;
					return true;
				}

				bool Equals(Matrix<T>& operand)
				{
					if (_rows != operand._rows || _cols != operand._cols)
						return false;
					for (int i = 0; i < _rows; ++i)
						for (int j = 0; j < _cols; ++j)
							if (_data[i * _cols + j] != operand._data[i * operand._cols + j])
								return false;
					return true;
				}

				bool ApproxEquals(Matrix<T>& operand)
				{
					if (_rows != operand._rows || _cols != operand._cols)
						return false;
					for (int i = 0; i < _rows; ++i)
					{
						for (int j = 0; j < _cols; ++j)
						{
							T diff = _data[i * _cols + j] - operand._data[i * operand._cols + j];
							if (diff > 0.00001 || diff < -0.00001)
								return false;
						}
					}
					return true;
				}

				bool operator!=(Matrix<T>& operand)
				{
					if(_rows != operand._rows || _cols != operand._cols)
						return true;
					for(int i = 0; i < _rows; ++i)
						for(int j = 0; j < _cols; ++j)
							if(_data[i * _cols + j] != operand._data[i * operand._cols + j])
								return true;
					return false;
				}

				Matrix<T>* operator+(T operand)
				{
					Matrix<T>* ret = new Matrix<T>(this);
					for(int i = 0; i < _rows; ++i)
						for(int j = 0; j < _cols; ++j)
							ret->_data[i * _cols + j] += operand;
					return ret;
				}
				Matrix<T>& operator+=(T operand)
				{
					for(int i = 0; i < _rows; ++i)
						for(int j = 0; j < _cols; ++j)
							_data[i * _cols + j] += operand;
					return *this;
				}

				Matrix<T>* operator-(T operand)
				{
					Matrix<T>* ret = new Matrix<T>(this);
					for(int i = 0; i < _rows; ++i)
						for(int j = 0; j < _cols; ++j)
							ret->_data[i * _cols + j] -= operand;
					return ret;
				}
				Matrix<T>& operator-=(T operand)
				{
					for(int i = 0; i < _rows; ++i)
						for(int j = 0; j < _cols; ++j)
							_data[i * _cols + j] -= operand;
					return *this;
				}

				Matrix<T>* operator*(T operand)
				{
					Matrix<T>* ret = new Matrix<T>(this);
					for(int i = 0; i < _rows; ++i)
						for(int j = 0; j < _cols; ++j)
							ret->_data[i * _cols + j] *= operand;
					return ret;
				}
				Matrix<T>& operator*=(T operand)
				{
					for(int i = 0; i < _rows; ++i)
						for(int j = 0; j < _cols; ++j)
							_data[i * _cols + j] *= operand;
					return *this;
				}

				Matrix<T>* operator/(T operand)
				{
					Matrix<T>* ret = new Matrix<T>(this);
					for(int i = 0; i < _rows; ++i)
						for(int j = 0; j < _cols; ++j)
							ret->_data[i * _cols + j] /= operand;
					return ret;
				}
				Matrix<T>& operator/=(T operand)
				{
					for(int i = 0; i < _rows; ++i)
						for(int j = 0; j < _cols; ++j)
							_data[i * _cols + j] /= operand;
					return *this;
				}

				Matrix<T>* operator^(T operand)
				{
					Matrix<T>* ret = new Matrix<T>(this);
					for(int i = 0; i < _rows; ++i)
						for(int j = 0; j < _cols; ++j)
							ret->_data[i * _cols + j] = (T)pow((double)_data[i * _cols + j], (double)operand);
					return ret;
				}
				Matrix<T>& operator^=(T operand)
				{
					for(int i = 0; i < _rows; ++i)
						for(int j = 0; j < _cols; ++j)
							_data[i * _cols + j] = (T)pow((double)_data[i * _cols + j], (double)operand);
					return *this;
				}

				T Sum()
				{
					T ret = 0;
					int c = _rows * _cols;
					for (int i = 0; i < c; ++i)
						ret += _data[i];
					return ret;
				}

				Matrix<T>* operator+(Matrix<T>& operand)
				{
					if (_rows != operand._rows || _cols != operand._cols)
						throw gcnew Exception("Mismatched matrix sizes for operator +: " + _rows.ToString() + "x" + _cols.ToString() + " * " + operand._rows.ToString() + "x" + operand._cols.ToString() + ". Matricies must be same size.");
					Matrix<T>* ret = new Matrix<T>(_rows, _cols);
					for (int i = 0; i < _rows; ++i)
					{
						for (int j = 0; j < _cols; ++j)
						{
							int idx = i * _cols + j;
							ret->_data[idx] = _data[idx] + operand._data[idx];
						}
					}
					return ret;
				}

				Matrix<T>* operator-(Matrix<T>& operand)
				{
					if (_rows != operand._rows || _cols != operand._cols)
						throw gcnew Exception("Mismatched matrix sizes for operator -: " + _rows.ToString() + "x" + _cols.ToString() + " * " + operand._rows.ToString() + "x" + operand._cols.ToString() + ". Matricies must be same size.");
					Matrix<T>* ret = new Matrix<T>(_rows, _cols);
					for (int i = 0; i < _rows; ++i)
					{
						for (int j = 0; j < _cols; ++j)
						{
							int idx = i * _cols + j;
							ret->_data[idx] = _data[idx] - operand._data[idx];
						}
					}
					return ret;
				}

				Matrix<T>& operator+=(Matrix<T>& operand)
				{
					if (_rows != operand._rows || _cols != operand._cols)
						throw gcnew Exception("Mismatched matrix sizes for operator +: " + _rows.ToString() + "x" + _cols.ToString() + " * " + operand._rows.ToString() + "x" + operand._cols.ToString() + ". Matricies must be same size.");
					for (int i = 0; i < _rows; ++i)
					{
						for (int j = 0; j < _cols; ++j)
						{
							int idx = i * _cols + j;
							_data[idx] += operand._data[idx];
						}
					}
					return *this;
				}

				Matrix<T>& operator-=(Matrix<T>& operand)
				{
					if (_rows != operand._rows || _cols != operand._cols)
						throw gcnew Exception("Mismatched matrix sizes for operator -: " + _rows.ToString() + "x" + _cols.ToString() + " * " + operand._rows.ToString() + "x" + operand._cols.ToString() + ". Matricies must be same size.");
					for (int i = 0; i < _rows; ++i)
					{
						for (int j = 0; j < _cols; ++j)
						{
							int idx = i * _cols + j;
							_data[idx] -= operand._data[idx];
						}
					}
					return *this;
				}


			private:
				static T Determinant(T* a, int a_size, int size) {
					T det = 0;
					if (size == 1) {
						return a[0];
					}
					else if (size == 2)
					{
						det = (a[0] * a[a_size + 1]) - (a[1] * a[a_size]);
					} else {
						T* b = new T[size * size];
						for (int c = 0; c < size; c++) {
							int m = 0;
							int n = 0;
							for (int i = 1; i < size; i++) {
								for (int j = 0; j < size; j++) {
									if (j != c) {
										b[m * size + n] = a[i * a_size + j];
										n++;
										if (n == size - 1)
										{
											m++;
											n = 0;
										}
									}
								}
							}
							det += a[c] * (T)pow((double)-1, (int)c) * Determinant(b, size, size - 1);
						}
						delete[] b;
					}
					return det;
				}

			public:
				T Determinant()
				{
					if(_rows != _cols)
						throw gcnew System::Exception("Cannot calculate determinant on non-square matrix.");
					if(_rows == 0)
						throw gcnew System::Exception("Cannot calculate determinant on empty matrix.");
					return Determinant(_data, _rows, _rows);
				}

				Matrix<T>* Transposition()
				{
					T* ret = new T[_rows * _cols];
					for (int i = 0; i < _rows; ++i) {
						for (int j = 0; j < _cols; ++j) {
							ret[j * _rows + i] = _data[i * _cols + j];
						}
					}
					return new Matrix<T>(ret, _cols, _rows);
				}

				Matrix<T>* Cofactor() {
					int c = _rows * _cols;
					T* b = new T[c];
					T* fac = new T[c];
					for (int q = 0; q < _rows; q++) {
						for (int p = 0; p < _rows; p++) {
							int m = 0;
							int n = 0;
							for (int i = 0; i < _rows; i++) {
								for (int j = 0; j < _rows; j++) {
									b[i * _cols + j] = 0;
									if (i != q && j != p) {
										b[m * _rows + n] = _data[i * _cols + j];
										if (n < (_rows - 2))
											n++;
										else {
											n = 0;
											m++;
										}
									}
								}
							}
							fac[q * _rows + p] = (T)pow((double)-1, q + p) * Determinant(b, _rows, _rows - 1);
						}
					}
					delete b;
					return new Matrix<T>(fac, _rows, _cols);
				}

				Matrix<T>* Inverse()
				{
					T d = Determinant();
					if (d == 0)
						throw gcnew System::Exception("A matrix with a zero determinant cannot be inverted.");
					Matrix<T>* cofac = Cofactor();
					Matrix<T>* ret = cofac->Transposition();
					*ret /= d;
					delete cofac;
					return ret;
				}

				Matrix<T>* operator*(Matrix<T>& operand)
				{
					if(_cols != operand._rows)
						throw gcnew Exception("Mismatched matrix sizes for operator *: " + _rows.ToString() + "x" + _cols.ToString() + " * " + operand._rows.ToString() + "x" + operand._cols.ToString() + ". Columns from first operand must match rows from second operand.");
					T* ret = new T[_rows * operand._cols];
					for(int i = 0; i < _rows; ++i)
					{
						for(int j = 0; j < operand._cols; ++j)
						{
							int idx = i * operand._cols + j;
							ret[idx] = 0;
							for(int k = 0; k < _cols; ++k)
								ret[idx] += (_data[i * _cols + k] * operand._data[k * operand._cols + j]);
						}
					}
					return new Matrix<T>(ret, _rows, operand._cols);
				}

				int RowCount()
				{
					return _rows;
				}

				int ColumnCount()
				{
					return _cols;
				}

				System::String^ ToString()
				{
					System::Text::StringBuilder^ ret = gcnew System::Text::StringBuilder();
					for(int i = 0; i < _rows; ++i)
					{
						ret.Append("[");
						for(int j = 0; j < _cols; ++j)
						{
							if(j > 0) ret.Append(" ");
							ret.Append( Convert::ToString(_data[i * _rows + j]) );
						}
						ret.Append("]");
					}
					return ret.ToString();
				}

			private:
				int _rows;
				int _cols;
				T* _data;
			};

#ifdef DEBUG
			public ref class MatrixTester
			{
			public:
				static void Test();
			};
#endif

		}
	}
}
