#include "Texture.hpp"
#include "Transform.hpp"
#include "GameUtility.hpp"
#include "DxLib.h"
#include <cmath>

Engine::Components::Texture::Texture(const Transform& transform, const char* path)
	: posX(0.f), posY(0.f), angle(0.f), imgWidth(1.f), imgHeight(1.f),
	drawScaleWidth(1.f), drawScaleHeight(1.f), imageHandle(NONE), parentTransform(transform)
{
	imageHandle = LoadGraph(path);

	GetGraphSizeF(imageHandle, &imgWidth, &imgHeight);
}

void Engine::Components::Texture::Update()
{
	UpdatePos();
	UpdateAngle();
	UpdateDrawScale();
}

void Engine::Components::Texture::Draw()
{
	if (imageHandle == NONE) return;

	DrawRotaGraph3F(posX, posY, imgWidth / 2.f, imgHeight / 2.f,
		drawScaleWidth, drawScaleHeight, angle, imageHandle, false, false);
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


void Engine::Components::Texture::UpdatePos()
{
	Position pos = parentTransform.GetPosition();
	posX = pos.x;
	posY = pos.y;
}

void Engine::Components::Texture::UpdateAngle()
{
	Rotation rot = parentTransform.GetRotation();
	angle = DegreeToRadian(rot.angle);
}

void Engine::Components::Texture::UpdateDrawScale()
{
	Size size = parentTransform.GetSize();
	drawScaleWidth = CalcDrawScaleWidth(size);
	drawScaleHeight = CalcDrawScaleHeight(size);
}

double Engine::Components::Texture::CalcDrawScaleWidth(const Size& size)
{
	float sizeWidth = size.width;
	float scaleWidth = size.scaleWidth;
	// DrawRotaGraphF�̑�5��6�����͌��̉摜�T�C�Y�Ɉˑ������{���Ȃ̂ŁA
	// ���g���w�肵���T�C�Y�Ɖ摜�T�C�Y�Ƃ̔䗦����ɂ����`��{�������߂邱�Ƃ�
	// ���܂����킹�� (���������l)
	return static_cast<double>(sizeWidth / imgWidth) * scaleWidth;
}

double Engine::Components::Texture::CalcDrawScaleHeight(const Size& size)
{
	float sizeHeight = size.height;
	float scaleHeight = size.scaleHeight;
	return static_cast<double>(sizeHeight / imgHeight) * scaleHeight;
}
