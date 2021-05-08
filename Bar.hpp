#pragma once
#include "GameObject.hpp"
#include <vector>
// ���ߐ��N���X
class Bar : public GameObject {
private:
	//�����ߖڂ�
	int barNum;

	static std::vector<int> line1;		// 1/1
	static std::vector<int> line4;		// 1/4
	static std::vector<int> line8;		// 1/8
	static std::vector<int> line16;		// 1/16
	static std::vector<int> line32;		// 1/32

	//�����ڂ��̔���Ɏg��Vector�z����쐬
	void MakeLineDistanceList() noexcept;

	void MakeList(std::vector<int>& list, int lineNum) noexcept;
public:
	// �t�H���g
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