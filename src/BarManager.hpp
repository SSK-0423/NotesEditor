#pragma once
#include "GameObject.hpp"
//#include "Editor.hpp"
#include <vector>

typedef enum BARTYPE {
	BAR1,				// 1/1
	BAR4,				// 1/4
	BAR8,				// 1/8
	BAR16,				// 1/16
	BAR32,				// 1/32
	BARTYPENUM			// 小節線の種類数
};

// 小節線管理クラス
class BarManager {
private:
	//小節線の画像ハンドル 1/1 1/4 1/8 1/16 1/32
	std::vector<int> barHandle;
	//生成した小節線オブジェクト
	std::vector<GameObject*> bars;
	static BARTYPE type;
	//小節線画像の変更
	void ChangeBarHandle(int handle) noexcept;
	//画像ハンドルのセット
	void SetHandle() noexcept;
	//小節線の当たり判定実行
	void BarsCollision(float& posX, float& posY) noexcept;

public:
	BarManager() noexcept;
	~BarManager() noexcept;

	//Barオブジェクトの生成
	void MakeBar(int num) noexcept;

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
	//ノーツ設置時の座標を決定
	void DecidePutPos(float& posX, float& posY) noexcept;
	static BARTYPE GetBarType() noexcept;

	void Update() noexcept;
	void Draw() noexcept;
	std::vector<GameObject*>* GetListRef() noexcept;
	void DeleteObj() noexcept;
};
