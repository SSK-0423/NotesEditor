#pragma once
#include "NotesCreator.hpp"
#include "BarManager.hpp"
class LongNotesCreator : public NotesCreator {
private:
	BarManager* barManager;
public:
	LongNotesCreator(BarManager& barManager) noexcept;
	Notes* CreateNotes(float& x, float& y) noexcept;
};