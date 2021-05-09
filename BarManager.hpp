#pragma once
#include "GameObject.hpp"
//#include "Editor.hpp"
#include <vector>

typedef enum BARTYPE {
	BAR1,				// 1/1
	BAR4,				// 1/4
	BAR8,				// 1/8
	BAR16,				// 1/16
	BAR32,				// 1/32
	BARTYPENUM			// ���ߐ��̎�ސ�
};

// ���ߐ��Ǘ��N���X
class BarManager {
private:
	//���ߐ��̉摜�n���h�� 1/1 1/4 1/8 1/16 1/32
	std::vector<int> barHandle;
	//�����������ߐ��I�u�W�F�N�g
	std::vector<GameObject*> bars;
	static BARTYPE TYPE;
	//���ߐ��摜�̕ύX
	void ChangeBarHandle(int handle) noexcept;
	//�摜�n���h���̃Z�b�g
	void SetHandle() noexcept;
	//�L�[���͊Ǘ�
	void KeyInput() noexcept;

public:
	BarManager() noexcept;
	~BarManager() noexcept;

	//Bar�I�u�W�F�N�g�̐���
	void MakeBar(std::vector<GameObject*>& vec, int num) noexcept;

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
	//���ߐ��̓����蔻����s
	void BarsCollision() noexcept;

	static BARTYPE GetBarType() noexcept;

	void Update() noexcept;
	void Draw() noexcept;

	void DeleteObj() noexcept;
};
