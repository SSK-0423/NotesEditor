#pragma once
#include <vector>
#include "Singleton.hpp"

namespace NotesEditor
{
	class Lane;
	class LaneManager : public Singleton<LaneManager>{
		friend Singleton<LaneManager>;
	private:
		LaneManager();
		static const int MAXLANENUM = 6;
		float lanePosX[MAXLANENUM];
		std::vector<Lane*> laneList;
	public:
		~LaneManager();
		void Update();
		void Draw();
		float Collision(float x, float y);
		int GetLane(float x);
		void Delete();
	};
}