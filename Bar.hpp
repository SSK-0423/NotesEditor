#pragma once
#include "GameObject.hpp"
// ���ߐ��N���X
class Bar : public GameObject {
private:
	//�����ߖڂ�
	int barNum;
public:
	// �t�H���g
	static int fontHandle;

	Bar(int handle, int i) noexcept;
	~Bar() noexcept;
	void Update() noexcept;
	void Draw() noexcept;
};