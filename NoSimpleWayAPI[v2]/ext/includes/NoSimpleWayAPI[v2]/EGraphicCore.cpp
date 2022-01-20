#ifndef _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#define _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#include "EGraphicCore.h"
#endif

namespace NS_EGraphicCore
{
	int							SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
	float						correction_x = 1.0f, correction_y = 1.0f;
	Shader* shader_texture_atlas_putter;

	glm::mat4						matrix_transform_default;

	ERenderBatcher* default_batcher_for_texture_atlas;
	ERenderBatcher* default_batcher_for_drawing;

	GLFWwindow* main_window;

	unsigned int					texture[32];
	ETextureAtlas* default_texture_atlas;
	unsigned char* image_data;
	int							texture_loader_width, texture_loader_height, nrChannels, last_texture_width, last_texture_height;
	std::vector<ETextureGabarite*>	texture_gabarites_list;
	float						delta_time;
	float						saved_time_for_delta;

	float current_offset_x	= 0.0f;
	float current_offset_y	= 0.0f;
	float current_zoom		= 1.0f;

	EColor_4 active_color[4]{ 1.0f, 1.0f, 1.0f, 1.0f };

	//ETextureAtlas*					default_texture_atlas;

	void processInput(GLFWwindow* window);

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void recalculate_correction();

	void switch_to_texture_atlas_draw_mode(ETextureAtlas* _atlas);
	void make_transform_from_size(glm::mat4 _transform, float _size_x, float _size_y);

	void initiate_graphic_core();


};

namespace NS_DefaultGabarites
{
	ETextureGabarite* texture_gabarite_gudron;
	ETextureGabarite* texture_gabarite_white_pixel;
}
ERenderBatcher::ERenderBatcher()
{
	size_t indices_id = 0;
	size_t indices_order = 0;

	for (int i = 0; i < MAX_SHAPES_COUNT; i++) {
		indices_buffer[indices_id + 0] = indices_order + 0;
		indices_buffer[indices_id + 1] = indices_order + 1;
		indices_buffer[indices_id + 2] = indices_order + 3;

		indices_buffer[indices_id + 3] = indices_order + 1;
		indices_buffer[indices_id + 4] = indices_order + 2;
		indices_buffer[indices_id + 5] = indices_order + 3;

		//std::

		indices_id += 6;
		indices_order += 4;

		//std::cout << "Generated indices. Id->[" << std::to_string(i) << "]" << " indices count->["<< std::to_string(indices_id) << "]" << std::endl;
	}

	std::cout << "initiate" << std::endl;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_buffer), indices_buffer, GL_STATIC_DRAW);

	/*
	std::cout << "initiate" << std::endl;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_buffer), indices_buffer, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	*/

	//zzz(indices_buffer);
	//indices_buffer = generateData();
}

ERenderBatcher::~ERenderBatcher()
{
}

namespace zalupa
{
	int zalupa1;
	int zalupa2;
	int zalupa3;
}
/*
void ERenderBatcher::render_sprite_call(ESprite* _sprite)
{
	if (pointer_to_sprite_render != nullptr)
	{
		pointer_to_sprite_render(_sprite);
	}
}*/

void ERenderBatcher::draw_call()
{
	//NS_EGraphicCore::make_transform_from_size(this, NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT);
	//if (get_shader() == nullptr) { EInputCore::logger_simple_error("you mad?"); }
	if ((last_vertice_buffer_index > 0) & (batcher_shader != nullptr))
	{
		
		batcher_shader->use();
		apply_transform();

		glBindBuffer(GL_ARRAY_BUFFER, VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * last_vertice_buffer_index, vertex_buffer, GL_DYNAMIC_DRAW);

		glDrawElements(GL_TRIANGLES, 6 * (int)(last_vertice_buffer_index / (gl_vertex_attribute_total_count * 4)), GL_UNSIGNED_INT, 0);

		//glDrawElements(GL_TRIANGLES, 6 * (last_vertice_buffer_index / 32), GL_UNSIGNED_INT, 0);

		//std::cout << "Draw call! element [16] is: " << std::to_string(vertex_buffer[16]) << std::endl;
	}
	else
	{
		if (batcher_shader == nullptr) { EInputCore::logger_simple_error("Shader is NULL"); }
	}

	reset();
}

void ERenderBatcher::set_active_color(const float(&_color)[4])
{
	std::copy(std::begin(_color), std::end(_color), std::begin(batch_color));
}

void ERenderBatcher::reset()
{
	set_last_id(0);
	//indices_id = 0;
	//indices_order = 0;
}

unsigned int ERenderBatcher::get_last_id()
{
	return last_vertice_buffer_index;
}

void ERenderBatcher::set_last_id(unsigned int _id)
{
	last_vertice_buffer_index = _id;
}

void ERenderBatcher::apply_transform()
{
	//NS_EGraphicCore::make_transform_from_size(this, NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT);
	NS_EGraphicCore::matrix_transform_default = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	NS_EGraphicCore::matrix_transform_default = glm::translate(NS_EGraphicCore::matrix_transform_default, glm::vec3(-1.0f, -1.0f, 0.0f));
	NS_EGraphicCore::matrix_transform_default = glm::scale(NS_EGraphicCore::matrix_transform_default, glm::vec3(1.0f / transform_screen_size_x * 2.0f, 1.0f / transform_screen_size_y * 2.0f, 1.0f));

	unsigned int transformLoc = glGetUniformLocation(batcher_shader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(NS_EGraphicCore::matrix_transform_default));
}

void ERenderBatcher::set_shader(Shader* _shader)
{
	batcher_shader = _shader;
	EInputCore::logger_simple_success("crete new shader");
}

Shader* ERenderBatcher::get_shader()
{
	return batcher_shader;
}

void ERenderBatcher::set_transform_position(float _x, float _y)
{
	transform_position_x = _x;
	transform_position_y = _y;
}

void ERenderBatcher::set_transform_screen_size(float _size_x, float _size_y)
{
	transform_screen_size_x = _size_x;
	transform_screen_size_y = _size_y;
}

void ERenderBatcher::set_transform_zoom(float _zoom)
{
	transform_zoom = _zoom;
}

bool ERenderBatcher::is_batcher_have_free_space(ERenderBatcher* _batcher)
{
	if (_batcher->last_vertice_buffer_index + _batcher->gl_vertex_attribute_total_count >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE)
	{
		_batcher->draw_call();
		return false;
	}

	return true;
}

void ERenderBatcher::set_total_attribute_count(GLsizei _attribute_count)
{
	gl_vertex_attribute_total_count = _attribute_count;
}

void ERenderBatcher::register_new_vertex_attribute(GLint _subpameters_count)
{
	glVertexAttribPointer
	(
		gl_vertex_attribute_id,
		_subpameters_count,
		GL_FLOAT,
		GL_FALSE,
		gl_vertex_attribute_total_count * sizeof(float),
		(void*)(gl_vertex_attribute_offset * sizeof(float))
	);

	glEnableVertexAttribArray(gl_vertex_attribute_id);

	gl_vertex_attribute_id++;
	gl_vertex_attribute_offset += _subpameters_count;
}

/*
unsigned int Batcher::set_last_id()
{
	return 0;
}
*/

bool ETextureAtlas::can_place_here(int _x, int _y, int _w, int _h)
{
	for (int i = _y; i <= _y + _h; i++)
		for (int j = _x; j <= _x + _w; j++)
		{
			if ((j * 4 >= *atlas_size_x) || (i * 4 >= *atlas_size_x))
			{
				return false;
			}

			if (!free_space[j][i]) { return false; }
		}

	return true;
}

unsigned short ETextureAtlas::get_atlas_size_x()
{
	return *atlas_size_x;
}

unsigned short ETextureAtlas::get_atlas_size_y()
{
	return *atlas_size_y;
}

unsigned short ETextureAtlas::get_framebuffer()
{
	return *framebuffer;
}

unsigned short ETextureAtlas::get_colorbuffer()
{
	return *colorbuffer;
}

ETextureAtlas::ETextureAtlas(float _size_x, float _size_y, int _color_depth, int _byte_mode)
{
	*atlas_size_x = _size_x;
	*atlas_size_y = _size_y;

	//////////////////////////////
	glGenFramebuffers(1, framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, *framebuffer);

	glGenTextures(1, colorbuffer);
	glBindTexture(GL_TEXTURE_2D, *colorbuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, _color_depth, _size_x, _size_y, 0, GL_RGBA, _byte_mode, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *colorbuffer, 0);

	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//////////////////////////////////////

	free_space = new bool* [(int)(_size_x / 4.0f)];

	for (auto i = 0; i < (int)(_size_x / 4.0f); i++)
	{
		free_space[i] = new bool[(int)(_size_y / 4.0f)];

		for (auto j = 0; j < (int)(_size_y / 4.0f); ++j)
		{
			free_space[i][j] = true;
		}
	}
}

ETextureAtlas::~ETextureAtlas()
{
}

void NS_EGraphicCore::switch_to_texture_atlas_draw_mode(ETextureAtlas* _atlas)
{
	glViewport(0, 0, _atlas->get_atlas_size_x(), _atlas->get_atlas_size_y());
	glBindFramebuffer(GL_FRAMEBUFFER, _atlas->get_framebuffer());

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_MAX);

	make_transform_from_size(NS_EGraphicCore::default_batcher_for_texture_atlas, _atlas->get_atlas_size_x(), _atlas->get_atlas_size_y());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, NS_EGraphicCore::texture[0]);

	default_batcher_for_texture_atlas->set_active_color(NS_EColorCollection::COLOR_WHITE);
}

void NS_EGraphicCore::make_transform_from_size(ERenderBatcher* _batcher, float _size_x, float _size_y)
{
	NS_EGraphicCore::matrix_transform_default = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	NS_EGraphicCore::matrix_transform_default = glm::translate(NS_EGraphicCore::matrix_transform_default, glm::vec3(-1.0f, -1.0f, 0.0f));
	NS_EGraphicCore::matrix_transform_default = glm::scale(NS_EGraphicCore::matrix_transform_default, glm::vec3(1.0f / _size_x * 2.0f, 1.0f / _size_y * 2.0f, 1.0f));


}

//void EGraphicCore::make_transform_from_size(glm::mat4 _transform)
//{
//}

void NS_EGraphicCore::initiate_graphic_core()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 2);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	/*glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_DECORATED, NULL);*/

	NS_EGraphicCore::main_window = glfwCreateWindow(NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT, "Window name", NULL, NULL);
	//std::cout << "[0]window is:" << (EGraphicCore::main_window) << std::endl;

	if (NS_EGraphicCore::main_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		//return -1;
	}

	glfwMakeContextCurrent(NS_EGraphicCore::main_window);

	glfwSetFramebufferSizeCallback(NS_EGraphicCore::main_window, framebuffer_size_callback);
	glfwSetInputMode(NS_EGraphicCore::main_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	//glfwSetMousePos(0, 0);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		//return -1;
	}

	//EGraphicCore::shader_texture_atlas_putter = new Shader("data/#default.vs", "data/#default.fs");
	//EGraphicCore::shader_texture_atlas_putter->use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT);
	recalculate_correction();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glBlendEquation(GL_FUNC_ADD);

	NS_EGraphicCore::default_texture_atlas = new ETextureAtlas(4096, 4096);
	NS_EGraphicCore::load_texture("data/textures/white_pixel.png", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, NS_EGraphicCore::texture[0]);

	NS_EGraphicCore::default_batcher_for_texture_atlas = new ERenderBatcher();

	NS_EGraphicCore::default_batcher_for_texture_atlas->set_total_attribute_count(8);

	NS_EGraphicCore::default_batcher_for_texture_atlas->register_new_vertex_attribute(2);//position	| [x][y]
	NS_EGraphicCore::default_batcher_for_texture_atlas->register_new_vertex_attribute(4);//color		| [r][g][b][a]
	NS_EGraphicCore::default_batcher_for_texture_atlas->register_new_vertex_attribute(2);//UV texure	| [U][V]		|

	NS_EGraphicCore::default_batcher_for_texture_atlas->set_shader(new Shader("data/#default.vs", "data/#default.fs"));

	NS_EGraphicCore::default_batcher_for_texture_atlas->set_transform_screen_size
	(
		NS_EGraphicCore::default_texture_atlas->get_atlas_size_x(),
		NS_EGraphicCore::default_texture_atlas->get_atlas_size_y()
	);

	NS_EGraphicCore::default_batcher_for_texture_atlas->set_transform_position(0.0f, 0.0f);
	NS_EGraphicCore::default_batcher_for_texture_atlas->set_transform_zoom(1.0f);


	default_batcher_for_drawing = new ERenderBatcher();
	default_batcher_for_drawing->set_total_attribute_count(8);		//[x][y][r][g][b][a][u][v]

	default_batcher_for_drawing->register_new_vertex_attribute(2);	//position	1[x]	2[y]	#	#
	default_batcher_for_drawing->register_new_vertex_attribute(4);	//color		1[r]	2[g]	3[b]	4[a]
	default_batcher_for_drawing->register_new_vertex_attribute(2);	//uv texture	1[u]	2[v]	#	#

	//total
	//[0][32][64][96][128][164]===164 bits(32 bytes) per vertex ===32*4 (128) bytes per shape
	//[x][y][r][g][b][a][u][v]

	default_batcher_for_drawing->set_shader(new Shader("data/#default.vs", "data/#default.fs"));


	NS_DefaultGabarites::texture_gabarite_white_pixel = NS_EGraphicCore::put_texture_to_atlas("data/textures/white_pixel.png", NS_EGraphicCore::default_texture_atlas);
	NS_DefaultGabarites::texture_gabarite_gudron = NS_EGraphicCore::put_texture_to_atlas("data/textures/gudron_roof.png", NS_EGraphicCore::default_texture_atlas);
	
	//font
	EFont* new_font = NULL;
	ETextureGabarite* font_gabarite = NS_EGraphicCore::put_texture_to_atlas("data/font/franklin_0.png", NS_EGraphicCore::default_texture_atlas);
	new_font = new EFont("franklin", font_gabarite, NS_EGraphicCore::default_texture_atlas, false);
	EFont::font_list.push_back(new_font);
}

void NS_EGraphicCore::gl_set_texture_filtering(GLint _wrap_mode, GLint _filter)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrap_mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrap_mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filter);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filter);//
}

void NS_EGraphicCore::gl_set_blend_mode_default()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
}

void NS_EGraphicCore::set_active_color(const EColor_4(&_color)[4])
{
	NS_EGraphicCore::active_color[0] = _color[0];
	NS_EGraphicCore::active_color[1] = _color[1];
	NS_EGraphicCore::active_color[2] = _color[2];
	NS_EGraphicCore::active_color[3] = _color[3];
}

void NS_EGraphicCore::set_active_color(EColor_4 *_color)
{
	NS_EGraphicCore::active_color[0] = _color[0];
	NS_EGraphicCore::active_color[1] = _color[1];
	NS_EGraphicCore::active_color[2] = _color[2];
	NS_EGraphicCore::active_color[3] = _color[3];

	/*EInputCore::logger_param("COLOR [0]", _color[0]);
	EInputCore::logger_param("COLOR [1]", _color[1]);
	EInputCore::logger_param("COLOR [2]", _color[2]);
	EInputCore::logger_param("COLOR [3]", _color[3]);
	std::cout << "---------" << std::endl;*/
}

	


void NS_EGraphicCore::load_texture(char const* _path, int _id)
{
	glGenTextures(_id, &texture[_id]);
	glBindTexture(GL_TEXTURE_2D, texture[_id]);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	//ifstream (_path)

	image_data = stbi_load(_path, &texture_loader_width, &texture_loader_height, &nrChannels, STBI_rgb_alpha);
	if (image_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_loader_width, texture_loader_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		//glGenerateMipmap(GL_TEXTURE_2D);

		//cout << "loaded texture W:" << width << " H:" << height << endl;

		last_texture_height = texture_loader_height;
		last_texture_width = texture_loader_width;

		//texture_error = false;
		/*texture_w[_id] = width;
		texture_h[_id] = height;*/
	}
	else
	{
		image_data = stbi_load("data/textures/ERROR.png", &texture_loader_width, &texture_loader_height, &nrChannels, STBI_rgb_alpha);
		if (image_data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_loader_width, texture_loader_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
			last_texture_height = texture_loader_height;
			last_texture_width = texture_loader_width;
		}
		//cout << red << "Failed to load texture " << yellow << "(" << _path << ")" << green << endl;
		std::cout << "Failed to load texture " << "(" << _path << ")" << std::endl;
		//last_texture_h = 21;
		//last_texture_w = 21;

		//texture_error = true;

		//just_created_gabarite = DefaultGabarite::gabarite_error;
	}

	stbi_image_free(image_data);
}

ETextureGabarite* NS_EGraphicCore::put_texture_to_atlas(std::string _full_path, ETextureAtlas* _atlas)
{
	for (int i = 0; i < _full_path.length(); i++)
	{
		if (_full_path[i] == '\\') { _full_path[i] = '/'; }
	}

	ETextureGabarite* duplicate_gabarite = nullptr;

	//search already loaded texture gabarite
	for (ETextureGabarite* g : NS_EGraphicCore::texture_gabarites_list)
	{
		if (g->get_full_path() == _full_path)
		{
			duplicate_gabarite = g;
		}
	}

	ETextureGabarite* new_gabarite = nullptr;

	if (duplicate_gabarite == nullptr)
	{
		NS_EGraphicCore::switch_to_texture_atlas_draw_mode(_atlas);

		NS_EGraphicCore::load_texture(_full_path.c_str(), 0);

		//search free place for new texture
		int place_x = -1;
		int place_y = -1;
		for (int x = 0; x < (int)(_atlas->get_atlas_size_x() / 4.0f); x++)
		{
			for (int y = 0; y < (int)(_atlas->get_atlas_size_y() / 4.0f); y++)
			{
				if (_atlas->can_place_here(x, y, ceil(NS_EGraphicCore::last_texture_width / 4.0f), ceil(NS_EGraphicCore::last_texture_height / 4.0f)))
				{
					place_x = x * 4;
					place_y = y * 4;

					break;
				}
			}
			if (place_x >= 0) { break; }
		}
		//
		for (int x = (ceil)(place_x / 4.0f) - 2; x < (ceil)((place_x + NS_EGraphicCore::last_texture_width) / 4.0f) + 2; x++)
			for (int y = (ceil)(place_y / 4.0f) - 2; y < (ceil)((place_y + NS_EGraphicCore::last_texture_height) / 4.0f) + 2; y++)
				if
					(
						(x < (int)(_atlas->get_atlas_size_x() / 4.0f))
						&
						(y < (int)(_atlas->get_atlas_size_y() / 4.0f))
						&
						(x >= 0)
						&
						(y >= 0)
					)
				{
					_atlas->free_space[x][y] = false;
				}

		NS_EGraphicCore::default_batcher_for_texture_atlas->reset();


		NS_ERenderCollection::add_data_to_vertex_buffer_default
		(
			NS_EGraphicCore::default_batcher_for_texture_atlas->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_texture_atlas->last_vertice_buffer_index,
			place_x,
			place_y,
			NS_EGraphicCore::last_texture_width,
			NS_EGraphicCore::last_texture_height
		);
		NS_EGraphicCore::default_batcher_for_texture_atlas->draw_call();

		new_gabarite = new ETextureGabarite();

		if (new_gabarite != nullptr)
		{
			new_gabarite->set_full_path(_full_path);
			new_gabarite->set_name_based_on_full_path(_full_path);

			new_gabarite->set_uv_parameters
			(
				(float)(place_x + 0.0f) / (float)(_atlas->get_atlas_size_x()),
				(float)(place_y + 0.0f) / (float)(_atlas->get_atlas_size_y()),

				((float)(NS_EGraphicCore::last_texture_width) - 1.0f / (float)(last_texture_width)) / (float)_atlas->get_atlas_size_x(),
				((float)(NS_EGraphicCore::last_texture_height) - 1.0f / (float)(last_texture_height)) / (float)_atlas->get_atlas_size_y()
			);

			new_gabarite->set_real_texture_size
			(
				NS_EGraphicCore::last_texture_width,
				NS_EGraphicCore::last_texture_height
			);

			EInputCore::logger_param("Generate new gabarite (full path)", new_gabarite->get_full_path());
			EInputCore::logger_param("Generate new gabarite (name)", new_gabarite->get_name());
			NS_EGraphicCore::texture_gabarites_list.push_back(new_gabarite);
		}
	}
	else
	{
		new_gabarite = duplicate_gabarite;
		EInputCore::logger_param("Use existed gabarite", new_gabarite->get_full_path());
	}


	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDisable(GL_DEPTH_TEST);
	glBlendEquation(GL_FUNC_ADD);

	glViewport(0, 0, NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, NS_EGraphicCore::default_texture_atlas->get_colorbuffer());

	return new_gabarite;
}

void NS_ERenderCollection::add_data_to_vertex_buffer_default(float* _array, unsigned int& _start_offset, float _x, float _y, float _w, float _h)
{
	//address arithmetic, get pointer to buffer array, and move to +_offset
	_array += _start_offset;

	//.#
	//..
	//[!][!][!]WARNING![!][!][!] It not "[0][1][2]..." index, it "[_start_offset + 0][_start_offset + 1][_start_offset + 2]..." index, see address arithmetic above
	_array[0] = (_x + _w);//x
	_array[1] = (_y + _h);//y

	_array[2] = NS_EGraphicCore::active_color[0];//r
	_array[3] = NS_EGraphicCore::active_color[1];//g
	_array[4] = NS_EGraphicCore::active_color[2];//b
	_array[5] = NS_EGraphicCore::active_color[3];//a

	_array[6] = 1.0f;//u
	_array[7] = 1.0f;//v

	//..
	//.#
	_array[8] = (_x + _w);
	_array[9] = _y;

	_array[10] = NS_EGraphicCore::active_color[0];
	_array[11] = NS_EGraphicCore::active_color[1];
	_array[12] = NS_EGraphicCore::active_color[2];
	_array[13] = NS_EGraphicCore::active_color[3];

	_array[14] = 1.0f;
	_array[15] = 0.0f;

	//..
	//#.
	_array[16] = _x;
	_array[17] = _y;

	_array[18] = NS_EGraphicCore::active_color[0];
	_array[19] = NS_EGraphicCore::active_color[1];
	_array[20] = NS_EGraphicCore::active_color[2];
	_array[21] = NS_EGraphicCore::active_color[3];

	_array[22] = 0.0f;
	_array[23] = 0.0f;

	//#.
	//..
	_array[24] = _x;
	_array[25] = (_y + _h);

	_array[26] = NS_EGraphicCore::active_color[0];
	_array[27] = NS_EGraphicCore::active_color[1];
	_array[28] = NS_EGraphicCore::active_color[2];
	_array[29] = NS_EGraphicCore::active_color[3];

	_array[30] = 0.0f;
	_array[31] = 1.0f;

	_start_offset += 32;
}

void NS_ERenderCollection::add_data_to_vertex_buffer_rama(float* _array, unsigned int& _start_offset, float _x, float _y, float _w, float _h, float _t, ETextureGabarite* _texture)
{
	//left (vertical)
	add_data_to_vertex_buffer_textured_rectangle_with_custom_size(_array, _start_offset, _x, _y, _t, _h, _texture);

	//right (vertical)
	add_data_to_vertex_buffer_textured_rectangle_with_custom_size(_array, _start_offset, _x + _h - _t, _y, _t, _h, _texture);

	//down (horizontal)
	add_data_to_vertex_buffer_textured_rectangle_with_custom_size(_array, _start_offset, _x, _y, _w, _t, _texture);

	//up (horizontal)
	add_data_to_vertex_buffer_textured_rectangle_with_custom_size(_array, _start_offset, _x, _y + _h - _t, _w, _t, _texture);
}

void NS_ERenderCollection::add_data_to_vertex_buffer_custom_uv(float* _array, unsigned int& _start_offset, float _x, float _y, float _size_x, float _size_y, float _uv_start_x, float _uv_start_y, float _uv_end_x, float _uv_end_y)
{
	//address arithmetic, get pointer to buffer array, and move to +_offset
	_array += _start_offset;

	//[!][!][!]WARNING![!][!][!] It not "[0][1][2]..." index, it "[_start_offset + 0][_start_offset + 1][_start_offset + 2]..." index, see address arithmetic above
	//.#
	//..
	_array[0] = (_x + _size_x);
	_array[1] = (_y + _size_y);

	_array[2] = NS_EGraphicCore::active_color[0];
	_array[3] = NS_EGraphicCore::active_color[1];
	_array[4] = NS_EGraphicCore::active_color[2];
	_array[5] = NS_EGraphicCore::active_color[3];

	_array[6] = _uv_end_x;
	_array[7] = _uv_end_y;

	//EInputCore::logger_param("internal", _uv_end_y);

	//..
	//.#
	_array[8] = (_x + _size_x);
	_array[9] = _y;

	_array[10] = NS_EGraphicCore::active_color[0];
	_array[11] = NS_EGraphicCore::active_color[1];
	_array[12] = NS_EGraphicCore::active_color[2];
	_array[13] = NS_EGraphicCore::active_color[3];

	_array[14] = _uv_end_x;
	_array[15] = _uv_start_y;

	//..
	//#.
	_array[16] = _x;
	_array[17] = _y;

	_array[18] = NS_EGraphicCore::active_color[0];
	_array[19] = NS_EGraphicCore::active_color[1];
	_array[20] = NS_EGraphicCore::active_color[2];
	_array[21] = NS_EGraphicCore::active_color[3];

	_array[22] = _uv_start_x;
	_array[23] = _uv_start_y;

	//#.
	//..
	_array[24] = _x;
	_array[25] = (_y + _size_y);

	_array[26] = NS_EGraphicCore::active_color[0];
	_array[27] = NS_EGraphicCore::active_color[1];
	_array[28] = NS_EGraphicCore::active_color[2];
	_array[29] = NS_EGraphicCore::active_color[3];

	_array[30] = _uv_start_x;
	_array[31] = _uv_end_y;

	_start_offset += 32;
}

void NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size(float* _array, unsigned int& _start_offset, float _x, float _y, float _w, float _h, ETextureGabarite* _texture)
{
	//address arithmetic, get pointer to buffer array, and move to +_offset
	_array += _start_offset;

	//[!][!][!]WARNING![!][!][!] It not "[0][1][2]..." index, it "[_start_offset + 0][_start_offset + 1][_start_offset + 2]..." index, see address arithmetic above
	_array[0] = (_x + _w);
	_array[1] = (_y + _h);

	_array[2] = NS_EGraphicCore::active_color[0];
	_array[3] = NS_EGraphicCore::active_color[1];
	_array[4] = NS_EGraphicCore::active_color[2];
	_array[5] = NS_EGraphicCore::active_color[3];

	_array[6] = *_texture->uv_end_x;
	_array[7] = *_texture->uv_end_y;

	//..
	//.#
	_array[8] = (_x + _w);
	_array[9] = _y;

	_array[10] = NS_EGraphicCore::active_color[0];
	_array[11] = NS_EGraphicCore::active_color[1];
	_array[12] = NS_EGraphicCore::active_color[2];
	_array[13] = NS_EGraphicCore::active_color[3];

	_array[14] = *_texture->uv_end_x;
	_array[15] = *_texture->uv_start_y;

	//..
	//#.
	_array[16] = _x;
	_array[17] = _y;

	_array[18] = NS_EGraphicCore::active_color[0];
	_array[19] = NS_EGraphicCore::active_color[1];
	_array[20] = NS_EGraphicCore::active_color[2];
	_array[21] = NS_EGraphicCore::active_color[3];

	_array[22] = *_texture->uv_start_x;
	_array[23] = *_texture->uv_start_y;

	//#.
	//..
	_array[24] = _x;
	_array[25] = (_y + _h);

	_array[26] = NS_EGraphicCore::active_color[0];
	_array[27] = NS_EGraphicCore::active_color[1];
	_array[28] = NS_EGraphicCore::active_color[2];
	_array[29] = NS_EGraphicCore::active_color[3];

	_array[30] = *_texture->uv_start_x;
	_array[31] = *_texture->uv_end_y;

	_start_offset += 32;
}

void NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_real_size(float* _array, unsigned int& _start_offset, float _x, float _y, ETextureGabarite* _texture)
{
	//address arithmetic, get pointer to buffer array, and move to +_offset
	_array += _start_offset;

	//[!][!][!]WARNING![!][!][!] It not "[0][1][2]..." index, it "[_start_offset + 0][_start_offset + 1][_start_offset + 2]..." index, see address arithmetic above
	_array[0] = (_x + *_texture->size_x_in_pixels);
	_array[1] = (_y + *_texture->size_y_in_pixels);

	_array[2] = NS_EGraphicCore::active_color[0];
	_array[3] = NS_EGraphicCore::active_color[1];
	_array[4] = NS_EGraphicCore::active_color[2];
	_array[5] = NS_EGraphicCore::active_color[3];

	_array[6] = *_texture->uv_end_x;
	_array[7] = *_texture->uv_end_y;

	//..
	//.#
	_array[8] = (_x + *_texture->size_x_in_pixels);
	_array[9] = _y;

	_array[10] = NS_EGraphicCore::active_color[0];
	_array[11] = NS_EGraphicCore::active_color[1];
	_array[12] = NS_EGraphicCore::active_color[2];
	_array[13] = NS_EGraphicCore::active_color[3];

	_array[14] = *_texture->uv_end_x;
	_array[15] = *_texture->uv_start_y;

	//..
	//#.
	_array[16] = _x;
	_array[17] = _y;

	_array[18] = NS_EGraphicCore::active_color[0];
	_array[19] = NS_EGraphicCore::active_color[1];
	_array[20] = NS_EGraphicCore::active_color[2];
	_array[21] = NS_EGraphicCore::active_color[3];

	_array[22] = *_texture->uv_start_x;
	_array[23] = *_texture->uv_start_y;

	//#.
	//..
	_array[24] = _x;
	_array[25] = (_y + *_texture->size_y_in_pixels);

	_array[26] = NS_EGraphicCore::active_color[0];
	_array[27] = NS_EGraphicCore::active_color[1];
	_array[28] = NS_EGraphicCore::active_color[2];
	_array[29] = NS_EGraphicCore::active_color[3];

	_array[30] = *_texture->uv_start_x;
	_array[31] = *_texture->uv_end_y;

	_start_offset += 32;

	
}

void NS_ERenderCollection::call_render_textured_rectangle_with_custom_size(ESprite* _sprite)
{
	NS_EGraphicCore::set_active_color(_sprite->sprite_color);

	if ((_sprite != nullptr) && (_sprite->main_texture != nullptr))
	{
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			_sprite->master_sprite_layer->vertex_buffer,
			*_sprite->master_sprite_layer->last_buffer_id,

			*_sprite->world_position_x,
			*_sprite->world_position_y,

			*_sprite->size_x,
			*_sprite->size_y,

			_sprite->main_texture
		);
	}
}

void NS_ERenderCollection::call_render_textured_rectangle_real_size(ESprite* _sprite)
{
	//EInputCore::logger_simple_success("call render texured rectangle");

	//unsigned int zalupa;

	if ((_sprite != nullptr) && (_sprite->main_texture != nullptr))
	{
		_sprite->master_sprite_layer->vertex_buffer = new float[100];

		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_real_size
		(
			_sprite->master_sprite_layer->vertex_buffer,
			*_sprite->master_sprite_layer->last_buffer_id,
			*_sprite->world_position_x,
			*_sprite->world_position_y,
			_sprite->main_texture
		);
	}
	else
	{
		if (_sprite == nullptr) { EInputCore::logger_simple_error("Sprite in call render textured rectangle is null"); }
		else
		{
			if (_sprite->main_texture == nullptr) { EInputCore::logger_simple_error("Sprite texture in call render textured rectangle is null"); }
		}
	}
}

void NS_EGraphicCore::processInput(GLFWwindow* window)
{
}

void NS_EGraphicCore::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{//
	//width = round(width / 2.0f) * 2;
	//height = round(height / 2.0f) * 2;
	//glScissor(0, 0, 500, 500);
	glfwSetWindowSize(NS_EGraphicCore::main_window, width, height);

	glViewport(0, 0, width, height);
	glfwGetWindowSize(window, &NS_EGraphicCore::SCREEN_WIDTH, &NS_EGraphicCore::SCREEN_WIDTH);

	std::cout << "Resize event width:" << NS_EGraphicCore::SCREEN_WIDTH << " height: " << NS_EGraphicCore::SCREEN_WIDTH << std::endl;

	recalculate_correction();
}

void NS_EGraphicCore::recalculate_correction()
{
	if ((NS_EGraphicCore::SCREEN_WIDTH > 100) && (NS_EGraphicCore::SCREEN_HEIGHT > 100))
	{
		NS_EGraphicCore::correction_x = 1.0f / NS_EGraphicCore::SCREEN_WIDTH * 2.0f;
		NS_EGraphicCore::correction_y = 1.0f / NS_EGraphicCore::SCREEN_HEIGHT * 2.0f;

		//std::cout << "helper correction_x: " << correction_x << " correction_y: " << correction_y << std::endl;
	}
}

std::string_view ETextureGabarite::get_full_path()
{
	return *full_path;
}

void ETextureGabarite::set_full_path(std::string _full_path)
{
	if (full_path != nullptr)
	{
		*full_path = _full_path;
	}
}

std::string_view ETextureGabarite::get_name()
{
	return *name;
}

void ESpriteLayer::translate_sprite_layer(float _x, float _y, float _z)
{
	/*
	*offset_x += _x;
	*offset_y += _y;
	*offset_z += _z;
	*/

	*world_position_x += _x;
	*world_position_y += _y;
	*world_position_z += _z;

	translate_sprites(_x, _y, _z);
	modify_buffer_position_for_sprite_layer(_x, _y, _z);


}

void ETextureGabarite::set_name_based_on_full_path(std::string _name)
{
	int start_s = 0;
	int end_s = 0;

	for (int i = 0; i < _name.length(); i++)
	{
		if ((_name.at(i) == '/') || (_name.at(i) == '\\'))
		{
			start_s = i + 1;
		}

		if ((_name.at(i) == '.'))
		{
			end_s = i - 1;
		}
	}

	*name = _name.substr(start_s, end_s - start_s + 1);
}

void ETextureGabarite::set_uv_parameters(float _uv_start_x, float _uv_start_y, float _uv_size_x, float _uv_size_y)
{
	*uv_start_x = _uv_start_x;
	*uv_start_y = _uv_start_y;

	*uv_end_x = _uv_start_x + _uv_size_x;
	*uv_end_y = _uv_start_y + _uv_size_y;

	EInputCore::logger_param("uv_start_x", *uv_start_x);
	EInputCore::logger_param("uv_start_y", *uv_start_y);

	EInputCore::logger_param("uv_end_x", *uv_end_x);
	EInputCore::logger_param("uv_end_y", *uv_end_y);
}

void ETextureGabarite::set_real_texture_size(int _size_x, int _size_y)
{
	*size_x_in_pixels = _size_x;
	*size_y_in_pixels = _size_y;
}


void ESpriteLayer::modify_buffer_position_for_sprite_layer(float _x, float _y, float _z)
{




	for (int k = 0; k < 4; k++)
	for (int i = 0; i < *last_buffer_id; i += 32)
	{
			vertex_buffer[i + k * 8 + 0] += _x;
			vertex_buffer[i + k * 8 + 1] += _y;
	}

	for (ESprite* spr : sprite_list)
	{
		*spr->offset_x += _x;
		*spr->offset_y += _y;
		*spr->offset_z += _z;
	}
}

void ESpriteLayer::generate_vertex_buffer_for_sprite_layer(std::string _text)
{

	if
	(
		(!sprite_list.empty())
		&
		(
			(batcher != nullptr)
		)
	)
	{
		*last_buffer_id = 0;

		for (ESprite* spr : sprite_list)
		{
			if ((spr != nullptr) && (spr->pointer_to_sprite_render != nullptr))
			{
				//EInputCore::logger_simple_success("try call render by pointer[" + std::to_string(_text) + "]");
				spr->pointer_to_sprite_render(spr);
			}
			else
			{
				EInputCore::logger_simple_error("Sprite is null!");
			}
		}
	}
	else
	{
		//if (sl == nullptr) { EInputCore::logger_simple_error("SpriteList is null!"); }

		if (batcher == nullptr)
		{
			EInputCore::logger_simple_error("[sprite layer batcher] is null");
		}
	}
}

void ESpriteLayer::transfer_vertex_buffer_to_batcher()
{
	if
	(
		(last_buffer_id > 0)
		&&
		(
			(batcher != nullptr)
		)
	)
	{
		//memcpy();
		//std::cout << "-------" << std::endl;

		unsigned int vertices_buffer_capacity = MAX_SHAPES_COUNT * VERTICES_PER_SHAPE * batcher->gl_vertex_attribute_total_count;
		//EInputCore::logger_param("vertices_buffer_capacity", vertices_buffer_capacity);

		unsigned int passes = ceil(*last_buffer_id / (float)vertices_buffer_capacity);
		//EInputCore::logger_param("passes", passes);

		unsigned int data_size = *last_buffer_id;
		//EInputCore::logger_param("data_size", data_size);


		for (unsigned int i = 0; i < passes; i++)
		{

			memcpy
			(
				batcher->vertex_buffer + batcher->last_vertice_buffer_index,
				vertex_buffer + (size_t)(i * vertices_buffer_capacity),
				min(data_size, vertices_buffer_capacity) * sizeof(*vertex_buffer)
			);

			batcher->last_vertice_buffer_index += min(data_size, vertices_buffer_capacity);

			if (batcher->last_vertice_buffer_index >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE)
			{
				batcher->draw_call();
			}
		}

		
		//std::copy(0, (int)(sizeof(sl->vertex_buffer)), std::begin(sl->batcher->vertex_buffer));
	}
	else
	{
		if (batcher == nullptr) { EInputCore::logger_simple_error("batcher is null"); }
	}
}

void ESpriteLayer::translate_sprites(float _x, float _y, float _z)
{
	for (ESprite* spr : sprite_list)
	{
		*spr->offset_x += _x;
		*spr->offset_y += _y;
		*spr->offset_z += _z;

		*spr->world_position_x += _x;
		*spr->world_position_y += _y;
		*spr->world_position_z += _z;
	}


}

ESprite::ESprite()
{

}

ESprite::~ESprite()
{
}

void ESprite::set_color(float _r, float _g, float _b, float _a)
{
	sprite_color[0] = _r;
	sprite_color[1] = _g;
	sprite_color[2] = _b;
	sprite_color[3] = _a;
}

void ESprite::set_color(const float(&_color)[4])
{
	sprite_color[0] = _color[0];
	sprite_color[1] = _color[1];
	sprite_color[2] = _color[2];
	sprite_color[3] = _color[3];
}

void ESprite::translate_sprite(float _x, float _y, float _z)
{
	*offset_x += _x;
	*offset_y += _y;
	*offset_z += _z;
}

void ESprite::generate_vertex_buffer_for_master_sprite_layer()
{
	if ((master_sprite_layer != nullptr) & (main_texture != nullptr))
	{
		//master_sprite_layer->batcher->pointer_to_render()
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_real_size
		(
			master_sprite_layer->vertex_buffer,
			*master_sprite_layer->last_buffer_id,
			*world_position_x,
			*world_position_y + *world_position_z,
			main_texture
		);
	}
}
