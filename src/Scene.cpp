#include "Scene.h"

Scene::Scene(GLuint screenWidth, GLuint screenHeight)
	:camera_(0.0f, 100.0f, 0.0f, 100.0f), screenWidth_(screenWidth), screenHeight_(screenHeight)
{
	// 多重采样帧缓冲的初始化
	glGenFramebuffers(1, &msfbo_);
	glBindFramebuffer(GL_FRAMEBUFFER, msfbo_);
	glGenRenderbuffers(1, &msrbo_);
	glBindRenderbuffer(GL_RENDERBUFFER, msrbo_);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGBA, screenWidth, screenHeight); // 颜色缓冲
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, msrbo_);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::MMAPSCENE: Failed to initialize MSFBO" << std::endl;
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// 中间帧缓冲的初始化
	glGenFramebuffers(1, &fbo_);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
	glGenTextures(1, &tex_);
	glBindTexture(GL_TEXTURE_2D, tex_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::MMAPSCENE: Failed to initialize FBO" << std::endl;
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Scene::~Scene()
{
	glDeleteFramebuffers(1, &msfbo_);
	glDeleteFramebuffers(1, &fbo_);
	glDeleteRenderbuffers(1, &msrbo_);
	glDeleteTextures(1, &tex_);
}

void Scene::BeginDraw(float r, float g, float b, float a)
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->msfbo_);
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Scene::EndDraw()
{
	// 现在将MSFBO传送到FBO
	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->msfbo_);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->fbo_);
	glBlitFramebuffer(0, 0, screenWidth_, screenHeight_, 0, 0, screenWidth_, screenHeight_, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // 绑定回默认帧缓冲
}

GLuint Scene::GetRenderResult()
{
	return tex_;
}
