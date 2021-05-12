#pragma once
#include "NotesCreator.hpp"

class SlideNotesCreator : public NotesCreator {
public:
	Notes CreateNotes(float& x, float& y) noexcept;
};