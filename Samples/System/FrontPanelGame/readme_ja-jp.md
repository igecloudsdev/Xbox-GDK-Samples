  ![](./media/image1.png)

#   FrontPanelGame サンプル

*このサンプルは、Microsoft ゲーム開発キットのプレビュー (2019 年 11 月)
に対応しています。*

# 

# 説明

FrontPanelGame は従来の \"ヘビゲーム\" を Xbox One X Devkit および
Project Scarlett Devkit のフロント
パネルに完全に実装しています。サンプルは主として楽しむために提供されていますが、フロント
パネル コントロールの重要な側面を示しています。

-   フロント パネルは、タイトル コードから完全にプログラミング可能です

-   ボタンと方向パッドの API は、使い慣れた Gamepad API に似ています。

-   このサンプルは、独自のフロント パネル
    プロジェクトで使用できるユーティリティ
    コードをいくつか示しています。

    -   RasterFont を使用したテキスト レンダリング (関連項目:
        FrontPanelText サンプル)

    -   FrontPanelInput による DirectXTK::GamePad
        によく似た再利用可能なインプット クラスの提供

    -   FrontPanelDisplay によるフロント パネル
        バッファを管理するシンプルなクラスの提供

    -   線や四角形などの基本的な図形を描画するためのコード

![](./media/image3.png)

# サンプルのビルド

Xbox One の devkit を使用している場合は、アクティブなソリューション
プラットフォームを Gaming.Xbox.XboxOne.x64 に設定します。

Project Scarlett を使用している場合は、アクティブなソリューション
プラットフォームを Gaming.Xbox.Scarlett.x64 に設定します。

*詳細については、GDK
ドキュメント*の「サンプルの実行」を*参照してください*。

# サンプルの使用

| 動作                                      |  フロント パネル          |
|-------------------------------------------|--------------------------|
| 新しいゲームを開始する                    |  ボタン 1                 |
| ヘビを移動する  |  方向パッド (左、右、上、下)         |
| スクリーンショットをとる                  |  方向パッド選択           |
| ゲーム モードとシステム モードを切り替える |  方向パッド選択の長押し |

# 更新履歴

2019 年 4 月、サンプルの最初のリリース。

2019 年 11 月、Project Scarlett Devkit のサポート。

# プライバシーに関する声明

サンプルをコンパイルして実行すると、サンプルの使用状況を追跡するため、サンプル実行可能ファイルのファイル名が
Microsoft に送信されます。このデータ収集を無効にするには、「Sample Usage
Telemetry」とラベル付けされた Main.cpp
内のコードのブロックを削除します。

Microsoft のプライバシー方針の詳細については、「[Microsoft
プライバシーに関する声明](https://privacy.microsoft.com/en-us/privacystatement/)」を参照してください。
