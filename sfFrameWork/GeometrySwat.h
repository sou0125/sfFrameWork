#pragma once
#include "App.h"
namespace app
{
	namespace test
	{
		class GeometrySwat :public sf::geometry::GeometryFbx
		{
		public:
			//�ǂݍ���
			void Load();

			//�`��(�I�[�o�[���C�h)
			void Draw(const sf::Material& mtl)override;

		protected:
			//�S�e�N�X�`���̓ǂݍ���(�I�[�o�[���C�h)
			void LoadTextures(const aiScene* scene)override;
		};
	}
}