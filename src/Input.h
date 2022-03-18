#pragma once

#include <glm/glm.hpp>
#include <bitset>

// 存在BUG：当一帧需要多次捕捉键鼠按下和松开信号时，只有第一个捕捉才能成功

// 键鼠输入系统
class Input
{
public:
    // 重置所有的输入信号
    static void Reset();

    // 键盘正在被按住
    static bool GetKey(int key);
    // 键盘被按下
    static bool GetKeyDown(int key);
    // 键盘被松开
    static bool GetKeyUp(int key);

    // 鼠标正在被按住
    static bool GetMouseButton(int button);
    // 鼠标被按下
    static bool GetMouseButtonDown(int button);
    // 鼠标被松开
    static bool GetMouseButtonUp(int button);

    static glm::vec2 GetMousePos();
    static glm::vec2 GetMouseMovement();
    static float GetMouseScroll();

    static std::bitset<1024> keys_;
    static std::bitset<1024> processed_keys_;
    static std::bitset<1024> free_keys_;
    static std::bitset<16> buttons_;
    static std::bitset<16> processed_buttons_;
    static std::bitset<16> free_buttons_;
    static float mouse_pos_x_; 
    static float mouse_pos_y_;
    static float mouse_last_pos_x_; 
    static float mouse_last_pos_y_;
    static float scroll_offset_y_; 
};

