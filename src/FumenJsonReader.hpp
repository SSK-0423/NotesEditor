#pragma once
#include "Singleton.hpp"

/*
	譜面ファイルを読み込むクラス
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