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
	void ChangeBarHandle(int handle);
public:
	BarManager();
	~BarManager();
	//Bar�I�u�W�F�N�g�̃Z�b�g
	void SetObject(GameObject* bar);
	//�摜�n���h���̃Z�b�g
	void SetHandle(int& handle);

	//�摜�ύX 1/1
	void ChangeHandle();
	//�摜�ύX 1/4
	void ChangeHandle4();
	//�摜�ύX 1/8
	void ChangeHandle8();
	//�摜�ύX 1/16
	void ChangeHandle16();
	//�摜�ύX 1/32
	void ChangeHandle32();

	void Update();
	void Draw();

	void DeleteObj();
};

// ���ߐ��N���X
class Bar : public GameObject{
private:
	//�����ߖڂ�
	int barNum;
public:
	Bar(int handle,int i);
	~Bar();
	void Update();
	void Draw();

	//�摜�n���h���̃Z�b�g
	void SetHandle(int handle);
};
