# Soton P20 Project
*By Taibo Wu & Zirui Zhang*

# 项目要求

## 3.1 图形用户界面的发送和接收窗口 - 5 分

制作一个带有两个窗口（或同一窗口的两个部分）的 Qt 应用程序，一个发送/本地窗口用于用户绘图，另一个接收/远程窗口用于显示图表。
窗口用于用户绘图，另一个接收/远程窗口用于显示来自其他用户的图。

显示来自其他用户的图表。为您支持的不同绘图操作实现各种 "绘图命令 "类
实现各种 "绘图命令 "类，以支持不同的绘图操作（至少包括线条绘制和屏幕清除）。让发送窗口
响应鼠标/键盘事件，创建这些命令，并在本地显示这些命令，使其在窗口关闭时不会消失。
窗口重新绘制时不会消失。创建这些命令时，将其传递给接收窗口
并使接收窗口显示这些命令，以便在重新绘制窗口时它们不会消失。
在重新绘制时不会消失。


## 3.2 序列化和反序列化绘图命令 - 5 分

编写代码，将这些命令序列化（即转换为二进制形式，如字符数组）并反序列化。
命令，并将其反序列化。更改发送和接收窗口，以便在发送和接收命令时将其序列化和反序列化。
序列化和反序列化。


## 3.3 实现发送和接收线程 - 5 分

实现发送和接收线程，其中发送线程接收序列化命令，并通过 GPIO
接收线程将从 GPIO 读取数据，并将其传递到接收窗口。
接收窗口。先不要通过 GPIO 传输数据。现在，只需通过
使用队列传递序列化命令。您可能需要实现一个线程安全的
队列模板类来实现。


## 3.4 使用布尔实现通信协议 - 8 分

在实际使用物理 GPIO 接口之前，通过拨动共享的布尔类来实现并测试您的位流
在实际使用物理 GPIO 接口之前，通过切换共享布尔变量而不是写入 GPIO 引脚来实现并测试您的位流通信协议。
请记住，您需要考虑如何在比特准备读取时发出信号，以及在远程 Pi 读取时发出信号。
位已被远程 Pi 读取。
提示：您可以在每个方向上使用 3 根跳线（即 3 根跳线连接 Pi 的输出端，6 根跳线连接自己的输入端）来实现这一目的。
或 6 根跳线将两台 Pi 连接在一起）。您可能需要使用互斥来避免竞争条件。
条件。


## 3.5 读写物理 GPIO 引脚 - 7 分

更改发送/接收线程，使用 wiringPi 库实际写入 GPIO 引脚。
首先，将您的 Pi 连接到环回（即将发送引脚连接到同一台 Pi 上的接收引脚）。
Pi）。理想情况下，这需要通过电阻来保护 Pi，以防两个引脚意外连接在一起，而这两个引脚都处于输出模式。
如果不小心将两个都处于输出模式的引脚连接在一起，Pi 就会受到保护。请注意，您需要打开一个终端，使用 "sudo "运行您的应用程序。
使用 "sudo "运行应用程序，允许其使用 GPIO 引脚。一旦这样做
将白板应用程序放到邻居的 Raspberry Pi 上（使用 U 盘
或保存在 SD 卡上），然后将两台 Pi 连接在一起。您需要将
GPIO 地线连接在一起，但注意不要将 5V 或 3.3V 引脚相互连接。测试
当连接到另一台 Pi 时，您的应用程序是否能正常工作。

# 项目信息

# 模块

## 模块列表

1. GUI
   1. 主面板 - `mainwindow`
   2. 发送面板 - `Canvas`
   3. 接收面板 - `ReceiveCanvas`
   4. 颜色类 - `colors`
2. 发送接收线程
   1. 发送线程 - `SendThread`
   2. 接收线程 - `ReceivedThread`
3. 安全队列 - `SafeQueue`
4. 画图命令 - `DrawingCommand`

## 主面板 - `mainwindow`

## 发送面板 - `Canvas`

### 成员变量 & 函数

```cpp
public:
    Canvas(QWidget *parent = nullptr,int id=0);

    DrawingCommandType penType;
    DrawingCommand *currentCommand;

    void setPenColor(QColor color);

    QColor getPenColor();

    void setPenWidth(int width);

    int getPenWidth();


protected:
    void mousePressEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QImage img;
    QImage tempImg;
    QImage lastImg;
    QPoint lastPoint;
    QColor penColor;
    int penWidth;
    int deviceID;
```



### 信号 & 槽

```cpp
signals:
	// 每次完成一个命令就会发送这个命令，让发送线程发送这个命令。
    void commandFinished(DrawingCommand *command);

public slots:
	// 接收来自 mainwindow 的菜单清除信号
    void clear();
```



## 接收面板 - `ReceiveCanvas`

## 颜色类 - `colors`

- `enum Color`
- `extern std::map<QCoaslor,std::string,ColorComparator> colorNames`
  - 存储 `<QT颜色,颜色对应文字>` 的字典

## 发送线程 - `SendThread`

## 接收线程 - `ReceivedThread`


## 安全队列 - `SafeQueue`

## 画图命令 - `DrawingCommand`