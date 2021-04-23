#pragma once
#include "Task.hpp"
#include "GameObject.hpp"
#include <vector>
#include "Music.hpp"

class Camera2D : public GameObject{
private:
	// �`��ΏۃI�u�W�F�N�g�̃|�C���^
	std::vector<GameObject*> objList;
	// �J�������̕`��\�I�u�W�F�N�g�̃|�C���^
	std::vector<GameObject*> drawList;
	// �����蔻��A�ړ��p�|�W�V����
	Vector2D collisionPos;

public:
	Camera2D();
	~Camera2D();
	Vector2D minPos;
	Vector2D maxPos;
	//�`��ΏۃI�u�W�F�N�g�ɒǉ�
	void SetObject(GameObject* obj);
	// �J�������I�u�W�F�N�g���X�g�̍X�V
	void UpdateDrawList();
	// �`��ΏۃI�u�W�F�N�g�̃������J��
	void DeleteObj();

	void Update();
	void Draw();

	void SetPosition(float x, float y);
	void SetMinPosition(float x, float y);
	void SetMaxPosition(float x, float y);
	bool Collision(const GameObject& obj) const;
};