#pragma once
#include <vector>
#include "Singleton.hpp"
#include "Notes.hpp"
#include "GameUtility.hpp"
#include "INotesCreator.hpp"

namespace Engine
{
	class GameObject;
}

namespace NotesEditor
{
	class Notes;
	struct NotesData;

	//ノーツ管理クラス
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
		void ChangeNotesTypeShort();
		void ChangeNotesTypeLong();
		void ChangeNotesTypeSlide();
		void Update();
		void Draw();
		void CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList);
		void DeleteNotes(float x, float y, std::vector<Engine::GameObject*>& objList);
		void DeleteObj();
		NOTESTYPE GetPutNotesType();
		std::vector<Notes*>& GetNotesListRef();
	};
}