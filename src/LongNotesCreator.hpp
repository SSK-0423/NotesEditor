#pragma once
#include "NotesCreator.hpp"
#include "BarManager.hpp"
#include "ShortNotes.hpp"
#include "LongNotes.hpp"

class LongNotesCreator : public NotesCreator {
private:
	static bool isStart;
	ShortNotes* startNotes;
	ShortNotes* endNotes;

public:
	LongNotesCreator() noexcept;
	Notes* CreateNotes(float& x, float& y) noexcept;
	void CreateNotes(float& x, float& y, std::vector<GameObject*>& objList) noexcept;
	void Cancel(std::vector<GameObject*>& objList) noexcept;
};