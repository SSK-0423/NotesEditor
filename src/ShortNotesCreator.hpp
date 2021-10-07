#pragma once
#include "NotesCreator.hpp"

namespace Engine
{
	class GameObject;
}

namespace NotesEditor
{
	class ShortNotesCreator : public NotesCreator {
	public:
		Notes* CreateNotes(float& x, float& y) noexcept;
		void CreateNotes(float& x, float& y, std::vector<Engine::GameObject*>& objList) noexcept;
	};
}