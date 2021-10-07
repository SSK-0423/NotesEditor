#pragma once
#include "GameObject.hpp"
#include "GameSymbol.hpp"
#include "Singleton.hpp"
#include <vector>

namespace NotesEditor
{
	class Bar;

	class BarManager : public Singleton<BarManager> {
		friend Singleton<BarManager>;
	private:
		BarManager();
		// 生成した小節線オブジェクト
		std::vector<Bar*> barList;

	public:
		void CreateBar(std::vector<Engine::GameObject*>& objList, int barNum);
		//小節タイプ変更 1/1
		void ChangeBarType();
		//小節タイプ変更1/4
		void ChangeBarType4();
		//小節タイプ変更 1/8
		void ChangeBarType8();
		//小節タイプ変更 1/16
		void ChangeBarType16();
		//小節タイプ変更 1/32
		void ChangeBarType32();

		void ChangeSize();
		bool Collision(float x, float y);
	};
}
