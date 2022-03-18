#pragma once

#include <glm/glm.hpp>


// 这里定义了所有的常数
// 顶点数据文件
#define VertexFile "assets/data/vertices.csv"
// 边数据文件
#define EdgeFile "assets/data/edges.csv"
// 字体文件
#define FontFile "assets/fonts/calibri.ttf"

// 路况更新时间间隔
constexpr float SimulateDelta = 2.0f;

// 颜色转换函数
// 如果把RGB转成16进制颜色表示值，比如RGB2HEX(255, 255, 255) = 0xffffff;
constexpr unsigned int RGB2HEX(unsigned int red, unsigned int green, unsigned int blue)
{
	return (red << 16) | (green << 8) | (blue);
}

constexpr float GetRed(unsigned int color)
{
	return static_cast<float>((color & 0xFF0000) >> 16) / 255.0f;
}

constexpr float GetGreen(unsigned int color)
{
	return static_cast<float>((color & 0xFF00) >> 8) / 255.0f;
}

constexpr float GetBlue(unsigned int color)
{
	return static_cast<float>(color & 0xFF) / 255.0f;
}

constexpr glm::vec3 ColorNormalize(unsigned int color)
{
	return glm::vec3(GetRed(color), GetGreen(color), GetBlue(color));
}

#define ColorTheme 1
#if ColorTheme == 1
// 第一份颜色方案

// 背景颜色
constexpr unsigned int BackgroundColor = 0x00334c;
// 默认顶点颜色
constexpr unsigned int VertexDefaultColor = 0x66cc66;
// 顶点被点击后的颜色
constexpr unsigned int VertexClickedColor = 0xff6666;
// 最近100个顶点函数中的中心顶点的颜色
constexpr unsigned int VertexCenterColor = 0x3333ff;
// 最短路径中，开始顶点的颜色
constexpr unsigned int VertexStartColor = 0x19e5ff;
// 最短路径中，结束顶点的颜色
constexpr unsigned int VertexEndColor = 0xffe519;
// 路径中一般顶点的颜色
constexpr unsigned int VertexInPathColor = 0xff3333;

// 默认边的颜色
constexpr unsigned int EdgeDefaultColor = 0x6666cc;
// 路径上的边的颜色
constexpr unsigned int EdgeInPathColor = 0xff3f0f;
// 处于拥堵状态下的道路的颜色
constexpr unsigned int EdgeJamColor = 0xff00ff;

// 文本颜色
constexpr unsigned int TextColor = 0xffffff;
// 默认按钮的颜色
constexpr unsigned int ButtonDefaultColor = 0x664ce5;
// 按钮使能的颜色
constexpr unsigned int ButtonHighLight = 0xff9966;
// 按钮上的文本的颜色
constexpr unsigned int ButtonTextColor = 0x99e54c;
// 面板的颜色
constexpr unsigned int PanelColor = 0x007f7f;

#elif ColorTheme == 2
// 第二份颜色方案

// 背景颜色
constexpr unsigned int BackgroundColor = 0xf4f4f4;
// 默认顶点颜色
constexpr unsigned int VertexDefaultColor = 0xaeb5c7;
// 顶点被点击后的颜色
constexpr unsigned int VertexClickedColor = 0xFF0000;
// 最近100个顶点函数中的中心顶点的颜色
constexpr unsigned int VertexCenterColor = 0x228B22;
// 最短路径中，开始顶点的颜色
constexpr unsigned int VertexStartColor = 0x00FF7F;
// 最短路径中，结束顶点的颜色
constexpr unsigned int VertexEndColor = 0x008B45;
// 路径中一般顶点的颜色
constexpr unsigned int VertexInPathColor = 0x1E90FF;

// 默认边的颜色
constexpr unsigned int EdgeDefaultColor = 0x1C1C1C;
// 路径上的边的颜色
constexpr unsigned int EdgeInPathColor = 0x00ff00;
// 处于拥堵状态下的道路的颜色
constexpr unsigned int EdgeJamColor = 0xFF0000;
// 边的颜色会根据道路的拥堵情况来变色，这部分代码在Tool.h，Tool.cpp里实现，在Program.cpp里调用

// 文本颜色
constexpr unsigned int TextColor = 0x4F4F4F;
// 默认按钮的颜色
constexpr unsigned int ButtonDefaultColor = 0x000000;
// 按钮使能的颜色
constexpr unsigned int ButtonHighLight = 0x668B8B;
// 按钮上的文本的颜色
constexpr unsigned int ButtonTextColor = 0xFFFFFF;
// 面板的颜色
constexpr unsigned int PanelColor = 0xDCDCDC;

#endif