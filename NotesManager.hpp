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
class NotesManager {
private:
	static NOTESTYPE type;						//ノーツタイプ
	std::vector<Notes*> notesList;				//ノーツリスト
	std::vector<GameObject*>* objList;			//カメラ描画対象オブジェクトリスト
	ShortNotesCreator shortNotesCreator;		//ショートノーツ作成クラス
	LongNotesCreator longNotesCreator;			//ロングノーツ作成クラス
	SlideNotesCreator slideNotesCreator;		//スライドノーツ作成クラス
	bool IsExist(float& x, float& y) noexcept;	//ノーツの二重配置検知

public:
	NotesManager() noexcept;
	void ChangeNotesTypeShort() noexcept;
	void ChangeNotesTypeLong() noexcept;
	void ChangeNotesTypeSlide() noexcept;
	void Update() noexcept;
	void Draw() noexcept;
	void SetObjList(std::vector<GameObject*>& objList) noexcept;
	void CreateNotes(float& x, float& y) noexcept;
	void DeleteNotes(float& x, float& y) noexcept;
	void DeleteObj() noexcept;
};