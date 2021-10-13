#pragma once
#include <vector>
#include "Singleton.hpp"

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
		void Update();
		void Draw();
		float Collision(float x);
		int GetLane(float x);
		void Delete();
	};
}