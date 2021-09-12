#pragma once
#include "Game.hpp"
#include "Object.hpp"

class GameObject{
protected:

	// 画像ハンドル
	Image imageHandle;

	// オブジェクトの高さ、幅
	int width;
	int height;

public:
	GameObject() noexcept;
	~GameObject() noexcept;

	// オブジェクトの描画座標
	Position<float> position;
	// オブジェクトの座標
	Position<float> collisionPos;

	// 画像の設定
	void SetHandle(int handle) noexcept;
	// 位置の設定・更新
	void SetPosition(float x, float y) noexcept;
	// 幅の取得
	int GetObjWidth() noexcept;
	// 高さの取得
	int GetObjHeight() noexcept;

	virtual void Update() = 0;
	virtual void Draw() = 0;
};