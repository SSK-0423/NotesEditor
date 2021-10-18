#pragma once
template<class ...T>
class DelegateBase;

template<class K, class ...U>
class DelegateBase<K(U...)> {
public:
	DelegateBase() {};
	virtual ~DelegateBase() {};
	// �߂�lK�^�A�����͕�����
	virtual K operator()(U... u) = 0;
};

template<class ...T>
class Delegate;
// �߂�l�̌^�ƈ��������R�Ɏw��ł���
// �n���֐��������Ă���N���X�A�֐��̖߂�l�̌^�A������
template<class T, class K, class ...U>
class Delegate<T, K(U...)> : public DelegateBase<K(U...)> {
public:
	Delegate() : obj(nullptr), func(nullptr) {};
	virtual ~Delegate() {};

	//�I�y���[�^����
	K operator()(U... u) override {
		return (obj->*func)(u...); //�o�^���ꂽ�֐����s
	}

	// void(T::* func)�^��EventFunc�^�ɖ��O�ύX
	typedef K(T::* EventFunc)(U...);

	//�I�u�W�F�N�g�ƃ��\�b�h��o�^
	void set(T* obj, EventFunc func) {
		this->obj = obj;
		this->func = func;
	}
	// �f���Q�[�^�����֐�
	// �f���Q�[�^�̐����Ɗ֐��E�I�u�W�F�N�g��ݒ肵�ADelegateBase�^�Ƃ��ĕԂ�
	static DelegateBase<K(U...)>* CreateDelegator(T* obj, K(T::* func)(U...)) {
		Delegate<T, K(U...)>* dg = new Delegate<T, K(U...)>;
		dg->set(obj, func);
		return dg;
	}
protected:
	T* obj;				//�I�u�W�F�N�g
	EventFunc func;	//�֐��|�C���^
};