#pragma once
#include "Notes.hpp"
class NotesCreator {
public:
	virtual Notes* CreateNotes(float& x, float& y) noexcept = 0;
	//virtual void CreateNotes(float& x, float& y) noexcept = 0;
};