#include <glad/glad.h>
#include <GLFW/glfw3.h>

//GLM Headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

//stb_image
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>
#include <iostream>

float x_mod = 0;
float y_mod = 0;
float z_mod = -1;

float scale_x = 1;
float scale_y = 1;

float x, y, z;
float theta;
float theta_x;
float theta_y;

float width = 600.0f;
float height = 600.0f;

void Key_Callback(
    GLFWwindow* window,
    int key, //key code
    int scancode, //physical position in the keyboard
    int action, // press or release
    int mod //modifier keys - ctrl alt shift
)
{
    //transform
    /*if (key == GLFW_KEY_D) {
        //x_mod += 0.1f;
        switch (action) {
            case GLFW_PRESS:
                x_mod += 0.01f;
                break;

            case GLFW_REPEAT:
                x_mod += 0.01f;
                break;
            
        }
    }
    if (key == GLFW_KEY_A) {
        switch (action) {
            case GLFW_PRESS:
                x_mod -= 0.01f;
                break;

            case GLFW_REPEAT:
                x_mod -= 0.01f;
                break;

        }
    }*/
    if (key == GLFW_KEY_W) {
        switch (action) {
            case GLFW_PRESS:
                y_mod += 0.01f;
                break;

            case GLFW_REPEAT:
                y_mod += 0.01f;
                break;

        }
    }
    if (key == GLFW_KEY_S) {
        switch (action) {
            case GLFW_PRESS:
                y_mod -= 0.01f;
                break;

            case GLFW_REPEAT:
                y_mod -= 0.01f;
                break;

        }
    }
    //zoom in/out
    if (key == GLFW_KEY_X) {
        switch (action) {
            case GLFW_PRESS:
                z_mod += 0.01f;
                break;

            case GLFW_REPEAT:
                z_mod += 0.01f;
                break;

        }
    }
    if (key == GLFW_KEY_Z) {
        switch (action) {
            case GLFW_PRESS:
                z_mod -= 0.01f;
                break;

            case GLFW_REPEAT:
                z_mod -= 0.01f;
                break;

        }
    }
    //scale
    /*
    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        scale_x += 0.1f;
    }
    if (key == GLFW_KEY_X && action == GLFW_PRESS) {
        scale_x -= 0.1f;
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        scale_y += 0.1f;
    }
    if (key == GLFW_KEY_V && action == GLFW_PRESS) {
        scale_y -= 0.1f;
    }
    */
    /*if (key == GLFW_KEY_Q) {
        
        switch (action) {
            case GLFW_PRESS:
                scale_x -= 0.1f;
                scale_y -= 0.1f;
                break;

            case GLFW_REPEAT:
                scale_x -= 0.1f;
                scale_y -= 0.1f;
                break;

        }
    }
    if (key == GLFW_KEY_E) {
        switch (action) {
            case GLFW_PRESS:
                scale_x += 0.1f;
                scale_y += 0.1f;
                break;

            case GLFW_REPEAT:
                scale_x += 0.1f;
                scale_y += 0.1f;
                break;

        }
    }*/
    //rotation
    if (key == GLFW_KEY_DOWN) {
        
        switch (action) {
            case GLFW_PRESS:
                theta_x += 10.0f;
                break;

            case GLFW_REPEAT:
                theta_x += 10.0f;
                break;

        }
    }
    if (key == GLFW_KEY_UP) {
        
        switch (action) {
            case GLFW_PRESS:
                theta_x -= 10.0f;
                break;

            case GLFW_REPEAT:
                theta_x -= 10.0f;
                break;

        }
    }
    /*if (key == GLFW_KEY_LEFT) {
        
        switch (action) {
            case GLFW_PRESS:
                theta_y -= 10.0f;
                break;

            case GLFW_REPEAT:
                theta_y -= 10.0f;
                break;

        }
    }
    if (key == GLFW_KEY_RIGHT) {
        switch (action) {
            case GLFW_PRESS:
                theta_y += 10.0f;
                break;

            case GLFW_REPEAT:
                theta_y += 10.0f;
                break;

        }
    }*/
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Francis Apolinar", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    std::string path = "3D/djSword.obj";
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    tinyobj::attrib_t attributes;

    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str()
    );

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    //for splitscreen view - Oooo
    /*glViewport(0, //min x
        0, //min y
        width, //width
        height //height
    );*/

    GLfloat UV[]{
        0.f, 1.f,
        0.f, 0.f,
        1.f, 1.f,
        1.f, 0.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 1.f,
        0.f, 0.f
    };

    //Fix the flipped texture
    stbi_set_flip_vertically_on_load(true);

    int img_width, //width of the texture
        img_height, //height of the texture
        colorChannels; //number of color channels

    //load the texture and fill out the variables
    unsigned char* tex_bytes =
        stbi_load("3D/ayaya.png", //texture path
            &img_width, //fills out the width
            &img_height, //fills out the height
            &colorChannels, //fills out the color channel
            0);

    //OpenGL reference to the texture
    GLuint texture;
    //Generate a reference
    glGenTextures(1, &texture);
    //Set the current texture we're working on to texture0
    glActiveTexture(GL_TEXTURE0);
    //Bind our next tasks to Tex0 to our current reference similar to what we're doing to VBOs
    glBindTexture(GL_TEXTURE_2D, texture);

    //Assign the loaded texture to the Opengl reference
    glTexImage2D(GL_TEXTURE_2D,
        0, //texture 0
        GL_RGBA, //target color format of the texture
        img_width, //texture width
        img_height, //texture height
        0,
        GL_RGBA, //Color format of the texture
        GL_UNSIGNED_BYTE,
        tex_bytes); //loaded texture in bytes

    //generate the mipmaps to the current texture
    glGenerateMipmap(GL_TEXTURE_2D);
    //free up the loaded bytes
    stbi_image_free(tex_bytes);

    //Enable depth testing
    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, Key_Callback);

    //shader here
    std::fstream vertSrc("Shaders/sample.vert");
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    std::fstream fragSrc("Shaders/sample.frag");
    std::stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();
    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &v, NULL);
    glCompileShader(vertShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &f, NULL);
    glCompileShader(fragShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);

    glLinkProgram(shaderProgram);
    //shader ends here

    //skybox shader
    std::fstream sky_vertSrc("Shaders/skybox.vert");
    std::stringstream sky_vertBuff;
    sky_vertBuff << sky_vertSrc.rdbuf();
    std::string sky_vertS = sky_vertBuff.str();
    const char* sky_v = sky_vertS.c_str();

    std::fstream sky_fragSrc("Shaders/skybox.frag");
    std::stringstream sky_fragBuff;
    sky_fragBuff << sky_fragSrc.rdbuf();
    std::string sky_fragS = sky_fragBuff.str();
    const char* sky_f = sky_fragS.c_str();

    GLuint sky_vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sky_vertShader, 1, &sky_v, NULL);
    glCompileShader(sky_vertShader);

    GLuint sky_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sky_fragShader, 1, &sky_f, NULL);
    glCompileShader(sky_fragShader);

    GLuint skyboxProgram = glCreateProgram();
    glAttachShader(skyboxProgram, sky_vertShader);
    glAttachShader(skyboxProgram, sky_fragShader);

    glLinkProgram(skyboxProgram);
    //skybox shader ends here

    std::vector<GLuint> mesh_indices;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        mesh_indices.push_back(
            shapes[0].mesh.indices[i].vertex_index
        );
    }

    //Initialize the array of vertex data
    std::vector<GLfloat> fullVertexData;
    //loop through all the vertex indices
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        //assign the index for easy access
        tinyobj::index_t vData = shapes[0].mesh.indices[i];

        //push the x position of the vertex
        fullVertexData.push_back(
            //multiply the index by 3 to get the base offset
            attributes.vertices[(vData.vertex_index * 3)]
        );

        //push the y position of the vertex
        fullVertexData.push_back(
            //add the base offset by 1 to get y
            attributes.vertices[(vData.vertex_index * 3) + 1]
        );

        //push the z position of the vertex
        fullVertexData.push_back(
            //add the base offset by 2 to get z
            attributes.vertices[(vData.vertex_index * 3) + 2]
        );

        //normals xyz
        fullVertexData.push_back(
            attributes.normals[vData.normal_index * 3]
        );

        fullVertexData.push_back(
            attributes.normals[vData.normal_index * 3 + 1]
        );

        fullVertexData.push_back(
            attributes.normals[vData.normal_index * 3 + 2]
        );

        //push the U of the tex coords
        fullVertexData.push_back(
            //multiply the index by 2 to get the base offset
            attributes.texcoords[(vData.texcoord_index * 2)]
        );

        //push the V of the tex coords
        fullVertexData.push_back(
            //add the base offset by 1 to get V
            attributes.texcoords[(vData.texcoord_index * 2) + 1]
        );
    }

    /*
      7--------6
     /|       /|
    4--------5 |
    | |      | |
    | 3------|-2
    |/       |/
    0--------1
    */
    //Vertices for the cube
    float skyboxVertices[]{
        -1.f, -1.f, 1.f, //0
        1.f, -1.f, 1.f,  //1
        1.f, -1.f, -1.f, //2
        -1.f, -1.f, -1.f,//3
        -1.f, 1.f, 1.f,  //4
        1.f, 1.f, 1.f,   //5
        1.f, 1.f, -1.f,  //6
        -1.f, 1.f, -1.f  //7
    };

    //Skybox Indices
    unsigned int skyboxIndices[]{
        1,2,6,
        6,5,1,

        0,4,7,
        7,3,0,

        4,5,6,
        6,7,4,

        0,3,2,
        2,1,0,

        0,1,5,
        5,4,0,

        3,7,6,
        6,2,3
    };

    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);

    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);

    std::string facesSkybox[]{
        "Skybox/rainbow_rt.png", //right
        "Skybox/rainbow_lf.png", //left
        "Skybox/rainbow_up.png", //up
        "Skybox/rainbow_dn.png", //down
        "Skybox/rainbow_ft.png", //front
        "Skybox/rainbow_bk.png" //back
    };

    unsigned int skyboxTex;

    glGenTextures(1, &skyboxTex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);

    //avoid pixelations worst case is blur
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //avoid tiling
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++) {
        int w, h, skyCChannel;
        stbi_set_flip_vertically_on_load(false);

        unsigned char* data = stbi_load(
            facesSkybox[i].c_str(),
            &w,
            &h,
            &skyCChannel,
            0
        );

        if (data) {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB, //png for GL_RGB
                w,
                h,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
        }

        stbi_image_free(data);
    }

    stbi_set_flip_vertically_on_load(true);

    GLfloat vertices[]{
        //x y z
        0.f, 0.5f, 0.f, //point 1
        -0.5f, -0.5f, 0.f, //point 2
        0.5f, -0.5f, 0.f
    };

    GLuint indices[]{
        0, 1, 2
    };

    //changes the size of screen from 1 to x, x being any number
    /*glm::mat4 projection = glm::ortho(
        -2.0f, //left moost point
        2.0f, //right most point
        -2.0f, //bottom most point
        2.0f, //top most point
        -1.0f, //z near
        1.0f); //z far
    */

    glm::mat4 projection = glm::perspective(
        glm::radians(60.0f), //fov
        height / width, //aspect ratio / window height and width
        0.1f, //near
        100.f //far
    );

    //creates a 3x3 identity matrix
    glm::mat3 identity_matrix3 = glm::mat3(1.0f);
    //creates a 4x4 identity matrix
    glm::mat4 identity_matrix4 = glm::mat4(1.0f);

    glm::mat4 translation =
        glm::translate(identity_matrix4,
            glm::vec3(x,
                y,
                z)
        );

    glm::mat4 scale =
        glm::scale(identity_matrix4,
            glm::vec3(x,
                y,
                z)
        );

    glm::mat4 rotation =
        glm::rotate(identity_matrix4,
            glm::radians(theta),
            glm::vec3(x,
                y,
                z)
        );

    //order matters in VAO & VBO
    GLuint VAO, VBO, EBO, VBO_UV; // added EBO for indices & VBO_UV for our UV
    glGenVertexArrays(1, &VAO); //outputs 1 VBO in a VAO - also creates an array for VBO
    glGenBuffers(1, &VBO);
    //commented for vertex attributes
    //glGenBuffers(1, &VBO_UV); //Generate our UV Buffer
    //glGenBuffers(1, &EBO);

    //This will tell OpenGl we're working on this VAO
    glBindVertexArray(VAO);
    //assign VBO to VAO above
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //add in the our new array of vertex data in the VBO
    glBufferData(
        GL_ARRAY_BUFFER,
        //size of the whole array in bytes
        sizeof(GLfloat)* fullVertexData.size(),
        //Data of the array
        fullVertexData.data(),
        GL_DYNAMIC_DRAW
    );

    //tells openGl wat to o with the data above
    glVertexAttribPointer(
        0, //0 for position, 1 for uv, 2 for textures
        3, //how many indices - 3 for x y z
        GL_FLOAT, //wat array it is
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0 //will be explain in the future
    );

    //this will enable index 0 above
    glEnableVertexAttribArray(0);

    ////add in how to get the position data from our array
    //glVertexAttribPointer(
    //    0, //index 0 is the vertex position
    //    3, //position is 3 floats (x, y, z)
    //    GL_FLOAT, //data type of array
    //    GL_FALSE,
    //    //our vertex data has 5 floats in it which is x,y,z,u,v
    //    5 * sizeof(float), //size of vertex data in bytes
    //    (void*)0
    //);

    GLintptr normPointer = 3 * sizeof(float);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPointer
    );

    glEnableVertexAttribArray(1);

    //since our uv starts at index 3 or the 4th index of our vertex data
    GLintptr uvPtr = 6 * sizeof(float);

    //add in how to get the UV data from our array
    glVertexAttribPointer(
        2, //index 2 is tex coordinates / uv
        2, //uv is 2 floats u and v
        GL_FLOAT, //data type of array
        GL_FALSE,
        //our vertex data has 5 floats in it (X,y,z,u,v)
        8 * sizeof(GL_FLOAT),
        //add in the offset here
        (void*)uvPtr
    );

    //glBufferData(
    //    GL_ARRAY_BUFFER, //type of buffer
    //    sizeof( /*vertices*/ GL_FLOAT) * attributes.vertices.size(), //size in bytes
    //    /*vertices*/ &attributes.vertices[0], //array itself
    //    GL_STATIC_DRAW //static for not moving, dynamic for moving
    //);

    //EBO for indices
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    //    sizeof(/*indices*/ GLuint) * mesh_indices.size(),
    //    /*indices*/ mesh_indices.data(),
    //    GL_STATIC_DRAW
    //);
    //above is the EBO stuff
    
    //Bind the UV Buffer
    //glBindBuffer(GL_ARRAY_BUFFER, VBO_UV);

    ////Add in the buffer data
    //glBufferData(GL_ARRAY_BUFFER,
    //    sizeof(GLfloat)* (sizeof(UV) / sizeof(UV[0])), //float * size of the UV array
    //    &UV[0], //the UV array earlier
    //    GL_DYNAMIC_DRAW);
    //Add in how to interpret the array
    //glVertexAttribPointer(
    //    2, //2 for the UV or tex coords
    //    2, // UV
    //    GL_FLOAT, //type of array
    //    GL_FALSE,
    //    2 * sizeof(float), //every 2 index
    //    (void*)0
    //);
    //Enable 2 for out UV/tex coords
    glEnableVertexAttribArray(2);

    //this tells opengl we're done with VBO & VAO and now EBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //float x_mod = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Position of light
        glm::vec3 lightPos = glm::vec3(-10, 3, 0);
        //Light color
        glm::vec3 lightColor = glm::vec3(1, 1, 1);

        //Ambient Strength
        float ambientStr = 0.1f;
        //Ambient Color
        glm::vec3 ambientColor = lightColor;

        //Spec strength
        float specStr = 0.5f;
        //Spec phong
        float specPhong = 16;

        glm::vec3 cameraPos = glm::vec3(-80.f, 0, 30.f);
        glm::mat4 cameraPosMatrix = glm::translate(
            glm::mat4(1.0f),
            cameraPos * -1.0f
        );

        //up direction of the wrld
        glm::vec3 worldUp = glm::normalize(glm::vec3(0, 1.0f, 0));

        //camera's center tilted up by 3
        glm::vec3 cameraCenter = glm::vec3(0, 3.0f, 0);

        //get the forward
        glm::vec3 F = (cameraCenter - cameraPos);
        F = glm::normalize(F);

        //get the right - F x world up
        glm::vec3 R = glm::cross(F, worldUp);
        //get the up - R x F
        glm::vec3 U = glm::cross(R, F);

        glm::mat4 cameraOrientation = glm::mat4(1.0f);

        //matrix[C][R]
        //right
        cameraOrientation[0][0] = R.x;
        cameraOrientation[1][0] = R.y;
        cameraOrientation[2][0] = R.z;

        //up
        cameraOrientation[0][1] = U.x;
        cameraOrientation[1][1] = U.y;
        cameraOrientation[2][1] = U.z;

        //-forward
        cameraOrientation[0][2] = -F.x;
        cameraOrientation[1][2] = -F.y;
        cameraOrientation[2][2] = -F.z;

        //glm::mat4 viewMatrix = cameraOrientation * cameraPosMatrix;
        //easier versin of ^^^^^
        glm::mat4 viewMatrix =
            glm::lookAt(cameraPos, cameraCenter, worldUp);

        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);

        glUseProgram(skyboxProgram);
        glm::mat4 sky_view = glm::mat4(1.0f);
        sky_view = glm::mat4(
            glm::mat3(viewMatrix)
        );

        unsigned int skyProjectionLoc = glGetUniformLocation(skyboxProgram, "projection");
        glUniformMatrix4fv(skyProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        unsigned int skyViewLoc = glGetUniformLocation(skyboxProgram, "view");
        glUniformMatrix4fv(skyViewLoc, 1, GL_FALSE, glm::value_ptr(sky_view));

        glBindVertexArray(skyboxVAO);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);

        glUseProgram(shaderProgram);

        //x_mod += 0.001f;

        theta_y += 0.05f;

        /*unsigned int xLoc = glGetUniformLocation(shaderProgram, "x");
        glUniform1f(xLoc, x_mod);

        unsigned int yLoc = glGetUniformLocation(shaderProgram, "y");
        glUniform1f(yLoc, y_mod);*/

        glm::mat4 transformation_matrix = glm::translate(
            identity_matrix4,
            glm::vec3(x_mod, y_mod, z_mod)); //-1 to see the bunny in the projection matrix since 0 is on the camera itself
        
        transformation_matrix = glm::scale(
            transformation_matrix,
            glm::vec3(scale_x, scale_y, 1)
        );

        transformation_matrix = glm::rotate(
            transformation_matrix,
            glm::radians(theta_x),
            glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f))
        );

        transformation_matrix = glm::rotate(
            transformation_matrix,
            glm::radians(theta_y),
            glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))
        );

        //std::cout << theta << std::endl;

        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc,
            1,
            GL_FALSE,
            glm::value_ptr(viewMatrix));

        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");

        glUniformMatrix4fv(transformLoc,
            1,
            GL_FALSE,
            glm::value_ptr(transformation_matrix));

        unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projLoc,
            1,
            GL_FALSE,
            glm::value_ptr(projection));

        glUseProgram(shaderProgram);

        //drawing time
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3); //tiangle, first index, how many indecis

        //Get the location of tex 0 in the fragment shader
        GLuint tex0Address = glGetUniformLocation(shaderProgram, "tex0");
        //tell opengl to use the texture
        glBindTexture(GL_TEXTURE_2D, texture);

        //use the texture at 0
        glUniform1i(tex0Address, 0);

        //Get the address of the light position from the shader
        GLuint lightAddress = glGetUniformLocation(shaderProgram, "lightPos");
        glUniform3fv(lightAddress, 1, glm::value_ptr(lightPos));
        //Get the address of the light color from the shader
        GLuint lightColorAddress = glGetUniformLocation(shaderProgram, "lightColor");
        glUniform3fv(lightColorAddress, 1, glm::value_ptr(lightColor));

        //Get the address of the ambient str from the shader
        GLuint ambientStrAddress = glGetUniformLocation(shaderProgram, "ambientStr");
        glUniform1f(ambientStrAddress, ambientStr);
        //Get the address of the ambient color from the shader
        GLuint ambientColorAddress = glGetUniformLocation(shaderProgram, "ambientColor");
        glUniform3fv(ambientColorAddress, 1, glm::value_ptr(ambientColor));

        //Get the address of the ambient color from the shader
        GLuint cameraPosAddress = glGetUniformLocation(shaderProgram, "cameraPos");
        glUniform3fv(cameraPosAddress, 1, glm::value_ptr(cameraPos));
        //Get the address of the ambient str from the shader
        GLuint specStrAddress = glGetUniformLocation(shaderProgram, "specStr");
        glUniform1f(specStrAddress, specStr);
        //Get the address of the ambient str from the shader
        GLuint specPhongAddress = glGetUniformLocation(shaderProgram, "specPhong");
        glUniform1f(specPhongAddress, specPhong);

        //since our vertex data has 5 float in it
        //we divide the array size by 5 to get the number of vertices
        glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);

        //no longer for the above line code
        //glDrawElements(
        //    GL_TRIANGLES,
        //    //sizeof(indices),
        //    mesh_indices.size(),
        //    GL_UNSIGNED_INT,
        //    0
        //);

        /*glBegin(GL_POLYGON); manual pentagon :)
        glVertex2f(-0.3f, -0.5f); 
        glVertex2f(-0.5f, 0.1f); 
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, 0.1f);
        glVertex2f(0.3f, -0.5f);
        glEnd(); */
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //cleanup code
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}