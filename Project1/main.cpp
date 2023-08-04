//includes transfered to main.h
#include "main.h"

//Player
//#include "Controls.h"

//#include "SkyBox.h"

//Global Variables
GLFWwindow* window;

float x, y, z;

float x_mod = 0;
float y_mod = 0;
float z_mod = -1;

float scale_x = 1;
float scale_y = 1;

float theta;
float theta_x;
float theta_y;

float width = 600.0f;
float height = 600.0f;

//time
float deltaTime = 0.0f; //time between current frame and last frame
float lastFrame = 0.0f; //time for last frame

//Calls the mouse control callback
void Mouse_Callback(GLFWwindow* window, double xpos, double ypos);

//Calls the 1st person controls callback
void FirstPerson_Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mod);

//Calls the 3rd person controls callback
void ThirdPerson_Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mod);

class Model {
public:
    
    //void DrawBunny() {
    //    //Relative path to the mesh
    //    std::string path2 = "3D/bunny.obj";
    //    //Will contain the mesh's shapes
    //    std::vector<tinyobj::shape_t> shapes2;
    //    //Will contain the mesh's material
    //    std::vector<tinyobj::material_t> material2;
    //    //Some error messages might popup
    //    std::string warning2, error2;
    //    //Basic attributes related to the mesh
    //    tinyobj::attrib_t attributes2;
    //
    //    //Load the mesh
    //    bool success2 = tinyobj::LoadObj(&attributes2,
    //        &shapes2,
    //        &material2,
    //        &warning2,
    //        &error2,
    //        path2.c_str());
    //
    //    std::vector<GLuint> mesh_indices2;
    //    //iterate through all the vertices and push the indices to our vector
    //    for (int i = 0; i < shapes2[0].mesh.indices.size(); i++) {
    //        mesh_indices2.push_back(shapes2[0].mesh.indices[i].vertex_index);
    //    }
    //
    //    //order matters in VAO & VBO
    //    GLuint VAO2, VBO2, EBO2, VBO_UV2; // added EBO for indices & VBO_UV for our UV
    //    glGenVertexArrays(2, &VAO2); //outputs 1 VBO in a VAO - also creates an array for VBO
    //    glGenBuffers(2, &VBO2);
    //
    //    glBindVertexArray(VAO2);
    //    //Create an array buffer to store our vertex positions
    //    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    //    glBufferData(GL_ARRAY_BUFFER,
    //        sizeof(GL_FLOAT) * attributes2.vertices.size(),
    //        &attributes2.vertices[0],
    //        GL_STATIC_DRAW);
    //
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    //    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    //        sizeof(GLuint) * mesh_indices2.size(),
    //        mesh_indices2.data(),
    //        GL_STATIC_DRAW);
    //
    //    glBindVertexArray(VAO2);
    //    /*glDrawElements(GL_TRIANGLES,
    //        ARRAY_COUNT(mesh_indices2.size()),
    //        GL_UNSIGNED_INT,
    //        0);*/
    //    glDrawArrays(GL_TRIANGLES, mesh_indices2.size(), 0);
    //}
};
//Class declaration for the model class
Model model;

class Camera {
public:
    //Camera variables
    float cameraPosX = 0;
    float cameraPosY = 0;
    float cameraPosZ = 3;

    float cameraFrontX = 0;
    float cameraFrontY = 0;
    float cameraFrontZ = -1;

    float cameraUpX = 0;
    float cameraUpY = 1;
    float cameraUpZ = 0;

    glm::vec3 direction;
    glm::mat4 projection;

    //POV
    bool setOrtho = false;
    bool setPers = true;
    float fov = 60;

    //Camera Position
    glm::vec3 cameraPos = glm::vec3(cameraPosX, cameraPosY, cameraPosZ);
    //Construct the position matrix using the eye/cam position
    glm::mat4 cameraPosMatrix = glm::translate(
        glm::mat4(1.0f), cameraPos * -1.0f);

    //up direction of the world
    glm::vec3 worldUp = glm::vec3(cameraUpX, cameraUpY, cameraUpZ);
    
    glm::vec3 cameraCenter = glm::vec3(0, 0.0f, 0);
    //Get the front
    glm::vec3 cameraFront = glm::vec3(cameraFrontX, cameraFrontY, cameraFrontZ);

    //get the forward
    glm::vec3 F = glm::normalize((cameraCenter - cameraPos));
    //get the right - F x world up
    glm::vec3 R = glm::cross(cameraFront, worldUp);
    //get the up - R x F
    glm::vec3 U = glm::cross(R, F);
    
};
//Class declaration for the camera class
Camera cam;

class Player {
public:
    //Player
    bool POVChange = true;

    //Position
    glm::mat4 transformation_matrix;

    //mouse
    float yaw = -90.0f; //mouse yawn
    float pitch = 0.0f; //mouse voice pitch jk
    float xoffset;
    float yoffset;

    float lastX = 300, lastY = 300;
    bool firstMouse = true;

    void PlayerPerspective(bool perspective, bool CameraPers) {

        if (perspective && CameraPers) {
            glfwSetCursorPosCallback(window, Mouse_Callback);
            glfwSetKeyCallback(window, ThirdPerson_Key_Callback);
        }
        else {
            
            glfwSetCursorPosCallback(window, NULL);
            glfwSetKeyCallback(window, FirstPerson_Key_Callback);
        }
    }
};
//Player declaration for the player class
Player player;

class Shader {
public:

    
};
//Class declaration for the shader class
Shader shader;

int main(void)
{
    //GLFWwindow* window;

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

    //path for player model
    //std::string path = "3D/Models/Tank/WW2_Tank_Germany_Panzer.obj";
    //Path for the barricade (currently unscaled)
    //std::string path = "3D/Models/Barricade/PoliceBarricade.obj";
    
    //Path for the tree
    std::string path = "3D/Models/Trees/Tree.obj";
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
        stbi_load("3D/Models/Trees/bark_0004.jpg", //texture path
            &img_width, //fills out the width
            &img_height, //fills out the height
            &colorChannels, //fills out the color channel
            0);

    //Load the normal map
    int img_width2, img_height2, colorChannel2;

    unsigned char* normal_bytes =
        stbi_load("3D/Models/Trees/DB2X2_L02_NRM.jpg", //texture path
            &img_width2, //fills out the width
            &img_height2, //fills out the height
            &colorChannel2, //fills out the color channel
            0);

    //Enable Blending | placed a top most for all layers
    glEnable(GL_BLEND);
    //Choose a blending function | source factor, destination factor | foreground, background layer
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA/*GL_SRC_COLOR*/);
    //Changes function to subtraction or inverses the alpha
    //glBlendEquation(GL_FUNC_SUBTRACT);
    
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
        GL_RGB, //target color format of the texture
        img_width, //texture width
        img_height, //texture height
        0,
        GL_RGB, //Color format of the texture
        GL_UNSIGNED_BYTE,
        tex_bytes); //loaded texture in bytes

    //generate the mipmaps to the current texture
    glGenerateMipmap(GL_TEXTURE_2D);
    //free up the loaded bytes
    stbi_image_free(tex_bytes);

    //Declare a Gluint for the normal texture
    GLuint norm_tex;
    //Generates a texture of the address
    glGenTextures(1, &norm_tex);
    //Use texture1 for normal since texture0 is being used (array)
    glActiveTexture(GL_TEXTURE1);
    //Tells opengl we're modifying norm_tex
    glBindTexture(GL_TEXTURE_2D, norm_tex);
    //Set the parameters to be the same as the diffuse color
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    //Load texture itself to norm_tex
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        img_width2,
        img_height2,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        normal_bytes
        );
    //Generate mipmaps of the normal map
    glGenerateMipmap(GL_TEXTURE_2D);
    //Cleanup
    stbi_image_free(normal_bytes);

    //Enable depth testing
    glEnable(GL_DEPTH_TEST);

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
    //Load the shader file into a string stream
    std::fstream sky_vertSrc("Shaders/skybox.vert");
    std::stringstream sky_vertBuff;
    //Adds the file stream to the string stream
    sky_vertBuff << sky_vertSrc.rdbuf();
    //Convert the stream to a char array
    std::string sky_vertS = sky_vertBuff.str();
    const char* sky_v = sky_vertS.c_str();

    //Load the shader file into a string stream
    std::fstream sky_fragSrc("Shaders/skybox.frag");
    std::stringstream sky_fragBuff;
    //Adds the file stream to the string stream
    sky_fragBuff << sky_fragSrc.rdbuf();
    //Convert the stream to a char array
    std::string sky_fragS = sky_fragBuff.str();
    const char* sky_f = sky_fragS.c_str();

    //Create a vertex shader for the skybox
    GLuint sky_vertShader = glCreateShader(GL_VERTEX_SHADER);
    //Assign the source to the vertex shader
    glShaderSource(sky_vertShader, 1, &sky_v, NULL);
    //Compile the vertex shader
    glCompileShader(sky_vertShader);

    //Create a fragment shader for the skybox
    GLuint sky_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    //Assign the source to the fragment shader
    glShaderSource(sky_fragShader, 1, &sky_f, NULL);
    //Compile the fragment shader
    glCompileShader(sky_fragShader);

    //Creates the skybox shader program
    GLuint skyboxProgram = glCreateProgram();
    //Attach the compiled skybox vertex shader
    glAttachShader(skyboxProgram, sky_vertShader);
    //Attach the compiled skybox fragment shader
    glAttachShader(skyboxProgram, sky_fragShader);

    //Finalize the compilation process
    glLinkProgram(skyboxProgram);
    //Cleanup
    glDeleteShader(sky_vertShader);
    glDeleteShader(sky_fragShader);
    //skybox shader ends here

    //directional shader
    //Load the shader file into a string stream
    std::fstream dl_vertSrc("Shaders/DirectionalLight.vert");
    std::stringstream dl_vertBuff;
    //Adds the file stream to the string stream
    dl_vertBuff << dl_vertSrc.rdbuf();
    //Convert the stream to a char array
    std::string dl_vertS = dl_vertBuff.str();
    const char* dl_v = dl_vertS.c_str();

    //Load the shader file into a string stream
    std::fstream dl_fragSrc("Shaders/DirectionalLight.frag");
    std::stringstream dl_fragBuff;
    //Adds the file stream to the string stream
    dl_fragBuff << dl_fragSrc.rdbuf();
    //Convert the stream to a char array
    std::string dl_fragS = dl_fragBuff.str();
    const char* dl_f = dl_fragS.c_str();

    //Create a vertex shader for the directional light
    GLuint dl_vertShader = glCreateShader(GL_VERTEX_SHADER);
    //Assign the source to the vertex shader
    glShaderSource(dl_vertShader, 1, &dl_v, NULL);
    //Compile the vertex shader
    glCompileShader(dl_vertShader);

    //Create a fragment shader for the directional light
    GLuint dl_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    //Assign the source to the fragment shader
    glShaderSource(dl_fragShader, 1, &dl_f, NULL);
    //Compile the fragment shader
    glCompileShader(dl_fragShader);

    //Creates the directional light shader program
    GLuint dlProgram = glCreateProgram();
    //Attach the compiled directional light vertex shader
    glAttachShader(dlProgram, dl_vertShader);
    //Attach the compiled directional light fragment shader
    glAttachShader(dlProgram, dl_fragShader);

    //Finalize the compilation process
    glLinkProgram(dlProgram);
    //Cleanup
    glDeleteShader(dl_vertShader);
    glDeleteShader(dl_fragShader);
    //directional shader ends here

    //point light shader
    //Load the shader file into a string stream
    std::fstream pl_vertSrc("Shaders/PointLight.vert");
    std::stringstream pl_vertBuff;
    //Adds the file stream to the string stream
    pl_vertBuff << pl_vertSrc.rdbuf();
    //Convert the stream to a char array
    std::string pl_vertS = pl_vertBuff.str();
    const char* pl_v = pl_vertS.c_str();

    //Load the shader file into a string stream
    std::fstream pl_fragSrc("Shaders/PointLight.frag");
    std::stringstream pl_fragBuff;
    //Adds the file stream to the string stream
    pl_fragBuff << pl_fragSrc.rdbuf();
    //Convert the stream to a char array
    std::string pl_fragS = pl_fragBuff.str();
    const char* pl_f = pl_fragS.c_str();

    //Create a vertex shader for the point light
    GLuint pl_vertShader = glCreateShader(GL_VERTEX_SHADER);
    //Assign the source to the vertex shader
    glShaderSource(pl_vertShader, 1, &pl_v, NULL);
    //Compile the vertex shader
    glCompileShader(pl_vertShader);

    //Create a fragment shader for the point light
    GLuint pl_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    //Assign the source to the fragment shader
    glShaderSource(pl_fragShader, 1, &pl_f, NULL);
    //Compile the fragment shader
    glCompileShader(pl_fragShader);

    //Creates the point light shader program
    GLuint plProgram = glCreateProgram();
    //Attach the compiled skybox vertex shader
    glAttachShader(plProgram, pl_vertShader);
    //Attach the compiled skybox fragment shader
    glAttachShader(plProgram, pl_fragShader);

    //Finalize the compilation process
    glLinkProgram(plProgram);
    //Cleanup
    glDeleteShader(pl_vertShader);
    glDeleteShader(pl_fragShader);
    //point light shader ends here

    std::vector<GLuint> mesh_indices;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        mesh_indices.push_back(
            shapes[0].mesh.indices[i].vertex_index
        );
    }

    //Vector to hold our tangets
    std::vector<glm::vec3> tangents;
    //Vector to hold our bitangents
    std::vector<glm::vec3> bitangents;

    //For loop that will go over all the vertices by 3
    for (int i = 0; i < shapes[0].mesh.indices.size(); i += 3) {
        //Get the 3 vertex data for the triangle
        tinyobj::index_t vData1 = shapes[0].mesh.indices[i];
        tinyobj::index_t vData2 = shapes[0].mesh.indices[i + 1];
        tinyobj::index_t vData3 = shapes[0].mesh.indices[i + 2];

        //Position of vertex 1
        glm::vec3 v1 = glm::vec3(
            attributes.vertices[vData1.vertex_index * 3],
            attributes.vertices[(vData1.vertex_index * 3) + 1],
            attributes.vertices[(vData1.vertex_index * 3) + 2]
            );
        //Position of vertex 2
        glm::vec3 v2 = glm::vec3(
            attributes.vertices[vData2.vertex_index * 3],
            attributes.vertices[(vData2.vertex_index * 3) + 1],
            attributes.vertices[(vData2.vertex_index * 3) + 2]
        );
        //Position of vertex 3
        glm::vec3 v3 = glm::vec3(
            attributes.vertices[vData3.vertex_index * 3],
            attributes.vertices[(vData3.vertex_index * 3) + 1],
            attributes.vertices[(vData3.vertex_index * 3) + 2]
        );

        //UV of vertex 1
        glm::vec2 uv1 = glm::vec2(
            attributes.texcoords[(vData1.texcoord_index * 2)],
            attributes.texcoords[(vData1.texcoord_index * 2) + 1]
            );
        //UV of vertex 2
        glm::vec2 uv2 = glm::vec2(
            attributes.texcoords[(vData2.texcoord_index * 2)],
            attributes.texcoords[(vData2.texcoord_index * 2) + 1]
        );
        //UV of vertex 3
        glm::vec2 uv3 = glm::vec2(
            attributes.texcoords[(vData3.texcoord_index * 2)],
            attributes.texcoords[(vData3.texcoord_index * 2) + 1]
        );

        //Edges of the triangle : position delta
        glm::vec3 deltaPos1 = v2 - v1;
        glm::vec3 deltaPos2 = v3 - v1;

        //UV delta
        glm::vec2 deltaUV1 = uv2 - uv1;
        glm::vec2 deltaUV2 = uv3 - uv1;

        float r = 1.0f / ((deltaUV1.x * deltaUV2.y) - (deltaUV1.y * deltaUV2.x));
        //Tangent (T)
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
        //Bitangent (B)
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

        //Push the tangent 3x for the 3 vertices of the triangle
        tangents.push_back(tangent);
        tangents.push_back(tangent);
        tangents.push_back(tangent);
        //Push the bitangent 3x for the 3 vertices of the triangle
        bitangents.push_back(tangent);
        bitangents.push_back(tangent);
        bitangents.push_back(tangent);
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

        //Push the tangent and bitangent to the vertex data
        fullVertexData.push_back(
            tangents[i].x //8 T.x
        );
        fullVertexData.push_back(
            tangents[i].y //9 T.y
        );
        fullVertexData.push_back(
            tangents[i].z //10 T.z
        );
        fullVertexData.push_back(
            bitangents[i].x //11 B.x
        );
        fullVertexData.push_back(
            bitangents[i].y //12 B.y
        );
        fullVertexData.push_back(
            bitangents[i].z //13 B.z
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

    //float skyboxVertices[] = {
    //     //positions          
    //    -1.0f,  1.0f, -1.0f,
    //    -1.0f, -1.0f, -1.0f,
    //     1.0f, -1.0f, -1.0f,
    //     1.0f, -1.0f, -1.0f,
    //     1.0f,  1.0f, -1.0f,
    //    -1.0f,  1.0f, -1.0f,

    //    -1.0f, -1.0f,  1.0f,
    //    -1.0f, -1.0f, -1.0f,
    //    -1.0f,  1.0f, -1.0f,
    //    -1.0f,  1.0f, -1.0f,
    //    -1.0f,  1.0f,  1.0f,
    //    -1.0f, -1.0f,  1.0f,

    //     1.0f, -1.0f, -1.0f,
    //     1.0f, -1.0f,  1.0f,
    //     1.0f,  1.0f,  1.0f,
    //     1.0f,  1.0f,  1.0f,
    //     1.0f,  1.0f, -1.0f,
    //     1.0f, -1.0f, -1.0f,

    //    -1.0f, -1.0f,  1.0f,
    //    -1.0f,  1.0f,  1.0f,
    //     1.0f,  1.0f,  1.0f,
    //     1.0f,  1.0f,  1.0f,
    //     1.0f, -1.0f,  1.0f,
    //    -1.0f, -1.0f,  1.0f,

    //    -1.0f,  1.0f, -1.0f,
    //     1.0f,  1.0f, -1.0f,
    //     1.0f,  1.0f,  1.0f,
    //     1.0f,  1.0f,  1.0f,
    //    -1.0f,  1.0f,  1.0f,
    //    -1.0f,  1.0f, -1.0f,

    //    -1.0f, -1.0f, -1.0f,
    //    -1.0f, -1.0f,  1.0f,
    //     1.0f, -1.0f, -1.0f,
    //     1.0f, -1.0f, -1.0f,
    //    -1.0f, -1.0f,  1.0f,
    //     1.0f, -1.0f,  1.0f
    //};

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

    //Treats the skybox as a standard 3d obj like b4
    //Create the VAO, VBO, and EBO
    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    //Generate the VAO of the skybox
    glGenVertexArrays(1, &skyboxVAO);
    //Generate the VBO of the skybox
    glGenBuffers(1, &skyboxVBO);
    //Generate the EBO of the skybox
    glGenBuffers(1, &skyboxEBO);

    //Work the the skybox VAO
    glBindVertexArray(skyboxVAO);
    //Work with the skybox VBO
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    //Add in the skybox vertices to the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    //Our vertices only take XYZ so only 3
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);

    //Work with the skybox EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    //Add in the skybox index array
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);

    //enable index 0 for position later in the shader
    glEnableVertexAttribArray(0);

    /*unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);*/


    //Faces of the skybox for easy loading
    std::string facesSkybox[]{
        "Skybox/rainbow_rt.png", //right
        "Skybox/rainbow_lf.png", //left
        "Skybox/rainbow_up.png", //up
        "Skybox/rainbow_dn.png", //down
        "Skybox/rainbow_ft.png", //front
        "Skybox/rainbow_bk.png" //back
        /*"Skybox/right.png",
        "Skybox/left.png",
        "Skybox/top.png",
        "Skybox/bottom.png",
        "Skybox/front.png",
        "Skybox/back.png"*/
    };
    
    std::vector<std::string> faces{
        "right.png",
        "left.png",
        "top.png",
        "bottom.png",
        "front.png",
        "back.png"
    };

    //SkyboxData skybox = LoadSkybox("Skybox", faces);

    //unsigned int cubemapTexture = loadCubemap(faces);
    /*unsigned int skyboxTex;
    glGenTextures(1, &skyboxTex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);

    int w, h, nrChannels;
    unsigned char* data;
    for (unsigned int i = 0; i < faces.size(); i++) {
        data = stbi_load(faces[i].c_str(), &w, &h, &nrChannels, 0);
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data
        );
    }*/

    //Skybox tex
    unsigned int skyboxTex;
    //Generate our skybox textures
    glGenTextures(1, &skyboxTex);
    //glActiveTexture(GL_TEXTURE0);
    //Initialize it as a cube map
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);

    //avoid pixelations worst case is blur
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //avoid tiling
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //Skybox from the class
    for (unsigned int i = 0; i < 6; i++) {
        //Declare the width, height and color channel of the our skybox textures
        int w, h, skyCChannel;
        //Temporarily disable flipping the image
        stbi_set_flip_vertically_on_load(false);
        //Load the image as usual
        unsigned char* data = stbi_load(
            facesSkybox[i].c_str(),
            &w,
            &h,
            &skyCChannel,
            0
        );
        //if loaded properly
        if (data) {
            glTexImage2D(
                //Cubemap face address start at positive_x (R)
                //increment it by 1
                //Right -> left -> top -> Bottom -> front -> back
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB, //png for GL_RGB
                w,
                h,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE, //Data type
                data //Texture data itself
            );
        }
        //Cleanup
        stbi_image_free(data);
    }
    
    ////My skybox that doesn't appear ;-; (even though same premise, couldn't figure out in time what was wrong)
    //std::string skyboxpath = "Skybox/cubemap.png";
    ////Declare the width, height and color channel of the our skybox textures
    //int w, h, nrChannel;
    ////Temporarily disable flipping the image
    //stbi_set_flip_vertically_on_load(false);
    ////Load the image as usual
    //unsigned char* data = stbi_load(
    //    skyboxpath.c_str(),
    //    &w,
    //    &h,
    //    &nrChannel,
    //    0
    //);

    //for (unsigned int i = 0; i < faces.size(); i++) {
    //    if (data) {
    //        glTexImage2D(
    //            //Cubemap face address start at positive_x (R)
    //            //increment it by 1
    //            //Right -> left -> top -> Bottom -> front -> back
    //            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
    //            0,
    //            GL_RGB,
    //            w,
    //            h,
    //            0,
    //            GL_RGB,
    //            GL_UNSIGNED_BYTE,
    //            data);
    //    }
    //}
    ////cleanup
    //stbi_image_free(data);
    
    //Reenable flipping the image
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
        14 * sizeof(GLfloat), //XYZ N(XYZ) UV T(XYZ) B(XYZ)
        (void*)0 //will be explain in the future
    );

    //this will enable index 0 above
    glEnableVertexAttribArray(0);

    GLintptr normPointer = 3 * sizeof(float);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        14 * sizeof(GLfloat), //XYZ N(XYZ) UV T(XYZ) B(XYZ)
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
        //XYZ N(XYZ) UV T(XYZ) B(XYZ)
        14 * sizeof(GLfloat),
        //add in the offset here
        (void*)uvPtr
    );

    //Tangent starts at index 8; Bitangent starts at index 11
    GLintptr tangentPtr = 8 * sizeof(float);
    GLintptr bitangentPtr = 11 * sizeof(float);

    glVertexAttribPointer(
        3, //3 = tangent
        3, //T(XYZ)
        GL_FLOAT, //data type of array
        GL_FALSE,
        //XYZ N(XYZ) UV T(XYZ) B(XYZ)
        14 * sizeof(GLfloat),
        //add in the offset here
        (void*)tangentPtr
    );

    glVertexAttribPointer(
        4, //4 = bitangent
        3, //B(XYZ)
        GL_FLOAT, //data type of array
        GL_FALSE,
        //XYZ N(XYZ) UV T(XYZ) B(XYZ)
        14 * sizeof(GLfloat),
        //add in the offset here
        (void*)bitangentPtr
    );

    //Enable 2 for out UV/tex coords
    glEnableVertexAttribArray(2);
    //Enable 4 & 3 for tangent and bitangent
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(3);

    //this tells opengl we're done with VBO & VAO and now EBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //float x_mod = 0;
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */       
        
        //Changes camera projection - orthographic or perspective
        if (cam.setOrtho) {
            cam.projection = glm::ortho(
                -1.0f, //-2.0f, //left moost point
                1.0f, //2.0f, //right most point
                -1.0f, //-2.0f, //bottom most point
                1.0f, //2.0f, //top most point
                0.1f, //z near
                1000.0f); //z far
        }
        else if(cam.setPers) {
            cam.projection = glm::perspective(
                glm::radians(cam.fov), //fov
                height / width, //aspect ratio / window height and width
                0.1f, //near
                1000.f //far
            );
        }

        //Get the player POV
        player.PlayerPerspective(player.POVChange, cam.setPers);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Position of light
        glm::vec3 lightPos = glm::vec3(cam.cameraPosX, cam.cameraPosY, cam.cameraPosZ);
        //Light color
        glm::vec3 lightColor = glm::vec3(1, 1, 1);

        //New look at function for fps i think
        glm::mat4 viewMatrix = glm::lookAt(cam.cameraPos, cam.cameraPos + cam.cameraFront, cam.U);

        //Use the directional light shaders
        glUseProgram(dlProgram);

        //Directional Light Variables
        float MDLdiffuse = 0;
        float MDLspecular = 1;

        glm::vec3 LDLdirection = glm::vec3(-0.2, -1.0, -0.3);
        //view pos of directional light
        glm::vec3 DLviewPos = cam.cameraPos;

        glm::vec3 LDLambient = glm::vec3(0.2, 0.2, 0.2);
        glm::vec3 LDLdiffuse = glm::vec3(0.5, 0.5, 0.5);
        glm::vec3 LDLspecular = glm::vec3(1.0, 1.0, 1.0);

        glm::mat4 DLview = glm::mat4(1.0f);
        DLview = glm::mat4(
            //Cast the same view matrix of the camera
            //turn it into a mat3 to remove translations
            glm::mat3(viewMatrix)
            //then convert it to a mat4
        );

        //Get position of model
        glm::mat4 DLmodel = player.transformation_matrix;

        //Directional light shaders
        //Directional light vertex
        unsigned int DLviewLoc = glGetUniformLocation(dlProgram, "view");
        glUniformMatrix4fv(DLviewLoc, //Address of the variable
            1, //How many we are modifying
            GL_FALSE,
            glm::value_ptr(DLview));

        unsigned int DLmodelLoc = glGetUniformLocation(dlProgram, "model");
        glUniformMatrix4fv(DLmodelLoc, //Address of the variable
            1, //How many we are modifying
            GL_FALSE,
            glm::value_ptr(DLmodel));

        unsigned int dlProjectionLoc = glGetUniformLocation(dlProgram, "projection");
        glUniformMatrix4fv(dlProjectionLoc, //Address of the variable
            1, //How many values we are modifying
            GL_FALSE,
            //Using same projection matrix as the camera
            glm::value_ptr(cam.projection));

        //Directional light fragment
        GLuint MDLdiffuseAddress = glGetUniformLocation(dlProgram, "MDLdiffuse");
        glUniform1f(MDLdiffuseAddress, MDLdiffuse);

        GLuint MDLspecularAddress = glGetUniformLocation(dlProgram, "MDLspecular");
        glUniform1f(MDLspecularAddress, MDLspecular);

        GLuint LDLdirectionAddress = glGetUniformLocation(dlProgram, "LDLdirection");
        glUniform3fv(LDLdirectionAddress, 1, glm::value_ptr(LDLdirection));

        GLuint DLviewAddress = glGetUniformLocation(dlProgram, "DLviewPos");
        glUniform3fv(DLviewAddress, 1, glm::value_ptr(DLviewPos));

        GLuint LDLambientAddress = glGetUniformLocation(dlProgram, "LDLambient");
        glUniform3fv(LDLambientAddress, 1, glm::value_ptr(LDLambient));

        GLuint LDLdiffuseAddress = glGetUniformLocation(dlProgram, "LDLdiffuse");
        glUniform3fv(LDLdiffuseAddress, 1, glm::value_ptr(LDLdiffuse));

        GLuint LDLspecularAddress = glGetUniformLocation(dlProgram, "LDLspecular");
        glUniform3fv(LDLspecularAddress, 1, glm::value_ptr(LDLspecular));
        //Directional light shaders ends here
        
        //Point light stuff
        glUseProgram(plProgram);

        //Directional Light Variables
        float PMLdiffuse = 0;
        float PMLspecular = 1;

        //glm::vec3 PLLposition = glm::vec3(-0.2, -1.0, -0.3);
        glm::vec3 PLLposition = lightPos;

        glm::vec3 PLLambient = glm::vec3(0.2f, 0.2f, 0.2f);
        glm::vec3 PLLdiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::vec3 PLLspecular = glm::vec3(1.0f, 1.0f, 1.0f);

        glm::vec3 PLviewPos = cam.cameraPos;

        glm::mat4 PLview = glm::mat4(1.0f);
        PLview = glm::mat4(
            //Cast the same view matrix of the camera
            //turn it into a mat3 to remove translations
            glm::mat3(viewMatrix)
            //then convert it to a mat4
        );

        //Get position of model
        glm::mat4 PLmodel = player.transformation_matrix;

        //Point light shaders
        //Point light vertex
        unsigned int PLviewLoc = glGetUniformLocation(plProgram, "view");
        glUniformMatrix4fv(PLviewLoc, //Address of the variable
            1, //How many we are modifying
            GL_FALSE,
            glm::value_ptr(PLview));

        unsigned int PLmodelLoc = glGetUniformLocation(plProgram, "model");
        glUniformMatrix4fv(PLmodelLoc, //Address of the variable
            1, //How many we are modifying
            GL_FALSE,
            glm::value_ptr(PLmodel));

        unsigned int plProjectionLoc = glGetUniformLocation(plProgram, "projection");
        glUniformMatrix4fv(plProjectionLoc, //Address of the variable
            1, //How many values we are modifying
            GL_FALSE,
            //Using same projection matrix as the camera
            glm::value_ptr(cam.projection));

        //Point light fragment
        GLuint PMLdiffuseAddress = glGetUniformLocation(plProgram, "PMLdiffuse");
        glUniform1f(PMLdiffuseAddress, PMLdiffuse);

        GLuint PMLspecularAddress = glGetUniformLocation(plProgram, "PMLspecular");
        glUniform1f(PMLspecularAddress, PMLspecular);

        GLuint PLLpositionAddress = glGetUniformLocation(plProgram, "PLLposition");
        glUniform3fv(PLLpositionAddress, 1, glm::value_ptr(PLLposition));

        GLuint PLLambientAddress = glGetUniformLocation(plProgram, "PLLambient");
        glUniform3fv(PLLambientAddress, 1, glm::value_ptr(PLLambient));

        GLuint PLLdiffuseAddress = glGetUniformLocation(plProgram, "PLLdiffuse");
        glUniform3fv(PLLdiffuseAddress, 1, glm::value_ptr(PLLdiffuse));

        GLuint PLLspecularAddress = glGetUniformLocation(plProgram, "PLLspecular");
        glUniform3fv(PLLspecularAddress, 1, glm::value_ptr(PLLspecular));

        GLuint PLviewAddress = glGetUniformLocation(plProgram, "PLviewPos");
        glUniform3fv(PLviewAddress, 1, glm::value_ptr(PLviewPos));
        //Point light shaders ends here

        //Disable the depth mask
        glDepthMask(GL_FALSE);
        //Change the depth funstion to <=
        glDepthFunc(GL_LEQUAL);
        //Cullface testing for skybox
        glCullFace(GL_FRONT);

        //Use the skybox shaders
        glUseProgram(skyboxProgram);
        //Initialize the skybox's view matrix
        glm::mat4 sky_view = glm::mat4(1.0f);
        sky_view = glm::mat4(
            //Cast the same view matrix of the camera
            //turn it into a mat3 to remove translations
            glm::mat3(viewMatrix)
            //then convert it to a mat4
        );

        //skybox projection
        unsigned int skyProjectionLoc = glGetUniformLocation(skyboxProgram, "projection");
        glUniformMatrix4fv(skyProjectionLoc, //Address of the variable
            1, //How many values we are modifying
            GL_FALSE, 
            //Using same projection matrix as the camera
            glm::value_ptr(cam.projection));

        //skybox view
        unsigned int skyViewLoc = glGetUniformLocation(skyboxProgram, "view");
        glUniformMatrix4fv(skyViewLoc, //Address of the variable
            1, //How many values we are modifying
            GL_FALSE, 
            glm::value_ptr(sky_view)); //View matrix

        //Bind the skybox VAO
        glBindVertexArray(skyboxVAO);
        //Set the texture index to use
        glActiveTexture(GL_TEXTURE0);
        //Bind our cubemap to the texture index
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);

        //Draw the skybox
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //Reset depth testing so true
        glDepthMask(GL_TRUE);
        //Reset the depth function to normal
        glDepthFunc(GL_LESS);
        glCullFace(GL_BACK);

        player.transformation_matrix = glm::translate(
            identity_matrix4,
            glm::vec3(x_mod, y_mod, z_mod)); //-1 to see the bunny in the projection matrix since 0 is on the camera itself
        
        player.transformation_matrix = glm::scale(
            player.transformation_matrix,
            glm::vec3(scale_x, scale_y, 1)
        );

        player.transformation_matrix = glm::rotate(
            player.transformation_matrix,
            glm::radians(theta_x),
            glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f))
        );

        player.transformation_matrix = glm::rotate(
            player.transformation_matrix,
            glm::radians(theta_y),
            glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))
        );

        //std::cout << theta << std::endl;

        glUseProgram(shaderProgram);

        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, //Address of the variable
            1, //How many we are modifying
            GL_FALSE,
            glm::value_ptr(viewMatrix));

        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, //Address of the variable
            1, //How many we are modifying
            GL_FALSE,
            glm::value_ptr(player.transformation_matrix));

        //Get the variable named projection from one of the shaders
        unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projLoc, //Address of the variable
            1, //How many we are modifying
            GL_FALSE,
            glm::value_ptr(cam.projection)); //Projection matrix

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

        //Tell we're modifying texture 0
        glActiveTexture(GL_TEXTURE0);
        //Get the address of tex0 in the shader
        GLuint tex0Loc = glGetUniformLocation(shaderProgram, "tex0");
        //Bind the brickwall texture to texture 0
        glBindTexture(GL_TEXTURE_2D, texture);
        //Pass texture 0 to the shader
        glUniform1i(tex0Loc, 0);

        //Tell we're modifying texture 1
        glActiveTexture(GL_TEXTURE1);
        //Get the address of norm_tex in the shader
        GLuint tex1Loc = glGetUniformLocation(shaderProgram, "norm_tex");
        //Bind the brickwall_normal texture to texture 1
        glBindTexture(GL_TEXTURE_2D, norm_tex);
        //Pass texture 1 to the shader
        glUniform1i(tex1Loc, 1);

        //since our vertex data has 5 float in it
        //we divide the array size by 5 to get the number of vertices

        glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 14);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        //Set the callback function to the window
        //glfwSetKeyCallback(window, Key_Callback);
    }

    //cleanup code
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

//Functions placed below for less scroll suffering while coding lol
//Mouse movement
void Mouse_Callback(
    GLFWwindow* window, 
    double xpos, 
    double ypos
)
{
    //Get the cursor position
    if (player.firstMouse) //Initially set to true
    {
        player.lastX = xpos;
        player.lastY = ypos;
        player.firstMouse = false;
    }

    //Calculate the offset movement between the last and current frame
    player.xoffset = xpos - player.lastX;
    player.yoffset = player.lastY - ypos; //reversed since y-coordinate range from bottom to top
    player.lastX = xpos;
    player.lastY = ypos;

    float sensitivity = 0.1f;
    player.xoffset *= sensitivity;
    player.yoffset *= sensitivity;

    //Add the offset values to the declared pitch and yaw values
    player.yaw += player.xoffset;
    player.pitch += player.yoffset;

    //Adds constraints so camera won't exceed the 89 degree mark
    if (player.pitch > 89.0f)
        player.pitch = 89.0f;
    if (player.pitch < -89.0f)
        player.pitch = -89.0f;

    //Calculate the actual direction vector
    cam.direction.x = cos(glm::radians(player.yaw)) * cos(glm::radians(player.pitch));
    cam.direction.y = sin(glm::radians(player.pitch));
    cam.direction.z = sin(glm::radians(player.yaw)) * cos(glm::radians(player.pitch));
    cam.cameraFront = glm::normalize(cam.direction);
}

//First person controls
void FirstPerson_Key_Callback(
    GLFWwindow* window,
    int key, //key code
    int scancode, //physical position in the keyboard
    int action, // press or release
    int mod //modifier keys - ctrl alt shift
)
{
    //Exit button
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }
    //Key to change from top down orthographic to perspective
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        cam.setPers = true;
        cam.setOrtho = false;
        //pers = true;
    }
    //Zoom in/out
    if (key == GLFW_KEY_Q) {
        cam.fov -= 1;
        if (cam.fov < 1.0f)
            cam.fov = 1.0f;
        if (cam.fov > 45.0f)
            cam.fov = 45.0f;
    }
    if (key == GLFW_KEY_E) {
        cam.fov += 1;
        if (cam.fov < 1.0f)
            cam.fov = 1.0f;
        if (cam.fov > 45.0f)
            cam.fov = 45.0f;
    }
    //Binocular movements
    if (key == GLFW_KEY_D) {
        cam.direction.x += 0.01;
        cam.cameraFront = glm::normalize(cam.direction);
    }
    if (key == GLFW_KEY_A) {
        cam.direction.x -= 0.01;
        cam.cameraFront = glm::normalize(cam.direction);
    }
    if (key == GLFW_KEY_W) {
        cam.direction.y += 0.01;
        cam.cameraFront = glm::normalize(cam.direction);
    }
    if (key == GLFW_KEY_S) {
        cam.direction.y -= 0.01;
        cam.cameraFront = glm::normalize(cam.direction);
    }
    //Key to change from first person to third person pov
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        player.POVChange = true;
    }
    
}

//Third person controls
void ThirdPerson_Key_Callback(
    GLFWwindow* window,
    int key, //key code
    int scancode, //physical position in the keyboard
    int action, // press or release
    int mod //modifier keys - ctrl alt shift
)
{
    //Value for camera speed
    float cameraSpeed = 0.05f * deltaTime;

    //Added for an exit button
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }
    //Key to change from perspective to top down orthographic
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        cam.setPers = false;
        cam.setOrtho = true;
    }
    //Player movements / move around the world
    if (key == GLFW_KEY_D) {
        cam.cameraPos += glm::normalize(cam.R) * cameraSpeed;
    }
    if (key == GLFW_KEY_A) {
        cam.cameraPos -= glm::normalize(cam.R) * cameraSpeed;
    }
    if (key == GLFW_KEY_W) {
        cam.cameraPos += cameraSpeed * cam.cameraFront;
    }
    if (key == GLFW_KEY_S) {
        cam.cameraPos -= cameraSpeed * cam.cameraFront;
    }
    //Key to change from 3rd person pov to 1st person pov
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        player.POVChange = false;
    }
    
}