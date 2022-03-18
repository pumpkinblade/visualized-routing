#include "Controller.h"

Controller::Controller(GLuint screenWidth, GLuint screenHeight)
	:screenWidth_(screenWidth), screenHeight_(screenHeight),
	map_(screenWidth, screenHeight), ui_(screenWidth, screenHeight)
{
	map_.control_enabled_ = true;
	ui_.control_enabled_ = false;
}

Controller::~Controller()
{
}

void Controller::Start()
{
	// º”‘ÿµÿÕº≥°æ∞
	map_.LoadFromFile(VertexFile, EdgeFile);

	ui_.map_ = &map_;

	ui_.Start();
}

void Controller::Update()
{
	if (Input::GetKeyDown(GLFW_KEY_TAB))
	{
		map_.control_enabled_ = !map_.control_enabled_;
		ui_.control_enabled_ = !ui_.control_enabled_;
	}

	map_.Update();
	ui_.Update();

	// ‰÷»æµΩ∆¡ƒª
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	SpriteRenderer::SetProjectionMatrix(glm::mat4(1.0f));
	SpriteRenderer::Draw(map_.GetRenderResult(), glm::vec2(0.0f), glm::vec2(1.0f));
	SpriteRenderer::Draw(ui_.GetRenderResult(), glm::vec2(0.0f), glm::vec2(1.0f));
}

