#pragma once
#include "UI.h"
#include "Material.h"
namespace sf
{
	namespace ui
	{
		//UI`æNX
		class Image :public UI
		{
		public:
			void Draw()override;

		public:
			Material material;
		};
	}
}