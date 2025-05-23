![](./media/image1.png)

# Compute Particles

*このサンプルは、Microsoft Game Development Kit と互換性があります (2022 年 3 月)*

# 説明

このサンプルは、計算シェーダーと追加バッファーを使用して基本的なパーティクル シミュレーションを実行し、膨大な数のパーティクルを頻繁にレンダリングする方法を示します。

![](./media/image3.png)

# サンプルのビルド

Xbox One 開発キットを使用している場合は、アクティブなソリューション プラットフォームを `Gaming.Xbox.XboxOne.x64` に設定します。

Xbox Series X|S 開発キットを使用している場合は、アクティブ ソリューション プラットフォームを `Gaming.Xbox.Scarlett.x64` に設定します。

*詳細については、* *GDK ドキュメント*の「__サンプルの実行__」を参照してください。

# サンプルの使用方法

このサンプルでは、次のコントロールを使用します。

| 操作 | ゲームパッド |
|---|---|
| サンプルを終了する。 | 選択 |
| パーティクルの弾力性を上げる/下げる | 右/左トリガー |
| カメラを回転させる | 左スティックと右スティック |
| パーティクル エミッターを移動する | 左スティックと右スティック + 右肩 |
| パーティクルのレンダリングを切り替える | A ボタン |
| パーティクルの更新を切り替える | B ボタン |
| パーティクルの数を増やす/減らす | 方向パッド (上/下) |

# 実装メモ

このサンプルでは、D3D11 とコンピュート シェーダーで使用できる、より難解で興味深い手法の一部を示します。 このサンプルには興味をそそる 3 つの部分があります。 最初の 2 つはパーティクルの更新される方法とカリングされる方法に関連しており、3 つ目は、コンピュート シェーダー ステージの結果が通常のレンダリング パイプラインでどのように使用されるかについて示しています。

1. **パーティクル シミュレーション**

AdvanceParticlesCS コンピューター シェーダー シミュレーション フェーズには、主に 2 つの手順が含まれています。 まず、パーティクルの位置、速度、および経過時間が UAV バッファーから読み取られ、ワールド スペースでシミュレートされます。 その後、簡略化されたワールド ジオメトリ (グラウンド平面と球) に対する衝突は、ブルート フォース アプローチを使用して計算されます。 新しい位置、速度、年齢は同じ UAV バッファーに書き戻され、以前に読み取られたデータが上書きされます。

2. **パーティクルのカリングと書き込み**

単純な平面カリング アルゴリズムが各パーティクルに適用され、視錐台内に表示するかどうかを検討します。 パーティクルが表示されると、その位置がレンダリング用の追加バッファーに追加されます。

追加バッファーを使用するには、 `ID3D12Device::CreateUnorderedAccessView(...)` API を使用してバッファー リソースの順序なしアクセス ビュー (UAV) を作成し、2 番目のリソースを 'pCounterResource' パラメーターとして指定します。 追加バッファーの現在のカウント (1 つの 32 ビット符号なし整数) を格納するには、カウンター リソースが少なくとも 4 バイトである必要があります。 カウンター リソースの UAV も作成され、 `ID3D12GraphicsCommandList::ClearUnorderedAccessViewUint(...)` API を使用して各フレームの数をクリアできます。 作成したら、バッファーを `AppendStructuredBuffer<...>` として宣言された UAV シェーダー スロットにバインドするだけです。

AdvanceParticlesCS コンピュート シェーダーは、アクティブなパーティクル インスタンスをシミュレートし、追加バッファーに追加します。 完了すると、`ID3D12GraphicsCommandList::CopyBufferRegion(...)` API を使用して、カウンター リソースから間接引数バッファー リソースにパーティクル数をコピーします。これは、`ID3D12GraphicsCommandList::ExecuteIndirect(...)` API への入力として使用できます。 これにより、AdvanceParticlesCS の視錐台のカリング テストによって指示された可視パーティクルのみを描画できます。

3. **レンダリング**

`ID3D12GraphicsCommandList::ExecuteIndirect(...)` API は、パーティクル レンダリングをディスパッチするために使用されます。 `ID3D12Device::CreateCommandSignature(...)` を使用して作成されたコマンド シグネチャは、ExecuteIndirect がディスパッチするコマンドの種類を指定するために必要です。 コマンドの種類によって、間接引数バッファーの内容の解釈方法が決まります。 この場合、コマンドの種類は 'Draw' で、`ID3D12GraphicsCommandList::DrawInstanced(...)` API に関連付けられます -- 4 つの 32 ビット符号なし整数です。 VertexCountPerInstance を 4 つにハードコーディングし、パーティクル数を各フレームの InstanceCount の場所にコピーします。

頂点属性は、頂点シェーダーの定数参照テーブルとしてハードコーディングされます。 頂点 ID (SV_VertexID) は、各頂点の属性にアクセスするために、この検索テーブルにインデックスを作成するために使用されます。 インスタンス ID (SV_InstanceID) は、各インスタンスのプロパティにアクセスするために、パーティクル インスタンス バッファーにインデックスを作成するために使用されます。

# 更新履歴

2019 年 3 月 -- 従来の Xbox サンプル フレームワークから新しいテンプレートに移植します。

# プライバシーに関する声明

サンプルをコンパイルして実行する場合、サンプルの使用状況を追跡するために、サンプルの実行可能ファイルのファイル名が Microsoft に送信されます。 このデータ コレクションからオプトアウトするには、Main.cpp の "サンプル使用状況テレメトリ" というラベルの付いたコードのブロックを削除します。

Microsoft のプライバシー ポリシー全般の詳細については、「[Microsoft のプライバシーに関する声明](https://privacy.microsoft.com/en-us/privacystatement/)」を参照してください。


