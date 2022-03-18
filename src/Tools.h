#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include <iostream>
#include <vector>

// 字形信息
struct Character
{
    GLuint textureID_;    // 纹理ID
    glm::ivec2 size_;     // 字形的大小（宽和高）(单位：像素)
    glm::ivec2 bearing_;  // 从基准线到字形的左/上距离（单位：像素）
    GLuint advance_;      // 原点到下一原点的距离(字符的间距)（单位：1/64像素）
};

// 字形库
class CharacterLibrary
{
public:
    static void Init(const std::string& font, GLuint size);
    static void Terminate();

    static void Load();

    static std::string font_;
    static GLuint size_;
    static std::vector<Character> library_;
private:
    CharacterLibrary() = delete;
};

// 使用线性插值制作colormap
class ColorMap
{
public:
    // s是用来插值的点的个数
    // 通过一列点(p[i], c[i])为各分量插值
    // p[i]的取值范围是0.0f - 1.0f, c[i]是16进制颜色值如0x00ffff
    static void Init(int s, float* p, unsigned int* c);
    static void Terminate();
    static glm::vec3 Invoke(float x);
private:
    ColorMap() = delete;
    static float Red(unsigned int c);
    static float Green(unsigned int c);
    static float Blue(unsigned int c);

    // s表示用来插值的点的个数
    static int s_;
    // p表示上述点的x坐标
    static float* p_;
    // 线性插值计算出来的直线的斜率和常数
    static float* kr_;
    static float* cr_;
    static float* kg_;
    static float* cg_;
    static float* kb_;
    static float* cb_;
};