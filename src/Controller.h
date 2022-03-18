#pragma once

#include "Input.h"
#include "Map.h"
#include "Renderers.h"
#include "UI.h"

/*
 * Controller类
 * 负责加载和初始化资源，渲染到屏幕
*/

class Controller
{
public:
    Controller(GLuint screenWidth, GLuint screenHeight);
    ~Controller();

    // 初始化
    void Start();
    // 每帧调用一次Update函数
    void Update();

    // 场景
    Map map_;
    UI ui_;

    // 屏幕宽度和高度
    const GLuint screenWidth_;
    const GLuint screenHeight_;
};
