
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "directionalLight.h"
#include "spotLight.h"
#include "cube.h"
#include "stb_image.h"
#include "cylinder.h"
#include "curve.h"

#include <iostream>

#include <ctime>

#define STB_IMAGE_IMPLEMENTATION
#pragma warning(disable:4996)
#include <unordered_map>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);


//object making functions

void shaderActivate(Shader& shader);


void Wall(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Ceil(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Wall_clock(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void oWall(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void oWall2(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void oWall3(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void oWall4(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
//void oWall5(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Floor(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void SideWall(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void SideWall2(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Showcase(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void ShowcaseRack(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
//void GlassDoor(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void FC1(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Logo(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Siri1(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void ServeWall(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);

void Table(Cube &cube,Shader& lightingShader, glm::mat4 alTogether);
void Sofa(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Bookself(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Bed(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Wardrobe(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Shokez(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void DiningTable(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Chair(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Grass(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void NormalCube(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
//void Clock(Cube& cube, Shader& lightingShader, glm::mat4 alTogether, Shader& lightingShaderWithTexture, Cube& cube, Shader& ourShader, Sphere& clock_bell, Cube& clock, Cube& x);
//void Clock(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void getCurrentTime(int& hours, int& minutes, int& seconds);

void curve(Shader& lightingShader, glm::mat4 alTogether);
void cylinder(Shader& lightingShader, glm::mat4 alTogether);



//ZAF 1
long long nCr(int n, int r);
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
unsigned int hollowBezier(GLfloat ctrlpoints[], int L);

int indx = 0;



// settings
const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 720;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;
float rotateAngle_XB = 0.0;
float rotateAngle_YB = 0.0;
float rotateAngle_ZB = 0.0;
float rotateXMatrixB = 0.0;
float rotateYMatrixB = 0.0;
float rotateZMatrixB = 0.0;



//ZAF 2
vector<float> cntrlPoints
{
-0.8000, 1.4500, 5.1000,
-0.8000, 1.3150, 5.1000,
-0.7750, 1.2050, 5.1000,
-0.7150, 1.1350, 5.1000,
-0.6400, 1.0500, 5.1000,
-0.5650, 0.9750, 5.1000,
-0.4550, 0.9400, 5.1000,
-0.3550, 0.9150, 5.1000,
-0.2800, 0.8950, 5.1000,
-0.2250, 0.8900, 5.1000,
-0.1700, 0.8850, 5.1000,
-0.0800, 0.8650, 5.1000,
-0.0500, 0.8600, 5.1000,
0.0450, 0.8550, 5.1000,
0.0150, 0.8850, 5.1000,
0.0750, 0.8800, 5.1000,
-0.7850, 1.4650, 5.1000,
-0.7550, 1.5000, 5.1000,
-0.7250, 1.5100, 5.1000,
-0.6800, 1.5150, 5.1000,
-0.6550, 1.5050, 5.1000,
-0.6350, 1.4550, 5.1000,
-0.6300, 1.4250, 5.1000,
-0.6200, 1.3900, 5.1000,
-0.6000, 1.3450, 5.1000,
-0.5650, 1.3050, 5.1000,
-0.5300, 1.2700, 5.1000,
-0.4900, 1.2450, 5.1000,
-0.4350, 1.2350, 5.1000,
-0.4000, 1.2200, 5.1000,
-0.3400, 1.2050, 5.1000,
-0.2750, 1.2000, 5.1000,
-0.2100, 1.2000, 5.1000,
-0.1500, 1.2000, 5.1000,
-0.1000, 1.1800, 5.1000,
-0.0350, 1.1750, 5.1000,
0.0400, 1.1750, 5.1000,
0.0900, 1.1750, 5.1000,
0.0900, 1.1750, 5.1000,
0.1200, 1.1750, 5.1000
};

vector<float> cntrlPointsT
{

-0.0439, 2.0085, 5.1000,
-0.0586, 1.9702, 5.1000,
-0.0820, 1.9234, 5.1000,
-0.0966, 1.8340, 5.1000,
-0.1171, 1.7362, 5.1000,
-0.1347, 1.6766, 5.1000,
-0.1347, 1.5787, 5.1000,
-0.1435, 1.5191, 5.1000,
-0.1874, 1.3872, 5.1000,
-0.2196, 1.3362, 5.1000,
-0.2548, 1.2511, 5.1000,
-0.2928, 1.1617, 5.1000,
-0.3309, 1.0894, 5.1000,
-0.3367, 1.0213, 5.1000,
-0.3397, 0.9404, 5.1000,
-0.3338, 0.9319, 5.1000,
-0.3016, 0.9149, 5.1000,
-0.2782, 0.9064, 5.1000,
-0.2372, 0.8979, 5.1000,
-0.1874, 0.8979, 5.1000,
-0.1640, 0.8851, 5.1000,
-0.1083, 0.8851, 5.1000,
-0.0820, 0.8851, 5.1000,
-0.0293, 0.8936, 5.1000,
-0.0088, 0.8894, 5.1000,
0.0176, 0.8894, 5.1000,

};

vector<float> cntrlPointsH
{
-0.2606, 1.8638, 5.1000,
-0.3485, 1.8000, 5.1000,
-0.3982, 1.6936, 5.1000,
-0.4041, 1.5574, 5.1000,
-0.3953, 1.4468, 5.1000,
-0.3660, 1.3404, 5.1000,
-0.2958, 1.2894, 5.1000,
-0.2255, 1.2638, 5.1000,
-0.1552, 1.2511, 5.1000,
-0.0673, 1.2426, 5.1000,
-0.2020, 1.8936, 5.1000,
-0.1376, 1.8936, 5.1000,
-0.0586, 1.8979, 5.1000,
-0.0117, 1.8681, 5.1000,
0.0000, 1.2511, 5.1000,
0.0351, 1.2766, 5.1000,
};

vector<float> cntrlPointsB
{
-0.2606, 1.8638, 5.1000,
-0.3485, 1.8000, 5.1000,
-0.3982, 1.6936, 5.1000,
-0.4041, 1.5574, 5.1000,
-0.3953, 1.4468, 5.1000,
-0.3660, 1.3404, 5.1000,
-0.2958, 1.2894, 5.1000,
-0.2255, 1.2638, 5.1000,
-0.1552, 1.2511, 5.1000,
-0.0673, 1.2426, 5.1000,
-0.2020, 1.8936, 5.1000,
-0.1376, 1.8936, 5.1000,
-0.0586, 1.8979, 5.1000,
-0.0117, 1.8681, 5.1000,
0.0000, 1.2511, 5.1000,
0.0351, 1.2766, 5.1000,
};

vector<float> cntrlPointsL
{
-0.1611, 1.8723, 5.1000,
-0.1640, 1.7319, 5.1000,
-0.1640, 1.6213, 5.1000,
-0.1698, 1.5447, 5.1000,
-0.1757, 1.4553, 5.1000,
-0.1757, 1.3660, 5.1000,
-0.1757, 1.2596, 5.1000,
-0.1581, 1.1660, 5.1000,
-0.1230, 1.1021, 5.1000,
-0.0878, 1.0553, 5.1000,
-0.0527, 1.0128, 5.1000,
-0.0205, 1.0043, 5.1000,
-0.1611, 1.9957, 5.1000,
-0.1669, 1.8213, 5.1000,
};




vector<float> cntrlPointsCylinder
{
-0.4500, 1.7950, 5.1000,
-0.4550, 1.4950, 5.1000,
-0.4550, 1.0000, 5.1000,
};




//alif
vector <float> coordinates;
vector <float> normals;
vector <int> indices;
vector <float> vertices;
class point
{
public:
    point()
    {
        x = 0;
        y = 0;
    }
    int x;
    int y;
} clkpt[2];
int mouseButtonFlag = 0;
FILE* fp;
const double pi = 3.14159265389;
const int nt = 40;
const int ntheta = 20;
bool showControlPoints = true;
bool loadBezierCurvePoints = false;
bool showHollowBezier = false;
bool lineMode = false;
unsigned int bezierVAO;
unsigned int bezierTree;
unsigned int bezierHead;
unsigned int bezierBody;
unsigned int bezierLeg;
unsigned int bezierCylinderVAO;

Camera camera(glm::vec3(26, 20.0f, 40.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
// lights
// positions of the point lights

glm::mat4 transform(float tr_x, float tr_y, float tr_z, float rot_x, float rot_y, float rot_z, float scal_x, float scal_y, float scal_z) {
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(tr_x, tr_y, tr_z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rot_x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rot_y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rot_z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scal_x, scal_y, scal_z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    return model;
}
glm::vec3 LightPositions[] = {
    /*glm::vec3(2 ,7 ,2),
    glm::vec3(23 ,7, 2),
    glm::vec3(2 ,7.0 ,23),
    glm::vec3(23 ,7.0 ,23)*/
    glm::vec3(-10 ,7 ,10),
    glm::vec3(10 ,7, 10),
    glm::vec3(-10 ,7 ,40),
    glm::vec3(65, 18, 50),
    glm::vec3(10 ,14 ,40),
    glm::vec3(-20 ,11 ,20),
    glm::vec3(-30 ,11, 30),
    glm::vec3(-40 ,11 ,40),
    glm::vec3(-50 ,11,50),
    glm::vec3(44.5, 14, 30.5)
};

DirLight dirlight(
    LightPositions[0].x, LightPositions[0].y, LightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 0.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
SpotLight spotlight1(
    LightPositions[1].x, LightPositions[1].y, LightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);

PointLight pointlight1(
    LightPositions[2].x, LightPositions[2].y, LightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    10.0f, 10.0f, 10.0f,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);

PointLight pointlight2(
    LightPositions[3].x, LightPositions[3].y, LightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    10.0f, 10.0f, 10.0f,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
SpotLight spotlight2(
    LightPositions[4].x, LightPositions[4].y, LightPositions[4].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight3(
    LightPositions[3].x, LightPositions[3].y, LightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    10.0f, 10.0f, 10.0f,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight4(
    LightPositions[3].x, LightPositions[3].y, LightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    10.0f, 10.0f, 10.0f,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight5(
    LightPositions[3].x, LightPositions[3].y, LightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    10.0f, 10.0f, 10.0f,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight6(
    LightPositions[3].x, LightPositions[3].y, LightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    10.0f, 10.0f, 10.0f,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight7(
    LightPositions[3].x, LightPositions[3].y, LightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    10.0f, 10.0f, 10.0f,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);



// light settings
bool pointLightOn1 = true;
bool pointLightOn2 = true;
bool pointLightOn3 = true;
bool pointLightOn4 = true;
bool pointLightOn5 = true;
bool pointLightOn6 = true;
bool pointLightOn7 = true;
bool dirLightOn = true;
bool spotLightOn1 = true;
bool spotLightOn2 = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;
bool emissionToggle = true;
bool openD = false;
bool fanS = false;
bool walk = false;

glm::mat4 projection;
glm::mat4 view;

int fanA = 30;
int walkA = 0, walkB = 0, walkC=0;

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    string diffuseMapPath = "container2.png";
    string specularMapPath = "container2_specular.png";
    string f_tiles = "tile.jpeg";
    string wood = "wood.jpeg";
    string self = "self.jpg";
    string sofa = "sofa.jpg";
    string sofa2 = "sofa2.jpg";
    string bed = "bed.jpg";
    string chair = "chair.jpg";
    string roof = "walls.jpg";
    string wall = "walls.jpg";
    string front_wall = "front_wall.jpg";
    string grass = "grass.jpg";
    string road = "road.jpg";
    string clock1 = "clock.png";
    string black = "black.jfif";
    string logo = "cf.png";
    string dorja = "dorja.jpg";


 vector<string> PoolIMG
  {
 "img/x (1).jpg",
"img/x (2).jpg",
"img/x (3).jpg",
"img/x (4).jpg",
"img/x (5).jpg",
"img/x (6).jpg",
"img/x (7).jpg",
"img/x (8).jpg",
"img/x (9).jpg",
"img/x (10).jpg",
"img/x (11).jpg",
"img/x (12).jpg",
"img/x (13).jpg",
"img/x (14).jpg",
"img/x (15).jpg",
"img/x (16).jpg",
"img/x (17).jpg",
"img/x (18).jpg",
"img/x (19).jpg",
"img/x (20).jpg",
"img/x (21).jpg",
"img/x (22).jpg",
"img/x (23).jpg",
"img/x (24).jpg",
"img/x (25).jpg",
"img/x (26).jpg",
"img/x (27).jpg",
"img/x (28).jpg",
"img/x (29).jpg",
"img/x (30).jpg",
"img/x (31).jpg",
"img/x (32).jpg",
"img/x (33).jpg",
"img/x (34).jpg",
"img/x (35).jpg",
"img/x (36).jpg",
"img/x (37).jpg",
"img/x (38).jpg",
"img/x (39).jpg",
"img/x (40).jpg",
"img/x (41).jpg",
"img/x (42).jpg",
"img/x (43).jpg",
"img/x (44).jpg",
"img/x (45).jpg",
"img/x (46).jpg",
"img/x (47).jpg",
"img/x (48).jpg",
"img/x (49).jpg",
"img/x (50).jpg",
 };

    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int floor_tiles = loadTexture(f_tiles.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int wood_tex = loadTexture(wood.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int self_tex = loadTexture(self.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int sofa_tex = loadTexture(sofa.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int sofa2_tex = loadTexture(sofa2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int bed_tex = loadTexture(bed.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int chair_tex = loadTexture(chair.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int roof_tex = loadTexture(roof.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int wall_tex = loadTexture(wall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int front_wall_tex = loadTexture(front_wall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int grass_tex = loadTexture(grass.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int road_tex = loadTexture(road.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int clock_tex = loadTexture(clock1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int black_tex = loadTexture(black.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int logo_tex = loadTexture(logo.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int dorja_tex = loadTexture(dorja.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
   
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
   //Cube wall = Cube(glm::vec3(0.95294117647f, 0.93333333333f, 0.91764705882f), glm::vec3(0.95294117647, 0.93333333333, 0.91764705882), glm::vec3(0.95294117647, 0.93333333333, 0.91764705882), 32.0f, 1.0f);
    Cube tiles_cube = Cube(floor_tiles, floor_tiles, 32.0, 0.0f, 0.0f, 5.0f, 5.0f);
    Cube roof_cube = Cube(roof_tex, roof_tex, 32.0, 0.0f, 0.0f, 20.0f, 20.0f);
    Cube front_wall_cube = Cube(front_wall_tex, front_wall_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    /*Cube grass_cube = Cube(grass_tex, grass_tex, 32.0, 0.0f, 0.0f, 5.0f, 5.0f);*/
    //0.95294117647, 0.93333333333, 0.91764705882
    Cube glassDoor = Cube(glm::vec3(0.391f, 0.391f, 0.432f), glm::vec3(0.391f, 0.391f, 0.432f), glm::vec3(0.391f, 0.391f, 0.432f), 32, 0.9f);
    Cube basin = Cube(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.1f, 0.1f, 0.1f), 32, 0.3f);
    Cube clock_cube = Cube(clock_tex, clock_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    //Cube basin = Cube(glm::vec3(0.20392156863f, 0.34117647059f, 0.83529411765f), glm::vec3(0.20392156863f, 0.34117647059f, 0.83529411765f), glm::vec3(0.20392156863f, 0.34117647059f, 0.83529411765f), 32, 0.9f);
    CurveObj curve1 = CurveObj(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f,1.0f), glm::vec4(0.1f, 0.1f, 0.1f,1.0f));
    
       


    //ZAF 3
   //bazierVAO
    bezierVAO = hollowBezier(cntrlPoints.data(), ((unsigned int)cntrlPoints.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    bezierCylinderVAO = hollowBezier(cntrlPointsCylinder.data(), ((unsigned int)cntrlPointsCylinder.size() / 3) - 1);

    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierTree = hollowBezier(cntrlPointsT.data(), ((unsigned int)cntrlPointsT.size() / 3) - 1);

    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierHead = hollowBezier(cntrlPointsH.data(), ((unsigned int)cntrlPointsH.size() / 3) - 1);

    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierBody = hollowBezier(cntrlPointsB.data(), ((unsigned int)cntrlPointsB.size() / 3) - 1);

    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierLeg = hollowBezier(cntrlPointsL.data(), ((unsigned int)cntrlPointsL.size() / 3) - 1);
    


    //draw a cylilnder ends
    //Cube wall_cube = Cube(wall_tex, wall_tex, 32.0, 0.0f, 0.0f, 20.0f, 10.0f);
    //Sphere sphere = Sphere();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    //Cylinder cylinder = Cylinder(1.0f, 36, 18, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);

    // All the faces of the cubemap (make sure they are in this exact order)
    /*std::string facesCubemap[6] =
    {
        sky + "/sky.png",
        parentDir + "/Resources/YoutubeOpenGL 19 - Cubemaps & Skyboxes/skybox/left.jpg",
        parentDir + "/Resources/YoutubeOpenGL 19 - Cubemaps & Skyboxes/skybox/top.jpg",
        parentDir + "/Resources/YoutubeOpenGL 19 - Cubemaps & Skyboxes/skybox/bottom.jpg",
        parentDir + "/Resources/YoutubeOpenGL 19 - Cubemaps & Skyboxes/skybox/front.jpg",
        parentDir + "/Resources/YoutubeOpenGL 19 - Cubemaps & Skyboxes/skybox/back.jpg"
    };*/

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 200.0f);
        lightingShaderWithTexture.setMat4("projection", projection);
        
        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShaderWithTexture.setMat4("view", view);
       

        pointlight1.setUpPointLight(lightingShaderWithTexture);
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        pointlight4.setUpPointLight(lightingShaderWithTexture);
        pointlight5.setUpPointLight(lightingShaderWithTexture);
        pointlight6.setUpPointLight(lightingShaderWithTexture);
        pointlight7.setUpPointLight(lightingShaderWithTexture);
        dirlight.setUpPointLight(lightingShaderWithTexture);
        spotlight1.setUpPointLight(lightingShaderWithTexture);
        spotlight2.setUpPointLight(lightingShaderWithTexture);

        //// Modelling Transformation
        //glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(2.42, 0.11, 8.18f));
        //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix;
        
        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model,translate2;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix ;

        ///*float rotateAngle_XB = 78.0, rotateAngle_YB = 0.0, rotateAngle_ZB = -90.0;*/
        //glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixB, rotateXMatrixB, rotateYMatrixB, rotateZMatrixB, scaleMatrixB, modelForCurve;
        //translateMatrixB = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
        //rotateXMatrixB = glm::rotate(identityMatrix, glm::radians(rotateAngle_XB), glm::vec3(1.0f, 0.0f, 0.0f));
        //rotateYMatrixB = glm::rotate(identityMatrix, glm::radians(rotateAngle_YB), glm::vec3(0.0f, 1.0f, 0.0f));
        //rotateZMatrixB = glm::rotate(identityMatrix, glm::radians(rotateAngle_ZB), glm::vec3(0.0f, 0.0f, 1.0f));
        //scaleMatrixB = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        //modelForCurve = alTogether * translateMatrixB * rotateXMatrixB * rotateYMatrixB * rotateZMatrixB * scaleMatrixB;
      
        if (openD)
        {
            
            model = transform(17, 0.5, 28, rotateAngle_X, -90, rotateAngle_Z, -8.825, 14, 1);
            cube.setTextureProperty(dorja_tex, dorja_tex, 32.0f);
            shaderActivate(lightingShader);
            NormalCube(cube, lightingShader, model);
            model = transform(8.15, 0.5, 28, rotateAngle_X, 90, rotateAngle_Z, 8.825, 14, 1);
            cube.setTextureProperty(dorja_tex, dorja_tex, 32.0f);
            shaderActivate(lightingShader);
            NormalCube(cube, lightingShader, model);

        }
        else
        {
            model = transform(17, 0.5, 28, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -8.825, 14, 1);
            cube.setTextureProperty(dorja_tex, dorja_tex, 32.0f);
            shaderActivate(lightingShader);
            NormalCube(cube, lightingShader, model);
            model = transform(8.15, 0.5, 28, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 8.825, 14, 1);
            cube.setTextureProperty(dorja_tex, dorja_tex, 32.0f);
            shaderActivate(lightingShader);
            NormalCube(cube, lightingShader, model);
        }

        

        ////ZAF 4
        ////draw a cylinder
        //glm :: mat4 identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        //translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5, 2, 20));
        //rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        //rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        //rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        //scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3, 2.5, 3));
        //modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        //lightingShader.setMat4("model", modelforCurve);

        //lightingShader.use();
        //lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
        //lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
        //lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        //lightingShader.setFloat("material.shininess", 32.0f);
        //glBindVertexArray(bezierCylinderVAO);
        //glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        //glBindVertexArray(0);

        



        //Table 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10, 1.35, 4));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 1.35, 4));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10, 1.35, 8));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 1.35, 8));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10, 1.35, 12));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 1.35, 12));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10, 1.35, 12));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 1.35, 12));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10, 1.35, 16));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 1.35, 16));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10, 1.35, 16));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 1.35, 16));
        Table(cube, lightingShaderWithTexture, translateMatrix);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10, 1.35, 20));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 1.35, 20));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10, 1.35, 20));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 1.35, 20));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10, 1.35, 24));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 1.35, 24));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10, 1.35, 24));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 1.35, 24));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10, 1.35, 28));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 1.35, 28));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10, 1.35, 28));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 1.35, 28));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10, 1.35, 4));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        /*translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 1.35, 4));
        Table(cube, lightingShaderWithTexture, translateMatrix);*/

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10, 1.35, 8));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 1.35, 8));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5, 1.35, 12));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 1.35, 12));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5, 1.35, 12));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 1.35, 12));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5, 1.35, 16));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 1.35, 16));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5, 1.35, 16));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 1.35, 16));
        Table(cube, lightingShaderWithTexture, translateMatrix);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5, 1.35, 20));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 1.35, 20));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5, 1.35, 20));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 1.35, 20));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5, 1.35, 24));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 1.35, 24));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5, 1.35, 24));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 1.35, 24));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5, 1.35, 28));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 1.35, 28));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5, 1.35, 28));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 1.35, 28));
        Table(cube, lightingShaderWithTexture, translateMatrix);



        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5, 1.35, 4));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        /*translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 1.35, 4));
        Table(cube, lightingShaderWithTexture, translateMatrix);*/

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5, 1.35, 8));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        /*translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 1.35, 8));
        Table(cube, lightingShaderWithTexture, translateMatrix);*/



        //Chair 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(55, 0.9, 31.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(60, 0.9, 31.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(65, 0.9, 31.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(70, 0.9, 31.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(55, 0.9, 35.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(60, 0.9, 35.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(65, 0.9, 35.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(70, 0.9, 35.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(55, 0.9, 39.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(60, 0.9, 39.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(65, 0.9, 39.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(70, 0.9, 39.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        
        translateMatrix = glm::translate(identityMatrix, glm::vec3(55, 0.9, 43.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(60, 0.9, 43.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(65, 0.9, 43.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(70, 0.9, 43.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);



        //Table 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(55, 1.35, 32));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(60, 1.35, 32));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(65, 1.35, 32));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(70, 1.35, 32));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(55, 1.35, 36));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(60, 1.35, 36));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(65, 1.35, 36));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(70, 1.35, 36));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(55, 1.35, 40));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(60, 1.35, 40));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(65, 1.35, 40));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(70, 1.35, 40));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(55, 1.35, 44));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(60, 1.35, 44));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(65, 1.35, 44));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(70, 1.35, 44));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(55, 1.35, 48));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(60, 1.35, 48));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(65, 1.35, 48));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(70, 1.35, 48));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, 1.35, 4));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(15, 1.35, 4));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, 1.35, 8));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(15, 1.35, 8));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, 1.35, 12));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(15, 1.35, 12));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, 1.35, 12));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(15, 1.35, 12));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, 1.35, 16));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(15, 1.35, 16));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, 1.35, 16));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(15, 1.35, 16));
        Table(cube, lightingShaderWithTexture, translateMatrix);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, 1.35, 20));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(15, 1.35, 20));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, 1.35, 20));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(15, 1.35, 20));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, 1.35, 4));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        /*translateMatrix = glm::translate(identityMatrix, glm::vec3(15, 1.35, 4));
        Table(cube, lightingShaderWithTexture, translateMatrix);*/

        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, 1.35, 8));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(15, 1.35, 8));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5, 1.35, 12));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(20, 1.35, 12));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5, 1.35, 12));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(20, 1.35, 12));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5, 1.35, 16));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(20, 1.35, 16));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5, 1.35, 16));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(20, 1.35, 16));
        Table(cube, lightingShaderWithTexture, translateMatrix);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(5, 1.35, 20));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(20, 1.35, 20));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5, 1.35, 20));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(20, 1.35, 20));
        Table(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5, 1.35, 4));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        /*translateMatrix = glm::translate(identityMatrix, glm::vec3(20, 1.35, 4));
        Table(cube, lightingShaderWithTexture, translateMatrix);*/

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5, 1.35, 8));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        /*translateMatrix = glm::translate(identityMatrix, glm::vec3(20, 1.35, 8));
        Table(cube, lightingShaderWithTexture, translateMatrix);*/
        

        /*translateMatrix = glm::translate(identityMatrix, glm::vec3(, 1.35, 20));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube, lightingShaderWithTexture, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(20, 1.35, 20));
        Table(cube, lightingShaderWithTexture, translateMatrix);*/



        //Chair 2
        for (int i = 0; i <= 16; i++)
        {
            for (float j = 0; j <27 ; j++)

            {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(-20 + i, 0.9, 3.5 + j));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
                cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
                Chair(cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);
                
                model = transform(-19.5 + i, 0.9, 6 + j, rotateAngle_X, 180, rotateAngle_Z, 1, 1, 1);
                cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
                Chair(cube, lightingShaderWithTexture, model);
                j = j + 3;

            }
            i=i+4;

        }

        for (int i = 0; i <= 10; i++)
        {
            for (float j = 0; j < 6; j++)

            {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(5 + i, 0.9, 3.5+j));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
                cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
                Chair(cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);
            

                model = transform(5.5 + i, 0.9, 6 + j, rotateAngle_X, 180, rotateAngle_Z, 1, 1, 1);
                cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
                Chair(cube, lightingShaderWithTexture, model);
                j = j + 3;
            }
            i = i + 4;
        }

        for (int i = 0; i <= 15; i++)
        {
            for (float j = 0; j < 12; j++)

            {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(5 + i, 0.9, 11.5+j));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
                cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
                Chair(cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);

                model = transform(5.5 + i, 0.9, 14 + j, rotateAngle_X, 180, rotateAngle_Z, 1, 1, 1);
                cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
                Chair(cube, lightingShaderWithTexture, model);
                j = j + 3;
            }
            i = i + 4;
        }

        for (int i = 0; i <= 16; i++)
        {
            for (int j = 0; j <= 27; j++)
            {

                model = transform(-21.1 + i, 0.9, 5+j, rotateAngle_X, 90, rotateAngle_Z, 1, 1, 1);
                cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
                Chair(cube, lightingShaderWithTexture, model);
                model = transform(-18.5 + i, 0.9, 4.5 + j, rotateAngle_X, 270, rotateAngle_Z, 1, 1, 1);
                cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
                Chair(cube, lightingShaderWithTexture, model);
                j = j + 3;
            }

            
            i = i + 4;
        }

        for (int i = 0; i <= 12; i++)
        {
            for (int j = 0; j <= 16; j++)
            {
                model = transform(3.9 + i, 0.9, 5+j, rotateAngle_X, 90, rotateAngle_Z, 1, 1, 1);
                cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
                Chair(cube, lightingShaderWithTexture, model);
                j = j + 3;
            }
            i = i + 4;
        }
        for (int j = 0; j <=12; j++)
        {
            model = transform(18.9, 0.9, 13 + j, rotateAngle_X, 90, rotateAngle_Z, 1, 1, 1);
            cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
            Chair(cube, lightingShaderWithTexture, model);
            model = transform(21.5, 0.9, 12.5 + j, rotateAngle_X, 270, rotateAngle_Z, 1, 1, 1);
            cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
            Chair(cube, lightingShaderWithTexture, model);
            j = j + 3;
        }
        /*for (int i = 0; i <= 16; i++)
        {
            model = transform(-21.1 + i, 0.9, 5, rotateAngle_X, 90, rotateAngle_Z, 1, 1, 1);
            cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
            Chair(cube, lightingShaderWithTexture, model);

            model = transform(-21.1 + i, 0.9, 9, rotateAngle_X, 90, rotateAngle_Z, 1, 1, 1);
            cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
            Chair(cube, lightingShaderWithTexture, model);

            model = transform(-21.1 + i, 0.9, 13, rotateAngle_X, 90, rotateAngle_Z, 1, 1, 1);
            cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
            Chair(cube, lightingShaderWithTexture, model);

            model = transform(-21.1 + i, 0.9, 17, rotateAngle_X, 90, rotateAngle_Z, 1, 1, 1);
            cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
            Chair(cube, lightingShaderWithTexture, model);

            model = transform(-21.1 + i, 0.9, 21, rotateAngle_X, 90, rotateAngle_Z, 1, 1, 1);
            cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
            Chair(cube, lightingShaderWithTexture, model);

            model = transform(-21.1 + i, 0.9, 25, rotateAngle_X, 90, rotateAngle_Z, 1, 1, 1);
            cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
            Chair(cube, lightingShaderWithTexture, model);
            model = transform(-21.1 + i, 0.9, 29, rotateAngle_X, 90, rotateAngle_Z, 1, 1, 1);
            cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
            Chair(cube, lightingShaderWithTexture, model);
            i = i + 4;
        }*/
        /*

        model = transform(-4.5, 0.9, 6, rotateAngle_X, 180, rotateAngle_Z, 1, 1, 1);
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, model);

        model = transform(-3.4, 0.9, 4.5, rotateAngle_X, -90, rotateAngle_Z, 1, 1, 1);
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Chair(cube, lightingShaderWithTexture, model);*/

        //Floor

        //Floor 1st
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, -1.5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2, 4, 1));
        Floor(tiles_cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);

        //Floor 
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-50, -1.5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 4, 1.25));
        Floor(tiles_cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Floor 
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-25, -1.5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 4, 1.25));
        Floor(tiles_cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Floor 
        translateMatrix = glm::translate(identityMatrix, glm::vec3(50, -1.5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 4, 1));
        Floor(tiles_cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Floor 
        translateMatrix = glm::translate(identityMatrix, glm::vec3(45, -1.5, 28));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(60, 4, 55));
        Wall(tiles_cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);



        //Ceil 1st
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 8.5, -15));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 1, 86));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Ceil(cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);

        //Ceil 2nd
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-25, 8.5, -15));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 1, 100));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Ceil(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Ceil 3rd
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-50, 8.5, -15));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(50,1, 100));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Ceil(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Ceil 4th
        translateMatrix = glm::translate(identityMatrix, glm::vec3(25, 8.5, -15));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 1, 86));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Ceil(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Ceil 5th
        translateMatrix = glm::translate(identityMatrix, glm::vec3(50, 8.5, -15));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 1, 86));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Ceil(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        
        //Ceil 6th
        translateMatrix = glm::translate(identityMatrix, glm::vec3(45, 8.5, 28));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(60, 1, 56));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Ceil(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Ceil 7th
        translateMatrix = glm::translate(identityMatrix, glm::vec3(75, 8.5, -70));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-20, 1, 110));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //FAN
        //1 st
        //model = transform(5.5 + i, 0.9, 6 + j, rotateAngle_X, 180, rotateAngle_Z, 1, 1, 1);
        //cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        //Chair(cube, lightingShaderWithTexture, model);
         //ghorir kata
        //model = transform(6.2, 6.1, .9, 0, 0, 0, 0.4, 0.4, 0.2);
        //cube.setTextureProperty(black_tex, black_tex, 32.0f);
        //NormalCube(cube, lightingShaderWithTexture, model);
        ////second
        //float rudian = (-(seconds - 30) * 6.0f);
        //model = transform(6.25, 6.2, 1, rotateAngle_X, rotateAngle_Y, rudian, 0.1, -1.7, 0.1);
        //cube.setTextureProperty(black_tex, black_tex, 32.0f);
        //NormalCube(cube, lightingShaderWithTexture, model);        // minutes
        //rudian = -(minutes * 60 + seconds - 30) * 0.1f + 180.0f;
        //model = transform(6.25, 6.2, 1, rotateAngle_X, rotateAngle_Y, rudian, 0.1, -1.4, 0.1);
        //cube.setTextureProperty(black_tex, black_tex, 32.0f);
        //NormalCube(cube, lightingShaderWithTexture, model);
        //// hours
        //rudian = -(hours * 3600 + minutes * 60 + seconds - 30) * (1.0f / 120.0f);
        //model = transform(6.25, 6.2, 1, rotateAngle_X, rotateAngle_Y, rudian, 0.1, -1.1, 0.1);
        //cube.setTextureProperty(black_tex, black_tex, 32.0f);
        //NormalCube(cube, lightingShaderWithTexture, model);

        for (int i = 0; i < 25; i++)
        {
            for(int j=0; j<15;j++)
            {
                model = transform(10 - i, 8.5, 10+j, rotateAngle_X, rotateAxis_Y, rotateAngle_Z, .25, -2, .25);
                cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
                NormalCube(cube, lightingShaderWithTexture, model);

                model = transform(9.5 - i, 7.5, 9.5+j, rotateAngle_X, rotateAxis_Y, rotateAngle_Z, 2, -.5, 2);
                cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
                NormalCube(cube, lightingShaderWithTexture, model);

                model = transform(10 - i, 7.25, 10+j, rotateAngle_X, rotateAxis_Y + fanA, rotateAngle_Z, 5, .25, 1);
                cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
                NormalCube(cube, lightingShaderWithTexture, model);

                model = transform(10 - i, 7.25, 10+j, rotateAngle_X, 120 + fanA, rotateAngle_Z, 5, .25, 1);
                cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
                NormalCube(cube, lightingShaderWithTexture, model);

                model = transform(10 - i, 7.25, 10+j, rotateAngle_X, -120 + fanA, rotateAngle_Z, 5, .25, 1);
                cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
                NormalCube(cube, lightingShaderWithTexture, model);

                j += 5;
            }
            
            i += 5;
        }
        model = transform(-0.25 , 12, 0, rotateAngle_X, rotateAxis_Y, rotateAngle_Z, 2, 1, 1);
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, model);
        model = transform(-0.25, 12, -0.25, rotateAngle_X, rotateAxis_Y, rotateAngle_Z, 2, -2, 2);
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, model);
        

        //angle
        if (fanS) {
            fanA += 10;
            fanA = fanA % 370;
        }

       
        //0 room
        //front wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-50, 0.5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 17, 1));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //left wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-50, .5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1.25));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        SideWall2(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Basin 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-49.5, .5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(6, 6, 34));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Basin 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-49.5, .5, 17));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(6, 6, 36));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //out wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-50, -0.15, 35));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.75, 1.35, 1));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        oWall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //border
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-50, 0.5, 17));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 17, 1));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        

        //1st room
        //front wall 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, .5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(20, 17, 1));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);

        //front wall 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(25, .5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-20, 17, 1));
        //cube.setTextureProperty(front_wall_tex, front_wall_tex, 32.0f);
        Wall_clock(front_wall_cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Road 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, 9, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10, -3, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);


        //2nd room
        //front wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-25, 0.5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 17, 1));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //left wall 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-25, .5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 17, 26));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //left wall up
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-25, 9, 17.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, -5, 8));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //left wall up
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-25, 9, 17.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, -5, -9));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //left wall 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-25, .5, 35));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 17, -27));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);

        //out wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-24, -1.5, 35));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 21, 1.25));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);

        //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.25, 9, 35));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.75, -0.33, 1));
        ////cube.setTextureProperty(front_wall_tex, front_wall_tex, 32.0f);
        //oWall(front_wall_cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //out wall2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, -0.15, 28));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25, 1.35, 1));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        oWall2(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //out wall3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, -0.15, 28));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 1.35, 30));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        oWall3(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //out wall4
        translateMatrix = glm::translate(identityMatrix, glm::vec3(25, -1.5, 28));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-16, 21, 1));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);



        

        

        //3rd Room
        //front wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(25, 0.5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 17, 1));
        //cube.setTextureProperty(front_wall_tex, front_wall_tex, 32.0f);
        Wall(front_wall_cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //out wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(25, -1.5, 28));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(40, 21, 1)); 
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //ServeWall (down 1)
        translateMatrix = glm::translate(identityMatrix, glm::vec3(25, 0, 0.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5, 6, 15));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        ServeWall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //ServeWall (down 1)
        translateMatrix = glm::translate(identityMatrix, glm::vec3(25, 0, 28));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5, 6, -30));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        ServeWall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //ServeWall (up)
        translateMatrix = glm::translate(identityMatrix, glm::vec3(25, 9, 0.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, -6, 55));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        ServeWall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //4th Room
        //front wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(50, 0.5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 17, 1));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //out wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(50, 0.5, 28));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 17, 1));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //right wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(75, -1.5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 21, 57));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        
        //LeftWall 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(50, 0, 0.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 18, 15));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //LeftWall 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(50, 0, 28));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 18, -30));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //5th room

        //right wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(75, -1.5, 28));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 21, 55));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //left wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(45, -1.5, 28));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-1, 21, 55));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //out wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(44.5, -1.5, 55.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(62, 21, 1));
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //right counter1 showcase
        translateMatrix = glm::translate(identityMatrix, glm::vec3(25, 3, 2.375));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        ShowcaseRack(cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);
      

        //FC1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        FC1(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Logom
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(logo_tex, logo_tex, 32.0f);
        Logo(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Siri1 
        translateMatrix = glm::translate(identityMatrix, glm::vec3(8.15, -1.5, 28));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(17, 1.33, 9));
        Siri1(tiles_cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Siri1 
        translateMatrix = glm::translate(identityMatrix, glm::vec3(8.15, -1.0, 28));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(17, 1.33, 6));
        Siri1(tiles_cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        //Siri1 
        translateMatrix = glm::translate(identityMatrix, glm::vec3(8.15, -0.5, 28));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(17, 1.33, 3));
        Siri1(tiles_cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Siri1(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        //Siri2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, .5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 0.67));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Siri1(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        //Siri3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, .5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 3));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Siri1(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //right counter2 showcase
        translateMatrix = glm::translate(identityMatrix, glm::vec3(50, 3, 25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-1, 1, -1));
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Showcase(cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);

        //Grass
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-100, -2, -70));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(400, 1, 800));
        roof_cube.setTextureProperty(grass_tex, grass_tex, 32.0f);
        Grass(roof_cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Road 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-100, -1.5, 60));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(400, 1, 30));
        cube.setTextureProperty(road_tex, road_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Road 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(8, -1.5, 32));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(18, 1, 56));
        cube.setTextureProperty(road_tex, road_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Mukto Road
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-50, -1.5, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(250, 4, -30));
        cube.setTextureProperty(road_tex, road_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Mukto Moncho base
        translateMatrix = glm::translate(identityMatrix, glm::vec3(55, -1.5, -50));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-25, 8, 45));
        cube.setTextureProperty(road_tex, road_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Mukto Moncho dewal
        translateMatrix = glm::translate(identityMatrix, glm::vec3(55, 2.5, -50));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-1, 22, 45));
        cube.setTextureProperty(road_tex, road_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //Road 3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(75,-1.5, -70));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-20, 4, 110));
        cube.setTextureProperty(road_tex, road_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        ////Pool
        ////right wall
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(75, 9, 28));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 21, 55));
        //cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        //Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        ////left wall
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(45, 9, 28));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(-1, 21, 55));
        //cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        //Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        ////out wall
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(44.5, 9, 55.5));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(62, 21, 1));
        //cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        //Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        ////in wall
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(44.5, 9, 28));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(62, 21, 1));
        //cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        //Wall(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        //translateMatrix = glm::translate(identityMatrix, glm::vec3(45, 16.5, 28));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(60, .1, 56));
        //unsigned int water_tex = loadTexture(PoolIMG[indx].c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
        //indx++;
        //indx %= PoolIMG.size();
        //cube.setTextureProperty(water_tex, water_tex, 32.0f);
        //Ceil(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);


        ////ZAF 4
        //draw curve
        glm::mat4 identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-48, 2.5, 3)); 
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1, 1.25, 2));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        curve(lightingShader, modelforCurve);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        int bb = 0;
        for (int i = 0; i < 5; i++)
        {
            glm::mat4 identityMatrixCurveT = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            glm::mat4 translateMatrixCurveT, rotateXMatrixCurveT, rotateYMatrixCurveT, rotateZMatrixCurveT, scaleMatrixCurveT, modelforCurveT;
            translateMatrixCurveT = glm::translate(identityMatrixCurveT, glm::vec3((-50+bb), -2.5, 45));
            rotateXMatrixCurveT = glm::rotate(identityMatrixCurveT, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
            rotateYMatrixCurveT = glm::rotate(identityMatrixCurveT, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
            rotateZMatrixCurveT = glm::rotate(identityMatrixCurveT, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
            scaleMatrixCurveT = glm::scale(identityMatrixCurveT, glm::vec3(8, 4, 8));
            modelforCurveT = translateMatrixCurveT * rotateXMatrixCurveT * rotateYMatrixCurveT * rotateZMatrixCurveT * scaleMatrixCurveT;
            lightingShaderWithTexture.setMat4("model", modelforCurveT);
            curve(lightingShaderWithTexture, modelforCurveT);
            /*curve(lightingShaderWithTexture, modelforCurveT);
            curve.setTextureProperty(road_tex, road_tex, 32.0f);*/



            glBindVertexArray(bezierTree);
            glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
            glBindVertexArray(0);

            //kando
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-50+ bb, -5.5, 45));
            rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
            rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 4, 1));
            model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
            lightingShader.setMat4("model", model);
            cylinder(lightingShader, model);
            glBindVertexArray(bezierCylinderVAO);
            glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
            glBindVertexArray(0);


            bb += 10;
        }

        // my robot
        //Head
        //glm::mat4 identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(walkA, 8.5+walkC, 7+walkB));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1, 1.5, 1));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        curve(lightingShader, modelforCurve);
        glBindVertexArray(bezierHead);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        

        //Leg 1
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-0.5+walkA, 14.5 + walkC, 7 + walkB));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.5, -4, 0.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        curve(lightingShader, modelforCurve);
        glBindVertexArray(bezierBody);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //Leg 2
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(.50 + walkA, 14.5 + walkC, 7 + walkB));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.5, -4, 0.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        curve(lightingShader, modelforCurve);
        glBindVertexArray(bezierBody);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //Hand
        float rotateAngle_Xh = 0.0, rotateAngle_Yh = 0.0, rotateAngle_Zh = -30.0;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(2.250 + walkA, 15 + walkC, 7 + walkB));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Xh), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Yh), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Zh), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.5, -4, 0.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        curve(lightingShader, modelforCurve);
        glBindVertexArray(bezierBody);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //Hand2
        float rotateAngle_Xh1 = 0.0, rotateAngle_Yh1 = 0.0, rotateAngle_Zh1 = 30.0;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-2.250 + walkA, 15 + walkC, 7 + walkB));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Xh1), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Yh1), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Zh1), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.5, -4, 0.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        curve(lightingShader, modelforCurve);
        glBindVertexArray(bezierBody);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //Body
        float rotateAngle_X = 180.0, rotateAngle_Y = 0.0, rotateAngle_Z = 0.0;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(00 + walkA, 16 + walkC, 7 + walkB));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 180.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 4, 2));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        curve(lightingShader, modelforCurve);
        glBindVertexArray(bezierBody);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //angle
        if (walk) {
            walk += 10;
            walk = walk % 370;
        }
        //walkA++;

        /*glm::mat4 identityMatrix = glm::mat4(1.0f);*/ // make sure to initialize matrix to identity matrix first
        /*glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, translate2;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;*/
      
        //basin base
        /*model = transform(-48, 3.5, 3, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.25, 2);
        cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);*/

        //three basins
        int aa = 0;
        for (int i = 0; i <=7 ; i++) {
            float rotateAngle_X = 0.0, rotateAngle_Y = 0.0, rotateAngle_Z = 0.0;
            /*model = transform(-48, 3.5, aa, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.25, 2);
            cube.setTextureProperty(wood_tex, wood_tex, 32.0f);
            NormalCube(cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);*/
            translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-48, 2.5, 3+aa));
            rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
            rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
            rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
            scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1, 1.25, 2));
            modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
            lightingShader.setMat4("model", modelforCurve);
            curve(lightingShader, modelforCurve);
            glBindVertexArray(bezierVAO);
            glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
            glBindVertexArray(0);

            aa += 4;
        }




        ////draw a cylinder
        //identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        ////glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        //translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5, 2, 20));
        //rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        //rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        //rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        //scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3, 2.5, 3));
        //modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        //lightingShader.setMat4("model", modelforCurve);


        
        
        ///*glDisable(GL_DEPTH_TEST);*/
        /*glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        model = transform(17, 0.5, 28, rotateAngle_X, rotateAngle_Y, rotateAngle_Z,-8.825, 14, 1);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(8.15, 0.5, 28, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 8.825, 14, 1);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        glDisable(GL_BLEND);*/
        ///*glEnable(GL_DEPTH_TEST); */

        
        //my clock
        //black base
        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.75, 4.75, 0.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(6, 6, 0.5));
        cube.setTextureProperty(road_tex, road_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5, 5, 0.74));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5, 5, 0.5));
        cube.setTextureProperty(clock_tex, clock_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);

        int hours, minutes, seconds;
        getCurrentTime(hours, minutes, seconds);
        hours = (hours + 6) % 12;
        //ghorir kata
        model = transform(6.2, 6.1, .9, 0, 0, 0, 0.4, 0.4, 0.2);
        cube.setTextureProperty(black_tex, black_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, model);
        //second
        float rudian = (-(seconds - 30) * 6.0f);
        model = transform(6.25, 6.2, 1, rotateAngle_X, rotateAngle_Y, rudian, 0.1, -1.7, 0.1);
        cube.setTextureProperty(black_tex, black_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, model);        // minutes
        rudian = -(minutes * 60 + seconds - 30) * 0.1f + 180.0f;
        model = transform(6.25, 6.2, 1, rotateAngle_X, rotateAngle_Y, rudian, 0.1, -1.4, 0.1);
        cube.setTextureProperty(black_tex, black_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, model);
        // hours
        rudian = -(hours * 3600 + minutes * 60 + seconds - 30) * (1.0f / 120.0f);
        model = transform(6.25, 6.2, 1, rotateAngle_X, rotateAngle_Y, rudian, 0.1, -1.1, 0.1);
        cube.setTextureProperty(black_tex, black_tex, 32.0f);
        NormalCube(cube, lightingShaderWithTexture, model);
        

        lightingShader.use();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);
        
        pointlight1.setUpPointLight(lightingShader);
        pointlight2.setUpPointLight(lightingShader);
        pointlight3.setUpPointLight(lightingShader);
        pointlight4.setUpPointLight(lightingShader);
        pointlight5.setUpPointLight(lightingShader);
        pointlight6.setUpPointLight(lightingShader);
        pointlight7.setUpPointLight(lightingShader);
        dirlight.setUpPointLight(lightingShader);
        spotlight1.setUpPointLight(lightingShader);
        spotlight2.setUpPointLight(lightingShader);

        

        glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.065, 4.86783));
        
        //Table(cube, lightingShader, translateMatrix);


        
        

        // also draw the lamp object(s)
        
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        glm::vec3 LightColor[] = {
        glm::vec3(0.8f, 0.8f, 0.8f),// White - Dir
        glm::vec3(1.0f,  0.0f,  0.0f),//Red - Spot Light
        glm::vec3(0.0f,  1.0f,  0.0f),//Green - Point Light 1
        glm::vec3(0.0f,  0.0f,  1.0f)//Blue - Point Light 1
        };

        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, LightPositions[i]);
            model = glm::scale(model, glm::vec3(0.5f)); // Make it a smaller cube
            cube.drawCube(ourShader, model);
        }
        
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();


    }
    /*cout << translate_X << " ," << translate_Y << " ," << translate_Z << endl;*/
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_RIGHT, deltaTime);
    }

    /*if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }*/
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        walkB--;
        
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        walkB++;
        
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        walkA++;
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        walkA--;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        walkC++;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        walkC--;
    }
    

}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (dirLightOn)
        {
            dirlight.turnOff();
            dirLightOn = !dirLightOn;
        }
        else
        {
            dirlight.turnOn();
            dirLightOn = !dirLightOn;
        }
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (pointLightOn1)
        {
            pointlight1.turnOff();
            pointLightOn1 = !pointLightOn1;
        }
        else
        {
            pointlight1.turnOn();
            pointLightOn1 = !pointLightOn1;
        }
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (pointLightOn2)
        {
            pointlight2.turnOff();
            pointLightOn2 = !pointLightOn2;
        }
        else
        {
            pointlight2.turnOn();
            pointLightOn2 = !pointLightOn2;
        }
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (pointLightOn3)
        {
            pointlight3.turnOff();
            pointLightOn3 = !pointLightOn3;
        }
        else
        {
            pointlight3.turnOn();
            pointLightOn3 = !pointLightOn3;
        }
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (pointLightOn4)
        {
            pointlight4.turnOff();
            pointLightOn4 = !pointLightOn4;
        }
        else
        {
            pointlight4.turnOn();
            pointLightOn4 = !pointLightOn4;
        }
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (pointLightOn5)
        {
            pointlight5.turnOff();
            pointLightOn5 = !pointLightOn5;
        }
        else
        {
            pointlight5.turnOn();
            pointLightOn5 = !pointLightOn5;
        }
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (pointLightOn6)
        {
            pointlight6.turnOff();
            pointLightOn6 = !pointLightOn6;
        }
        else
        {
            pointlight6.turnOn();
            pointLightOn6 = !pointLightOn6;
        }
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (pointLightOn7)
        {
            pointlight7.turnOff();
            pointLightOn7 = !pointLightOn7;
        }
        else
        {
            pointlight7.turnOn();
            pointLightOn7 = !pointLightOn7;
        }
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        if (spotLightOn1 && spotLightOn2)
        {
            spotlight1.turnOff();
            spotLightOn1 = !spotLightOn1;
            spotlight2.turnOff();
            spotLightOn2 = !spotLightOn2;
        }
        else
        {
            spotlight1.turnOn();
            spotLightOn1 = !spotLightOn1;
            spotlight2.turnOn();
            spotLightOn2 = !spotLightOn2;
        }
    }
    if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        if (openD)
        {
            openD = !openD;
        }
        else
        {   
            openD = !openD;      
        }
    }
    if (key == GLFW_KEY_0 && action == GLFW_PRESS)
    {
        if (fanS)
        {
            fanS = !fanS;
        }
        else
        {
            fanS = !fanS;
        }
    }
    if (key == GLFW_KEY_G && action == GLFW_PRESS)
    {
        if (walk)
        {
            walk = !walk;
        }
        else
        {
            walk = !walk;
        }
    }
    /*if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        if (ambientToggle)
        {
            if (pointLightOn1)
                pointlight1.turnAmbientOff();
            if (pointLightOn2)
                pointlight2.turnAmbientOff();
            spotlight.turnAmbientOff();
            if (dirLightOn)
                dirlight.turnAmbientOff();
            ambientToggle = !ambientToggle;
        }
        else
        {
            if (pointLightOn1)
                pointlight1.turnAmbientOn();
            if (pointLightOn2)
                pointlight2.turnAmbientOn();
            if (spotLightOn)
                spotlight.turnAmbientOn();
            if (dirLightOn)
                dirlight.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
    }
    if (key == GLFW_KEY_6 && action == GLFW_PRESS)
    {
        if (diffuseToggle)
        {
            if (pointLightOn1)
                pointlight1.turnDiffuseOff();
            if (pointLightOn2)
                pointlight2.turnDiffuseOff();
            if (dirLightOn)
                dirlight.turnDiffuseOff();
            if (spotLightOn)
                spotlight.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {
            if (pointLightOn1)
                pointlight1.turnDiffuseOn();
            if (pointLightOn2)
                pointlight2.turnDiffuseOn();
            if (dirLightOn)
                dirlight.turnDiffuseOn();
            if (spotLightOn)
                spotlight.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }
    }
    if (key == GLFW_KEY_7 && action == GLFW_PRESS)
    {
        if (specularToggle)
        {
            if (pointLightOn1)
                pointlight1.turnSpecularOff();
            if (pointLightOn2)
                pointlight2.turnSpecularOff();
            if (dirLightOn)
                dirlight.turnSpecularOff();
            if (spotLightOn)
                spotlight.turnSpecularOff();
            specularToggle = !specularToggle;
        }
        else
        {
            if (pointLightOn1)
                pointlight1.turnSpecularOn();
            if (pointLightOn2)
                pointlight2.turnSpecularOn();
            if (dirLightOn)
                dirlight.turnSpecularOn();
            if (spotLightOn)
                spotlight.turnSpecularOn();
            specularToggle = !specularToggle;
        }
    }*/
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}





//Flood Drawing
void Floor(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 1.0f, 56));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}
void Ceil(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}
void Siri1(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1.0f, 1));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}
void Wall(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}
void Wall_clock(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}

void Grass(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}
void oWall(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, -0.075, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(70, 16, 1));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}
void oWall2(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, -0.075, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5, 16, 1));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}

void oWall4(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, -0.075, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-5, 16, 1));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}

void oWall5(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}


void oWall3(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, -0.075, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(10, 16, .475));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}
void Wall2(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-50, 16, 1));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}

void SideWall(Cube& cube, Shader& lightingShader, glm::mat4 alTogether) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 16, 50));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}

void SideWall2(Cube& cube, Shader& lightingShader, glm::mat4 alTogether) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 17, 56));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}
void ServeWall(Cube& cube, Shader& lightingShader, glm::mat4 alTogether) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}

void Table(Cube &cube, Shader& lightingShader, glm::mat4 alTogether)
{
    //cube.setMaterialisticProperty(glm::vec3(0.862f, 0.46f, 0.321f));
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2f, -0.2f, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 0.2f, 3.0f));
    model = scaleMatrix * translateMatrix;
    cube.drawCubeWithTexture(lightingShader, alTogether * model);


    glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-0.6f, 0.0f, -0.1f));
    rotateXMatrix1 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix1 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix1 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix1 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model1 = rotateXMatrix1 * translateMatrix1 * scaleMatrix1;
    cube.drawCubeWithTexture(lightingShader, alTogether * model1);

    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.8f, 0.0f, -0.1f));
    rotateXMatrix2 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix2 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix2 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix2 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    model2 = rotateXMatrix2 * translateMatrix2 * scaleMatrix2;
    cube.drawCubeWithTexture(lightingShader, alTogether * model2);

    glm::mat4 translateMatrix3, rotateXMatrix3, rotateYMatrix3, rotateZMatrix3, scaleMatrix3, model3;
    translateMatrix3 = glm::translate(identityMatrix, glm::vec3(0.8f, 0.0f, -1.49f));
    rotateXMatrix3 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix3 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix3 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model3 = rotateXMatrix3 * translateMatrix3 * scaleMatrix3;
    cube.drawCubeWithTexture(lightingShader, alTogether * model3);
    // Modelling Transformation
    glm::mat4 translateMatrix4, rotateXMatrix4, rotateYMatrix4, rotateZMatrix4, scaleMatrix4, model4;
    translateMatrix4 = glm::translate(identityMatrix, glm::vec3(-0.6f, 0.0f, -1.49f));
    rotateXMatrix4 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix4 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    model4 = rotateXMatrix4 * translateMatrix4 * scaleMatrix4;
    cube.drawCubeWithTexture(lightingShader, alTogether * model4);
}
//void Bed(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
//{
//    float baseHeight = 0.3;
//    float width = 1;
//    float length = 2;
//    float pillowWidth = 0.3;
//    float pillowLength = 0.15;
//    float blanketWidth = 0.8;
//    float blanketLength = 0.7;
//    float headHeight = 0.6;
//
//    //base
//    glm::mat4 model = glm::mat4(1.0f);
//    glm::mat4 translate = glm::mat4(1.0f);
//    glm::mat4 translate2 = glm::mat4(1.0f);
//    glm::mat4 scale = glm::mat4(1.0f);
//    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
//    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
//    model = alTogether * translate * scale;
//    cube.setMaterialisticProperty(glm::vec3(0.545, 0.271, 0.075),32);
//    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
//
//    //foam
//    model = glm::mat4(1.0f);
//    translate = glm::mat4(1.0f);
//    translate2 = glm::mat4(1.0f);
//    scale = glm::mat4(1.0f);
//    translate2 = glm::translate(model, glm::vec3(0, baseHeight / 2, 0));
//    scale = glm::scale(model, glm::vec3(width, 0.06, length));
//    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
//    model = alTogether * translate2 * translate * scale;
//    cube.setMaterialisticProperty(glm::vec3(0.804, 0.361, 0.361));
//    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
//
//    //head
//    model = glm::mat4(1.0f);
//    translate = glm::mat4(1.0f);
//    translate2 = glm::mat4(1.0f);
//    scale = glm::mat4(1.0f);
//    translate2 = glm::translate(model, glm::vec3(0, 0, (length / 2 - 0.02 / 2) + 0.02));
//    scale = glm::scale(model, glm::vec3(width, headHeight*1.2, 0.2));
//    translate = glm::translate(model, glm::vec3(-0.489272, -0.00849999, -1.51654));
//    model = alTogether * translate2 * translate * scale;
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//}
//void Wardrobe(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
//{
//    //WARDROBE 
//        //back
//    glm::mat4 translateMatrix, scaleMatrix, model;
//    model = transform(6.95, -0.75, -8.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 7.0f, 4.0f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //left
//    model = transform(5.95, -0.75, -8.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, 7.0f, 0.1f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//
//    //right
//    model = transform(5.95, -0.75, -6.55, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, 7.0f, 0.1f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //upper
//    model = transform(5.95, 2.75, -8.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.1f, .1f, 4.0f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //.5 down
//    model = transform(5.95, -0.5 - 0.025, -8.5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //WARDROBE front self
//    model = transform(5.95, -0.5 + 0.025, -8.5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 6.45f, 3.8f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //WARDROBE front self border
//    model = transform(5.95 - 0.01, -0.5 + 0.025, -7.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 6.45f, 0.02f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//}
//void Shokez(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
//{
//
//    glm::mat4 translateMatrix, scaleMatrix, model;
//    model = transform(6.95, -0.75, .5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 7.0f, 4.0f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //left
//    model = transform(5.95, -0.75, .5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, 7.0f, 0.1f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //right
//    model = transform(5.95, -0.75, 2.45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, 7.0f, 0.1f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//    //upper
//    model = transform(5.95, 2.75, .5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.1f, .1f, 4.0f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//
//    //3
//    model = transform(5.95, 0.75 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //.5
//    model = transform(5.95, -0.5 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //front self
//    model = transform(5.95, -0.5 + 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 2.4f, 3.8f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //front self border
//    model = transform(5.95 - 0.01, -0.5 + 0.025, 1.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 2.4f, 0.02f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //4
//    model = transform(5.95, 1.25 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //5
//    model = transform(5.95, 1.75 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//
//    //6 
//    model = transform(5.95, 2.25 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.8f, .1f, 3.8f);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//    //bokself end
//
//
//}
void DiningTable(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2f, 0, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 0.3f, 3.0f));
    model = scaleMatrix * translateMatrix;
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2f, 2.52, -0.025));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.5f, 0.05f, 3.5f));
    model = scaleMatrix * translateMatrix;
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //ourShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-0.6f, 0.0f, -0.1f));
    rotateXMatrix1 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix1 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix1 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix1 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model1 = rotateXMatrix1 * translateMatrix1 * scaleMatrix1;
    cube.drawCubeWithTexture(lightingShader, alTogether * model1);

    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.8f, 0.0f, -0.1f));
    rotateXMatrix2 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix2 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix2 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix2 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    model2 = rotateXMatrix2 * translateMatrix2 * scaleMatrix2;
    cube.drawCubeWithTexture(lightingShader, alTogether * model2);

    glm::mat4 translateMatrix3, rotateXMatrix3, rotateYMatrix3, rotateZMatrix3, scaleMatrix3, model3;
    translateMatrix3 = glm::translate(identityMatrix, glm::vec3(0.8f, 0.0f, -1.49f));
    rotateXMatrix3 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix3 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix3 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model3 = rotateXMatrix3 * translateMatrix3 * scaleMatrix3;
    cube.drawCubeWithTexture(lightingShader, alTogether * model3);
    // Modelling Transformation
    glm::mat4 translateMatrix4, rotateXMatrix4, rotateYMatrix4, rotateZMatrix4, scaleMatrix4, model4;
    translateMatrix4 = glm::translate(identityMatrix, glm::vec3(-0.6f, 0.0f, -1.49f));
    rotateXMatrix4 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix4 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    model4 = rotateXMatrix4 * translateMatrix4 * scaleMatrix4;
    cube.drawCubeWithTexture(lightingShader, alTogether * model4);
}
//void Chair(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
//{
//
//    //Seat
//    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
//    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.22, -1.0, 0.05));//
//    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.1f, 1.0f));
//    alTogether = rotateYMatrix * alTogether;
//    model = scaleMatrix * translateMatrix;
//    cube.setMaterialisticProperty(glm::vec3(0.804, 0.361, 0.361));
//    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
//
//    //Back
//    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.22, 0.15f, 0.5f));
//    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.7f, 0.1f));
//    model = scaleMatrix * translateMatrix;
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
//    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-0.2f, 0.1, -0.1f));
//    rotateXMatrix1 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//    scaleMatrix1 = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
//    model1 = rotateXMatrix1 * translateMatrix1 * scaleMatrix1;
//    cube.setMaterialisticProperty(glm::vec3(0.804, 0.361, 0.361));
//    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model1);
//
//    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
//    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-0.2f, 0.1, -0.5f));
//    rotateXMatrix2 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//    scaleMatrix2 = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
//    model2 = rotateXMatrix2 * translateMatrix2 * scaleMatrix2;
//    cube.setMaterialisticProperty(glm::vec3(0.804, 0.361, 0.361));
//    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model2);
//
//    // Modelling Transformation
//    glm::mat4 identityMatrix3 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 translateMatrix3, rotateXMatrix3, rotateYMatrix3, rotateZMatrix3, scaleMatrix3, model3;
//    translateMatrix3 = glm::translate(identityMatrix, glm::vec3(0.2f, 0.1, -0.1f));
//    rotateXMatrix3 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//    scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
//    model3 = rotateXMatrix3 * translateMatrix3 * scaleMatrix3;
//    cube.setMaterialisticProperty(glm::vec3(0.804, 0.361, 0.361));
//    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model3);
//
//    // Modelling Transformation
//
//    glm::mat4 translateMatrix4, rotateXMatrix4, rotateYMatrix4, rotateZMatrix4, scaleMatrix4, model4;
//    translateMatrix4 = glm::translate(identityMatrix, glm::vec3(0.2f, 0.1, -0.5f));
//    rotateXMatrix4 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//    scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
//    model4 = rotateXMatrix4 * translateMatrix4 * scaleMatrix4;
//    cube.setMaterialisticProperty(glm::vec3(0.804, 0.361, 0.361));
//    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model4);
//
//    translateMatrix4 = glm::translate(identityMatrix, glm::vec3(-0.2f, -0.1f, 0.05f));
//    scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.1f, 0.5f, 0.1f));
//    model4 = translateMatrix4 * scaleMatrix4;
//    cube.setMaterialisticProperty(glm::vec3(0.804, 0.361, 0.361));
//    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model4);
//
//    translateMatrix4 = glm::translate(identityMatrix, glm::vec3(0.2f, -0.1f, 0.05f));
//    scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.1f, 0.5f, 0.1f));
//    model4 = translateMatrix4 * scaleMatrix4;
//    cube.setMaterialisticProperty(glm::vec3(0.804, 0.361, 0.361));
//    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model4);
//
//}
void FWall(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;
    lightingShader.setMat4("model", alTogether * model);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}

//void Shokez(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
//{
//    //pichoner base
//    glm::mat4 translateMatrix, scaleMatrix, model;
//    model = transform(0, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 6, 15);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //left border
//    model = transform(0, 0, 7.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 6, -0.3);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //upper border
//    model = transform(0, 3, 7.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 0.3, -15);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //lower border
//    model = transform(0, 0, 7.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, -0.3, -15);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //Right border
//    model = transform(0, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 6, 0.3);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //middle border
//    model = transform(0, 0, 2.6, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 6, -0.3);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //middle rack
//    model = transform(0, 1.5, 7.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 0.3, -9.8);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//
//    //Samner palla
//    model = transform(2, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 6, 5.2);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    //pallar handle
//    model = transform(2.05, 1.35, 1.9, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 1, 0.2);
//    cube.drawCube(lightingShader, alTogether * model, 0, 0, 0);
//}
void Showcase(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    //pichoner base
    glm::mat4 translateMatrix, scaleMatrix, model;
    model = transform(0, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 6, 15);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //left border
    model = transform(0, 0, 7.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 6, -0.3);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //upper border
    model = transform(0, 3, 7.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 0.3, -15);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //lower border
    model = transform(0, 0, 7.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, -0.3, -15);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //Right border
    model = transform(0, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 6, 0.3);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //middle border
    model = transform(0, 0, 2.6, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 6, -0.3);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //middle rack
    model = transform(0, 1.5, 7.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 0.3, -9.8);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);


    //Samner palla
    model = transform(2, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 6, 5.2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //pallar handle
    model = transform(2.05, 1.35, 1.9, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 1, 0.2);
    cube.drawCube(lightingShader, alTogether * model, 0, 0, 0);
}
void ShowcaseRack(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    //pichoner base
    glm::mat4 translateMatrix, scaleMatrix, model;
    model = transform(3, 0, -1.875, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 7.5, 6, 0.5);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //left border
    model = transform(6.75, 0, -1.875, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -0.3, 6, 2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //upper border
    model = transform(6.75, 3, -1.875, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -7.5, 0.3, 2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //lower border
    model = transform(6.75, 0, -1.875, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -7.5, -0.3, 2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //Right border
    model = transform(3, 0, -1.875, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.3, 6, 2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    
    //middle border
    model = transform(5, 0, -1.875, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -0.3, 6, 2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    

    //middle rack
    model = transform(6.75, 1.5, -1.875, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -7.5, 0.3, 2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //border
    model = transform(1.5, 0.00001, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 15, -5, 0.5);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    model = transform(1.5, 0.00001, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.5, -5, -3);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    model = transform(9, 0.00001, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -0.5, -5, -5.75);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}
//void ServeWall(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
//{
//    //nicher border
//    glm::mat4 translateMatrix, scaleMatrix, model;
//    model = transform(25, 0, 0.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 6, 55);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//
//    
//}
void FC1(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    //nicher border
    glm::mat4 translateMatrix, scaleMatrix, model;
    model = transform(8, 7, 28, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 18, 4, 0.5);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}
void Logo(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    //nicher border
    glm::mat4 translateMatrix, scaleMatrix, model;
    model = transform(8, 7, 28.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 18, 3, 4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}
//void Siri1(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
//{
//    //nicher border
//    glm::mat4 translateMatrix, scaleMatrix, model;
//    model = transform(8, -1.5, 28.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 18, 1, 9);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//}
//void Siri2(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
//{
//    //nicher border
//    glm::mat4 translateMatrix, scaleMatrix, model;
//    model = transform(8, 7, 28.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 18, 3, 4);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//}
//void Siri3(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
//{
//    //nicher border
//    glm::mat4 translateMatrix, scaleMatrix, model;
//    model = transform(8, 7, 28.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 18, 3, 4);
//    cube.drawCubeWithTexture(lightingShader, alTogether * model);
//}
void NormalCube(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}

void Chair(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    //pichoner base
    glm::mat4 translateMatrix, scaleMatrix, model;
    model = transform(0, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.2, 1, 0.2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    /*model = transform(1.2, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -0.4, 0.5, -0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    model = transform(0, 0.25, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.4, 0.2, -0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    model = transform(0, 0.35, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.4, 0.375, -0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    model = transform(1.2, 0.35, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -0.4, 0.375, -0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    model = transform(0, 0.5375, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.4, 0.5, -0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);*/


    //boshar base
    model = transform(0, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.2, 0.2, 1.2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //pichone left leg
    model = transform(0, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, -0.75, 0.2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //pichone right leg
    model = transform(0.6, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -0.2, -0.75, 0.2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //samner left leg
    model = transform(0, 0, 0.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, -0.75, 0.2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);


    //pichone right leg
    model = transform(0.6, 0, 0.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -0.2, -0.75, 0.2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}

//ZAF 5
long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L)
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i < L + 1; i++)
    {
        long long ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i * 3];
        y += coef * ctrlpoints[(i * 3) + 1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}

unsigned int hollowBezier(GLfloat ctrlpoints[], int L)
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float theta;
    float nx, ny, nz, lengthInv;    // vertex normal


    const float dtheta = 2 * pi / ntheta;        //angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];

    for (i = 0; i <= nt; ++i)              //step through y
    {
        BezierCurve(t, xy, ctrlpoints, L);
        r = xy[0];
        y = xy[1];
        theta = 0;
        t += dt;
        lengthInv = 1.0 / r;

        for (j = 0; j <= ntheta; ++j)
        {
            double cosa = cos(theta);
            double sina = sin(theta);
            z = r * cosa;
            x = r * sina;

            coordinates.push_back(x);
            coordinates.push_back(y);
            coordinates.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            // center point of the circle (0,y,0)
            nx = (x - 0) * lengthInv;
            ny = (y - y) * lengthInv;
            nz = (z - 0) * lengthInv;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            theta += dtheta;
        }
    }

    // generate index list of triangles
    // k1--k1+1
    // |  / |
    // | /  |
    // k2--k2+1

    int k1, k2;
    for (int i = 0; i < nt; ++i)
    {
        k1 = i * (ntheta + 1);     // beginning of current stack
        k2 = k1 + ntheta + 1;      // beginning of next stack

        for (int j = 0; j < ntheta; ++j, ++k1, ++k2)
        {
            // k1 => k2 => k1+1
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            // k1+1 => k2 => k2+1
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }

    size_t count = coordinates.size();
    for (int i = 0; i < count; i += 3)
    {
        vertices.push_back(coordinates[i]);
        vertices.push_back(coordinates[i + 1]);
        vertices.push_back(coordinates[i + 2]);

        vertices.push_back(normals[i]);
        vertices.push_back(normals[i + 1]);
        vertices.push_back(normals[i + 2]);
    }

    unsigned int bezierVAO;
    glGenVertexArrays(1, &bezierVAO);
    glBindVertexArray(bezierVAO);

    // create VBO to copy vertex data to VBO
    unsigned int bezierVBO;
    glGenBuffers(1, &bezierVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);           // for vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // target
        (unsigned int)vertices.size() * sizeof(float), // data size, # of bytes
        vertices.data(),   // ptr to vertex data
        GL_STATIC_DRAW);                   // usage

    // create EBO to copy index data
    unsigned int bezierEBO;
    glGenBuffers(1, &bezierEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);   // for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
        (unsigned int)indices.size() * sizeof(unsigned int),             // data size, # of bytes
        indices.data(),               // ptr to index data
        GL_STATIC_DRAW);                   // usage

    // activate attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // set attrib arrays with stride and offset
    int stride = 24;     // should be 24 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));

    // unbind VAO, VBO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return bezierVAO;
}
void getCurrentTime(int& hours, int& minutes, int& seconds) {
    time_t currentTime = time(nullptr); // Get current UNIX timestamp
    struct tm* timeinfo;
    timeinfo = localtime(&currentTime);

    seconds = timeinfo->tm_sec;
    minutes = timeinfo->tm_min;
    hours = timeinfo->tm_hour;
}

void shaderActivate(Shader& shader)
{
    shader.use();
    shader.setVec3("viewPos", camera.Position);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
};

void curve(Shader& lightingShader, glm::mat4 alTogether)
{

    /*float rotateAngle_XB = 78.0, rotateAngle_YB = 0.0, rotateAngle_ZB = -90.0;*/
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrixB, rotateXMatrixB, rotateYMatrixB, rotateZMatrixB, scaleMatrixB, modelForCurve;
    translateMatrixB = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
    rotateXMatrixB = glm::rotate(identityMatrix, glm::radians(rotateAngle_XB), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixB = glm::rotate(identityMatrix, glm::radians(rotateAngle_YB), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixB = glm::rotate(identityMatrix, glm::radians(rotateAngle_ZB), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixB = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
    modelForCurve = alTogether * translateMatrixB * rotateXMatrixB * rotateYMatrixB * rotateZMatrixB * scaleMatrixB;

    lightingShader.setMat4("model", modelForCurve);

    if (loadBezierCurvePoints)
    {
        bezierVAO = hollowBezier(cntrlPoints.data(), ((unsigned int)cntrlPoints.size() / 3) - 1);
        loadBezierCurvePoints = false;
        showHollowBezier = true;
    }
    if (showHollowBezier)
    {
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 1.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(01.0f, 01.0f, 1.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);

        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLES,                    // primitive type
            (unsigned int)indices.size(),          // # of indices
            GL_UNSIGNED_INT,                 // data type
            (void*)0);                       // offset to indices

        // unbind VAO
        glBindVertexArray(0);
    }


}

void cylinder(Shader& lightingShader, glm::mat4 alTogether)
{

    /*float rotateAngle_XB = 78.0, rotateAngle_YB = 0.0, rotateAngle_ZB = -90.0;*/
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrixB, rotateXMatrixB, rotateYMatrixB, rotateZMatrixB, scaleMatrixB, modelForCurve;
    translateMatrixB = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
    rotateXMatrixB = glm::rotate(identityMatrix, glm::radians(rotateAngle_XB), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixB = glm::rotate(identityMatrix, glm::radians(rotateAngle_YB), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixB = glm::rotate(identityMatrix, glm::radians(rotateAngle_ZB), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixB = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
    modelForCurve = alTogether * translateMatrixB * rotateXMatrixB * rotateYMatrixB * rotateZMatrixB * scaleMatrixB;

    lightingShader.setMat4("model", modelForCurve);

    if (loadBezierCurvePoints)
    {
        bezierVAO = hollowBezier(cntrlPointsCylinder.data(), ((unsigned int)cntrlPointsCylinder.size() / 3) - 1);
        loadBezierCurvePoints = false;
        showHollowBezier = true;
    }
    if (showHollowBezier)
    {
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 1.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(01.0f, 01.0f, 1.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);

        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLES,                    // primitive type
            (unsigned int)indices.size(),          // # of indices
            GL_UNSIGNED_INT,                 // data type
            (void*)0);                       // offset to indices

        // unbind VAO
        glBindVertexArray(0);
    }


}