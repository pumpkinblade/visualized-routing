#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <string>
#include <sstream>
#include <list>

#include "Renderers.h"
#include "Constants.h"

// UI����Ļ���
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

	// ����
	virtual void Draw();

};

// �ı���
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

	// ���ö��뷽ʽ
	void SetPivot(TextRenderer::Pivot pivot);
	// ��������
	void SetText(const std::string& text);
	// ��Ⱦ����
	virtual void Draw() override;
	virtual void SetPosition(glm::vec2 position) override;

	// ��ɫ
	glm::vec3 color_;
	// �ı�
	std::string text_;
	// ���뷽ʽ
	TextRenderer::Pivot pivot_;
};

// ��ť��
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

	// ����
	virtual void Draw() override;
	// ��ť��������¼�������
	virtual void OnMouseClick() = 0;

	// ��ť������������ɫ
	glm::vec3 color_;
	// �ı�����
	Text text_;

public:
	static std::vector<Button*> buttonList_;
};
