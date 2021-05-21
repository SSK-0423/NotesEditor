#pragma once
#include <vector>
#include "Notes.hpp"
#include "BarManager.hpp"
#include "NotesCreator.hpp"
#include "ShortNotesCreator.hpp"
#include "LongNotesCreator.hpp"
#include "SlideNotesCreator.hpp"
typedef enum NOTESTYPE {
	SHORT_NOTES,		//ショートノーツ
	LONG_NOTES,			//ロングノーツ
	SLIDE_NOTES,		//スライドノーツ
	TYPENUM				//ノーツの種類数
};

//ノーツ管理クラス
class NotesManager{
private:
	static NOTESTYPE type;
	std::vector<Notes*> notesList;
	std::vector<GameObject*>* objList;
	ShortNotesCreator shortNotesCreator;
	LongNotesCreator longNotesCreator;
	SlideNotesCreator slideNotesCreator;
	bool IsExist(float& x, float& y) noexcept;

public:
	NotesManager() noexcept;
	void ChangeNotesTypeShort() noexcept;
	void ChangeNotesTypeLong() noexcept;
	void ChangeNotesTypeSlide() noexcept;
	void Update() noexcept;
	void Draw() noexcept;
	void SetObjList(std::vector<GameObject*>& objList) noexcept;
	void CreateNotes(float& x, float& y) noexcept;
	void DeleteObj() noexcept;
};