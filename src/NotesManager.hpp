#pragma once
#include <vector>
#include "Singleton.hpp"
#include "Notes.hpp"
#include "GameSymbol.hpp"
#include "INotesCreator.hpp"
#include "ShortNotesCreator.hpp"
#include "LongNotesCreator.hpp"
#include "SlideNotesCreator.hpp"

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
		Color color;
		ShortNotesCreator shortNotesCreator;
		LongNotesCreator longNotesCreator;
		SlideNotesCreator slideNotesCreator;
		bool IsExist(float x, float y);				//ノーツの二重配置検知

	public:
		void ChangeNotesTypeShort();
		void ChangeNotesTypeLong();
		void ChangeNotesTypeSlide();
		void Update();
		void Draw();
		void CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList);
		void DeleteNotes(float x, float y);
		void DeleteObj();
	};
}