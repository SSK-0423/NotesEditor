#pragma once
#include "GameObject.hpp"
#include "IPlayable.hpp"
#include "Music.hpp"
#include "Game.hpp"
#include "KeyInput.hpp"
#include <vector>

class Camera2D : public GameObject, IPlayable{
private:
	// 描画対象オブジェクトのポインタ
	std::vector<std::vector<GameObject*>*>* objList; // objList[0] = objList objList->size() = 2 objList[0].size() = 2
	// カメラ内の描画可能オブジェクトのポインタ
	std::vector<GameObject*> drawList;
	// カメラの原点(左上座標)
	Position2D<float> origin;

	void UpdateOrigin();
	// カメラ内オブジェクトの更新処理
	void UpdateInCameraObj() noexcept;
	// カメラ内オブジェクトの描画
	void DrawInCameraObj() noexcept;
	// デバッグ用描画関数
	void DebugDraw() noexcept;
	// キーボード、マウス操作
	void Controll() noexcept override;
	// 移動限界
	void LimitPos() noexcept override;
	// オブジェクトがカメラ内に入ったかどうかを判定
	bool Collision(const GameObject& obj) noexcept;
	// オブジェクト間の距離を計算
	Vector2<float> CalcDistance(const Transform& targetTransform);
	// 2つのオブジェクトのサイズの合計値を計算
	Vector2<float> SumSize(const Transform& targetTransform);

public:
	Camera2D(std::vector<std::vector<GameObject*>*>& vec) noexcept;
	~Camera2D() noexcept;

	// 更新
	void Update() noexcept;
	// 描画
	void Draw() noexcept;
	// キー入力
	void Input() noexcept;
	// カメラ内オブジェクトリストの更新
	void UpdateDrawList() noexcept;
	// 描画対象オブジェクトのメモリ開放
	void DeleteObj() noexcept;
	// 移動限界をセット
	void SetMinposition(float x, float y) noexcept;
	void SetMaxposition(float x, float y) noexcept;

};