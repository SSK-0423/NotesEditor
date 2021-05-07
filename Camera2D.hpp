#pragma once
#include "Task.hpp"
#include "GameObject.hpp"
#include "PlayableObj.hpp"
#include <vector>
#include "Music.hpp"

class Camera2D : public GameObject, PlayableObj {
private:
	// 描画対象オブジェクトのポインタ
	std::vector<GameObject*> objList;
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
	Camera2D() noexcept;
	~Camera2D() noexcept;

	//更新
	void Update() noexcept;
	//描画
	void Draw() noexcept;
	//描画対象オブジェクトに追加
	void SetObject(GameObject& obj) noexcept;
	// カメラ内オブジェクトリストの更新
	void UpdateDrawList() noexcept;
	// 描画対象オブジェクトのメモリ開放
	void DeleteObj() noexcept;

	//移動限界
	void SetMinPosition(float x, float y) noexcept;
	void SetMaxPosition(float x, float y) noexcept;

	//オブジェクトがカメラ内に入ったかどうかを判定
	bool Collision(GameObject& obj) const noexcept;
};