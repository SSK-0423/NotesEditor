#pragma once
#include "Game.hpp"
#include "Object.hpp"
class GameObject : public Object{
protected:

	// 画像ハンドル
	int imageHandle;

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

	virtual void Update() noexcept;
	virtual void Draw() noexcept;
};

//class GameObject : public Object {
//protected:
//	Transform transform;
//public:
//	GameObject();
//	~GameObject();
////	virtual void Update() noexcept;
////	virtual void Draw() noexcept;
//};
//
//int main() {
//	GameObject obj;
//	obj.GetComponent<Transform>().
//}
