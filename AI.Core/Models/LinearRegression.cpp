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

			CostFunctionReturnValue<double> LinearRegression::CostFunction(Matrix<double>* x, Matrix<double>* y, Matrix<double>* theta)
			{
				CostFunctionReturnValue<double> ret;
				ret.Cost = 0;
				int n_plus_1 = theta->ColumnCount();
				int m = x->RowCount();

				// h_of_theta = theta' * X';
				Matrix<double>* theta_transpose = theta->Transposition();
				Matrix<double>* x_transpose = x->Transposition();
				Matrix<double>* h_of_theta = (*theta_transpose) * (*x_transpose);
				delete x_transpose; delete theta_transpose;
				// J = sum((h_of_theta' - y) .^ 2) / (2 * m);
				Matrix<double>* h_of_theta_transpose = h_of_theta->Transposition();
				delete h_of_theta;
				Matrix<double>* diff = (*h_of_theta_transpose) - (*y);
				delete h_of_theta_transpose;
				Matrix<double>* diff2 = (*diff) ^ 2;
				ret.Cost = diff2->Sum() / (2 * m);
				delete diff2;

				// J_grad = ((h_of_theta' - y)' * X)' / m
				Matrix<double>* diff_transpose = diff->Transposition();
				delete diff;
				Matrix<double>* diff_x = (*diff_transpose) * (*x);
				delete diff_transpose;
				Matrix<double>* diff_x_trans = diff_x->Transposition();
				delete diff_x;
				(*diff_x_trans) /= m;
				ret.ParameterGradients = diff_x_trans;

				return ret;
			}

			void LinearRegression::TrainGradient(AI::Core::IO::IInputLinearRegression^ input, int max_iterations, double learning_rate)
			{
				int m = input->TrainingExampleCount;
				int n = input->FeatureCount;
				if(_theta != 0) delete _theta; _theta = new Matrix<double>(n + 1);

				for(int i = 0; i < max_iterations; ++i)
				{
					// theta = theta - alpha * CostFunction().ParameterGradients
					CostFunctionReturnValue<double> cost; // = CostFunction();
					Matrix<double>* grad = (*cost.ParameterGradients) * learning_rate;
					delete cost.ParameterGradients;
					(*_theta) -= *grad;
					delete grad;
				}

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