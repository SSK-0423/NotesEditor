#include "LongNotesCreator.hpp"
#include "LongNotes.hpp"

Notes* LongNotesCreator::CreateNotes(float& x, float& y) noexcept {
	Notes* notes = new LongNotes(x, y);
	return notes;
}