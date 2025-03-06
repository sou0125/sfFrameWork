#pragma once
#include "App.h"
#include "GeometrySwat.h"
#include "SwatMotionArray.h"
namespace app
{
	namespace test
	{
		class DynamicScene :public sf::Scene<DynamicScene>
		{
		public:
			void Init()override;

		private:
			sf::geometry::GeometrySphere g_sphere;

			//�l�^���f��
			GeometrySwat g_human;

			//�l�^���[�V�����A���C
			SwatMotionArray ma_human;
		};
	}
}