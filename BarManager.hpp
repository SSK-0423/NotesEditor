#pragma once
#include "GameObject.hpp"
#include <vector>
//typedef enum BARTYPE {
//	BAR,	// 1/1
//	BAR4,	// 1/4
//	BAR8,	// 1/8
//	BAR16,	// 1/16
//	BAR32,	// 1/32
//	BAR_NUM	// 小節線の種類数
//};

// 小節線管理クラス
class BarManager{
private:
	//小節線の画像ハンドル 1/1 1/4 1/8 1/16 1/32
	std::vector<int> barHandle;
	//生成した小節線オブジェクト
	std::vector<GameObject*> bars;
	//小節線画像の変更
	void ChangeBarHandle(int handle) noexcept;
public:
	BarManager() noexcept;
	~BarManager() noexcept;
	//Barオブジェクトのセット
	void SetObject(GameObject& bar) noexcept;
	//画像ハンドルのセット
	void SetHandle(int& handle) noexcept;

	//画像変更 1/1
	void ChangeHandle() noexcept;
	//画像変更 1/4
	void ChangeHandle4() noexcept;
	//画像変更 1/8
	void ChangeHandle8() noexcept;
	//画像変更 1/16
	void ChangeHandle16() noexcept;
	//画像変更 1/32
	void ChangeHandle32() noexcept;

	void Update() noexcept;
	void Draw() noexcept;

	void DeleteObj() noexcept;
};

// 小節線クラス
class Bar : public GameObject{
private:
	//何小節目か
	int barNum;
public:
	Bar(int handle,int i) noexcept;
	~Bar() noexcept;
	void Update() noexcept;
	void Draw() noexcept;
};
