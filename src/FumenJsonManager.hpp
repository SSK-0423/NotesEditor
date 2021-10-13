#pragma once
#include "Singleton.hpp"

namespace NotesEditor
{
	class FumenJsonManager : public Singleton<FumenJsonManager>
	{
		friend Singleton<FumenJsonManager>;
	private:
		FumenJsonManager();
	public:
		~FumenJsonManager();
		void LoadFumen();
		void SaveFumen();
	};
}