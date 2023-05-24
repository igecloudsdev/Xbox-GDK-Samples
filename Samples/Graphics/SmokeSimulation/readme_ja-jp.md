  ![](./media/image1.png)

#   スモーク シミュレーション

*このサンプルは、Microsoft ゲーム開発キットのプレビュー (2019 年 11 月)
に対応しています。*

# 説明

このサンプルでは、Compute Shader 6.0 と 3D
テクスチャを使用して、基本的な 3D Navier-Stokes
流体シミュレーションを実装する方法を示します。また、簡単なレイマーチ
アルゴリズムを使用して、容積測定データをレンダリングする方法についても実証します。

![](./media/image3.png)

# サンプルの作成

Xbox One の devkit を使用している場合は、アクティブなソリューション
プラットフォームを Gaming.Xbox.XboxOne.x64 に設定します。

Project Scarlett を使用している場合は、アクティブなソリューション
プラットフォームを Gaming.Xbox.Scarlett.x64 に設定します。

*詳細については、GDK ドキュメントの*
「サンプルの実行」*を参照してください。*

# サンプルの使用

このサンプルでは、次のコントロールが使用されます。

| 動作                            |  ゲームパッド                       |
|---------------------------------|------------------------------------|
| サンプルを終了する。            |  選択                               |
| カメラを回転させる              |  右スティック                       |
| エミッタを回転させる            |  左スティック                       |
| エミッタを移動する              |  左/右トリガー                      |
| エミッタの方向をリセットする    |  X ボタン                           |
| シミュレ ーションの一時停止を切り替える |  A ボタン |
| シミュレーションをリセットする  |  B ボタン                           |

# 実装に関する注意事項

**シミュレーション手法**

このサンプルで使用されるシミュレーション手法の詳細については、GPU の GPU
Gems 第 38
章「高速流体シミュレーション」に記載されています。この記事では、2D
流体にシミュレーション手法を適用していますが、このサンプルではそれを 3D
データに拡張しています。このサンプルでは、シミュレーションが 128x128x128
のグリッドに対して実行されており、その状態は 3D
テクスチャで保存されます。

Compute Shader 5.0 を使用すると、一度にすべての 3D
テクスチャのスライスを直接操作できます。これは、更新する 3D テクスチャ
スライスの指定に使用する Geometry
シェーダーによる代替法よりも効率が向上します。

**レンダリング技法**

シミュレーションの結果は、特定のシミュレーション
ステップで流体の状態を表す 3D
速度フィールドです。速度は直接表示されないため、表示できるトレース粒子が必要となり、これは速度フィールドで実行されます。シミュレーション自体に必要なすべての
3D テクスチャに加えて、これらの粒子を格納する 3D
テクスチャもあります。この 3D
テクスチャは、レンダリングの段階で可視化します。

レンダリングでは、キューブの正面をレンダリングします。ピクセル
シェーダーでは、目の位置からキューブの現在の位置に光線が出て、先の段落で述べた
3D
テクスチャをその光線に沿って一定の間隔でサンプリングする一方、色と不透明度が蓄積されます。

また、このサンプルでは、レイトキャスト
アルゴリズムの簡単かつ効果的な加速設定テクニックを示します。シミュレーション中、1/8
サイズの 3D
テクスチャは並列リダクションを使用して生成されます。レンダリングするとき、元の
3D
テクスチャを一定の間隔で直接サンプリングすると、空領域のサンプリングに多くの時間を浪費する可能性があるため、最初にこの
1/8 サイズの 3D
テクスチャをサンプリングして、サンプリングした値がしきい値よりも小さい場合、領域でチャンクをスキップします。この技法は、ここでのスモークのように、3D
テクスチャに格納されたデータが疎な場合に特に効果的です。

# 更新履歴

2019 年 4 月 -- 従来の Xbox サンプル
フレームワークから新しいテンプレートに移植。

# プライバシーに関する声明

サンプルをコンパイルして実行すると、サンプルの使用状況を追跡するため、サンプル実行可能ファイルのファイル名が
Microsoft に送信されます。このデータ収集を無効にするには、「Sample Usage
Telemetry」とラベル付けされた Main.cpp
内のコードのブロックを削除します。

Microsoft プライバシー ステートメントの詳細については、「[Microsoft
プライバシー
ステートメント](https://privacy.microsoft.com/en-us/privacystatement/)」を参照してください。