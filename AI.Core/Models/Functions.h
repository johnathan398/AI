#pragma once

#include "../Stdafx.h"
#include "../LinearAlgebra/Matrix.h"

using namespace System;
using namespace AI::Core::LinearAlgebra;

#define CostFunctionParameter(T,arg_name) CostFunctionReturnValue<T> (*arg_name)(Matrix<T>*,Matrix<T>*,Matrix<T>*)

namespace AI
{
	namespace Core
	{
		namespace Models
		{
			template<class T>
			struct CostFunctionReturnValue
			{
			public:
				T Cost;
				T* ParameterGradients;
			};

			

			class Functions
			{
			public:
				template<class T>
				void GradientDescent(CostFunctionParameter(T,cost_function), Matrix<T>* parameters)
				{

				}
			};
		}
	}
}