#pragma once
#include "INotesCreator.hpp"
#include "Singleton.hpp"

/*
* �V���[�g�m�[�c�����N���X
*/

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