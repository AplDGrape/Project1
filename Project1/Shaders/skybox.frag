#version 330 core

//returns a color
out vec4 FragColor;

//take in a vec3 texcoord
in vec3 texCoord;

//add in our cubemap
uniform samplerCube skybox;

void main (){
	//Call the texture function to get the color
	FragColor = texture(skybox, texCoord);
}