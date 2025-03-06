#include "GeometrySwat.h"

void app::test::GeometrySwat::Load()
{
	//Swat���f���̓ǂݍ���
	LoadFbx("Assets\\Model\\Swat.fbx");
}

void app::test::GeometrySwat::Draw(const sf::Material& mtl)
{
	sf::dx::DirectX11* dx11 = sf::dx::DirectX11::Instance();

	//�}�e���A���ݒ�(diffuse�e�N�X�`��,�@���e�N�X�`������)
	mtl.SetGPU(dx11->GetMainDevice(), true, true);

	//�e�o�b�t�@�̐ݒ�
	vertexBuffer.SetGPU(dx11->GetMainDevice());
	indexBuffer.SetGPU(dx11->GetMainDevice());

	//�g�|���W�[�ƃV�F�[�_�[�ݒ�
	dx11->GetMainDevice().GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	dx11->vsMotion.SetGPU(dx11->GetMainDevice());
	dx11->gsNone.SetGPU(dx11->GetMainDevice());
	dx11->ps3d.SetGPU(dx11->GetMainDevice());

	const std::vector<sf::Subset>& subsets = subsetData.GetData();

	//�T�u�Z�b�g�ʕ`�揈��(�����_��)
	auto draw = [](const sf::Subset& subset)
		{
			sf::dx::DirectX11::Instance()->
				GetMainDevice().
				GetContext()->
				DrawIndexed(subset.IndexNum(), subset.indexBase, subset.vertexBase);
		};


	//�T�u�Z�b�g0:�w�����b�g
	//�T�u�Z�b�g1:��
	//�T�u�Z�b�g2:��

	textures[0].SetGPU(0, dx11->GetMainDevice());	//diffuse�e�N�X�`��
	textures[1].SetGPU(1, dx11->GetMainDevice());	//�@���e�N�X�`��
	draw(subsets[0]);//�w�����b�g
	draw(subsets[2]);//��

	textures[3].SetGPU(0, dx11->GetMainDevice());	//diffuse�e�N�X�`��
	textures[4].SetGPU(1, dx11->GetMainDevice());	//�@���e�N�X�`��
	draw(subsets[1]);//��
}

void app::test::GeometrySwat::LoadTextures(const aiScene* scene)
{
	//�e�N�X�`����6��
	const int textureNum = 6;

	textures.resize(textureNum);

	textures[0].LoadTexture(scene->mTextures[0]);//�x�[�X�J���[(��)
	textures[1].LoadTexture(scene->mTextures[1]);//�@���J���[(��)
	textures[2].LoadTexture(scene->mTextures[2]);//��J���[(��)

	textures[3].LoadTexture(scene->mTextures[3]);//�x�[�X�J���[(��)
	textures[4].LoadTexture(scene->mTextures[4]);//�@���J���[(��)
	textures[5].LoadTexture(scene->mTextures[5]);//��J���[(��)
}
