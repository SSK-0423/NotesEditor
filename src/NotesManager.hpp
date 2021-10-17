#pragma once
#include <vector>
#include "Singleton.hpp"
#include "Notes.hpp"
#include "GameUtility.hpp"
#include "INotesCreator.hpp"

/*
* ノーツ管理クラス
*/

namespace Engine
{
	class GameObject;
}

namespace NotesEditor
{
	class Notes;
	struct NotesData;

	class NotesManager : public Singleton<NotesManager> {
		friend Singleton<NotesManager>;
	private:
		NotesManager();
		static NOTESTYPE type;						//ノーツタイプ
		std::vector<Notes*> notesList;				//ノーツリスト
		Color mousePointerColor;
		bool IsExist(float x, float y);				//ノーツの二重配置検知
		void Cancel(NOTESTYPE type, std::vector<Engine::GameObject*>& objList);

	public:
		~NotesManager();
		void ChangeNotesTypeShort();
		void ChangeNotesTypeLong();
		void ChangeNotesTypeSlide();
		void Update();
		void Draw();
		void CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList);
		void DeleteNotes(float x, float y, std::vector<Engine::GameObject*>& objList);
		void Delete();
		void ChangedSize(float size);
		NOTESTYPE GetPutNotesType();
		std::vector<Notes*>& GetNotesListRef();
	};
}