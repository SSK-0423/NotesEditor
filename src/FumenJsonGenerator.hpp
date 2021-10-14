#pragma once
#include "Singleton.hpp"
#include <vector>

namespace NotesEditor
{
	class Notes;
	class NotesEditorMusic;

	class FumenJsonGenerator : public Singleton<FumenJsonGenerator>
	{
		friend Singleton<FumenJsonGenerator>;
	private:
		FumenJsonGenerator();
		void QuickSort(std::vector<Notes*>& notesList, int left, int right);
		std::vector<Notes*>* notesList;
		NotesEditorMusic* notesEditorMusic;
	public:
		~FumenJsonGenerator();
		void SetNotesList(std::vector<Notes*>& notesList);
		void SetNotesEditorMusic(NotesEditorMusic& notesEditorMusic);
		void SaveFumen();
	};
}