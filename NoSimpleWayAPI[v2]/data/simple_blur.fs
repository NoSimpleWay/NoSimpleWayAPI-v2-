

#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float blur_size_x = 1.0f/20480.0f;
uniform float blur_size_y = 1.0f/20480.0f;

vec4 result_color;
float divis = 0.0f;
float mul = 0.0f;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	result_color = vec4(0.0f);
	
	for (int i = -8; i <= 8; i++)
	for (int j = -8; j <= 8; j++)
	{
		mul = 1.0f / (i*i + j*j + 1);
		
		result_color += texture(texture1, TexCoord + vec2(blur_size_x * j, blur_size_y * i)).rgba * mul;
		divis += mul;
	}
	
	result_color /= divis;	
	//result_color.a += 0.2;
	
	FragColor.rgba = result_color;
	//FragColor.a = 1.0f;
	//FragColor.r = gl_FragCoord.x / 1920.0f;
	//FragColor.g = gl_FragCoord.y / 1080.0f;
	//FragColor.b = 0.0f;
}

