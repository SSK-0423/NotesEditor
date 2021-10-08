#pragma once
#include "GameObject.hpp"

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

	public:
		float GetTiming();
		int GetLane();
		NOTESTYPE GetNotesType();
		virtual void Draw() = 0;
		virtual void Update() = 0;
	};

}