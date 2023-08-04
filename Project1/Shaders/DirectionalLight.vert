#version 330 core

//0 at vertexattribarray position
layout(location = 0) in vec3 aPos;
//1 for attribute normal
layout(location = 1) in vec3 aNormal;
//2 for texcoord
layout(location = 2) in vec3 aTexCoords;

//Pass to directional light fragment shader
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    TexCoords = aTexCoords;
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}