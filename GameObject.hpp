#pragma once
#include "Task.hpp"
#include "Vector2D.hpp"

class GameObject : public Task{
protected:

	// 画像ハンドル
	int imageHandle;

public:
	GameObject() noexcept;
	~GameObject() noexcept;

	// オブジェクトの座標
	Vector2D position;
	// オブジェクトの初期位置(当たり判定に使用)
	Vector2D collisionPos;

	// 画像の設定
	void SetHandle(int handle) noexcept;
	// 位置の設定・更新
	void SetPosition(float x, float y) noexcept;

	// オブジェクトの高さ、幅
	int width;
	int height;
	
	virtual void Update() noexcept;
	virtual void Draw() noexcept;
};