#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <string>
#include <sstream>
#include <list>

#include "Renderers.h"
#include "Constants.h"

// UI组件的基类
class UIComponent
{
public:
	UIComponent(glm::vec2 position = glm::vec2(0.0f), glm::vec2 scale = glm::vec2(1.0f), UIComponent* parent = NULL);

	glm::vec2 position_;
	glm::vec2 scale_;

	glm::vec2 world_position_;

	bool active_;
	UIComponent* parent_;
	std::list<UIComponent*> children_;
	virtual void SetPosition(glm::vec2 position);

	// 绘制
	virtual void Draw();

};

// 文本类
class Text : public UIComponent
{
public:
	Text(
		glm::vec2 position = glm::vec2(0.0f),
		const std::string& text = "\0",
		glm::vec3 color = ColorNormalize(TextColor),
		TextRenderer::Pivot pivot = TextRenderer::Pivot::LEFT_TOP,
		UIComponent* parent=NULL
	);

	// 设置对齐方式
	void SetPivot(TextRenderer::Pivot pivot);
	// 设置文字
	void SetText(const std::string& text);
	// 渲染文字
	virtual void Draw() override;
	virtual void SetPosition(glm::vec2 position) override;

	// 颜色
	glm::vec3 color_;
	// 文本
	std::string text_;
	// 对齐方式
	TextRenderer::Pivot pivot_;
};

// 按钮类
class Button : public UIComponent
{
public:
	Button(
		glm::vec2 position = glm::vec2(0.0f),
		glm::vec2 scale = glm::vec2(1.0f),
		glm::vec3 color = ColorNormalize(ButtonDefaultColor),
		const std::string& text = "\0",
		glm::vec3 text_color = ColorNormalize(TextColor),
		UIComponent* parent = NULL
	);

	// 绘制
	virtual void Draw() override;
	// 按钮被点击的事件处理函数
	virtual void OnMouseClick() = 0;

	// 按钮（背景）的颜色
	glm::vec3 color_;
	// 文本对象
	Text text_;

public:
	static std::vector<Button*> buttonList_;
};
