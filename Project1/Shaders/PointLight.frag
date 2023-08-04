#version 330 core

out vec4 FragColor;

//Material
uniform sampler2D PMLdiffuse;
uniform sampler2D PMLspecular;    
//float shininess;

//Light
uniform vec3 PLLposition;  
  
uniform vec3 PLLambient;
uniform vec3 PLLdiffuse;
uniform vec3 PLLspecular;
	
float constant;
float linear;
float quadratic;

//Pass from vertex shader
in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 PLviewPos;

void main()
{
    // ambient
    vec3 ambient = PLLambient * texture(PMLdiffuse, TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(PLLposition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = PLLdiffuse * diff * texture(PMLdiffuse, TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0); //, material.shininess);
    vec3 specular = PLLspecular * spec * texture(PMLspecular, TexCoords).rgb;  
    
    // attenuation
    float distance    = length(PLLposition - FragPos);
    float attenuation = 1.0 / (PLLconstant + linear * distance + quadratic * (distance * distance));    

    ambient  *= attenuation;  
    diffuse   *= attenuation;
    specular *= attenuation;   
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 