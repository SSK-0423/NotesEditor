#pragma once
#include "GameObject.hpp"
#include <vector>
typedef enum BARTYPE {
	BAR,	// 1/1
	BAR4,	// 1/4
	BAR8,	// 1/8
	BAR16,	// 1/16
	BAR32,	// 1/32
	BAR_NUM	// 小節線の種類数
};

// 小節線管理クラス
class BarController{
private:
	//小節線の画像ハンドル 1/1 1/4 1/8 1/16 1/32
	std::vector<int> barHandle;
	//生成した小節線オブジェクト
	std::vector<GameObject*> bars;
	void ChangeBarHandle(int handle);
public:
	BarController();
	~BarController();
	void SetObject(GameObject* bar);
	void SetHandle(int& handle);
	void ChangeHandle();
	void ChangeHandle4();
	void ChangeHandle8();
	void ChangeHandle16();
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
	BARTYPE type;
	Bar(int handle,int i);
	~Bar();
	void Update();
	void Draw();
	void SetHandle(int handle);
};
