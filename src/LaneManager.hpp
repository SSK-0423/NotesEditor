#pragma once
#include <vector>
#include "Singleton.hpp"

/*
* ���[���Ǘ��N���X
*/

namespace NotesEditor
{
	class Lane;

	class LaneManager : public Singleton<LaneManager> {
		friend Singleton<LaneManager>;
	private:
		LaneManager();
		static const int LANENUM = 6;
		static const int SLIDELANENUM = 11;
		float lanePosX[LANENUM];
		float slideLanePosX[SLIDELANENUM];
		std::vector<Lane*> laneList;

		float DecideLane(float x, float laneList[], int size);
		float DecidePosX(float x, float laneList[], int size);
	public:
		~LaneManager();
		void Draw();
		float DecidePutPosX(float x);
		int GetLane(float x);
		float GetLanePosX(int lane);
		float GetSlideLanePosX(int lane);
		void Delete();
	};
}