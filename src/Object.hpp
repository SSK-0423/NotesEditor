//#pragma once
//#include "Component.hpp"
//#include <vector>
//#include <iostream>
//
//class Object {
//protected:
//	std::vector<Component*> componentList;	//コンポーネントリスト
//
//public:
//	//コンポーネント取得
//	template <class T>
//	T* GetComponent() {
//		for (auto comp : componentList) {
//			// dynamic_castは避けるべき
//			T* castComp = dynamic_cast<T*>(comp);
//			if (castComp != nullptr) {
//				return castComp;
//			}
//		}
//		return nullptr;
//	}
//
//	//コンポーネント追加
//	template <class T>
//	void AddComponent() {
//		//コンポーネントが既に存在するかチェック
//		for (auto comp : componentList) {
//			// #ダウンキャストは危険(?)
//			T* castComp = dynamic_cast<T*>(comp);
//			if (castComp != nullptr) {
//				return;
//			}
//		}
//		componentList.push_back(new T());
//	}
//
//	virtual void Update() = 0;
//
//	virtual void Draw() = 0;
//};