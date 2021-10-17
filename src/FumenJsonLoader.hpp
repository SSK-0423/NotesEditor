#pragma once
#include "Singleton.hpp"
#include "NotesData.hpp"
#include "picojson.h"
#include <vector>

/*
	譜面ファイルを読み込むクラス
*/

namespace Engine
{
	class GameObject;
}

namespace NotesEditor
{
	class Notes;
	class ShortNotes;
	class LongNotes;
	class SlideNotes;
	class NotesEditorMusic;
	enum class NOTESTYPE;

	class FumenJsonLoader : public Singleton<FumenJsonLoader>
	{
		friend Singleton<FumenJsonLoader>;
	private:
		FumenJsonLoader();
		std::vector<Engine::GameObject*>* objList;
		std::vector<Notes*>* notesList;
		NotesEditorMusic* notesEditorMusic;

		void DeleteExitNotes();
		float GetPosX(NOTESTYPE parentType, int lane);
		float CalcPosY(float timing);
		void CreateNotesFromFumen(picojson::value fumen);
		NotesData MakeNotesData(picojson::value notesVal, NOTESTYPE parentType);
		Notes* CreateNotes(picojson::value notesVal, NOTESTYPE type);
		ShortNotes* CreateShortNotes(picojson::value notesVal, NOTESTYPE type);
		LongNotes* CreateLongNotes(picojson::value notesVal, NOTESTYPE type);
		SlideNotes* CreateSlideNotes(picojson::value notesVal, NOTESTYPE type);
	public:
		~FumenJsonLoader();
		void SetObjList(std::vector<Engine::GameObject*>& objList);
		void SetNotesList(std::vector<Notes*>& notesList);
		void SetNotesEditorMusic(NotesEditorMusic& notesEditorMusic);
		void LoadFumen();
	};
}