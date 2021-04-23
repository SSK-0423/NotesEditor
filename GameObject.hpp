#pragma once
#include "Task.hpp"

// 座標
struct Vector2D {
	float x;
	float y;
};

class GameObject : public Task{
protected:

	// 画像ハンドル
	int imageHandle;

public:
	GameObject();
	~GameObject();

	// オブジェクトの座標
	Vector2D position;
	// オブジェクトの初期位置(当たり判定に使用)
	Vector2D collisionPos;

	// 画像の設定
	virtual void SetHandle(int handle) { imageHandle = handle; }
	// 位置の設定・更新
	virtual void SetPosition(float x, float y) {}

	// オブジェクトの高さ、幅
	int width;
	int height;
	
	virtual void Update();
	virtual void Draw();
};