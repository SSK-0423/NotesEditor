#include "ShortNotesCreator.hpp"
#include "ShortNotes.hpp"

Notes* ShortNotesCreator::CreateNotes(float&x, float& y) noexcept {
	Notes* notes = new ShortNotes(x,y);
	return notes;
}

