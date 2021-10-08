#pragma once
#include <vector>
#include "Singleton.hpp"
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
	class Notes;



	//�m�[�c�Ǘ��N���X
	class NotesManager : public Singleton<NotesManager> {
		friend Singleton<NotesManager>;
	private:
		NotesManager();
		static NOTESTYPE type;						//�m�[�c�^�C�v
		std::vector<Notes*> notesList;				//�m�[�c���X�g
		unsigned int color;
		//ShortNotesCreator shortNotesCreator;		//�V���[�g�m�[�c�쐬�N���X
		//LongNotesCreator longNotesCreator;		//�����O�m�[�c�쐬�N���X
		//SlideNotesCreator slideNotesCreator;		//�X���C�h�m�[�c�쐬�N���X
		bool IsExist(float& x, float& y);	//�m�[�c�̓�d�z�u���m

	public:
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