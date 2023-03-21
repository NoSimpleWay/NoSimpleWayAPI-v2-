

#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform int blur_table = 0;
uniform float blur_size_x = 1.0f/20480.0f;
uniform float blur_size_y = 1.0f/20480.0f;

vec4 result_color;
float divis = 0.0f;
float mul = 0.0f;

float table[7] = {8.0f, 16.0f, 16.0f, 32.0f, 32.0f, 32.0f, 64.0f};

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	if (blur_table >= 0)
	{
		result_color = vec4(0.0f);
		
		for (int i = -32; i <= 32; i++)
		for (int j = -32; j <= 32; j++)
		{
			mul = 1.0f / (pow((i*i + j*j) / table[blur_table] , 2.0f / (1.0f + blur_table / 15.0f)) + 1.0f) * (texture(texture1, TexCoord).a * 1.0f + 1.0f);
			
			result_color += texture(texture1, TexCoord + vec2(blur_size_x * j, blur_size_y * i) * 1.0f).rgba * mul;
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
	
	FragColor.rgba = result_color;
	//FragColor.rgba = texture(texture1, TexCoord);
	//FragColor.a = 1.0f;
	//FragColor.r = gl_FragCoord.x / 1920.0f;
	//FragColor.g = gl_FragCoord.y / 1080.0f;
	//FragColor.b = 0.0f;
}

