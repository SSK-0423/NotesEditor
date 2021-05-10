#pragma once
#include <vector>
#include "GameObject.hpp"
#include "Notes.hpp"

typedef enum NOTESTYPE {
	SHORT_NOTES,		//ショートノーツ
	LONG_NOTES,			//ロングノーツ
	SLIDE_NOTES,		//スライドノーツ
	TYPENUM				//ノーツの種類数
};

//ノーツ管理クラス
class NotesManager {
private:
	static NOTESTYPE type;

	std::vector<Notes*> notesList;
public:
	void ChangeNotesTypeShort() noexcept;
	void ChangeNotesTypeLong() noexcept;
	void ChangeNotesTypeSlide() noexcept;
	void PutNotes(std::vector<GameObject*> objList) noexcept;
	void CreateNotes(std::vector<GameObject*> objList) noexcept;
};