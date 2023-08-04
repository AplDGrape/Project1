#version 330 core

//Get the vertex position of the skybox
layout(location = 0) in vec3 aPos;

//A cubemap takes in a vec3 instead of 2 so using 3 :)
out vec3 texCoord;

//Create a projection variable
//Assigning the projection matrix here
uniform mat4 projection;
//Create a view variable and assigning it here as well
uniform mat4 view;

void main (){
	//no need for the transformation matrix for the skybox
	vec4 pos = projection * //Multiply the projection matrix in the view
					view * //Multiply the view with the position
					vec4(aPos, 1.0);

	//Directly write onto view space
	gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);

	//Assign texcoord with the vertex position directly
	texCoord = aPos;

	//gl_Position = projection * view * vec4(aPos, 1.0);
}