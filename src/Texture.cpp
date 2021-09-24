#include "Texture.hpp"
#include "Transform.hpp"
#include "DxLib.h"
#include <cmath>

Game::Component::Texture::Texture(const Transform& transform, const char* path) : imageHandle(-1), parentTransform(transform)
{
	imageHandle = LoadGraph(path);

	// 画像サイズ取得
	GetGraphSizeF(imageHandle, &imgWidth, &imgHeight);
}

void Game::Component::Texture::Draw()
{
	// 画像がセットされていない場合は描画しない
	if (imageHandle == -1) return;

	Position pos = parentTransform.GetPosition();
	Rotation rot = parentTransform.GetRotation();
	Size size = parentTransform.GetSize();

	float x = pos.GetPosX();
	float y = pos.GetPosY();
	// 度数からラジアンへ変換
	float angle = acosf(-1.f) / 180.f * rot.GetAngle();

	float width = size.GetWidth();
	float height = size.GetHeight();

	DrawRotaGraph3F(x, y, imgWidth / 2.f, imgHeight / 2.f,
		width / imgWidth, height / imgHeight,
		angle, imageHandle, false, false);
}

void Game::Component::Texture::LoadTexture(const char* path) const
{
	imageHandle = LoadGraph(path);
}

void Game::Component::Texture::GetTextureSize(float& w, float& h) const
{
	w = imgWidth;
	h = imgHeight;
}
