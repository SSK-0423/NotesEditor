#pragma once
#include "Game.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "DxLib.h"

class Texture{
private:
	// 画像
	mutable Image imageHandle;
	// 親オブジェクトのTransform
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
		
		// 画像描画
		DrawModiGraph(
			pos.x - size.width/ 2, pos.y - size.height / 2, //左上座標
			pos.x + size.width/ 2, pos.y - size.height / 2, //右上座標
			pos.x + size.width/ 2, pos.y + size.height / 2, //右下座標
			pos.x - size.width/ 2, pos.y + size.height / 2, //左下座標
			imageHandle, true);								//グラフィックハンドル、透過処理
	}

	// テクスチャ読み込み
	void LoadTexture(const char* path) const
	{
		imageHandle = LoadGraph(path);
	}
};