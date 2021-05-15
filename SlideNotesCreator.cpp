#include "SlideNotesCreator.hpp"
#include "SlideNotes.hpp"

//void SlideNotesCreator::CreateNotes(float& x, float& y) noexcept {
//	Notes* notes = new SlideNotes(x, y);
//}

Notes* SlideNotesCreator::CreateNotes(float& x, float& y) noexcept {
	Notes* notes = new SlideNotes(x, y);
	return notes;
}