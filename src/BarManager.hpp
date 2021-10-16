#pragma once
#include "GameObject.hpp"
#include "GameUtility.hpp"
#include "Singleton.hpp"
#include <vector>

namespace NotesEditor
{
	class Bar;

	class BarManager : public Singleton<BarManager> {
		friend Singleton<BarManager>;
	private:
		BarManager();
		std::vector<Bar*> barList;
		int lineNum;
		static const int FONTSIZE;
		static const int FONTTHICK;

	public:
		// 1è¨êﬂìñÇΩÇËÇÃç≈ëÂâπïÑêî
		static const int MAXNOTENUM = 32;

		void CreateBar(std::vector<Engine::GameObject*>& objList, int barNum, int lineNum);
		void ChangeBarType();
		void ChangeBarType4();
		void ChangeBarType8();
		void ChangeBarType16();
		void ChangeBarType32();
		float Collision(float x, float y);
		float CalcTiming(float y);
		unsigned int GetBarNum();
		int GetLineNum();
		void Delete();
	};
}
