<img style="float: left" src="./media/image1.png" /><img style="float: right" src="./media/image3.png" /> <br/><br/><br/><br/><br/>

# FidelityFX コントラスト アダプティブ シャープニング (CAS) サンプル

*このサンプルは、Microsoft Game Development Kit と互換性があります (2022 年 3 月)*

# 説明

このサンプルでは、シーンに対して AMD の FidelityFX Contrast Adaptive Sharpening (CAS) を利用するさまざまな方法を示します。

![](./media/image4.jpeg)

# サンプルのビルド

Windows デスクトップを使用している場合は、アクティブなソリューション プラットフォームを `Gaming.Desktop.x64` に設定します。

Xbox One 開発キットを使用している場合は、アクティブなソリューション プラットフォームを `Gaming.Xbox.XboxOne.x64` に設定します。

Xbox Series X|S を使用している場合は、アクティブなソリューション プラットフォームを `Gaming.Xbox.Scarlett.x64` に設定します。

*詳細については、* *GDK ドキュメント*の「__サンプルの実行__」を参照してください。

# サンプルの使用方法

| 操作 | ゲームパッド |
|---|---|
| CAS モードのサイクル | A ボタン / B ボタン |
| アップスケール モードのレンダースケールを循環する | X ボタン / Y ボタン |
| 回転ビュー | 左サムスティック |
| ビューのリセット | 左サムスティック (クリック) |
| シャープネスの量を増やす | 右トリガー |
| シャープネスの量を減らす | 左トリガー |
| Exit | ビュー ボタン |

# 実装メモ

コントラスト アダプティブ シャープニング (CAS) は、画像をシャープにしたり、必要に応じてスケーリングしたりするための混合機能を提供します。 このアルゴリズムでは、ピクセルあたりのシャープニングの量を調整して、イメージ全体のシャープネスの均等なレベルをターゲットにします。 既にシャープになっている入力画像の領域は少なく、詳細がない領域はよりシャープになります。 これにより、アーティファクトの数を減らすと、全体的な自然な視覚的なシャープネスが向上します。

CAS は、既存のテンポラル アンチエイリアシング (TAA) ソリューションの品質を向上させるために設計されました。 TAA では、多くの場合、一時的なフィードバックによって可変量のぼかしが発生します。 CAS によって提供されるアダプティブ シャープニングは、TAA の後に生成された画像の詳細を復元するのに最適です。

CAS のオプションのスケーリング機能は、動的解像度スケーリング (DRS) をサポートするように設計されています。 DRS では、フレームごとにレンダリング解像度が変更されます。固定解像度ユーザー インターフェイス (UI) を作成する前にスケーリングする必要があります。 CAS は、シャープニングを適用する同じ単一パスでのアップサンプリングとダウンサンプリングの両方をサポートします。

シャープニング アルゴリズムとアップスケーリング アルゴリズムの実装の詳細は <https://gpuopen.com/fidelityfx-cas/> に、さらに深く掘り下げたプレゼンテーションは <https://gpuopen.com/wp-content/uploads/2019/07/FidelityFX-CAS.pptx> にある。

## 統合

シャープニングは、既存のポスト TAA シャープ パスの代わりにのみ使用できます。

シャープニング + アップサンプリングは、1 回のパスで動的解像度のスケーリングに使用できます。

CAS の前に発生するフィルム粒子の量を減らす方が良い可能性があります (CAS は粒子を増幅するため)。

別の方法として、CAS の後に粒子を追加する方法があります。

トーンマッピング後に CAS を実行することをお勧めしています。

CAS は UI に若干影響を与える可能性があるため、以前に適用することをお勧めします。

一般的な推奨事項 -- 後処理チェーンの後、フィルム粒子の前、UI の前

CAS は、コンピューティング シェーダーとして実行するように設計されています。

Fp32 フォームは、1 つの {64,1,1} スレッドグループを介して 8x8 タイルで動作します。 CAS は、このサンプルに実装された 4 方向のアンロールを使用して、常に展開されたループを実行するように設計されています。

## CPU 側のセットアップ

入力解像度、出力解像度、シャープニング スケールなど、CAS パスに必要なすべての情報をエンコードする 2 つの int4 定数が必要です。

これらの定数は、提供される CasSetup 関数を使用して更新できます。

```cpp
XMUINT4 const0;
XMUINT4 const1;

CasSetup(const0, const1
&nbsp;        0.5f,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; // **Sharpness tuning knob** (0.0 to 1.0).
         1920.0f,1080.0f,&nbsp; // Example input size.
&nbsp;        2560.0f,1440.0f); // Example output size.
```


CasSetup の定義は、A_CPU を定義し、ffx_a.h および ffx_cas.h ヘッダー ファイルを含めることによって、C++ ソースに含めることができます:

```cpp
#define A_CPU
#include "ffx_a.h"
#include "ffx_cas.h"
```


# 更新履歴

このサンプルは 2020 年 10 月に作成されました。

# プライバシーに関する声明

サンプルをコンパイルして実行する場合、サンプルの使用状況を追跡するために、サンプルの実行可能ファイルのファイル名が Microsoft に送信されます。 このデータ コレクションからオプトアウトするには、Main.cpp の "サンプル使用状況テレメトリ" というラベルの付いたコードのブロックを削除します。

Microsoft のプライバシー ポリシー全般の詳細については、「[Microsoft のプライバシーに関する声明](https://privacy.microsoft.com/en-us/privacystatement/)」を参照してください。

# 免責事項

ここに記載されている情報は情報提供のみを目的としており、予告なしに変更される場合があります。 このドキュメントの準備段階ではすべての予防措置が講じられていますが、技術的な不正確さ、省略、文字体裁上の誤りが含まれている可能性があり、AMD は、この情報を更新または修正する義務を負いません。 Advanced Micro Devices, Inc. は、本ドキュメントの内容の正確性または完全性に関して一切の表明または保証を行いません。また、AMD ハードウェア、ソフトウェア、またはここに記載されているその他の製品の運用または使用に関して、特定の目的に対する非侵害、商品性、適合性に関する暗黙の保証を含め、いかなる種類の責任も負いません。 このドキュメントでは、いかなる知的財産権に対しても、黙示的または禁反言によるライセンスは付与されません。 AMD 製品の購入または使用に適用される使用条件と制限は、両当事者間の署名済み契約または AMD の標準販売条件に記載されています。

AMD、AMD Arrow ロゴ、Radeon、RDNA、Ryzen、およびその組み合わせは Advanced Micro Devices, Inc. の商標です。 この文書で使用されるその他の製品名は、識別のみを目的としており、それぞれの会社の商標である可能性があります。

Windows は、米国およびその他の国における Microsoft Corporation の商標です。

Xbox は、米国およびその他の国における Microsoft Corporation の商標です。

© 2020 Advanced Micro Devices, Inc. All rights reserved.


