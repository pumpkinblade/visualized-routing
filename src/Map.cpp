#include "Map.h"


Map::Map(GLuint screenWidth, GLuint screenHeight)
	:Scene(screenWidth, screenHeight),
	vertex_entities_(NULL), edge_entities_(NULL), clicked_vertex_color(ColorNormalize(VertexClickedColor))
{
	control_enabled_ = false;
	translated_ = false;
	clicked_vertex_ = -1;
	simulating_ = false;
	paused_ = false;
	timer_ = 0;
	showingAroundPoint_ = showingShortestPoint_ = false;
	centerVertex_ = endVertex_ = startVertex_ = -1;
	aroundAmount_ = 0;
	theDistance_ = INFINITY;
}

Map::~Map()
{
	if (edge_entities_ != NULL)
		delete[] edge_entities_;
	if (vertex_entities_ != NULL)
		delete[] vertex_entities_;
}

void Map::Draw()
{
	// 画图前的一些准备工作
	BeginDraw(GetRed(BackgroundColor), GetGreen(BackgroundColor), GetBlue(BackgroundColor), 1.0f);

	InstancedMeshRenderer::SetProjectionMatrix(camera_.GetProjection());
	// 实例化渲染
	// 画边
	InstancedMeshRenderer::DrawInstancedLine(linemesh_);
	// 画点
	InstancedMeshRenderer::DrawInstancedTriangle(trimesh_);

	// 逐个渲染
	//TriangleRenderer::SetProjectionMatrix(camera_.GetProjection());
	//LineRenderer::SetProjectionMatrix(camera_.GetProjection());
	// 画边
	//for (int index = 0; index < num_edges_; index++)
	//	LineRenderer::Draw(glm::vec4(edge_entities_[index].start_, edge_entities_[index].end_), edge_entities_[index].color_);
	// 画点
	//for (int index = 0; index < num_vertices_; index++)
	//	TriangleRenderer::Draw(vertex_entities_[index].position_, vertex_entities_[index].scale_, vertex_entities_[index].color_);

	// 画完后的工作
	EndDraw();
}

void Map::FoucsOn(int id)
{
	if (id < 0 || id >= num_vertices_)
		return;
	glm::vec2 target = vertex_entities_[id].position_;
	camera_.FoucsOn(target);
}

void Map::LoadFromFile(const char* vertex_file, const char* edge_file)
{
	timer_ = 0.0f;
	simulating_ = false;
	showingAroundPoint_ = showingShortestPoint_ = false;
	centerVertex_ = endVertex_ = startVertex_ = -1;
	aroundAmount_ = 0;
	theDistance_ = INFINITY;

	Clear();
	// 加载地图文件
	std::ifstream vfile(vertex_file);
	std::ifstream efile(edge_file);
	if (vfile.bad() || vfile.fail())
	{
		std::cout << "ERROR::can't open file::`" << vertex_file << "`\n";
		return;
	}
	if (efile.bad() || efile.fail())
	{
		std::cout << "ERROR::can't open file::`" << edge_file << "`\n";
		return;
	}

	// 规定顶点数据文件的第一行指定顶点的个数
	if (!(vfile >> num_vertices_ && !vfile.eof()))
	{
		std::cout << "ERROR::file format error" << std::endl;
		return;
	}
	// 加载所有的顶点
	//VertexEntity::SetInstanceNumber(num_vertices_);
	vertices_ = new Vertex[num_vertices_];
	vertex_entities_ = new VertexEntity[num_vertices_];
	// ID应该是程序内部的变量，不要在文件中定义
	int id = 0;
	float x, y;
	char c1, c2;
	vfile >> c1 >> c2;
	while (vfile >> id >> c1 >> x >> c2 >> y && !vfile.eof())
	{
		vertices_[id].id_ = id;
		vertex_entities_[id].position_ = glm::vec2(x, y);
		vertices_[id].entity_ = &vertex_entities_[id];
	}
	// 计算出默认的投影属性
	if (num_vertices_ == 0)
	{
		std::cout << "WARNING::Empty Graph\n";
		return;
	}
	int it = 0;
	float x_m = vertex_entities_[0].position_.x - 10.0f;
	float x_M = vertex_entities_[0].position_.x + 10.0f;
	float y_m = vertex_entities_[0].position_.y - 10.0f;
	float y_M = vertex_entities_[0].position_.y + 10.0f;
	for (it = 1; it < num_vertices_; it++)
	{
		x_m = vertex_entities_[it].position_.x < x_m ? vertex_entities_[it].position_.x : x_m;
		x_M = vertex_entities_[it].position_.x > x_M ? vertex_entities_[it].position_.x : x_M;
		y_m = vertex_entities_[it].position_.y < y_m ? vertex_entities_[it].position_.y : y_m;
		y_M = vertex_entities_[it].position_.y > y_M ? vertex_entities_[it].position_.y : y_M;
	}

	camera_.SetProjAttribs(x_m, x_M, y_m, y_M);
	camera_.Scale(1.1f);
	// 设置点的大小
	float density = num_vertices_ / ((x_M - x_m) * (y_M - y_m));
	glm::vec2 scale(0.125f / glm::sqrt(density));
	for (it = 0; it < num_vertices_; it++)
		vertex_entities_[it].scale_ = glm::vec2(scale);

	// 规定边数据文件的第一行指定边的数量
	if (!(efile >> num_edges_ && !efile.eof()))
	{
		std::cout << "ERROR::file format error" << std::endl;
		return;
	}
	// 加载所有的边
	edge_entities_ = new EdgeEntity[num_edges_];
	int start_id, end_id;
	int line = 0;
	float weight;
	efile >> c1 >> c2;
	while (efile >> start_id >> c1 >> end_id >> c2 >> weight && !efile.eof())
	{
		if (start_id < 0 || start_id >= num_vertices_ || end_id < 0 || end_id >= num_vertices_)
			std::cout << "WARNNING::invalid edge::in file `" << edge_file << "` Line " << line << std::endl;
		else
		{
			edge_entities_[line] = EdgeEntity(vertex_entities_[start_id].position_, vertex_entities_[end_id].position_);
			vertices_[start_id].AddEdge(end_id, weight, &edge_entities_[line]);
			vertices_[end_id].AddEdge(start_id, weight, &edge_entities_[line]);
			line++;
		}
	}
	// 实际有效的边的总数
	num_edges_ = line;
	ResetColor();
	// 初始化网格
	trimesh_.SetupInstanced(num_vertices_);
	BlitTrianlgeColorInstanced();
	BlitTriangleModelInstanced();
	linemesh_.SetupInstanced(num_edges_);
	BlitLineModelInstanced();
	BlitLineColorInstanced();


	// 初始化标记数组等
	Init();
}

void Map::Clear()
{
	LinkGraph::Clear();
	if (vertex_entities_ != NULL)
		delete[] vertex_entities_;
	vertex_entities_ = NULL;
	if (edge_entities_ != NULL)
		delete[] edge_entities_;
	edge_entities_ = NULL;
}

void Map::ClickVertex()
{
	if (num_vertices_ <= 0)
		return;
	// 寻找离鼠标最近的点
	glm::vec2 pos = camera_.Clip2WorldPoint(Input::GetMousePos());
	int id = 0;
	float m = glm::distance(vertex_entities_[0].position_, pos);
	float t;
	for (int i = 1; i < num_vertices_; i++)
	{
		t = glm::distance(vertex_entities_[i].position_, pos);
		if (t < m)
		{
			m = t;
			id = i;
		}
	}
	if (clicked_vertex_ >= 0)
	{
		// 把上一个被点击的顶点的颜色变回去
		vertex_entities_[clicked_vertex_].color_ = clicked_vertex_color;
		ChangeTriangleColor(clicked_vertex_, clicked_vertex_color);
	}
	if (m < glm::length(vertex_entities_[id].scale_))
	{
		clicked_vertex_color = vertex_entities_[id].color_;
		vertex_entities_[id].color_ = ColorNormalize(VertexClickedColor);
		ChangeTriangleColor(id, ColorNormalize(VertexClickedColor));
		clicked_vertex_ = id;
	}
	else
	{
		clicked_vertex_ = -1;
	}
}

void Map::ProcessInput()
{
	// 鼠标滚轮缩放
	float scroll = Input::GetMouseScroll();
	if (glm::abs(scroll) > 0.001f)
	{
		camera_.Scale(1.0f - 0.1f * scroll);
	}

	// 左键按住拖动地图
	if (Input::GetMouseButton(GLFW_MOUSE_BUTTON_LEFT))
	{
		glm::vec2 offset = Input::GetMouseMovement();
		if (offset.x * offset.x + offset.y * offset.y > 0.0f)
		{
			translated_ = true;
			camera_.Translate(camera_.Clip2WorldVector(-offset));
		}
	}

	if (Input::GetMouseButtonUp(GLFW_MOUSE_BUTTON_LEFT))
	{
		if (!translated_)
			ClickVertex();
		translated_ = false;
	}
}

void Map::Update()
{
	if (control_enabled_)
	{
		ProcessInput();
	}
	if (simulating_)
	{
		Simulate();
	}
	Draw();
}

void Map::BlitTriangleModelInstanced()
{
	glm::mat4 model;
	int index;
	glBindBuffer(GL_ARRAY_BUFFER, trimesh_.modelVBO_);
	for (index = 0; index < num_vertices_; index++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(vertex_entities_[index].position_, 0.0f));
		model = glm::scale(model, glm::vec3(vertex_entities_[index].scale_, 1.0f));
		glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(glm::mat4), sizeof(glm::mat4), &model);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Map::BlitTrianlgeColorInstanced()
{
	glBindBuffer(GL_ARRAY_BUFFER, trimesh_.colorVBO_);
	int index;
	glm::vec3 color;
	for (index = 0; index < num_vertices_; index++)
	{
		color = vertex_entities_[index].color_;
		glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(glm::vec3), sizeof(glm::vec3), &color);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Map::BlitLineModelInstanced()
{
	glBindBuffer(GL_ARRAY_BUFFER, linemesh_.modelVBO_);
	int index;
	glm::mat4 model;
	for (index = 0; index < num_edges_; index++)
	{
		model = glm::mat4(
			glm::vec4(edge_entities_[index].end_ - edge_entities_[index].start_, 0, 0),
			glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
			glm::vec4(edge_entities_[index].start_, 0.0f, 1.0f));
		glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(glm::mat4), sizeof(glm::mat4), &model);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Map::BlitLineColorInstanced()
{
	glBindBuffer(GL_ARRAY_BUFFER, linemesh_.colorVBO_);
	int index;
	glm::vec3 color;
	for (index = 0; index < num_edges_; index++)
	{
		color = edge_entities_[index].color_;
		glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(glm::vec3), sizeof(glm::vec3), &color);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Map::ChangeTriangleColor(int id, const glm::vec3& color)
{
	glBindBuffer(GL_ARRAY_BUFFER, trimesh_.colorVBO_);
	glBufferSubData(GL_ARRAY_BUFFER, id * sizeof(glm::vec3), sizeof(glm::vec3), &color);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Map::ColoringPath(const Path& path)
{
	// 路径上的点变色
	for (int i = 0; i < path.Length(); i++)
		vertex_entities_[path[i]].color_ = ColorNormalize(VertexInPathColor);
	// 路径上的边变色
	for (int i = 0; i < path.Length() - 1; i++)
		vertices_[path[i]].FindEdge(path[i + 1])->entity_->color_ = ColorNormalize(EdgeInPathColor);
}


void Map::ResetColor()
{
	for (int i = 0; i < num_vertices_; i++)
		vertex_entities_[i].color_ = ColorNormalize(VertexDefaultColor);
	if (!simulating_)
	{
		for (int i = 0; i < num_edges_; i++)
			edge_entities_[i].color_ = ColorNormalize(EdgeDefaultColor);
	}
	else
	{
		SetTrafficColor();
	}
}

void Map::SetTrafficColor()
{
	Edge* edge;
	for (int i = 0; i < num_vertices_; i++)
		for (vertices_[i].SetStart(); !vertices_[i].IsTail(); vertices_[i].Next())
		{
			edge = vertices_[i].GetValue();
			edge->entity_->color_ = ColorMap::Invoke(2.0f * static_cast<float>(edge->CurrentNumber_ - edge->VolumeMax_) / static_cast<float>(edge->VolumeMax_));
		}
}

void Map::ShowAroundPoint(int id, int num)
{
	if (0 <= id && id < num_vertices_)
	{
		int i, j;
		AroundPoint(id, num, simulating_);
		ResetColor();
		if (clicked_vertex_ == id)
			clicked_vertex_color = ColorNormalize(VertexCenterColor);
		// 改变路径的颜色
		for (i = 0; i < num; i++)
			ColoringPath(p[i]);
		vertex_entities_[id].color_ = ColorNormalize(VertexCenterColor);
		BlitTrianlgeColorInstanced();
		BlitLineColorInstanced();

		showingAroundPoint_ = true;
		showingShortestPoint_ = false;
		centerVertex_ = id;
		aroundAmount_ = num;
	}
}

void Map::ShowShortestPath(int start_id, int end_id)
{
	theDistance_ = INFINITY;
	if (0 <= start_id && start_id < num_vertices_ && 0 <= end_id && end_id < num_vertices_)
	{
		theDistance_ = FindPath(start_id, end_id, simulating_);
		ResetColor();
		ColoringPath(shortestPath_);
		vertex_entities_[start_id].color_ = ColorNormalize(VertexStartColor);
		vertex_entities_[end_id].color_ = ColorNormalize(VertexEndColor);
		BlitTrianlgeColorInstanced();
		BlitLineColorInstanced();

		if (clicked_vertex_ == start_id)
			clicked_vertex_color = ColorNormalize(VertexStartColor);
		else if (clicked_vertex_ == end_id)
			clicked_vertex_color = ColorNormalize(VertexEndColor);

		showingAroundPoint_ = false;
		showingShortestPoint_ = true;
		startVertex_ = start_id;
		endVertex_ = end_id;
	}
}


void Map::SetSimulate(bool simulate)
{
	simulating_ = simulate;
	if (simulating_)
	{
		timer_ = SimulateDelta;
		Simulate();
	}
	else
	{
		if (showingAroundPoint_)
		{
			ShowAroundPoint(centerVertex_, aroundAmount_);
		}
		else if (showingShortestPoint_)
		{
			ShowShortestPath(startVertex_, endVertex_);
		}
		else
		{
			ResetColor();
			BlitLineColorInstanced();
			BlitTriangleModelInstanced();
		}
	}
}

bool Map::IsSimulating() const
{
	return simulating_;
}

void Map::SetPause(bool pause)
{
	paused_ = pause;
}

bool Map::IsPaused() const
{
	return paused_;
}

void Map::Simulate()
{
	if (paused_)
		return;
	timer_ += Time::GetDeltaTime();
	if (timer_ >= SimulateDelta)
	{
		timer_ -= SimulateDelta;
		UpdateTraffic();
		if (showingAroundPoint_)
		{
			ShowAroundPoint(centerVertex_, aroundAmount_);
		}
		else if (showingShortestPoint_)
		{
			ShowShortestPath(startVertex_, endVertex_);
		}
		else
		{
			SetTrafficColor();
			BlitLineColorInstanced();
		}
	}
}