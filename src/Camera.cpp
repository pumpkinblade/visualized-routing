#include "Camera.h"

Camera::Camera(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top)
{
	SetProjAttribs(left, right, bottom, top);
}

void Camera::SetProjAttribs(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top)
{
	proj_left_ = left;
	proj_right_ = right;
	proj_bottom_ = bottom;
	proj_top_ = top;

	proj_mat_ = glm::ortho(left, right, bottom, top);
	inv_proj_mat_ = glm::inverse(proj_mat_);
}

glm::vec2 Camera::Clip2WorldVector(glm::vec2 clip)
{
	glm::vec4 vec = inv_proj_mat_ * glm::vec4(clip, 0.0f, 0.0f);
	return glm::vec2(vec.x, vec.y);
}

glm::vec2 Camera::Clip2WorldPoint(glm::vec2 clip)
{
	glm::vec4 vec = inv_proj_mat_ * glm::vec4(clip, 0.0f, 1.0f);
	return glm::vec2(vec.x, vec.y);
}

void Camera::FoucsOn(glm::vec2 point)
{
	float x = point.x;
	float y = point.y;

	SetProjAttribs(
		x - 0.5f * (proj_right_ - proj_left_), x + 0.5f * (proj_right_ - proj_left_),
		y - 0.5f * (proj_top_ - proj_bottom_), y + 0.5f * (proj_top_ - proj_bottom_)
	);
}

void Camera::Scale(float ratio)
{
	SetProjAttribs(
		0.5f * (1.0f + ratio) * proj_left_ + 0.5f * (1.0f - ratio) * proj_right_,
		0.5f * (1.0f + ratio) * proj_right_ + 0.5f * (1.0f - ratio) * proj_left_,
		0.5f * (1.0f + ratio) * proj_bottom_ + 0.5f * (1.0f - ratio) * proj_top_,
		0.5f * (1.0f + ratio) * proj_top_ + 0.5f * (1.0f - ratio) * proj_bottom_
	);
}

void Camera::Translate(glm::vec2 vector)
{
	float x = vector.x;
	float y = vector.y;

	SetProjAttribs(
		proj_left_ + x, proj_right_ + x,
		proj_bottom_ + y, proj_top_ + y
	);
}

const glm::mat4& Camera::GetProjection() const
{
	return proj_mat_;
}

