#pragma once
#include <vector>
#include "Singleton.hpp"
#include "Notes.hpp"
#include "GameUtility.hpp"
#include "INotesCreator.hpp"

/*
* �m�[�c�Ǘ��N���X
*/

namespace Engine
{
	class GameObject;
}

namespace NotesEditor
{
	class Notes;
	struct NotesData;

	class NotesManager : public Singleton<NotesManager> {
		friend Singleton<NotesManager>;
	private:
		NotesManager();
		static NOTESTYPE type;						//�m�[�c�^�C�v
		std::vector<Notes*> notesList;				//�m�[�c���X�g
		Color mousePointerColor;
		bool IsExist(float x, float y);				//�m�[�c�̓�d�z�u���m
		void Cancel(NOTESTYPE type, std::vector<Engine::GameObject*>& objList);

	public:
		~NotesManager();
		void ChangeNotesTypeShort();
		void ChangeNotesTypeLong();
		void ChangeNotesTypeSlide();
		void Update();
		void Draw();
		void CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList);
		void DeleteNotes(float x, float y, std::vector<Engine::GameObject*>& objList);
		void Delete();
		void ChangedSize(float size);
		NOTESTYPE GetPutNotesType();
		std::vector<Notes*>& GetNotesListRef();
	};
}