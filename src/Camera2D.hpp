#pragma once
#include "GameObject.hpp"
#include "IPlayable.hpp"
#include "Music.hpp"
#include "Game.hpp"
#include "KeyInput.hpp"
#include <vector>

class Camera2D : public GameObject, IPlayable{
private:
	// �`��ΏۃI�u�W�F�N�g�̃|�C���^
	std::vector<std::vector<GameObject*>*>* objList; // objList[0] = objList objList->size() = 2 objList[0].size() = 2
	// �J�������̕`��\�I�u�W�F�N�g�̃|�C���^
	std::vector<GameObject*> drawList;
	// �J�����̌��_(������W)
	Position2D<float> origin;

	void UpdateOrigin();
	// �J�������I�u�W�F�N�g�̍X�V����
	void UpdateInCameraObj() noexcept;
	// �J�������I�u�W�F�N�g�̕`��
	void DrawInCameraObj() noexcept;
	// �f�o�b�O�p�`��֐�
	void DebugDraw() noexcept;
	// �L�[�{�[�h�A�}�E�X����
	void Controll() noexcept override;
	// �ړ����E
	void LimitPos() noexcept override;
	// �I�u�W�F�N�g���J�������ɓ��������ǂ����𔻒�
	bool Collision(const GameObject& obj) noexcept;
	// �I�u�W�F�N�g�Ԃ̋������v�Z
	Vector2<float> CalcDistance(const Transform& targetTransform);
	// 2�̃I�u�W�F�N�g�̃T�C�Y�̍��v�l���v�Z
	Vector2<float> SumSize(const Transform& targetTransform);

public:
	Camera2D(std::vector<std::vector<GameObject*>*>& vec) noexcept;
	~Camera2D() noexcept;

	// �X�V
	void Update() noexcept;
	// �`��
	void Draw() noexcept;
	// �L�[����
	void Input() noexcept;
	// �J�������I�u�W�F�N�g���X�g�̍X�V
	void UpdateDrawList() noexcept;
	// �`��ΏۃI�u�W�F�N�g�̃������J��
	void DeleteObj() noexcept;
	// �ړ����E���Z�b�g
	void SetMinposition(float x, float y) noexcept;
	void SetMaxposition(float x, float y) noexcept;

};