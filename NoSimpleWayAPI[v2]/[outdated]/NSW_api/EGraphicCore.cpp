#include "EGraphicCore.h"

unsigned int EGraphicCore::texture[32];
unsigned char* EGraphicCore::data1;

int EGraphicCore::width;
int EGraphicCore::height;
int EGraphicCore::nrChannels;

int EGraphicCore::last_texture_w;
int EGraphicCore::last_texture_h;

Shader* EGraphicCore::ourShader;
Shader* EGraphicCore::shadowmap;
Shader* EGraphicCore::shader_terrain;
Shader* EGraphicCore::lightmap_blur;
Shader* EGraphicCore::lightmap_spread;

Shader* EGraphicCore::AO_shader;
Shader* EGraphicCore::PBR_shader;
Shader* EGraphicCore::simple_blur;

Batcher* EGraphicCore::batch;
Batcher* EGraphicCore::batch_shadowmap;
Batcher* EGraphicCore::batch_terrain;

Batcher* EGraphicCore::batch_PBR;


glm::mat4 EGraphicCore::matrix_transform;

int EGraphicCore::SCR_WIDTH = 1920;
int EGraphicCore::SCR_HEIGHT = 1080;

float EGraphicCore::correction_x = 0.1f;
float EGraphicCore::correction_y = 0.1f;

float EGraphicCore::sun_position_x = 0.5f;
float EGraphicCore::sun_position_y = 0.6f;

float EGraphicCore::sun_size = 0.02f;

float EGraphicCore::sun_matte_power = 1.00f;
float EGraphicCore::sky_lum = 0.06f;
float EGraphicCore::ground_lum = 0.05f;

float EGraphicCore::blur_size = 5.50f;
float EGraphicCore::blur_size_buffer = 2.50f;
float EGraphicCore::brightness_multiplier = 20.00f;

float EGraphicCore::gloss_input = 1.00f;
float EGraphicCore::sky_ambient_light_power = 0.75f;
float EGraphicCore::sky_free_top_light = 0.35f;

int EGraphicCore::selected_blur_level = 0;

std::vector<EGabarite*> EGraphicCore::gabarite_list;

//std::vector<EGabarite*> EGraphicCore::gabarite_collection;

EGabarite* EGraphicCore::gabarite_white_pixel;
EGabarite* EGraphicCore::gabarite_tileset;
EGabarite* EGraphicCore::gabarite_small_wood_button_bg;
EGabarite* EGraphicCore::gabarite_wood_button_bg;
EGabarite* EGraphicCore::gabarite_ERROR;
EGabarite* EGraphicCore::gabarite_radial_button;
EGabarite* EGraphicCore::gabarite_radial_button_dot;
EGabarite* EGraphicCore::gabarite_supermap_placeholder;
EGabarite* EGraphicCore::gabarite_full_atlas;

EGabarite* EGraphicCore::gabarite_sun;
EGabarite* EGraphicCore::gabarite_sky;
EGabarite* EGraphicCore::gabarite_panorama;
EGabarite* EGraphicCore::gabarite_button_texture_AO_shadow;

float EGraphicCore::sun_zenith_factor;

void EGraphicCore::reset_sprite_data(EGraphicCore::ESprite* _sprite)
{
	*_sprite->fragment_x = 1.0f;
	*_sprite->fragment_y = 1.0f;

	*_sprite->offset_x = 0.0f;
	*_sprite->offset_y = 0.0f;
	*_sprite->offset_z = 0.0f;

	*_sprite->fragment_down = 0.0f;
	*_sprite->fragment_up = 0.0f;
	*_sprite->fragment_left = 0.0f;
	*_sprite->fragment_right = 0.0f;

	_sprite->texture_gabarite = NULL;
	_sprite->normal_gloss_map_gabarite = NULL;

	*_sprite->size_x = 0.0f;
	*_sprite->size_y = 0.0f;
	*_sprite->size_z = 0.0f;

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

	data1 = stbi_load(_path, &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
		//glGenerateMipmap(GL_TEXTURE_2D);

		//cout << "loaded texture W:" << width << " H:" << height << endl;

		last_texture_h = height;
		last_texture_w = width;

		//texture_error = false;
		/*texture_w[_id] = width;
		texture_h[_id] = height;*/
	}
	else
	{
		data1 = stbi_load("data/textures/ERROR.png", &width, &height, &nrChannels, STBI_rgb_alpha);
		if (data1)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
			last_texture_h = height;
			last_texture_w = width;
		}
		//cout << red << "Failed to load texture " << yellow << "(" << _path << ")" << green << endl;
		std::cout << "Failed to load texture " << "(" << _path << ")" << std::endl;
		//last_texture_h = 21;
		//last_texture_w = 21;

		//texture_error = true;

		//just_created_gabarite = DefaultGabarite::gabarite_error;
	}

	stbi_image_free(data1);
}

EGraphicCore::EGraphicCore()
{
}

EGraphicCore::~EGraphicCore()
{
}

void EGraphicCore::draw_sprite_regular(sprite_array* _sprite_array, Batcher* _batch, float _offset_x, float _offset_y, float _offset_z)
{
	if (_sprite_array != NULL)
	{
		for (ESprite* spr : _sprite_array->sprite_list)
			if ((spr != NULL) && (spr->texture_gabarite != NULL))
			{
				_batch->setcolor(EColor::COLOR_WHITE);
				_batch->draw_sprite
				(
					_offset_x + *spr->offset_x,
					_offset_y + *spr->offset_y + _offset_z + *spr->offset_z,

					*spr->size_x,
					*spr->size_y,

					*spr->fragment_left,
					*spr->fragment_right,
					*spr->fragment_down,
					*spr->fragment_up,

					spr->texture_gabarite
				);
				//_batch->draw_gabarite(_offset_x + *spr->offset_x, _offset_y + *spr->offset_y + _offset_z + *spr->offset_z, spr->texture_gabarite);
			}
	}
}

/*
void EGraphicCore::draw_sprite_regular(EGraphicCore::ESprite* _sprite, Batcher* _batch, float _offset_x, float _offset_y, float _offset_z)
{
	
}*/

/*void EGraphicCore::draw_sprite_PBR(EGraphicCore::ESprite* _sprite, Batcher* _batch, float _offset_x, float _offset_y, float _offset_z, float _true_height)
{
	if ((_sprite != NULL) && (_sprite->texture_gabarite != NULL))
	{
		_batch->setcolor(EColor::COLOR_WHITE);
		_batch->draw_sprite
		(
			_offset_x + *_sprite->offset_x,
			_offset_y + *_sprite->offset_y + _offset_z + *_sprite->offset_z,

			*_sprite->size_x,
			*_sprite->size_y,

			*_sprite->fragment_left,
			*_sprite->fragment_right,
			*_sprite->fragment_down,
			*_sprite->fragment_up,

			_sprite->texture_gabarite
		);
		//_batch->draw_gabarite(_offset_x + *spr->offset_x, _offset_y + *spr->offset_y + _offset_z + *spr->offset_z, spr->texture_gabarite);
	}
}*/

EGraphicCore::ESprite::~ESprite()
{
	delete offset_x;
	delete offset_y;
	delete offset_z;

	delete fragment_x;
	delete fragment_y;

	delete fragment_left;
	delete fragment_up;
	delete fragment_right;
	delete fragment_down;

	delete size_x;
	delete size_y;
	delete size_z;

	delete normal_gloss_map_gabarite;
	delete texture_gabarite;
	
	/*if (normal_gloss_map_gabarite != NULL)
	{
		
	}*/

	delete selected_draw_mode;
}