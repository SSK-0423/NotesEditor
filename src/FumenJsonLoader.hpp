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
		
		float GetPosX(NOTESTYPE parentType, int lane);
		float CalcPosY(float timing);
		NotesData MakeNotesData(picojson::value notesVal, NOTESTYPE parentType);
		void CreateNotes(picojson::value fumen);
	public:
		~FumenJsonLoader();
		void SetObjList(std::vector<Engine::GameObject*>& objList);
		void SetNotesList(std::vector<Notes*>& notesList);
		void SetNotesEditorMusic(NotesEditorMusic& notesEditorMusic);
		void LoadFumen();
	};
}