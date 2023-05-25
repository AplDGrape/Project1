#version 330 core

layout(location = 0) in vec3 aPos;
//0 at vertexattribarray position

//uniform float x;
//uniform float y;

uniform mat4 transform;

uniform mat4 projection;

void main(){

	//vec3 newPos = vec3(aPos.x, aPos.y, aPos.z);

	//gl_Position = transform * vec4(aPos, 1.0);

	gl_Position = projection * transform * vec4(aPos, 1.0);

	//gl_Position = vec4(newPos, 1.0);
}
