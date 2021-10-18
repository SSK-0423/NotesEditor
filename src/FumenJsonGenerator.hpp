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
		bool isSaveComplete;
		std::vector<Notes*>* notesList;
		NotesEditorMusic* notesEditorMusic;
		void DrawSaveText();
		void QuickSort(std::vector<Notes*>& notesList, size_t left, size_t right);
		void MakeLongNotesData(picojson::object& parentNotes, Notes& notes);
		void MakeSlideNotesData(picojson::object& parentNotes, Notes& notes);
		void MakeNotesDataList(picojson::object& fumen);
		void AddMusicInfo(picojson::object& fumen);
		void SaveCompleted();
	public:
		~FumenJsonGenerator();
		void Draw();
		void SetNotesList(std::vector<Notes*>& notesList);
		void SetNotesEditorMusic(NotesEditorMusic& notesEditorMusic);
		void SaveFumen();
		void NotSaveCompleted();
	};
}