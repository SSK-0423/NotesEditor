#pragma once
#include <vector>
#include "Singleton.hpp"
#include "Notes.hpp"
#include "BarManager.hpp"
#include "NotesCreator.hpp"
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



	//ノーツ管理クラス
	class NotesManager : public Singleton<NotesManager> {
		friend Singleton<NotesManager>;
	private:
		NotesManager();
		static NOTESTYPE type;						//ノーツタイプ
		std::vector<Notes*> notesList;				//ノーツリスト
		unsigned int color;
		//ShortNotesCreator shortNotesCreator;		//ショートノーツ作成クラス
		//LongNotesCreator longNotesCreator;		//ロングノーツ作成クラス
		//SlideNotesCreator slideNotesCreator;		//スライドノーツ作成クラス
		bool IsExist(float& x, float& y);	//ノーツの二重配置検知

	public:
		void ChangeNotesTypeShort();
		void ChangeNotesTypeLong();
		void ChangeNotesTypeSlide();
		void Update();
		void Draw();
		std::vector<Engine::GameObject*>* GetListRef();
		void CreateNotes(float& x, float& y);
		void DeleteNotes(float& x, float& y);
		void DeleteObj();
	};
}