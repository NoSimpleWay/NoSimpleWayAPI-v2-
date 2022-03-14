#ifndef _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#define _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#include "EGraphicCore.h"
#endif

namespace NS_EGraphicCore
{
	int							SCREEN_WIDTH = 1920, SCREEN_HEIGHT = 1080;
	float						correction_x = 1.0f, correction_y = 1.0f;
	Shader* shader_texture_atlas_putter;

	glm::mat4						matrix_transform_default;

	ERenderBatcher* default_batcher_for_texture_atlas;
	ERenderBatcher* default_batcher_for_drawing;

	GLFWwindow* main_window;

	unsigned int					texture[32];
	ETextureAtlas* default_texture_atlas;
	unsigned char* image_data;
	unsigned char* zalupa;
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

namespace NS_ERenderCollection
{
	float			border_left_size;
	float			border_right_size;
	float			border_up_size;
	float			border_down_size;

	unsigned int		subdivision_x;
	unsigned int		subdivision_y;
}

namespace NS_DefaultGabarites
{
	ETextureGabarite* texture_gabarite_gudron;
	ETextureGabarite* texture_rusted_bronze;
	ETextureGabarite* texture_lead_and_gold;
	ETextureGabarite* texture_slider_bg_lead_and_gold;
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

bool ERenderBatcher::check_batcher(ERenderBatcher* _batcher)
{
	if (_batcher->last_vertice_buffer_index + _batcher->gl_vertex_attribute_total_count * VERTICES_PER_SHAPE >= _batcher->gl_vertex_attribute_total_count * VERTICES_PER_SHAPE * MAX_SHAPES_COUNT)
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

	default_batcher_for_texture_atlas->set_active_color(NS_EColorUtils::COLOR_WHITE);
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

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_DECORATED, NULL);

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


	NS_DefaultGabarites::texture_gabarite_white_pixel		= NS_EGraphicCore::put_texture_to_atlas("data/textures/white_pixel.png", NS_EGraphicCore::default_texture_atlas);
	NS_DefaultGabarites::texture_gabarite_gudron			= NS_EGraphicCore::put_texture_to_atlas("data/textures/gudron_roof.png", NS_EGraphicCore::default_texture_atlas);
	NS_DefaultGabarites::texture_rusted_bronze				= NS_EGraphicCore::put_texture_to_atlas("data/textures/Rusted_bronze.png", NS_EGraphicCore::default_texture_atlas);
	NS_DefaultGabarites::texture_lead_and_gold				= NS_EGraphicCore::put_texture_to_atlas("data/textures/Lead_and_gold.png", NS_EGraphicCore::default_texture_atlas);
	NS_DefaultGabarites::texture_slider_bg_lead_and_gold	= NS_EGraphicCore::put_texture_to_atlas("data/textures/slider_bg_lead_and_gold.png", NS_EGraphicCore::default_texture_atlas);
	
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

void NS_EGraphicCore::set_active_color_custom_alpha(const EColor_4(&_color)[4], float _alpha)
{
	NS_EGraphicCore::active_color[0] = _color[0];
	NS_EGraphicCore::active_color[1] = _color[1];
	NS_EGraphicCore::active_color[2] = _color[2];
	NS_EGraphicCore::active_color[3] = _alpha;
}

void NS_EGraphicCore::set_active_color(EColor_4 *_color)
{
	NS_EGraphicCore::active_color[0] = _color[0];
	NS_EGraphicCore::active_color[1] = _color[1];
	NS_EGraphicCore::active_color[2] = _color[2];
	NS_EGraphicCore::active_color[3] = _color[3];
}

	


void NS_EGraphicCore::load_texture(char const* _path, int _id)
{
	glGenTextures(_id, &texture[_id]);
	glBindTexture(GL_TEXTURE_2D, texture[_id]);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	//ifstream (_path)

	image_data = stbi_load(_path, &texture_loader_width, &texture_loader_height, &nrChannels, STBI_rgb_alpha);
	
	//std::string sss = std::to_string(*image_data);
	//EInputCore::logger_simple_success(sss);
	
	

	if (image_data)
	{
		//for (int i = 0; i < texture_loader_width * texture_loader_height * 4; i++)
		//{
		//	image_data[i] = rand() % 256;
		//}

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
		//image_data = stbi_load("data/textures/ERROR.png", &texture_loader_width, &texture_loader_height, &nrChannels, STBI_rgb_alpha);
		
		
		last_texture_height = 100;
		last_texture_width = 100;

		texture_loader_width = 3;
		texture_loader_height = 3;
		//std::string error_string = "xxxÿxxxÿxxxÿxxxÿxxxÿxxxÿxxxÿxxxÿxxxÿxxxÿxxxÿxxxÿxxxÿxxxÿ   ÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿÿ ÿÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ   ÿ";

		//unsigned char zzz = 97;

		int image_size = texture_loader_width * texture_loader_height * 4;
		zalupa = new unsigned char[image_size]();

		zalupa[0] = 0;
		zalupa[1] = 0;
		zalupa[2] = 0;
		zalupa[3] = 255;

		zalupa[4] = 255;
		zalupa[5] = 0;
		zalupa[6] = 255;
		zalupa[7] = 255;

		zalupa[8] = 0;
		zalupa[9] = 0;
		zalupa[10] = 0;
		zalupa[11] = 255;



		zalupa[12] = 255;
		zalupa[13] = 0;
		zalupa[14] = 255;
		zalupa[15] = 255;

		zalupa[16] = 0;
		zalupa[17] = 0;
		zalupa[18] = 0;
		zalupa[19] = 255;

		zalupa[20] = 255;
		zalupa[21] = 0;
		zalupa[22] = 255;
		zalupa[23] = 255;



		zalupa[24] = 0;
		zalupa[25] = 0;
		zalupa[26] = 0;
		zalupa[27] = 255;

		zalupa[28] = 255;
		zalupa[29] = 0;
		zalupa[30] = 255;
		zalupa[31] = 255;

		zalupa[32] = 0;
		zalupa[33] = 0;
		zalupa[34] = 0;
		zalupa[35] = 255;

		/*for (int i = 0; i < texture_loader_width * texture_loader_height; i++)
		{
			zalupa[size_t(i + 0)] = 0;
			zalupa[size_t(i + 1)] = 0;
			zalupa[size_t(i + 2)] = 0;
			zalupa[size_t(i + 3)] = 255;
		}*/
		//zalupa[0] = 0;

		//std::cout << zalupa << std::endl;

		if (zalupa)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_loader_width, texture_loader_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, zalupa);
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
						&&
						(y < (int)(_atlas->get_atlas_size_y() / 4.0f))
						&&
						(x >= 0)
						&&
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

			*new_gabarite->position_on_texture_atlas_x = place_x;
			*new_gabarite->position_on_texture_atlas_y = place_y;

			new_gabarite->set_uv_parameters
			(
				(float)(place_x + 0.0f) / (float)(_atlas->get_atlas_size_x()),
				(float)(place_y + 0.0f) / (float)(_atlas->get_atlas_size_y()),

				((float)(NS_EGraphicCore::last_texture_width) - 1.0f / (float)(last_texture_width)) / (float)_atlas->get_atlas_size_x(),
				((float)(NS_EGraphicCore::last_texture_height) - 1.0f / (float)(last_texture_height)) / (float)_atlas->get_atlas_size_y()
			);

			new_gabarite->target_atlas = _atlas;

			new_gabarite->set_real_texture_size
			(
				NS_EGraphicCore::last_texture_width,
				NS_EGraphicCore::last_texture_height
			);

			//EInputCore::logger_param("Generate new gabarite (full path)", new_gabarite->get_full_path());
			//EInputCore::logger_param("Generate new gabarite (name)", new_gabarite->get_name());

			NS_EGraphicCore::texture_gabarites_list.push_back(new_gabarite);
		}
	}
	else
	{
		new_gabarite = duplicate_gabarite;
		//EInputCore::logger_param("Use existed gabarite", new_gabarite->get_full_path());
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
	add_data_to_vertex_buffer_textured_rectangle_with_custom_size(_array, _start_offset, _x - _t, _y, _t, _h, _texture);

	//right (vertical)
	add_data_to_vertex_buffer_textured_rectangle_with_custom_size(_array, _start_offset, _x + _w, _y, _t, _h, _texture);

	//down (horizontal)
	add_data_to_vertex_buffer_textured_rectangle_with_custom_size(_array, _start_offset, _x - _t, _y - _t, _w + _t * 2.0f, _t, _texture);

	//up (horizontal)
	add_data_to_vertex_buffer_textured_rectangle_with_custom_size(_array, _start_offset, _x - _t, _y + _h, _w + _t * 2.0f, _t, _texture);
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

void NS_ERenderCollection::add_data_to_vertex_buffer_sprite(float* _array, unsigned int& _start_offset, ESprite* _sprite)
{
	//address arithmetic, get pointer to buffer array, and move to +_offset
	_array += _start_offset;

	//.#
	//..
	//[!][!][!]WARNING![!][!][!] It not "[0][1][2]..." index, it "[_start_offset + 0][_start_offset + 1][_start_offset + 2]..." index, see address arithmetic above
	_array[0] = *_sprite->world_position_x + *_sprite->size_x;
	_array[1] = *_sprite->world_position_y + *_sprite->size_y;

	_array[2] = NS_EGraphicCore::active_color[0];
	_array[3] = NS_EGraphicCore::active_color[1];
	_array[4] = NS_EGraphicCore::active_color[2];
	_array[5] = NS_EGraphicCore::active_color[3];

	_array[6] = *_sprite->uv_end_x;
	_array[7] = *_sprite->uv_end_y;

	//..
	//.#
	_array[8] = *_sprite->world_position_x + *_sprite->size_x;
	_array[9] = *_sprite->world_position_y;

	_array[10] = NS_EGraphicCore::active_color[0];
	_array[11] = NS_EGraphicCore::active_color[1];
	_array[12] = NS_EGraphicCore::active_color[2];
	_array[13] = NS_EGraphicCore::active_color[3];

	_array[14] = *_sprite->uv_end_x;
	_array[15] = *_sprite->uv_start_y;

	//..
	//#.
	_array[16] = *_sprite->world_position_x;
	_array[17] = *_sprite->world_position_y;

	_array[18] = NS_EGraphicCore::active_color[0];
	_array[19] = NS_EGraphicCore::active_color[1];
	_array[20] = NS_EGraphicCore::active_color[2];
	_array[21] = NS_EGraphicCore::active_color[3];

	_array[22] = *_sprite->uv_start_x;
	_array[23] = *_sprite->uv_start_y;

	//#.
	//..
	_array[24]= *_sprite->world_position_x;
	_array[25]= *_sprite->world_position_y + *_sprite->size_y;

	_array[26] = NS_EGraphicCore::active_color[0];
	_array[27] = NS_EGraphicCore::active_color[1];
	_array[28] = NS_EGraphicCore::active_color[2];
	_array[29] = NS_EGraphicCore::active_color[3];

	_array[30] = *_sprite->uv_start_x;
	_array[31] = *_sprite->uv_end_y;

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
		//_sprite->master_sprite_layer->vertex_buffer = new float[100];

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

void NS_ERenderCollection::call_render_textured_sprite(ESprite* _sprite)
{
	//EInputCore::logger_simple_success("call render texured rectangle");

	//unsigned int zalupa;

	if ((_sprite != nullptr) && (_sprite->main_texture != nullptr))
	{
		//_sprite->master_sprite_layer->vertex_buffer = new float[100];

		NS_EGraphicCore::set_active_color(_sprite->sprite_color);

		NS_ERenderCollection::add_data_to_vertex_buffer_sprite
		(
			_sprite->master_sprite_layer->vertex_buffer,
			*_sprite->master_sprite_layer->last_buffer_id,
			_sprite
		);
	}
	else
	{
		if (_sprite == nullptr) { EInputCore::logger_simple_error("Sprite in call render textured rectangle is null"); }
		else
		{
			if (_sprite->main_texture == nullptr) { EInputCore::logger_simple_error("[call_render_textured_sprite] sprite main texture is null"); }
		}
	}
}



void NS_ERenderCollection::set_borders_and_subdivisions(float _left, float _right, float _bottom, float _up, int _subdivision_x, int _subdivision_y)
{
	border_left_size = _left;
	border_right_size = _right;

	border_down_size = _bottom;
	border_up_size = _up;

	subdivision_x = _subdivision_x;
	subdivision_y = _subdivision_y;

}

void NS_ERenderCollection::generate_brick_texture(ERegionGabarite* _region, ESpriteLayer* _sprite_layer, ETextureGabarite* _texture_gabarite)
{

	//dynamic
		int		total_divisions_x = 1;
		int		total_divisions_y = 1;

		//how many tiles need to fill region (X)
		float	final_fragments_count_x = 0.0f;
		//how many tiles need to fill region (Y)
		float	final_fragments_count_y = 0.0f;

		//cycle count x
		int		count_of_generations_x = 0;
		//cycles count y
		int		count_of_generations_y = 0;

		//offset relative region start x
		float	base_offset_x = 0.0f;
		//offset relative region start y
		float	base_offset_yz = 0.0f;

		//size of one tile (x)
		float	size_of_brick_x = *_texture_gabarite->size_x_in_pixels / (float)total_divisions_x;
		//size of one tile (y)
		float	size_of_brick_y = *_texture_gabarite->size_y_in_pixels / (float)total_divisions_y;

		//uv offset in texture in pixels (x)
		float	texture_offset_x = 0.0f;
		//uv offset in texture in pixels (y)
		float	texture_offset_y = 0.0f;

		//tile offset x
		float	final_offset_x = 0.0f;
		//tile offset y
		float	final_offset_yz = 0.0f;

		int current_sprite_frame_id = 0;
		ESprite* current_sprite = nullptr;

	//static
		float full_segment_size_x = *_region->size_x;
		float full_segment_size_y = *_region->size_y;

		float cropped_mid_segment_size_x = full_segment_size_x - NS_ERenderCollection::border_left_size - NS_ERenderCollection::border_right_size;
		float cropped_mid_segment_size_y = full_segment_size_y - NS_ERenderCollection::border_down_size - NS_ERenderCollection::border_up_size;

		float final_mid_segment_size_x = full_segment_size_x - NS_ERenderCollection::border_left_size - NS_ERenderCollection::border_right_size;
		float final_mid_segment_size_y = full_segment_size_y - NS_ERenderCollection::border_up_size - NS_ERenderCollection::border_down_size;

		//EInputCore::logger_param("cropped segment x", cropped_mid_segment_size_x);


	//segment		seg_x	seg_y
	//
	//left bottom	0		0
	//bottom		1		0
	//right bottom	2		0 
	//left mid		0		1 
	//mid		q	1		1 
	//rightmid		2		1 
	//left up		0		2 
	//up			1		2 
	//right up		2		2
	//
	//

	if (false)
	for (int i = _sprite_layer->sprite_frame_list.size(); i < 1'000; i++)
	{
		//ESpriteLayer::add_new_default_frame_with_sprite(_texture_gabarite, _sprite_layer);
		_sprite_layer->sprite_frame_list.push_back(ESpriteFrame::create_default_sprite_frame_with_sprite(_texture_gabarite, _sprite_layer));
	}

	for (ESpriteFrame* frm : _sprite_layer->sprite_frame_list)
	{
		//frm->sprite_list[0]->reset_sprite();
	}

	if (true)
	for (unsigned int seg_y = 0; seg_y < 3; seg_y++)
	{
	
		//left border
		
			if ((seg_y == 0))//down
			{
				total_divisions_y = 1;
				size_of_brick_y = NS_ERenderCollection::border_down_size;

				base_offset_yz = *_region->offset_y;

				final_fragments_count_y = 1.0f;
				count_of_generations_y = 1;

				texture_offset_y = 0.0f;
			}
			else
			//mid wall
			if ((seg_y == 1))
			{
				total_divisions_y = NS_ERenderCollection::subdivision_y + 1;
				size_of_brick_y = (*_texture_gabarite->size_y_in_pixels - NS_ERenderCollection::border_down_size - NS_ERenderCollection::border_up_size) / (float)total_divisions_y;

				base_offset_yz = *_region->offset_y + NS_ERenderCollection::border_down_size + 0.0f;

				final_fragments_count_y = cropped_mid_segment_size_y / size_of_brick_y;
				count_of_generations_y = ceil(final_fragments_count_y);

				texture_offset_y = NS_ERenderCollection::border_down_size;
			}
			else
			if ((seg_y == 2))
			{
				total_divisions_y = 1;
				size_of_brick_y = NS_ERenderCollection::border_up_size;

				base_offset_yz = *_region->offset_y + cropped_mid_segment_size_y + NS_ERenderCollection::border_down_size + 0.0f;

				final_fragments_count_y = 1.0f;
				count_of_generations_y = 1;
			
				texture_offset_y = *_texture_gabarite->size_y_in_pixels - NS_ERenderCollection::border_up_size;
			}

		for (unsigned int seg_x = 0; seg_x < 3; seg_x++)
		{
			

			
			if ((seg_x == 0))
			{
				total_divisions_x = 1;
				size_of_brick_x = NS_ERenderCollection::border_left_size;

				base_offset_x = *_region->offset_x + 0.0f;

				final_fragments_count_x = 1.0f;
				count_of_generations_x = 1;
			
				texture_offset_x = 0.0f;
			}
			else
			//mid wall
			if ((seg_x == 1))
			{
				total_divisions_x = NS_ERenderCollection::subdivision_x + 1;
				size_of_brick_x = (*_texture_gabarite->size_x_in_pixels - NS_ERenderCollection::border_left_size - NS_ERenderCollection::border_right_size) / (float)total_divisions_x;

				base_offset_x = *_region->offset_x + NS_ERenderCollection::border_left_size + 0.0f;

				final_fragments_count_x = (cropped_mid_segment_size_x - 0.0f) / size_of_brick_x;
				count_of_generations_x = ceil(final_fragments_count_x);

				texture_offset_x = NS_ERenderCollection::border_left_size;
			}
			else
			if ((seg_x == 2))
			{
				total_divisions_x = 1;
				size_of_brick_x = NS_ERenderCollection::border_right_size;

				base_offset_x = *_region->offset_x + cropped_mid_segment_size_x + NS_ERenderCollection::border_left_size + 0.0f;

				final_fragments_count_x = 1.0f;
				count_of_generations_x = 1;
			
				texture_offset_x = *_texture_gabarite->size_x_in_pixels - NS_ERenderCollection::border_right_size;
			}

			
			final_offset_yz = base_offset_yz;
			for (int yy = 0; yy < count_of_generations_y; yy++)
			{
				final_offset_x = base_offset_x;

				for (int xx = 0; xx < count_of_generations_x; xx++)//base_sprite_fragment_offset_x = full_mid_segment_size_x - NS_ERenderCollection::border_left_size;
				{
					if (current_sprite_frame_id >= _sprite_layer->sprite_frame_list.size())
					{
						_sprite_layer->sprite_frame_list.push_back(ESpriteFrame::create_default_sprite_frame_with_sprite(_texture_gabarite, _sprite_layer));
					}

					current_sprite = _sprite_layer->sprite_frame_list.at(current_sprite_frame_id)->sprite_list.at(0);
					current_sprite->reset_sprite();

					current_sprite->set_texture_gabarite(_texture_gabarite);

					*current_sprite->fragment_offset_x = texture_offset_x + (rand() % (total_divisions_x ) * size_of_brick_x);
					*current_sprite->fragment_offset_y = texture_offset_y + (rand() % (total_divisions_y ) * size_of_brick_y);

					*current_sprite->offset_x = final_offset_x;
					*current_sprite->offset_y = final_offset_yz;

					*current_sprite->fragment_size_x = min (final_fragments_count_x - xx, 1.0f) * size_of_brick_x;
					*current_sprite->fragment_size_y = min (final_fragments_count_y - yy, 1.0f) * size_of_brick_y;

					*current_sprite->size_x = *current_sprite->fragment_size_x;
					*current_sprite->size_y = *current_sprite->fragment_size_y;

					
					current_sprite->sprite_calculate_uv();
					final_offset_x += size_of_brick_x + 0.0f;

					current_sprite_frame_id++;
					
				}//base_sprite_fragment_offset_x = full_mid_segment_size_x - NS_ERenderCollection::border_left_size;

				final_offset_yz += size_of_brick_y + 0.0f;

				
				
			}
		}
	}

	for (int i = current_sprite_frame_id; i < _sprite_layer->sprite_frame_list.size(); i++)
	{
		_sprite_layer->sprite_frame_list[i]->sprite_list[0]->reset_sprite();
	}

	//_sprite_layer->generate_vertex_buffer_for_sprite_layer("autobuilding");


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

std::string ETextureGabarite::get_full_path()
{
	return *full_path;
}

void ETextureGabarite::calculate_final_sizes()
{

}

void ETextureGabarite::set_full_path(std::string _full_path)
{
	if (full_path != nullptr)
	{
		*full_path = _full_path;
	}
}

std::string ETextureGabarite::get_name()
{
	return *name;
}

void ESpriteLayer::translate_sprite_layer(float _x, float _y, float _z, bool _move_offset)
{
	*world_position_x += _x;
	*world_position_y += _y;
	*world_position_z += _z;

	if (_move_offset)
	{
		*offset_x += _x;
		*offset_y += _y;
		*offset_z += _z;
	}

	//child elements, modify only world coordinates
	translate_sprites(_x, _y, _z, false);


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

	//EInputCore::logger_param("uv_start_x", *uv_start_x);
	//EInputCore::logger_param("uv_start_y", *uv_start_y);

	//EInputCore::logger_param("uv_end_x", *uv_end_x);
	//EInputCore::logger_param("uv_end_y", *uv_end_y);
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

	for (ESpriteFrame* frame:sprite_frame_list)
	for (ESprite* spr : frame->sprite_list)
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
		(!sprite_frame_list.empty())
		&&
		(
			(batcher != nullptr)
		)
	)
	{
		//if array is too small, delete and register new size
		if (sprite_frame_list.size() * batcher->gl_vertex_attribute_total_count * 4 >= *last_buffer_id)
		{
			delete[] vertex_buffer; 
			vertex_buffer = new float[sprite_frame_list.size() * batcher->gl_vertex_attribute_total_count * 4];
		}

		*last_buffer_id = 0;
		
		
		

		for (ESpriteFrame* frame:sprite_frame_list)
		//for (ESprite* spr : frame->sprite_list)
		{
			ESprite* spr = frame->sprite_list.at(*frame->active_frame_id);
			//EInputCore::logger_param("frame id", *frame->active_frame_id);
			//EInputCore::logger_param("texture name", spr->main_texture->get_name());
			//EInputCore::logger_param("memory", spr);

			//std::cout << "memory location" << spr << std::endl;
			if ((spr != nullptr) && (*spr->size_x * *spr->size_y > 0) && (spr->pointer_to_sprite_render != nullptr))
			{
				//EInputCore::logger_simple_success("try call render by pointer[" + std::to_string(_text) + "]");
				ERenderBatcher::check_batcher(batcher);
				spr->pointer_to_sprite_render(spr);
				//batcher->draw_call();
			}
			else
			{
				if (spr == nullptr) { EInputCore::logger_simple_error("Sprite is null!"); }
				else
				if (spr->pointer_to_sprite_render == nullptr) { EInputCore::logger_simple_error("Pointer to render is null!"); }
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
		(*last_buffer_id > 0)
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

			if (batcher->last_vertice_buffer_index >= vertices_buffer_capacity)
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

void ESpriteLayer::sprite_layer_set_world_position(float _x, float _y, float _z)
{

	*world_position_x =_x + *offset_x;
	*world_position_y =_y + *offset_y;
	*world_position_z =_z + *offset_z;

	for (ESpriteFrame* frame : sprite_frame_list)
		for (ESprite* spr : frame->sprite_list)
			if (spr != nullptr)
			{
				*spr->world_position_x = *world_position_x + *spr->offset_x;
				*spr->world_position_y = *world_position_y + *spr->offset_y;
				*spr->world_position_z = *world_position_z + *spr->offset_z;
			}
}

ESpriteLayer* ESpriteLayer::create_default_sprite_layer(ETextureGabarite* _texture)
{
	ESpriteLayer*	jc_sprite_layer	=	new ESpriteLayer();
	ESpriteFrame*	jc_sprite_frame	=	ESpriteFrame::create_default_sprite_frame_with_sprite(_texture, jc_sprite_layer);
	ESprite*		jc_sprite		=	jc_sprite_frame->sprite_list[0];

	jc_sprite_layer->sprite_frame_list.push_back(jc_sprite_frame);
	jc_sprite_layer->batcher = NS_EGraphicCore::default_batcher_for_drawing;

	jc_sprite->pointer_to_sprite_render = &NS_ERenderCollection::call_render_textured_sprite;
	jc_sprite->master_sprite_layer = jc_sprite_layer;


	//if (_texture != nullptr) { jc_sprite->set_texture_gabarite(_texture); }

	return jc_sprite_layer;
}

ESprite* ESpriteLayer::get_last_created_sprite(ESpriteLayer* _layer)
{
	int last_frame_id	= _layer->sprite_frame_list.size() - 1;
	int last_sprite_id	= _layer->sprite_frame_list[last_frame_id]->sprite_list.size() - 1;

	return _layer->sprite_frame_list[last_frame_id]->sprite_list[last_sprite_id];
}

ESpriteFrame* ESpriteLayer::get_last_sprite_frame(ESpriteLayer* _layer)
{
	if (!_layer->sprite_frame_list.empty())
	{
		return _layer->sprite_frame_list[_layer->sprite_frame_list.size() - 1];
	}
	else
	{
		return nullptr;
	}
}

void ESpriteLayer::set_size_for_last_sprite(ESpriteLayer* _layer, float _size_x, float _size_y)
{
	ESprite* last_sprite = ESpriteLayer::get_last_created_sprite(_layer);

	*last_sprite->size_x = _size_x;
	*last_sprite->size_y = _size_y;

	last_sprite->sprite_calculate_uv();
	
}

void ESpriteLayer::add_new_default_frame_with_sprite(ETextureGabarite* _texture_gabarite, ESpriteLayer* _sprite_layer)
{
	_sprite_layer->sprite_frame_list.push_back(ESpriteFrame::create_default_sprite_frame_with_sprite(_texture_gabarite, _sprite_layer));
}

void ESpriteLayer::translate_sprites(float _x, float _y, float _z, bool _move_offset)
{
	for (ESpriteFrame* frame : sprite_frame_list)
	for (ESprite* spr : frame->sprite_list)
	{
		*spr->world_position_x += _x;
		*spr->world_position_y += _y;
		*spr->world_position_z += _z;

		if (_move_offset)
		{
			*spr->offset_x += _x;
			*spr->offset_y += _y;
			*spr->offset_z += _z;
		}
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


void ESprite::set_texture_gabarite(ETextureGabarite* _gabarite)
{
	main_texture = _gabarite;



	if (_gabarite != nullptr)
	{
		*fragment_size_x = *_gabarite->size_x_in_pixels;
		*fragment_size_y = *_gabarite->size_y_in_pixels;

		*size_x = *_gabarite->size_x_in_pixels;
		*size_y = *_gabarite->size_y_in_pixels;
	}
	else
	{
		EInputCore::logger_simple_error("[set texture gabarite] _gabarite is nullptr!");
	}

	sprite_calculate_uv();
}

void ESprite::sprite_calculate_uv()
{
	*uv_start_x = *main_texture->uv_start_x + *fragment_offset_x / main_texture->target_atlas->get_atlas_size_x();
	*uv_start_y = *main_texture->uv_start_y + *fragment_offset_y / main_texture->target_atlas->get_atlas_size_y();

	*uv_end_x = *uv_start_x + (*fragment_size_x - 1.0f / *fragment_size_x) / main_texture->target_atlas->get_atlas_size_x();
	*uv_end_y = *uv_start_y + (*fragment_size_y - 1.0f / *fragment_size_y) / main_texture->target_atlas->get_atlas_size_y();

}

void ESprite::reset_sprite()
{
	main_texture = nullptr;

	*fragment_offset_x	= 0.0f;
	*fragment_offset_y	= 0.0f;

	*fragment_size_x	= 0.0f;
	*fragment_size_y	= 0.0f;


	*uv_start_x			= 0.0f;
	*uv_start_y			= 0.0f;

	*uv_end_x			= 0.0f;
	*uv_end_y			= 0.0f;

	*offset_x			= 0.0f;
	*offset_y			= 0.0f;
	*offset_z			= 0.0f;

	*world_position_x	= 0.0f;
	*world_position_y	= 0.0f;
	*world_position_z	= 0.0f;

	*size_x				= (0.0f);
	*size_y				= (0.0f);
}

void ESprite::sprite_set_world_positions(float _x, float _y, float _z)
{
	*world_position_x = _x + *offset_x;
	*world_position_y = _y + *offset_y;
	*world_position_z = _z + *offset_z;
}

ESprite* ESprite::create_default_sprite(ETextureGabarite* _gabarite, ESpriteLayer* _sprite_layer)
{
	ESprite* jc_sprite = new ESprite();

	if (_gabarite != nullptr)
	{
		jc_sprite->set_texture_gabarite(_gabarite);
	}

	jc_sprite->pointer_to_sprite_render = &NS_ERenderCollection::call_render_textured_sprite;
	jc_sprite->master_sprite_layer = _sprite_layer;

	return jc_sprite;
}

//void ESprite::create_default_sprite_layer()
//{
//}

EColor_4 const (&NS_EColorUtils::choose_from_two(const EColor_4(&_color1)[4], const EColor_4(&_color2)[4], bool _condition))[4]
{
	if (_condition)
	{
		return _color1;
	}

	return _color2;
}

ESpriteFrame* ESpriteFrame::create_default_sprite_frame()
{
	//ESprite*		jc_sprite			= new ESprite();
	ESpriteFrame*	jc_sprite_frame		= new ESpriteFrame();

	//jc_sprite_frame->sprite_list.push_back(jc_sprite);

	return jc_sprite_frame;
}

ESpriteFrame* ESpriteFrame::create_default_sprite_frame_with_sprite(ETextureGabarite* _texture_gabarite, ESpriteLayer* _parent_sprite_layer)
{
	ESprite* jc_sprite = ESprite::create_default_sprite(_texture_gabarite, _parent_sprite_layer);
	ESpriteFrame* jc_sprite_frame = new ESpriteFrame();

	jc_sprite_frame->sprite_list.push_back(jc_sprite);

	return jc_sprite_frame;
}

//ESpriteFrame* ESpriteFrame::create_default_sprite_frame_with_sprite(*ETexturEeGabarite _texture_gabarite, *ESpriteLayer _parent_sprite_layer)
//{
//	return nullptr;
//}
