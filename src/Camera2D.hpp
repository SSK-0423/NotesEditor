#pragma once
#include "GameObject.hpp"
#include "GameUtility.hpp"
#include "Transform.hpp"
#include "Vector2.hpp"
#include <vector>

namespace Engine
{
	namespace Collider
	{
		class ICollider;
	}

	class Camera2D : public GameObject {
	private:
		std::vector<Engine::GameObject*>& objList;
		std::vector<GameObject*> drawList;
		Components::Position origin;
		Vector2<float> minLimitPos;
		Vector2<float> maxLimitPos;
		float speed;
		void UpdateOrigin();
		void UpdateDrawList();
		void UpdateInCameraObj();
		void DrawInCameraObj();
		void LimitPos();
		void Input();
		void AutoScroll();
		// オブジェクトがカメラ枠に入っているか判定
		bool Collision(const GameObject& obj);
		Vector2<float> CalcDistance(const Components::Transform& targetTransform);
		Components::Size SumSize(const Components::Transform& targetTransform);
	public:
		Camera2D(std::vector<Engine::GameObject*>& objList);
		~Camera2D();
		void Update() override;
		void Draw() override;
		void Delete();
		Components::Position GetOriginPos();
		// 移動限界をセット
		void SetMinPosition(float x, float y);
		void SetMaxPosition(float x, float y);
		void ChangedScrollSpeed(float speed);
	};
}