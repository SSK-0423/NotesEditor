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
	class LongNotes : public Notes {
	private:
		// �m�[�c�̐F
		static Color color;
		// �n�_�m�[�c
		ShortNotes* startNotes;
		// �I�_�m�[�c
		ShortNotes* endNotes;

		void DrawMiddleLine();
	public:
		LongNotes(ShortNotes& start, ShortNotes& end);
		~LongNotes();
		NOTESTYPE GetNotesType();
		bool Collision(float x, float y) override;
		void Update() override;
		void Draw() override;
	};
}