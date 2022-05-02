#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec2 normalMapTexCoord;
layout (location = 4) in vec2 glossMapTexCoord;

out vec4 ourColor;
out vec2 TexCoord;
out vec2 NormalMapTexCoord;
out vec2 GlossMapTexCoord;

out vec3 WorldPosition;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPos.x, aPos.y + aPos.z, 1.0, 1.0);
	
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	
	NormalMapTexCoord = vec2(normalMapTexCoord.x, normalMapTexCoord.y);
	GlossMapTexCoord = vec2(glossMapTexCoord.x, glossMapTexCoord.y);
	
	WorldPosition
	=
	vec3
	(
		aPos[0],
		aPos[1],
		aPos[2]
	);
	
	
}