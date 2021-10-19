# NotesEditor α版ver1.0.0
自作音楽ゲーム用のノーツエディタ
![ノーツエディターサンプル画像](https://user-images.githubusercontent.com/83057130/137940970-50f5d995-4bbe-4da6-a6aa-f0db82057254.PNG)
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
#### 画面構成
![画面構成](https://user-images.githubusercontent.com/83057130/137941139-2955bd59-ce60-4e78-8b2e-d8ae2547e874.png)
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
#### ノーツの設置方法
- ショートノーツ：「SHORT」ボタンをクリックし，譜面を置きたい場所でクリック
- ロングノーツ：「LONG」ボタンをクリックし，始点ノーツと終点ノーツを置く
- スライドノーツ：「SLIDE」ボタンをクリックし，4つ以上のノーツを置いてEnterキーを押す
スライドノーツの形が未確定のときはピンク色，確定時は黄色になります．
スライドノーツ設置時に限り，レーン数が11となり水色の縦線と交差している部分にもノーツが置けるようになります
### 実行環境
Windows10 DirectX9以上
### 実行手順
NotesEditor.exeを起動
