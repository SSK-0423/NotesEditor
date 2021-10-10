#pragma once
#include "Notes.hpp"
#include "NotesData.hpp"
#include <vector>

namespace NotesEditor
{
	class INotesCreator {
	public:
		virtual Notes* CreateNotes(const NotesData& notesData) = 0;
		virtual Notes* CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList) = 0;
	};
}