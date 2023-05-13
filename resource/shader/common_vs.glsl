#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 proj;
uniform mat4 model;

uniform vec4 info;

void main() {
	gl_Position = proj * model * vec4(aPos, 1.0f);
	// TexCoord = vec2(aTexCoord.x , aTexCoord.y );
	TexCoord = vec2((aTexCoord.x + info[2])/info[0], (aTexCoord.y + info[3])/info[1]);
}