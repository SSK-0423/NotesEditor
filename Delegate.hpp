#pragma once
template<class ...T>
class DelegateBase;

template<class K, class ...U>
class DelegateBase<K(U...)> {
public:
	DelegateBase() {};
	virtual ~DelegateBase() {};
	// ()���Z�q�̃I�[�o�[���[�h
	// �����z�֐�
	// �߂�lK�^�A�����͕�����
	virtual K operator()(U... u) = 0;
};

// �����w��Ȃ��Ő錾����̂𕉉�
template<class ...T>
class Delegate;
// �߂�l�̌^�ƈ��������R�Ɏw��ł���
// �n���֐��������Ă���N���X�A�֐��̖߂�l�̌^�A������
template<class T,class K, class ...U>
class Delegate<T,K(U...)> : public DelegateBase<K(U...)> {
public:
	Delegate() {};
	virtual ~Delegate() {};

	//�I�y���[�^����
	K operator()(U... u) override{
		return (mObj->*mFunc)(u...); //�o�^���ꂽ�֐����s
	}

	// void(T::* func)�^��EventFunc�^�ɖ��O�ύX
	// typedef�̍l����
	// 1.�ϐ���錾
	//	void (T::* func)();
	// 2.����typedef��t����
	//typedef void (T::* func)();
	// 3. �ϐ�����V�����^���ɂ��� => ����
	typedef K (T::* EventFunc)(U...);

	//�I�u�W�F�N�g�ƃ��\�b�h��o�^
	void set(T* obj, EventFunc func) {
		mObj = obj;
		mFunc = func;
	}
	// �f���Q�[�^�����֐�
	// �f���Q�[�^�̐����Ɗ֐��E�I�u�W�F�N�g��ݒ肵�ADelegateBase�^�Ƃ��ĕԂ�
	static DelegateBase<K(U...)>* createDelegator(T* obj, K (T::*func)(U...)) {
		Delegate<T,K(U...)>* dg = new Delegate<T,K(U...)>;
		dg->set(obj, func);
		return dg;
	}
protected:
	T* mObj;			//�I�u�W�F�N�g
	EventFunc mFunc;	//�֐��|�C���^
};