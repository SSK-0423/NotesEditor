#pragma once
#include "INotesCreator.hpp"
#include "BarManager.hpp"
#include "ShortNotes.hpp"
#include "LongNotes.hpp"
#include "NotesData.hpp"

namespace Engine
{
	class GameObject;
}

namespace NotesEditor
{
	class LongNotesCreator : public INotesCreator {
	private:
		static bool isStart;
		static ShortNotes* startNotes;
		static ShortNotes* endNotes;

	public:
		LongNotesCreator();
		~LongNotesCreator();
		Notes* CreateNotes(const NotesData& notesData);
		void CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList);
		void Cancel(std::vector<Engine::GameObject*>& objList);
		void DeleteNotes(Engine::GameObject& notes);

	};
}