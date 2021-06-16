#pragma once
#include "GameObject.hpp"
#include <vector>
// ���ߐ��N���X
class Bar : public GameObject {
private:
	//�����ߖڂ�
	int barNum;

	static int lane[6];		//���[������p�z��

	//���[������Ɏg���z����쐬
	void InitLaneArray() noexcept;
	//�����ڂ����肷��Vector�z����쐬
	void MakeLineCollisionList(std::vector<int>& list) noexcept;
	//���ۂɉ����ڂ����肷��Vector�z����쐬����֐�
	void MakeList(std::vector<int>& list, int lineNum) noexcept;
public:
	// �t�H���g
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