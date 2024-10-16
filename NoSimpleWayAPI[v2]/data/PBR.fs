
#version 330 core



out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;
//in vec2 ReflectionTexCoord;
in vec2 NormalMapTexCoord;
in vec2 GlossMapTexCoord;
in vec3 WorldPosition;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D normal_map_texture;
uniform sampler2D gloss_map_texture;

uniform sampler2D SD_array[7];




uniform float brightness_multiplier		= 1.5f;
uniform float reflection_multiplier		= 1.0f;


uniform float skydome_light_power = 1.0f;
uniform float free_sky_light = 0.35f;
uniform float free_sun_light = 0.45f;
uniform float direct_sun_matte_multiplier = 1.0f;

uniform float sun_position_x = 0.5f;
uniform float sun_position_y = 0.55f;

uniform float ground_level = 0.333f;
uniform float sun_size = 0.075f;
uniform float sun_blur = 0.075f;
uniform float sun_bright = 0.075f;
uniform float sun_exp = 2.0f;
uniform float time = 0.0f;
uniform float move_multiplier = 1.0f;

uniform float normal_map_multiplier = 1.0f;
uniform float gloss_map_multiplier = 1.0f;
uniform float plastic_or_metal_multiplier = 1.0f;

uniform float screen_offset_x;
uniform float screen_offset_y;
uniform float screen_offset_z;

uniform float scr_x;
uniform float scr_y;

uniform float sun_flat_decay = 0.05f;

float c_r;
float c_g;
float c_b;
float c_a;

vec4 skydome_pixel;
vec4 skydome_pixel_A;
vec4 skydome_pixel_B;


float tile_offset_x	[11] = {0.0f, 0.5f, 0.75f,	0.5f,	0.625f, 0.750f,	0.875f,	0.5f,	0.625f,	0.750f, 0.875f};
float tile_offset_y	[11] = {0.0f, 0.5f, 0.5f,	0.25f,	0.25f,	0.25f, 	0.25f,	0.0f, 	0.000f,	0.000f,	0.000f};
float tile_scale	[11] = {1.0f, 0.5f, 0.5f,	0.25f,	0.25f,	0.25f, 	0.25f,	0.25f, 	0.25f,	0.25f,	0.25f};


float level = 0.0f;
int glossy_flat = 0;
float ipr = 0.5f;
//float interpolation_A = 1.0f;
float skydome_mix_factor = 0.0f;

float plastic_or_metal = 0.0f;
float reflection_blur_area = 0.0f;

vec2 reflect_coord;

float gloss_result = 1.0f;
float matte_result_sun = 0.0f;
float matte_result_sky = 0.0f;

//float normal_x;
//float normal_y;

vec2 nrm;

//precision lowp float;
float reflect_pos_x;
float reflect_pos_y;

float dist_x;
float dist_y;
float dist_total;

uniform vec3 sun_light_gloss_color = vec3(1.8f, 1.1f, 0.5f);
vec3 sun_light_matte = vec3(1.7f, 1.1f, 0.8f);

vec3 gloss_sun_light;
vec3 matte_sun_light;

vec3 sky_light_gloss = vec3(0.9f, 1.0f, 1.1f);
vec3 sky_light_matte = vec3(0.85f, 0.875f, 0.9f);
vec3 sky_light;


float AO_bottom_shade_factor;

int steps = 10;

float fast_gloss;

float sun_angle = 0.0f;

void main()
{
	
	plastic_or_metal			= clamp(texture(texture1, GlossMapTexCoord).g, 0.0f, 1.0f);
	plastic_or_metal			*= plastic_or_metal_multiplier;
	
	reflection_blur_area		= clamp(texture(texture1, GlossMapTexCoord).b, 0.0f, 1.0f);
	
	
	reflection_blur_area		*= gloss_map_multiplier;
	//reflection_blur_area		= pow (reflection_blur_area, move_multiplier);
	reflection_blur_area		= min(reflection_blur_area, 1.0f);
	
	//reflection_blur_area = sun_flat_decay;
	//gloss_power = 0.2f;
	
	fast_gloss = clamp(reflection_blur_area, 0.01f, 1.0f);
	
	level = (1.0f - fast_gloss) * steps;
	//level = (level - 0.5) * 2.000f;
	//level = 0.0f;
	
	glossy_flat = clamp(int(floor(level)), 0, steps);
	//glossy_flat = 4 - glossy_flat;
	
	skydome_mix_factor = level - glossy_flat;
	
	//glossy_flat = 0;
	//glossy_flat = int(round(move_multiplier));
	nrm = (texture(texture1, NormalMapTexCoord).rg - vec2(0.5f)) * 2.0f;
	//nrm = pow(nrm, vec2(2.0f)) * vec2((nrm[0] < 0) ? (-1.0f) : (1.0f),(nrm[1] < 0) ? (-1.0f) : (1.0f));
	
	nrm *= vec2(normal_map_multiplier);
	//normal_x = ((texture(texture1, NormalMapTexCoord).r));
	//normal_y = ((texture(texture1, NormalMapTexCoord).g));

	
	//normal_x += -0.5f;
	//normal_y += -0.5f;
	
	
	if (glossy_flat <= 10)
	{
		reflect_pos_x = (gl_FragCoord.x / scr_x);
		reflect_pos_x += nrm[0] * 0.333f;
		reflect_pos_x += time / 50.0f;
		reflect_pos_x = ((reflect_pos_x * 2.0f) - floor(reflect_pos_x * 2.0f));
		
		reflect_pos_x *= 0.5f;
		reflect_pos_x *= tile_scale		[glossy_flat];
		reflect_pos_x += tile_offset_x	[glossy_flat];
		reflect_pos_x = clamp(reflect_pos_x, tile_offset_x[glossy_flat] + 0.5f / 1024.0f, tile_offset_x[glossy_flat] + tile_scale[glossy_flat] * 0.5f - 0.5f / 1024.0f);
		
		
		
		reflect_pos_y = (WorldPosition.y / scr_y);
		reflect_pos_y += nrm[1] * 0.333f;
		reflect_pos_y *= tile_scale[glossy_flat];
		reflect_pos_y += tile_offset_y[glossy_flat];

		reflect_coord = vec2 (reflect_pos_x, reflect_pos_y);
		skydome_pixel_A = texture(SD_array[1], reflect_coord);	
	}
	else
	{
		skydome_pixel_A = vec4(1.0f, 0.75f, 0.5f, 1.0f);
	}
	
	glossy_flat = min(glossy_flat + 1, 11);
	if (glossy_flat <= 10)
	{
		
		
		reflect_pos_x = (gl_FragCoord.x / scr_x);
		reflect_pos_x += nrm[0] * 0.333f;
		reflect_pos_x += time / 50.0f;
		reflect_pos_x = ((reflect_pos_x * 2.0f) - floor(reflect_pos_x * 2.0f));
		
		reflect_pos_x *= 0.5f;
		reflect_pos_x *= tile_scale		[glossy_flat];
		reflect_pos_x += tile_offset_x	[glossy_flat];
		reflect_pos_x = clamp(reflect_pos_x, tile_offset_x[glossy_flat] + 0.5f / 1024.0f, tile_offset_x[glossy_flat] + tile_scale[glossy_flat] * 0.5f - 0.5f / 1024.0f);
		
		
		
		reflect_pos_y = (WorldPosition.y / scr_y);
		reflect_pos_y += nrm[1] * 0.333f;
		reflect_pos_y *= tile_scale[glossy_flat];
		reflect_pos_y += tile_offset_y[glossy_flat];

		reflect_coord = vec2 (reflect_pos_x, reflect_pos_y);
		
		skydome_pixel_B = texture(SD_array[1], reflect_coord);	
	}
	else
	{
		skydome_pixel_B = vec4(0.9f, 0.95f, 1.00f, 1.0f);
	}
	
	skydome_pixel = mix(skydome_pixel_A, skydome_pixel_B, skydome_mix_factor);
	
	//else
	//{
	//	skydome_pixel = vec4(0.5f, 0.75f, 1.0, 1.0f);
	//}
	reflect_pos_x = (gl_FragCoord.x / scr_x);
	reflect_pos_x += nrm[0] * 0.333f;
	
	reflect_pos_y = (WorldPosition.y / scr_y);
	reflect_pos_y += nrm[1] * 0.333f;
	
	dist_x = reflect_pos_x - (sun_position_x);
	dist_y = reflect_pos_y - (sun_position_y);
	dist_x /= (scr_y / scr_x);
	
	dist_total = length(vec2(dist_x, dist_y)) - sun_size / 10.0f;
	//dist_total = pow(dist_total, 2.0);
	dist_total /= 1.0f + (skydome_pixel.a) * 5.000f;
	//dist_total = 1.0f - dist_total;
																
	dist_total = clamp(1.0f  - ((dist_total * sun_blur * sun_blur * 100.0f) * (sun_flat_decay + reflection_blur_area)), 0.0f, 1.0f);
	//dist_total*=dist_total;
	dist_total = pow (dist_total, sun_exp);
	
	//gloss_result = plastic_or_metal;
	

		//gloss_sun_light = mix(sun_light_gloss_color, sun_light_gloss_color / 2.0f, plastic_or_metal) * dist_total * (1.0f - skydome_pixel.a);
		gloss_sun_light = sun_light_gloss_color * dist_total * (1.0f - skydome_pixel.a * skydome_pixel.a);
		
		
		gloss_sun_light *= sun_bright * (plastic_or_metal) * (reflection_blur_area * 0.9f + 0.1f);
		
		float indirect_sun_dist = length(vec2(nrm[0]  - (sun_position_x - 0.5f) * 4.0f, nrm[1] - (sun_position_y - 0.5f) * 4.0f));

		
		indirect_sun_dist -= sun_size / 10.0f;
		
		
		
			//indirect_sun_dist /= sun_size;
		
			//indirect_sun_dist = clamp(sun_angle, 0.0f, 1.0f);
		
			//sun_angle = clamp(1.0f - indirect_sun_dist * sun_blur * sun_blur * (5.0f), 0.0f, 1.0f);
			//sun_angle *= 0.1f;
			sun_angle = (1.0f - indirect_sun_dist);
			sun_angle = max(sun_angle, 0.0f);
			//sun_angle = pow(sun_angle, sun_exp);
		if (indirect_sun_dist >= 3.333f)
		{	
			float sun_see_factor = max(1.0f - (indirect_sun_dist - 0.333f) / sun_size, 0.0f);
			
			sun_angle = sun_angle * sun_see_factor;
			//sun_angle = 1.0f;
		}
		
		sun_angle = clamp(sun_angle, 0.0f, 1.0f);
		
		float ground_light = (nrm[1] + 1.0f) / 2.0f;
		ground_light = clamp(ground_light, 0.0f, 1.0f);
		
		float sun_light_multiplier = (nrm[1] + 1.5f) / 2.0f;
		sun_light_multiplier = clamp(sun_light_multiplier, 0.0f, 1.0f);
		//						lighted										unlighted									mix
		
		//always lighted by sky
		matte_sun_light	=	vec3(0.90f, 0.95f, 1.0f)	* free_sky_light * ground_light;
		matte_sun_light	+=	vec3(1.00f, 0.95f, 0.9f)	* free_sun_light * sun_angle * sun_light_multiplier;
		
		//matte_sun_light = vec3(1.0f);
	
	//sky_light = mix(sky_light_matte, sky_light_gloss, plastic_or_metal);
	//sky_light += texture(SD_array[4], reflect_coord + vec2(0.0f, ground_level * 2.0f - 1.0f)).a;
	
	

	//sun_light *= 1.0f - skydome_pixel.a;
	
	
	
	
	FragColor.rgb
	=
	clamp
	(
		//SKYDOME TOTAL LIGHT
		(
			//REFLECTION (black for plastic, pixel for matte)
			mix(vec3(0.0f), skydome_pixel.rgb * reflection_multiplier, min(plastic_or_metal * 1.0f, 1.0f))
			+
			//SUN
			mix(matte_sun_light, gloss_sun_light, min(plastic_or_metal , 1.0f))
			//vec3(skydome_pixel) * 2.0f
		)
		*
		//MATTE
		texture(texture1, TexCoord).rgb
		*
		ourColor.rgb,
		vec3(0.0f),
		vec3(1.0f)
	);
	
	//if (sky_reflect_x > 1.0f) {FragColor.r = 1.0f;}
	//if (sky_reflect_y > 1.0f) {FragColor.g = 1.0f;}
	
	//FragColor.r = (reflect_pos_x);
	//FragColor.g = (reflect_pos_y);
	//FragColor.b = 0.5f;
	
	//FragColor.rgb = skydome_pixel.rgb;
	FragColor.a = texture(texture1, TexCoord).a * ourColor.a;
	//FragColor.rgb = vec3(dist_total);
	//FragColor.rgb = (matte_sun_light);
	//FragColor.rgb = vec3(sun_angle);
	//FragColor.rgb = vec3(1.0f - indirect_sun_dist);
	//FragColor.rgb = vec3(reflect_coord.x, reflect_coord.y, 1.0f);
	//FragColor.rgb = texture(texture1, TexCoord).rgb * ourColor.rgb;
	//FragColor.rgb =  (sky_light) * (1.0f - gloss_result) + (sun_light);
	//FragColor.rgb =  vec3(sun_light);
	//FragColor.rgb =  vec3(texture(texture1, NormalMapTexCoord));	FragColor.a = 1.0;
	//FragColor.rgb =  vec3(texture(texture1, GlossMapTexCoord));	FragColor.a = 1.0;
	
	//FragColor.rgb =  vec3(c_r, c_g, c_b);	FragColor.a = 1.0;

}

