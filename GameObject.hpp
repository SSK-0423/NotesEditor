#pragma once
#include "Task.hpp"
#include "Vector2D.hpp"

class GameObject : public Task{
protected:

	// �摜�n���h��
	int imageHandle;

public:
	GameObject() noexcept;
	~GameObject() noexcept;

	// �I�u�W�F�N�g�̍��W
	Vector2D position;
	// �I�u�W�F�N�g�̏����ʒu(�����蔻��Ɏg�p)
	Vector2D collisionPos;

	// �摜�̐ݒ�
	void SetHandle(int handle) noexcept;
	// �ʒu�̐ݒ�E�X�V
	void SetPosition(float x, float y) noexcept;

	// �I�u�W�F�N�g�̍����A��
	int width;
	int height;
	
	virtual void Update() noexcept;
	virtual void Draw() noexcept;
};