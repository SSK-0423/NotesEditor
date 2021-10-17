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
		// �I�u�W�F�N�g�̈ʒu�E�T�C�Y
		Components::Transform* transform;
		// �`��p���W
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