#pragma once
#include "Notes.hpp"
#include "ShortNotes.hpp"
#include "GameSymbol.hpp"
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
		// �m�[�c�̐F
		static Color color;
		// �n�_�ƏI�_
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