#pragma once

#include "Input.h"
#include "Map.h"
#include "Renderers.h"
#include "UI.h"

/*
 * Controller��
 * ������غͳ�ʼ����Դ����Ⱦ����Ļ
*/

class Controller
{
public:
    Controller(GLuint screenWidth, GLuint screenHeight);
    ~Controller();

    // ��ʼ��
    void Start();
    // ÿ֡����һ��Update����
    void Update();

    // ����
    Map map_;
    UI ui_;

    // ��Ļ��Ⱥ͸߶�
    const GLuint screenWidth_;
    const GLuint screenHeight_;
};
