#pragma once

#include <glm/glm.hpp>
#include <bitset>

// ����BUG����һ֡��Ҫ��β�׽�����º��ɿ��ź�ʱ��ֻ�е�һ����׽���ܳɹ�

// ��������ϵͳ
class Input
{
public:
    // �������е������ź�
    static void Reset();

    // �������ڱ���ס
    static bool GetKey(int key);
    // ���̱�����
    static bool GetKeyDown(int key);
    // ���̱��ɿ�
    static bool GetKeyUp(int key);

    // ������ڱ���ס
    static bool GetMouseButton(int button);
    // ��걻����
    static bool GetMouseButtonDown(int button);
    // ��걻�ɿ�
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

