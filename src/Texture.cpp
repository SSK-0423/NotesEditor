#include "Texture.hpp"
#include "Transform.hpp"
#include "DxLib.h"
#include "TestObject.h"
#include <cmath>

Engine::Components::Texture::Texture(const Transform& transform, const char* path)
	: posX(0.f), posY(0.f), angle(0.f), imgWidth(1.f), imgHeight(1.f),
	drawScaleWidth(1.f), drawScaleHeight(1.f), imageHandle(-1), parentTransform(transform)
{
	parentScreenPos = nullptr;

	imageHandle = LoadGraph(path);

	// �摜�T�C�Y�擾
	GetGraphSizeF(imageHandle, &imgWidth, &imgHeight);
}

Engine::Components::Texture::Texture(const Transform& transform, const Position& pos, const char* path)
	: posX(0.f), posY(0.f), angle(0.f), imgWidth(1.f), imgHeight(1.f),
	drawScaleWidth(1.f), drawScaleHeight(1.f), imageHandle(-1), parentTransform(transform), parentScreenPos(&pos)
{
	imageHandle = LoadGraph(path);

	// �摜�T�C�Y�擾
	GetGraphSizeF(imageHandle, &imgWidth, &imgHeight);
}

Engine::Components::Texture::Texture(const Transform& transform, const Position& pos, Image handle)
	: posX(0.f), posY(0.f), angle(0.f), imgWidth(1.f), imgHeight(1.f),
	drawScaleWidth(1.f), drawScaleHeight(1.f), imageHandle(-1), parentTransform(transform), parentScreenPos(&pos)
{
	imageHandle = handle;
	// �摜�T�C�Y�擾
	GetGraphSizeF(imageHandle, &imgWidth, &imgHeight);
}

void Engine::Components::Texture::Update()
{
	Rotation rot = parentTransform.GetRotation();
	Size size = parentTransform.GetSize();

	if (parentScreenPos == nullptr)
	{
		posX = parentTransform.GetPosition().x;
		posY = parentTransform.GetPosition().y;
	}
	else
	{
		// ���W�擾
		posX = parentScreenPos->x;
		posY = parentScreenPos->y;
	}

	// �x�����烉�W�A���֕ϊ�
	angle = acosf(-1.f) / 180.f * rot.angle;

	float sizeWidth = size.width;
	float sizeHeight = size.height;

	// �X�P�[���擾
	float scaleWidth = size.scaleWidth;
	float scaleHeight = size.scaleHeight;

	// �`�掞�̃X�P�[���v�Z
	drawScaleWidth = static_cast<double>(sizeWidth / imgWidth) * scaleWidth;
	drawScaleHeight = static_cast<double>(sizeHeight / imgHeight) * scaleHeight;
}

void Engine::Components::Texture::Draw()
{
	// �摜���Z�b�g����Ă��Ȃ��ꍇ�͕`�悵�Ȃ�
	if (imageHandle == -1) return;

	DrawRotaGraph3F(posX, posY, imgWidth / 2.f, imgHeight / 2.f,
		drawScaleWidth, drawScaleHeight, angle, imageHandle, true, false);
}

void Engine::Components::Texture::LoadTexture(const char* path) const
{
	imageHandle = LoadGraph(path);
}

void Engine::Components::Texture::GetTextureSize(float& w, float& h) const
{
	w = imgWidth;
	h = imgHeight;
}

void Engine::Components::Texture::SetImage(Image handle)
{
	imageHandle = handle;
}
