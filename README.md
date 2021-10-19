# NotesEditor α版ver1.0.0
自作音楽ゲーム用のノーツエディタ
![ノーツエディターサンプル画像](https://user-images.githubusercontent.com/83057130/137784052-2b4c224c-50c0-4d72-be73-ffc09a61ec5b.PNG)
### 機能
+ ショート、ロング、スライドノーツ(3次Spline補間)対応
+ 4分,8分,16分,32分対応
+ 4/4拍子のみ対応
+ 譜面(json)のセーブ・ロード
+ 小節の拡大・縮小
### 今後実装を予定している機能や改善点
+ コピー&ペースト
+ Undo&Redo
+ スライドノーツ生成方法の変更
+ 軽量化
+ ショートカットキーの追加
### 使用方法
#### 操作方法
| アクション | 操作 |
| :--- | :--- |
| ボタン選択，ノーツ設置 | 左クリック |
| ノーツ削除 | 右クリック |
| 画面スクロール | マウスホイール |
| 画面スクロール | 上下矢印キー |
| 画面をウィンドウサイズ分スクロール | PgUp/PgDn |
| 画面を連続でウィンドウサイズ分スクロール | PgUp/PgDn長押し| 
| 拡大・縮小| 左Ctrl + マウスホイール |
| 譜面保存 | 左Ctrl + S |
#### 画面構成
#### 
#### 楽曲情報, 譜面ファイル書式
``` json
// 楽曲情報ファイル書式(json)
{
    "name": "楽曲名",
    "bpm": bpm,     
    "beat":beat,    // 拍子
    "path":"sounds/楽曲名.ogg" // NotesEditor.exeからの相対ファイルパス
}
```

``` json
// 譜面ファイル書式(json)
// 注意：picojsonの仕様上項目名でソートされるため，以下の書式と実際に出力される書式は異なる
{
    "name": "楽曲名",
    "bpm": bpm,
    "beat":beat,
    "path":"sounds/楽曲名.ogg",
    "notes":[
        // ショートノーツ
        {
            "type": 0,       // 0:SHORT 1:LONG 2:SLIDE            
            "lane": lane,       // ノーツが所属するレーン(SHORT・LONG：0～5 SLIDE：0～10)
            "timing": timing,   // 判定タイミング
            "barNum": barNum,   // ノーツが所属する小節番号
            "lineNum": lineNum // ノーツが所属する小節の中でのライン番号：0～31
        },
        // ロングノーツ
        {
            "type": 1,                   
            "lane": lane,       
            "timing": timing,   
            "barNum": barNum,   
            "lineNum": lineNum, 
            "notes":[
                // 始点ノーツ
                {
                    "type": 0,                   
                    "lane": lane,       
                    "timing": timing,   
                    "barNum": barNum,   
                    "lineNum": lineNum 
                },
                // 終点ノーツ
                {
                    "type": 0,                   
                    "lane": lane,       
                    "timing": timing,   
                    "barNum": barNum,   
                    "lineNum": lineNum 
                }
            ]
        },
        // スライドノーツ
        {
            "type": 2,                   
            "lane": lane,       
            "timing": timing,   
            "barNum": barNum,   
            "lineNum": lineNum, 
            "notes":[
                // スライドノーツを構成する全てのノーツ
                {
                    "type": 0,                   
                    "lane": lane,       
                    "timing": timing,   
                    "barNum": barNum,   
                    "lineNum": lineNum
                },
                ...
            ]
        }
    ]
}
```
### 実行環境
Windows10
### 実行手順
NotesEditor.exeを起動
