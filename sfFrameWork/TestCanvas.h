#pragma once
#include "App.h"
namespace app
{
	namespace test
	{
		class TestCanvas :public sf::ui::Canvas
		{
		public:
			void Begin()override;

		private:
			//テクスチャ
			sf::Texture texture;
		};
	}
}