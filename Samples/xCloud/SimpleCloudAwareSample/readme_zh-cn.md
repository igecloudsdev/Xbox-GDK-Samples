# 简单云感知示例

*此示例可用于 Microsoft 游戏开发工具包 (2022 年 3 月)*

# 说明

此示例演示如何检测游戏流式处理客户端、更改屏幕控件布局、读取触摸点。

![屏幕截图显示自动生成的计算机描述以及中等可信度](./media/image1.png)

# 使用示例

在启动示例之前，请确保已启用游戏流式处理。 可以在&ldquo;流式处理&rdquo;部分的&ldquo;开发者主页&rdquo;中执行此操作，或从&ldquo;游戏&rdquo;命令提示符运行 xbgamestream startlistening。

使用任何兼容的客户端应用（如 Xbox 游戏流式处理测试应用）连接到运行示例的主机。 连接后，该示例应更改以反映流式处理客户端的存在。

该示例包括可通过在游戏命令提示符中运行来加载的示例布局：

tak serve \--takx-file sample-layouts.takx

按下按钮可显示内容，移动控制杆和扳机可查看其读数。 按 A（或覆盖中的 A 等效项）切换到新的覆盖。 如果客户端已启用触摸，请触摸屏幕以查看正在读取的触摸点。

# 实现说明

此示例演示如何使用适用于 xCloud 的云感知 API。

布局来自示例布局 GitHub： <https://github.com/microsoft/xbox-game-streaming-tools/tree/main/touch-adaptation-kit/samples>

# 版本历史记录

2021 年 5 月：初始示例

2022 年 3 月：更新以更正初始化代码

# 隐私声明

在编译和运行示例时，将向 Microsoft 发送示例可执行文件的文件名以帮助跟踪示例使用情况。 若要选择退出此数据收集，你可以删除 Main.cpp 中标记为&ldquo;示例使用遥测&rdquo;的代码块。

有关 Microsoft 的一般隐私策略的详细信息，请参阅 [Microsoft 隐私声明](https://privacy.microsoft.com/en-us/privacystatement/)。


