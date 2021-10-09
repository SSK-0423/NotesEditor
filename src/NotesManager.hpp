#pragma once
#include <vector>
#include "Singleton.hpp"
#include "Notes.hpp"
#include "GameSymbol.hpp"
#include "INotesCreator.hpp"
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
	struct NotesData;

	//�m�[�c�Ǘ��N���X
	class NotesManager : public Singleton<NotesManager> {
		friend Singleton<NotesManager>;
	private:
		NotesManager();
		static NOTESTYPE type;						//�m�[�c�^�C�v
		std::vector<Notes*> notesList;				//�m�[�c���X�g
		Color color;
		ShortNotesCreator shortNotesCreator;
		LongNotesCreator longNotesCreator;
		SlideNotesCreator slideNotesCreator;
		bool IsExist(float x, float y);				//�m�[�c�̓�d�z�u���m

	public:
		void ChangeNotesTypeShort();
		void ChangeNotesTypeLong();
		void ChangeNotesTypeSlide();
		void Update();
		void Draw();
		void CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList);
		void DeleteNotes(float x, float y);
		void DeleteObj();
	};
}