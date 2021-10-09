#pragma once
#include "INotesCreator.hpp"
#include "ShortNotes.hpp"

namespace Engine
{
	class GameObject;
}

namespace NotesEditor
{
	class SlideNotesCreator : public INotesCreator {
	private:
		bool isEnd;
		std::vector<ShortNotes*> slideNotesList;
	public:
		SlideNotesCreator();
		Notes* CreateNotes(const NotesData& notesData);
		void CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList);
		void IsEnd();
		void Cancel(std::vector<Engine::GameObject*>& objList);
		void DeleteNotes(Engine::GameObject& notes);
		void Draw();
	};
}