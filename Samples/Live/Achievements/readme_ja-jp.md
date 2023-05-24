  ![](./media/image1.png)

#   Achievements 2017 のサンプル

*このサンプルは、Microsoft ゲーム開発キットのプレビュー (2019 年 11 月)
に対応しています。*

# 

# 説明

このサンプルは、Microsoft ゲーム SDK によって提供されている Achievements
2017 (「簡素化された実績」とも呼ばれます) C-API
を使用する方法を示します。 このサンプルには、次のシナリオが含まれます。

-   複数ページの結果の処理を含む、タイトルのすべての実績を対象にした
    Xbox Live に対するクエリの実行

-   1 つの実績を対象にしたクエリの実行

-   実績の進行状況の更新

# サンプルの作成

Xbox One の devkit を使用している場合は、アクティブなソリューション
プラットフォームを Gaming.Xbox.XboxOne.x64 に設定します。

Project Scarlett を使用している場合は、アクティブなソリューション
プラットフォームを Gaming.Xbox.Scarlett.x64 に設定します。

*詳細については、GDK ドキュメントの*
「サンプルの実行」*を参照してください。*

# サンプルの実行

-   実績の進行状況の更新を送信するには、Xbox Live のテスト
    アカウントにサインインする必要があります。

-   Xbox One devkit: コンソールのサンドボックスを XDKS.1 に設定します

# サンプルの使用

## 

![](./media/image3.png)

| 実施                                   |  ゲームパッド                |
|----------------------------------------|-----------------------------|
| 実行するシナリオを選択                 |  方向パッドを上へ/下へ       |
| シナリオを実行                         |  A ボタン                    |
| \[表示\] ボタン                        |  終了                        |

\[ログ\] ウィンドウには、呼び出されている API の情報が表示されます。
\[結果\] ウィンドウには、サービスの応答内容の一部が表示されます。

# 試すシナリオ

-   すべての実績を列挙する

    -   このサンプルでは "take" カウントを意図的に 1
        に制限しており、このサンプルには 2
        つの実績が登録されているため、すべての実績を取得するには API を
        2 回呼び出す必要があります。

-   1 つの実績を取得する

    -   これは、特定の実績の状態を確認する場合に使用します。
        タイトルの実績をすべてクエリしたくない場合は、これをお勧めします。

-   1 回の呼び出しで実績を完了する

    -   これにより、1 回の呼び出しで実績の進行状況の値が 100
        に設定されます。 多くの実績はこのように動作します
        (プレイヤーが新たなレベルに入った、映像を視聴したなど)。

-   複数の呼び出しを使用して実績を完了する

    -   これにより、実績が、ボタンで指定した値に設定されます。
        進行状況がアップロードされていない実績は、\"未開始\"
        とマークされます。 100
        未満の値がアップロードされた実績は、\"進行中\"
        とマークされます。

    -   進行状況を送信することによって返される応答に注意してください。

        -   実績 2 を \"25%\" に設定すると、初回は成功します。
            再度その値に設定すると、\"変更されていません\"
            という応答が返されます。

        -   その後、実績 2 を \"50%\" に設定すると、再び成功します。
            その後、25% または 50% に設定しようとすると、再び
            \"変更されていません\" という応答が返されます。
            また、どちらの場合も、Get Achievement
            を呼び出したときに、それまでに受け取った最高のパーセンテージ値が返されることに注意してください。

        -   実績 2 が 100% に設定されると、 \"達成済み\"
            とマークされ、どの呼び出しによっても変更できなくなります。

# 実装に関する注意事項

Achievements 2017 API の動作は、Achievements 2013
(\"クラウドに基づく実績\" とも呼ばれます) API とは異なります。
この[ドキュメント](https://docs.microsoft.com/en-us/gaming/xbox-live/achievements-2017/simplified-achievements)には、相違点の多くと、それらの相違点の背景にある理由が説明されています。

# 既知の問題

すべての実績がユーザーによって達成されると、実績を再度トリガーすることはできません。
再度表示するには、新しいユーザーを選択する必要があります。

# 

# 更新履歴

**初期リリース:**2019 年 4 月

# 

# プライバシーに関する声明

サンプルをコンパイルして実行すると、サンプルの使用状況を追跡するため、サンプル実行可能ファイルのファイル名が
Microsoft に送信されます。このデータ収集を無効にするには、「Sample Usage
Telemetry」とラベル付けされた Main.cpp
内のコードのブロックを削除します。

Microsoft のプライバシーに関する声明の詳細については、「[Microsoft
のプライバシーに関する声明](https://privacy.microsoft.com/en-us/privacystatement/)」を参照してください。