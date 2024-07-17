

#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float blur_size = 0.0f;
uniform float blur_size_x = 1.0f/20480.0f;
uniform float blur_size_y = 1.0f/20480.0f;

vec4 result_color;
float divis = 0.0f;
float mul = 0.0f;

float linear_dist;
float dist_factor;

float table[7] = {8.0f, 16.0f, 16.0f, 32.0f, 32.0f, 32.0f, 64.0f};

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	//blur_size = blur_size * 2.0f;
	if (blur_size > 0.0f)
	{
		result_color = vec4(0.0f);
		
		for (int i = -8; i <= 8; i++)
		for (int j = -8; j <= 8; j++)
		{
			linear_dist = (i*i + j*j) / 8.0f;
			//linear_dist = pow(linear_dist, 2.0f);
			//linear_dist = 0.0f;
			dist_factor = 1.0f - linear_dist * linear_dist;
			
			//dist_factor = 1.0f;
			
			mul = clamp(dist_factor, 0.0f, 1.0f) * (texture(texture1, TexCoord).a);
			//mul = 1.0f;
			
			result_color += texture(texture1, TexCoord + vec2(blur_size_x * float(j) / 8.0f, blur_size_y * float(i) / 8.0f) * blur_size).rgba * mul;
			divis += mul;
		}
		
		result_color /= divis;	
	}
	else
	{
		result_color = texture(texture1, TexCoord).rgba;
	}
	
	//result_color.a += 0.2;
	//result_color.a = 1.0;
	
	FragColor.rgba = clamp(result_color, vec4(0.0f), vec4(1.0f));
	//FragColor.rgba = texture(texture1, TexCoord);
	//FragColor.a = 1.0f;
	//FragColor.r = gl_FragCoord.x / 1920.0f;
	//FragColor.g = gl_FragCoord.y / 1080.0f;
	//FragColor.b = 0.0f;
}

