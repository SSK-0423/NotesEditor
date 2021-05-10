#pragma once
#include <vector>
#include "GameObject.hpp"
#include "Notes.hpp"

typedef enum NOTESTYPE {
	SHORT_NOTES,		//�V���[�g�m�[�c
	LONG_NOTES,			//�����O�m�[�c
	SLIDE_NOTES,		//�X���C�h�m�[�c
	TYPENUM				//�m�[�c�̎�ސ�
};

//�m�[�c�Ǘ��N���X
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