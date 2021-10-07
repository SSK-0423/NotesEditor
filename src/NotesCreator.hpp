#pragma once
#include "Notes.hpp"
#include <vector>
namespace NotesEditor
{
	class NotesCreator {
	public:
		virtual Notes* CreateNotes(float& x, float& y) noexcept = 0;
		virtual void CreateNotes(float& x, float& y, std::vector<Engine::GameObject*>& objList) noexcept = 0;
	};
}