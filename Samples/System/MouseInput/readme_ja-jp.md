![](./media/image1.png)

# マウス入力のサンプル

*このサンプルは、Microsoft Game Development Kit と互換性があります (2020 年 8 月)*

# 説明

このサンプルでは、GameInput を使用してマウス コントロールを実装する方法を示します。 2 つの異なるマウス コントロールが示されています。相対マウス コントロールとクリップ カーソル マウス コントロールは、アプリまたはゲームのウィンドウ内に収まるように Windows マウスをキャプチャします。

# サンプルの使用方法

このサンプルでは、UI およびゲーム モードとの対話にマウス コントロールを使用します。 左右のマウス ボタンを押して、さまざまなゲーム モードを終了し、UI に戻ります。

# 実装メモ

このサンプルでは、GameInput を使用した低待機時間の生デルタと OS によって計算される絶対位置という 2 つの方法でマウスを使用します。

## 相対モード (一人称視点シューティング)

このモードは、"マウスルック" または "マウス移動" カメラ モードと呼ばれることがあります。 一部のアプリやゲームでは、マウスの位置ではなく、マウスの相対的な動きに基づいて、一般的な入力デバイスとしてマウスを使用することをお勧めします。 これは、一人称視点のシューティング ゲームでよく見られます。

サンプルでこのモードを開始するには、マウスの左ボタンを使用して最初の人物のシューティング タイルを選択します。 マウスの左ボタンと右ボタンの両方を押して終了します。

## エッジ カーソル モード

このモードでは、マウスはアプリケーションのウィンドウの境界に制限され、それらの境界に近づくとスクロールします。 待機時間の短い入力に GameInput を使用するのではなく、OS によって計算された処理された絶対位置を取得します。 サンプルでこのモードを開始するには、マウスの左ボタンを使用して [リアルタイム戦略] タイルを選択します。 マウスの左ボタンと右ボタンの両方を押して終了します。

# プライバシーにかんするせいめい

サンプルをコンパイルして実行する場合、サンプルの使用状況を追跡するために、サンプルの実行可能ファイルのファイル名が Microsoft に送信されます。 このデータ コレクションからオプトアウトするには、Main.cpp の "サンプル使用状況テレメトリ" というラベルの付いたコードのブロックを削除します。

Microsoft のプライバシー ポリシー全般の詳細については、「[Microsoft のプライバシーに関する声明](https://privacy.microsoft.com/en-us/privacystatement/)」を参照してください。


