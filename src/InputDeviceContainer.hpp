#pragma once
#include "IInputDevice.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "Singleton.hpp"
#include <vector>

/*
	入力デバイスのインスタンスを取得するためのクラス
*/

namespace Engine
{
	namespace Input {

		class InputDeviceContainer : public Singleton<InputDeviceContainer> {
			friend Singleton<InputDeviceContainer>;
		private:
			InputDeviceContainer() {}

		public:
			// キーボードのインスタンス取得
			const Keyboard& GetKeyboard() const
			{
				return Keyboard::Instance();
			}
			// マウスのインスタンス取得
			const Mouse& GetMouse() const
			{
				return Mouse::Instance();
			}
		};
	}
}

	/*
		実装時メモ
		新しいデバイスが追加された場合、ここに新規にGet*メソッドを追記する必要がある。
		既存のコードには変更は加えなくてよい→オープンクローズドの原則
		Instance()メソッドの中身はSingletonクラス→滅多に変更はない→詳細に依存しているわけではない
		テンプレート化した場合のメリット
		・新しいInputDeviceを作成するだけで、InputDeviceContainerには変更を加えることなく利用できる
		型チェックをしようにも、Tのインスタンスがないとダメ→Tがシングルトンかどうかを調べるためにインスタンス化しなきゃいけない→循環
	*/