# HDR 調整のサンプル

*このサンプルは、Microsoft Game Development Kit と互換性があります (2022 年 3 月)*

# 説明

HDR テレビは、HDR 機能に関していえば幅広く異なり、画像品質に影響を与えます。 エントリ レベルのテレビでは、HDR を物理的に再生することが困難な場合があります。これは、ピーク時の明るさが十分ではなく、ローカルイルミネーションではなくパネル全体のイルミネーションを使用する場合があります。 これらの違いを補正するために、ゲームでは、消費者がゲームの HDR 画像を調整できるようにする必要があります。 このサンプルでは、HDR テレビを HDR モードに切り替え、ユーザーに暗さと明るさで表示される詳細を調整したり、画像の全体的な輝度と色の彩度を調整したりするためのさまざまな調整オプションを提供します。 2 つの異なるモードを使用できます。ユーザーが適切に見えるまで画像を調整する際の自動調整と、テレビの機能を決定するためのテスト パターンが表示される目的の調整です。

![](./media/image1.jpeg)

# サンプルのビルド

Xbox One 開発キットを使用している場合は、アクティブなソリューション プラットフォームを `Gaming.Xbox.XboxOne.x64` に設定します。

Xbox Series X|S を使用している場合は、アクティブなソリューション プラットフォームを `Gaming.Xbox.Scarlett.x64` に設定します。

*詳細については、* *GDK ドキュメント*の「__サンプルの実行__」を参照してください。

# サンプルの使用方法

このサンプルでは、次のコントロールを使用します。

| 操作 | ゲームパッド |
|---|---|
| 調整の適用の切り替え | A |
| 調整画面の表示/非表示 | X |
| 主観的な調整と目的の調整の切り替え | B |
| 調整を選択 | 方向パッド (上/下) |
| 選択した調整を調整する | 方向パッドの左右 |

# 実装メモ

**明るさの詳細** -- テレビで表示できる値を超える HDR 値はクリップされるため、明るさの詳細は失われます。 シーン内の非常に明るい HDR 値をテレビの最大輝度にマップできるように、テレビの最大認識明るさを決定する必要があります。 調整イメージは、ST.2084 仕様の最大輝度である 10,000 ニトを表す値をシーンにレンダリングします。 その後、小さい画像が現在の明るさでレンダリングされます。 ユーザーは、2 つの画像を区別できなくなるまで、現在の明るさの値を調整します。 たとえば、テレビで 1,000 ニトを表示できる場合、1,000 ニトよりも明るいピクセルを表すシーンにレンダリングされた値は、1000 ニトとして認識されます。 HDRDisplayMapping サンプルを参照してください。 Xbox システム HDRGameCalibration の MaxToneMapLuminance 値は、この値の適切な既定の開始点として使用されます。 コンシューマーは、本体の [設定] の [ゲームの HDR の調整] オプションからアプリにアクセスできます。

**暗さの詳細** -- ほとんどのゲームには、表示ガンマを決定するためのビデオ オプションがメニューにあります。 これを使用して、ピクセル シェーダーのパワー関数を使用してコントラストを修正し、暗い色で正しい量の詳細を確認できます。 この調整は、テレビが HDR モードの場合に非常に重要です。 適切な調整を行わないと、HDR イメージは SDR イメージと比較して "フラット" でくすんで見えます。 画面の中央に調整画面をレンダリングすることが重要です。これは、一部の LCD テレビの表示角度によって、画像のコントラストが小さい角度から変わる可能性があるためです。 たとえば、調整イメージを LCD 画面の側面にレンダリングする場合、決定された表示ガンマ値は、画面の中央でレンダリングする場合と若干異なります。 点滅するイメージを使用すると、この調整に適しています。これは、中央の調整ブロックが非表示になるタイミングをユーザーが簡単に判断できるためです。 コントラスト調整を適用すると、HDR シーンの最大値が変更されることに注意してください。これは、効果的な HDR ディスプレイ マッピングを行うために重要であるため、HDR ディスプレイ マッピングに入る最大シーン値にもコントラスト調整関数を適用する必要があります。

**全体的な明るさ** -- エントリ レベルの HDR テレビには、ピーク時の明るさが大きくはありません。 HDR を表示できるようにするには、イメージの SDR 範囲の明るさを低下させる必要があります。これにより、SDR テレビと比較してイメージの外観が悪くなる可能性があります。 たとえば、100 ニトをレンダリングする場合、優れた HDR テレビでは 100 ニトが出力されますが、エントリ レベルのテレビでは、100 ニトをレンダリングする場合にのみ 30 ニトが出力される場合があります。 したがって、コンシューマーがイメージ内の SDR 範囲の明るさを調整できるようにする必要があります。 これを行うには、ペーパーホワイトのホワイト ニト値を調整します。 ペーパーホワイトが大きくなると、HDR の範囲が小さくなる可能性があることに注意してください。 したがって、より小さい HDR 範囲で明るい SDR 範囲の侵害をコンシューマーが理解できるように、明るい色に多くの詳細を含む HDR イメージを表示することをお勧めします。

**色の彩度** -- HDR テレビのディスプレイ パネルには、Rec.709 色空間の外部で色を生成できるため、非常に明るくカラフルな画像を生成する機能があります。 SDR モードでは、テレビは色域拡張を使用して SDR イメージをよりカラフルに見せることが多いです。 HDR モードで理論上正しい色をレンダリングする場合、多くの場合、イメージは SDR モードの場合よりもカラフルではありません。 この問題の解決策は、ゲーム内で色域拡張を行うことです。 このオプションは、適用する色域拡張の量を制御します。

テスト パターンで目的の調整を使用する場合は、表示ガンマやソフト ショルダーを実際の輝度調整ブロックに適用しないように注意してください。これにより、認識される最大輝度値が変更されるためです。 このサンプルでは、ブロックの境界ボックスを使用してこれらを無視しますが、バック グラウンドのプレビュー イメージに適用します。 たとえば、テレビの最大認識明るさを決定しようとすると、ディスプレイガンマ調整を使用すると、間違った値になります。

ホワイト ペーパー「[HDR on Xbox One](http://aka.ms/hdr-on-xbox-one)」と HDRDisplayMapping サンプルを参照してください。

*テスト 画像は、Turn 10 Studios によって開発され*、Microsoft Studios によって公開された *Forza Horizon 3 からキャプチャされたスクリーンショットです*

# 既知の問題

なし

# 更新履歴

初回のリリース 2019 年 6月

# プライバシーに関する声明

サンプルをコンパイルして実行する場合、サンプルの使用状況を追跡するために、サンプルの実行可能ファイルのファイル名が Microsoft に送信されます。 このデータ コレクションからオプトアウトするには、Main.cpp の "サンプル使用状況テレメトリ" というラベルの付いたコードのブロックを削除します。

Microsoft のプライバシー ポリシー全般の詳細については、「[Microsoft のプライバシーに関する声明](https://privacy.microsoft.com/en-us/privacystatement/)」を参照してください。


