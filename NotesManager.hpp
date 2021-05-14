#pragma once
#include <vector>
#include "Notes.hpp"
#include "BarManager.hpp"
typedef enum NOTESTYPE {
	SHORT_NOTES,		//�V���[�g�m�[�c
	LONG_NOTES,			//�����O�m�[�c
	SLIDE_NOTES,		//�X���C�h�m�[�c
	TYPENUM				//�m�[�c�̎�ސ�
};

//�m�[�c�Ǘ��N���X
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