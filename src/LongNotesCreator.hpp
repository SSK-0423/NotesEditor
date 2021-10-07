#pragma once
#include "NotesCreator.hpp"
#include "BarManager.hpp"
#include "ShortNotes.hpp"
#include "LongNotes.hpp"

namespace Engine
{
	class GameObject;
}

namespace NotesEditor
{
	class LongNotesCreator : public NotesCreator {
	private:
		static bool isStart;
		ShortNotes* startNotes;
		ShortNotes* endNotes;

	public:
		LongNotesCreator() noexcept;
		Notes* CreateNotes(float& x, float& y) noexcept;
		void CreateNotes(float& x, float& y, std::vector<Engine::GameObject*>& objList) noexcept;
		void Cancel(std::vector<Engine::GameObject*>& objList) noexcept;
		void DeleteNotes(Engine::GameObject& notes) noexcept;

	};
}