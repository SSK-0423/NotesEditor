#pragma once
#include "NotesCreator.hpp"
#include "ShortNotes.hpp"


class SlideNotesCreator : public NotesCreator {
private:
	bool isEnd;
	std::vector<ShortNotes*> slideNotesList;
public:
	SlideNotesCreator() noexcept;
	Notes* CreateNotes(float& x, float& y) noexcept;
	void CreateNotes(std::vector<GameObject*>& objList) noexcept;
	void CreateNotes(float& x, float& y, std::vector<GameObject*>& objList) noexcept;
	void IsEnd() noexcept;
	void Cancel(std::vector<GameObject*>& objList) noexcept;
	void DeleteNotes(GameObject& notes) noexcept;
	void Draw();
};