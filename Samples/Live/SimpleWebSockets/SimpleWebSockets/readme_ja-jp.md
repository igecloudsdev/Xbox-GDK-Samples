  ![](./media/image1.png)

#   SimpleWebSockets サンプル

*このサンプルは Microsoft GDK (Desktop) および GDKX (Xbox) (2020 年 6
月) と互換性があります*

# 説明

このサンプルでは、LibHttpClient を使用して、Web
ソケット経由でホストとの間でメッセージを接続、送受信する方法を示します。

# サンプルのビルド

XDKS.1
サンドボックスを使用する場合、サンプルは、ビルドに特定の変更を必要とせず、修正なしで実行する必要があります。

*詳細については、GDK
のドキュメントの*「サンプルの実行」*を参照してください。*

# サンプルの使用方法

サンプルを実行すると、送信したメッセージを繰り返すサービスへの WebSocket
接続を開くことができます。

最初に \[接続\] ボタンをクリックして WebSocket 接続を確立します。
既定では、サンプルは wss://echo.websocket.org で開いているエコー
サーバーに接続します。 接続すると、\[メッセージの送信\]
を選択すると仮想キーボードが表示されるので、カスタム
メッセージをエンドポイントに送信できます。\[バイナリ メッセージの送信\]
を選択すると、バイナリ ペイロードを含むテスト
メッセージがエンドポイントに送信されます。

## メイン画面

![Text Description automatically generated](./media/image3.png)

# 更新履歴

2021 年 4 月の初回リリース

# プライバシー ステートメント

サンプルをコンパイルして実行する場合、サンプルの使用状況を追跡するために、サンプル実行ファイルのファイル名が
Microsoft に送信されます。このデータ
コレクションからオプトアウトするには、Main.cpp の「Sample Usage
Telemetry」というラベルの付いたコードのブロックを削除します。

全般的な Microsoft のプライバシー ポリシーの詳細については、「[Microsoft
プライバシー
ステートメント](https://privacy.microsoft.com/en-us/privacystatement/)」を参照してください。