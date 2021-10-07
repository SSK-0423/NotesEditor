#pragma once
#include "NotesCreator.hpp"
#include "ShortNotes.hpp"

namespace Engine
{
	class GameObject;
}

namespace NotesEditor
{
	class SlideNotesCreator : public NotesCreator {
	private:
		bool isEnd;
		std::vector<ShortNotes*> slideNotesList;
	public:
		SlideNotesCreator() noexcept;
		Notes* CreateNotes(float& x, float& y) noexcept;
		void CreateNotes(std::vector<Engine::GameObject*>& objList) noexcept;
		void CreateNotes(float& x, float& y, std::vector<Engine::GameObject*>& objList) noexcept;
		void IsEnd() noexcept;
		void Cancel(std::vector<Engine::GameObject*>& objList) noexcept;
		void DeleteNotes(Engine::GameObject& notes) noexcept;
		void Draw();
	};
}