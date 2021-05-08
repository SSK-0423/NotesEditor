#pragma once
#include "GameObject.hpp"
#include <vector>
// 小節線クラス
class Bar : public GameObject {
private:
	//何小節目か
	int barNum;

	static std::vector<int> line1;		// 1/1
	static std::vector<int> line4;		// 1/4
	static std::vector<int> line8;		// 1/8
	static std::vector<int> line16;		// 1/16
	static std::vector<int> line32;		// 1/32

	//何分目かの判定に使うVector配列を作成
	void MakeLineDistanceList() noexcept;

	void MakeList(std::vector<int>& list, int lineNum) noexcept;
public:
	// フォント
	static int fontHandle;


	Bar(int handle, int i) noexcept;
	~Bar() noexcept;
	void Update() noexcept;
	void Draw() noexcept;
	void Collision() noexcept;
	void CollisionLine(int& x, int& y) noexcept;
	void CollisionLane(int& x, int& y) noexcept;
	void DebugDraw() noexcept;
};