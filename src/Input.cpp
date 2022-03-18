#include "Input.h"

std::bitset<1024> Input::keys_;
std::bitset<1024> Input::processed_keys_;
std::bitset<1024> Input::free_keys_;
std::bitset<16> Input::buttons_;
std::bitset<16> Input::processed_buttons_;
std::bitset<16> Input::free_buttons_;
float Input::mouse_pos_x_ = 0.0f;
float Input::mouse_pos_y_ = 0.0f;
float Input::mouse_last_pos_y_ = 0.0f;
float Input::mouse_last_pos_x_ = 0.0f;
float Input::scroll_offset_y_ = 0.0f;

void Input::Reset()
{
	free_keys_ = keys_;
	keys_.reset();
	processed_keys_.reset();
	free_buttons_ = buttons_;
	buttons_.reset();
	processed_keys_.reset();
	mouse_pos_x_ = 0.0f;
	mouse_pos_y_ = 0.0f;
	mouse_last_pos_y_ = 0.0f;
	mouse_last_pos_x_ = 0.0f;
	scroll_offset_y_ = 0.0f;
}


bool Input::GetKeyDown(int key)
{
	bool res = keys_[key] && !processed_keys_[key];
	if(res)
		processed_keys_[key] = true;
	return res;
}

bool Input::GetKeyUp(int key)
{
	bool res = !keys_[key] && free_keys_[key];
	if (res)
		free_keys_[key] = false;
	return res;
}

bool Input::GetKey(int key)
{
	return keys_[key];
}

bool Input::GetMouseButton(int button)
{
	return buttons_[button];
}

bool Input::GetMouseButtonDown(int button)
{
	bool res = buttons_[button] && !processed_buttons_[button];
	if(res)
		processed_buttons_[button] = true;
	return res;
}

bool Input::GetMouseButtonUp(int button)
{
	bool res = !buttons_[button] && free_buttons_[button];
	if (res)
		free_buttons_[button] = false;
	return res;
}


glm::vec2 Input::GetMousePos()
{
	return glm::vec2(mouse_pos_x_, mouse_pos_y_);
}

glm::vec2 Input::GetMouseMovement()
{
	return glm::vec2(mouse_pos_x_ - mouse_last_pos_x_, mouse_pos_y_ - mouse_last_pos_y_);
}

float Input::GetMouseScroll()
{
	float res = scroll_offset_y_;
	scroll_offset_y_ = 0.0f;
	return res;
}
