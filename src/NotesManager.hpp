#pragma once
#include <vector>
//#include "Notes.hpp"
#include "BarManager.hpp"
#include "NotesCreator.hpp"
//#include "ShortNotesCreator.hpp"
//#include "LongNotesCreator.hpp"
//#include "SlideNotesCreator.hpp"

namespace Engine
{
	class GameObject;
}

namespace NotesEditor
{
	typedef enum NOTESTYPE {
		SHORT_NOTES,		//ショートノーツ
		LONG_NOTES,			//ロングノーツ
		SLIDE_NOTES,		//スライドノーツ
		TYPENUM				//ノーツの種類数
	};

	//ノーツ管理クラス
	class NotesManager {
	private:
		static NOTESTYPE type;						//ノーツタイプ
		std::vector<Engine::GameObject*> notesList;				//ノーツリスト
		unsigned int color;
		//ShortNotesCreator shortNotesCreator;		//ショートノーツ作成クラス
		//LongNotesCreator longNotesCreator;			//ロングノーツ作成クラス
		//SlideNotesCreator slideNotesCreator;		//スライドノーツ作成クラス
		bool IsExist(float& x, float& y) noexcept;	//ノーツの二重配置検知

	public:
		NotesManager() noexcept;
		void ChangeNotesTypeShort() noexcept;
		void ChangeNotesTypeLong() noexcept;
		void ChangeNotesTypeSlide() noexcept;
		void Update() noexcept;
		void Draw() noexcept;
		std::vector<Engine::GameObject*>* GetListRef() noexcept;
		void CreateNotes(float& x, float& y) noexcept;
		void DeleteNotes(float& x, float& y) noexcept;
		void DeleteObj() noexcept;
	};
}