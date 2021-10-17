#pragma once
#include "Singleton.hpp"
#include "picojson.h"
#include <vector>

/*
* 譜面のJsonファイルを生成するクラス
*/

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
		void MakeLongNotesData(picojson::object& parentNotes, Notes& notes);
		void MakeSlideNotesData(picojson::object& parentNotes, Notes& notes);
		void MakeNotesDataList(picojson::object& fumen);
		void AddMusicInfo(picojson::object& fumen);
	public:
		~FumenJsonGenerator();
		void SetNotesList(std::vector<Notes*>& notesList);
		void SetNotesEditorMusic(NotesEditorMusic& notesEditorMusic);
		void SaveFumen();
	};
}