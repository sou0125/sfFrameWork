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
			//�L���[�u�̌`��
			sf::geometry::GeometryCube g_cube;
		};
	}
}