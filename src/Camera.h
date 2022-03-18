#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// ���������
class Camera
{
public:
	Camera(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top);
	// ����Ļ����任����������
	glm::vec2 Clip2WorldVector(glm::vec2 clip);
	glm::vec2 Clip2WorldPoint(glm::vec2 clip);

	// ����ͶӰ����
	void SetProjAttribs(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top);

	// �۽���һ����
	void FoucsOn(glm::vec2 point);
	// ����
	void Scale(float ratio);
	// �ƶ�
	void Translate(glm::vec2 vector);
	// 
	const glm::mat4& GetProjection() const;
private:
	// ͶӰ����Ĳ���
	GLfloat proj_left_;
	GLfloat proj_right_;
	GLfloat proj_bottom_;
	GLfloat proj_top_;

	// ͶӰ����
	glm::mat4 proj_mat_;
	glm::mat4 inv_proj_mat_;
};

