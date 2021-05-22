#pragma once
#include "Task.hpp"
#include "GameObject.hpp"
#include "PlayableObj.hpp"
#include <vector>
#include "Music.hpp"

class Camera2D : public GameObject, PlayableObj {
private:
	// 描画対象オブジェクトのポインタ
	std::vector<std::vector<GameObject*>*>* objList; // objList[0] = objList objList->size() = 2 objList[0].size() = 2
	// カメラ内の描画可能オブジェクトのポインタ
	std::vector<GameObject*> drawList;

	//カメラ内オブジェクトの更新処理
	void InCameraObjUpdate() noexcept;
	//カメラ内オブジェクトの描画
	void InCameraObjDraw() noexcept;
	//デバッグ用描画関数
	void DebugDraw() noexcept;
	//キーボード、マウス操作
	void Controll() noexcept override;
	//移動限界
	void PosLimit() noexcept override;

public:
	Camera2D(std::vector<std::vector<GameObject*>*>& vec) noexcept;
	~Camera2D() noexcept;

	//更新
	void Update() noexcept;
	//描画
	void Draw() noexcept;
	// カメラ内オブジェクトリストの更新
	void UpdateDrawList() noexcept;
	// 描画対象オブジェクトのメモリ開放
	void DeleteObj() noexcept;

	//移動限界
	void SetMinposition(float x, float y) noexcept;
	void SetMaxposition(float x, float y) noexcept;

	//オブジェクトがカメラ内に入ったかどうかを判定
	bool Collision(GameObject& obj) const noexcept;
};