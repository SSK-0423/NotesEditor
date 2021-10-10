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
		// ノーツの色
		static Color color;
		// 始点ノーツ
		ShortNotes* startNotes;
		// 終点ノーツ
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