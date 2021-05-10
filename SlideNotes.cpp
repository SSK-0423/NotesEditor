#include "SlideNotes.hpp"

SlideNotes::SlideNotes() noexcept {

}

SlideNotes::~SlideNotes() noexcept {
	for (auto obj : notes) {
		delete[] obj;
	}
	notes.clear();
}

void SlideNotes::Draw() noexcept {
	
}