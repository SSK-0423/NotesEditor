#pragma once
#include "GameObject.hpp"
#include <vector>
//typedef enum BARTYPE {
//	BAR,	// 1/1
//	BAR4,	// 1/4
//	BAR8,	// 1/8
//	BAR16,	// 1/16
//	BAR32,	// 1/32
//	BAR_NUM	// ���ߐ��̎�ސ�
//};

// ���ߐ��Ǘ��N���X
class BarManager{
private:
	//���ߐ��̉摜�n���h�� 1/1 1/4 1/8 1/16 1/32
	std::vector<int> barHandle;
	//�����������ߐ��I�u�W�F�N�g
	std::vector<GameObject*> bars;
	//���ߐ��摜�̕ύX
	void ChangeBarHandle(int handle) noexcept;
public:
	BarManager() noexcept;
	~BarManager() noexcept;
	//Bar�I�u�W�F�N�g�̃Z�b�g
	void SetObject(GameObject& bar) noexcept;
	//�摜�n���h���̃Z�b�g
	void SetHandle(int& handle) noexcept;

	//�摜�ύX 1/1
	void ChangeHandle() noexcept;
	//�摜�ύX 1/4
	void ChangeHandle4() noexcept;
	//�摜�ύX 1/8
	void ChangeHandle8() noexcept;
	//�摜�ύX 1/16
	void ChangeHandle16() noexcept;
	//�摜�ύX 1/32
	void ChangeHandle32() noexcept;

	void Update() noexcept;
	void Draw() noexcept;

	void DeleteObj() noexcept;
};

// ���ߐ��N���X
class Bar : public GameObject{
private:
	//�����ߖڂ�
	int barNum;
public:
	Bar(int handle,int i) noexcept;
	~Bar() noexcept;
	void Update() noexcept;
	void Draw() noexcept;
};
