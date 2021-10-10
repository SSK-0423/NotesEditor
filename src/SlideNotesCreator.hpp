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
		// 始点ノーツを置くタイミングかどうか
		bool isStart;
		// スライドノーツとして確定させるかどうか
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