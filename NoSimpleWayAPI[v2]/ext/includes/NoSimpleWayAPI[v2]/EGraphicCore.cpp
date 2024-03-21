#ifndef _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#define _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#include "EGraphicCore.h"
#endif



namespace NS_EGraphicCore
{
	int								old_w, old_h;
	bool							changed_resolution = false;
	int								SCREEN_WIDTH = 1620, SCREEN_HEIGHT = 880;
	float							correction_x = 1.0f, correction_y = 1.0f;
	Shader* shader_texture_atlas_putter;

	glm::mat4						matrix_transform_default;

	ERenderBatcher* default_batcher_for_texture_atlas;
	ERenderBatcher* default_batcher_for_drawing;
	ERenderBatcher* pbr_batcher;
	ERenderBatcher* test_batcher;
	ERenderBatcher* skydome_batcher;

	GLFWwindow* main_window;

	unsigned int					texture[32];

	ETextureAtlas* default_texture_atlas;
	ETextureAtlas* skydome_texture_atlas[texture_skydome_levels];

	unsigned char* image_data;
	unsigned char* zalupa;
	//MidlWinrtTypeSerializationInfoVersionOne	

	int								nrChannels;
	int					texture_loader_width, texture_loader_height,  last_texture_width, last_texture_height;

	//std::vector<ETextureGabarite*>	texture_gabarites_list;
	std::vector <std::vector<ETextureGabarite*>> texture_gabarites_list{ 256 };

	float							delta_time;
	float							saved_time_for_delta;

	float							current_offset_x					= 0.0f;
	float							current_offset_y					= 0.0f;

	float							stored_zoom							= 1.0f;
	float							current_zoom						= 1.0f;


	float							global_normal_multiplier			= 1.0f;

	float							global_free_sky_light_multiplier	= 1.0f;
	float							global_free_sun_light_multiplier	= 1.0f;
	float							global_reflection_multiplier		= 2.0f;

	float							global_gloss_multiplier				= 1.0f;
	float							plastic_or_metal_multiplier			= 1.0f;
	float							sun_x								= 0.5f;
	float							sun_y								= 0.60f;
	float							sun_size							= 0.175f;
	float							sun_blur							= 0.75f;
	float							sun_bright							= 21.000f;
	float							sun_exp								= 3.300f;
	float							ground_level						= 0.475f;
	float							time_total							= 0.00f;
	float							move_multiplier						= 2.35f;
	float							sun_flat_decay						= 0.05f;

	HSVRGBAColor			sun_color;

	EColor_4 active_color[4]{ 1.0f, 1.0f, 1.0f, 1.0f };

	//ETextureAtlas*					default_texture_atlas;

	void processInput(GLFWwindow* window);


	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void recalculate_correction();

	void switch_to_texture_atlas_draw_mode(ETextureAtlas* _atlas);
	void make_transform_from_size(glm::mat4 _transform, float _size_x, float _size_y);

	void initiate_graphic_core();
	//void initiate_sound_core();

	void create_styles();


};

namespace NS_ERenderCollection
{
	float			border_left_size;
	float			border_right_size;
	float			border_up_size;
	float			border_down_size;

	unsigned int	subdivision_x;
	unsigned int	subdivision_y;

	bool			temporary_sprites = false;
}

namespace NS_DefaultGabarites
{
	ETextureGabarite* texture_gabarite_gudron;
	ETextureGabarite* texture_rusted_bronze;
	ETextureGabarite* texture_lead_and_gold;
	ETextureGabarite* texture_lapis_wood;
	ETextureGabarite* texture_black_marble;
	ETextureGabarite* texture_dark_spruce;
	ETextureGabarite* texture_slider_bg_lead_and_gold;
	ETextureGabarite* texture_gabarite_white_pixel;

	ETextureGabarite* texture_gabarite_normal_map_placeholder;
	ETextureGabarite* texture_gabarite_gloss_map_placeholder;
	ETextureGabarite* texture_gabarite_skydome;

	ETextureGabarite* texture_bool_switcher_activated_box;
	ETextureGabarite* texture_bool_switcher_deactivated_box;

	ETextureGabarite* texture_bool_switcher_force_field_on;
	ETextureGabarite* texture_bool_switcher_force_field_off;

	ETextureGabarite* texture_button_radiance;
	ETextureGabarite* texture_button_radiance_dot;

	ETextureGabarite* texture_close_circle;

	ETextureGabarite* texture_socket;
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
	if ((last_vertice_buffer_index > 0) && (batcher_shader != nullptr))
	{


		batcher_shader->use();
		apply_transform();

		//batcher_shader->setInt("texture1", 0);
		
		
		if
		(
			(gl_vertex_attribute_total_count > 12)
			//&&
			//(EInputCore::key_pressed_once(GLFW_KEY_LEFT_SHIFT))
		)
		{
			glActiveTexture(GL_TEXTURE0);
			//NS_EGraphicCore::gl_set_texture_filtering(GL_CLAMP_TO_EDGE, GL_NEAREST);

			
			NS_EGraphicCore::pbr_batcher->get_shader()->setInt("texture1", 0);
			//BASE TEXTURE ATLAS
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);//texture filtering
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glBindTexture(GL_TEXTURE_2D, NS_EGraphicCore::default_texture_atlas->get_colorbuffer());

			//SKYDOMES
			for (int i = 0; i < texture_skydome_levels; i++)
			{


				glActiveTexture(GL_TEXTURE1 + i);
				

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);//texture filtering
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
				//NS_EGraphicCore::gl_set_texture_filtering(GL_CLAMP, GL_NEAREST);
				glBindTexture(GL_TEXTURE_2D, NS_EGraphicCore::skydome_texture_atlas[i]->get_colorbuffer());//1
				NS_EGraphicCore::pbr_batcher->get_shader()->setInt("SD_array[" + std::to_string(i) + "]", i + 1);
			}

			//NS_EGraphicCore::pbr_batcher->get_shader()->setInt("SD_array[0]", 0);

			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("normal_map_multiplier", round(NS_EGraphicCore::global_normal_multiplier * 50.0f) / 50.0f);
			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("gloss_map_multiplier", NS_EGraphicCore::global_gloss_multiplier);
			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("plastic_or_metal_multiplier", NS_EGraphicCore::plastic_or_metal_multiplier);

			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("sun_position_x", NS_EGraphicCore::sun_x);
			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("sun_position_y", NS_EGraphicCore::sun_y);
			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("sun_size", NS_EGraphicCore::sun_size);
			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("sun_blur", NS_EGraphicCore::sun_blur);
			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("sun_bright", NS_EGraphicCore::sun_bright);
			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("sun_exp", NS_EGraphicCore::sun_exp);
			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("sun_flat_decay", NS_EGraphicCore::sun_flat_decay);

			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("ground_level", NS_EGraphicCore::ground_level);

			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("scr_x", NS_EGraphicCore::SCREEN_WIDTH);
			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("scr_y", NS_EGraphicCore::SCREEN_HEIGHT);

			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("time", NS_EGraphicCore::time_total);
			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("move_multiplier", NS_EGraphicCore::move_multiplier);

			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("free_sky_light", NS_EGraphicCore::global_free_sky_light_multiplier);
			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("free_sun_light", NS_EGraphicCore::global_free_sun_light_multiplier);
			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("reflection_multiplier", NS_EGraphicCore::global_reflection_multiplier);

			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("sun_light_gloss[0]", 1.0f);
			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("sun_light_gloss[1]", 0.2f);
			NS_EGraphicCore::pbr_batcher->get_shader()->setFloat("sun_light_gloss[2]", 0.1f);

			glm::vec3 v
			(
				NS_EGraphicCore::sun_color.r,
				NS_EGraphicCore::sun_color.g,
				NS_EGraphicCore::sun_color.b
			);

			GLuint focusLoc = glGetUniformLocation(NS_EGraphicCore::pbr_batcher->get_shader()->ID, "sun_light_gloss_color");
			glUniform3fv(focusLoc, 1, &v[0]);
		}

		glBindBuffer(GL_ARRAY_BUFFER, VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * last_vertice_buffer_index, &vertex_buffer, GL_STREAM_DRAW);

		//							 6 indices																  4 vertex to form shape
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

	NS_EGraphicCore::matrix_transform_default = glm::scale
	(
		NS_EGraphicCore::matrix_transform_default, glm::vec3
		(
			2.0f / transform_screen_size_x,
			2.0f / transform_screen_size_y,
			1.0f
		)
	);

	unsigned int transformLoc = glGetUniformLocation(batcher_shader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(NS_EGraphicCore::matrix_transform_default));

	unsigned int zoom_loc = glGetUniformLocation(batcher_shader->ID, "zoom");
	glUniform1f(zoom_loc, NS_EGraphicCore::current_zoom);
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

bool ERenderBatcher::check_batcher(ERenderBatcher* _batcher, unsigned int _add)
{
	if (_batcher->last_vertice_buffer_index + _add >= _batcher->gl_vertex_attribute_total_count * VERTICES_PER_SHAPE * MAX_SHAPES_COUNT)
	{
		_batcher->draw_call();
		return false;
	}

	return true;
}

bool ERenderBatcher::if_have_space_for_data(ERenderBatcher* _batcher, unsigned int _add)
{
	return check_batcher(_batcher, _batcher->gl_vertex_attribute_total_count * VERTICES_PER_SHAPE * _add);
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

ETextureAtlas::ETextureAtlas(int _size_x, int _size_y, int _color_depth, int _byte_mode)
{
	*atlas_size_x = _size_x;
	*atlas_size_y = _size_y;

	//////////////////////////////
	glGenTextures(1, colorbuffer);
	glBindTexture(GL_TEXTURE_2D, *colorbuffer);
	EInputCore::logger_param("[texture atlas] texture created", *colorbuffer);

	glGenFramebuffers(1, framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, *framebuffer);
	EInputCore::logger_param("[texture atlas] framebuffer created", *framebuffer);



	glTexImage2D(GL_TEXTURE_2D, 0, _color_depth, _size_x, _size_y, 0, GL_RGBA, _byte_mode, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *colorbuffer, 0);

	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now



	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
	NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_WHITE);
	glViewport(0, 0, _atlas->get_atlas_size_x(), _atlas->get_atlas_size_y());
	glBindFramebuffer(GL_FRAMEBUFFER, _atlas->get_framebuffer());

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendEquation(GL_MAX);

	//back blend mode
	//glEnable(GL_BLEND);
	//glBlendFuncSeparate(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);
	//glBlendEquation(GL_FUNC_ADD);

	//normal blend mode
	//glEnable(GL_BLEND);
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);
	//glBlendEquation(GL_FUNC_ADD);

	//make_transform_from_size(NS_EGraphicCore::default_batcher_for_texture_atlas, _atlas->get_atlas_size_x(), _atlas->get_atlas_size_y());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, NS_EGraphicCore::texture[0]);

	//default_batcher_for_texture_atlas->set_active_color(NS_EColorUtils::COLOR_WHITE);
}

void NS_EGraphicCore::make_transform_from_size(ERenderBatcher* _batcher, float _size_x, float _size_y)
{
	NS_EGraphicCore::matrix_transform_default = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	NS_EGraphicCore::matrix_transform_default = glm::translate(NS_EGraphicCore::matrix_transform_default, glm::vec3(-1.0f, -1.0f, 0.0f));
	NS_EGraphicCore::matrix_transform_default = glm::scale(NS_EGraphicCore::matrix_transform_default, glm::vec3(1.0f / _size_x * 2.0f, 1.0f / _size_y * 2.0f, 1.0f));


}

void NS_EGraphicCore::switch_to_this_FBO(ETextureAtlas* _atlas)
{
	NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_WHITE);
	glViewport(0, 0, _atlas->get_atlas_size_x(), _atlas->get_atlas_size_y());
	glBindFramebuffer(GL_FRAMEBUFFER, _atlas->get_framebuffer());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, NS_EGraphicCore::texture[0]);
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
	//glfwWindowHint(GLFW_SAMPLES, 1);

	

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	//glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	//glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	//glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	//glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	//glfwWindowHint(GLFW_DECORATED, NULL);

	NS_EGraphicCore::main_window = glfwCreateWindow(NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT, "Awakened DaDEditor", NULL, NULL);
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



	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glBlendEquation(GL_FUNC_ADD);



	GLint max_tex_size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_tex_size);

	NS_EGraphicCore::default_texture_atlas = new ETextureAtlas(min(max_tex_size, 8192), min(8192 / 2, max_tex_size));
	
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

	default_batcher_for_drawing->register_new_vertex_attribute(2);	//position		1[x]	2[y]	#		#
	default_batcher_for_drawing->register_new_vertex_attribute(4);	//color			1[r]	2[g]	3[b]	4[a]
	default_batcher_for_drawing->register_new_vertex_attribute(2);	//uv texture	1[u]	2[v]	#		#

	default_batcher_for_drawing->set_shader(new Shader("data/#default.vs", "data/#default.fs"));
	//total
	//8 floats, * 4 byte(per float) = 32 byte per vertex ===32*4 (128) bytes per shape
	//[x][y][r][g][b][a][u][v]

	pbr_batcher = new ERenderBatcher();				//|1 |2 |3 |4 |5 |6 |7 |8 |9 |10|11|12|13|
	pbr_batcher->set_total_attribute_count(13);		//[x][y][z][r][g][b][a][u][v][u][v][u][v]

	pbr_batcher->register_new_vertex_attribute(3);	//position			1[x]	2[y]	3[z]	#
	pbr_batcher->register_new_vertex_attribute(4);	//color				1[r]	2[g]	3[b]	4[a]
	pbr_batcher->register_new_vertex_attribute(2);	//uv texture		1[u]	2[v]	#		#
	pbr_batcher->register_new_vertex_attribute(2);	//normal map		1[u]	2[v]	#		#
	pbr_batcher->register_new_vertex_attribute(2);	//gloss map			1[u]	2[v]	#		#

	pbr_batcher->set_shader(new Shader("data/PBR.vs", "data/PBR.fs"));



	test_batcher = new ERenderBatcher();				//|1 |2 |3 |4 |5 |6 |7 |8 |9 |10|11|12|13|
	test_batcher->set_total_attribute_count(12);		//[x][y][z][r][g][b][a][u][v][u][v][u][v]

	test_batcher->register_new_vertex_attribute(3);	//position			1[x]	2[y]	3[z]	#
	test_batcher->register_new_vertex_attribute(4);	//color				1[r]	2[g]	3[b]	4[a]
	test_batcher->register_new_vertex_attribute(2);	//uv texture		1[u]	2[v]	#		#
	test_batcher->register_new_vertex_attribute(2);	//uv texture		1[u]	2[v]	#		#
	test_batcher->register_new_vertex_attribute(2);	//uv texture		1[u]	2[v]	#		#

	test_batcher->set_shader(new Shader("data/#test.vs", "data/#test.fs"));
	//total
	//13 floats, * 4 byte(per float) = 32 byte per vertex ===32*4 (128) bytes per shape


	//pbr_skydbatcher = new ERenderBatcher();			//|1 |2 |3 |4 |5 |6 |7 |8 |9 |10|11|12|13|
	skydome_batcher = new ERenderBatcher();				//|1 |2 |3 |4 |5 |6 |7 |8 |9 |10|11|12|13|
	skydome_batcher->set_total_attribute_count(8);		//[x][y][z][r][g][b][a][u][v][u][v][u][v]

	skydome_batcher->register_new_vertex_attribute(2);	//position			1[x]	2[y]	#		#
	skydome_batcher->register_new_vertex_attribute(4);	//color				1[r]	2[g]	3[b]	4[a]
	skydome_batcher->register_new_vertex_attribute(2);	//uv texture		1[u]	2[v]	#		#

	skydome_batcher->set_shader(new Shader("data/simple_blur.vs", "data/simple_blur.fs"));
	NS_EGraphicCore::skydome_batcher->set_transform_screen_size(1.0f, 1.0f);

	glViewport(0, 0, NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT);
	recalculate_correction();

	

	NS_DefaultGabarites::texture_gabarite_normal_map_placeholder = NS_EGraphicCore::put_texture_to_atlas("data/textures/normal_map_placeholder.png", NS_EGraphicCore::default_texture_atlas);
	NS_DefaultGabarites::texture_gabarite_gloss_map_placeholder = NS_EGraphicCore::put_texture_to_atlas("data/textures/gloss_map_placeholder.png", NS_EGraphicCore::default_texture_atlas);

	NS_DefaultGabarites::texture_gabarite_white_pixel = NS_EGraphicCore::put_texture_to_atlas("data/textures/white_pixel.png", NS_EGraphicCore::default_texture_atlas);


	//NS_DefaultGabarites::texture_gabarite_gudron				= NS_EGraphicCore::put_texture_to_atlas("data/textures/gudron_roof.png", NS_EGraphicCore::default_texture_atlas);
	//NS_DefaultGabarites::texture_rusted_bronze				= NS_EGraphicCore::put_texture_to_atlas("data/textures/Rusted_bronze.png", NS_EGraphicCore::default_texture_atlas);
	//NS_DefaultGabarites::texture_lead_and_gold				= NS_EGraphicCore::put_texture_to_atlas("data/textures/styles/lead_and_gold/Group_bg.png", NS_EGraphicCore::default_texture_atlas);
	//NS_DefaultGabarites::texture_black_marble					= NS_EGraphicCore::put_texture_to_atlas("data/textures/Black_marble.png", NS_EGraphicCore::default_texture_atlas);
//	NS_DefaultGabarites::texture_dark_spruce					= NS_EGraphicCore::put_texture_to_atlas("data/textures/Dark_spruce.png", NS_EGraphicCore::default_texture_atlas);
	//NS_DefaultGabarites::texture_dark_spruce					= NS_EGraphicCore::put_texture_to_atlas("data/textures/styles/dark_spruce/Group_bg.png", NS_EGraphicCore::default_texture_atlas);
	//NS_DefaultGabarites::texture_lapis_wood					= NS_EGraphicCore::put_texture_to_atlas("data/textures/Lapis_wood.png", NS_EGraphicCore::default_texture_atlas);

	NS_DefaultGabarites::texture_gabarite_skydome				= NS_EGraphicCore::put_texture_to_atlas("data/textures/skydome_city.png",			NS_EGraphicCore::default_texture_atlas);
	NS_EGraphicCore::complete_texture_gabarite(NS_DefaultGabarites::texture_gabarite_skydome);

	NS_DefaultGabarites::texture_bool_switcher_activated_box	= NS_EGraphicCore::put_texture_to_atlas("data/textures/buttons/box_switcher_on.png",		NS_EGraphicCore::default_texture_atlas);
	NS_DefaultGabarites::texture_bool_switcher_deactivated_box	= NS_EGraphicCore::put_texture_to_atlas("data/textures/buttons/box_switcher_off.png",		NS_EGraphicCore::default_texture_atlas);
	
	NS_DefaultGabarites::texture_bool_switcher_force_field_on	= NS_EGraphicCore::put_texture_to_atlas("data/textures/buttons/force_field_for_separator_on.png",		NS_EGraphicCore::default_texture_atlas);
	NS_DefaultGabarites::texture_bool_switcher_force_field_off	= NS_EGraphicCore::put_texture_to_atlas("data/textures/buttons/force_field_for_separator_off.png",		NS_EGraphicCore::default_texture_atlas);
	
	NS_DefaultGabarites::texture_button_radiance				= NS_EGraphicCore::put_texture_to_atlas("data/textures/buttons/radiance_button.png",		NS_EGraphicCore::default_texture_atlas);
	NS_DefaultGabarites::texture_button_radiance_dot			= NS_EGraphicCore::put_texture_to_atlas("data/textures/buttons/radiance_button_dot.png",	NS_EGraphicCore::default_texture_atlas);
	//NS_DefaultGabarites::texture_slider_bg_lead_and_gold				= NS_EGraphicCore::put_texture_to_atlas("data/textures/slider_bg_lead_and_gold.png", NS_EGraphicCore::default_texture_atlas);

	NS_DefaultGabarites::texture_close_circle					= NS_EGraphicCore::load_from_textures_folder("close_circle");
	

	NS_DefaultGabarites::texture_socket							= NS_EGraphicCore::load_from_textures_folder("socket");
	//[0]2048(1024)
	//[1]1024
	//[2]512
	//[3]256
	//[4]128
	//[5]64
	//[6]64
	//
	for (int i = 0; i < texture_skydome_levels; i++)
	{
		NS_EGraphicCore::skydome_texture_atlas[i]
		=
		new ETextureAtlas
		(
			std::clamp(int(2048 / (pow(2.0, i * 1))), 64, 1024)
			,
			std::clamp(int(2048 / (pow(2.0, i * 1))), 64, 1024)
		);
	}

	make_skydome_textures(NS_DefaultGabarites::texture_gabarite_skydome);

	//STYLE LIST//
	create_styles();

	//font
	EFont* new_font = NULL;
	ETextureGabarite* font_gabarite = nullptr;

	font_gabarite = NS_EGraphicCore::put_texture_to_atlas("data/font/palatino_0.png", NS_EGraphicCore::default_texture_atlas);
	new_font = new EFont("palatino", font_gabarite, NS_EGraphicCore::default_texture_atlas, false);
	EFont::font_list.push_back(new_font);

	font_gabarite = NS_EGraphicCore::put_texture_to_atlas("data/font/fontin_0.png", NS_EGraphicCore::default_texture_atlas);
	new_font = new EFont("fontin", font_gabarite, NS_EGraphicCore::default_texture_atlas, false);
	EFont::font_list.push_back(new_font);

	//NS_EGraphicCore::sun_color = Helper::hsvrgba_color;
	NS_EGraphicCore::sun_color.r = 1.0f;
	NS_EGraphicCore::sun_color.g = 0.6f;
	NS_EGraphicCore::sun_color.b = 0.277f;

	NS_EGraphicCore::sun_color.a = 1.0f;

	NS_EGraphicCore::sun_color.is_from_collection = false;

	Helper::rgb2hsv(&NS_EGraphicCore::sun_color);

	glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
}

//void NS_EGraphicCore::initiate_sound_core()
//{
//
//}

void NS_EGraphicCore::create_styles()
{
	//*******************************

	EGUIStyle* just_created_style = nullptr;
	EBrickStyle* jc_brick = nullptr;

	ELocalisationText l_text;
	//lead and gold
	if (true)
	{


		just_created_style = new EGUIStyle("lead_and_gold");
		l_text.base_name = "lead_and_gold";
		l_text.localisations[NSW_localisation_EN] = "Lead and Gold";
		l_text.localisations[NSW_localisation_RU] = "Ñâèíåö è Çîëîòî";
		just_created_style->localisation_text = l_text;

		//***********************************************************
		//main gutton group
		/*just_created_style->set_color_array(TextColorArray::WHITE,	0.9f,	0.85f,	0.6f,	1.0f);
		just_created_style->set_color_array(TextColorArray::GRAY,		0.7f,	0.68f,	0.65f,	1.0f);
		just_created_style->set_color_array(TextColorArray::BLACK,		0.5f,	0.48f,	0.46f,	1.0f);
		just_created_style->set_color_array(TextColorArray::RED,		1.0f,	0.3f,	0.15f,	1.0f);
		just_created_style->set_color_array(TextColorArray::ORANGE,		1.0f,	0.50f,	0.10f,	1.0f);
		just_created_style->set_color_array(TextColorArray::YELLOW,		1.0f,	0.90f,	0.20f,	1.0f);
		just_created_style->set_color_array(TextColorArray::GREEN,		1.0f,	0.20f,	0.10f,	1.0f);
		just_created_style->set_color_array(TextColorArray::CYAN,		0.2f,	1.0f,	0.9f,	1.0f);
		just_created_style->set_color_array(TextColorArray::BLUE,		0.2f,	1.0f,	0.9f,	1.0f);
		just_created_style->set_color_array(TextColorArray::MAGENTA,	1.0f,	0.2f,	0.9f,	1.0f);*/

		//just_created_style->text_color_multiplier = 0.0f, 0.0f, 0.0f, 0.0f;

		just_created_style->set_color_multiplier(0.9f, 0.85f, 0.6f, 1.0f);
		EBrickStyle* jc_brick = new EBrickStyle("Group_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_offset_size(jc_brick, 5.0f, 5.0f, 5.0f, 5.0f);
		EBrickStyle::set_subdivisions(jc_brick, 2, 2);

		just_created_style->brick_style[BrickStyleID::GROUP_DEFAULT] = *jc_brick;

		//***********************************************************
		//darken gutton group
		jc_brick = new EBrickStyle("Root_group_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 7.0f, 7.0f, 7.0f, 7.0f);
		EBrickStyle::set_offset_size(jc_brick, 10.0f, 10.0f, 10.0f, 10.0f);
		EBrickStyle::set_subdivisions(jc_brick, 2, 2);

		just_created_style->brick_style[BrickStyleID::GROUP_DARKEN] = *jc_brick;
		//***********************************************************
		//slider bg
		jc_brick = new EBrickStyle("Slider_bg");
		jc_brick->parent_style = just_created_style;
	
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 4.0f, 4.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 4.0f, 4.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_BG] = *jc_brick;
		//***********************************************************
		//slider head inactive
		jc_brick = new EBrickStyle("Slider_head_inactive");
		jc_brick->parent_style = just_created_style;
	
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_INACTIVE] = *jc_brick;
		//***********************************************************
		//slider head active
		jc_brick = new EBrickStyle("Slider_head_active");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_ACTIVE] = *jc_brick;
		//***********************************************************
		//slider head round
		jc_brick = new EBrickStyle("Slider_head_round");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::ROUND_SLIDER] = *jc_brick;
		//***********************************************************
		//button background
		jc_brick = new EBrickStyle("Button_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_offset_size(jc_brick, 4.0f, 4.0f, 4.0f, 4.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::BUTTON_BG] = *jc_brick;




		EGUIStyle::active_style = just_created_style;
		EGUIStyle::style_list.push_back(just_created_style);
	}


	//*******************************
	//dark spruce
	if (true)
	{
		just_created_style = new EGUIStyle("dark_spruce");
		l_text.base_name = "dark_spruce";
		l_text.localisations[NSW_localisation_EN] = "Dark spruce";
		l_text.localisations[NSW_localisation_RU] = "Ò¸ìíàÿ åëü";
		just_created_style->localisation_text = l_text;
		//***********************************************************
		//main gutton group
		just_created_style->set_color_multiplier(0.9f, 0.85f, 0.8f, 1.0f);

		jc_brick = new EBrickStyle("Group_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 7.0f, 7.0f, 7.0f, 7.0f);
		EBrickStyle::set_offset_size(jc_brick, 10.0f, 10.0f, 10.0f, 10.0f);
		EBrickStyle::set_subdivisions(jc_brick, 8, 0);

		just_created_style->brick_style[BrickStyleID::GROUP_DEFAULT] = *jc_brick;

		//***********************************************************
		//darken gutton group
		jc_brick = new EBrickStyle("Root_group_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 6.0f, 6.0f, 6.0f, 6.0f);
		EBrickStyle::set_offset_size(jc_brick, 6.0f, 6.0f, 6.0f, 6.0f);
		EBrickStyle::set_subdivisions(jc_brick, 3, 0);

		just_created_style->brick_style[BrickStyleID::GROUP_DARKEN] = *jc_brick;

		//***********************************************************
		//slider bg
		jc_brick = new EBrickStyle("Slider_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 4.0f, 4.0f, 4.0f, 4.0f);
		EBrickStyle::set_offset_size(jc_brick, 4.0f, 4.0f, 4.0f, 4.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_BG] = *jc_brick;
		//***********************************************************
		//slider head inactive
		jc_brick = new EBrickStyle("Slider_head_inactive");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_INACTIVE] = *jc_brick;

		//***********************************************************
		//slider head active
		jc_brick = new EBrickStyle("Slider_head_active");
		jc_brick->parent_style = just_created_style;
	
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_ACTIVE] = *jc_brick;
		//***********************************************************
		//slider head round
		jc_brick = new EBrickStyle("Slider_head_round");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::ROUND_SLIDER] = *jc_brick;
		//***********************************************************
		//button background
		jc_brick = new EBrickStyle("Button_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::BUTTON_BG] = *jc_brick;

		EGUIStyle::style_list.push_back(just_created_style);
	}

	//###########################################################
	//GRAY MINIMALISM
	if (true)
	{
		just_created_style = new EGUIStyle("gray_minimalism");
		l_text.base_name = "gray_minimalism";
		l_text.localisations[NSW_localisation_EN] = "Strict gray";
		l_text.localisations[NSW_localisation_RU] = "Ñòðîãèé ñåðûé";
		just_created_style->localisation_text = l_text;
		//***********************************************************
		//main gutton group
		jc_brick = new EBrickStyle("Group_bg");
		jc_brick->parent_style = just_created_style;
	
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 4.0f, 4.0f, 4.0f, 4.0f);
		EBrickStyle::set_offset_size(jc_brick, 5.0f, 5.0f, 5.0f, 5.0f);
		EBrickStyle::set_subdivisions(jc_brick, 1, 1);

		just_created_style->brick_style[BrickStyleID::GROUP_DEFAULT] = *jc_brick;

		//***********************************************************
		//darken gutton group
		jc_brick = new EBrickStyle("Root_group_bg");
		jc_brick->parent_style = just_created_style;
	
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 5.0f, 5.0f, 5.0f, 5.0f);
		EBrickStyle::set_offset_size(jc_brick, 5.0f, 5.0f, 5.0f, 5.0f);
		EBrickStyle::set_subdivisions(jc_brick, 1, 1);

		just_created_style->brick_style[BrickStyleID::GROUP_DARKEN] = *jc_brick;
		//***********************************************************
		//slider bg
		jc_brick = new EBrickStyle("Slider_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_BG] = *jc_brick;
		//***********************************************************
		//slider head inactive
		jc_brick = new EBrickStyle("Slider_head_inactive");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_INACTIVE] = *jc_brick;
		//***********************************************************
		//slider head active
		jc_brick = new EBrickStyle("Slider_head_active");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_ACTIVE] = *jc_brick;
		//***********************************************************
		//button background
		jc_brick = new EBrickStyle("Button_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::BUTTON_BG] = *jc_brick;
		//***********************************************************
		//slider head round
		jc_brick = new EBrickStyle("Slider_head_round");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::ROUND_SLIDER] = *jc_brick;

		EGUIStyle::style_list.push_back(just_created_style);
	}

	//stone
	if (false)
	{
		//###########################################################
		//STONE CASTLE
		just_created_style = new EGUIStyle("stone_castle");
		l_text.base_name = "stone_castle";
		l_text.localisations[NSW_localisation_EN] = "Stone castle";
		l_text.localisations[NSW_localisation_RU] = "Êàìåííûé çàìîê";
		just_created_style->localisation_text = l_text;
		//***********************************************************
		//main gutton group
		jc_brick = new EBrickStyle("Group_bg");
		jc_brick->parent_style = just_created_style;
	
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_offset_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_subdivisions(jc_brick, 2, 0);

		just_created_style->brick_style[BrickStyleID::GROUP_DEFAULT] = *jc_brick;
		//***********************************************************
		//darken gutton group
		jc_brick = new EBrickStyle("Root_group_bg");
		jc_brick->parent_style = just_created_style;
	
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 11.0f, 11.0f, 11.0f, 18.0f);
		EBrickStyle::set_offset_size(jc_brick, 7.0f, 7.0f, 6.0f, 4.0f);
		EBrickStyle::set_subdivisions(jc_brick, 2, 2);

		just_created_style->brick_style[BrickStyleID::GROUP_DARKEN] = *jc_brick;

		//***********************************************************
		//slider bg
		jc_brick = new EBrickStyle("Slider_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_BG] = *jc_brick;
		//***********************************************************
		//slider head inactive
		jc_brick = new EBrickStyle("Slider_head_inactive");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_INACTIVE] = *jc_brick;
		//***********************************************************
		//slider head active
		jc_brick = new EBrickStyle("Slider_head_active");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_ACTIVE] = *jc_brick;
		//***********************************************************
		//button background
		jc_brick = new EBrickStyle("Button_bg");
		jc_brick->parent_style = just_created_style;
	
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::BUTTON_BG] = *jc_brick;

		EGUIStyle::style_list.push_back(just_created_style);
	}

	//neon
	if (false)
	{
		//###########################################################
		//NEON VEIN
		just_created_style = new EGUIStyle("neon_vein");
		l_text.base_name = "neon_vein";
		l_text.localisations[NSW_localisation_EN] = "Neon vein";
		l_text.localisations[NSW_localisation_RU] = "Íåîíîâàÿ æèëà";
		just_created_style->localisation_text = l_text;
		//***********************************************************
		//main gutton group
		jc_brick = new EBrickStyle("Group_bg");
		jc_brick->parent_style = just_created_style;
	
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 4.0f, 4.0f, 4.0f, 4.0f);
		EBrickStyle::set_offset_size(jc_brick, 4.0f, 4.0f, 4.0f, 4.0f);
		EBrickStyle::set_subdivisions(jc_brick, 3, 2);

		just_created_style->brick_style[BrickStyleID::GROUP_DEFAULT] = *jc_brick;
		//***********************************************************
		//darken gutton group
		jc_brick = new EBrickStyle("Root_group_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 4.0f, 4.0f, 4.0f, 4.0f);
		EBrickStyle::set_offset_size(jc_brick, 4.0f, 4.0f, 4.0f, 4.0f);
		EBrickStyle::set_subdivisions(jc_brick, 3, 2);

		just_created_style->brick_style[BrickStyleID::GROUP_DARKEN] = *jc_brick;
		//***********************************************************
		//slider bg
		jc_brick = new EBrickStyle("Slider_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 4.0f, 4.0f, 4.0f, 4.0f);
		EBrickStyle::set_offset_size(jc_brick, 4.0f, 4.0f, 4.0f, 4.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_BG] = *jc_brick;
		//***********************************************************
		//slider head inactive
		jc_brick = new EBrickStyle("Slider_head_inactive");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_INACTIVE] = *jc_brick;
		//***********************************************************
		//slider head active
		jc_brick = new EBrickStyle("Slider_head_active");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_ACTIVE] = *jc_brick;
		//***********************************************************
		//button background
		jc_brick = new EBrickStyle("Button_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::BUTTON_BG] = *jc_brick;

		EGUIStyle::style_list.push_back(just_created_style);
	}




	//modern
	if (false)
	{
		//###########################################################
		//MODERN
		just_created_style = new EGUIStyle("modern");
		l_text.base_name = "modern";
		l_text.localisations[NSW_localisation_EN] = "Modern";
		l_text.localisations[NSW_localisation_RU] = "Ìîäåðí";
		just_created_style->localisation_text = l_text;
		//***********************************************************
		//main gutton group
		just_created_style->set_color_multiplier(0.3f, 0.35f, 0.3f, 1.0f);

		jc_brick = new EBrickStyle("Group_bg");
		jc_brick->parent_style = just_created_style;
	
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_offset_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::GROUP_DEFAULT] = *jc_brick;
		//***********************************************************
		//darken gutton group
		jc_brick = new EBrickStyle("Root_group_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_offset_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::GROUP_DARKEN] = *jc_brick;
		//***********************************************************
		//slider bg
		jc_brick = new EBrickStyle("Slider_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 0.0f, 0.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 0.0f, 0.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_BG] = *jc_brick;
		//***********************************************************
		//slider head inactive
		jc_brick = new EBrickStyle("Slider_head_inactive");
		jc_brick->parent_style = just_created_style;
	
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 0.0f, 0.0f, 0.0f, 0.0f);
		EBrickStyle::set_offset_size(jc_brick, 0.0f, 0.0f, 0.0f, 0.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_INACTIVE] = *jc_brick;
		//***********************************************************
		//slider head active
		jc_brick = new EBrickStyle("Slider_head_active");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 0.0f, 0.0f, 0.0f, 0.0f);
		EBrickStyle::set_offset_size(jc_brick, 0.0f, 0.0f, 0.0f, 0.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_ACTIVE] = *jc_brick;
		//***********************************************************
		//button background
		jc_brick = new EBrickStyle("Button_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 5.0f, 5.0f, 6.0f, 3.0f);
		EBrickStyle::set_offset_size(jc_brick, 5.0f, 5.0f, 6.0f, 3.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::BUTTON_BG] = *jc_brick;

		EGUIStyle::style_list.push_back(just_created_style);
	}

	//red velvet
	if (false)
	{
		//###########################################################
		//MODERN
		just_created_style = new EGUIStyle("red_velvet");
		l_text.base_name = "red_velvet";
		l_text.localisations[NSW_localisation_EN] = "Red velvet";
		l_text.localisations[NSW_localisation_RU] = "Êðàñíûé áàðõàò";
		just_created_style->localisation_text = l_text;
		//***********************************************************
		//main gutton group
		//just_created_style->set_color_multiplier(0.3f, 0.35f, 0.3f, 1.0f);
		just_created_style->set_color_multiplier(0.9f, 0.85f, 0.6f, 1.0f);

		jc_brick = new EBrickStyle("Group_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 4.0f, 4.0f, 4.0f, 4.0f);
		EBrickStyle::set_offset_size(jc_brick, 4.0f, 4.0f, 4.0f, 4.0f);
		EBrickStyle::set_subdivisions(jc_brick, 2, 2);

		just_created_style->brick_style[BrickStyleID::GROUP_DEFAULT] = *jc_brick;
		//***********************************************************
		//darken gutton group
		jc_brick = new EBrickStyle("Root_group_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_offset_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::GROUP_DARKEN] = *jc_brick;
		//***********************************************************
		//slider bg
		jc_brick = new EBrickStyle("Slider_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 3.0f, 3.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 3.0f, 3.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_BG] = *jc_brick;
		//***********************************************************
		//slider head inactive
		jc_brick = new EBrickStyle("Slider_head_inactive");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 0.0f, 0.0f, 0.0f, 0.0f);
		EBrickStyle::set_offset_size(jc_brick, 0.0f, 0.0f, 0.0f, 0.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_INACTIVE] = *jc_brick;
		//***********************************************************
		//slider head active
		jc_brick = new EBrickStyle("Slider_head_active");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 0.0f, 0.0f, 0.0f, 0.0f);
		EBrickStyle::set_offset_size(jc_brick, 0.0f, 0.0f, 0.0f, 0.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_ACTIVE] = *jc_brick;
		//***********************************************************
		//button background
		jc_brick = new EBrickStyle("Button_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 1, 1);

		just_created_style->brick_style[BrickStyleID::BUTTON_BG] = *jc_brick;

		EGUIStyle::style_list.push_back(just_created_style);
	}


	//gasoline
	if (false)
	{
		//###########################################################
		//MODERN
		just_created_style = new EGUIStyle("gasoline_stains");
		l_text.base_name = "gasoline_stains";
		l_text.localisations[NSW_localisation_EN] = "Gasoline stains";
		l_text.localisations[NSW_localisation_RU] = "Ïÿòíàÿ áåíçèíà";
		just_created_style->localisation_text = l_text;
		//***********************************************************
		//main gutton group
		//just_created_style->set_color_multiplier(0.3f, 0.35f, 0.3f, 1.0f);
		just_created_style->set_color_multiplier(0.9f, 0.85f, 0.6f, 1.0f);

		jc_brick = new EBrickStyle("Group_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 5.0f, 5.0f, 5.0f, 5.0f);
		EBrickStyle::set_offset_size(jc_brick, 5.0f, 5.0f, 5.0f, 5.0f);
		EBrickStyle::set_subdivisions(jc_brick, 3, 3);

		just_created_style->brick_style[BrickStyleID::GROUP_DEFAULT] = *jc_brick;
		//***********************************************************
		//darken gutton group
		jc_brick = new EBrickStyle("Root_group_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_offset_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::GROUP_DARKEN] = *jc_brick;
		//***********************************************************
		//slider bg
		jc_brick = new EBrickStyle("Slider_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 3.0f, 3.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 3.0f, 3.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_BG] = *jc_brick;
		//***********************************************************
		//slider head inactive
		jc_brick = new EBrickStyle("Slider_head_inactive");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 0.0f, 0.0f, 0.0f, 0.0f);
		EBrickStyle::set_offset_size(jc_brick, 0.0f, 0.0f, 0.0f, 0.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_INACTIVE] = *jc_brick;
		//***********************************************************
		//slider head active
		jc_brick = new EBrickStyle("Slider_head_active");
		jc_brick->parent_style = just_created_style;

		just_created_style->brick_style[BrickStyleID::SLIDER_ACTIVE] = *jc_brick;
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 0.0f, 0.0f, 0.0f, 0.0f);
		EBrickStyle::set_offset_size(jc_brick, 0.0f, 0.0f, 0.0f, 0.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		//***********************************************************
		//button background
		jc_brick = new EBrickStyle("Button_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 1, 1);

		just_created_style->brick_style[BrickStyleID::BUTTON_BG] = *jc_brick;

		EGUIStyle::style_list.push_back(just_created_style);
	}

	//lines
	if (false)
	{
		//###########################################################
		//MODERN
		just_created_style = new EGUIStyle("lines");
		l_text.base_name = "lines";
		l_text.localisations[NSW_localisation_EN] = "Lines";
		l_text.localisations[NSW_localisation_RU] = "Ëèíèè";
		just_created_style->localisation_text = l_text;
		//***********************************************************
		//main gutton group
		//just_created_style->set_color_multiplier(0.3f, 0.35f, 0.3f, 1.0f);
		just_created_style->set_color_multiplier(0.9f, 0.85f, 0.6f, 1.0f);

		jc_brick = new EBrickStyle("Group_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_offset_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_subdivisions(jc_brick, 3, 3);

		just_created_style->brick_style[BrickStyleID::GROUP_DEFAULT] = *jc_brick;
		//***********************************************************
	//darken gutton group
		jc_brick = new EBrickStyle("Root_group_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_offset_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_subdivisions(jc_brick, 3, 3);

		just_created_style->brick_style[BrickStyleID::GROUP_DARKEN] = *jc_brick;
		//***********************************************************
		//slider bg
		jc_brick = new EBrickStyle("Slider_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 4.0f, 4.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 4.0f, 4.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_BG] = *jc_brick;
		//***********************************************************
		//slider head inactive
		jc_brick = new EBrickStyle("Slider_head_inactive");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_INACTIVE] = *jc_brick;
		//***********************************************************
		//slider head active
		jc_brick = new EBrickStyle("Slider_head_active");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_ACTIVE] = *jc_brick;
		//***********************************************************
		//button background
		jc_brick = new EBrickStyle("Button_bg");
		jc_brick->parent_style = just_created_style;
	
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::BUTTON_BG] = *jc_brick;
		EGUIStyle::style_list.push_back(just_created_style);
	}

	//path of black
	if (true)
	{
		//###########################################################
		//MODERN
		just_created_style = new EGUIStyle("path_of_black");
		l_text.base_name = "path_of_black";
		l_text.localisations[NSW_localisation_EN] = "Path of Black";
		l_text.localisations[NSW_localisation_RU] = "×¸ðíàÿ äîðîãà";
		just_created_style->localisation_text = l_text;
		//***********************************************************
		//main gutton group
		//just_created_style->set_color_multiplier(0.3f, 0.35f, 0.3f, 1.0f);
		just_created_style->set_color_multiplier(0.9f, 0.85f, 0.6f, 1.0f);

		jc_brick = new EBrickStyle("Group_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 2, 2);

		just_created_style->brick_style[BrickStyleID::GROUP_DEFAULT] = *jc_brick;
		//***********************************************************
		//darken gutton group
		jc_brick = new EBrickStyle("Root_group_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 5.0f, 5.0f, 5.0f, 5.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::GROUP_DARKEN] = *jc_brick;
		//***********************************************************
		//slider bg
		jc_brick = new EBrickStyle("Slider_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_BG] = *jc_brick;
		//***********************************************************
		//slider head inactive
		jc_brick = new EBrickStyle("Slider_head_inactive");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_INACTIVE] = *jc_brick;
		//***********************************************************
		//slider head active
		jc_brick = new EBrickStyle("Slider_head_active");
		jc_brick->parent_style = just_created_style;
	
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_ACTIVE] = *jc_brick;
		//***********************************************************
		//button background
		jc_brick = new EBrickStyle("Button_bg");
		jc_brick->parent_style = just_created_style;
	
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::BUTTON_BG] = *jc_brick;
		//***********************************************************
		//slider head round
		jc_brick = new EBrickStyle("Slider_head_round");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::ROUND_SLIDER] = *jc_brick;
		EGUIStyle::style_list.push_back(just_created_style);
	}

	//basalt
	if (true)
	{
		//###########################################################
		//MODERN
		just_created_style = new EGUIStyle("basalt");
		l_text.base_name = "basalt";
		l_text.localisations[NSW_localisation_EN] = "Basalt";
		l_text.localisations[NSW_localisation_RU] = "Áàçàëüò";
		just_created_style->localisation_text = l_text;
		//***********************************************************
		//main gutton group
		//just_created_style->set_color_multiplier(0.3f, 0.35f, 0.3f, 1.0f);
		just_created_style->set_color_multiplier(0.9f, 0.85f, 0.6f, 1.0f);

		jc_brick = new EBrickStyle("Group_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 3.0f, 3.0f, 3.0f, 3.0f);
		EBrickStyle::set_offset_size(jc_brick, 6.0f, 6.0f, 6.0f, 6.0f);
		EBrickStyle::set_subdivisions(jc_brick, 2, 2);

		just_created_style->brick_style[BrickStyleID::GROUP_DEFAULT] = *jc_brick;
		//***********************************************************
	//darken gutton group
		jc_brick = new EBrickStyle("Root_group_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 5.0f, 5.0f, 5.0f, 5.0f);
		EBrickStyle::set_offset_size(jc_brick, 5.0f, 5.0f, 5.0f, 5.0f);
		EBrickStyle::set_subdivisions(jc_brick, 2, 2);

		just_created_style->brick_style[BrickStyleID::GROUP_DARKEN] = *jc_brick;
		//***********************************************************
		//slider bg
		jc_brick = new EBrickStyle("Slider_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 4.0f, 4.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 4.0f, 4.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_BG] = *jc_brick;
		//***********************************************************
		//slider head inactive
		jc_brick = new EBrickStyle("Slider_head_inactive");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_INACTIVE] = *jc_brick;
		//***********************************************************
		//slider head active
		jc_brick = new EBrickStyle("Slider_head_active");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_ACTIVE] = *jc_brick;
		//***********************************************************
		//button background
		jc_brick = new EBrickStyle("Button_bg");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::BUTTON_BG] = *jc_brick;
		//***********************************************************
		//slider head round
		jc_brick = new EBrickStyle("Slider_head_round");
		jc_brick->parent_style = just_created_style;
		
		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::ROUND_SLIDER] = *jc_brick;
		EGUIStyle::style_list.push_back(just_created_style);
	}

	//TEST
	if (false)
	{
		//###########################################################
		//MODERN
		just_created_style = new EGUIStyle("test");
		l_text.base_name = "test";
		l_text.localisations[NSW_localisation_EN] = "TEST";
		l_text.localisations[NSW_localisation_RU] = "ÒÅÑÒ";
		just_created_style->localisation_text = l_text;
		//***********************************************************
		//main gutton group
		//just_created_style->set_color_multiplier(0.3f, 0.35f, 0.3f, 1.0f);
		just_created_style->set_color_multiplier(0.9f, 0.85f, 0.6f, 1.0f);

		jc_brick = new EBrickStyle("Group_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 0.0f, 0.0f, 0.0f, 0.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::GROUP_DEFAULT] = *jc_brick;
		//***********************************************************
		//darken gutton group
		jc_brick = new EBrickStyle("Root_group_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 5.0f, 5.0f, 5.0f, 5.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::GROUP_DARKEN] = *jc_brick;
		//***********************************************************
		//slider bg
		jc_brick = new EBrickStyle("Slider_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_BG] = *jc_brick;
		//***********************************************************
		//slider head inactive
		jc_brick = new EBrickStyle("Slider_head_inactive");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_INACTIVE] = *jc_brick;
		//***********************************************************
		//slider head active
		jc_brick = new EBrickStyle("Slider_head_active");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_ACTIVE] = *jc_brick;
		//***********************************************************
		//button background
		jc_brick = new EBrickStyle("Button_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::BUTTON_BG] = *jc_brick;
		//***********************************************************
		//slider head round
		jc_brick = new EBrickStyle("Slider_head_round");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::ROUND_SLIDER] = *jc_brick;
		EGUIStyle::style_list.push_back(just_created_style);
	}

	//500 cats
	if (false)
	{
		//###########################################################
		//MODERN
		just_created_style = new EGUIStyle("500_cats");
		l_text.base_name = "500_cats";
		l_text.localisations[NSW_localisation_EN] = "500 friendly cats";
		l_text.localisations[NSW_localisation_RU] = "500 ëàñêîâûõ êîøåê";
		just_created_style->localisation_text = l_text;
		//***********************************************************
		// 

		just_created_style->is_rotator = true;

		//main gutton group
		//just_created_style->set_color_multiplier(0.3f, 0.35f, 0.3f, 1.0f);
		just_created_style->set_color_multiplier(0.9f, 0.85f, 0.6f, 1.0f);

		jc_brick = new EBrickStyle("Group_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 10.0f, 10.0f, 10.0f, 10.0f);
		EBrickStyle::set_offset_size(jc_brick, 12.0f, 12.0f, 12.0f, 12.0f);
		EBrickStyle::set_subdivisions(jc_brick, 1, 1);

		just_created_style->brick_style[BrickStyleID::GROUP_DEFAULT] = *jc_brick;
		//***********************************************************
		//darken gutton group
		jc_brick = new EBrickStyle("Root_group_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 5.0f, 5.0f, 5.0f, 5.0f);
		EBrickStyle::set_offset_size(jc_brick, 7.0f, 7.0f, 7.0f, 7.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::GROUP_DARKEN] = *jc_brick;
		//***********************************************************
		//slider bg
		jc_brick = new EBrickStyle("Slider_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_BG] = *jc_brick;
		//***********************************************************
		//slider head inactive
		jc_brick = new EBrickStyle("Slider_head_inactive");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_INACTIVE] = *jc_brick;
		//***********************************************************
		//slider head active
		jc_brick = new EBrickStyle("Slider_head_active");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_ACTIVE] = *jc_brick;
		//***********************************************************
		//button background
		jc_brick = new EBrickStyle("Button_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::BUTTON_BG] = *jc_brick;
		//***********************************************************
		//slider head round
		jc_brick = new EBrickStyle("Slider_head_round");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::ROUND_SLIDER] = *jc_brick;
		EGUIStyle::style_list.push_back(just_created_style);
	}//500 cats

	//never gonna give you up
	if (false)
	{
		//###########################################################
		//MODERN
		just_created_style = new EGUIStyle("never_gonna_give_you_up");
		l_text.base_name = "never_gonna_give_you_up";
		l_text.localisations[NSW_localisation_EN] = "Concrete wall";
		l_text.localisations[NSW_localisation_RU] = "Áåòîííàÿ ñòåíà";
		just_created_style->localisation_text = l_text;
		//***********************************************************
		//main gutton group
		//just_created_style->set_color_multiplier(0.3f, 0.35f, 0.3f, 1.0f);
		just_created_style->set_color_multiplier(0.9f, 0.85f, 0.6f, 1.0f);

		jc_brick = new EBrickStyle("Group_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 5.0f, 5.0f, 5.0f, 5.0f);
		EBrickStyle::set_offset_size(jc_brick, 7.0f, 7.0f, 7.0f, 7.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 4);

		just_created_style->brick_style[BrickStyleID::GROUP_DEFAULT] = *jc_brick;
		//***********************************************************
		//darken gutton group
		jc_brick = new EBrickStyle("Root_group_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 5.0f, 5.0f, 5.0f, 5.0f);
		EBrickStyle::set_offset_size(jc_brick, 7.0f, 7.0f, 7.0f, 7.0f);
		EBrickStyle::set_subdivisions(jc_brick, 2, 2);

		just_created_style->brick_style[BrickStyleID::GROUP_DARKEN] = *jc_brick;
		//***********************************************************
		//slider bg
		jc_brick = new EBrickStyle("Slider_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_BG] = *jc_brick;
		//***********************************************************
		//slider head inactive
		jc_brick = new EBrickStyle("Slider_head_inactive");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_INACTIVE] = *jc_brick;
		//***********************************************************
		//slider head active
		jc_brick = new EBrickStyle("Slider_head_active");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_ACTIVE] = *jc_brick;
		//***********************************************************
		//button background
		jc_brick = new EBrickStyle("Button_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::BUTTON_BG] = *jc_brick;
		//***********************************************************
		//slider head round
		jc_brick = new EBrickStyle("Slider_head_round");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::ROUND_SLIDER] = *jc_brick;
		EGUIStyle::style_list.push_back(just_created_style);
	}

	//frontrooms
	if (false)
	{
		//###########################################################
		//MODERN
		just_created_style = new EGUIStyle("frontrooms");
		l_text.base_name = "frontrooms";
		l_text.localisations[NSW_localisation_EN] = "Frontrooms";
		l_text.localisations[NSW_localisation_RU] = "Ïðåäêóëèñüå";
		just_created_style->localisation_text = l_text;
		//***********************************************************
		//main gutton group
		//just_created_style->set_color_multiplier(0.3f, 0.35f, 0.3f, 1.0f);
		just_created_style->set_color_multiplier(0.9f, 0.85f, 0.6f, 1.0f);

		jc_brick = new EBrickStyle("Group_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 5.0f, 5.0f, 5.0f, 5.0f);
		EBrickStyle::set_offset_size(jc_brick, 7.0f, 7.0f, 7.0f, 7.0f);
		EBrickStyle::set_subdivisions(jc_brick, 1, 1);

		just_created_style->brick_style[BrickStyleID::GROUP_DEFAULT] = *jc_brick;
		//***********************************************************
		//darken gutton group
		jc_brick = new EBrickStyle("Root_group_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 5.0f, 5.0f, 5.0f, 5.0f);
		EBrickStyle::set_offset_size(jc_brick, 7.0f, 7.0f, 7.0f, 7.0f);
		EBrickStyle::set_subdivisions(jc_brick, 2, 2);

		just_created_style->brick_style[BrickStyleID::GROUP_DARKEN] = *jc_brick;
		//***********************************************************
		//slider bg
		jc_brick = new EBrickStyle("Slider_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_BG] = *jc_brick;
		//***********************************************************
		//slider head inactive
		jc_brick = new EBrickStyle("Slider_head_inactive");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_INACTIVE] = *jc_brick;
		//***********************************************************
		//slider head active
		jc_brick = new EBrickStyle("Slider_head_active");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::SLIDER_ACTIVE] = *jc_brick;
		//***********************************************************
		//button background
		jc_brick = new EBrickStyle("Button_bg");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_offset_size(jc_brick, 2.0f, 2.0f, 2.0f, 2.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::BUTTON_BG] = *jc_brick;
		//***********************************************************
		//slider head round
		jc_brick = new EBrickStyle("Slider_head_round");
		jc_brick->parent_style = just_created_style;

		NS_EGraphicCore::load_style_texture(just_created_style, jc_brick);

		EBrickStyle::set_border_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_offset_size(jc_brick, 1.0f, 1.0f, 1.0f, 1.0f);
		EBrickStyle::set_subdivisions(jc_brick, 0, 0);

		just_created_style->brick_style[BrickStyleID::ROUND_SLIDER] = *jc_brick;
		EGUIStyle::style_list.push_back(just_created_style);
	}

	////*******************************
	////gray minimalism
	//just_created_style = new EGUIStyle();
	//EGUIStyle::set_style_borders_and_subdivisions(just_created_style, 5.0f, 5.0f, 5.0f, 5.0f, 1, 1);
	//EGUIStyle::set_style_offset_borders(just_created_style, 5.0f, 5.0f, 5.0f, 5.0f);

	//EGUIStyle::set_style_borders_and_subdivision_for_buttons(just_created_style, 2.0f, 2.0f, 2.0f, 2.0f, 0, 0);
	//EGUIStyle::set_style_borders_and_subdivision_for_slider_bg(just_created_style, 2.0f, 2.0f, 2.0f, 2.0f, 0, 0);

	//

	//just_created_style->slider_head_active = NS_EGraphicCore::put_texture_to_atlas
	//("data/textures/styles/gray_minimalism/Slider_head_active.png", NS_EGraphicCore::default_texture_atlas);

	//just_created_style->slider_head_inactive = NS_EGraphicCore::put_texture_to_atlas
	//("data/textures/styles/gray_minimalism/Slider_head_inactive.png", NS_EGraphicCore::default_texture_atlas);

	//just_created_style->background_for_slider = NS_EGraphicCore::put_texture_to_atlas
	//("data/textures/styles/gray_minimalism/Slider_bg.png", NS_EGraphicCore::default_texture_atlas);



	//just_created_style->background_for_button_group = NS_EGraphicCore::put_texture_to_atlas
	//("data/textures/styles/gray_minimalism/Group_bg.png", NS_EGraphicCore::default_texture_atlas);

	//just_created_style->background_for_root_button_group = NS_EGraphicCore::put_texture_to_atlas
	//("data/textures/styles/gray_minimalism/Root_group_bg.png", NS_EGraphicCore::default_texture_atlas);



	//just_created_style->backround_for_buttons = NS_EGraphicCore::put_texture_to_atlas
	//("data/textures/styles/gray_minimalism/Button_bg.png", NS_EGraphicCore::default_texture_atlas);
	////EGUIStyle::active_style = just_created_style;
	//EGUIStyle::style_list.push_back(just_created_style);
	////EGUIStyle::style_list.push_back(just_created_style);
	////EGUIStyle::style_list.push_back(just_created_style);

	////*******************************
	////stone castle
	//just_created_style = new EGUIStyle();
	//EGUIStyle::set_style_borders_and_subdivisions(just_created_style, 11.0f, 11.0f, 11.0f, 18.0f, 2, 2);
	//EGUIStyle::set_style_offset_borders(just_created_style, 8.0f, 8.0f, 11.0f, 16.0f);

	//EGUIStyle::set_style_borders_and_subdivision_for_buttons(just_created_style, 2.0f, 2.0f, 2.0f, 2.0f, 0, 0);
	//EGUIStyle::set_style_borders_and_subdivision_for_slider_bg(just_created_style, 2.0f, 2.0f, 2.0f, 2.0f, 0, 0);



	//just_created_style->slider_head_active = NS_EGraphicCore::put_texture_to_atlas
	//("data/textures/styles/stone_castle/Slider_head_active.png", NS_EGraphicCore::default_texture_atlas);

	//just_created_style->slider_head_inactive = NS_EGraphicCore::put_texture_to_atlas
	//("data/textures/styles/stone_castle/Slider_head_inactive.png", NS_EGraphicCore::default_texture_atlas);

	//just_created_style->background_for_slider = NS_EGraphicCore::put_texture_to_atlas
	//("data/textures/styles/stone_castle/Slider_bg.png", NS_EGraphicCore::default_texture_atlas);



	//just_created_style->background_for_button_group = NS_EGraphicCore::put_texture_to_atlas
	//("data/textures/styles/stone_castle/Group_bg.png", NS_EGraphicCore::default_texture_atlas);

	//just_created_style->background_for_root_button_group = NS_EGraphicCore::put_texture_to_atlas
	//("data/textures/styles/stone_castle/Root_group_bg.png", NS_EGraphicCore::default_texture_atlas);



	//just_created_style->backround_for_buttons = NS_EGraphicCore::put_texture_to_atlas
	//("data/textures/styles/stone_castle/Button_bg.png", NS_EGraphicCore::default_texture_atlas);
	////EGUIStyle::active_style = just_created_style;
	//EGUIStyle::style_list.push_back(just_created_style);


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

void NS_EGraphicCore::set_active_color(const EColor_4(*_color)[4])
{
	NS_EGraphicCore::active_color[0] = (*_color)[0];
	NS_EGraphicCore::active_color[1] = (*_color)[1];
	NS_EGraphicCore::active_color[2] = (*_color)[2];
	NS_EGraphicCore::active_color[3] = (*_color)[3];
}


void NS_EGraphicCore::set_active_color_custom_alpha(const EColor_4(&_color)[4], float _alpha)
{
	NS_EGraphicCore::active_color[0] = _color[0];
	NS_EGraphicCore::active_color[1] = _color[1];
	NS_EGraphicCore::active_color[2] = _color[2];
	NS_EGraphicCore::active_color[3] = _alpha;
}

void NS_EGraphicCore::set_active_color(EColor_4* _color)
{
	NS_EGraphicCore::active_color[0] = _color[0];
	NS_EGraphicCore::active_color[1] = _color[1];
	NS_EGraphicCore::active_color[2] = _color[2];
	NS_EGraphicCore::active_color[3] = _color[3];
}

void NS_EGraphicCore::set_active_color(float _r, float _g, float _b, float _a)
{
	NS_EGraphicCore::active_color[0] = _r;
	NS_EGraphicCore::active_color[1] = _g;
	NS_EGraphicCore::active_color[2] = _b;
	NS_EGraphicCore::active_color[3] = _a;
}

void NS_EGraphicCore::set_active_color(HSVRGBAColor* _color)
{
	NS_EGraphicCore::active_color[0] = _color->r;
	NS_EGraphicCore::active_color[1] = _color->g;
	NS_EGraphicCore::active_color[2] = _color->b;
	NS_EGraphicCore::active_color[3] = _color->a;
}

void NS_EGraphicCore::make_skydome_textures(ETextureGabarite* _texture)
{
	//NS_EGraphicCore::gl_set_texture_filtering(GL_CLAMP, GL_NEAREST);
	NS_EGraphicCore::skydome_batcher->get_shader()->use();
	{


		set_source_FBO(GL_TEXTURE0, default_texture_atlas->get_colorbuffer());
		set_target_FBO(skydome_texture_atlas[0]->get_framebuffer());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//

		NS_EGraphicCore::skydome_batcher->get_shader()->setInt("blur_table", -1);

		NS_EGraphicCore::skydome_batcher->set_transform_screen_size(1.0f, 1.0f);

		glViewport(0, 0, skydome_texture_atlas[0]->get_atlas_size_x(), skydome_texture_atlas[0]->get_atlas_size_y());

		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			NS_EGraphicCore::skydome_batcher->vertex_buffer,
			NS_EGraphicCore::skydome_batcher->last_vertice_buffer_index,
			0.0f,
			0.0f,
			1.0f,
			1.0f,
			_texture
		);

		NS_EGraphicCore::skydome_batcher->draw_call();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, skydome_texture_atlas[0]->get_framebuffer());
		glGenerateMipmap(GL_TEXTURE_2D);
	}


	float blur_table[texture_skydome_levels] = { 2, 2, 3, 4, 5, 6, 7 };
	for (int i = 1; i < texture_skydome_levels; i++)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_WHITE);
		set_source_FBO(GL_TEXTURE0, skydome_texture_atlas[i - 1]->get_colorbuffer());
		set_target_FBO(skydome_texture_atlas[i]->get_framebuffer());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//

		float pp = max(1.0f, i - 0.8f);
		pp *= pp;

		NS_EGraphicCore::skydome_batcher->get_shader()->setInt("blur_table", i - 1);
		NS_EGraphicCore::skydome_batcher->get_shader()->setFloat("blur_size_x", 1.0f / skydome_texture_atlas[i]->get_atlas_size_x());
		NS_EGraphicCore::skydome_batcher->get_shader()->setFloat("blur_size_y", 1.0f / skydome_texture_atlas[i]->get_atlas_size_y());

		NS_EGraphicCore::skydome_batcher->set_transform_screen_size(1.0f, 1.0f);
		//NS_EGraphicCore::gl_set_texture_filtering(GL_CLAMP, GL_NEAREST);

		glViewport(0, 0, skydome_texture_atlas[i]->get_atlas_size_x(), skydome_texture_atlas[i]->get_atlas_size_y());

		NS_ERenderCollection::add_data_to_vertex_buffer_default
		(
			NS_EGraphicCore::skydome_batcher->vertex_buffer,
			NS_EGraphicCore::skydome_batcher->last_vertice_buffer_index,
			0.0f,
			0.0f,
			1.0f,
			1.0f
		);

		NS_EGraphicCore::skydome_batcher->draw_call();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, skydome_texture_atlas[i]->get_framebuffer());
		glGenerateMipmap(GL_TEXTURE_2D);
	}

		//restore default viewport setting
		set_target_FBO(0);
		set_source_FBO(GL_TEXTURE0, NS_EGraphicCore::default_texture_atlas->get_colorbuffer());
		glViewport(0, 0, NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT);

		glDisable(GL_DEPTH_TEST);
		glBlendEquation(GL_FUNC_ADD);

}

void NS_EGraphicCore::set_source_FBO(int _GL_texture_id, unsigned int _colorbuffer_id)
{
	glActiveTexture(_GL_texture_id);
	glBindTexture(GL_TEXTURE_2D, _colorbuffer_id);
}

void NS_EGraphicCore::set_target_FBO(unsigned int _framebuffer_id)
{
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer_id);
}

ETextureGabarite* NS_EGraphicCore::get_gabarite_from_full_path_and_suffix(ETextureGabarite* _gabarite, std::string _suffix)
{
	std::string full_path = _gabarite->get_full_path();
	//																	4 = ".png"
	std::string final_path = full_path.insert(full_path.length() - 4, _suffix);
	//std::string final_path	=

	//EInputCore::logger_param("final_path", final_path);

	if (std::filesystem::exists(final_path))
	{
		//EInputCore::logger_simple_success("exist");
		return load_texture_to_default_atlas(final_path);
	}
	else
	{
		//EInputCore::logger_simple_error("not exist");
		return nullptr;
	}
}

NS_EGraphicCore::RgbColor NS_EGraphicCore::HsvToRgb(HsvColor hsv)
{
	RgbColor rgb;
	unsigned char region, remainder, p, q, t;

	if (hsv.s == 0)
	{
		rgb.r = hsv.v;
		rgb.g = hsv.v;
		rgb.b = hsv.v;
		return rgb;
	}

	region = hsv.h / 43;
	remainder = (hsv.h - (region * 43)) * 6;

	p = (hsv.v * (255 - hsv.s)) >> 8;
	q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
	t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

	switch (region)
	{
	case 0:
		rgb.r = hsv.v; rgb.g = t; rgb.b = p;
		break;
	case 1:
		rgb.r = q; rgb.g = hsv.v; rgb.b = p;
		break;
	case 2:
		rgb.r = p; rgb.g = hsv.v; rgb.b = t;
		break;
	case 3:
		rgb.r = p; rgb.g = q; rgb.b = hsv.v;
		break;
	case 4:
		rgb.r = t; rgb.g = p; rgb.b = hsv.v;
		break;
	default:
		rgb.r = hsv.v; rgb.g = p; rgb.b = q;
		break;
	}

	return rgb;
}

NS_EGraphicCore::HsvColor NS_EGraphicCore::RgbToHsv(RgbColor rgb)
{
	HsvColor hsv;
	unsigned char rgbMin, rgbMax;

	rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
	rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);

	hsv.v = rgbMax;
	if (hsv.v == 0)
	{
		hsv.h = 0;
		hsv.s = 0;
		return hsv;
	}

	hsv.s = 255 * long(rgbMax - rgbMin) / hsv.v;
	if (hsv.s == 0)
	{
		hsv.h = 0;
		return hsv;
	}

	if (rgbMax == rgb.r)
		hsv.h = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
	else if (rgbMax == rgb.g)
		hsv.h = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
	else
		hsv.h = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);

	return hsv;
}




void NS_EGraphicCore::load_texture(char const* _path, int _id)
{
	glGenTextures(_id, &texture[_id]);
	glBindTexture(GL_TEXTURE_2D, texture[_id]);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	//ifstream (_path)

	std::string full_path = _path;



	
	image_data = stbi_load(_path, &texture_loader_width, &texture_loader_height, &nrChannels, STBI_rgb_alpha);
	
	//getPngSize(_path, u_size_x, u_size_y);
	
	

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

		last_texture_width = texture_loader_width;
		last_texture_height = texture_loader_height;
		



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
		std::cout << red << "Failed to load texture " << yellow << "(" << _path << ")" << green << std::endl;
		//std::cout << "Failed to load texture " << "(" << _path << ")" << std::endl;
		//last_texture_h = 21;
		//last_texture_w = 21;

		//texture_error = true;

		//just_created_gabarite = DefaultGabarite::gabarite_error;
	}

	stbi_image_free(image_data);
}

void NS_EGraphicCore::get_png_image_dimensions(std::string& file_path, unsigned int& width, unsigned int& height)
{
	unsigned char buf[9];
	unsigned char full[17];

	std::ifstream in(file_path, std::ios_base::in | std::ios_base::binary);
	in.read(reinterpret_cast<char*>(&full), 16);
	//in.seekg(16);
	in.read(reinterpret_cast<char*>(&buf), 8);

	buf[8] = '\0';
	full[16] = '\0';

	std::string zzz;

	//width = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + (buf[3] << 0);
	//height = (buf[4] << 24) + (buf[5] << 16) + (buf[6] << 8) + (buf[7] << 0);

	width =  buf[3] + buf[2] * 256;
	height = buf[7] + buf[6] * 256;

	if ((width >= 10000) || (height >= 10000))
	{
		EInputCore::logger_param_with_warning("PNG header readed incorrect", file_path);
		
		width = 1000;
		height = 1000;

		for (int i = 0; i < 8; i++)
		{
			EInputCore::logger_param_with_warning("buf" + std::to_string(i), buf[i]);
		}

		EInputCore::logger_param_with_warning("?", width);
		EInputCore::logger_param_with_warning("?", height);
	}
}

bool NS_EGraphicCore::getPngSize(const char* fileName, int& _x, int& _y)
{
	std::ifstream file(fileName, std::ios_base::binary | std::ios_base::in);

	if (!file.is_open() || !file) {
		file.close();
		return false;
	}

	// Skip PNG file signature
	file.seekg(8, std::ios_base::cur);

	// First chunk: IHDR image header
	// Skip Chunk Length
	file.seekg(4, std::ios_base::cur);
	// Skip Chunk Type
	file.seekg(4, std::ios_base::cur);

	__int32 width, height;

	file.read((char*)&width, 4);
	file.read((char*)&height, 4);

	std::cout << file.tellg();

	_x = width;
	_y = height;

	file.close();

	return true;

	return true;
}

ETextureGabarite* NS_EGraphicCore::put_texture_to_atlas(std::string _full_path, ETextureAtlas* _atlas)
{
	float stored_zoom = NS_EGraphicCore::current_zoom;
	NS_EGraphicCore::current_zoom = 1.0f;

	for (int i = 0; i < _full_path.length(); i++)
	{
		if (_full_path[i] == '\\') { _full_path[i] = '/'; }
	}

	ETextureGabarite* duplicate_gabarite = nullptr;

	//search already loaded texture gabarite
	int
	index = EStringUtils::get_id_by_hash(_full_path);



	for (ETextureGabarite* g : NS_EGraphicCore::texture_gabarites_list[index])
	{
		if (g->get_full_path() == _full_path)
		{
			duplicate_gabarite = g;
		}
	}

	ETextureGabarite* new_gabarite = nullptr;

	if (duplicate_gabarite == nullptr)
	{
		
		
		unsigned int u_size_x = 0;
		unsigned int u_size_y = 0;
		get_png_image_dimensions(_full_path, u_size_x, u_size_y);

		
		

		//search free place for new texture
		int place_x = -1;
		int place_y = -1;
		for (int x = 0; x < (int)(_atlas->get_atlas_size_x() / 4.0f); x++)
		{
			for (int y = 0; y < (int)(_atlas->get_atlas_size_y() / 4.0f); y++)
			{
				if (_atlas->can_place_here(x, y, ceil(u_size_x / 4.0f), ceil(u_size_y / 4.0f)))
				{
					place_x = x * 4;
					place_y = y * 4;

					break;
				}
			}
			if (place_x >= 0) { break; }
		}

		//remove free space
		//
		for (int x = (ceil)(place_x / 4.0f) - 2; x < (ceil)((place_x + u_size_x) / 4.0f) + 2; x++)
			for (int y = (ceil)(place_y / 4.0f) - 2; y < (ceil)((place_y + u_size_y) / 4.0f) + 2; y++)
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
	

		new_gabarite = new ETextureGabarite();

		if (new_gabarite != nullptr)
		{
			new_gabarite->set_full_path(_full_path);
			new_gabarite->set_name_based_on_full_path(_full_path);

			new_gabarite->position_on_texture_atlas_x = place_x;
			new_gabarite->position_on_texture_atlas_y = place_y;

			new_gabarite->set_uv_parameters
			(
				(float)(place_x + 0.5f) / (float)(_atlas->get_atlas_size_x()),
				(float)(place_y + 0.5f) / (float)(_atlas->get_atlas_size_y()),

				(float)(u_size_x - 1.0f) / (float)(_atlas->get_atlas_size_x()),
				(float)(u_size_y - 1.0f) / (float)(_atlas->get_atlas_size_y())
			);

			new_gabarite->target_atlas = _atlas;

			new_gabarite->set_real_texture_size
			(
				u_size_x,
				u_size_y
			);

			//EInputCore::logger_param("Generate new gabarite (full path)", new_gabarite->get_full_path());
			//EInputCore::logger_param("Generate new gabarite (name)", new_gabarite->get_name());

			//NS_EGraphicCore::complete_texture_gabarite(new_gabarite);
			NS_EGraphicCore::texture_gabarites_list[index].push_back(new_gabarite);

			ETextureGabarite::incomplete_gabarites_list.push_back(new_gabarite);

			if (new_gabarite->get_name() == "")
			{
				EInputCore::logger_simple_error("empty texture name");
			}
		}
	}
	else
	{
		new_gabarite = duplicate_gabarite;
		//EInputCore::logger_param("Use existed gabarite", new_gabarite->get_full_path());
	}

	




	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, NS_EGraphicCore::default_texture_atlas->get_colorbuffer());

	//if (_full_path == "data/textures/loot_version_strong_ignore.png")
	//{
	//	duplicate_gabarite = duplicate_gabarite;
	//}

	NS_EGraphicCore::current_zoom = stored_zoom;
	return new_gabarite;
}

ETextureGabarite* NS_EGraphicCore::load_from_textures_folder(std::string _name)
{
	return put_texture_to_atlas("data/textures/" + _name + ".png", default_texture_atlas);
}

ETextureGabarite* NS_EGraphicCore::load_texture_to_default_atlas(std::string _name)
{
	return put_texture_to_atlas(_name, default_texture_atlas);
}

void NS_EGraphicCore::load_style_texture(EGUIStyle* _style, EBrickStyle* _brick)
{
	_brick->main_texture = put_texture_to_atlas("data/textures/styles/" + *_style->folder + "/" + _brick->file_name + ".png", default_texture_atlas);

	if (std::filesystem::exists("data/textures/styles/" + *_style->folder + "/" + _brick->file_name + "[normal_map].png"))
	{
		_brick->normal_map_texture = put_texture_to_atlas("data/textures/styles/" + *_style->folder + "/" + _brick->file_name + "[normal_map].png", default_texture_atlas);
	}
	else
	{
		_brick->normal_map_texture = NS_DefaultGabarites::texture_gabarite_normal_map_placeholder;
		//EInputCore::logger_simple_error("data/textures/styles/" + *_style->folder + "/" + *_brick->file_name + "[normal_map].png " + "not exist");
	}

	if (std::filesystem::exists("data/textures/styles/" + *_style->folder + "/" + _brick->file_name + "[gloss_map].png"))
	{
		_brick->gloss_map_texture = put_texture_to_atlas("data/textures/styles/" + *_style->folder + "/" + _brick->file_name + "[gloss_map].png", default_texture_atlas);
	}
	else
	{
		_brick->gloss_map_texture = NS_DefaultGabarites::texture_gabarite_gloss_map_placeholder;
		//EInputCore::logger_simple_error("data/textures/styles/" + *_style->folder + "/" + *_brick->file_name + "[gloss_map].png " + "not exist");
		//EInputCore::logger_simple_error("Error! Cannot load: " + *_brick->file_name);
	}
}

void NS_EGraphicCore::complete_texture_gabarite(ETextureGabarite* _texture_gabarite)
{

	glEnable(GL_BLEND);
	glad_glBlendFuncSeparate(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);
	glBlendEquation(GL_FUNC_ADD);

	NS_EGraphicCore::switch_to_texture_atlas_draw_mode(_texture_gabarite->target_atlas);


	NS_EGraphicCore::load_texture(_texture_gabarite->get_full_path().c_str(), 0);
	NS_EGraphicCore::default_batcher_for_texture_atlas->reset();


	NS_ERenderCollection::add_data_to_vertex_buffer_default
	(
		NS_EGraphicCore::default_batcher_for_texture_atlas->vertex_buffer,
		NS_EGraphicCore::default_batcher_for_texture_atlas->last_vertice_buffer_index,
		_texture_gabarite->position_on_texture_atlas_x,
		_texture_gabarite->position_on_texture_atlas_y,
		_texture_gabarite->size_x_in_pixels,
		_texture_gabarite->size_y_in_pixels
	);

	NS_EGraphicCore::default_batcher_for_texture_atlas->draw_call();

	//DRAW

	set_target_FBO(0);
	set_source_FBO(GL_TEXTURE0, NS_EGraphicCore::default_texture_atlas->get_colorbuffer());
	glViewport(0, 0, NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT);

	glDisable(GL_DEPTH_TEST);
	glBlendEquation(GL_FUNC_ADD);
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
	add_data_to_vertex_buffer_textured_rectangle_with_custom_size(_array, _start_offset, _x, _y + _t, _t, _h - _t * 2.0f, _texture);

	//right (vertical)
	add_data_to_vertex_buffer_textured_rectangle_with_custom_size(_array, _start_offset, _x + _w - _t, _y + _t, _t, _h - _t * 2.0f, _texture);

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

	_array[6] = _texture->uv_end_x;
	_array[7] = _texture->uv_end_y;

	//..
	//.#
	_array[8] = (_x + _w);
	_array[9] = _y;

	_array[10] = NS_EGraphicCore::active_color[0];
	_array[11] = NS_EGraphicCore::active_color[1];
	_array[12] = NS_EGraphicCore::active_color[2];
	_array[13] = NS_EGraphicCore::active_color[3];

	_array[14] = _texture->uv_end_x;
	_array[15] = _texture->uv_start_y;

	//..
	//#.
	_array[16] = _x;
	_array[17] = _y;

	_array[18] = NS_EGraphicCore::active_color[0];
	_array[19] = NS_EGraphicCore::active_color[1];
	_array[20] = NS_EGraphicCore::active_color[2];
	_array[21] = NS_EGraphicCore::active_color[3];

	_array[22] = _texture->uv_start_x;
	_array[23] = _texture->uv_start_y;

	//#.
	//..
	_array[24] = _x;
	_array[25] = (_y + _h);

	_array[26] = NS_EGraphicCore::active_color[0];
	_array[27] = NS_EGraphicCore::active_color[1];
	_array[28] = NS_EGraphicCore::active_color[2];
	_array[29] = NS_EGraphicCore::active_color[3];

	_array[30] = _texture->uv_start_x;
	_array[31] = _texture->uv_end_y;

	_start_offset += 32;
}

void NS_ERenderCollection::add_data_to_vertex_buffer_sprite(float* _array, unsigned int& _start_offset, ESprite* _sprite)
{
	//address arithmetic, get pointer to buffer array, and move to +_offset
	_array += _start_offset;

	//.#
	//..
	//[!][!][!]WARNING![!][!][!] It not "[0][1][2]..." index, it "[_start_offset + 0][_start_offset + 1][_start_offset + 2]..." index, see address arithmetic above
	_array[0] = _sprite->world_position_x + _sprite->size_x;
	_array[1] = _sprite->world_position_y + _sprite->size_y;

	_array[2] = NS_EGraphicCore::active_color[0];
	_array[3] = NS_EGraphicCore::active_color[1];
	_array[4] = NS_EGraphicCore::active_color[2];
	_array[5] = NS_EGraphicCore::active_color[3];

	_array[6] = _sprite->uv_end_x;
	_array[7] = _sprite->uv_end_y;

	//..
	//.#
	_array[8] = _sprite->world_position_x + _sprite->size_x;
	_array[9] = _sprite->world_position_y;

	_array[10] = NS_EGraphicCore::active_color[0];
	_array[11] = NS_EGraphicCore::active_color[1];
	_array[12] = NS_EGraphicCore::active_color[2];
	_array[13] = NS_EGraphicCore::active_color[3];

	_array[14] = _sprite->uv_end_x;
	_array[15] = _sprite->uv_start_y;

	//..
	//#.
	_array[16] = _sprite->world_position_x;
	_array[17] = _sprite->world_position_y;

	_array[18] = NS_EGraphicCore::active_color[0];
	_array[19] = NS_EGraphicCore::active_color[1];
	_array[20] = NS_EGraphicCore::active_color[2];
	_array[21] = NS_EGraphicCore::active_color[3];

	_array[22] = _sprite->uv_start_x;
	_array[23] = _sprite->uv_start_y;

	//#.
	//..
	_array[24] = _sprite->world_position_x;
	_array[25] = _sprite->world_position_y + _sprite->size_y;

	_array[26] = NS_EGraphicCore::active_color[0];
	_array[27] = NS_EGraphicCore::active_color[1];
	_array[28] = NS_EGraphicCore::active_color[2];
	_array[29] = NS_EGraphicCore::active_color[3];

	_array[30] = _sprite->uv_start_x;
	_array[31] = _sprite->uv_end_y;

	_start_offset += 32;
}

void NS_ERenderCollection::add_data_to_vertex_buffer_sprite_test(float* _array, unsigned int& _start_offset, ESprite* _sprite)
{

	//address arithmetic, get pointer to buffer array, and move to +_offset
	_array += _start_offset;

	//.#
	//..
	//[!][!][!]WARNING![!][!][!] It not "[0][1][2]..." index, it "[_start_offset + 0][_start_offset + 1][_start_offset + 2]..." index, see address arithmetic above
	_array[0] = _sprite->world_position_x + _sprite->size_x;
	_array[1] = _sprite->world_position_y + _sprite->size_y;
	_array[2] = _sprite->world_position_z + _sprite->size_z;

	_array[3] = NS_EGraphicCore::active_color[0];
	_array[4] = NS_EGraphicCore::active_color[1];
	_array[5] = NS_EGraphicCore::active_color[2];
	_array[6] = NS_EGraphicCore::active_color[3];

	_array[7] = _sprite->uv_end_x;
	_array[8] = _sprite->uv_end_y;

	//..
	//.#
	_array[9] = _sprite->world_position_x + _sprite->size_x;
	_array[10] = _sprite->world_position_y;
	_array[11] = _sprite->world_position_z;

	_array[12] = NS_EGraphicCore::active_color[0];
	_array[13] = NS_EGraphicCore::active_color[1];
	_array[14] = NS_EGraphicCore::active_color[2];
	_array[15] = NS_EGraphicCore::active_color[3];

	_array[16] = _sprite->uv_end_x;
	_array[17] = _sprite->uv_start_y;

	//..
	//#.
	_array[18] = _sprite->world_position_x;
	_array[19] = _sprite->world_position_y;
	_array[20] = _sprite->world_position_z;

	_array[21] = NS_EGraphicCore::active_color[0];
	_array[22] = NS_EGraphicCore::active_color[1];
	_array[23] = NS_EGraphicCore::active_color[2];
	_array[24] = NS_EGraphicCore::active_color[3];

	_array[25] = _sprite->uv_start_x;
	_array[26] = _sprite->uv_start_y;

	//#.
	//..
	_array[27] = _sprite->world_position_x;
	_array[28] = _sprite->world_position_y + _sprite->size_y;
	_array[29] = _sprite->world_position_z + _sprite->size_z;

	_array[30] = NS_EGraphicCore::active_color[0];
	_array[31] = NS_EGraphicCore::active_color[1];
	_array[32] = NS_EGraphicCore::active_color[2];
	_array[33] = NS_EGraphicCore::active_color[3];

	_array[34] = _sprite->uv_start_x;
	_array[35] = _sprite->uv_end_y;

	_start_offset += 48;
}

void NS_ERenderCollection::add_data_to_vertex_buffer_sprite_PBR(float* _array, unsigned int& _start_offset, ESprite* _sprite)
{

	{
		//address arithmetic, get pointer to buffer array, and move to +_offset
		_array += _start_offset;

		//.#
		//..
		//[!][!][!]WARNING![!][!][!] It not "[0][1][2]..." index, it "[_start_offset + 0][_start_offset + 1][_start_offset + 2]..." index, see address arithmetic above
		_array[0] = _sprite->world_position_x + _sprite->size_x;
		_array[1] = _sprite->world_position_y + _sprite->size_y;
		_array[2] = _sprite->world_position_z + _sprite->size_z;

		_array[3] = NS_EGraphicCore::active_color[0];
		_array[4] = NS_EGraphicCore::active_color[1];
		_array[5] = NS_EGraphicCore::active_color[2];
		_array[6] = NS_EGraphicCore::active_color[3];

		_array[7] = _sprite->uv_end_x;
		_array[8] = _sprite->uv_end_y;

		_array[9] = _sprite->normal_uv_end_x;
		_array[10] = _sprite->normal_uv_end_y;

		_array[11] = _sprite->gloss_uv_end_x;
		_array[12] = _sprite->gloss_uv_end_y;

		//..
		//.#
		_array[13] = _sprite->world_position_x + _sprite->size_x;
		_array[14] = _sprite->world_position_y;
		_array[15] = _sprite->world_position_z;

		_array[16] = NS_EGraphicCore::active_color[0];
		_array[17] = NS_EGraphicCore::active_color[1];
		_array[18] = NS_EGraphicCore::active_color[2];
		_array[19] = NS_EGraphicCore::active_color[3];

		_array[20] = _sprite->uv_end_x;
		_array[21] = _sprite->uv_start_y;

		_array[22] = _sprite->normal_uv_end_x;
		_array[23] = _sprite->normal_uv_start_y;

		_array[24] = _sprite->gloss_uv_end_x;
		_array[25] = _sprite->gloss_uv_start_y;

		//..
		//#.
		_array[26] = _sprite->world_position_x;
		_array[27] = _sprite->world_position_y;
		_array[28] = _sprite->world_position_z;

		_array[29] = NS_EGraphicCore::active_color[0];
		_array[30] = NS_EGraphicCore::active_color[1];
		_array[31] = NS_EGraphicCore::active_color[2];
		_array[32] = NS_EGraphicCore::active_color[3];

		_array[33] = _sprite->uv_start_x;
		_array[34] = _sprite->uv_start_y;

		_array[35] = _sprite->normal_uv_start_x;
		_array[36] = _sprite->normal_uv_start_y;

		_array[37] = _sprite->gloss_uv_start_x;
		_array[38] = _sprite->gloss_uv_start_y;

		//#.
		//..
		_array[39] = _sprite->world_position_x;
		_array[40] = _sprite->world_position_y + _sprite->size_y;
		_array[41] = _sprite->world_position_z + _sprite->size_z;

		_array[42] = NS_EGraphicCore::active_color[0];
		_array[43] = NS_EGraphicCore::active_color[1];
		_array[44] = NS_EGraphicCore::active_color[2];
		_array[45] = NS_EGraphicCore::active_color[3];

		_array[46] = _sprite->uv_start_x;
		_array[47] = _sprite->uv_end_y;

		_array[48] = _sprite->normal_uv_start_x;
		_array[49] = _sprite->normal_uv_end_y;

		_array[50] = _sprite->gloss_uv_start_x;
		_array[51] = _sprite->gloss_uv_end_y;

		_start_offset += 52;
	}
}

void NS_ERenderCollection::add_data_to_vertex_buffer_texture_gabarite_PBR(float* _array, unsigned int& _start_offset, float _x, float _y, float _w, float _h, ETextureGabarite* _texture, ETextureGabarite* _gloss, ETextureGabarite* _normal)
{
	{
		//address arithmetic, get pointer to buffer array, and move to +_offset
		_array += _start_offset;

		//.#
		//..
		//[!][!][!]WARNING![!][!][!] It not "[0][1][2]..." index, it "[_start_offset + 0][_start_offset + 1][_start_offset + 2]..." index, see address arithmetic above
		_array[0] = _x + _w;
		_array[1] = _y + _h;
		_array[2] = 0.0f;

		_array[3] = NS_EGraphicCore::active_color[0];
		_array[4] = NS_EGraphicCore::active_color[1];
		_array[5] = NS_EGraphicCore::active_color[2];
		_array[6] = NS_EGraphicCore::active_color[3];

		_array[7] = _texture->uv_end_x;
		_array[8] = _texture->uv_end_y;

		_array[9] = _normal->uv_end_x;
		_array[10] = _normal->uv_end_y;

		_array[11] = _gloss->uv_end_x;
		_array[12] = _gloss->uv_end_y;

		//..
		//.#
		_array[13] = _x + _w;
		_array[14] = _y;
		_array[15] = 0.0f;

		_array[16] = NS_EGraphicCore::active_color[0];
		_array[17] = NS_EGraphicCore::active_color[1];
		_array[18] = NS_EGraphicCore::active_color[2];
		_array[19] = NS_EGraphicCore::active_color[3];

		_array[20] = _texture->uv_end_x;
		_array[21] = _texture->uv_start_y;

		_array[22] = _normal->uv_end_x;
		_array[23] = _normal->uv_start_y;

		_array[24] = _gloss->uv_end_x;
		_array[25] = _gloss->uv_start_y;

		//..
		//#.
		_array[26] = _x;
		_array[27] = _y;
		_array[28] = 0.0f;

		_array[29] = NS_EGraphicCore::active_color[0];
		_array[30] = NS_EGraphicCore::active_color[1];
		_array[31] = NS_EGraphicCore::active_color[2];
		_array[32] = NS_EGraphicCore::active_color[3];

		_array[33] = _texture->uv_start_x;
		_array[34] = _texture->uv_start_y;

		_array[35] = _normal->uv_start_x;
		_array[36] = _normal->uv_start_y;

		_array[37] = _gloss->uv_start_x;
		_array[38] = _gloss->uv_start_y;

		//#.
		//..
		_array[39] = _x;
		_array[40] = _y + _h;
		_array[41] = 0.0f;

		_array[42] = NS_EGraphicCore::active_color[0];
		_array[43] = NS_EGraphicCore::active_color[1];
		_array[44] = NS_EGraphicCore::active_color[2];
		_array[45] = NS_EGraphicCore::active_color[3];

		_array[46] = _texture->uv_start_x;
		_array[47] = _texture->uv_end_y;

		_array[48] = _normal->uv_start_x;
		_array[49] = _normal->uv_end_y;

		_array[50] = _gloss->uv_start_x;
		_array[51] = _gloss->uv_end_y;

		_start_offset += 52;
	}
}

void NS_ERenderCollection::add_data_to_vertex_buffer_texture_fragment_PBR(float* _array, unsigned int& _start_offset, float _x, float _y, float _w, float _h, float _uv_x, float _uv_y, ETextureGabarite* _texture, ETextureGabarite* _gloss, ETextureGabarite* _normal)
{
	{
		//address arithmetic, get pointer to buffer array, and move to +_offset
		_array += _start_offset;

		//.#
		//..
		//[!][!][!]WARNING![!][!][!] It not "[0][1][2]..." index, it "[_start_offset + 0][_start_offset + 1][_start_offset + 2]..." index, see address arithmetic above
		_array[0] = _x + _w;
		_array[1] = _y + _h;
		_array[2] = 0.0f;

		_array[3] = NS_EGraphicCore::active_color[0];
		_array[4] = NS_EGraphicCore::active_color[1];
		_array[5] = NS_EGraphicCore::active_color[2];
		_array[6] = NS_EGraphicCore::active_color[3];

		_array[7] =		_texture->uv_start_x + _uv_x;
		_array[8] =		_texture->uv_start_y + _uv_y;

		_array[9] =		_normal->uv_start_x + _uv_x;
		_array[10] =	_normal->uv_start_y + _uv_y;

		_array[11] =	_gloss->uv_start_x + _uv_x;
		_array[12] =	_gloss->uv_start_y + _uv_y;

		//..
		//.#
		_array[13] = _x + _w;
		_array[14] = _y;
		_array[15] = 0.0f;

		_array[16] = NS_EGraphicCore::active_color[0];
		_array[17] = NS_EGraphicCore::active_color[1];
		_array[18] = NS_EGraphicCore::active_color[2];
		_array[19] = NS_EGraphicCore::active_color[3];

		_array[20] = _texture->uv_start_x + _uv_x;
		_array[21] = _texture->uv_start_y;

		_array[22] = _normal->uv_start_x + _uv_x;
		_array[23] = _normal->uv_start_y;

		_array[24] = _gloss->uv_start_x + _uv_x;
		_array[25] = _gloss->uv_start_y;

		//..
		//#.
		_array[26] = _x;
		_array[27] = _y;
		_array[28] = 0.0f;

		_array[29] = NS_EGraphicCore::active_color[0];
		_array[30] = NS_EGraphicCore::active_color[1];
		_array[31] = NS_EGraphicCore::active_color[2];
		_array[32] = NS_EGraphicCore::active_color[3];

		_array[33] = _texture->uv_start_x;
		_array[34] = _texture->uv_start_y;

		_array[35] = _normal->uv_start_x;
		_array[36] = _normal->uv_start_y;

		_array[37] = _gloss->uv_start_x;
		_array[38] = _gloss->uv_start_y;

		//#.
		//..
		_array[39] = _x;
		_array[40] = _y + _h;
		_array[41] = 0.0f;

		_array[42] = NS_EGraphicCore::active_color[0];
		_array[43] = NS_EGraphicCore::active_color[1];
		_array[44] = NS_EGraphicCore::active_color[2];
		_array[45] = NS_EGraphicCore::active_color[3];

		_array[46] = _texture->uv_start_x;
		_array[47] = _texture->uv_start_y + _uv_y;

		_array[48] = _normal->uv_start_x;
		_array[49] = _normal->uv_start_y + _uv_y;

		_array[50] = _gloss->uv_start_x;
		_array[51] = _gloss->uv_start_y + _uv_y;

		_start_offset += 52;
	}
}

void NS_ERenderCollection::add_data_to_vertex_buffer_rotated_square_PBR(float* _array, unsigned int& _start_offset, float _x, float _y, float _w, float _h, float _rotation, float _r_factor, ETextureGabarite* _texture, ETextureGabarite* _gloss, ETextureGabarite* _normal)
{
	{
		float l = sqrt(_w * _w + _h * _h) * 0.5f;
		//address arithmetic, get pointer to buffer array, and move to +_offset
		_array += _start_offset;
		_r_factor = 45.0f;
		//.#
		//..
		//[!][!][!]WARNING![!][!][!] It not "[0][1][2]..." index, it "[_start_offset + 0][_start_offset + 1][_start_offset + 2]..." index, see address arithmetic above
		_array[0] = _x + _w / 2.0f + sinf((45.0f + _rotation) * 0.017453f) * l;
		_array[1] = _y + _h / 2.0f + cosf((45.0f + _rotation) * 0.017453f) * l;
		_array[2] = 0.0f;

		_array[3] = NS_EGraphicCore::active_color[0];
		_array[4] = NS_EGraphicCore::active_color[1];
		_array[5] = NS_EGraphicCore::active_color[2];
		_array[6] = NS_EGraphicCore::active_color[3];

		_array[7] = _texture->uv_end_x;
		_array[8] = _texture->uv_end_y;

		_array[9] = _normal->uv_end_x;
		_array[10] = _normal->uv_end_y;

		_array[11] = _gloss->uv_end_x;
		_array[12] = _gloss->uv_end_y;

		//..
		//.#
		_array[13] = _x + _w / 2.0f + sinf((135.0 + _rotation) * 0.017453f) * l;
		_array[14] = _y + _h / 2.0f + cosf((135.0 + _rotation) * 0.017453f) * l;
		_array[15] = 0.0f;

		_array[16] = NS_EGraphicCore::active_color[0];
		_array[17] = NS_EGraphicCore::active_color[1];
		_array[18] = NS_EGraphicCore::active_color[2];
		_array[19] = NS_EGraphicCore::active_color[3];

		_array[20] = _texture->uv_end_x;
		_array[21] = _texture->uv_start_y;

		_array[22] = _normal->uv_end_x;
		_array[23] = _normal->uv_start_y;

		_array[24] = _gloss->uv_end_x;
		_array[25] = _gloss->uv_start_y;

		//..
		//#.
		_array[26] = _x + _w / 2.0f + sinf((225.0f + _rotation) * 0.017453f) * l;
		_array[27] = _y + _h / 2.0f + cosf((225.0f + _rotation) * 0.017453f) * l;
		_array[28] = 0.0f;

		_array[29] = NS_EGraphicCore::active_color[0];
		_array[30] = NS_EGraphicCore::active_color[1];
		_array[31] = NS_EGraphicCore::active_color[2];
		_array[32] = NS_EGraphicCore::active_color[3];

		_array[33] = _texture->uv_start_x;
		_array[34] = _texture->uv_start_y;

		_array[35] = _normal->uv_start_x;
		_array[36] = _normal->uv_start_y;

		_array[37] = _gloss->uv_start_x;
		_array[38] = _gloss->uv_start_y;

		//#.
		//..
		_array[39] = _x + _w / 2.0f + sinf((315.0f + _rotation) * 0.017453f) * l;
		_array[40] = _y + _h / 2.0f + cosf((315.0f + _rotation) * 0.017453f) * l;
		_array[41] = 0.0f;

		_array[42] = NS_EGraphicCore::active_color[0];
		_array[43] = NS_EGraphicCore::active_color[1];
		_array[44] = NS_EGraphicCore::active_color[2];
		_array[45] = NS_EGraphicCore::active_color[3];

		_array[46] = _texture->uv_start_x;
		_array[47] = _texture->uv_end_y;

		_array[48] = _normal->uv_start_x;
		_array[49] = _normal->uv_end_y;

		_array[50] = _gloss->uv_start_x;
		_array[51] = _gloss->uv_end_y;

		_start_offset += 52;
	}
}

//void NS_ERenderCollection::add_data_to_vertex_buffer_rotated_square(float* _array, unsigned int& _start_offset, float _x, float _y, float _w, float _h, float _rotation, ETextureGabarite* _texture)
//{
//}

void NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_real_size(float* _array, unsigned int& _start_offset, float _x, float _y, ETextureGabarite* _texture)
{
	//address arithmetic, get pointer to buffer array, and move to +_offset
	_array += _start_offset;

	//[!][!][!]WARNING![!][!][!] It not "[0][1][2]..." index, it "[_start_offset + 0][_start_offset + 1][_start_offset + 2]..." index, see address arithmetic above
	_array[0] = (_x + _texture->size_x_in_pixels);
	_array[1] = (_y + _texture->size_y_in_pixels);

	_array[2] = NS_EGraphicCore::active_color[0];
	_array[3] = NS_EGraphicCore::active_color[1];
	_array[4] = NS_EGraphicCore::active_color[2];
	_array[5] = NS_EGraphicCore::active_color[3];

	_array[6] = _texture->uv_end_x;
	_array[7] = _texture->uv_end_y;

	//..
	//.#
	_array[8] = (_x + _texture->size_x_in_pixels);
	_array[9] = _y;

	_array[10] = NS_EGraphicCore::active_color[0];
	_array[11] = NS_EGraphicCore::active_color[1];
	_array[12] = NS_EGraphicCore::active_color[2];
	_array[13] = NS_EGraphicCore::active_color[3];

	_array[14] = _texture->uv_end_x;
	_array[15] = _texture->uv_start_y;

	//..
	//#.
	_array[16] = _x;
	_array[17] = _y;

	_array[18] = NS_EGraphicCore::active_color[0];
	_array[19] = NS_EGraphicCore::active_color[1];
	_array[20] = NS_EGraphicCore::active_color[2];
	_array[21] = NS_EGraphicCore::active_color[3];

	_array[22] = _texture->uv_start_x;
	_array[23] = _texture->uv_start_y;

	//#.
	//..
	_array[24] = _x;
	_array[25] = (_y + _texture->size_y_in_pixels);

	_array[26] = NS_EGraphicCore::active_color[0];
	_array[27] = NS_EGraphicCore::active_color[1];
	_array[28] = NS_EGraphicCore::active_color[2];
	_array[29] = NS_EGraphicCore::active_color[3];

	_array[30] = _texture->uv_start_x;
	_array[31] = _texture->uv_end_y;

	_start_offset += 32;


}

void NS_ERenderCollection::call_render_textured_rectangle_with_custom_size(ESprite* _sprite)
{
	NS_EGraphicCore::set_active_color(&(_sprite->sprite_color));

	if ((_sprite != nullptr) && (_sprite->main_texture != nullptr))
	{
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			_sprite->master_sprite_layer->vertex_buffer,
			_sprite->master_sprite_layer->last_buffer_id,

			_sprite->world_position_x,
			_sprite->world_position_y,

			_sprite->size_x,
			_sprite->size_y,

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
			_sprite->master_sprite_layer->last_buffer_id,
			_sprite->world_position_x,
			_sprite->world_position_y,
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

		NS_EGraphicCore::set_active_color(&(_sprite->sprite_color));

		NS_ERenderCollection::add_data_to_vertex_buffer_sprite
		(
			_sprite->master_sprite_layer->vertex_buffer,
			_sprite->master_sprite_layer->last_buffer_id,
			_sprite
		);
	}
	else
	{
		if (NSW_debug_graphic_to_console)
		{
			if (_sprite == nullptr) { EInputCore::logger_simple_error("Sprite in call render textured rectangle is null"); }
			else
			{
				if (_sprite->main_texture == nullptr) { EInputCore::logger_simple_error("[call_render_textured_sprite] sprite main texture is null"); }
			}
		}
	}
}

void NS_ERenderCollection::call_render_textured_sprite_test(ESprite* _sprite)
{

	//EInputCore::logger_simple_success("call render texured rectangle");

	//unsigned int zalupa;

	if ((_sprite != nullptr) && (_sprite->main_texture != nullptr))
	{
		//_sprite->master_sprite_layer->vertex_buffer = new float[100];

		NS_EGraphicCore::set_active_color(&_sprite->sprite_color);

		NS_ERenderCollection::add_data_to_vertex_buffer_sprite_test
		(
			_sprite->master_sprite_layer->vertex_buffer,
			_sprite->master_sprite_layer->last_buffer_id,
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

void NS_ERenderCollection::call_render_textured_sprite_PBR(ESprite* _sprite)
{
	{
		//EInputCore::logger_simple_success("call render texured rectangle");

		//unsigned int zalupa;

		if ((_sprite != nullptr) && (_sprite->main_texture != nullptr))
		{
			//_sprite->master_sprite_layer->vertex_buffer = new float[100];

			NS_EGraphicCore::set_active_color(&_sprite->sprite_color);

			NS_ERenderCollection::add_data_to_vertex_buffer_sprite_PBR
			(
				_sprite->master_sprite_layer->vertex_buffer,
				_sprite->master_sprite_layer->last_buffer_id,
				_sprite
			);
		}
		else
		{
			if (_sprite == nullptr) { EInputCore::logger_simple_error("[call_render_textured_sprite_PBR]Sprite is null"); }
			else
			{
				if (_sprite->main_texture == nullptr) { EInputCore::logger_simple_error("[call_render_textured_sprite_PBR] sprite main texture is null"); }
			}
		}
	}
}



void NS_ERenderCollection::set_brick_borders_and_subdivisions(float _left, float _right, float _bottom, float _up, int _subdivision_x, int _subdivision_y)
{
	border_left_size = _left;
	border_right_size = _right;

	border_down_size = _bottom;
	border_up_size = _up;

	subdivision_x = _subdivision_x;
	subdivision_y = _subdivision_y;

}

void NS_ERenderCollection::set_brick_borders_and_subdivisions(EBrickStyle _brick_style)
{
	border_left_size	= _brick_style.border_texture_size_left;
	border_right_size	= _brick_style.border_texture_size_right;

	border_down_size	= _brick_style.border_texture_size_bottom;
	border_up_size		= _brick_style.border_texture_size_up;

	subdivision_x		= _brick_style.subdivision_x;
	subdivision_y		= _brick_style.subdivision_y;
}

void NS_ERenderCollection::add_data_to_vertex_buffer_shade(float* _array, unsigned int& _start_offset, float _x, float _y, float _w, float _h, float _shade_size, ETextureGabarite* _texture)
{
	//address arithmetic, get pointer to buffer array, and move to +_offset
	_array += _start_offset;
	//[!][!][!]WARNING![!][!][!] It not "[0][1][2]..." index, it "[_start_offset + 0][_start_offset + 1][_start_offset + 2]..." index, see address arithmetic above

	//...
	//...
	//#..
	

		//.#
		//..
		_array[0] = (_x);
		_array[1] = (_y);

		_array[2] = NS_EGraphicCore::active_color[0];
		_array[3] = NS_EGraphicCore::active_color[1];
		_array[4] = NS_EGraphicCore::active_color[2];
		_array[5] = NS_EGraphicCore::active_color[3];

		_array[6] = _texture->uv_end_x;
		_array[7] = _texture->uv_end_y;

		//..
		//.#
		_array[8] = (_x);
		_array[9] = _y - _shade_size;

		_array[10] = NS_EGraphicCore::active_color[0];
		_array[11] = NS_EGraphicCore::active_color[1];
		_array[12] = NS_EGraphicCore::active_color[2];
		_array[13] = 0.0f;

		_array[14] = _texture->uv_end_x;
		_array[15] = _texture->uv_start_y;

		//..
		//#.
		_array[16] = _x - _shade_size;
		_array[17] = _y - _shade_size;

		_array[18] = NS_EGraphicCore::active_color[0];
		_array[19] = NS_EGraphicCore::active_color[1];
		_array[20] = NS_EGraphicCore::active_color[2];
		_array[21] = 0.0f;

		_array[22] = _texture->uv_start_x;
		_array[23] = _texture->uv_start_y;

		//#.
		//..
		_array[24] = _x - _shade_size;
		_array[25] = _y;

		_array[26] = NS_EGraphicCore::active_color[0];
		_array[27] = NS_EGraphicCore::active_color[1];
		_array[28] = NS_EGraphicCore::active_color[2];
		_array[29] = 0.0f;

		_array[30] = _texture->uv_start_x;
		_array[31] = _texture->uv_end_y;

		_start_offset += 32;

	//...
	//#..
	//...


		//.#
		//..
		_array += 32;

		_array[0] = (_x);
		_array[1] = (_y + _h);

		_array[2] = NS_EGraphicCore::active_color[0];
		_array[3] = NS_EGraphicCore::active_color[1];
		_array[4] = NS_EGraphicCore::active_color[2];
		_array[5] = NS_EGraphicCore::active_color[3];

		_array[6] = _texture->uv_end_x;
		_array[7] = _texture->uv_end_y;

		//..
		//.#
		_array[8] = (_x);
		_array[9] = _y;

		_array[10] = NS_EGraphicCore::active_color[0];
		_array[11] = NS_EGraphicCore::active_color[1];
		_array[12] = NS_EGraphicCore::active_color[2];
		_array[13] = NS_EGraphicCore::active_color[3];

		_array[14] = _texture->uv_end_x;
		_array[15] = _texture->uv_start_y;

		//..
		//#.
		_array[16] = _x - _shade_size;
		_array[17] = _y;

		_array[18] = NS_EGraphicCore::active_color[0];
		_array[19] = NS_EGraphicCore::active_color[1];
		_array[20] = NS_EGraphicCore::active_color[2];
		_array[21] = 0.0f;

		_array[22] = _texture->uv_start_x;
		_array[23] = _texture->uv_start_y;

		//#.
		//..
		_array[24] = _x - _shade_size;
		_array[25] = _y + _h;

		_array[26] = NS_EGraphicCore::active_color[0];
		_array[27] = NS_EGraphicCore::active_color[1];
		_array[28] = NS_EGraphicCore::active_color[2];
		_array[29] = 0.0f;

		_array[30] = _texture->uv_start_x;
		_array[31] = _texture->uv_end_y;

		_start_offset += 32;
	
	
	//#..
	//...
	//...


		//..
		//.#
		_array += 32;

		_array[0] = (_x);
		_array[1] = (_y + _h);

		_array[2] = NS_EGraphicCore::active_color[0];
		_array[3] = NS_EGraphicCore::active_color[1];
		_array[4] = NS_EGraphicCore::active_color[2];
		_array[5] = NS_EGraphicCore::active_color[3];

		_array[6] = _texture->uv_end_x;
		_array[7] = _texture->uv_end_y;

		//.#
		//..
		_array[8] = (_x);
		_array[9] = _y + _h + _shade_size;

		_array[10] = NS_EGraphicCore::active_color[0];
		_array[11] = NS_EGraphicCore::active_color[1];
		_array[12] = NS_EGraphicCore::active_color[2];
		_array[13] = 0.0f;

		_array[14] = _texture->uv_end_x;
		_array[15] = _texture->uv_start_y;

		//#.
		//..
		_array[16] = _x - _shade_size;
		_array[17] = _y + _h + _shade_size;

		_array[18] = NS_EGraphicCore::active_color[0];
		_array[19] = NS_EGraphicCore::active_color[1];
		_array[20] = NS_EGraphicCore::active_color[2];
		_array[21] = 0.0f;

		_array[22] = _texture->uv_start_x;
		_array[23] = _texture->uv_start_y;

		//..
		//#.
		_array[24] = _x - _shade_size;
		_array[25] = _y + _h;

		_array[26] = NS_EGraphicCore::active_color[0];
		_array[27] = NS_EGraphicCore::active_color[1];
		_array[28] = NS_EGraphicCore::active_color[2];
		_array[29] = 0.0f;

		_array[30] = _texture->uv_start_x;
		_array[31] = _texture->uv_end_y;

		_start_offset += 32;

	//...
	//...
	//..#
	

		//#.
		//..
		_array += 32;

		_array[0] = (_x + _w);
		_array[1] = (_y);

		_array[2] = NS_EGraphicCore::active_color[0];
		_array[3] = NS_EGraphicCore::active_color[1];
		_array[4] = NS_EGraphicCore::active_color[2];
		_array[5] = NS_EGraphicCore::active_color[3];

		_array[6] = _texture->uv_end_x;
		_array[7] = _texture->uv_end_y;

		//..
		//#.
		_array[8] = (_x + _w);
		_array[9] = _y - _shade_size;

		_array[10] = NS_EGraphicCore::active_color[0];
		_array[11] = NS_EGraphicCore::active_color[1];
		_array[12] = NS_EGraphicCore::active_color[2];
		_array[13] = 0.0f;

		_array[14] = _texture->uv_end_x;
		_array[15] = _texture->uv_start_y;

		//..
		//.#
		_array[16] = _x + _w + _shade_size;
		_array[17] = _y - _shade_size;

		_array[18] = NS_EGraphicCore::active_color[0];
		_array[19] = NS_EGraphicCore::active_color[1];
		_array[20] = NS_EGraphicCore::active_color[2];
		_array[21] = 0.0f;

		_array[22] = _texture->uv_start_x;
		_array[23] = _texture->uv_start_y;

		//.#
		//..
		_array[24] = _x + _w + _shade_size;
		_array[25] = _y;

		_array[26] = NS_EGraphicCore::active_color[0];
		_array[27] = NS_EGraphicCore::active_color[1];
		_array[28] = NS_EGraphicCore::active_color[2];
		_array[29] = 0.0f;

		_array[30] = _texture->uv_start_x;
		_array[31] = _texture->uv_end_y;

		_start_offset += 32;

	//...
	//..#
	//...


		//#.
		//..
		_array += 32;

		_array[0] = (_x + _w);
		_array[1] = (_y + _h);

		_array[2] = NS_EGraphicCore::active_color[0];
		_array[3] = NS_EGraphicCore::active_color[1];
		_array[4] = NS_EGraphicCore::active_color[2];
		_array[5] = NS_EGraphicCore::active_color[3];

		_array[6] = _texture->uv_end_x;
		_array[7] = _texture->uv_end_y;

		//..
		//#.
		_array[8] = (_x + _w);
		_array[9] = _y;

		_array[10] = NS_EGraphicCore::active_color[0];
		_array[11] = NS_EGraphicCore::active_color[1];
		_array[12] = NS_EGraphicCore::active_color[2];
		_array[13] = NS_EGraphicCore::active_color[3];

		_array[14] = _texture->uv_end_x;
		_array[15] = _texture->uv_start_y;

		//..
		//.#
		_array[16] = _x + _w + _shade_size;
		_array[17] = _y;

		_array[18] = NS_EGraphicCore::active_color[0];
		_array[19] = NS_EGraphicCore::active_color[1];
		_array[20] = NS_EGraphicCore::active_color[2];
		_array[21] = 0.0f;

		_array[22] = _texture->uv_start_x;
		_array[23] = _texture->uv_start_y;

		//.#
		//..
		_array[24] = _x + _w + _shade_size;
		_array[25] = _y + _h;

		_array[26] = NS_EGraphicCore::active_color[0];
		_array[27] = NS_EGraphicCore::active_color[1];
		_array[28] = NS_EGraphicCore::active_color[2];
		_array[29] = 0.0f;

		_array[30] = _texture->uv_start_x;
		_array[31] = _texture->uv_end_y;

		_start_offset += 32;
	
	
	//..#
	//...
	//...


		//..
		//#.
		_array += 32;

		_array[0] = (_x + _w);
		_array[1] = (_y + _h);

		_array[2] = NS_EGraphicCore::active_color[0];
		_array[3] = NS_EGraphicCore::active_color[1];
		_array[4] = NS_EGraphicCore::active_color[2];
		_array[5] = NS_EGraphicCore::active_color[3];

		_array[6] = _texture->uv_end_x;
		_array[7] = _texture->uv_end_y;

		//#.
		//..
		_array[8] = (_x + _w);
		_array[9] = _y + _h + _shade_size;

		_array[10] = NS_EGraphicCore::active_color[0];
		_array[11] = NS_EGraphicCore::active_color[1];
		_array[12] = NS_EGraphicCore::active_color[2];
		_array[13] = 0.0f;

		_array[14] = _texture->uv_end_x;
		_array[15] = _texture->uv_start_y;

		//.#
		//..
		_array[16] = _x + _w + _shade_size;
		_array[17] = _y + _h + _shade_size;

		_array[18] = NS_EGraphicCore::active_color[0];
		_array[19] = NS_EGraphicCore::active_color[1];
		_array[20] = NS_EGraphicCore::active_color[2];
		_array[21] = 0.0f;

		_array[22] = _texture->uv_start_x;
		_array[23] = _texture->uv_start_y;

		//..
		//.#
		_array[24] = _x + _w + _shade_size;
		_array[25] = _y + _h;

		_array[26] = NS_EGraphicCore::active_color[0];
		_array[27] = NS_EGraphicCore::active_color[1];
		_array[28] = NS_EGraphicCore::active_color[2];
		_array[29] = 0.0f;

		_array[30] = _texture->uv_start_x;
		_array[31] = _texture->uv_end_y;

		_start_offset += 32;

	//...
	//...
	//.#.


		//#.
		//..
		_array += 32;

		_array[0] = (_x);
		_array[1] = (_y);

		_array[2] = NS_EGraphicCore::active_color[0];
		_array[3] = NS_EGraphicCore::active_color[1];
		_array[4] = NS_EGraphicCore::active_color[2];
		_array[5] = NS_EGraphicCore::active_color[3];

		_array[6] = _texture->uv_end_x;
		_array[7] = _texture->uv_end_y;

		//..
		//#.
		_array[8] = (_x);
		_array[9] = _y - _shade_size;

		_array[10] = NS_EGraphicCore::active_color[0];
		_array[11] = NS_EGraphicCore::active_color[1];
		_array[12] = NS_EGraphicCore::active_color[2];
		_array[13] = 0.0f;

		_array[14] = _texture->uv_end_x;
		_array[15] = _texture->uv_start_y;

		//..
		//.#
		_array[16] = _x + _w;
		_array[17] = _y - _shade_size;

		_array[18] = NS_EGraphicCore::active_color[0];
		_array[19] = NS_EGraphicCore::active_color[1];
		_array[20] = NS_EGraphicCore::active_color[2];
		_array[21] = 0.0f;

		_array[22] = _texture->uv_start_x;
		_array[23] = _texture->uv_start_y;

		//.#
		//..
		_array[24] = _x + _w;
		_array[25] = _y;

		_array[26] = NS_EGraphicCore::active_color[0];
		_array[27] = NS_EGraphicCore::active_color[1];
		_array[28] = NS_EGraphicCore::active_color[2];
		_array[29] = NS_EGraphicCore::active_color[3];

		_array[30] = _texture->uv_start_x;
		_array[31] = _texture->uv_end_y;

		_start_offset += 32;

	//.#.
	//...
	//...


		//..
		//#.
		_array += 32;

		_array[0] = (_x);
		_array[1] = (_y + _h);

		_array[2] = NS_EGraphicCore::active_color[0];
		_array[3] = NS_EGraphicCore::active_color[1];
		_array[4] = NS_EGraphicCore::active_color[2];
		_array[5] = NS_EGraphicCore::active_color[3];

		_array[6] = _texture->uv_end_x;
		_array[7] = _texture->uv_end_y;

		//..
		//.#
		_array[8] = (_x + _w);
		_array[9] = _y + _h;

		_array[10] = NS_EGraphicCore::active_color[0];
		_array[11] = NS_EGraphicCore::active_color[1];
		_array[12] = NS_EGraphicCore::active_color[2];
		_array[13] = NS_EGraphicCore::active_color[3];

		_array[14] = _texture->uv_end_x;
		_array[15] = _texture->uv_start_y;

		//.#
		//..
		_array[16] = _x + _w;
		_array[17] = _y + _h +  _shade_size;

		_array[18] = NS_EGraphicCore::active_color[0];
		_array[19] = NS_EGraphicCore::active_color[1];
		_array[20] = NS_EGraphicCore::active_color[2];
		_array[21] = 0.0f;

		_array[22] = _texture->uv_start_x;
		_array[23] = _texture->uv_start_y;

		//#.
		//..
		_array[24] = _x;
		_array[25] = _y + _h + _shade_size;

		_array[26] = NS_EGraphicCore::active_color[0];
		_array[27] = NS_EGraphicCore::active_color[1];
		_array[28] = NS_EGraphicCore::active_color[2];
		_array[29] = 0.0f;

		_array[30] = _texture->uv_start_x;
		_array[31] = _texture->uv_end_y;

		_start_offset += 32;


}

void NS_ERenderCollection::generate_brick_texture(ERegionGabarite* _region, ESpriteLayer* _sprite_layer, ETextureGabarite* _texture_gabarite, ETextureGabarite* _normal_map_gabarite, ETextureGabarite* _gloss_map_gabarite)
{




	if ((_region != nullptr) && (_sprite_layer != nullptr) && (_texture_gabarite != nullptr))
	{
		_sprite_layer->autodeletable = false;

		for (int i = 0; i < _sprite_layer->sprite_frame_list.size(); i++)
		{
			if (!disable_deleting) {delete _sprite_layer->sprite_frame_list[i];}
		}
		_sprite_layer->sprite_frame_list.resize(0);
		_sprite_layer->sprite_frame_list.shrink_to_fit();

		_sprite_layer->batcher = NS_EGraphicCore::pbr_batcher;
		//_sprite_layer->batcher->reset();
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
		float	size_of_brick_x = _texture_gabarite->size_x_in_pixels / (float)total_divisions_x;
		//size of one tile (y)
		float	size_of_brick_y = _texture_gabarite->size_y_in_pixels / (float)total_divisions_y;

		//uv offset in texture in pixels (x)
		float	texture_offset_x = 0.0f;
		//uv offset in texture in pixels (y)
		float	texture_offset_y = 0.0f;

		//tile offset x
		float	final_offset_x = 0.0f;
		//tile offset y
		float	final_offset_yz = 0.0f;

		int total_sprites = 4;

		int current_sprite_frame_id = 0;
		ESprite* current_sprite;

		unsigned int selected_random_x = 0;
		unsigned int selected_random_y = 0;

		static ESpriteFrame* jc_sprite_frame = ESpriteFrame::create_default_sprite_frame_with_sprite(_texture_gabarite, _sprite_layer);;

		//static
		float full_segment_size_x = _region->size_x;
		float full_segment_size_y = _region->size_y;

		float cropped_mid_segment_size_x = full_segment_size_x - NS_ERenderCollection::border_left_size - NS_ERenderCollection::border_right_size;
		float cropped_mid_segment_size_y = full_segment_size_y - NS_ERenderCollection::border_down_size - NS_ERenderCollection::border_up_size;

		float final_mid_segment_size_x = full_segment_size_x - NS_ERenderCollection::border_left_size - NS_ERenderCollection::border_right_size;
		float final_mid_segment_size_y = full_segment_size_y - NS_ERenderCollection::border_up_size - NS_ERenderCollection::border_down_size;

		float mid_brick_size_x = (_texture_gabarite->size_x_in_pixels - NS_ERenderCollection::border_left_size - NS_ERenderCollection::border_right_size) / (float)(NS_ERenderCollection::subdivision_x + 1);
		float mid_brick_size_y = (_texture_gabarite->size_y_in_pixels - NS_ERenderCollection::border_down_size - NS_ERenderCollection::border_up_size) / (float)(NS_ERenderCollection::subdivision_y + 1);

		total_sprites = 4;
		//mid section
		if (ceil(cropped_mid_segment_size_x / mid_brick_size_x) * ceil(cropped_mid_segment_size_y / mid_brick_size_y) > 0)
		{
			total_sprites += ceil(cropped_mid_segment_size_x / mid_brick_size_x) * ceil(cropped_mid_segment_size_y / mid_brick_size_y);
		}

		//borders
		if (ceil(cropped_mid_segment_size_x / mid_brick_size_x) * 2 + ceil(cropped_mid_segment_size_y / mid_brick_size_y) * 2 > 0)
		{
			total_sprites += ceil(cropped_mid_segment_size_x / mid_brick_size_x) * 2 + ceil(cropped_mid_segment_size_y / mid_brick_size_y) * 2;
		}

		//total_sprites *= 6;
		////total_sprites *= 4;
		//if (total_sprites >)

	
		

		//delete and create vertext buffer, if size changed, or create new buffer, if old not exist
		if (_sprite_layer == nullptr)//something wrong, sprite layer is NULL
		{}
		else
		{
			int new_capacity = total_sprites * _sprite_layer->batcher->gl_vertex_attribute_total_count * 4;

			if (new_capacity <= 0)//no one vertex buffer will created, no sense to create new VB. Existing VB will be destroyed
			{
				if (_sprite_layer->vertex_buffer != nullptr)
				{
					if (!disable_deleting) { delete[] _sprite_layer->vertex_buffer; }
					_sprite_layer->vertex_buffer = nullptr;
				}
			}
			else
			{
				//buffer not exist, create new
				if (_sprite_layer->vertex_buffer == nullptr)
				{
					_sprite_layer->vertex_buffer = new float[new_capacity];
				}
				else
				{
					if (new_capacity != _sprite_layer->total_capacity)//size of VB changed, or VB still not created
					{
						if (_sprite_layer->vertex_buffer != nullptr)
						{
							if (!disable_deleting) { delete[] _sprite_layer->vertex_buffer; }
							_sprite_layer->vertex_buffer = new float[new_capacity];
						}
					}
					else//
					{

					}
				}
			}

			_sprite_layer->last_buffer_id = 0;
			_sprite_layer->total_capacity = new_capacity;
		}

		
		//ETextureGabarite* autoloaded_normal_map	= NS_EGraphicCore::get_gabarite_from_full_path_and_suffix(_texture_gabarite, "[normal_map]");
		//ETextureGabarite* autoloaded_gloss_map	= NS_EGraphicCore::get_gabarite_from_full_path_and_suffix(_texture_gabarite, "[gloss_map]");

		//EInputCore::logger_param("cropped segment x", cropped_mid_segment_size_x);

		//EInputCore::logger_param("EXCEPT SPRITES COUNT", total_sprites);

		int real_sprites_count = 0;
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
	// 
		//EInputCore::logger_simple_info("invoke brick generator");





		//std::cout << "successed deleted" << std::endl;




		//std::cout << "successed deleted" << std::endl;
		//EInputCore::logger_simple_info("began generate bricks");
		if ((true) && (total_sprites > 0))
			for (unsigned int seg_y = 0; seg_y < 3; seg_y++)
			{

				//down border

				if ((seg_y == 0))//down
				{
					total_divisions_y = 1;
					size_of_brick_y = NS_ERenderCollection::border_down_size;

					base_offset_yz = 0.0f;

					final_fragments_count_y = 1.0f;
					count_of_generations_y = 1;

					texture_offset_y = 0.0f;
				}
				else
					//mid wall
					if ((seg_y == 1))
					{
						total_divisions_y = NS_ERenderCollection::subdivision_y + 1;
						size_of_brick_y = mid_brick_size_y;

						base_offset_yz = 0.0f + NS_ERenderCollection::border_down_size + 0.0f;

						final_fragments_count_y = cropped_mid_segment_size_y / size_of_brick_y;
						count_of_generations_y = ceil(final_fragments_count_y);

						texture_offset_y = NS_ERenderCollection::border_down_size;
					}
					else
						//up border
						if ((seg_y == 2))
						{
							total_divisions_y = 1;
							size_of_brick_y = NS_ERenderCollection::border_up_size;

							base_offset_yz = 0.0f + cropped_mid_segment_size_y + NS_ERenderCollection::border_down_size + 0.0f;

							final_fragments_count_y = 1.0f;
							count_of_generations_y = 1;

							texture_offset_y = _texture_gabarite->size_y_in_pixels - NS_ERenderCollection::border_up_size;
						}

				for (unsigned int seg_x = 0; seg_x < 3; seg_x++)
				{



					if ((seg_x == 0))
					{
						total_divisions_x = 1;
						size_of_brick_x = NS_ERenderCollection::border_left_size;

						base_offset_x = 0.0f + 0.0f;

						final_fragments_count_x = 1.0f;
						count_of_generations_x = 1;

						texture_offset_x = 0.0f;
					}
					else
						//mid wall
						if ((seg_x == 1))
						{
							total_divisions_x = NS_ERenderCollection::subdivision_x + 1;
							size_of_brick_x = mid_brick_size_x;

							base_offset_x = 0.0f + NS_ERenderCollection::border_left_size + 0.0f;

							final_fragments_count_x = (cropped_mid_segment_size_x - 0.0f) / size_of_brick_x;
							count_of_generations_x = ceil(final_fragments_count_x);

							texture_offset_x = NS_ERenderCollection::border_left_size;
						}
						else
							if ((seg_x == 2))
							{
								total_divisions_x = 1;
								size_of_brick_x = NS_ERenderCollection::border_right_size;

								base_offset_x = 0.0f + cropped_mid_segment_size_x + NS_ERenderCollection::border_left_size + 0.0f;

								final_fragments_count_x = 1.0f;
								count_of_generations_x = 1;

								texture_offset_x = _texture_gabarite->size_x_in_pixels - NS_ERenderCollection::border_right_size;
							}


					final_offset_yz = base_offset_yz;



					for (int yy = 0; yy < count_of_generations_y; yy++)
					{
						final_offset_x = base_offset_x;

						for (int xx = 0; xx < count_of_generations_x; xx++)//base_sprite_fragment_offset_x = full_mid_segment_size_x - NS_ERenderCollection::border_left_size;
						{

							selected_random_x = (rand() % (total_divisions_x)*size_of_brick_x);
							selected_random_y = (rand() % (total_divisions_y)*size_of_brick_y);

							
							
								//_sprite_layer->sprite_frame_list.at(current_sprite_frame_id)->marked_as_temporary = temporary_sprites;
								current_sprite = jc_sprite_frame->sprite_list.at(0);
								//current_sprite->reset_sprite();
								
								current_sprite->pointer_to_sprite_render = &NS_ERenderCollection::call_render_textured_sprite_PBR;

								current_sprite->set_texture_gabarite(_texture_gabarite, _normal_map_gabarite, _gloss_map_gabarite);
								
								current_sprite->fragment_offset_x = texture_offset_x + selected_random_x;
								current_sprite->fragment_offset_y = texture_offset_y + selected_random_y;

								current_sprite->offset_x = final_offset_x;
								current_sprite->offset_y = final_offset_yz;

								current_sprite->world_position_x = _region->world_position_x + final_offset_x;
								current_sprite->world_position_y = _region->world_position_y + final_offset_yz;

								current_sprite->fragment_size_x = min(final_fragments_count_x - xx, 1.0f) * size_of_brick_x;
								current_sprite->fragment_size_y = min(final_fragments_count_y - yy, 1.0f) * size_of_brick_y;

								current_sprite->size_x = current_sprite->fragment_size_x;
								current_sprite->size_y = current_sprite->fragment_size_y;

								//if ((seg_x == seg_y) && (seg_x == 1)) { *current_sprite->size_x = 0.0f; *current_sprite->size_x = 0.0f; }

								current_sprite->sprite_calculate_uv();

								real_sprites_count++;

							final_offset_x += size_of_brick_x + 0.0f;



							NS_EGraphicCore::set_active_color(&current_sprite->sprite_color);

							//EInputCore::logger_param("xx", xx);
							//EInputCore::logger_param("yy", yy);
							//
							//EInputCore::logger_param("gen x", count_of_generations_x);
							//EInputCore::logger_param("gen y", count_of_generations_y);

							//EInputCore::logger_param("total sprites", total_sprites);

							//EInputCore::logger_param("last buffer id", _sprite_layer->last_buffer_id);
							//EInputCore::logger_param("total capacity", _sprite_layer->total_capacity);

							if (_sprite_layer->last_buffer_id + _sprite_layer->batcher->gl_vertex_attribute_total_count * 4 <= _sprite_layer->total_capacity)
							{
								NS_ERenderCollection::add_data_to_vertex_buffer_sprite_PBR
								(
									_sprite_layer->vertex_buffer,
									_sprite_layer->last_buffer_id,
									current_sprite
								);
							}
							else
							{
								//EInputCore::logger_simple_error("over capacity [" + std::to_string(_sprite_layer->last_buffer_id) + "/" + std::to_string(_sprite_layer->total_capacity) + "]");
								//_sprite_layer->last_buffer_id += 52;
							}

							//EInputCore::logger_param("last buffer id [post]", _sprite_layer->last_buffer_id);

							//std::cout << std::endl << std::endl;


							/*NS_ERenderCollection::add_data_to_vertex_buffer_texture_fragment_PBR
							(
								_sprite_layer->batcher->vertex_buffer,
								_sprite_layer->batcher->last_vertice_buffer_index,

								_region->world_position_x + final_offset_x,
								_region->world_position_y + final_offset_yz,

								min(final_fragments_count_x - xx, 1.0f) * size_of_brick_x,
								min(final_fragments_count_y - yy, 1.0f) * size_of_brick_y,

								_texture_gabarite->target_atlas->get_atlas_size_x() / min(final_fragments_count_x - xx, 1.0f) * size_of_brick_x,
								_texture_gabarite->target_atlas->get_atlas_size_y() / min(final_fragments_count_y - yy, 1.0f) * size_of_brick_y,

								_texture_gabarite,
								_gloss_map_gabarite,
								_normal_map_gabarite
							);*/

							//NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
							//(
							//	_sprite_layer->batcher->vertex_buffer,
							//	_sprite_layer->batcher->last_vertice_buffer_index,

							//	_region->world_position_x + final_offset_x,
							//	_region->world_position_y + final_offset_yz,

							//	10.0f,
							//	10.0f,

							//	_texture_gabarite,
							//);

							current_sprite_frame_id++;

						}//base_sprite_fragment_offset_x = full_mid_segment_size_x - NS_ERenderCollection::border_left_size;

						final_offset_yz += size_of_brick_y + 0.0f;



					}
				}
			}

			//EInputCore::logger_param("REAL SPRITES COUNT", real_sprites_count);
		//for (int i = current_sprite_frame_id; i < _sprite_layer->sprite_frame_list.size(); i++)
		//{
		//	_sprite_layer->sprite_frame_list[i]->sprite_list[0]->reset_sprite();
		//}

		if (false)
			if (!_sprite_layer->sprite_frame_list.empty())
			{
				for (int i = current_sprite_frame_id; i < _sprite_layer->sprite_frame_list.size(); i++)
					//for (ESpriteFrame* frm : _sprite_layer->sprite_frame_list)
				{
					//frm->sprite_list[0]->reset_sprite();
					//std::cout << "deleting sprite frame at[" << std::to_string(i) << "]" << std::endl;

					if (!disable_deleting){delete _sprite_layer->sprite_frame_list.at(i);}
				}
				//_sprite_layer->last_buffer_id = 0;
				//_sprite_layer->total_capacity = 0;
				_sprite_layer->sprite_frame_list.resize(current_sprite_frame_id);
				_sprite_layer->sprite_frame_list.shrink_to_fit();
			}

		//_sprite_layer->generate_vertex_buffer_for_sprite_layer("autobuilding");


	}
	else
	{
		if (_region == nullptr) { EInputCore::logger_simple_error("_region in [brick generator] is null!"); }
		if (_sprite_layer == nullptr) { EInputCore::logger_simple_error("_sprite_layer in [brick generator] is null!"); }
		if (_texture_gabarite == nullptr) { EInputCore::logger_simple_error("_texture gabarite in [brick generator] is null!"); }
	}
}

void NS_EGraphicCore::processInput(GLFWwindow* window)
{
}

void NS_EGraphicCore::refresh_autosize_groups(EWindow* _window)
{
	int dynamic_elements = 0;
	float static_elements_total_size = 0.0f;

	float full_size_x = NS_EGraphicCore::SCREEN_WIDTH / NS_EGraphicCore::current_zoom;
	float free_dynamic_size_y = NS_EGraphicCore::SCREEN_HEIGHT / NS_EGraphicCore::current_zoom;



	for (EButtonGroup* bg : _window->autosize_group_list)
	{
		bg->region_gabarite->size_x = full_size_x;
		bg->base_width = full_size_x;



		if (bg->dynamic_autosize_for_window)
		{
			dynamic_elements++;
		}
		else
		{
			//basic size
			free_dynamic_size_y -= bg->base_height;

			//real, expanded size
			if (bg->can_resize_to_workspace_size_y)
			{
				free_dynamic_size_y -= bg->group_offset_for_content_bottom + bg->group_offset_for_content_up;
			}
		}
	}

	//EInputCore::logger_simple_info("window list");
	for (EButtonGroup* bg : _window->autosize_group_list)
	{


		if (bg->dynamic_autosize_for_window)
		{
			bg->base_height = free_dynamic_size_y / (float)dynamic_elements;
			bg->region_gabarite->size_y = free_dynamic_size_y / (float)dynamic_elements;
		}
		else
		{
			bg->region_gabarite->size_y = bg->base_height;
		}

		if (bg->can_resize_to_workspace_size_y)
		{
			bg->region_gabarite->size_y += bg->group_offset_for_content_bottom + bg->group_offset_for_content_up;
			//bg->base_height -= bg->border_bottom + bg->border_up;
		}
	}

	EButtonGroup* prev_group = nullptr;
	for (EButtonGroup* bg : _window->autosize_group_list)
	{
		if (prev_group == nullptr)
		{
			bg->region_gabarite->offset_x = 0.0f;
			bg->region_gabarite->offset_y = 0.0f;
		}
		else
		{
			bg->region_gabarite->offset_x = 0.0f;
			bg->region_gabarite->offset_y = (prev_group->region_gabarite->offset_y + prev_group->region_gabarite->size_y);
		}

		prev_group = bg;

		//EInputCore::logger_param("autosize y", prev_group->region_gabarite->size_y);
	}
}

void NS_EGraphicCore::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{//

		//width = round(width / 2.0f) * 2;
		//height = round(height / 2.0f) * 2;
		//glScissor(0, 0, 500, 500);

		//glViewport(0, 0, width, height);

		old_w = NS_EGraphicCore::SCREEN_WIDTH;
		old_h = NS_EGraphicCore::SCREEN_HEIGHT;

		glfwGetWindowSize(window, &NS_EGraphicCore::SCREEN_WIDTH, &NS_EGraphicCore::SCREEN_HEIGHT);

		changed_resolution = true; 
		
}

void NS_EGraphicCore::recalculate_correction()
{
	if ((NS_EGraphicCore::SCREEN_WIDTH > 100) && (NS_EGraphicCore::SCREEN_HEIGHT > 100))
	{
		NS_EGraphicCore::correction_x = 1.0f / NS_EGraphicCore::SCREEN_WIDTH;
		NS_EGraphicCore::correction_y = 1.0f / NS_EGraphicCore::SCREEN_HEIGHT;

		//std::cout << "helper correction_x: " << correction_x << " correction_y: " << correction_y << std::endl;
	}

	NS_EGraphicCore::default_batcher_for_drawing->set_transform_screen_size(NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT);
	NS_EGraphicCore::test_batcher->set_transform_screen_size(NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT);
	NS_EGraphicCore::pbr_batcher->set_transform_screen_size(NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT);
}

std::string ETextureGabarite::get_full_path()
{
	return *full_path;
}

std::vector<ETextureGabarite*> ETextureGabarite::incomplete_gabarites_list;
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
	return *localised_name;
}

int ESpriteLayer::data_copies_count = 0;
int ESpriteLayer::data_copy_calls = 0;

ESpriteLayer::~ESpriteLayer()
{
	if (!disable_deleting) {
		destroy_vertex_buffer();
	}

	//if (!disable_deleting) {delete[] vertex_buffer;}


	for (ESpriteFrame* frame : sprite_frame_list)
	{
		if (!disable_deleting) {delete frame;}
	}

	sprite_frame_list.clear();
	sprite_frame_list.shrink_to_fit();
}

void ESpriteLayer::translate_sprite_layer(float _x, float _y, float _z, bool _move_positions)
{

	world_position_x += _x;
	world_position_y += _y;
	world_position_z += _z;

	if (_move_positions)
	{
		offset_x += _x;
		offset_y += _y;
		offset_z += _z;
	}

	//child elements, modify only world coordinates
	//translate_sprites(_x, _y, _z, false);


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

	*localised_name = _name.substr(start_s, end_s - start_s + 1);
}

void ETextureGabarite::set_uv_parameters(float _uv_start_x, float _uv_start_y, float _uv_size_x, float _uv_size_y)
{
	uv_start_x = _uv_start_x;
	uv_start_y = _uv_start_y;

	uv_end_x = _uv_start_x + _uv_size_x;
	uv_end_y = _uv_start_y + _uv_size_y;

	uv_size_x = _uv_size_x;
	uv_size_y = _uv_size_y;

	//EInputCore::logger_param("uv_start_x", *uv_start_x);
	//EInputCore::logger_param("uv_start_y", *uv_start_y);

	//EInputCore::logger_param("uv_end_x", *uv_end_x);
	//EInputCore::logger_param("uv_end_y", *uv_end_y);
}

void ETextureGabarite::set_real_texture_size(int _size_x, int _size_y)
{
	size_x_in_pixels = _size_x;
	size_y_in_pixels = _size_y;
}


void ESpriteLayer::modify_buffer_position_for_sprite_layer(float _x, float _y, float _z)
{
	for (unsigned int k = 0; k < 4; k++)																	//4 vertex
		for (unsigned int i = 0; i < last_buffer_id; i += batcher->gl_vertex_attribute_total_count * 4)		//1 shape = attribute counts * 4 vertex
		{
			vertex_buffer[i + k * batcher->gl_vertex_attribute_total_count + batcher->array_offset_for_x] += _x;								//offset 0 = x
			vertex_buffer[i + k * batcher->gl_vertex_attribute_total_count + batcher->array_offset_for_y] += _y;								//offset 1 = y

			//offset z
			if (batcher->array_offset_for_z >= 0) { vertex_buffer[i + k * batcher->gl_vertex_attribute_total_count + batcher->array_offset_for_z] += _z; }
		}



	//for (ESpriteFrame* frame:sprite_frame_list)
	//for (ESprite* spr : frame->sprite_list)
	//{
	//	*spr->offset_x += _x;
	//	*spr->offset_y += _y;
	//	*spr->offset_z += _z;
	//}
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
		//if (sprite_frame_list.size() * batcher->gl_vertex_attribute_total_count * 4 >= *last_buffer_id)
		if ((total_capacity > 0) && (vertex_buffer != nullptr) && (autodeletable))
		{
			if (!disable_deleting) {delete[] vertex_buffer;}
		}

		if (!sprite_frame_list.empty())
		{
			vertex_buffer = new float[sprite_frame_list.size() * batcher->gl_vertex_attribute_total_count * 4];
			//EInputCore::logger_param("length", sprite_frame_list.size() * batcher->gl_vertex_attribute_total_count * 4);
			total_capacity = sprite_frame_list.size() * batcher->gl_vertex_attribute_total_count * 4;

			last_buffer_id = 0;
		}




		//for (ESpriteFrame* frame:sprite_frame_list)
		for (unsigned int i = 0; i < sprite_frame_list.size(); i++)
		{
			ESpriteFrame* frame = sprite_frame_list[i];
			ESprite* spr = frame->sprite_list.at(frame->active_frame_id);
			//EInputCore::logger_param("frame id", *frame->active_frame_id);
			//EInputCore::logger_param("texture name", spr->main_texture->get_name());
			//EInputCore::logger_param("memory", spr);

			//std::cout << "memory location" << spr << std::endl;
			if ((spr != nullptr) && (spr->size_x * spr->size_y > 0) && (spr->pointer_to_sprite_render != nullptr))
			{
				//EInputCore::logger_simple_success("try call render by pointer[" + std::to_string(_text) + "]");
				//NS_EGraphicCore::set_active_color(spr->sprite_color);
				ERenderBatcher::if_have_space_for_data(batcher, 1);
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
		(last_buffer_id > 0)
		&&
		(
			(batcher != nullptr)
		)
		&&
		(!disable_draw)
	)
	{
		//memcpy();
		//std::cout << "-------" << std::endl;

		//[32000]
		//size of BATCHER vertex array
		unsigned int batcher_size = TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE - 200;
		//EInputCore::logger_param("vertices_buffer_capacity", vertices_buffer_capacity);

		//[31872]
		//size of SPRITE LAYER vertex array
		int remaining_data = last_buffer_id;
		//EInputCore::logger_param("data_size", data_size);

		//sprite layer array can be bigger than batcher array. in this case we need copy sprite array partially
		//unsigned int passes = ceil(layer_data_count / (float)batcher_size);
		//EInputCore::logger_param("passes", passes);

		unsigned int copy_start = 0;
		unsigned int batcher_free_space = batcher_size - batcher->last_vertice_buffer_index;
		unsigned int data_part = 0;

		while (true)
		{



			//if batcher have free space
			if (batcher_free_space > 0)
			{
				data_part = min(remaining_data, batcher_free_space);

				data_copy_calls++;

				memcpy
				(
					batcher->vertex_buffer + batcher->last_vertice_buffer_index,	//add to batcher vertex buffer
					vertex_buffer + (copy_start),									//get from sprite layer vertex buffer
					data_part * sizeof(float)
				);

				data_copies_count += data_part * sizeof(float);

				copy_start += data_part;

				batcher->last_vertice_buffer_index += data_part;
				remaining_data -= data_part;
				batcher_free_space -= data_part;


				//if (batcher->last_vertice_buffer_index >= batcher_size)
				//{
				//	batcher->draw_call();
				//	batcher_free_space = batcher_size;
				//}
			}
			else
			{
				EInputCore::logger_simple_info("free space in batcher consumed, draw call");
				batcher->draw_call();
				batcher_free_space = batcher_size;
			}

			if (remaining_data <= 0)
			{
				break;
			}
			//ERenderBatcher::check_batcher(batcher);
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

	world_position_x = _x + offset_x;
	world_position_y = _y + offset_y;
	world_position_z = _z + offset_z;

	for (ESpriteFrame* frame : sprite_frame_list)
		for (ESprite* spr : frame->sprite_list)
			if (spr != nullptr)
			{
				spr->world_position_x = world_position_x + spr->offset_x;
				spr->world_position_y = world_position_y + spr->offset_y;
				spr->world_position_z = world_position_z + spr->offset_z;
			}
}

void ESpriteLayer::destroy_vertex_buffer()
{
	if ((total_capacity > 0) && (vertex_buffer != nullptr))
	{
		//if (!disable_deleting)
		{ delete[] vertex_buffer; }

		vertex_buffer = nullptr;
		total_capacity	= 0;
		last_buffer_id	= 0;
	}
}

ESpriteLayer* ESpriteLayer::create_default_sprite_layer(ETextureGabarite* _texture)
{
	ESpriteLayer*
	jc_sprite_layer = new ESpriteLayer();

	jc_sprite_layer->batcher = NS_EGraphicCore::default_batcher_for_drawing;


		
		ESpriteFrame*
		jc_sprite_frame = ESpriteFrame::create_default_sprite_frame_with_sprite(_texture, jc_sprite_layer);

		ESprite*
		jc_sprite = jc_sprite_frame->sprite_list[0];

		jc_sprite_layer->sprite_frame_list.push_back(jc_sprite_frame);
		jc_sprite->pointer_to_sprite_render = &NS_ERenderCollection::call_render_textured_sprite;
		jc_sprite->master_sprite_layer = jc_sprite_layer;


	//if (_texture != nullptr) { jc_sprite->set_texture_gabarite(_texture); }

	return jc_sprite_layer;
}

void ESpriteLayer::make_as_PBR()
{

	batcher = NS_EGraphicCore::pbr_batcher;

	for (ESpriteFrame* frame : sprite_frame_list)
		for (ESprite* spr : frame->sprite_list)
		{
			spr->pointer_to_sprite_render = &NS_ERenderCollection::call_render_textured_sprite_PBR;
		}
}

ESpriteLayer* ESpriteLayer::create_default_sprite_layer_with_size_and_offset(ETextureGabarite* _texture, float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y, float _size_z)
{
	ESpriteLayer* jc_sprite_layer = ESpriteLayer::create_default_sprite_layer(_texture);
	ESprite* jc_sprite = ESpriteLayer::get_last_created_sprite(jc_sprite_layer);

	if (jc_sprite != nullptr)
	{
		jc_sprite->offset_x = _offset_x;
		jc_sprite->offset_y = _offset_y;
		jc_sprite->offset_z = _offset_z;

		jc_sprite->size_x = _size_x;
		jc_sprite->size_y = _size_y;
		//*jc_sprite->siz = _offset_z;
	}

	return jc_sprite_layer;
}

ESprite* ESpriteLayer::get_last_created_sprite(ESpriteLayer* _layer)
{
	if
		(
			(!_layer->sprite_frame_list.empty())
			&&
			(!(_layer->sprite_frame_list.back()->sprite_list.empty()))
			)
	{
		return _layer->sprite_frame_list.back()->sprite_list.back();
	}
	else
	{
		return nullptr;
	}


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

	if (last_sprite != nullptr)
	{
		last_sprite->size_x = _size_x;
		last_sprite->size_y = _size_y;

		last_sprite->sprite_calculate_uv();
	}

}

void ESpriteLayer::set_offset_for_last_sprite(ESpriteLayer* _layer, float _offset_x, float _offset_y, float _offset_z)
{
	ESprite* last_sprite = ESpriteLayer::get_last_created_sprite(_layer);

	if (last_sprite != nullptr)
	{
		last_sprite->offset_x = _offset_x;
		last_sprite->offset_y = _offset_y;
		last_sprite->offset_z = _offset_z;

		last_sprite->sprite_calculate_uv();
	}
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
			spr->world_position_x += _x;
			spr->world_position_y += _y;
			spr->world_position_z += _z;

			if (_move_offset)
			{
				spr->offset_x += _x;
				spr->offset_y += _y;
				spr->offset_z += _z;
			}
		}


}

ESprite::ESprite()
{

}

ESprite::~ESprite()
{

	//delete sprite_color;

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
	offset_x += _x;
	offset_y += _y;
	offset_z += _z;
}


void ESprite::generate_vertex_buffer_for_master_sprite_layer()
{
	if ((master_sprite_layer != nullptr) & (main_texture != nullptr))
	{
		//master_sprite_layer->batcher->pointer_to_render()
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_real_size
		(
			master_sprite_layer->vertex_buffer,
			master_sprite_layer->last_buffer_id,
			world_position_x,
			world_position_y + world_position_z,
			main_texture
		);
	}
}


void ESprite::set_texture_gabarite(ETextureGabarite* _gabarite, ETextureGabarite* _normal_map_gabarite, ETextureGabarite* _gloss_map_gabarite)
{
	main_texture = _gabarite;



	if (_gabarite != nullptr)
	{
		fragment_size_x = _gabarite->size_x_in_pixels;
		fragment_size_y = _gabarite->size_y_in_pixels;

		size_x = _gabarite->size_x_in_pixels;
		size_y = _gabarite->size_y_in_pixels;

		//normal_texture	= NS_EGraphicCore::get_gabarite_from_full_path_and_suffix(_gabarite, "[normal_map]");
		//gloss_texture	= NS_EGraphicCore::get_gabarite_from_full_path_and_suffix(_gabarite, "[gloss_map]");

		normal_texture = _normal_map_gabarite;
		gloss_texture = _gloss_map_gabarite;
	}
	else
	{
		EInputCore::logger_simple_error("[set texture gabarite] _gabarite is nullptr!");
	}

	sprite_calculate_uv();
}

void ESprite::set_texture_gabarite_with_size_and_offset(ETextureGabarite* _gabarite, ETextureGabarite* _normal_map_gabarite, ETextureGabarite* _gloss_map_gabarite, float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y, float _size_z)
{
	main_texture = _gabarite;

	offset_x = _offset_x;
	offset_y = _offset_y;
	offset_z = _offset_z;


	if (_gabarite != nullptr)
	{
		fragment_size_x = _size_x;
		fragment_size_y = _size_y;

		size_x = _size_x;
		size_y = _size_y;

		//normal_texture	= NS_EGraphicCore::get_gabarite_from_full_path_and_suffix(_gabarite, "[normal_map]");
		//gloss_texture	= NS_EGraphicCore::get_gabarite_from_full_path_and_suffix(_gabarite, "[gloss_map]");

		normal_texture = _normal_map_gabarite;
		gloss_texture = _gloss_map_gabarite;
	}
	else
	{
		EInputCore::logger_simple_error("[set texture gabarite] _gabarite is nullptr!");
	}

	sprite_calculate_uv();
}

void ESprite::size_texture_gabarite_to_this_size_and_offset(ETextureGabarite* _gabarite, ETextureGabarite* _normal_map_gabarite, ETextureGabarite* _gloss_map_gabarite, float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y, float _size_z)
{
	main_texture = _gabarite;

	offset_x = _offset_x;
	offset_y = _offset_y;
	offset_z = _offset_z;


	if (_gabarite != nullptr)
	{
		fragment_size_x = _gabarite->size_x_in_pixels;
		fragment_size_y = _gabarite->size_y_in_pixels;

		size_x = _size_x;
		size_y = _size_y;

		//normal_texture	= NS_EGraphicCore::get_gabarite_from_full_path_and_suffix(_gabarite, "[normal_map]");
		//gloss_texture	= NS_EGraphicCore::get_gabarite_from_full_path_and_suffix(_gabarite, "[gloss_map]");

		normal_texture = _normal_map_gabarite;
		gloss_texture = _gloss_map_gabarite;
	}
	else
	{
		EInputCore::logger_simple_error("[set texture gabarite] _gabarite is nullptr!");
	}

	sprite_calculate_uv();
}

void ESprite::sprite_calculate_uv()
{
	if (main_texture != nullptr)
	{
		uv_start_x = main_texture->uv_start_x + (fragment_offset_x + 0.0f) / main_texture->target_atlas->get_atlas_size_x();
		uv_start_y = main_texture->uv_start_y + (fragment_offset_y + 0.0f) / main_texture->target_atlas->get_atlas_size_y();

		uv_end_x = uv_start_x + (fragment_size_x - 1.0f) / main_texture->target_atlas->get_atlas_size_x();
		uv_end_y = uv_start_y + (fragment_size_y - 1.0f) / main_texture->target_atlas->get_atlas_size_y();
	}

	if ((normal_texture != nullptr) && (normal_texture != NS_DefaultGabarites::texture_gabarite_normal_map_placeholder))
	{
		normal_uv_start_x = normal_texture->uv_start_x + (fragment_offset_x + 0.0f) / normal_texture->target_atlas->get_atlas_size_x();
		normal_uv_start_y = normal_texture->uv_start_y + (fragment_offset_y + 0.0f) / normal_texture->target_atlas->get_atlas_size_y();

		normal_uv_end_x = normal_uv_start_x + (fragment_size_x - 1.0f) / normal_texture->target_atlas->get_atlas_size_x();
		normal_uv_end_y = normal_uv_start_y + (fragment_size_y - 1.0f) / normal_texture->target_atlas->get_atlas_size_y();
	}
	else
	{
		normal_uv_start_x = NS_DefaultGabarites::texture_gabarite_normal_map_placeholder->uv_start_x;
		normal_uv_start_y = NS_DefaultGabarites::texture_gabarite_normal_map_placeholder->uv_start_y;

		normal_uv_end_x = NS_DefaultGabarites::texture_gabarite_normal_map_placeholder->uv_start_x;
		normal_uv_end_y = NS_DefaultGabarites::texture_gabarite_normal_map_placeholder->uv_start_y;
	}

	if ((gloss_texture != nullptr) && (gloss_texture != NS_DefaultGabarites::texture_gabarite_gloss_map_placeholder))
	{
		gloss_uv_start_x = gloss_texture->uv_start_x + (fragment_offset_x + 0.0f) / gloss_texture->target_atlas->get_atlas_size_x();
		gloss_uv_start_y = gloss_texture->uv_start_y + (fragment_offset_y + 0.0f) / gloss_texture->target_atlas->get_atlas_size_y();

		gloss_uv_end_x = gloss_uv_start_x + (fragment_size_x - 1.0f) / gloss_texture->target_atlas->get_atlas_size_x();
		gloss_uv_end_y = gloss_uv_start_y + (fragment_size_y - 1.0f) / gloss_texture->target_atlas->get_atlas_size_y();
	}
	else
	{
		gloss_uv_start_x = NS_DefaultGabarites::texture_gabarite_gloss_map_placeholder->uv_start_x;
		gloss_uv_start_y = NS_DefaultGabarites::texture_gabarite_gloss_map_placeholder->uv_start_y;

		gloss_uv_end_x = NS_DefaultGabarites::texture_gabarite_gloss_map_placeholder->uv_start_x;
		gloss_uv_end_y = NS_DefaultGabarites::texture_gabarite_gloss_map_placeholder->uv_start_y;
	}

}

void ESprite::reset_sprite()
{
	main_texture = nullptr;

	fragment_offset_x = 0.0f;
	fragment_offset_y = 0.0f;

	fragment_size_x = 0.0f;
	fragment_size_y = 0.0f;

	uv_start_x = 0.0f;
	uv_start_y = 0.0f;

	uv_end_x = 0.0f;
	uv_end_y = 0.0f;

	gloss_uv_start_x = 0.0f;
	gloss_uv_start_y = 0.0f;

	gloss_uv_end_x = 0.0f;
	gloss_uv_end_y = 0.0f;

	normal_uv_start_x = 0.0f;
	normal_uv_start_y = 0.0f;

	normal_uv_end_x = 0.0f;
	normal_uv_end_y = 0.0f;

	offset_x = 0.0f;
	offset_y = 0.0f;
	offset_z = 0.0f;

	world_position_x = 0.0f;
	world_position_y = 0.0f;
	world_position_z = 0.0f;

	size_x = (0.0f);
	size_y = (0.0f);
}

void ESprite::sprite_set_world_positions(float _x, float _y, float _z)
{
	world_position_x = _x + offset_x;
	world_position_y = _y + offset_y;
	world_position_z = _z + offset_z;
}

ESprite* ESprite::create_default_sprite(ETextureGabarite* _gabarite, ESpriteLayer* _sprite_layer)
{
	ESprite* jc_sprite = new ESprite();

	if (_gabarite != nullptr)
	{
		jc_sprite->set_texture_gabarite(_gabarite, nullptr, nullptr);
	}

	jc_sprite->pointer_to_sprite_render = &NS_ERenderCollection::call_render_textured_sprite;
	jc_sprite->master_sprite_layer = _sprite_layer;

	return jc_sprite;
}

void ESprite::set_size(ESprite* _sprite, float _size_x, float _size_y, float _size_z)
{
	_sprite->size_x = _size_x;
	_sprite->size_y = _size_y;

	_sprite->sprite_calculate_uv();
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

ESpriteFrame::~ESpriteFrame()
{
	if (!disable_deleting)
	{
		for (int i = 0; i < sprite_list.size() /* * 0*/; i++)
		{
			delete sprite_list.at(i);
		}
	}
	//for (ESprite* sl:sprite_list) { delete sl; }
	sprite_list.clear();
	sprite_list.shrink_to_fit();
}

ESpriteFrame* ESpriteFrame::create_default_sprite_frame()
{
	//ESprite*		jc_sprite			= new ESprite();
	ESpriteFrame* jc_sprite_frame = new ESpriteFrame();

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
