#pragma once
#include "App.h"

namespace app
{
	namespace test
	{
		class TestScene :public sf::Scene<TestScene>
		{
		public:
			void Init()override;

		private:
			//キューブの形状
			sf::geometry::GeometryCube g_cube;
		};
	}
}