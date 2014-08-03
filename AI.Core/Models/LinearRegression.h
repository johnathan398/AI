#pragma once

#include "../Stdafx.h"
#include "../IO/IInput.h"
#include "../LinearAlgebra/Matrix.h"

using namespace System;
using namespace AI::Core::LinearAlgebra;

namespace AI
{
	namespace Core
	{
		namespace Models
		{
			ref class LinearRegression
			{
			public:
				LinearRegression();

				void TrainGradient(AI::Core::IO::IInputLinearRegression^ input, int max_iterations);
				void TrainNormal(AI::Core::IO::IInputLinearRegression^ input);
				double Predict(array<double>^ feature_vector);
				array<double>^ Predict(AI::Core::IO::IInput^ input);
			private:
				Matrix<double>* _theta;
			};
		}
	}
}