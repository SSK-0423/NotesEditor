#pragma once
#include "INotesCreator.hpp"
#include "ShortNotes.hpp"

namespace Engine
{
	class GameObject;
}

namespace NotesEditor
{
	class SlideNotes;

	class SlideNotesCreator : public INotesCreator {
	private:
		// �n�_�m�[�c��u���^�C�~���O���ǂ���
		bool isStart;
		// �X���C�h�m�[�c�Ƃ��Ċm�肳���邩�ǂ���
		bool isEnd;
		std::vector<ShortNotes*> slideNotesList;
		SlideNotes* slideNotes;

	public:
		SlideNotesCreator();
		Notes* CreateNotes(const NotesData& notesData);
		Notes* CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList);
		void IsEnd();
		void Cancel(std::vector<Engine::GameObject*>& objList);
		void DeleteNotes(Engine::GameObject& notes);
		void Draw();
	};
}