#include "Renderers.h"

Shader* SpriteRenderer::shader_ = NULL;
Quad* SpriteRenderer::mesh_ = NULL;

void SpriteRenderer::Draw(GLuint tex, const glm::vec2& position, const glm::vec2& size)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader_->Use();
	shader_->SetMat4("model", model);
	shader_->Set1i("texture1", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glBindVertexArray(mesh_->vao_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	shader_->Unuse();
}

void SpriteRenderer::SetProjectionMatrix(const glm::mat4& projection)
{
	shader_->Use();
	shader_->SetMat4("projection", projection);
}

void SpriteRenderer::Init()
{
	shader_ = new Shader("shaders/sprite.vs", "shaders/sprite.fs");
	mesh_ = new Quad;
}

void SpriteRenderer::Terminate()
{
	delete shader_;
	delete mesh_;
}



Shader* TriangleRenderer::shader_ = NULL;
Triangle* TriangleRenderer::defaultTriangle_ = NULL;

void TriangleRenderer::Init()
{
	shader_ = new Shader("shaders/triangle.vs", "shaders/triangle.fs");
	defaultTriangle_ = new Triangle;
}

void TriangleRenderer::Terminate()
{
	delete shader_;
	delete defaultTriangle_;
}

void TriangleRenderer::Draw(const glm::vec2& pos, const glm::vec2& scale, const glm::vec3& color)
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f));
	model = glm::scale(model, glm::vec3(scale, 1.0f));
	shader_->Use();
	shader_->SetVec3("color", color);
	shader_->SetMat4("model", model);
	glBindVertexArray(defaultTriangle_->vao_);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void TriangleRenderer::SetProjectionMatrix(const glm::mat4& projection)
{
	shader_->Use();
	shader_->SetMat4("projection", projection);
}


Shader* LineRenderer::shader_ = NULL;
Line* LineRenderer::defaultLine_ = NULL;

void LineRenderer::Init()
{
	shader_ = new Shader("shaders/line.vs", "shaders/line.fs");
	defaultLine_ = new Line;
}

void LineRenderer::Terminate()
{
	delete shader_;
	delete defaultLine_;
}

void LineRenderer::Draw(const glm::vec4& start_and_end, const glm::vec3& color)
{
	shader_->Use();
	shader_->SetVec3("color", color);
	glBindBuffer(GL_ARRAY_BUFFER, defaultLine_->vbo_);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(GLfloat), glm::value_ptr(start_and_end));
	glBindVertexArray(defaultLine_->vao_);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void LineRenderer::SetProjectionMatrix(const glm::mat4& projection)
{
	shader_->Use();
	shader_->SetMat4("projection", projection);
}



Shader* TextRenderer::shader_ = NULL;
TextMesh* TextRenderer::mesh_ = NULL;

void TextRenderer::Init()
{
	shader_ = new Shader("shaders/text.vs", "shaders/text.fs");
	mesh_ = new TextMesh;
}

void TextRenderer::Terminate()
{
	delete shader_;
	delete mesh_;
}

void TextRenderer::Draw(const std::string& text, const glm::vec2& position, const glm::vec3& color, Pivot pivot)
{
	// 计算渲染开始的位置
	GLuint w = 0;
	for (std::string::const_iterator it = text.begin(); it != text.end(); it++)
		w += (CharacterLibrary::library_[*it].advance_ >> 6);
	GLfloat x;
	GLfloat y;

	switch (pivot)
	{
	case TextRenderer::Pivot::LEFT_TOP:
		x = position.x;
		y = position.y;
		break;
	case TextRenderer::Pivot::LEFT_CENTER:
		y = position.y - 0.6f * CharacterLibrary::library_['H'].size_.y;
		x = position.x;
		break;
	case TextRenderer::Pivot::LEFT_DOWN:
		y = position.y - 1.2f * CharacterLibrary::library_['H'].size_.y;
		x = position.x;
		break;
	case TextRenderer::Pivot::CENTER_TOP:
		y = position.y;
		x = position.x - 0.5f * w;
		break;
	case TextRenderer::Pivot::CENTER_CENTER:
		y = position.y - 0.6f * CharacterLibrary::library_['H'].size_.y;
		x = position.x - 0.5f * w;
		break;
	case TextRenderer::Pivot::CENTER_DOWN:
		y = position.y - 1.2f * CharacterLibrary::library_['H'].size_.y;
		x = position.x - 0.5f * w;
		break;
	case TextRenderer::Pivot::RIGHT_TOP:
		y = position.y;
		x = position.x - w;
		break;
	case TextRenderer::Pivot::RIGHT_CENTER:
		y = position.y - 0.6f * CharacterLibrary::library_['H'].size_.y;
		x = position.x - w;
		break;
	case TextRenderer::Pivot::RIGHT_DOWN:
		y = position.y - 1.2f * CharacterLibrary::library_['H'].size_.y;
		x = position.x - w;
		break;
	default:
		x = position.x;
		y = position.y;
		break;
	}

	// 配置着色器
	shader_->Use();
	shader_->SetVec3("color", color);
	shader_->Set1i("tex", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mesh_->vao_);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_->vbo_);
	// 逐个遍历字符串的字符，并渲染
	for (std::string::const_iterator ch = text.begin(); ch != text.end(); ch++)
	{
		Character character = CharacterLibrary::library_[*ch];

		GLfloat xpos = x + character.bearing_.x;
		GLfloat ypos = y + (CharacterLibrary::library_['H'].bearing_.y - character.bearing_.y);

		GLfloat w = static_cast<GLfloat>(character.size_.x);
		GLfloat h = static_cast<GLfloat>(character.size_.y);
		// 更新VBO
		GLfloat vertices[6][4] = {
			{xpos,     ypos + h, 0.0f, 1.0f},
			{xpos + w, ypos,     1.0f, 0.0f},
			{xpos,     ypos,     0.0f, 0.0f},

			{xpos,     ypos + h, 0.0f, 1.0f},
			{xpos + w, ypos + h, 1.0f, 1.0f},
			{xpos + w, ypos,     1.0f, 0.0f}
		};
		glBufferSubData(GL_ARRAY_BUFFER, NULL, sizeof(vertices), vertices);
		// 绘制
		glBindTexture(GL_TEXTURE_2D, character.textureID_);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// 移动到下一个字形
		x += (character.advance_ >> 6); // 因为Advance的单位是(1/64像素)，因此需要右移6个位
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::SetProjectionMatrix(const glm::mat4& proj_mat)
{
	shader_->Use();
	shader_->SetMat4("projection", proj_mat);
}



Shader* QuadRenderer::shader_ = NULL;
Quad* QuadRenderer::quad_ = NULL;

void QuadRenderer::Init()
{
	shader_ = new Shader("shaders/quad.vs", "shaders/quad.fs");
	quad_ = new Quad;
}

void QuadRenderer::Terminate()
{
	delete shader_;
	delete quad_;
}

void QuadRenderer::Draw(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader_->Use();
	shader_->SetMat4("model", model);
	shader_->SetVec3("color", color);
	glBindVertexArray(quad_->vao_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	shader_->Unuse();
}

void QuadRenderer::SetProjectionMatrix(const glm::mat4& proj_mat)
{
	shader_->Use();
	shader_->SetMat4("projection", proj_mat);
}




Shader* InstancedMeshRenderer::shader_ = NULL;

void InstancedMeshRenderer::Init()
{
	shader_ = new Shader("shaders/instanced.vs", "shaders/instanced.fs");
}

void InstancedMeshRenderer::Terminate()
{
	delete shader_;
}

void InstancedMeshRenderer::DrawInstancedTriangle(const InstancedTriangle& tri)
{
	shader_->Use();
	glBindVertexArray(tri.vao_);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 3, tri.instance_amount_);
	glBindVertexArray(0);
}

void InstancedMeshRenderer::DrawInstancedLine(const InstancedLine& line)
{
	shader_->Use();
	glBindVertexArray(line.vao_);
	glDrawArraysInstanced(GL_LINES, 0, 2, line.instance_amount_);
	glBindVertexArray(0);
}

void InstancedMeshRenderer::SetProjectionMatrix(const glm::mat4& projection)
{
	shader_->Use();
	shader_->SetMat4("projection", projection);
}