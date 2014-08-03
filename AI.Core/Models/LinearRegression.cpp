#include "LinearRegression.h"

namespace AI
{
	namespace Core
	{
		namespace Models
		{
			LinearRegression::LinearRegression()
			{
				_theta = 0;
			}

			void LinearRegression::TrainGradient(AI::Core::IO::IInputLinearRegression^ input, int max_iterations)
			{
				throw gcnew NotImplementedException();
			}

			void LinearRegression::TrainNormal(AI::Core::IO::IInputLinearRegression^ input)
			{
				//theta = pinv(X'*X)*X'*y
				if(_theta != 0) delete _theta;
				int m = input->TrainingExampleCount;
				int n = input->FeatureCount;

				//build input matrix
				Matrix<double> x(m, n + 1, 1);
				Matrix<double> y(m, 1);
				for(int i = 0; i < m; ++i)
				{
					for(int j = 0; j < n; ++j)
					{
						x[i][j + 1] = input->AccessValue(i, j);
					}
					y[i][0] = input->AccessActualOutput(i);
				}
				Matrix<double>* x_trans = x.Transposition();
				Matrix<double>* x_prod = *x_trans * x;
				Matrix<double>* x_inv = x_prod->Inverse();
				Matrix<double>* x_final = *x_inv * *x_trans;
				delete x_trans;
				delete x_prod;
				delete x_inv;
				_theta = *x_final * y;
				delete x_final;
			}

			double LinearRegression::Predict(array<double>^ feature_vector)
			{
				if(_theta == 0) throw gcnew Exception("Unable to predict. Model not trained.");
				double ret = (*_theta)[0][0];
				int n = feature_vector->Length + 1;
				for(int i = 1; i < n; ++i)
					ret += ((*_theta)[i][0] * feature_vector[i - 1]);
				return ret;
			}

			array<double>^ LinearRegression::Predict(AI::Core::IO::IInput^ input)
			{
				if(_theta == 0) throw gcnew Exception("Unable to predict. Model not trained.");
				int m = input->TrainingExampleCount;
				int n = input->FeatureCount + 1;
				array<double>^ ret = gcnew array<double>(m);
				for(int t = 0; t < m; ++t)
				{
					ret[t] = (*_theta)[0][0];
					for(int i = 1; i < n; ++i)
						ret[t] += ((*_theta)[i][0] * input->AccessValue(t, i - 1));
				}
				return ret;
			}
		}
	}
}