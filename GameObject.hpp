#pragma once
#include "Task.hpp"
#include "Vector2D.hpp"

class GameObject : public Task{
protected:

	// �摜�n���h��
	int imageHandle;

	// �I�u�W�F�N�g�̍����A��
	int width;
	int height;

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
	// ���̎擾
	int GetObjWidth() noexcept;
	// �����̎擾
	int GetObjHeight() noexcept;

	virtual void Update() noexcept;
	virtual void Draw() noexcept;
};