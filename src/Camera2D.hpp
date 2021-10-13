#pragma once
#include "GameObject.hpp"
#include "IPlayable.hpp"
#include "GameSymbol.hpp"
#include "Transform.hpp"
#include "TestObject.h"
#include <vector>

namespace Engine
{
	namespace Collider 
	{
		class ICollider;
	}
	
	namespace Collision
	{
		class RectWithRect;
	}

	class Camera2D : public GameObject, IPlayable {
	private:
		// 描画対象オブジェクトのポインタ
		std::vector<Engine::GameObject*>& objList;
		// カメラ内の描画可能オブジェクトのポインタ
		std::vector<GameObject*> drawList;
		// カメラの原点(左上座標)
		Components::Position origin;
		
		// カメラの原点座標更新
		void UpdateOrigin();
		// カメラ内オブジェクトリストの更新
		void UpdateDrawList();
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

		void AutoScroll();
	public:
		Camera2D(std::vector<Engine::GameObject*>& objList);
		~Camera2D();

		void Update();
		void Draw();
		// 描画対象オブジェクトのメモリ開放
		void DeleteObj();
		// カメラの原点座標取得
		Components::Position GetOriginPos();
		// 移動限界をセット
		void SetMinposition(float x, float y);
		void SetMaxposition(float x, float y);

	};
}