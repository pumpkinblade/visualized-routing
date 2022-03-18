#pragma once

#include <glm/glm.hpp>


// ���ﶨ�������еĳ���
// ���������ļ�
#define VertexFile "assets/data/vertices.csv"
// �������ļ�
#define EdgeFile "assets/data/edges.csv"
// �����ļ�
#define FontFile "assets/fonts/calibri.ttf"

// ·������ʱ����
constexpr float SimulateDelta = 2.0f;

// ��ɫת������
// �����RGBת��16������ɫ��ʾֵ������RGB2HEX(255, 255, 255) = 0xffffff;
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
// ��һ����ɫ����

// ������ɫ
constexpr unsigned int BackgroundColor = 0x00334c;
// Ĭ�϶�����ɫ
constexpr unsigned int VertexDefaultColor = 0x66cc66;
// ���㱻��������ɫ
constexpr unsigned int VertexClickedColor = 0xff6666;
// ���100�����㺯���е����Ķ������ɫ
constexpr unsigned int VertexCenterColor = 0x3333ff;
// ���·���У���ʼ�������ɫ
constexpr unsigned int VertexStartColor = 0x19e5ff;
// ���·���У������������ɫ
constexpr unsigned int VertexEndColor = 0xffe519;
// ·����һ�㶥�����ɫ
constexpr unsigned int VertexInPathColor = 0xff3333;

// Ĭ�ϱߵ���ɫ
constexpr unsigned int EdgeDefaultColor = 0x6666cc;
// ·���ϵıߵ���ɫ
constexpr unsigned int EdgeInPathColor = 0xff3f0f;
// ����ӵ��״̬�µĵ�·����ɫ
constexpr unsigned int EdgeJamColor = 0xff00ff;

// �ı���ɫ
constexpr unsigned int TextColor = 0xffffff;
// Ĭ�ϰ�ť����ɫ
constexpr unsigned int ButtonDefaultColor = 0x664ce5;
// ��ťʹ�ܵ���ɫ
constexpr unsigned int ButtonHighLight = 0xff9966;
// ��ť�ϵ��ı�����ɫ
constexpr unsigned int ButtonTextColor = 0x99e54c;
// ������ɫ
constexpr unsigned int PanelColor = 0x007f7f;

#elif ColorTheme == 2
// �ڶ�����ɫ����

// ������ɫ
constexpr unsigned int BackgroundColor = 0xf4f4f4;
// Ĭ�϶�����ɫ
constexpr unsigned int VertexDefaultColor = 0xaeb5c7;
// ���㱻��������ɫ
constexpr unsigned int VertexClickedColor = 0xFF0000;
// ���100�����㺯���е����Ķ������ɫ
constexpr unsigned int VertexCenterColor = 0x228B22;
// ���·���У���ʼ�������ɫ
constexpr unsigned int VertexStartColor = 0x00FF7F;
// ���·���У������������ɫ
constexpr unsigned int VertexEndColor = 0x008B45;
// ·����һ�㶥�����ɫ
constexpr unsigned int VertexInPathColor = 0x1E90FF;

// Ĭ�ϱߵ���ɫ
constexpr unsigned int EdgeDefaultColor = 0x1C1C1C;
// ·���ϵıߵ���ɫ
constexpr unsigned int EdgeInPathColor = 0x00ff00;
// ����ӵ��״̬�µĵ�·����ɫ
constexpr unsigned int EdgeJamColor = 0xFF0000;
// �ߵ���ɫ����ݵ�·��ӵ���������ɫ���ⲿ�ִ�����Tool.h��Tool.cpp��ʵ�֣���Program.cpp�����

// �ı���ɫ
constexpr unsigned int TextColor = 0x4F4F4F;
// Ĭ�ϰ�ť����ɫ
constexpr unsigned int ButtonDefaultColor = 0x000000;
// ��ťʹ�ܵ���ɫ
constexpr unsigned int ButtonHighLight = 0x668B8B;
// ��ť�ϵ��ı�����ɫ
constexpr unsigned int ButtonTextColor = 0xFFFFFF;
// ������ɫ
constexpr unsigned int PanelColor = 0xDCDCDC;

#endif