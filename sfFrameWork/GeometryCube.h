#pragma once
#include "Geometry.h"

namespace sf
{
	namespace geometry
	{
		//�`��N���X-������
		class GeometryCube :public Geometry
		{
		public:
			void Draw(const Material& mtl)override;

		};
	}
}