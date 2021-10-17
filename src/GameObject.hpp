#pragma once
#include "GameUtility.hpp"

namespace Engine
{
	namespace Components
	{
		class Transform;
		class Position;
	}

	class GameObject {
	protected:
		// オブジェクトの位置・サイズ
		Components::Transform* transform;
		// 描画用座標
		Components::Position* screenPos;
		float beforePos;

	public:
		GameObject();
		virtual ~GameObject();
		const Components::Transform& GetTransform() const;
		Components::Transform& GetTransform();
		const Components::Position GetScreenPos() const;
		Components::Position GetScreenPos();
		void UpdateScreenPos(Components::Position pos);
		virtual void Update() = 0;
		virtual void Draw() = 0;
	};
}