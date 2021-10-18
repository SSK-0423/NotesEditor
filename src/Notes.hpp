#pragma once
#include "GameObject.hpp"

/*
* �m�[�c�̊��N���X
*/

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
		// �����ߖڂ�
		int barNum;
		// 1���߂��ŏ��P�ʉ����ŕ��������ۂ�
		// 1���߂̊J�n�ʒu���牽�Ԗڂ̃��C���Ȃ̂�
		int lineNum;

		Engine::Components::ICollider* collider;
		Engine::Collision::PointWithPolygon* collision;

	public:
		Notes();
		virtual ~Notes();
		float GetTiming();
		int GetLane();
		int GetBarNum();
		int GetLineNum();
		virtual void Draw() = 0;
		virtual void Update() = 0;
		virtual void ChangedTransformByScale(float size, bool isScaleUp) = 0;
		virtual bool Collision(float x, float y) = 0;
		virtual NOTESTYPE GetNotesType() = 0;
	};

}