#version 330 core
out vec4 FragColor;

//Material directional light
uniform sampler2D MDLdiffuse;
uniform sampler2D MDLspecular;    

//Light directional
uniform vec3 LDLdirection;

uniform vec3 LDLambient;
uniform vec3 LDLdiffuse;
uniform vec3 LDLspecular;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 DLviewPos;

void main()
{
    // ambient
    vec3 ambient = LDLambient * texture(MDLdiffuse, TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(light.position - FragPos);
    vec3 lightDir = normalize(-LDLdirection);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = LDLdiffuse * diff * texture(MDLdiffuse, TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(DLviewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0);//, material.shininess);
    vec3 specular = LDLspecular * spec * texture(MDLspecular, TexCoords).rgb;  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 