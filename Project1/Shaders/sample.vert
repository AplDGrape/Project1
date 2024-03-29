#version 330 core

layout(location = 0) in vec3 aPos;
//0 at vertexattribarray position

//the normals has attribute position 1
//Accesses the normals and assignes it to vertexNormal
layout(location = 1) in vec3 vertexNormal;

//the tex coord/uv is at 0
//accessess the uv and assignes it the aTex
layout(location = 2) in vec2 aTex;

//Location 3 == tangent
layout(location = 3) in vec3 m_tan;
//Location 4 == bitangent
layout(location = 4) in vec3 m_btan;

//Matrix that will convert tangent space to object space
out mat3 TBN;

//pass the tex coord to the fragment shader
out vec2 texCoord;

//pass the processed normals to the fragment shader later
out vec3 normCoord;
//pass the position of the vertex to the fragment shader later
out vec3 fragPos;

uniform float x;
//uniform float y;

uniform mat4 view;
uniform mat4 transform;

uniform mat4 projection;

void main(){

	vec3 newPos = vec3(aPos.x, aPos.y, aPos.z);
	//gl_Position = transform * vec4(aPos, 1.0);
	//gl_Position = vec4(newPos, 1.0);

	gl_Position = projection * view * transform * vec4(newPos, 1.0);

	//Assign the UV
	texCoord = aTex;

	//get the normal matrix and convert it to a 3x3 matrix
	//normCoord = mat3(transpose(inverse(transform))) * vertexNormal; 
	// apply the normal matrix to the normal data

	//Extract this from the previous formula of normCoord
	mat3 modelMat = mat3(transpose(inverse(transform))); 
	normCoord = modelMat * vertexNormal;

	//Tangent
	vec3 T = normalize(modelMat * m_tan);
	//Bitangent
	//vec3 B = normalize(modelMat * m_btan);
	//Normal
	vec3 N = normalize(normCoord);

	//Apply the Gram-Schmidt process to make T orthogonal to N
	T = normalize(T - dot(T, N) * N);
	//We can now get B by using only N and T
	vec3 B = cross(N, T);

	//Assign the TBN output
	TBN = mat3(T, B, N);

	//the position is just your transform matrix applied to the vertex as a vector 3
	fragPos = vec3(transform * vec4(newPos, 1.0)); // vertex position in world space
}
