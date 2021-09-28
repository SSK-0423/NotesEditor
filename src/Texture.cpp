#include "Texture.hpp"
#include "Transform.hpp"
#include "DxLib.h"
#include <cmath>

Component::Texture::Texture(const Transform& transform, const char* path) : imageHandle(-1), parentTransform(transform)
{
	imageHandle = LoadGraph(path);

	// �摜�T�C�Y�擾
	GetGraphSizeF(imageHandle, &imgWidth, &imgHeight);
}

void Component::Texture::Update()
{
	Position pos = parentTransform.GetPosition();
	Rotation rot = parentTransform.GetRotation();
	Size size = parentTransform.GetSize();

	posX = pos.GetPosX();
	posY = pos.GetPosY();
	// �x�����烉�W�A���֕ϊ�
	angle = acosf(-1.f) / 180.f * rot.GetAngle();

	sizeWidth = size.GetWidth();
	sizeHeight = size.GetHeight();
}

void Component::Texture::Draw()
{
	// �摜���Z�b�g����Ă��Ȃ��ꍇ�͕`�悵�Ȃ�
	if (imageHandle == -1) return;

	DrawRotaGraph3F(posX, posY, imgWidth / 2.f, imgHeight / 2.f,
		sizeWidth / imgWidth, sizeHeight / imgHeight,
		angle, imageHandle, false, false);
}

void Component::Texture::LoadTexture(const char* path) const
{
	imageHandle = LoadGraph(path);
}

void Component::Texture::GetTextureSize(float& w, float& h) const
{
	w = imgWidth;
	h = imgHeight;
}
