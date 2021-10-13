#pragma once
#include "Singleton.hpp"
#include <vector>

namespace NotesEditor
{
	class Notes;

	class FumenJsonGenerator : public Singleton<FumenJsonGenerator>
	{
		friend Singleton<FumenJsonGenerator>;
	private:
		FumenJsonGenerator();
		void QuickSort(std::vector<Notes*>& notesList, int left, int right);
	public:
		~FumenJsonGenerator();
		void SaveFumen(std::vector<Notes*> notesLIst);
	};
}