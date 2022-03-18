#include "Tools.h"

std::string CharacterLibrary::font_;
GLuint CharacterLibrary::size_;
std::vector<Character> CharacterLibrary::library_;

void CharacterLibrary::Init(const std::string& font, GLuint size)
{
	font_ = font;
	size_ = size;
	Load();
}

void CharacterLibrary::Terminate()
{
	// 释放所有资源
	for (auto ch = library_.begin(); ch != library_.end(); ch++)
	{
		glDeleteTextures(1, &ch->textureID_);
	}
}

void CharacterLibrary::Load()
{
	// 加载FreeType库
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	// 加载面
	FT_Face face;
	if (FT_New_Face(ft, font_.c_str(), 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	// 设置字体大小
	FT_Set_Pixel_Sizes(face, 0, size_);
	// 对齐
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte ch = 0; ch < 128; ch++)
	{
		// 加载字形
		if (FT_Load_Char(face, ch, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYPE: Failed to load glyph" << std::endl;
			continue;
		}
		// 生成纹理和字形结构体
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// 设置纹理参数
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glGenerateMipmap(GL_TEXTURE_2D);
		// 插入字形结构体集合中
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		library_.push_back(character);
	}
	// 释放FreeType的资源
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

int ColorMap::s_ = 0;
float* ColorMap::p_ = NULL;
float* ColorMap::kr_ = NULL;
float* ColorMap::cr_ = NULL;
float* ColorMap::kg_ = NULL;
float* ColorMap::cg_ = NULL;
float* ColorMap::kb_ = NULL;
float* ColorMap::cb_ = NULL;

void ColorMap::Init(int s, float* p, unsigned int* c)
{
	s_ = s;
	p_ = new float[s];
	kr_ = new float[s - 1];
	cr_ = new float[s - 1];
	kg_ = new float[s - 1];
	cg_ = new float[s - 1];
	kb_ = new float[s - 1];
	cb_ = new float[s - 1];

	for (int i = 0; i < s; i++)
		p_[i] = p[i];

	for (int i = 0; i < s - 1; i++)
	{
		kr_[i] = (Red(c[i + 1]) - Red(c[i])) / (p[i + 1] - p[i]);
		cr_[i] = -p[i] * kr_[i] + Red(c[i]);

		kg_[i] = (Green(c[i + 1]) - Green(c[i])) / (p[i + 1] - p[i]);
		cg_[i] = -p[i] * kg_[i] + Green(c[i]);

		kb_[i] = (Blue(c[i + 1]) - Blue(c[i])) / (p[i + 1] - p[i]);
		cb_[i] = -p[i] * kb_[i] + Blue(c[i]);
	}
}

void ColorMap::Terminate()
{
	delete[] p_;
	delete[] kr_;
	delete[] cr_;
	delete[] kg_;
	delete[] cg_;
	delete[] kb_;
	delete[] cb_;
}

glm::vec3 ColorMap::Invoke(float x)
{
	int i;
	for (i = 0; i < s_; i++)
		if (x < p_[i])
			break;
	if (i == 0)
	{
		x = 0.0f;
		i = 1;
	}
	else if (i == s_)
	{
		i = s_ - 1;
		x = 1.0f;
	}
	return glm::vec3(
		kr_[i - 1] * x + cr_[i - 1],
		kg_[i - 1] * x + cg_[i - 1],
		kb_[i - 1] * x + cb_[i - 1]
	);
}

float ColorMap::Red(unsigned int color)
{
	return static_cast<float>((color & 0xFF0000) >> 16) / 255.0f;
}

float ColorMap::Green(unsigned int color)
{
	return static_cast<float>((color & 0xFF00) >> 8) / 255.0f;
}

float ColorMap::Blue(unsigned int color)
{
	return static_cast<float>(color & 0xFF) / 255.0f;
}