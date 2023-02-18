

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



uniform float brightness_multiplier = 1.5f;
uniform float reflection_multiplier = 1.0f;
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

vec4 c_rgba;



float level = 0.0f;
int glossy_flat = 0;
float ipr = 0.5f;
float interpolation_A = 1.0f;
float interpolation_B = 0.0f;

float gloss_power = 0.0f;

vec2 reflect_coord;

float gloss_result = 1.0f;
float matte_result_sun = 0.0f;
float matte_result_sky = 0.0f;

float normal_x;
float normal_y;


float reflect_pos_x;
float reflect_pos_y;

float dist_x;
float dist_y;
float dist_total;

uniform vec3 sun_light_gloss = vec3(1.8f, 1.1f, 0.5f);
vec3 sun_light_matte = vec3(1.7f, 1.1f, 0.8f);

vec3 direct_sun_light;
vec3 indirect_sun_light;

vec3 sky_light_gloss = vec3(0.9f, 1.0f, 1.1f);
vec3 sky_light_matte = vec3(0.85f, 0.875f, 0.9f);
vec3 sky_light;


float AO_bottom_shade_factor;

int steps = 5;

float fast_gloss;

float indirect_sun_angle = 0.0f;

void main()
{
	
	gloss_power = clamp(texture(texture1, GlossMapTexCoord).b * gloss_map_multiplier, 0.0f, 1.0f);
	//gloss_power = 0.2f;
	
	fast_gloss = max(gloss_power - 0.5f, 0.0f) * 2.000f;
	
	level = (1.0f - fast_gloss) * steps;
	//level = (level - 0.5) * 2.000f;
	//level = 0.0f;
	
	glossy_flat = clamp(int(floor(level)), 0, steps);
	//glossy_flat = 4 - glossy_flat;
	
	interpolation_B = level - glossy_flat;
	interpolation_A = 1.0f - interpolation_B;
	
	
	normal_x = (texture(texture1, NormalMapTexCoord).r - 0.5f) * 2.000f * normal_map_multiplier;
	normal_y = (texture(texture1, NormalMapTexCoord).g - 0.5f) * 2.000f * normal_map_multiplier;
	
	//normal_x = clamp(normal_x, -1.0f, 1.0f);
	//normal_y = clamp(normal_y, -1.0f, 1.0f);

	reflect_pos_x =  0.333f + (gl_FragCoord.x	/ scr_x	* (1.0f - abs(clamp(normal_x, -1.0f, 1.0f) * 0.0f))) * 0.333f + clamp(normal_x, -1.0f, 1.0f) * 0.1666f;
	//reflect_pos_x = clamp(reflect_pos_x, 0.0f, 1.0f);
	//reflect_pos_x *= scr_x / scr_y;
	
	reflect_pos_y =  0.333f + (WorldPosition.y	/ scr_y	* (1.0f - abs(clamp(normal_y, -1.0f, 1.0f) * 0.0f))) * 0.333f + clamp(normal_y, -1.0f, 1.0f)	 * 0.1666f;
	//reflect_pos_y = clamp(reflect_pos_y, 0.0f, 1.0f);
	//reflect_pos_x = gl_FragCoord.x / 2880.0f;
	//reflect_pos_y = WorldPosition.y / 1800.0f;
	//((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 1.0f;
	
	//reflect_pos_y += (ground_level * 2.0f - 1.0f);
	reflect_coord =
	vec2
	(
		//base offset		screen position offset					//normal offset
		clamp(reflect_pos_x, 0.0f, 1.0f) * 2.0f * scr_x / scr_y + time / 50.0f * move_multiplier,
		
		
		clamp(reflect_pos_y, 0.0f, 1.0f) * 2.0f - ground_level - 0.0f
	);
	
	
	//interpolation_A = 1.0f;
	//interpolation_B = 0.0f;
	
	if (glossy_flat == 0)
	{
		c_rgba
		=
		(
			texture(SD_array[0], reflect_coord) * interpolation_A
			+
			texture(SD_array[1], reflect_coord) * interpolation_B
		);
		
		//c_rgba = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	if (glossy_flat == 1)
	{
		c_rgba
		=
		(
			texture(SD_array[1], reflect_coord) * interpolation_A
			+
			texture(SD_array[2], reflect_coord) * interpolation_B
		);
		
		//c_rgba = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	}
	else
	if (glossy_flat == 2)
	{
		c_rgba
		=
		(
			texture(SD_array[2], reflect_coord) * interpolation_A
			+
			texture(SD_array[3], reflect_coord) * interpolation_B
		);
		
		//c_rgba = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	else
	if (glossy_flat == 3)
	{
		c_rgba
		=
		(
			texture(SD_array[3], reflect_coord) * interpolation_A
			+
			texture(SD_array[4], reflect_coord) * interpolation_B
		);
		
		//c_rgba = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	if (glossy_flat == 4)
	{
		c_rgba
		=
		(
			texture(SD_array[4], reflect_coord) * interpolation_A
			+
			texture(SD_array[5], reflect_coord) * interpolation_B
		);
		
		//c_rgba = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		c_rgba
		=
		clamp
		(
			texture(SD_array[5], reflect_coord),
			vec4(0.0f),
			vec4(2.0f, 1.9f, 1.8f, 1.0f)
		);
		//c_rgba = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	
	dist_x = reflect_pos_x - (sun_position_x);
	dist_y = reflect_pos_y - (sun_position_y);
	dist_x /= (scr_y / scr_x);
	
	dist_total = length(vec2(dist_x, dist_y)) - sun_size / 10.0f;
	//dist_total = pow(dist_total, 2.0);
	dist_total /= 1.0f + (c_rgba.a) * 2.000f;
	//dist_total = 1.0f - dist_total;
	dist_total = clamp(1.0f  - (dist_total * sun_blur * sun_blur * 100.0f) * (sun_flat_decay + gloss_power), 0.0f, 1.0f);
	//dist_total*=dist_total;
	dist_total = pow (dist_total, sun_exp);
	
	gloss_result = gloss_power;
	

		direct_sun_light = mix(sun_light_gloss, sun_light_gloss / 2.0f, gloss_power) * dist_total * (1.0f - c_rgba.a);
		direct_sun_light *= sun_bright * (gloss_result);
		
		indirect_sun_angle
		= 
		1.0f
		-
		max
		(
			length
			(
				vec2
				(
					0.0f + normal_x * 1.0f - (sun_position_x - 0.5f) * 6.0f,
					0.0f + normal_y * 1.0f - (sun_position_y - 0.5f) * 6.0f
				)
			)
			-
			sun_size * 1.0f
			,
			0.0f
		)
		*
		(sun_blur * 8.0f + 0.0f);
		
		indirect_sun_angle = clamp(indirect_sun_angle, 0.0f, 1.0f);
		
		//						unlighted					lighted
		indirect_sun_light = mix(vec3(0.95f, 0.90f, 1.0f) * free_sky_light, vec3(1.1f, 1.05f, 1.0f) * free_sun_light, indirect_sun_angle);
		//indirect_sun_light = vec3(1.0f);
	
	sky_light = mix(sky_light_matte, sky_light_gloss, gloss_power);
	//sky_light += texture(SD_array[4], reflect_coord + vec2(0.0f, ground_level * 2.0f - 1.0f)).a;
	
	

	//sun_light *= 1.0f - c_rgba.a;
	
	
	
	
	FragColor.rgb
	=
	clamp
	(
		texture(texture1, TexCoord).rgb
		*
		(
			//vec3(c_rgba * 1.0f)// * (2.0f - c_rgba.a)
			mix(vec3(0.0f), c_rgba.rgb * reflection_multiplier, min(gloss_result * 1.0f, 1.0f))
			+
			mix(indirect_sun_light, direct_sun_light, min(gloss_result , 1.0f))
			//vec3(c_rgba) * 2.0f
		)
		*
		ourColor.rgb,
		vec3(0.0f),
		vec3(1.0f)
	);
	
	//FragColor.r = (reflect_pos_x);
	//FragColor.g = (reflect_pos_y);
	//FragColor.b = 0.5f;
	
	//FragColor.rgb = vec3(dist_total);
	FragColor.a = texture(texture1, TexCoord).a * ourColor.a;
	//FragColor.rgb = vec3(dist_total);
	//FragColor.rgb = vec3(indirect_sun_angle);
	//FragColor.rgb = vec3(reflect_coord.x, reflect_coord.y, 1.0f);
	//FragColor.rgb = texture(texture1, TexCoord).rgb * ourColor.rgb;
	//FragColor.rgb =  (sky_light) * (1.0f - gloss_result) + (sun_light);
	//FragColor.rgb =  vec3(sun_light);
	//FragColor.rgb =  vec3(texture(texture1, NormalMapTexCoord));	FragColor.a = 1.0;
	//FragColor.rgb =  vec3(texture(texture1, GlossMapTexCoord));	FragColor.a = 1.0;
	
	//FragColor.rgb =  vec3(c_r, c_g, c_b);	FragColor.a = 1.0;

}

