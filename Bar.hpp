#pragma once
#include "GameObject.hpp"
#include <vector>
typedef enum BARTYPE {
	BAR,	// 1/1
	BAR4,	// 1/4
	BAR8,	// 1/8
	BAR16,	// 1/16
	BAR32,	// 1/32
	BAR_NUM	// ���ߐ��̎�ސ�
};

// ���ߐ��Ǘ��N���X
class BarController{
private:
	//���ߐ��̉摜�n���h�� 1/1 1/4 1/8 1/16 1/32
	std::vector<int> barHandle;
	//�����������ߐ��I�u�W�F�N�g
	std::vector<GameObject*> bars;
	void ChangeBarHandle(int handle);
public:
	BarController();
	~BarController();
	void SetObject(GameObject* bar);
	void SetHandle(int& handle);
	void ChangeHandle();
	void ChangeHandle4();
	void ChangeHandle8();
	void ChangeHandle16();
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
	BARTYPE type;
	Bar(int handle,int i);
	~Bar();
	void Update();
	void Draw();
	void SetHandle(int handle);
};
