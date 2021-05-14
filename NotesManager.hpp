#pragma once
#include <vector>
#include "Notes.hpp"
#include "BarManager.hpp"
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
	BarManager* barManager;
	std::vector<Notes*> notesList;
public:
	NotesManager() noexcept;
	NotesManager(BarManager& barManager) noexcept;
	void SetBarManager(BarManager& barManager) noexcept;
	void ChangeNotesTypeShort() noexcept;
	void ChangeNotesTypeLong() noexcept;
	void ChangeNotesTypeSlide() noexcept;
	void Update() noexcept;
	Notes* CreateNotes(float& x, float& y) noexcept;
};