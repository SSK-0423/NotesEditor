#pragma once
#include "Singleton.hpp"

/*
	���ʃt�@�C����ǂݍ��ރN���X
*/
namespace NotesEditor
{
	class FumenJsonReader : public Singleton<FumenJsonReader>
	{
		friend Singleton<FumenJsonReader>;
	private:
		FumenJsonReader();
	public:
		~FumenJsonReader();
		void LoadFumen();
	};
}