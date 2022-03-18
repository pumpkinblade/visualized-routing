#pragma once
#include "UIComponents.h"


// ===================== UI Element ====================

UIComponent::UIComponent(glm::vec2 position, glm::vec2 scale, UIComponent* parent)
	:position_(position), scale_(scale), world_position_(position), active_(true), parent_(parent), children_()
{
}

void UIComponent::SetPosition(glm::vec2 position)
{
	position_ = position;
	if (parent_ != NULL)
		world_position_ = parent_->world_position_ + position;
	else
		world_position_ = position;
	for (auto it = children_.begin(); it != children_.end(); it++)
		(*it)->SetPosition((*it)->position_);
}

void UIComponent::Draw()
{
	for (auto it = children_.begin(); it != children_.end(); it++)
		if ((*it)->active_)
			(*it)->Draw();
}

// ======================= Text =============================

Text::Text(glm::vec2 position, const std::string& text, glm::vec3 color, TextRenderer::Pivot pivot, UIComponent* parent)
	:UIComponent(position, glm::vec2(1.0f), parent), text_(text), color_(color), pivot_(pivot)
{
}

void Text::SetPivot(TextRenderer::Pivot pivot)
{
	pivot_ = pivot;
}

void Text::SetText(const std::string& text)
{
	text_ = text;
}

void Text::Draw()
{
	TextRenderer::Draw(text_, world_position_, color_, pivot_);
}

void Text::SetPosition(glm::vec2 position)
{
	position_ = position;
	if (parent_ != NULL)
		world_position_ = parent_->world_position_ + position;
	else
		world_position_ = position;
}

// ======================= Button ============================

std::vector<Button*> Button::buttonList_;

Button::Button(
	glm::vec2 position, glm::vec2 scale, glm::vec3 color,
	const std::string& text, glm::vec3 text_color, UIComponent* parent)
	:UIComponent(position, scale, parent), text_(glm::vec2(0.0f), text, text_color, TextRenderer::Pivot::CENTER_CENTER, this), color_(color)
{
	buttonList_.push_back(this);
	children_.push_back(&text_);
}

void Button::Draw()
{
	QuadRenderer::Draw(world_position_, scale_, color_);
	text_.Draw();
}
