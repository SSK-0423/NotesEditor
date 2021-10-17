#include "OpenFileExplorer.hpp"
#include "DxLib.h"
#include <string.h>
#include <fstream>
#include <cstring>
#include <Windows.h>
//OPENFILENAME構造体の初期化
OpenFileExplorer::OpenFileExplorer(){

	memset(&ofn, 0, sizeof(OPENFILENAME));
	memset(fullPath, 0, sizeof(fullPath));
	memset(fileName, 0, sizeof(fileName));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetMainWindowHandle();//メインウィンドウのハンドルを取得

	//ファイル名のフィルタ設定
	ofn.lpstrFilter = "全てのファイル(*.*)\0*.*\0";
	ofn.lpstrFile = fullPath;
	//ファイルのフルパスを保存するバッファサイズ指定
	ofn.nMaxFile = sizeof(fullPath);

	ofn.lpstrFileTitle = fileName;
	ofn.nMaxFileTitle = sizeof(fileName);

	// ダイアログボックスの動作を指定
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	// ユーザーが拡張子を入力しなかった場合のデフォルト拡張子
	ofn.lpstrDefExt = "";
	
	ofn.lpstrInitialDir = "C:\\DxLib\\MyProjects\\NotesEditor";

	// ダイアログボックスのタイトル
	ofn.lpstrTitle = "ファイルの読み込み";
}

int OpenFileExplorer::OpenAudioFile() {
	ofn.lpstrTitle = "音楽ファイルの読み込み";
	ofn.lpstrFilter = "WAVファイル(*.wav)\0*.wav\0MP3ファイル(*.mp3)\0*.mp3\0\0";
	if (GetOpenFileName(&ofn) != 0) {
		return LoadSoundMem(fullPath);
	}
	return -1;
}

int OpenFileExplorer::OpenImageFile() {
	ofn.lpstrTitle = "画像ファイルの読み込み";
	ofn.lpstrFilter = "PNGファイル(*.png)\0*.png\0JPEGファイル(*.jpg)\0*.jpg\0\0";
	if (GetOpenFileName(&ofn) != 0) {
		return LoadGraph(fullPath);
	}
	return -1;
}

int OpenFileExplorer::OpenJsonFile(picojson::value& v) {
	ofn.lpstrTitle = "Jsonファイルの読み込み";
	ofn.lpstrFilter = "Jsonファイル(*.json)\0*.json\0\0";
	if (GetOpenFileName(&ofn) != 0) {
		std::ifstream ifs;
		ifs.open(fullPath);
		ifs >> v;
		ifs.close();
		//カレントディレクトリを戻す
		SetCurrentDirectory("..");
		return 0;
	}
	return -1;
}