![](./media/image1.png)

# Advanced Lighting サンプル

*このサンプルは、Microsoft Game Development Kit と互換性があります (2022 年 3 月)*

# 説明

このサンプルでは、シーン上の多数のライトを処理する際のレンダリング パフォーマンスを向上させるさまざまな手法を示します。

![](./media/image2.png)

# サンプルのビルド

Xbox One 開発キットを使用している場合は、アクティブなソリューション プラットフォームを `Gaming.Xbox.XboxOne.x64` に設定します。

Xbox Series X|Sを使用している場合は、アクティブなソリューション プラットフォームを `Gaming.Xbox.Scarlett.x64` に設定します。

PC で実行している場合は、アクティブなソリューション プラットフォームを `Gaming.Xbox.Desktop.x64` に設定します。

*詳細については、* GDK ドキュメントの「__サンプルの実行__」* を参照してください。*

# Controls

| 操作 | ゲームパッド |
|---|---|
| 手法を切り替える | A / B |
| ライトの半径を変更する | 右/左 DPad |
| ライトの切り替え | LB |
| レンダリング光源の切り替え (色付きパーティクル) | RB |
| カメラを回す | 上に移動するための LT-RT、右スティックを下に移動して回転ビューを左スティックに移動し、平行移動します |
| サンプルを終了する。 | ビュー ボタン |

# 実装メモ

サンプルでは、次のレンダリング手法を示します:

- 遅延レンダリング

- ライト ボリューム

- タイル遅延

- クラスター化された遅延

このサンプルでは、GPU にかかった時間とフレーム全体にかかった時間のタイマーを示すことで、これらの手法が相互にどのように比較されるかを示します。

ライト ボリュームの場合、アルゴリズムは、ライトのワールド位置と半径を使用して球体メッシュをレンダリングしてシーン上に配置およびスケーリングします。 この方法では、球体によってラスター化されたピクセル上の特定のライトに対してのみ動作します。 もちろん、(位置情報、ライトの減衰、ジオメトリ バッファーによって提供されるシーン情報を使用して) そのピクセルがライトの影響を受けているかどうかを確認する必要があります。

ライトのボリュームの欠点は、ラスター化された場合に複数の球体が重なったときに発生します。これは、同じピクセルに対して複数の描画呼び出しを呼び出すことになるためです。

タイル遅延は、この問題の解決策です。 球体をレンダリングする代わりに、画面をタイルに分割し、ライトをこれらのタイルにビン分割して、各タイルに影響を与えるすべてのライトの一覧を保持します。 次に、タイルごとにスレッド グループを割り当て、ライトのないタイルをスキップして、すべてのライトの計算を実行するコンピューティング シェーダーをディスパッチできます。

タイル遅延はライト ボリュームよりも向上しますが、それでもいくつかの問題があります。 1 つは、タイルに影響を与えるライトを調べているので、そのタイル内のシーン要素に影響を与えないライトの時間を無駄にしている可能性があるということです (たとえば、タイルの最も遠い要素よりも遠い場合があります)。 これは深度境界を定義することで解決できるため、シーンの最小深度と最大深度の間にあるライトのみを考慮します。 しかし、別の問題は深度の不連続です。同じタイルに異なる深度に 2 つのオブジェクトがある場合、シーン上の要素に影響を与えない場合でも、その間にあるすべてのライトが含まれます。

これを解決するために、提示される 3 番目の手法はクラスター化遅延です。 基本的には Tiled と同じ原則ですが、画面をタイル (2D) に分割するのではなく、fustrum をセル (3D クラスター) に分割します。 これを行い、これらのクラスターでライトをビン分割すると、シーン上で何も影響を与えないが、深度境界の間にあるライトの処理を保存できます。

# 注意

- 現在、ライト ボリュームは fustrum カリングされていません。

- サンプルは現在であるため、光源は他の光源の影響を受けません。

- 1 つのタイルのライトの数が許可されている最大値 (512) を超えた場合に表示されるアーティファクトがあります。 これは、半径が十分に膨らんでいる場合に発生します。

# 更新履歴

2022 年 9 月 26 日 -- 移植されたサンプル。

# プライバシーに関する声明

サンプルをコンパイルして実行する場合、サンプルの使用状況を追跡するために、サンプルの実行可能ファイルのファイル名が Microsoft に送信されます。 このデータ コレクションからオプトアウトするには、Main.cpp の "サンプル使用状況テレメトリ" というラベルの付いたコードのブロックを削除します。

Microsoft のプライバシー ポリシー全般の詳細については、「[Microsoft のプライバシーに関する声明](https://privacy.microsoft.com/en-us/privacystatement/)」を参照してください。

