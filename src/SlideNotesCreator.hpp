#pragma once
#include "INotesCreator.hpp"
#include "Singleton.hpp"

namespace NotesEditor
{
	class ShortNotes;
	class SlideNotes;

	class SlideNotesCreator : public INotesCreator, public  Singleton<SlideNotesCreator> {
		friend Singleton<SlideNotesCreator>;

	private:
		SlideNotesCreator();
		// �n�_�m�[�c��u���^�C�~���O���ǂ���
		bool isStart;
		std::vector<ShortNotes*> slideNotesList;
		SlideNotes* slideNotes;

	public:
		Notes* CreateNotes(const NotesData& notesData);
		void IsEnd();
		void Init();
		Notes* Cancel();
	};
}