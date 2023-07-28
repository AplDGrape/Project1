#version 330 core

//texture to be passed
uniform sampler2D tex0;

//should recieve the texcoord from the vertex shader
in vec2 texCoord;

//normal data
in vec3 normCoord;
//vertex position in world space
in vec3 fragPos;

//position of the light source
uniform vec3 lightPos;
//color of the light
uniform vec3 lightColor;

//strength of the ambient light
uniform float ambientStr;
//color of the ambient light
uniform vec3 ambientColor;

//Camera position
uniform vec3 cameraPos;
//specular str
uniform float specStr;
//specular phong
uniform float specPhong;

out vec4 FragColor; //Color pixel

void main(){
	//any color here
	//                 r     g     b     a
	//FragColor = vec4(0.0f, 0.3f, 0.4f, 1.0f);

	//normalize the recieved normals
	vec3 normal = normalize(normCoord);
	//get the direction of the light to the fragment
	vec3 lightDir = normalize(lightPos - fragPos);

	//get the ambient light
	vec3 ambientCol = ambientColor * ambientStr;

	//Get our view direction from the camera to the fragment
	vec3 viewDir = normalize(cameraPos - fragPos);
	//Get the reflection vector
	vec3 reflectDir = reflect(-lightDir, normal);

	//Get the specular light
	float spec = pow(max(dot(reflectDir, viewDir), 0.1), specPhong);
	vec3 specColor = spec* specStr * lightColor;

	//apply the diffuse formula here
	float diff = max(dot(normal, lightDir), 0.0);
	//multiply it to the desired light color
	vec3 diffuse = diff * lightColor;

	//apply it to the texture
	FragColor = vec4(specColor + diffuse + ambientCol, 1.0) * texture(tex0, texCoord);

	//assign the texture color using the function
	//FragColor = texture(tex0, texCoord);
}