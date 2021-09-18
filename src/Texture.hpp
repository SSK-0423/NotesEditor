#pragma once
#include "Game.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "DxLib.h"

class Texture{
private:
	// �摜
	mutable Image imageHandle;
	// �e�I�u�W�F�N�g��Transform
	const Transform& parentTransform;

public:
	Texture(const Transform& transform) : imageHandle(-1),parentTransform(transform)
	{
	}
	
	void Draw()
	{
		if (imageHandle == -1) return;
		
		Position2D<float> pos = parentTransform.GetPosition();
		Size2D<float> size = parentTransform.GetSize();
		
		// �摜�`��
		DrawModiGraph(
			pos.x - size.width/ 2, pos.y - size.height / 2, //������W
			pos.x + size.width/ 2, pos.y - size.height / 2, //�E����W
			pos.x + size.width/ 2, pos.y + size.height / 2, //�E�����W
			pos.x - size.width/ 2, pos.y + size.height / 2, //�������W
			imageHandle, true);								//�O���t�B�b�N�n���h���A���ߏ���
	}

	// �e�N�X�`���ǂݍ���
	void LoadTexture(const char* path) const
	{
		imageHandle = LoadGraph(path);
	}
};