#pragma once
#include "GameObject.hpp"
// 小節線クラス
class Bar : public GameObject {
private:
	//何小節目か
	int barNum;
public:
	// フォント
	static int fontHandle;

	Bar(int handle, int i) noexcept;
	~Bar() noexcept;
	void Update() noexcept;
	void Draw() noexcept;
};