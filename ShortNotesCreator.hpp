#pragma once
#include "NotesCreator.hpp"
class ShortNotesCreator : public NotesCreator {
public:
	Notes* CreateNotes(float& x, float& y) noexcept;
	//void CreateNotes(float& x, float& y) noexcept;
};