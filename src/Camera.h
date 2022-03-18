#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// 正交相机类
class Camera
{
public:
	Camera(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top);
	// 把屏幕坐标变换到世界坐标
	glm::vec2 Clip2WorldVector(glm::vec2 clip);
	glm::vec2 Clip2WorldPoint(glm::vec2 clip);

	// 设置投影矩阵
	void SetProjAttribs(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top);

	// 聚焦在一个点
	void FoucsOn(glm::vec2 point);
	// 缩放
	void Scale(float ratio);
	// 移动
	void Translate(glm::vec2 vector);
	// 
	const glm::mat4& GetProjection() const;
private:
	// 投影矩阵的参数
	GLfloat proj_left_;
	GLfloat proj_right_;
	GLfloat proj_bottom_;
	GLfloat proj_top_;

	// 投影矩阵
	glm::mat4 proj_mat_;
	glm::mat4 inv_proj_mat_;
};

