#pragma once
#include "GameObject.hpp"
#include <vector>
// 小節線クラス
class Bar : public GameObject {
private:
	//何小節目か
	int barNum;

	static int lane[6];		//レーン判定用配列

	//レーン判定に使う配列を作成
	void InitLaneArray() noexcept;
	//何分目か判定するVector配列を作成
	void MakeLineCollisionList(std::vector<int>& list) noexcept;
	//実際に何分目か判定するVector配列を作成する関数
	void MakeList(std::vector<int>& list, int lineNum) noexcept;
public:
	// フォント
	static int fontHandle;

	Bar(int handle, int i) noexcept;
	~Bar() noexcept;
	void Update() noexcept;
	void Draw() noexcept;
	void Collision(float& posX, float& posY) noexcept;
	bool CollisionBar(int& x, int& y) noexcept;
	float CollisionLane(int& x) noexcept;
	float CollisionLine(int& y) noexcept;
	void DebugDraw() noexcept;
};