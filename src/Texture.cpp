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

	// 画像サイズ取得
	GetGraphSizeF(imageHandle, &imgWidth, &imgHeight);
}

Engine::Components::Texture::Texture(const Transform& transform, const Position& pos, const char* path)
	: posX(0.f), posY(0.f), angle(0.f), imgWidth(1.f), imgHeight(1.f),
	drawScaleWidth(1.f), drawScaleHeight(1.f), imageHandle(-1), parentTransform(transform), parentScreenPos(&pos)
{
	imageHandle = LoadGraph(path);

	// 画像サイズ取得
	GetGraphSizeF(imageHandle, &imgWidth, &imgHeight);
}

Engine::Components::Texture::Texture(const Transform& transform, const Position& pos, Image handle)
	: posX(0.f), posY(0.f), angle(0.f), imgWidth(1.f), imgHeight(1.f),
	drawScaleWidth(1.f), drawScaleHeight(1.f), imageHandle(-1), parentTransform(transform), parentScreenPos(&pos)
{
	imageHandle = handle;
	// 画像サイズ取得
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
		// 座標取得
		posX = parentScreenPos->x;
		posY = parentScreenPos->y;
	}

	// 度数からラジアンへ変換
	angle = acosf(-1.f) / 180.f * rot.angle;

	float sizeWidth = size.width;
	float sizeHeight = size.height;

	// スケール取得
	float scaleWidth = size.scaleWidth;
	float scaleHeight = size.scaleHeight;

	// 描画時のスケール計算
	drawScaleWidth = static_cast<double>(sizeWidth / imgWidth) * scaleWidth;
	drawScaleHeight = static_cast<double>(sizeHeight / imgHeight) * scaleHeight;
}

void Engine::Components::Texture::Draw()
{
	// 画像がセットされていない場合は描画しない
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
