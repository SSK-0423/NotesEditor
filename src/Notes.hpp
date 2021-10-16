#pragma once
#include "GameObject.hpp"

namespace Engine
{
	namespace Components
	{
		class ICollider;
	}
	namespace Collision
	{
		class PointWithPolygon;
	}
}

namespace NotesEditor
{
	enum class NOTESTYPE {
		SHORT_NOTES,		//�V���[�g�m�[�c
		LONG_NOTES,			//�����O�m�[�c
		SLIDE_NOTES,		//�X���C�h�m�[�c
		TYPENUM				//�m�[�c�̎�ސ�
	};

	class Notes : public Engine::GameObject {
	protected:
		// ����^�C�~���O
		float timing;
		// �m�[�c�������郌�[��
		int lane;

		Engine::Components::ICollider* collider;
		Engine::Collision::PointWithPolygon* collision;

	public:
		Notes();
		virtual ~Notes();
		float GetTiming();
		int GetLane();
		virtual void Draw() = 0;
		virtual void Update() = 0;
		virtual bool Collision(float x, float y) = 0;
		virtual NOTESTYPE GetNotesType() = 0;
	};

}