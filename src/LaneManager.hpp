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
		float lanePosX[6];
		std::vector<Lane*> laneList;
	public:
		~LaneManager();
		void Update();
		void Draw();
		void Collision(float x, float y);
	};
}