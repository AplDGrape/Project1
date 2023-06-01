#include <glad/glad.h>
#include <GLFW/glfw3.h>

//GLM Headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

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
    if (key == GLFW_KEY_D) {
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
    }
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
    if (key == GLFW_KEY_Q) {
        
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
    }
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
    if (key == GLFW_KEY_LEFT) {
        
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
    }
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

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    //for splitscreen view - Oooo
    /*glViewport(0, //min x
        0, //min y
        width, //width
        height //height
    );*/

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

    std::string path = "3D/bunny.obj";
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

    std::vector<GLuint> mesh_indices;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        mesh_indices.push_back(
            shapes[0].mesh.indices[i].vertex_index
        );
    }

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
    GLuint VAO, VBO, EBO; // added EBO for indices
    glGenVertexArrays(1, &VAO); //outputs 1 VBO in a VAO - also creates an array for VBO
    glGenBuffers(1, &VBO); 
    glGenBuffers(1, &EBO);

    //This will tell OpenGl we're working on this VAO
    glBindVertexArray(VAO);
    //assign VBO to VAO above
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER, //type of buffer
        sizeof( /*vertices*/ GL_FLOAT) * attributes.vertices.size(), //size in bytes
        /*vertices*/ &attributes.vertices[0], //array itself
        GL_STATIC_DRAW //static for not moving, dynamic for moving
    );

    //tells openGl wat to o with the data above
    glVertexAttribPointer(
        0, //0 for position, 1 for uv, 2 for textures
        3, //how many indices - 3 for x y z
        GL_FLOAT, //wat array it is
        GL_FALSE, 
        3 * sizeof(GL_FLOAT),
        (void*)0 //will be explain in the future
    );
    //this will enable index 0 above
    glEnableVertexAttribArray(0);

    //EBO for indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(/*indices*/ GLuint) * mesh_indices.size(),
        /*indices*/ mesh_indices.data(),
        GL_STATIC_DRAW
    );

    //this tells opengl we're done with VBO & VAO and now EBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //float x_mod = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glm::vec3 cameraPos = glm::vec3(0, 0, 10.f);
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

        //x_mod += 0.001f;

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
        
        //no longer for the above line code
        glDrawElements(
            GL_TRIANGLES,
            //sizeof(indices),
            mesh_indices.size(),
            GL_UNSIGNED_INT,
            0
        );

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