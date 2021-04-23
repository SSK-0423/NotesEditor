#pragma once
#include "Task.hpp"

// ���W
struct Vector2D {
	float x;
	float y;
};

class GameObject : public Task{
protected:

	// �摜�n���h��
	int imageHandle;

public:
	GameObject();
	~GameObject();

	// �I�u�W�F�N�g�̍��W
	Vector2D position;
	// �I�u�W�F�N�g�̏����ʒu(�����蔻��Ɏg�p)
	Vector2D collisionPos;

	// �摜�̐ݒ�
	virtual void SetHandle(int handle) { imageHandle = handle; }
	// �ʒu�̐ݒ�E�X�V
	virtual void SetPosition(float x, float y) {}

	// �I�u�W�F�N�g�̍����A��
	int width;
	int height;
	
	virtual void Update();
	virtual void Draw();
};