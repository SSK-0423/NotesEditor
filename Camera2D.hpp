#pragma once
#include "Task.hpp"
#include "GameObject.hpp"
#include "PlayableObj.hpp"
#include <vector>
#include "Music.hpp"

class Camera2D : public GameObject, PlayableObj {
private:
	// �`��ΏۃI�u�W�F�N�g�̃|�C���^
	std::vector<std::vector<GameObject*>*>* objList; // objList[0] = objList objList->size() = 2 objList[0].size() = 2
	// �J�������̕`��\�I�u�W�F�N�g�̃|�C���^
	std::vector<GameObject*> drawList;

	//�J�������I�u�W�F�N�g�̍X�V����
	void InCameraObjUpdate() noexcept;
	//�J�������I�u�W�F�N�g�̕`��
	void InCameraObjDraw() noexcept;
	//�f�o�b�O�p�`��֐�
	void DebugDraw() noexcept;
	//�L�[�{�[�h�A�}�E�X����
	void Controll() noexcept override;
	//�ړ����E
	void PosLimit() noexcept override;

public:
	Camera2D(std::vector<std::vector<GameObject*>*>& vec) noexcept;
	~Camera2D() noexcept;

	//�X�V
	void Update() noexcept;
	//�`��
	void Draw() noexcept;
	// �J�������I�u�W�F�N�g���X�g�̍X�V
	void UpdateDrawList() noexcept;
	// �`��ΏۃI�u�W�F�N�g�̃������J��
	void DeleteObj() noexcept;

	//�ړ����E
	void SetMinposition(float x, float y) noexcept;
	void SetMaxposition(float x, float y) noexcept;

	//�I�u�W�F�N�g���J�������ɓ��������ǂ����𔻒�
	bool Collision(GameObject& obj) const noexcept;
};