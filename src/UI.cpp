#include "UI.h"

// ========================= Vertex Information =======================

VertexInfo::LocateButton::LocateButton(
	glm::vec2 position, glm::vec2 scale, glm::vec3 color,
	const std::string& text, glm::vec3 text_color,
	VertexInfo* parent)
	:Button(position, scale, color, text, text_color, parent), parent_(parent)
{
}

void VertexInfo::LocateButton::OnMouseClick()
{
	VertexInfo* parent = parent_;
	parent->map_->FoucsOn(parent->id_);
}

VertexInfo::ModifyButton::ModifyButton(
	glm::vec2 position, glm::vec2 scale, glm::vec3 color,
	const std::string& text, glm::vec3 text_color,
	VertexInfo* parent)
	:Button(position, scale, color, text, text_color, parent), parent_(parent)
{
}

void VertexInfo::ModifyButton::OnMouseClick()
{
	VertexInfo* parent = parent_;
	parent->id_can_change_ = !parent->id_can_change_;
	if (parent->id_can_change_)
		color_ = ColorNormalize(ButtonHighLight);
	else
		color_ = ColorNormalize(ButtonDefaultColor);
}

VertexInfo::VertexInfo(const std::string& tag, const glm::vec2& position, UIComponent* parent)
	:UIComponent(position, glm::vec2(0.0f), parent), id_(-1), id_can_change_(false), map_(NULL),
	text_tag_(glm::vec2(-140.0f, 0.0f), tag, ColorNormalize(TextColor), TextRenderer::Pivot::LEFT_CENTER, this),
	text_id_(glm::vec2(60.0f, 0.0f), "-1", ColorNormalize(TextColor), TextRenderer::Pivot::RIGHT_CENTER, this),
	button_modify_(glm::vec2(90.0f, 0.0f), glm::vec2(15.0f), ColorNormalize(ButtonDefaultColor), "M", ColorNormalize(ButtonTextColor), this),
	button_locate_(glm::vec2(130.0f, 0.0f), glm::vec2(15.0f), ColorNormalize(ButtonDefaultColor), "L", ColorNormalize(ButtonTextColor), this)
{
	children_.push_back(&text_tag_);
	children_.push_back(&text_id_);
	children_.push_back(&button_modify_);
	children_.push_back(&button_locate_);
	SetPosition(position);
}

void VertexInfo::Update()
{
	if (id_can_change_ && id_ != map_->clicked_vertex_)
	{
		id_ = map_->clicked_vertex_;
		std::stringstream ss;
		ss << id_;
		text_id_.SetText(ss.str());
	}
}

// ========================== Panel ============================

DetailsPanel::AroundPointButton::AroundPointButton(
	glm::vec2 position, glm::vec2 scale, glm::vec3 color,
	const std::string& text, glm::vec3 text_color, DetailsPanel* parent)
	:Button(position, scale, color, text, text_color, parent), parent_(parent)
{
}

void DetailsPanel::AroundPointButton::OnMouseClick()
{
	parent_->map_->ShowAroundPoint(parent_->info_center_.id_, 100);
}

DetailsPanel::ShortestPathButton::ShortestPathButton(
	glm::vec2 position, glm::vec2 scale, glm::vec3 color,
	const std::string& text, glm::vec3 text_color, DetailsPanel* parent)
	:Button(position, scale, color, text, text_color, parent), parent_(parent)
{
}

void DetailsPanel::ShortestPathButton::OnMouseClick()
{
	parent_->map_->ShowShortestPath(parent_->info_start_.id_, parent_->info_end_.id_);
}

DetailsPanel::SimulateButton::SimulateButton(
	glm::vec2 position, glm::vec2 scale, glm::vec3 color,
	const std::string& text, glm::vec3 text_color, DetailsPanel* parent)
	:Button(position, scale, color, text, text_color, parent), parent_(parent)
{
}

void DetailsPanel::SimulateButton::OnMouseClick()
{
	if (parent_->map_->IsSimulating())
	{
		color_ = ColorNormalize(ButtonDefaultColor);
		parent_->map_->SetSimulate(false);
		parent_->distance_text_.SetText("distance:");
	}
	else
	{
		color_ = ColorNormalize(ButtonHighLight);
		parent_->map_->SetSimulate(true);
		parent_->distance_text_.SetText("time:");
	}
}

DetailsPanel::PauseButton::PauseButton(
	glm::vec2 position, glm::vec2 scale, glm::vec3 color,
	const std::string& text, glm::vec3 text_color, DetailsPanel* parent)
	:Button(position, scale, color, text, text_color, parent), parent_(parent)
{
}

void DetailsPanel::PauseButton::OnMouseClick()
{
	if (parent_->map_->IsPaused())
	{
		color_ = ColorNormalize(ButtonDefaultColor);
		parent_->map_->SetPause(false);
	}
	else
	{
		color_ = ColorNormalize(ButtonHighLight);
		parent_->map_->SetPause(true);
	}
}


DetailsPanel::DetailsPanel()
	:UIComponent(glm::vec2(0.0f), glm::vec2(150.0f, 250.0f)), color_(ColorNormalize(PanelColor)), map_(NULL),
	selected_text_(glm::vec2(-140.0f, -200.0f), "selected", ColorNormalize(TextColor), TextRenderer::Pivot::LEFT_CENTER, this),
	selected_id_(glm::vec2(100.0f, -200.0f), "-1", ColorNormalize(TextColor), TextRenderer::Pivot::RIGHT_CENTER, this),
	info_center_("center:", glm::vec2(0.0f, -100.0f), this),
	around_point_btn_(glm::vec2(110.0f, -50.0f), glm::vec2(30.0f, 15.0f), ColorNormalize(ButtonDefaultColor), "A", ColorNormalize(ButtonTextColor), this),
	info_start_("start:", glm::vec2(0.0f, 0.0f), this), info_end_("end:", glm::vec2(0.0f, 50.0f), this),
	shortest_path_btn_(glm::vec2(110.0f, 100.0f), glm::vec2(30.0f, 15.0f), ColorNormalize(ButtonDefaultColor), "S", ColorNormalize(ButtonTextColor), this),
	distance_text_(glm::vec2(-140.0f, 150.0f), "distance:", ColorNormalize(TextColor), TextRenderer::Pivot::LEFT_CENTER, this),
	distance_value_(glm::vec2(100.0f, 150.0f), "inf", ColorNormalize(TextColor), TextRenderer::Pivot::RIGHT_CENTER, this),
	simulate_btn_(glm::vec2(75.0f, 200.0f), glm::vec2(50.0f, 15.0f), ColorNormalize(ButtonDefaultColor), "Simulate", ColorNormalize(ButtonTextColor), this),
	pause_btn_(glm::vec2(-75.0f, 200.0f), glm::vec2(50.0f, 15.0f), ColorNormalize(ButtonDefaultColor), "Pause", ColorNormalize(ButtonTextColor), this)
{
	children_.push_back(&around_point_btn_);
	children_.push_back(&shortest_path_btn_);
	children_.push_back(&simulate_btn_);
	children_.push_back(&pause_btn_);
	children_.push_back(&info_center_);
	children_.push_back(&info_start_);
	children_.push_back(&info_end_);
	children_.push_back(&selected_id_);
	children_.push_back(&selected_text_);
	children_.push_back(&distance_text_);
	children_.push_back(&distance_value_);
}

void DetailsPanel::Draw()
{
	QuadRenderer::Draw(world_position_, scale_, color_);
	UIComponent::Draw();
}

void DetailsPanel::SetMap(Map* map)
{
	map_ = map;
	info_end_.map_ = map;
	info_start_.map_ = map;
	info_center_.map_ = map_;
}

void DetailsPanel::Update()
{
	info_end_.Update();
	info_start_.Update();
	info_center_.Update();
	selected_id_.SetText(std::to_string(map_->clicked_vertex_));
	distance_value_.SetText(std::to_string(map_->theDistance_));
}

// ============================= UI Controller ==============================

UI::UI(GLuint screenWidth, GLuint screenHeight) : Scene(screenWidth, screenHeight)
{
	timer_ = 0.0f;

	map_ = NULL;
	camera_.SetProjAttribs(0.0f, static_cast<float>(screenWidth_), static_cast<float>(screenHeight_), 0.0f);

	fps_.SetPosition(glm::vec2(5.0f, 5.0f));
	fps_.SetPivot(TextRenderer::Pivot::LEFT_TOP);
	coords_.SetPosition(glm::vec2(static_cast<float>(screenWidth_), static_cast<float>(screenHeight_)));
	coords_.SetPivot(TextRenderer::Pivot::RIGHT_DOWN);
	panel_.SetPosition(glm::vec2(static_cast<float>(screenWidth_) * 0.5f, static_cast<float>(screenHeight_) * 0.5f));
	control_enabled_ = false;
	draging_panel_ = false;
}

UI::~UI()
{
}

void UI::Start()
{
	panel_.SetMap(map_);
}

void UI::ProcessInput()
{
	glm::vec2 mouse_pos = camera_.Clip2WorldPoint(Input::GetMousePos());
	//  Û±ÍÕœ∂Ø√Ê∞Â
	if (draging_panel_)
	{
		glm::vec2 panel_pos = panel_.position_ + camera_.Clip2WorldVector(Input::GetMouseMovement());
		panel_pos.x = glm::clamp(panel_pos.x, 0.0f, static_cast<float>(screenWidth_));
		panel_pos.y = glm::clamp(panel_pos.y, 0.0f, static_cast<float>(screenHeight_));
		panel_.SetPosition(panel_pos);

		if (Input::GetMouseButtonUp(GLFW_MOUSE_BUTTON_LEFT))
		{
			if (draging_panel_)
			{
				draging_panel_ = false;
				ProcessMouseClick(mouse_pos);
			}
		}
	}
	else
	{
		if (glm::abs(mouse_pos.x - panel_.position_.x) < panel_.scale_.x
			&& glm::abs(mouse_pos.y - panel_.position_.y) < panel_.scale_.y)
		{
			if (Input::GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
			{
				draging_panel_ = true;
			}
		}
		else
		{
			map_->ProcessInput();
		}
	}
}

void UI::Update()
{
	if (control_enabled_)
	{
		ProcessInput();
		panel_.Update();
	}

	timer_ += Time::GetDeltaTime();
	if (timer_ > 1.0f)
	{
		timer_ -= 1.0f;
		fps_.SetText(std::to_string(Time::GetFPS()));
	}

	glm::vec2 mouse_pos = map_->camera_.Clip2WorldPoint(Input::GetMousePos());
	std::stringstream ss;
	ss << "x:" << mouse_pos.x << ", y:" << mouse_pos.y;
	coords_.SetText(ss.str());

	Draw();
}

void UI::Draw()
{
	BeginDraw(0.1f, 0.1f, 0.1f, 0.3f * control_enabled_);

	TextRenderer::SetProjectionMatrix(camera_.GetProjection());
	QuadRenderer::SetProjectionMatrix(camera_.GetProjection());

	coords_.Draw();
	fps_.Draw();
	if (control_enabled_)
		panel_.Draw();

	EndDraw();
}

void UI::ProcessMouseClick(glm::vec2 pos)
{
	for (int i = 0; i < Button::buttonList_.size(); i++)
		if (glm::abs(Button::buttonList_[i]->world_position_.x - pos.x) < Button::buttonList_[i]->scale_.x
			&& glm::abs(Button::buttonList_[i]->world_position_.y - pos.y) < Button::buttonList_[i]->scale_.y)
			Button::buttonList_[i]->OnMouseClick();
}
