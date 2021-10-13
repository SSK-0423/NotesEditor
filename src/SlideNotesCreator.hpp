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
		// 始点ノーツを置くタイミングかどうか
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