#ifndef _EGRAPHICCORE_
/**/#define _EGRAPHICCORE_
/**/#include "EGraphicCore.h"
#endif

namespace EGraphicCore
{
	int							SCREEN_WIDTH = 1920, SCREEN_HEIGHT = 1080;
	float						correction_x = 1.0f, correction_y = 1.0f;
	Shader*						shader_texture_atlas_putter;

	glm::mat4						matrix_transform_default;
	Batcher*						default_batcher_for_texture_atlas;

	GLFWwindow*					main_window;

	unsigned int					texture[32];
	ETextureAtlas*					default_texture_atlas;
	unsigned char*					image_data;
	int							texture_loader_width, texture_loader_height, nrChannels, last_texture_width, last_texture_height;
	std::vector<ETextureGabarite*>	texture_gabarites_list;
	float						delta_time;
	float						saved_time_for_delta;

	//ETextureAtlas*					default_texture_atlas;


	void processInput(GLFWwindow* window);

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void recalculate_correction();

	void switch_to_texture_atlas_draw_mode(ETextureAtlas* _atlas);
	void make_transform_from_size(glm::mat4 _transform, float _size_x, float _size_y);

	void initiate_graphic_core();
};


Batcher::Batcher()
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

	glBufferData(GL_ARRAY_BUFFER,			sizeof(vertex_buffer),	vertex_buffer,		GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,	sizeof(indices_buffer),	indices_buffer,	GL_STATIC_DRAW);

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

Batcher::~Batcher()
{
}

namespace zalupa
{
	int zalupa1;
	int zalupa2;
	int zalupa3;
}


void Batcher::draw_call()
{
	if (last_vertice_buffer_index > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * last_vertice_buffer_index, vertex_buffer, GL_DYNAMIC_DRAW);
		
		glDrawElements(GL_TRIANGLES, 6 * (int)(last_vertice_buffer_index / (gl_vertex_attribute_total_count * 4)), GL_UNSIGNED_INT, 0);

		//glDrawElements(GL_TRIANGLES, 6 * (last_vertice_buffer_index / 32), GL_UNSIGNED_INT, 0);

		//std::cout << "Draw call! element [16] is: " << std::to_string(vertex_buffer[16]) << std::endl;
	}

	reset();
}

void Batcher::set_color(const float(&_color)[4])
{
	std::copy(std::begin(_color), std::end(_color), std::begin(batch_color));
}

void Batcher::reset()
{
	set_last_id(0);
	//indices_id = 0;
	//indices_order = 0;
}

unsigned int Batcher::get_last_id()
{
	return last_vertice_buffer_index;
}

void Batcher::set_last_id(unsigned int _id)
{
	last_vertice_buffer_index = _id;
}

void Batcher::set_total_attribute_count(GLsizei _attribute_count)
{
	gl_vertex_attribute_total_count = _attribute_count;
}

void Batcher::register_new_vertex_attribute(GLint _subpameters_count)
{
	glVertexAttribPointer
	(
		gl_vertex_attribute_id,
		_subpameters_count,
		GL_FLOAT,
		GL_FALSE,
		gl_vertex_attribute_total_count * sizeof(float),
		(void*) ( gl_vertex_attribute_offset * sizeof(float) )
	);

	glEnableVertexAttribArray	(gl_vertex_attribute_id);

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

void EGraphicCore::switch_to_texture_atlas_draw_mode(ETextureAtlas* _atlas)
{
	glViewport(0, 0, _atlas->get_atlas_size_x(), _atlas->get_atlas_size_y());
	glBindFramebuffer(GL_FRAMEBUFFER, _atlas->get_framebuffer());

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_MAX);

	make_transform_from_size(_atlas->get_atlas_size_x(), _atlas->get_atlas_size_y());
	EGraphicCore::shader_texture_atlas_putter->use();	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, EGraphicCore::texture[0]);
	EGraphicCore::shader_texture_atlas_putter->setInt("texture1", 0);
	default_batcher_for_texture_atlas->set_color(EColorCollection::COLOR_WHITE);

	
}

void EGraphicCore::make_transform_from_size(float _size_x, float _size_y)
{
		EGraphicCore::matrix_transform_default = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		EGraphicCore::matrix_transform_default = glm::translate(EGraphicCore::matrix_transform_default, glm::vec3(-1.0f, -1.0f, 0.0f));
		EGraphicCore::matrix_transform_default = glm::scale(EGraphicCore::matrix_transform_default, glm::vec3(1.0f / _size_x * 2.0f, 1.0f / _size_y * 2.0f, 1.0f));
		unsigned int transformLoc = glGetUniformLocation(EGraphicCore::shader_texture_atlas_putter->ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform_default));
}

//void EGraphicCore::make_transform_from_size(glm::mat4 _transform)
//{
//}


void EGraphicCore::initiate_graphic_core()
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

	EGraphicCore::main_window = glfwCreateWindow(EGraphicCore::SCREEN_WIDTH, EGraphicCore::SCREEN_HEIGHT, "Window name", NULL, NULL);
	//std::cout << "[0]window is:" << (EGraphicCore::main_window) << std::endl;

	if (EGraphicCore::main_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		//return -1;
	}

	glfwMakeContextCurrent(EGraphicCore::main_window);

	glfwSetFramebufferSizeCallback(EGraphicCore::main_window, framebuffer_size_callback);
	glfwSetInputMode(EGraphicCore::main_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	//glfwSetMousePos(0, 0);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		//return -1;
	}

	EGraphicCore::shader_texture_atlas_putter = new Shader("data/#default.vs", "data/#default.fs");
	EGraphicCore::shader_texture_atlas_putter->use();

	EGraphicCore::default_batcher_for_texture_atlas = new Batcher();
	EGraphicCore::default_batcher_for_texture_atlas->set_total_attribute_count(8);
	EGraphicCore::default_batcher_for_texture_atlas->register_new_vertex_attribute(2);//position	| [x][y]
	EGraphicCore::default_batcher_for_texture_atlas->register_new_vertex_attribute(4);//color		| [r][g][b][a]
	EGraphicCore::default_batcher_for_texture_atlas->register_new_vertex_attribute(2);//UV texure	| [U][V]		|




	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, EGraphicCore::SCREEN_WIDTH, EGraphicCore::SCREEN_HEIGHT);
	recalculate_correction();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glBlendEquation(GL_FUNC_ADD);

	EGraphicCore::default_texture_atlas = new ETextureAtlas(4096, 4096);
	EGraphicCore::load_texture("data/textures/white_pixel.png", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, EGraphicCore::texture[0]);

	EGraphicCore::shader_texture_atlas_putter->setInt("texture1", EGraphicCore::texture[0]);

	//EWindow::default_texture_atlas = new ETextureAtlas(4096, 4096);
}

void EGraphicCore::load_texture(char const* _path, int _id)
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

ETextureGabarite* EGraphicCore::put_texture_to_atlas(std::string _full_path, ETextureAtlas* _atlas)
{
	for (int i = 0; i < _full_path.length(); i++)
	{
		if (_full_path[i] == '\\') { _full_path[i] = '/'; }
	}

	ETextureGabarite* duplicate_gabarite = nullptr;

	//search already loaded texture gabarite
	for (ETextureGabarite* g : EGraphicCore::texture_gabarites_list)
	{
		if (g->get_full_path() == _full_path)
		{
			duplicate_gabarite = g;
		}
	}

	ETextureGabarite* new_gabarite = nullptr;

	if (duplicate_gabarite == nullptr)
	{
		EGraphicCore::switch_to_texture_atlas_draw_mode(_atlas);

		EGraphicCore::load_texture(_full_path.c_str(), 0);

		//search free place for new texture
		int place_x = -1;
		int place_y = -1;
		for (int x = 0; x < (int)(_atlas->get_atlas_size_x() / 4.0f); x++)
		{
			for (int y = 0; y < (int)(_atlas->get_atlas_size_y() / 4.0f); y++)
			{
				if (_atlas->can_place_here(x, y, ceil(EGraphicCore::last_texture_width / 4.0f), ceil(EGraphicCore::last_texture_height / 4.0f)))
				{
					place_x = x * 4;
					place_y = y * 4;

					break;
				}

				
			}
			if (place_x >= 0) { break; }
		}
		//
		for (int x = (ceil)(place_x / 4.0f) - 2; x < (ceil)((place_x + EGraphicCore::last_texture_width) / 4.0f) + 2; x++)
		for (int y = (ceil)(place_y / 4.0f) - 2; y < (ceil)((place_y + EGraphicCore::last_texture_height) / 4.0f) + 2; y++)
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

		EGraphicCore::default_batcher_for_texture_atlas->reset();
		EGraphicCore::fill_vertex_buffer_default
		(
			EGraphicCore::default_batcher_for_texture_atlas->vertex_buffer,
			EGraphicCore::default_batcher_for_texture_atlas->last_vertice_buffer_index,
			place_x,
			place_y,
			EGraphicCore::last_texture_width,
			EGraphicCore::last_texture_height
		);
		EGraphicCore::default_batcher_for_texture_atlas->draw_call();

		new_gabarite = new ETextureGabarite();

		if (new_gabarite != nullptr)
		{
			new_gabarite->set_full_path(_full_path);
			new_gabarite->set_name(_full_path.substr(_full_path.size() - 5, 4));

			EInputCore::logger_param("Generate new gabarite", new_gabarite->get_full_path());
			EGraphicCore::texture_gabarites_list.push_back(new_gabarite);
		}

		
	}
	else
	{
		new_gabarite = duplicate_gabarite;
		EInputCore::logger_param("Use existed gabarite", new_gabarite->get_full_path());
	}

	



	return new_gabarite;
}

void EGraphicCore::fill_vertex_buffer_default(float* _array, unsigned int& _start_offset, float _x, float _y, float _w, float _h)
{
	//address arithmetic, get pointer to buffer array, and move to +_offset
	_array += _start_offset;

	//[!][!][!]WARNING![!][!][!] It not "[0][1][2]..." index, it "[_start_offset + 0][_start_offset + 1][_start_offset + 2]..." index, see address arithmetic above
	_array[0] = (_x + _w);
	_array[1] = (_y + _h);

	_array[2] = 1.0f;
	_array[3] = 1.0f;
	_array[4] = 1.0f;
	_array[5] = 1.0f;

	_array[6] = 1.0f;
	_array[7] = 1.0f;

	//..
	//.#
	_array[8] = (_x + _w);
	_array[9] = _y;

	_array[10] = 1.0f;
	_array[11] = 1.0f;
	_array[12] = 1.0f;
	_array[13] = 1.0f;

	_array[14] = 1.0f;
	_array[15] = 0.0f;

	//..
	//#.
	_array[16] = _x;
	_array[17] = _y;

	_array[18] = 1.0f;
	_array[19] = 1.0f;
	_array[20] = 1.0f;
	_array[21] = 1.0f;

	_array[22] = 0.0f;
	_array[23] = 0.0f;

	//#.
	//..
	_array[24] = _x;
	_array[25] = (_y + _h);

	_array[26] = 1.0f;
	_array[27] = 1.0f;
	_array[28] = 1.0f;
	_array[29] = 1.0f;

	_array[30] = 0.0f;
	_array[31] = 1.0f;

	_start_offset += 32;
}






void EGraphicCore::processInput(GLFWwindow* window)
{
}

void EGraphicCore::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{//
	//width = round(width / 2.0f) * 2;
	//height = round(height / 2.0f) * 2;
	//glScissor(0, 0, 500, 500);
	glfwSetWindowSize(EGraphicCore::main_window, width, height);

	glViewport(0, 0, width, height);
	glfwGetWindowSize(window, &EGraphicCore::SCREEN_WIDTH, &EGraphicCore::SCREEN_WIDTH);

	std::cout << "Resize event width:" << EGraphicCore::SCREEN_WIDTH << " height: " << EGraphicCore::SCREEN_WIDTH << std::endl;

	recalculate_correction();
}

void EGraphicCore::recalculate_correction()
{
	if ((EGraphicCore::SCREEN_WIDTH > 100) && (EGraphicCore::SCREEN_HEIGHT > 100))
	{
		EGraphicCore::correction_x = 1.0f / EGraphicCore::SCREEN_WIDTH * 2.0f;
		EGraphicCore::correction_y = 1.0f / EGraphicCore::SCREEN_HEIGHT * 2.0f;

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

void ETextureGabarite::set_name(std::string _name)
{
	*name = _name;
}




