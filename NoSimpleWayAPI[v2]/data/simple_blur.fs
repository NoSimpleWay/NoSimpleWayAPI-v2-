

#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float blur_size_x = 1.0f/20480.0f;
uniform float blur_size_y = 1.0f/20480.0f;

vec3 result_color;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	result_color = vec3(0.0f, 0.0f, 0.0f);
	
	for (int i = -3; i <= 3; i++)
	for (int j = -3; j <= 3; j++)
	{
		result_color += texture(texture1, TexCoord + vec2(blur_size_x * j, blur_size_y * i)).rgb;
	}
	
	result_color /= 49.0f;	
	
	FragColor.rgb = result_color;
	FragColor.a = 1.0f;
	//FragColor.r = gl_FragCoord.x / 1920.0f;
	//FragColor.g = gl_FragCoord.y / 1080.0f;
	//FragColor.b = 0.0f;
}

