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
	void ChangeBarHandle(int handle);
public:
	BarManager();
	~BarManager();
	//Barオブジェクトのセット
	void SetObject(GameObject* bar);
	//画像ハンドルのセット
	void SetHandle(int& handle);

	//画像変更 1/1
	void ChangeHandle();
	//画像変更 1/4
	void ChangeHandle4();
	//画像変更 1/8
	void ChangeHandle8();
	//画像変更 1/16
	void ChangeHandle16();
	//画像変更 1/32
	void ChangeHandle32();

	void Update();
	void Draw();

	void DeleteObj();
};

// 小節線クラス
class Bar : public GameObject{
private:
	//何小節目か
	int barNum;
public:
	Bar(int handle,int i);
	~Bar();
	void Update();
	void Draw();

	//画像ハンドルのセット
	void SetHandle(int handle);
};
