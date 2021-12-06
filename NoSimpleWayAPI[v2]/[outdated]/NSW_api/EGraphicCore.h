#pragma once

#include "../../../ExternalEnums.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EGabarite.h"

#include <stb_image.h>
#include <learnopengl/shader_s.h>

#include "NSW_api/Batcher.h"
#include "EGabarite.h"
#include <vector>

constexpr int skydome_texture_levels = 5;
class EGraphicCore {
public:
	static unsigned char* data1;
	static unsigned int texture[32];
	static int width, height, nrChannels;

	static int last_texture_w;
	static int last_texture_h;

	static Shader* ourShader;
	static Shader* shadowmap;
	static Shader* shader_terrain;
	static Shader* lightmap_blur;
	static Shader* lightmap_spread;

	static Shader* AO_shader;
	static Shader* PBR_shader;
	static Shader* simple_blur;

	static Batcher* batch;
	static Batcher* batch_shadowmap;
	static Batcher* batch_terrain;

	static Batcher* batch_PBR;

	static glm::mat4 matrix_transform;

	static int SCR_WIDTH;
	static int SCR_HEIGHT;

	static float correction_x;
	static float correction_y;

	static void load_texture(char const* _path, int _id);

	static std::vector<EGabarite*> gabarite_list;
	//static std::vector<EGabarite*> gabarite_collection;

	static EGabarite* gabarite_white_pixel;
	static EGabarite* gabarite_tileset;
	static EGabarite* gabarite_small_wood_button_bg;
	static EGabarite* gabarite_wood_button_bg;
	static EGabarite* gabarite_ERROR;
	static EGabarite* gabarite_radial_button;
	static EGabarite* gabarite_radial_button_dot;
	static EGabarite* gabarite_supermap_placeholder;
	static EGabarite* gabarite_full_atlas;

	static EGabarite* gabarite_sun;
	static EGabarite* gabarite_sky;
	static EGabarite* gabarite_panorama;
	static EGabarite* gabarite_button_texture_AO_shadow;

	static float sun_zenith_factor;

	static float sun_position_x;
	static float sun_position_y;

	static float sun_size;

	static float sun_matte_power;
	static float sky_lum;
	static float ground_lum;

	static float blur_size;
	static float blur_size_buffer;
	static float brightness_multiplier;

	static float gloss_input;
	static float sky_ambient_light_power;
	static float sky_free_top_light;



	static int selected_blur_level;

	EGraphicCore();
	~EGraphicCore();

	struct ESprite
	{
		EGabarite* texture_gabarite				= NULL;
		EGabarite* normal_gloss_map_gabarite	= NULL;

		float* offset_x							= new float(0.0f);
		float* offset_y							= new float(0.0f);
		float* offset_z							= new float(0.0f);

		float* fragment_x						= new float(0.0f);
		float* fragment_y						= new float(0.0f);

		float* fragment_left					= new float(0.0f);
		float* fragment_right					= new float(0.0f);
		float* fragment_down					= new float(0.0f);
		float* fragment_up						= new float(0.0f);

		float* size_x							= new float(0.0f);
		float* size_y							= new float(0.0f);
		float* size_z							= new float(0.0f);

		int* selected_draw_mode = new int(SpriteDrawMode::SPRITE_DRAW_MODE_NORMAL);

		~ESprite();
	};

	struct sprite_array
	{
		std::vector <ESprite*> sprite_list;

		//Entity* master_entity;
		//EButton* master_button;
	};

	static void draw_sprite_regular(sprite_array* _sprite_array, Batcher* _batch, float _offset_x, float _offset_y, float _offset_z);

	__inline static void draw_sprite_PBR(EGraphicCore::ESprite* _sprite, Batcher* _batch, float _offset_x, float _offset_y, float _offset_z, float _true_height)
	{
		if ((_sprite != NULL) && (_sprite->texture_gabarite != NULL) && (_sprite->normal_gloss_map_gabarite != NULL))
		{

			//std::cout << "zalupa: " << _sprite->normal_gloss_map_gabarite->name << std::endl;
			/*if (_sprite->normal_gloss_map_gabarite == NULL)
			{
				_sprite->normal_gloss_map_gabarite = _sprite->texture_gabarite;
			}*/

			_batch->setcolor(EColor::COLOR_WHITE);
			_batch->draw_sprite_PBR
			(
				_offset_x + *_sprite->offset_x,
				_offset_y + *_sprite->offset_y,
				_offset_z + *_sprite->offset_z,

				*_sprite->size_x,
				*_sprite->size_y,
				*_sprite->size_z,

				*_sprite->fragment_left,
				*_sprite->fragment_right,
				*_sprite->fragment_down,
				*_sprite->fragment_up,

				_sprite->texture_gabarite,
				_sprite->normal_gloss_map_gabarite,
				_true_height
			);
			//_batch->draw_gabarite(_offset_x + *spr->offset_x, _offset_y + *spr->offset_y + _offset_z + *spr->offset_z, spr->texture_gabarite);
		}
	}

	//static void draw_sprite_PBR(EGraphicCore::ESprite* _sprite, Batcher* _batch, float _offset_x, float _offset_y, float _offset_z);
	static void reset_sprite_data(EGraphicCore::ESprite* _sprite);
};