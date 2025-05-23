![](./media/image1.png)

# AutoRGB サンプル

*このサンプルは、Microsoft Game Development Kit と互換性があります (2023 年 3 月 QFE1)*

# 説明

このサンプルでは、特定のシーンから 1 つの代表的なアンビエントカラーを抽出し、それを使用して接続デバイス (HID) からランプを点灯させる方法を示します。は LampArray API を使用してデバイスと通信するため、このサンプルには 2023 年 3 月の QFE 1 GDK 以降のバージョンが**必要**です。

![](./media/readme/image0.png)

> **ご注意ください:** 2023 年 3 月 QFE1 のリリース時点では、GDK LampArray API はコンソールで次のデバイスのみをサポートしています。 今後のリカバリ リリースでは、追加のデバイスのサポートが追加される予定です。
> - Xbox One 用 Razer Turret (キーボードとマウス)
> - Razer BlackWidow Tournament Edition Chroma V2

# サンプルのビルド

Xbox One 開発キットを使用している場合は、アクティブなソリューション プラットフォームを `Gaming.Xbox.XboxOne.x64` に設定します。

Xbox Series X|S を使用している場合は、アクティブなソリューション プラットフォームを `Gaming.Xbox.Scarlett.x64` に設定します。

*詳細については、* *GDK ドキュメント*の「__サンプルの実行__」を参照してください。

# Controls

| 操作 | ゲームパッド |
|---|---|
| ヒューリスティックを切り替える | A |
| シーンの濃淡を切り替える | B |
| モードを切り替える | Y |
| ライトの切り替え (サンプル モード) | RB |
| ヒストグラム UI の切り替え | LB |
| 色の切り替え速度を変更する | 右/左 DPad |
| 基本光強度の変更 (サンプル モード) | 上/下方向パッド |
| 次の画像に移動する (スクリーンショット モード) | RT |
| 前の画像に移動する (スクリーンショット モード) | LT |
| カメラを回す (サンプル モード) | 上に移動するための LT-RT、右スティックを下に移動して回転ビューを左スティックに移動し、平行移動します |
| サンプルを終了する。 | ビュー ボタン |

# 実装メモ

このサンプルでは、2 つのモードを示します。

## サンプル モード

![](./media/readme/image1.png)

1 つ目 (既定値) は通常のサンプルで、カメラを点灯したシーンの周りを自由に移動できます。 このシーンは、現在抽出されている色を表すカラー バンドでレンダリングされます。 カメラはシーン内を自由に移動でき、リアルタイムで色が更新されます (前のフレームの情報から計算されるため、遅延は 1 フレームです)。

コントロールを使用すると、次の方法でシーンを変更できます。 ライトのオンとオフを切り替えることができます (さまざまなレベルの照明と抽出された色の外観をテストするため)。 また、**ベース ライトの強度**レベルを制御して、上または下に移動することもできます。 0 に設定すると、ライトがオフに切り替えられると、シーンが真っ暗になります。 このサンプルでは、代表的な色が変化する速度を変更することもできます。 これは 1 フレームほど速くなりますが、**色の切り替え速度**を下げてスムーズにすることもできます。

最後に、B キーを押すと、サンプルはシーン全体に赤、緑、または青の濃淡を適用します。 これは、移行速度が正しいかどうか、または使用されるヒューリスティックが基本的なケースを適切に処理しているかどうかを簡単にテストするためです (以下のヒューリスティックの詳細を参照)。 B キーを押すと、サンプルは濃淡なし、赤、青、緑の間で回転します (その後、濃淡なしに戻ります)。 これはサンプル モード専用です。

## スクリーンショット モード

![](./media/readme/image2.png)

Y キーを押すと、サンプルはモードを切り替えます。 スクリーンショット モードでは、同じカラー バンドでゲームの静的な画像が表示されます。 ゲームパッド トリガーを使用すると、スクリーンショット内を移動できます。 これは、抽出された色が実稼働レベルのゲームのシーンとどの程度一致するかを示すために意図されています。 このモードではカメラを動かすことはできません。また、濃淡や基本光の強度を変更することもできません。

# UI

サンプルにはパス (PIX のヒストグラム) があり、現在のシーン (サンプルの背景または現在選択されているスクリーンショット) で何らかの画像処理を実行し、次に示すように 4 つのヒストグラムを取得します:

![](./media/readme/image3.png)

次の図では、赤い濃淡がシーンに適用されています。 ヒストグラム UI はそれに応じて変化し、より高い強度のビンにより多くの赤が表示されます。 ![](./media/readme/image4.png)

最初の 3 つのヒストグラムは、シーンに存在する赤、緑、青の量と、強度の観点から分布方法に対応します。 各ヒストグラムは 8 つのビンに分割されます。 各色の強度は 0 ~ 255 であるため、各ビンには、低強度 (左) から高強度 (右) までの 32 の強度値が含まれます。 各ビンの高さは、その強度範囲内にあるピクセル数に対応します。 4 番目のヒストグラムは、輝度コンポーネントを示し、シーンの輝度の測定値を取得するのに役立ちます。

> 一部のデバイスでは色の設定のみが許可されますが、その他のデバイスでは強度を変更することもできます。

# ヒューリスティック

サンプルがヒストグラムの形式で色分布情報を取得したら、これを使用して代表的なアンビエントカラーを取得できます。これを行うには、**ヒューリスティック**を使用する必要があります。 現時点では、このサンプルはシーン全体の単一の色を取得することを目的としています (そのため、色の場所に関する情報は取得されません)。 つまり、ヒューリスティックは、3 つのコンポーネント (赤、緑、青) の分布が等しく、灰色を返さない可能性があるケースを処理し、代わりにどの色がシーンにより多くの影響を及んでいるかを導き出す必要があることを意味します。

このサンプルには、A ボタンで変更できる 3 つのヒューリスティックがあります。 3 つの簡単な説明を次に示します。

1. 上位 X バケット: このメソッドは、3 つのコンポーネントの最も高いビンのみを調べてから開始します。 最初のビンでカバーされるピクセルの量が設定されたしきい値を超える場合、このビンのみが色の計算に使用されます。 それ以外の場合は、次のビンが追加され、プロセスが繰り返されます。 このヒューリスティックの考え方は、ピクセルの強度が高い色により多くの重みを与える一方で、ピクセル数を考慮してビンの数を適応的に変更することです。

2. 平均: すべてのヒストグラムの加重平均を取得し、結果を正規化するだけです。 明るいシーンでも同様の結果が得られますが、もっと薄暗い、暗いシーンでは色が強調される傾向があります。

3. バケット x AVG (**既定値**): 名前が示すように、このヒューリスティックは、前の 2 つの結果を補間し、その間をオファーします。

# 注意

# 更新履歴

2023 年 4 月 8 日 -- 移植されたサンプル。

# プライバシーに関する声明

サンプルをコンパイルして実行する場合、サンプルの使用状況を追跡するために、サンプルの実行可能ファイルのファイル名が Microsoft に送信されます。 このデータ コレクションからオプトアウトするには、Main.cpp の "サンプル使用状況テレメトリ" というラベルの付いたコードのブロックを削除します。

Microsoft のプライバシー ポリシー全般の詳細については、「[Microsoft のプライバシーに関する声明](https://privacy.microsoft.com/en-us/privacystatement/)」を参照してください。


