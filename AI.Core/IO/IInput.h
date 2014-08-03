#pragma once
#include "../Stdafx.h"

namespace AI
{
	namespace Core
	{
		namespace IO
		{
			interface class IInput
			{
			public:
				double AccessValue(int training_example_index, int feature_index);
				property int TrainingExampleCount;
				property int FeatureCount;
			};

			interface class IInputLinearRegression : public IInput
			{
			public:
				double AccessActualOutput(int training_example_index);
			};
		}
	}
}