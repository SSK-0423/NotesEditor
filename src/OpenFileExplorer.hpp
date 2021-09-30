#pragma once
#include "DxLib.h"
#include "picojson.h"
#include "Singleton.hpp"

class OpenFileExplorer {
private:
	char fullPath[MAX_PATH], fileName[MAX_PATH];
	OPENFILENAME ofn;

public:
	OpenFileExplorer();
	
	//音楽ファイルを開いてハンドルを返す
	int OpenAudioFile() noexcept;
	
	//画像ファイルを開いてハンドルを返す
	int OpenImageFile() noexcept;

	//Jsonファイルを開く
	int OpenJsonFile(picojson::value& v) noexcept;
};