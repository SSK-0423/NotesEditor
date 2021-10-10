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
		// ����^�C�~���O�����ߐ��̖��[���W / �Ȃ̒��� * �m�[�c�̍��W
		float timing;
		// �m�[�c�̃��[��
		int lane;
		// �m�[�c�^�C�v
		NOTESTYPE type;

		Engine::Components::ICollider* collider;
		Engine::Collision::PointWithPolygon* collision;

	public:
		virtual ~Notes();
		float GetTiming();
		int GetLane();
		virtual bool Collision(float x, float y) = 0;
		virtual NOTESTYPE GetNotesType() = 0;
		virtual void Draw() = 0;
		virtual void Update() = 0;
	};

}