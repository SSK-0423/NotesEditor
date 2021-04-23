#pragma once
#include "Task.hpp"
#include "GameObject.hpp"
#include <vector>
#include "Music.hpp"

class Camera2D : public GameObject{
private:
	// 描画対象オブジェクトのポインタ
	std::vector<GameObject*> objList;
	// カメラ内の描画可能オブジェクトのポインタ
	std::vector<GameObject*> drawList;

public:
	Camera2D();
	~Camera2D();

	//カメラのスクロール限界
	Vector2D minPos;	//下限
	Vector2D maxPos;	//上限

	//描画対象オブジェクトに追加
	void SetObject(GameObject* obj);
	// カメラ内オブジェクトリストの更新
	void UpdateDrawList();
	// 描画対象オブジェクトのメモリ開放
	void DeleteObj();

	void Update();
	void Draw();

	void SetPosition(float x, float y);
	void SetMinPosition(float x, float y);
	void SetMaxPosition(float x, float y);
	bool Collision(const GameObject& obj) const;
};