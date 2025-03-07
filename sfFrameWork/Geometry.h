#pragma once
#include "DirectX11.h"
#include "Ref.h"
#include "Material.h"
#include <map>
#include <source_location>

namespace sf
{
	namespace geometry
	{
		//形状基底クラス
		class Geometry :public sf::ref::autoRef<Geometry>
		{
		public:
			virtual void Draw(const Material& mtl) = 0;
		};
	}
}