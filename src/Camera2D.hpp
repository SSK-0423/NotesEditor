#pragma once
#include "GameObject.hpp"
#include "IPlayable.hpp"
#include "GameSymbol.hpp"
#include "Transform.hpp"
#include "TestObject.h"
#include <vector>

namespace Engine
{
	class Camera2D : public GameObject, IPlayable {
	private:
		// 描画対象オブジェクトのポインタ
		std::vector<std::vector<GameObject*>*>* objList; // objList[0] = objList objList->size() = 2 objList[0].size() = 2
		// カメラ内の描画可能オブジェクトのポインタ
		std::vector<GameObject*> drawList;
		// カメラの原点(左上座標)
		Components::Position origin;

		void UpdateOrigin();
		// カメラ内オブジェクトの更新処理
		void UpdateInCameraObj();
		// カメラ内オブジェクトの描画
		void DrawInCameraObj();
		// デバッグ用描画関数
		void DebugDraw();
		// キーボード、マウス操作
		void Controll() override;
		// 移動限界
		void LimitPos() override;
		// オブジェクトがカメラ内に入ったかどうかを判定
		bool Collision(const GameObject& obj);
		// オブジェクト間の距離を計算
		Vector2<float> CalcDistance(const Components::Transform& targetTransform);
		// 2つのオブジェクトのサイズの合計値を計算
		Components::Size SumSize(const Components::Transform& targetTransform);

	public:
		Camera2D();
		Camera2D(std::vector<std::vector<GameObject*>*>& vec);
		~Camera2D();

		void Update();
		void Draw();
		// カメラ内オブジェクトリストの更新
		void UpdateDrawList();
		// 描画対象オブジェクトのメモリ開放
		void DeleteObj();
		// 移動限界をセット
		void SetMinposition(float x, float y);
		void SetMaxposition(float x, float y);

	};
}