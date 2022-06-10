

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
uniform float input_gloss = 1.0f;
uniform float skydome_light_power = 1.0f;
uniform float free_top_light = 0.45f;
uniform float direct_sun_matte_multiplier = 1.0f;

uniform float sun_position_x = 0.5f;
uniform float sun_position_y = 0.55f;

uniform float ground_level = 0.5f;

uniform float normal_map_multiplier = 1.0f;
uniform float gloss_map_multiplier = 1.0f;

uniform float screen_offset_x;
uniform float screen_offset_y;
uniform float screen_offset_z;

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

vec3 sun_light_gloss = vec3(1.5f, 1.0f, 0.5f);
vec3 sun_light_matte = vec3(1.5f, 1.5f, 1.0f);
vec3 sun_light;

vec3 sky_light_gloss = vec3(0.9f, 1.1f, 1.2f);
vec3 sky_light_matte = vec3(0.85f, 0.875f, 0.9f);
vec3 sky_light;


float AO_bottom_shade_factor;

void main()
{
	
	gloss_power = min(texture(texture1, GlossMapTexCoord).b * gloss_map_multiplier, 1.0f);
	//gloss_power = 0.2f;
	level = (1.0f - gloss_power) * 4.0f;
	//level = 0.0f;
	
	glossy_flat = clamp(int(floor(level)), 0, 4);
	//glossy_flat = 4 - glossy_flat;
	
	interpolation_B = level - glossy_flat;
	interpolation_A = 1.0f - interpolation_B;
	
	
	normal_x = (texture(texture1, NormalMapTexCoord).r - 0.5f) * 2.0f * normal_map_multiplier;
	normal_y = (texture(texture1, NormalMapTexCoord).g - 0.5f) * 2.0f * normal_map_multiplier;
	
	reflect_pos_x = 0.999f * (normal_x + 1.0f)		+ (gl_FragCoord.x / 1920.0f		* (1.0f - abs(normal_x)))	* 0.999f + 0.999 / 2.0f * abs(normal_x);
	reflect_pos_y = 0.333f * (normal_y + 1.0f)		+ (WorldPosition.y / 1080.0f	* (1.0f - abs(normal_y)))	* 0.333f + 0.333 / 2.0f * abs(normal_y);
	//((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 1.0f;
	
	//reflect_pos_y += (ground_level * 2.0f - 1.0f);
	reflect_coord =
	vec2
	(
		//base offset		screen position offset					//normal offset
		reflect_pos_x,
		
		
		reflect_pos_y
	);
	
	

	
	if (glossy_flat == 0)
	{c_rgba = clamp ((texture(SD_array[0], reflect_coord + vec2(0.0f, ground_level * 2.0f - 1.0f)) * interpolation_A + texture(SD_array[1], reflect_coord+ vec2(0.0f, ground_level * 2.0f - 1.0f)) * interpolation_B), vec4(0.0f), vec4(2.0f, 1.9f, 1.8f, 1.0f));}
	else
	if (glossy_flat == 1)
	{c_rgba = clamp ((texture(SD_array[1], reflect_coord + vec2(0.0f, ground_level * 2.0f - 1.0f)) * interpolation_A + texture(SD_array[2], reflect_coord+ vec2(0.0f, ground_level * 2.0f - 1.0f)) * interpolation_B), vec4(0.0f), vec4(2.0f, 1.9f, 1.8f, 1.0f));}
	else
	if (glossy_flat == 2)
	{c_rgba = clamp ((texture(SD_array[2], reflect_coord + vec2(0.0f, ground_level * 2.0f - 1.0f)) * interpolation_A + texture(SD_array[3], reflect_coord+ vec2(0.0f, ground_level * 2.0f - 1.0f)) * interpolation_B), vec4(0.0f), vec4(2.0f, 1.9f, 1.8f, 1.0f));}                                                                                                                                                                   
	else
	if (glossy_flat == 3)
	{c_rgba = clamp ((texture(SD_array[3], reflect_coord + vec2(0.0f, ground_level * 2.0f - 1.0f)) * interpolation_A + texture(SD_array[4], reflect_coord+ vec2(0.0f, ground_level * 2.0f - 1.0f)) * interpolation_B), vec4(0.0f), vec4(2.0f, 1.9f, 1.8f, 1.0f));}  
	else
	{c_rgba = clamp (texture(SD_array[4], reflect_coord + vec2(0.0f, ground_level * 2.0f - 1.0f)), vec4(0.0f), vec4(2.0f, 1.9f, 1.8f, 1.0f));}
	
	dist_x = (reflect_pos_x * 0.333f - sun_position_x);
	dist_y = (reflect_pos_y - sun_position_y);
	dist_x /= (1080.0f / 1920.0f);
	
	dist_total = length(vec2(dist_x, dist_y)) * (0.0f + 3.0f);
	dist_total /= 1.0f + (c_rgba.a) * 0.333f;
	//dist_total = 1.0f - dist_total;
	dist_total = clamp(1.0f - (dist_total - 0.075f )* (1.0f + gloss_power * 10.0), 0.0f, 1.0f);
	
	sun_light = (sun_light_gloss * gloss_power	+	sun_light_matte * (1.0f - gloss_power))	* dist_total * (1.0f - c_rgba.a);
	sky_light = (sky_light_gloss * gloss_power	+	sky_light_matte * (1.0f - gloss_power));
	//sky_light += texture(SD_array[4], reflect_coord + vec2(0.0f, ground_level * 2.0f - 1.0f)).a;
	
	

	//sun_light *= 1.0f - c_rgba.a;
	
	gloss_result = gloss_power;
	
	
	FragColor.rgb
	=
	texture(texture1, TexCoord).rgb
	*
	(
		vec3(c_rgba) * brightness_multiplier * gloss_result
		+
		sky_light * (1.0f - gloss_result)
		+
		sun_light * 2.0f * gloss_result
	)
	*
	ourColor.rgb;
	
	//FragColor.rgb = vec3(dist_total);
	FragColor.a = texture(texture1, TexCoord).a * ourColor.a;
	//FragColor.rgb = vec3(dist_total);
	//FragColor.rgb = vec3(reflect_coord.x, reflect_coord.y, 1.0f);
	//FragColor.rgb = texture(texture1, TexCoord).rgb * ourColor.rgb;
	//FragColor.rgb =  (sky_light) * (1.0f - gloss_result) + (sun_light);
	//FragColor.rgb =  vec3(sun_light);
	//FragColor.rgb =  vec3(texture(texture1, NormalMapTexCoord));	FragColor.a = 1.0;
	//FragColor.rgb =  vec3(texture(texture1, GlossMapTexCoord));	FragColor.a = 1.0;
	
	//FragColor.rgb =  vec3(c_r, c_g, c_b);	FragColor.a = 1.0;

}

