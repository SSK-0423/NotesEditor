#pragma once
#include "Notes.hpp"
#include "ShortNotes.hpp"
#include "GameUtility.hpp"
#include <vector>

namespace Engine
{
	namespace Components
	{
		class ICollider;
	}
	namespace Collision
	{
		class PointWithPolygon;
	}
}

namespace NotesEditor
{
	enum class LONGNOTES 
	{
		STARTNOTES,
		ENDNOTES
	};
	class LongNotes : public Notes {
	private:
		// 始点と終点
		std::vector<ShortNotes*> notesList;

		void UpdateNotes();
		void UpdateNotesScreenPos();
		void DrawNotes();
		void DrawMiddleLine();
		void Init();
	public:
		LongNotes(ShortNotes& start);
		~LongNotes();
		NOTESTYPE GetNotesType();
		bool Collision(float x, float y) override;
		void Update() override;
		void Draw() override;
		void AddEndNotes(ShortNotes& end);
		std::vector<ShortNotes*> GetChildNotesList();
	};
}