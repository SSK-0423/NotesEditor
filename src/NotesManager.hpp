#pragma once
#include <vector>
#include "Notes.hpp"
#include "BarManager.hpp"
#include "NotesCreator.hpp"
#include "ShortNotesCreator.hpp"
#include "LongNotesCreator.hpp"
#include "SlideNotesCreator.hpp"

namespace Engine
{
	class GameObject;
}

namespace NotesEditor
{
	typedef enum NOTESTYPE {
		SHORT_NOTES,		//�V���[�g�m�[�c
		LONG_NOTES,			//�����O�m�[�c
		SLIDE_NOTES,		//�X���C�h�m�[�c
		TYPENUM				//�m�[�c�̎�ސ�
	};

	//�m�[�c�Ǘ��N���X
	class NotesManager {
	private:
		static NOTESTYPE type;						//�m�[�c�^�C�v
		std::vector<Engine::GameObject*> notesList;				//�m�[�c���X�g
		unsigned int color;
		//ShortNotesCreator shortNotesCreator;		//�V���[�g�m�[�c�쐬�N���X
		//LongNotesCreator longNotesCreator;			//�����O�m�[�c�쐬�N���X
		//SlideNotesCreator slideNotesCreator;		//�X���C�h�m�[�c�쐬�N���X
		bool IsExist(float& x, float& y);	//�m�[�c�̓�d�z�u���m

	public:
		NotesManager();
		void ChangeNotesTypeShort();
		void ChangeNotesTypeLong();
		void ChangeNotesTypeSlide();
		void Update();
		void Draw();
		std::vector<Engine::GameObject*>* GetListRef();
		void CreateNotes(float& x, float& y);
		void DeleteNotes(float& x, float& y);
		void DeleteObj();
	};
}