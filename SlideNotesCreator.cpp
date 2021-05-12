#include "SlideNotesCreator.hpp"
#include "SlideNotes.hpp"

Notes* SlideNotesCreator::CreateNotes(float& x, float& y) noexcept {
	Notes* notes = new SlideNotes(x, y);
	return notes;
}