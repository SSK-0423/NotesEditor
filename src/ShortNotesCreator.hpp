#pragma once
#include "INotesCreator.hpp"
#include "Singleton.hpp"

namespace NotesEditor
{
	class ShortNotesCreator : public INotesCreator, public Singleton<ShortNotesCreator> {
		friend Singleton<ShortNotesCreator>;
	private:
		ShortNotesCreator();
	public:
		Notes* CreateNotes(const NotesData& notesData);
	};
}