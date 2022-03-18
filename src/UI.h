#pragma once

#include <glm/glm.hpp>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Renderers.h"
#include "Map.h"
#include "LinkGraph.h"
#include "UIComponents.h"
#include "Time.h"
#include "Constants.h"

#include <string>
#include <sstream>

// ������UI����ʾĳ������Ĳ�����Ϣ
class VertexInfo : public UIComponent
{
public:
	// ��������������Զ�λ����Ӧ�Ķ���
	class LocateButton : public Button
	{
	public:
		LocateButton(
			glm::vec2 position = glm::vec2(0.0f),
			glm::vec2 scale = glm::vec2(1.0f),
			glm::vec3 color = ColorNormalize(ButtonDefaultColor),
			const std::string& text = "L",
			glm::vec3 text_color = ColorNormalize(ButtonTextColor),
			VertexInfo* parent = NULL
		);
		virtual void OnMouseClick() override;
		VertexInfo* parent_;
	};
	// ����������������޸ĵ�ǰ�Ķ���
	class ModifyButton : public Button
	{
	public:
		ModifyButton(
			glm::vec2 position = glm::vec2(0.0f),
			glm::vec2 scale = glm::vec2(1.0f),
			glm::vec3 color = ColorNormalize(ButtonDefaultColor),
			const std::string& text = "M",
			glm::vec3 text_color = ColorNormalize(ButtonTextColor),
			VertexInfo* parent = NULL
		);
		virtual void OnMouseClick() override;
		VertexInfo* parent_;
	};
public:
	VertexInfo(const std::string& tag, const glm::vec2& position, UIComponent* parent = NULL);

	void Update();

	// ��ǰ��ʾ������Ϣ��ID
	int id_;
	// ModifyButton���¿��Թر�/�������������������ڼ���״̬���ڵ�ͼ�е��һ�����㽫���������㸳��id_
	bool id_can_change_;
	// ��ͼ
	Map* map_;

	Text text_tag_;
	Text text_id_;
	LocateButton button_locate_;
	ModifyButton button_modify_;
};

// һ����ʾ��Ϣ�����
class DetailsPanel : public UIComponent
{
public:
	class AroundPointButton : public Button
	{
	public:
		AroundPointButton(
			glm::vec2 position = glm::vec2(0.0f),
			glm::vec2 scale = glm::vec2(1.0f),
			glm::vec3 color = ColorNormalize(ButtonDefaultColor),
			const std::string& text = "A",
			glm::vec3 text_color = ColorNormalize(ButtonTextColor),
			DetailsPanel* parent = NULL
		);
		virtual void OnMouseClick() override;
		DetailsPanel* parent_;
	};
	class ShortestPathButton : public Button
	{
	public:
		ShortestPathButton(
			glm::vec2 position = glm::vec2(0.0f),
			glm::vec2 scale = glm::vec2(1.0f),
			glm::vec3 color = ColorNormalize(ButtonDefaultColor),
			const std::string& text = "S",
			glm::vec3 text_color = ColorNormalize(ButtonTextColor),
			DetailsPanel* parent = NULL
		);
		virtual void OnMouseClick() override;
		DetailsPanel* parent_;
	};
	class SimulateButton : public Button
	{
	public:
		SimulateButton(
			glm::vec2 position = glm::vec2(0.0f),
			glm::vec2 scale = glm::vec2(1.0f),
			glm::vec3 color = ColorNormalize(ButtonDefaultColor),
			const std::string& text = "S",
			glm::vec3 text_color = ColorNormalize(ButtonTextColor),
			DetailsPanel* parent = NULL
		);
		virtual void OnMouseClick() override;
		DetailsPanel* parent_;
	};
	class PauseButton : public Button
	{
	public:
		PauseButton(
			glm::vec2 position = glm::vec2(0.0f),
			glm::vec2 scale = glm::vec2(1.0f),
			glm::vec3 color = ColorNormalize(ButtonDefaultColor),
			const std::string& text = "S",
			glm::vec3 text_color = ColorNormalize(ButtonTextColor),
			DetailsPanel* parent = NULL
		);
		virtual void OnMouseClick() override;
		DetailsPanel* parent_;
	};
public:
	DetailsPanel();

	void SetMap(Map* map);
	virtual void Draw() override;
	void Update();

	glm::vec3 color_;

	Text distance_text_;
	Text distance_value_;

	Text selected_text_;
	Text selected_id_;

	VertexInfo info_start_;
	VertexInfo info_end_;
	VertexInfo info_center_;

	AroundPointButton around_point_btn_;
	ShortestPathButton shortest_path_btn_;
	SimulateButton simulate_btn_;
	PauseButton pause_btn_;

	Map* map_;
};

// UI����
class UI : public Scene
{
public:
	UI(GLuint screenWidth = 1000, GLuint screenHeight = 800);
	~UI();

	void Start();
	void ProcessInput();
	void Update();
	void Draw();
	void ProcessMouseClick(glm::vec2 pos);

	Map* map_;
	// UI���
	DetailsPanel panel_;
	// �ڽ������½���ʾ��ǰ����λ�ã��������꣩
	Text coords_;
	// �����Ͻ���ʾ֡��
	Text fps_;
	float timer_;

	bool draging_panel_;
	bool control_enabled_;

	std::vector<Button*> buttons_;
};
