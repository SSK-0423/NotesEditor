#include "Texture.hpp"
#include "Transform.hpp"
#include "DxLib.h"

void Game::Component::Texture::Draw()
{
	// 画像がセットされていない場合は描画しない
	if (imageHandle == -1) return;

	Position pos = parentTransform.GetPosition();
	Rotation rot = parentTransform.GetRotation();
	Size size = parentTransform.GetSize();

	float x = pos.GetPosX();
	float y = pos.GetPosY();
	float angle = rot.GetAngle();
	float width = size.GetWidth();
	float height = size.GetHeight();

	// 画像サイズ取得
	float imgWidth;
	float imgHeight;

	GetGraphSizeF(imageHandle, &imgWidth, &imgHeight);

	DrawRotaGraph3F(x, y, width / 2, height / 2,
					width / imgWidth, height / imgHeight,
					angle, imageHandle, false, false);
}

void Game::Component::Texture::LoadTexture(const char* path) const
{
	imageHandle = LoadGraph(path);
}
