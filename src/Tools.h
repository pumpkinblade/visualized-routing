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

// ������Ϣ
struct Character
{
    GLuint textureID_;    // ����ID
    glm::ivec2 size_;     // ���εĴ�С����͸ߣ�(��λ������)
    glm::ivec2 bearing_;  // �ӻ�׼�ߵ����ε���/�Ͼ��루��λ�����أ�
    GLuint advance_;      // ԭ�㵽��һԭ��ľ���(�ַ��ļ��)����λ��1/64���أ�
};

// ���ο�
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

// ʹ�����Բ�ֵ����colormap
class ColorMap
{
public:
    // s��������ֵ�ĵ�ĸ���
    // ͨ��һ�е�(p[i], c[i])Ϊ��������ֵ
    // p[i]��ȡֵ��Χ��0.0f - 1.0f, c[i]��16������ɫֵ��0x00ffff
    static void Init(int s, float* p, unsigned int* c);
    static void Terminate();
    static glm::vec3 Invoke(float x);
private:
    ColorMap() = delete;
    static float Red(unsigned int c);
    static float Green(unsigned int c);
    static float Blue(unsigned int c);

    // s��ʾ������ֵ�ĵ�ĸ���
    static int s_;
    // p��ʾ�������x����
    static float* p_;
    // ���Բ�ֵ���������ֱ�ߵ�б�ʺͳ���
    static float* kr_;
    static float* cr_;
    static float* kg_;
    static float* cg_;
    static float* kb_;
    static float* cb_;
};