#pragma once
template<class ...T>
class DelegateBase;

template<class K, class ...U>
class DelegateBase<K(U...)> {
public:
	DelegateBase() {};
	virtual ~DelegateBase() {};
	// 戻り値K型、引数は複数個
	virtual K operator()(U... u) = 0;
};

template<class ...T>
class Delegate;
// 戻り値の型と引数を自由に指定できる
// 渡す関数を持っているクラス、関数の戻り値の型、引数列
template<class T, class K, class ...U>
class Delegate<T, K(U...)> : public DelegateBase<K(U...)> {
public:
	Delegate() : obj(nullptr), func(nullptr) {};
	virtual ~Delegate() {};

	//オペレータ実装
	K operator()(U... u) override {
		return (obj->*func)(u...); //登録された関数実行
	}

	// void(T::* func)型をEventFunc型に名前変更
	typedef K(T::* EventFunc)(U...);

	//オブジェクトとメソッドを登録
	void set(T* obj, EventFunc func) {
		this->obj = obj;
		this->func = func;
	}
	// デリゲータ生成関数
	// デリゲータの生成と関数・オブジェクトを設定し、DelegateBase型として返す
	static DelegateBase<K(U...)>* CreateDelegator(T* obj, K(T::* func)(U...)) {
		Delegate<T, K(U...)>* dg = new Delegate<T, K(U...)>;
		dg->set(obj, func);
		return dg;
	}
protected:
	T* obj;				//オブジェクト
	EventFunc func;	//関数ポインタ
};