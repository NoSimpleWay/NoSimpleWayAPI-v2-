

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

uniform sampler2D SD_array[6];



uniform float brightness_multiplier = 1.5f;
uniform float input_gloss = 1.0f;
uniform float skydome_light_power = 1.0f;
uniform float free_top_light = 0.45f;
uniform float direct_sun_matte_multiplier = 1.0f;

uniform float sun_position_x = 0.5f;
uniform float sun_position_y = 0.5f;

uniform float sun_zenith = 1.0f;

uniform float screen_offset_x;
uniform float screen_offset_y;
uniform float screen_offset_z;

float c_r;
float c_g;
float c_b;



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


float angle_x;
float angle_y;
float total_angle;

float AO_bottom_shade_factor;

void main()
{
	//gloss_power = 1.0f - (ReflectionTexCoord.y - 0.333f) * 3.0f ;
	//gloss_power = input_gloss;
	gloss_power = texture(texture1, GlossMapTexCoord).b;
	//gloss_power = 0.2f;
	//gloss_power = clamp (WorldPosition.y / 1080.0f * 2.0f, 0.0f, 1.0f);
	
	
	
	level = (1.0f - gloss_power) * 4.0f;
	
	glossy_flat = clamp(int(floor(level)), 0, 4);
	//glossy_flat = 0;
	
	interpolation_B = level - glossy_flat;
	interpolation_A = 1.0f - interpolation_B;
	
	
	normal_x = (texture(texture1, NormalMapTexCoord).r - 0.5f) * 2.0f;
	normal_y = (texture(texture1, NormalMapTexCoord).g - 0.5f) * 2.0f;
	//normal_y = 0.333f;
	
	angle_x = 1.0f-
	min
	(
		abs
		(
			texture
				(
					normal_map_texture,
					NormalMapTexCoord
				).r - (sun_position_x * 2.0f - 0.5f)
		) * 2.0f,
		1.0f
	);
	
	//angle_y = 1.0f - min(abs(texture(normal_gloss_map_texture, NormalGlossMapTexCoord).g - 0.5f) - sun_position_y) * 4.0f, 1.0f);
	
	angle_y = 1.0f-
	min
	(
		abs
		(
			texture
				(
					normal_map_texture,
					NormalMapTexCoord
				).g - (sun_position_y * 2.0f - 0.5f)
		) * 2.0f,
		1.0f
	);
	
	total_angle = min(angle_x, angle_y);
	//total_angle = (angle_x + angle_y) / 2.0f;
	
	//reflect_coord = vec2(gl_FragCoord.x / 1920.0f * 0.3f + 0.3f + normal_x, gl_FragCoord.y / 1080.0f * 0.3f + 0.3f + normal_y);
	
	//normal_x = 0.0f;
	//normal_y = 0.0f;
	reflect_coord =
	vec2
	(
		//base offset		screen position offset					//normal offset
		0.3333f				+ gl_FragCoord.x / 1920.0f * 0.3333f	+  normal_x * 0.333f,
		((WorldPosition[1] + screen_offset_y) / 1080.0f * abs(1.0f - normal_y) + WorldPosition[2] / 1080.0f * (abs(normal_y))) * 0.333f + 0.303f + 0.333f * normal_y
	);
	
	/*
	reflect_coord =
	vec2
	(
	gl_FragCoord.x / 1920.0f * 0.3333f + 0.3333f + normal_x * 1.0f,
	ReflectionTexCoord.y * 0.3333f + 0.3333f + normal_y * 1.0f
	);*/
	
	
	
	
	//glossy_flat = 4;
	if (glossy_flat == 0)
	{
		c_r = clamp ((texture(SD_array[0], reflect_coord).r * interpolation_A + texture(SD_array[1], reflect_coord).r * interpolation_B) * brightness_multiplier, 0.0f, 2.0f);
		c_g = clamp ((texture(SD_array[0], reflect_coord).g * interpolation_A + texture(SD_array[1], reflect_coord).g * interpolation_B) * brightness_multiplier, 0.0f, 1.9f);
		c_b = clamp ((texture(SD_array[0], reflect_coord).b * interpolation_A + texture(SD_array[1], reflect_coord).b * interpolation_B) * brightness_multiplier, 0.0f, 1.8f);
	}
	else
	if (glossy_flat == 1)
	{
		c_r = clamp ((texture(SD_array[1], reflect_coord).r * interpolation_A + texture(SD_array[2], reflect_coord).r * interpolation_B) * brightness_multiplier, 0.0f, 2.0f);
		c_g = clamp ((texture(SD_array[1], reflect_coord).g * interpolation_A + texture(SD_array[2], reflect_coord).g * interpolation_B) * brightness_multiplier, 0.0f, 1.9f);
		c_b = clamp ((texture(SD_array[1], reflect_coord).b * interpolation_A + texture(SD_array[2], reflect_coord).b * interpolation_B) * brightness_multiplier, 0.0f, 1.8f);
	}
	else
	if (glossy_flat == 2)
	{
		c_r = clamp ((texture(SD_array[2], reflect_coord).r * interpolation_A + texture(SD_array[3], reflect_coord).r * interpolation_B) * brightness_multiplier, 0.0f, 2.0f);
		c_g = clamp ((texture(SD_array[2], reflect_coord).g * interpolation_A + texture(SD_array[3], reflect_coord).g * interpolation_B) * brightness_multiplier, 0.0f, 1.9f);
		c_b = clamp ((texture(SD_array[2], reflect_coord).b * interpolation_A + texture(SD_array[3], reflect_coord).b * interpolation_B) * brightness_multiplier, 0.0f, 1.8f);
	}                                                                                                                                                                   
	else
	if (glossy_flat == 3)
	{
		c_r = clamp ((texture(SD_array[3], reflect_coord).r * interpolation_A + texture(SD_array[4], reflect_coord).r * interpolation_B) * brightness_multiplier, 0.0f, 2.0f);
		c_g = clamp ((texture(SD_array[3], reflect_coord).g * interpolation_A + texture(SD_array[4], reflect_coord).g * interpolation_B) * brightness_multiplier, 0.0f, 1.9f);
		c_b = clamp ((texture(SD_array[3], reflect_coord).b * interpolation_A + texture(SD_array[4], reflect_coord).b * interpolation_B) * brightness_multiplier, 0.0f, 1.8f);
	}  
	else
	{                                                                                                                                                                   
		c_r = clamp ((texture(SD_array[4], reflect_coord).r) * brightness_multiplier, 0.0f, 2.0f);
		c_g = clamp ((texture(SD_array[4], reflect_coord).g) * brightness_multiplier, 0.0f, 1.9f);
		c_b = clamp ((texture(SD_array[4], reflect_coord).b) * brightness_multiplier, 0.0f, 1.8f);
	}
	
	gloss_result = gloss_power;
	//gloss_result = 1.0f;
	
	/*AO_bottom_shade_factor = max(0.0f, (WorldPosition[2] / (WorldPosition[2] + 100.0f + 100.0f * (1.0f - gloss_result))) * (1.0f - normal_y) + normal_y);
	AO_bottom_shade_factor = 1.0f - pow(1.0f - AO_bottom_shade_factor, 2);
	AO_bottom_shade_factor = AO_bottom_shade_factor / 2.0f + 0.5f;*/
	AO_bottom_shade_factor = 1.0f;
	
	matte_result_sun = (1.0f - gloss_power) * total_angle;
	matte_result_sun *= direct_sun_matte_multiplier;
	
	matte_result_sky = (1.0f - gloss_power) * (1.0f - total_angle);
	matte_result_sky += (normal_y * (1.0f - gloss_power)  / 2.0f) * free_top_light;
	matte_result_sky *= skydome_light_power;
	
	//matte_result_sky = 1.0f;
	//matte_result_sky *= skydome_light_power + (normal_y * (1.0f - gloss_power)  / 2.0f);
	//matte_result = 0.0f;
	
	

	
	FragColor = texture(texture1, TexCoord)
	*
	ourColor
	*
	vec4
	(
		c_r * gloss_result + (matte_result_sun * 1.00f + matte_result_sky	* 1.000f)	* sun_zenith					* AO_bottom_shade_factor,
		c_g * gloss_result + (matte_result_sun * 1.00f + matte_result_sky	* 1.000f)	* pow(sun_zenith, 1.5f)			* AO_bottom_shade_factor,
		c_b * gloss_result + (matte_result_sun * 1.00f + matte_result_sky	* 1.000f)	* pow(sun_zenith, 2.0f)			* AO_bottom_shade_factor,
	1.0f
	);
	
	//FragColor.a = 1.0f;
	//FragColor = texture(texture1, TexCoord);
	//FragColor = texture(normal_gloss_map_texture, NormalGlossMapTexCoord);
	
	/*if ((WorldPosition[2] + screen_offset_z) < 50.0f)
	{
		FragColor.rgb *= max(vec3 ((WorldPosition[2] + screen_offset_z) / 1080.0f * 10.0f), 0.0f);
		
		if
		(
			(int(gl_FragCoord.x + gl_FragCoord.y) % max(int((WorldPosition[2] + screen_offset_z) / 10.0f + 1.0f), 2) == 0)
			&&
			(int(gl_FragCoord.y) % max(int((WorldPosition[2] + screen_offset_z) / 10.0f + 1.0f), 2) == 0)
		)
		{FragColor.a = 0.0f;}
	}*/
	
	/*if ((WorldPosition[1] + screen_offset_y) / 1080.0f < 0.00)
	{
		FragColor.a = 0.0f;
	}*/
	
	
	/*
	if ((WorldPosition[1] + screen_offset_y) / 1080.0f < 0.00)
	{
		FragColor.a = 0.0f;
	}
	*/
	
	//FragColor = texture(texture1, GlossMapTexCoord);	
	//FragColor = vec4(c_r, c_g, c_b, 1.0f);
	//FragColor = vec4(WorldPosition.x / 1920.0f, WorldPosition.y / 1080.0f, 0.0f, 1.0f);
	
	/*
	FragColor.r = (WorldPosition[0] + screen_offset_x) / 1920.0f;
	FragColor.g = (WorldPosition[1] + screen_offset_y) / 1080.0f;
	FragColor.b = WorldPosition[2] / 1080.0f;*/
	
	
	//FragColor = vec4(normal_x,normal_y,1.0f,1.0f);
	//FragColor = vec4(glossy_flat,glossy_flat,glossy_flat,1.0f);
	
	//FragColor.rgb = vec3(ReflectionTexCoord.y);
	//FragColor.r = gl_FragCoord.x / 1920.0f;
	//FragColor.g = gl_FragCoord.y / 1080.0f;
	//FragColor.b = 0.0f;
}

