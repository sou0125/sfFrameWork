#pragma once

#include "VertexBuffer.h"
#include <vector>
#include <map>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#pragma comment(lib,"assimp-vc143-mtd.lib")

namespace sf
{
	//�A�j���[�V�����p�{�[���̃E�F�C�g�N���X
	class Weight
	{
	public:
		std::string boneName;

		float weight = 0.0f;

		int	vertexindex = -1;
	};

	//�A�j���[�V�����p�{�[���N���X
	class Node
	{
	public:
		~Node();

		void Create(const aiNode* node);

	public:
		std::string boneName;

		std::vector<Node*> children;

	private:
		Node* parent = nullptr;
	};

	//�A�j���[�V�����̃{�[���N���X
	class Bone
	{
	public:
		void Set(const aiBone* bone);

		/// <summary>
		/// ���̃{�[���f�[�^���R�s�[����
		/// </summary>
		/// <param name="other"></param>
		void Copy(const Bone& other);

	private:
		static DirectX::XMMATRIX aiMtxToDxMtx(aiMatrix4x4 aimatrix);

	public:
		//�{�[����
		std::string boneName;

		//�v�Z���ʂƂȂ�e�q�֌W���l�������s��
		DirectX::XMMATRIX matrix = DirectX::XMMatrixIdentity();

		//�����̎��������l�����s��A���[�J���s��
		DirectX::XMMATRIX animationMatrix = DirectX::XMMatrixIdentity();

		//�{�[���I�t�Z�b�g�s��
		DirectX::XMMATRIX offsetMatrix = DirectX::XMMatrixIdentity();

		//�{�[���}�b�v�̒��Ő擪���牽�Ԗڂ�
		int index = -1;

		std::vector<Weight> weights;
	};

	//1�̃T�u�Z�b�g�������N���X
	class Subset
	{
	public:
		void Create(const aiMesh* mesh);

		//���_�z��擾
		const std::vector<dx::Vertex3D>& GetVertices()const { return vertices; }

		//�C���f�b�N�X�z��擾
		const std::vector<WORD>& GetIndices()const { return indices; }

		//���_��
		unsigned int VertexNum()const { return static_cast<unsigned int>(vertices.size()); }

		//�C���f�b�N�X��
		unsigned int IndexNum()const { return static_cast<unsigned int>(indices.size()); }

		//�}�e���A���C���f�b�N�X
		unsigned int MaterialIndex()const { return materialIdx; }

		const std::vector<Bone>& BoneData()const { return boneData; }

	public:
		//�J�n�C���f�b�N�X
		unsigned int indexBase = 0;

		//���_�x�[�X
		unsigned int vertexBase = 0;

	private:
		//���_�z��쐬�֐�
		void GetVerticesFromaiMesh(const aiMesh* aimesh);

		//�C���f�b�N�X�z��쐬�֐�
		void GetIndicesFromaiMesh(const aiMesh* aimesh);

	private:
		//�T�u�Z�b�g��
		std::string name;

		//�}�e���A���C���f�b�N�X
		unsigned int materialIdx = 0;

		//���_�z��
		std::vector<dx::Vertex3D> vertices;

		//�C���f�b�N�X�z��
		std::vector<WORD> indices;

		std::vector<Bone> boneData;
	};

	//�T�u�Z�b�g���W�߂��f�[�^�N���X
	class SubsetData
	{
	public:
		void Create(const aiScene* scene);

		const std::vector<Subset>& GetData()const { return datas; }
		const Subset& GetData(int i)const { return datas[i]; }

		const std::vector<dx::Vertex3D>& GetVertices()const { return vertices; }
		const std::vector<WORD>& GetIndices()const { return indices; }

	private:
		//�T�u�Z�b�g�̊J�n�ʒu���v�Z����֐�
		void CalcSubsetBases();

	private:
		std::vector<Subset> datas;

		//���_�z��(�E�F�C�g�f�[�^���͒�܂��Ă��Ȃ�)
		std::vector<dx::Vertex3D> vertices;

		//�C���f�b�N�X�z��
		std::vector<WORD> indices;

	};
}
