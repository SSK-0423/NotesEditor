#pragma once
#include "INotesCreator.hpp"
#include "Singleton.hpp"

/*
* ロングノーツ生成クラス
*/

namespace NotesEditor
{
	class ShortNotes;
	class LongNotes;

	class LongNotesCreator : public INotesCreator, public Singleton<LongNotesCreator> {
		friend Singleton<LongNotesCreator>;
	private:
		LongNotesCreator();
		static bool isStart;
		static ShortNotes* startNotes;
		static LongNotes* longNotes;

	public:
		~LongNotesCreator();
		Notes* CreateNotes(const NotesData& notesData);
		Notes* Cancel();
		void Init();
	};
}