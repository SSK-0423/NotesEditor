#pragma once
#include "GameObject.hpp"
#include "GameUtility.hpp"
#include "Singleton.hpp"
#include <vector>

namespace NotesEditor
{
	class Bar;
	class BarLine;

	class BarManager : public Singleton<BarManager> {
		friend Singleton<BarManager>;
	private:
		BarManager();
		std::vector<Bar*> barList;
		int lineNum;
		static const int FONTSIZE;
		static const int FONTTHICK;

	public:
		// 1小節当たりの最大音符数
		static const int MAXNOTENUM = 32;
		~BarManager();
		void CreateBar(std::vector<Engine::GameObject*>& objList, int barNum, int lineNum);
		void ChangeBarType();
		void ChangeBarType4();
		void ChangeBarType8();
		void ChangeBarType16();
		void ChangeBarType32();
		void ChangedBarsTransformByScale(float scaleHeight);
		float DecidePutPosY(float x, float y);
		float CalcTiming(float y);
		unsigned int GetBarNum();
		int GetLineNum();
		int NotesBarNum(float y);
		int NotesLineNum(float y);
		void Delete();
	};
}
