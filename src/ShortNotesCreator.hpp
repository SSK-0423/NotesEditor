#pragma once
#include "INotesCreator.hpp"

namespace Engine
{
	class GameObject;
}

namespace NotesEditor
{
	class ShortNotesCreator : public INotesCreator {
	public:
		Notes* CreateNotes(const NotesData& notesData);
		Notes* CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList);
	};
}