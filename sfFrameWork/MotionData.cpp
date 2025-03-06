#include "MotionData.h"
#include "Debug.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <DirectXMath.h>

void sf::motion::MotionData::LoadMotion(std::string path)
{
	Assimp::Importer importer;
	const aiScene* animScene = importer.ReadFile(
		path.c_str(),
		aiProcessPreset_TargetRealtime_MaxQuality |
		aiProcess_ConvertToLeftHanded |
		aiProcess_PopulateArmatureData);

	if (animScene == nullptr)
	{
		throw std::runtime_error("���[�V�����f�[�^�̓ǂݍ��݂Ɏ��s���܂���:" + path);
		return;
	}

	aiAnimation* anim = animScene->mAnimations[0];

	duration = anim->mDuration;

	datas.resize(duration);

	for (int t = 0; t < duration; t++)
	{
		for (int i = 0; i < anim->mNumChannels; i++)
		{
			//�g���m�[�h�A�j���[�V����
			aiNodeAnim* nodeAnim = anim->mChannels[i];

			int frame;

			frame = t % nodeAnim->mNumRotationKeys;
			aiQuaternion rot = nodeAnim->mRotationKeys[frame].mValue;

			frame = t % nodeAnim->mNumPositionKeys;
			aiVector3D pos = nodeAnim->mPositionKeys[frame].mValue;


			//---�A�j���[�V�����s��쐬---
			//�N�H�[�^�j�I���쐬
			DirectX::XMVECTOR _rotation = DirectX::XMVectorSet(rot.x, rot.y, rot.z, rot.w);

			//�X�P�[����1,1,1
			DirectX::XMMATRIX scalemtx = DirectX::XMMatrixScaling(1, 1, 1);

			//�N�H�[�^�j�I�������]�s����Z�o
			DirectX::XMMATRIX rotmtx = DirectX::XMMatrixRotationQuaternion(_rotation);

			//�ړ��s��쐬
			DirectX::XMMATRIX transmtx = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);

			datas[t][nodeAnim->mNodeName.C_Str()] = scalemtx * rotmtx * transmtx;
		}
	}

	debug::Debug::LogSafety("���[�V�����̓ǂݍ��݂ɐ������܂���:" + path);
}

DirectX::XMMATRIX sf::motion::MotionData::GetMatrix(int frame, std::string nodeName) const
{
	auto it = datas[frame % duration].find(nodeName);

	if (it != datas[frame % duration].end())
	{
		return it->second;
	}

	return DirectX::XMMatrixIdentity();
}
