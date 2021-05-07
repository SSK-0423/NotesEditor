#pragma once
#include "Task.hpp"
#include "GameObject.hpp"
#include "PlayableObj.hpp"
#include <vector>
#include "Music.hpp"

class Camera2D : public GameObject, PlayableObj {
private:
	// �`��ΏۃI�u�W�F�N�g�̃|�C���^
	std::vector<GameObject*> objList;
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
	Camera2D() noexcept;
	~Camera2D() noexcept;

	//�X�V
	void Update() noexcept;
	//�`��
	void Draw() noexcept;
	//�`��ΏۃI�u�W�F�N�g�ɒǉ�
	void SetObject(GameObject& obj) noexcept;
	// �J�������I�u�W�F�N�g���X�g�̍X�V
	void UpdateDrawList() noexcept;
	// �`��ΏۃI�u�W�F�N�g�̃������J��
	void DeleteObj() noexcept;

	//�ړ����E
	void SetMinPosition(float x, float y) noexcept;
	void SetMaxPosition(float x, float y) noexcept;

	//�I�u�W�F�N�g���J�������ɓ��������ǂ����𔻒�
	bool Collision(GameObject& obj) const noexcept;
};