#pragma once
#include "NotesCreator.hpp"

class LongNotesCreator : public NotesCreator {
public:
	Notes CreateNotes(float& x, float& y) noexcept;
};