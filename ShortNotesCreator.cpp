#include "ShortNotesCreator.hpp"
#include "ShortNotes.hpp"

Notes* ShortNotesCreator::CreateNotes(float&x, float& y) noexcept {
	Notes* notes = new ShortNotes(x,y);
	return notes;
}

void ShortNotesCreator::CreateNotes(float& x, float& y, std::vector<GameObject*>& objList) noexcept
{
	Notes* notes = new ShortNotes(x, y);
	objList.push_back(notes);
}

