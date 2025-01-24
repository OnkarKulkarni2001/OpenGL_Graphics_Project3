#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "cLoadModels.h"
#include "FlyCam.h"
#include "cShaderCompiler.h"
#include "cVAOManager.h"
#include "cScene.h"
#include "IPlayer.h"
#include "cPlayer.h"
#include "cAiEnemy.h"
#include "cLightManager.h"
#include "cLightMover.h"
#include "cPhysicsUpdated.h"
#include "cRenderModel.h"
#include "cLua.h"
#include "cTextureCreator.h"
#include <sstream>

const int MAP_HEIGHT = 16;
const int MAP_WIDTH = 20;


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

float getRandomFloat(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

glm::vec3 getRandom_vec3(glm::vec3 min, glm::vec3 max)
{
    return glm::vec3(
        getRandomFloat(min.x, max.x),
        getRandomFloat(min.y, max.y),
        getRandomFloat(min.z, max.z));
}

std::string getStringVec3(glm::vec3 theVec3)
{
    std::stringstream ssVec;
    ssVec << "(" << theVec3.x << ", " << theVec3.y << ", " << theVec3.z << ")";
    return ssVec.str();
}


std::string GiveFloor(int floorIndex) {
    std::string floor;
    if (floorIndex == 1) {
        floor = "../3D_models/Floors/SM_Env_Dwarf_Floor_01.ply";
    }
    if (floorIndex == 2) {
        floor = "../3D_models/Floors/SM_Env_Dwarf_Floor_02.ply";
    }
    if (floorIndex == 3) {
        floor = "../3D_models/Floors/SM_Env_Dwarf_Floor_03.ply";
    }
    if (floorIndex == 4) {
        floor = "../3D_models/Floors/SM_Env_Dwarf_Floor_04.ply";
    }
    if (floorIndex == 5) {
        floor = "../3D_models/Floors/SM_Env_Dwarf_Floor_05.ply";
    }
    if (floorIndex == 6) {
        floor = "../3D_models/Floors/SM_Env_Dwarf_Floor_06.ply";
    }
    if (floorIndex == 7) {
        floor = "../3D_models/Floors/SM_Env_Dwarf_Floor_07.ply";
    }
    if (floorIndex == 8) {
        floor = "../3D_models/Floors/SM_Env_Dwarf_Floor_08.ply";
    }
    if (floorIndex == 9) {
        floor = "../3D_models/Floors/SM_Env_Dwarf_Floor_09.ply";
    }
    return floor;
}

std::string GiveWall(int wallIndex) {
    std::string wall;
    if (wallIndex == 1) {
        wall = "../3D_models/Walls/SM_Env_Dwarf_Wall_01.ply";
    }
    if (wallIndex == 2) {
        wall = "../3D_models/Walls/SM_Env_Dwarf_Wall_02.ply";
    }
    if (wallIndex == 3) {
        wall = "../3D_models/Walls/SM_Env_Dwarf_Wall_03.ply";
    }
    if (wallIndex == 4) {
        wall = "../3D_models/Walls/SM_Env_Dwarf_Wall_04.ply";
    }
    if (wallIndex == 5) {
        wall = "../3D_models/Walls/SM_Env_Dwarf_Wall_05.ply";
    }
    if (wallIndex == 6) {
        wall = "../3D_models/Walls/SM_Env_Dwarf_Wall_06.ply";
    }
    if (wallIndex == 7) {
        wall = "../3D_models/Walls/SM_Env_Dwarf_Wall_Tunnel_01.ply";
    }
    if (wallIndex == 8) {
        wall = "../3D_models/Walls/SM_Env_Dwarf_Wall_Window_02.ply";
    }
    return wall;
}

/*
void AddCeiling(glm::vec3 position)
{
    //Make a mesh for the ceiling model
    sMesh* pCeilingPanel = new sMesh();
    pCeilingPanel->modelFileName = "assets/3D_models/Floors/SM_Env_Dwarf_Floor_07.ply";
    pCeilingPanel->positionXYZ = position;
    pCeilingPanel->rotationEulerXYZ = glm::vec3(180.0f, 0.0f, 0.0f);
    pCeilingPanel->objectColourRGBA = glm::vec4(getRandomFloat(0.0f, 0.1f), getRandomFloat(0.0f, 0.1f), getRandomFloat(0.0f, 0.1f), 1);
    pCeilingPanel->uniformScale = 0.01;
    pCeilingPanel->bIsWireframe = false;
    pCeilingPanel->bDoNotLight = false;
    pCeilingPanel->bOverrideObjectColour = true;
    pCeilingPanel->uniqueFriendlyName = "CeilingPanel";
    pCeilingPanel->textures[0] = "Dungeons_2_Texture_01_A.bmp";
    pCeilingPanel->blendRatio[0] = 1.0f;
    pCeilingPanel->bIsVisible = true;
    ::g_vecMeshesToDraw.push_back(pCeilingPanel);

    ::g_pPhysicEngine->addTriangleMesh(
        "assets/3D_models/Floors/SM_Env_Dwarf_Floor_07.ply",
        pCeilingPanel->positionXYZ,
        pCeilingPanel->rotationEulerXYZ,
        pCeilingPanel->uniformScale);
}
*/


void AddFloor(cVAOManager* meshManager, GLuint program, glm::vec3 location, cScene& scene, int floorIndex)
{
    // Get and print a random string
    std::string randomWall = GiveFloor(floorIndex);

    cLoadModels model;
    model.LoadPlyModel(randomWall);

    meshManager->GettingModelReadyToRender(model);
    std::cout << model.numberOfVertices << " vertices loaded" << std::endl;

    model.pMeshTransform.x = location.x;
    model.pMeshTransform.y = location.y;
    model.pMeshTransform.z = location.z;

    model.pMeshTransform.xScale = 1;
    model.pMeshTransform.yScale = 1;
    model.pMeshTransform.zScale = 1;

    model.pMeshTransform.xRotation = 0.0f;
    model.pMeshTransform.yRotation = 0.0f;
    model.pMeshTransform.zRotation = 0.0f;

    scene.pModels.push_back(model);

}

void AddWall(cVAOManager* meshManager, GLuint program, glm::vec3 location, float rotation, cScene& scene, int wallIndex)
{
    // Get and print a random string
    std::string randomWall = GiveWall(wallIndex);
    
    cLoadModels model;
    model.LoadPlyModel(randomWall);

    meshManager->GettingModelReadyToRender(model);
    std::cout << model.numberOfVertices << " vertices loaded" << std::endl;

    model.pMeshTransform.x = location.x;
    model.pMeshTransform.y = location.y;
    model.pMeshTransform.z = location.z;

    model.pMeshTransform.xScale = 1;
    model.pMeshTransform.yScale = 1;
    model.pMeshTransform.zScale = 1;

    model.pMeshTransform.xRotation = 0.0f;
    model.pMeshTransform.yRotation = rotation;
    model.pMeshTransform.zRotation = 0.0f;

    scene.pModels.push_back(model);

}

void AddTorch(cVAOManager* meshManager, GLuint program, glm::vec3 location, float rotation, cScene& scene)
{
    // Get and print a random string
    std::string randomWall = "../3D_models/Torches/SM_Prop_Dwarf_Torch_01.ply";

    cLoadModels model;
    model.LoadPlyModel(randomWall);

    meshManager->GettingModelReadyToRender(model);
    std::cout << model.numberOfVertices << " vertices loaded" << std::endl;

    model.ModelFileName = "torch";
    model.pMeshTransform.x = location.x;
    model.pMeshTransform.y = location.y;
    model.pMeshTransform.z = location.z;

    model.pMeshTransform.xScale = 1;
    model.pMeshTransform.yScale = 1;
    model.pMeshTransform.zScale = 1;

    model.pMeshTransform.xRotation = 0.0f;
    model.pMeshTransform.yRotation = rotation;
    model.pMeshTransform.zRotation = 0.0f;

    scene.pModels.push_back(model);
}

void readMapFile(const std::string& filename, int map[MAP_HEIGHT][MAP_WIDTH], float distance, cVAOManager* meshManager, GLuint program, cScene& scene)
{
    int floorIndex = 1;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::string line;
    int y = 0;
    while (std::getline(file, line) && y < MAP_HEIGHT)
    {
        std::istringstream iss(line);
        std::string value;
        int x = 0;

        while (iss >> value && x < MAP_WIDTH)
        {
            if (value == "x")
            {
                map[y][x] = 1;  // Wall
            }
            if (value == "y")
            {
                map[y][x] = 2;  // Wall
            }
            if (value == "z")
            {
                map[y][x] = 3;  // Wall
            }
            if (value == "w")
            {
                map[y][x] = 4;  // Wall
            }
            if (value == "a")
            {
                map[y][x] = 5;  // Wall
            }
            if (value == "b")
            {
                map[y][x] = 6;  // Wall
            }
            if (value == "c")
            {
                map[y][x] = 7;  // Wall
            }
            if (value == "d")
            {
                map[y][x] = 8;  // Wall
            }
            if (value == "e")
            {
                map[y][x] = 9;  // Wall
            }
            else if (value == "0")
            {
                map[y][x] = 0;  // Empty space
            }
            x++;
        }
        y++;
    }
    file.close();

    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            floorIndex = map[y][x];
            if (map[y][x] != 0)		//Check Floor
            {
                AddFloor(meshManager, program, glm::vec3(x * distance, 0.0, y * distance), scene, floorIndex);

                if (x > 0 && map[y][x - 1] == 0)	    //check if left object is Blank, if yes place wall
                {
                    //std::cout << "Left x Detected X = " << x << " Y = " << y << std::endl;
                    AddWall(meshManager, program, glm::vec3((x * distance) - distance, 0.0, (y * distance)), -90.0f, scene, floorIndex);
                }
                if (y == 0)     // Check if Top-most Horiontal line
                {
                    //std::cout << "Top Line X = " << x << " Y = " << y << std::endl;
                    AddWall(meshManager, program, glm::vec3((x * distance) - distance, 0.0, (y * distance) - distance), 180.0f, scene, floorIndex);
                }
                if (map[y][x + 1] == 0)    //Check of right object is blank, if yes place wall
                {
                    //std::cout << "Right x Detected X = " << x << " Y = " << y << std::endl;
                    AddWall(meshManager, program, glm::vec3((x * distance), 0.0, (y * distance) - distance), 90.0f, scene, floorIndex);
                }
                if (map[y - 1][x] == 0)     // Check if Top object is blank, if yes place wall
                {
                    //std::cout << "Top x Detected X = " << x << " Y = " << y << std::endl;
                    AddWall(meshManager, program, glm::vec3((x * distance) - distance, 0.0, (y * distance) - distance), 180.0f, scene, floorIndex);
                }
                if (map[y + 1][x] == 0)     // Check if Bottom object is blank, if yes place wall
                {
                    //std::cout << "Top x Detected X = " << x << " Y = " << y << std::endl;
                    AddWall(meshManager, program, glm::vec3((x * distance), 0.0, (y * distance)), 0.0f, scene, floorIndex);
                }
                if (x == 0)      // Check if Left - Most Line, if yes place wall
                {
                    //std::cout << "Left - most Line X = " << x << " Y = " << y << std::endl;
                    AddWall(meshManager, program, glm::vec3((x * distance) - distance, 0.0, (y * distance)), -90.0f, scene, floorIndex);
                }
                if (x == MAP_WIDTH - 1)    //Check of right-most Line, if yes place wall
                {
                    std::cout << "Right x Detected X = " << x << " Y = " << y << std::endl;
                    AddWall(meshManager, program, glm::vec3((x * distance), 0.0, (y * distance) - distance), 90.0f, scene, floorIndex);
                }
            }
        }
    }
}

void readTorchMapFile(const std::string& filename, int map[MAP_HEIGHT][MAP_WIDTH], float distance, cVAOManager* meshManager, GLuint program, cScene& scene)
{
    int floorIndex = 1;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::string line;
    int y = 0;
    while (std::getline(file, line) && y < MAP_HEIGHT)
    {
        std::istringstream iss(line);
        std::string value;
        int x = 0;

        while (iss >> value && x < MAP_WIDTH)
        {
            if (value == "t")
            {
                map[y][x] = 1;  // Wall
            }
            else if (value == "0")
            {
                map[y][x] = 0;  // Empty space
            }
            x++;
        }
        y++;
    }
    file.close();

    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            floorIndex = map[y][x];
            if (map[y][x] == 1)		//Check Floor
            {
                //AddTorch(meshManager, program, glm::vec3(x * distance, 0.0, y * distance), -90.0f, scene);

                if (x > 0 && map[y][x - 1] == 0)	    //check if left object is Blank, if yes place wall
                {
                    //std::cout << "Left x Detected X = " << x << " Y = " << y << std::endl;
                    AddTorch(meshManager, program, glm::vec3((x * distance) - distance, 400.0, (y * distance)), -90.0f, scene);
                }
                if (y == 0)     // Check if Top-most Horiontal line
                {
                    //std::cout << "Top Line X = " << x << " Y = " << y << std::endl;
                    AddTorch(meshManager, program, glm::vec3((x * distance) - distance, 400.0, (y * distance) - distance), 180.0f, scene);
                }
                if (map[y][x + 1] == 0)    //Check of right object is blank, if yes place wall
                {
                    //std::cout << "Right x Detected X = " << x << " Y = " << y << std::endl;
                    AddTorch(meshManager, program, glm::vec3((x * distance), 400.0, (y * distance) - distance), 90.0f, scene);
                }
                if (map[y - 1][x] == 0)     // Check if Top object is blank, if yes place wall
                {
                    //std::cout << "Top x Detected X = " << x << " Y = " << y << std::endl;
                    AddTorch(meshManager, program, glm::vec3((x * distance) - distance, 400.0, (y * distance) - distance), 180.0f, scene);
                }
                if (map[y + 1][x] == 0)     // Check if Bottom object is blank, if yes place wall
                {
                    //std::cout << "Top x Detected X = " << x << " Y = " << y << std::endl;
                    AddTorch(meshManager, program, glm::vec3((x * distance), 400.0, (y * distance)), 0.0f, scene);
                }
                if (x == 0)      // Check if Left - Most Line, if yes place wall
                {
                    //std::cout << "Left - most Line X = " << x << " Y = " << y << std::endl;
                    AddTorch(meshManager, program, glm::vec3((x * distance) - distance, 400.0, (y * distance)), -90.0f, scene);
                }
                if (x == MAP_WIDTH - 1)    //Check of right-most Line, if yes place wall
                {
                    std::cout << "Right x Detected X = " << x << " Y = " << y << std::endl;
                    AddTorch(meshManager, program, glm::vec3((x * distance), 400.0, (y * distance) - distance), 90.0f, scene);
                }
            }
        }
    }
}


int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set OpenGL version (3.3 core profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);                  // glTexStorage2D is not supported on version 3, need to use 4!!!
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Triangle", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Refer cShaderCompiler class for more info.
    cShaderCompiler shader;
    GLuint shaderProgram = shader.CompileShader();
    glUseProgram(shaderProgram);

    // Import Scene
    cScene scene;
    scene.CreateScene("../sceneFileWithNormals.txt");
    //scene.ExportMaterial(shaderProgram, scene.numberOfMeshesToLoad);            // Considering number of materials = number of meshes to load

    cVAOManager VAOManager;
    for (int i = 0; i != scene.pModels.size(); i++) {
        VAOManager.GettingModelReadyToRender(scene.pModels[i]);         // This thing is new just because I created whole new VAO thing which creates several different VAOs and now I can render a single model multiple times
    }

    cRenderModel renderer;

    /*int numberOfVerticesToRenderForAllModels = 0;
    for (int index = 0; index != scene.pModels.size(); index++) {
        numberOfVerticesToRenderForAllModels += scene.pModels[index].numberOfVerticesToRender;
    }*/

    cLightManager lightManager;
    lightManager.LoadLights("../lightsFile.txt");
    // Camera Initialization
    FlyCam flyCam(800, 600, glm::vec3(12132.0, 212.0, 6625.0), 180.0f);
    flyCam.camSpeed = 100.0f;
    flyCam.camPitch = 5.5f;

    cLightMover lightMover(lightManager, flyCam, 1);
    

    float deltaTime = 0;
    float startTime, endTime;



    for (int modelIndex = 0; modelIndex != scene.pModels.size(); modelIndex++) {
        scene.pModels[modelIndex].pTransformedVertices = new cLoadModels::sTransformedVertex[scene.pModels[modelIndex].numberOfVertices];
    
        glm::mat4 model = scene.pModels[modelIndex].CreateModelMatrix(shaderProgram, scene.pModels[modelIndex]);      // Creation of model matrix with arguements passed in sceneFile.txt
        scene.pModels[modelIndex].GenerateTransformedVertices(model);
    }   // Used for initializing the pTransformedVertices, Nothing new xD

    // Starting physics
    cPhysicsUpdated physicsEngine(scene);

    scene.pModels[1].bIsArchway = true;
    physicsEngine.CalculateAABB(scene);

    glm::vec4 minBoundsVec4 = glm::vec4(physicsEngine.pAABB[2].min, 1.0f);
    glm::vec4 maxBoundsVec4 = glm::vec4(physicsEngine.pAABB[2].max, 1.0f);
    scene.pModels[1].minBounds = glm::vec3(minBoundsVec4.x, minBoundsVec4.y, minBoundsVec4.z + 60.0f);
    scene.pModels[1].maxBounds = glm::vec3(maxBoundsVec4.x, maxBoundsVec4.y, maxBoundsVec4.z - 90.0f);

    startTime = glfwGetTime();
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



        //int num = 50;
    float floorDistance = 500.0f;

    int map[MAP_HEIGHT][MAP_WIDTH] = { 0 };
    std::string filename = "../map.txt";
    readMapFile(filename, map, floorDistance, &VAOManager, shaderProgram, scene);
    filename = "../mapTorch.txt";
    readTorchMapFile(filename, map, floorDistance, &VAOManager, shaderProgram, scene);


    // ------------------------------------------Texture---------------------------------------

    cTextureCreator textureCreator;

    
    for (int modelIndex = 0; modelIndex != scene.pModels.size(); modelIndex++) {
        
        if (!scene.pModels[modelIndex].bIsCubeMap) {
            textureCreator.LoadTextures24Bit(shaderProgram, scene.pModels[modelIndex], true);
        }
        else {
            textureCreator.LoadCubeMap24Bit(shaderProgram, true, scene.pModels[modelIndex].cubeMapTextureID,
                scene.pModels[modelIndex].textureFilePaths[0], scene.pModels[modelIndex].textureFilePaths[1],
                scene.pModels[modelIndex].textureFilePaths[2], scene.pModels[modelIndex].textureFilePaths[3],
                scene.pModels[modelIndex].textureFilePaths[4], scene.pModels[modelIndex].textureFilePaths[5]);
        }
        //std::cout << "numberOfTextures after loading textures: " << scene.pModels[modelIndex].numberOfTextures << std::endl;
    }

    for (int modelIndex = 0; modelIndex != scene.pModels.size(); modelIndex++) {
        if (modelIndex > 2) {
            //std::cout << "Setting textures for modelIndex: " << modelIndex << std::endl;
            scene.pModels[modelIndex].numberOfTextures = 1;
            scene.pModels[modelIndex].textureFilePaths.clear();
            scene.pModels[modelIndex].textureFilePaths.push_back("../3D_models/z_Dungeon_Textures/Dungeons_2_Texture_01_A/Dungeons_2_Texture_01_A.bmp");
            scene.pModels[modelIndex].textures.resize(scene.pModels[modelIndex].numberOfTextures);
            //std::cout << "numberOfTextures after setting: " << scene.pModels[modelIndex].numberOfTextures << std::endl;
        }
    }

    GLuint textureID;
    textureCreator.CreateTextureFrom24BitBMP("../3D_models/z_Dungeon_Textures/Dungeons_2_Texture_01_A/Dungeons_2_Texture_01_A.bmp", textureID);



    GLuint moonTexture;
    textureCreator.CreateTextureFrom24BitBMP("../3D_models/CGI_Moon_Kit/lroc_color_poles_4k.bmp", moonTexture);

    GLuint waterTexture;
    textureCreator.CreateTextureFrom24BitBMP("../assets/pexels-enginakyurt-1435752.bmp", waterTexture);

    GLuint beholderTexture;
    textureCreator.CreateTextureFrom24BitBMP("../3D_models/beholder/Beholder_Base_color.bmp", beholderTexture);

    cLoadModels beholder;
    beholder.LoadPlyModel("../3D_models/beholder/export_ply/BeholderSketchfab_xyz_n_rgba_uv.ply");
    VAOManager.GettingModelReadyToRender(beholder);
    std::cout << beholder.numberOfVertices << " vertices loaded" << std::endl;

    beholder.ModelFileName = "beholder";
    beholder.pMeshTransform.x = 6254.0;
    beholder.pMeshTransform.y = 620.0;
    beholder.pMeshTransform.z = 6741.0;

    beholder.pMeshTransform.xScale = 100;
    beholder.pMeshTransform.yScale = 100;
    beholder.pMeshTransform.zScale = 100;

    beholder.pMeshTransform.xRotation = 0.0f;
    beholder.pMeshTransform.yRotation = 0.0f;
    beholder.pMeshTransform.zRotation = 0.0f;

    //moon.GenerateTransformedVertices(moon.CreateModelMatrix(shaderProgram, moon));
    beholder.numberOfTextures = 1;
    beholder.textures.resize(1);
    beholder.textureFilePaths.resize(1);
    beholder.textureFilePaths[0] = "../3D_models/beholder/Beholder_Base_color.bmp";
    beholder.textures[0] = textureID;

    scene.pModels.push_back(beholder);


    cLoadModels moon;
    moon.LoadPlyModel("../3D_models/CGI_Moon_Kit/UV_Sphere_Cylindrical_UIV_Projection_.ply");
    VAOManager.GettingModelReadyToRender(moon);
    std::cout << moon.numberOfVertices << " vertices loaded" << std::endl;

    moon.ModelFileName = "moon";
    moon.pMeshTransform.x = 0.0;
    moon.pMeshTransform.y = 100000.0;
    moon.pMeshTransform.z = 0.0;

    moon.pMeshTransform.xScale = 1000;
    moon.pMeshTransform.yScale = 1000;
    moon.pMeshTransform.zScale = 1000;

    moon.pMeshTransform.xRotation = 0.0f;
    moon.pMeshTransform.yRotation = 0.0f;
    moon.pMeshTransform.zRotation = 0.0f;

    //moon.GenerateTransformedVertices(moon.CreateModelMatrix(shaderProgram, moon));
    moon.numberOfTextures = 1;
    moon.textures.resize(1);
    moon.textureFilePaths.resize(1);
    moon.textureFilePaths[0] = "../3D_models/CGI_Moon_Kit/lroc_color_poles_4k.bmp";
    moon.textures[0] = moonTexture;

    scene.pModels.push_back(moon);



    cLoadModels water;
    water.LoadPlyModel("../assets/water.ply");
    VAOManager.GettingModelReadyToRender(water);
    std::cout << moon.numberOfVertices << " vertices loaded" << std::endl;

    water.ModelFileName = "water";
    water.pMeshTransform.x = 23650.0;
    water.pMeshTransform.y = -23000.0;
    water.pMeshTransform.z = -12200.0;

    water.pMeshTransform.xScale = 10000;
    water.pMeshTransform.yScale = 10000;
    water.pMeshTransform.zScale = 10000;

    water.pMeshTransform.xRotation = -100.0f;
    water.pMeshTransform.yRotation = 0.0f;
    water.pMeshTransform.zRotation = 0.0f;

    //moon.GenerateTransformedVertices(moon.CreateModelMatrix(shaderProgram, moon));
    water.numberOfTextures = 1;
    water.textures.resize(1);
    water.textureFilePaths.resize(1);
    water.textureFilePaths[0] = "../assets/pexels-enginakyurt-1435752.bmp";
    water.textures[0] = waterTexture;

    //water.bIsTransparent = true;
    //water.transparencyIndex = 0.5f;
    //water.bIsReflective = true;
    //water.reflectiveIndex = 0.3f;
    scene.pModels.push_back(water);


    cLoadModels CRYSTAL;
    CRYSTAL.LoadPlyModel("../3D_models/Crystals/SM_Env_Crystals_Cluster_Large_01.ply");
    VAOManager.GettingModelReadyToRender(CRYSTAL);
    std::cout << CRYSTAL.numberOfVertices << " vertices loaded" << std::endl;

    CRYSTAL.ModelFileName = "crystal";
    CRYSTAL.pMeshTransform.x = 3207.0f;
    CRYSTAL.pMeshTransform.y = 0.0f;
    CRYSTAL.pMeshTransform.z = 6217.0f;

    CRYSTAL.pMeshTransform.xScale = 1;
    CRYSTAL.pMeshTransform.yScale = 1;
    CRYSTAL.pMeshTransform.zScale = 1;

    CRYSTAL.pMeshTransform.xRotation = 0.0f;
    CRYSTAL.pMeshTransform.yRotation = 0.0f;
    CRYSTAL.pMeshTransform.zRotation = 0.0f;

    CRYSTAL.numberOfTextures = 1;
    CRYSTAL.textures.resize(1);
    CRYSTAL.textureFilePaths.resize(1);
    CRYSTAL.textureFilePaths[0] = "../3D_models/z_Dungeon_Textures/Dungeons_2_Texture_01_A/Dungeons_2_Texture_01_A.bmp";
    CRYSTAL.textures[0] = textureID;

    CRYSTAL.bIsReflective = true;
    CRYSTAL.reflectiveIndex = 1.0f;
    CRYSTAL.bIsTransparent = true;
    CRYSTAL.transparencyIndex = 0.7f;
    CRYSTAL.bIsRefractive = true;
    CRYSTAL.refractiveIndex = 1.52f;
    scene.pModels.push_back(CRYSTAL);


    cLoadModels CRYSTAL1;
    CRYSTAL1.LoadPlyModel("../3D_models/Crystals/SM_Env_Crystals_Cluster_Large_02.ply");
    VAOManager.GettingModelReadyToRender(CRYSTAL1);
    std::cout << CRYSTAL1.numberOfVertices << " vertices loaded" << std::endl;

    CRYSTAL1.ModelFileName = "crystal";
    CRYSTAL1.pMeshTransform.x = 908.0f;
    CRYSTAL1.pMeshTransform.y = 0.0f;
    CRYSTAL1.pMeshTransform.z = 3008.0f;

    CRYSTAL1.pMeshTransform.xScale = 1;
    CRYSTAL1.pMeshTransform.yScale = 1;
    CRYSTAL1.pMeshTransform.zScale = 1;

    CRYSTAL1.pMeshTransform.xRotation = 0.0f;
    CRYSTAL1.pMeshTransform.yRotation = 0.0f;
    CRYSTAL1.pMeshTransform.zRotation = 0.0f;

    CRYSTAL1.numberOfTextures = 1;
    CRYSTAL1.textures.resize(1);
    CRYSTAL1.textureFilePaths.resize(1);
    CRYSTAL1.textureFilePaths[0] = "../3D_models/z_Dungeon_Textures/Dungeons_2_Texture_01_A/Dungeons_2_Texture_01_A.bmp";
    CRYSTAL1.textures[0] = textureID;

    CRYSTAL1.bIsReflective = true;
    CRYSTAL1.reflectiveIndex = 1.0f;
    CRYSTAL1.bIsTransparent = true;
    CRYSTAL1.transparencyIndex = 0.7f;
    CRYSTAL1.bIsRefractive = true;
    CRYSTAL1.refractiveIndex = 1.52f;
    scene.pModels.push_back(CRYSTAL1);


    cLoadModels CRYSTAL2;
    CRYSTAL2.LoadPlyModel("../3D_models/Crystals/SM_Env_Crystals_Cluster_Large_03.ply");
    VAOManager.GettingModelReadyToRender(CRYSTAL2);
    std::cout << CRYSTAL1.numberOfVertices << " vertices loaded" << std::endl;

    CRYSTAL2.ModelFileName = "crystal";
    CRYSTAL2.pMeshTransform.x = 3179.0f;
    CRYSTAL2.pMeshTransform.y = 0.0f;
    CRYSTAL2.pMeshTransform.z = -138.0f;

    CRYSTAL2.pMeshTransform.xScale = 1;
    CRYSTAL2.pMeshTransform.yScale = 1;
    CRYSTAL2.pMeshTransform.zScale = 1;

    CRYSTAL2.pMeshTransform.xRotation = 0.0f;
    CRYSTAL2.pMeshTransform.yRotation = 0.0f;
    CRYSTAL2.pMeshTransform.zRotation = 0.0f;

    CRYSTAL2.numberOfTextures = 1;
    CRYSTAL2.textures.resize(1);
    CRYSTAL2.textureFilePaths.resize(1);
    CRYSTAL2.textureFilePaths[0] = "../3D_models/z_Dungeon_Textures/Dungeons_2_Texture_01_A/Dungeons_2_Texture_01_A.bmp";
    CRYSTAL2.textures[0] = textureID;

    CRYSTAL2.bIsReflective = true;
    CRYSTAL2.reflectiveIndex = 1.0f;
    CRYSTAL2.bIsTransparent = true;
    CRYSTAL2.transparencyIndex = 0.7f;
    CRYSTAL2.bIsRefractive = true;
    CRYSTAL2.refractiveIndex = 1.52f;
    scene.pModels.push_back(CRYSTAL2);


    for (int modelIndex = 0; modelIndex != scene.pModels.size(); modelIndex++) {
        scene.pModels[modelIndex].pTransformedVertices = new cLoadModels::sTransformedVertex[scene.pModels[modelIndex].numberOfVertices];

        glm::mat4 model = scene.pModels[modelIndex].CreateModelMatrix(shaderProgram, scene.pModels[modelIndex]);      // Creation of model matrix with arguements passed in sceneFile.txt
        scene.pModels[modelIndex].GenerateTransformedVertices(model);

        /*if (scene.pModels[modelIndex].ModelFileName != "crystal") {
            scene.pModels[modelIndex].bIsTransparent = true;
            scene.pModels[modelIndex].transparencyIndex = 0.5f;
            scene.pModels[modelIndex].bIsReflective = true;
            scene.pModels[modelIndex].reflectiveIndex = 1.0f;
        }*/

        if (modelIndex > 2 && scene.pModels[modelIndex].ModelFileName != "moon" && scene.pModels[modelIndex].ModelFileName != "water") {
            scene.pModels[modelIndex].textures[0] = textureID;
            glActiveTexture(GL_TEXTURE0 + scene.pModels[modelIndex].textures[0]);   // 0 is texture unit
            glBindTexture(GL_TEXTURE_2D, scene.pModels[modelIndex].textures[0]);
            std::string textureString = "textureSamplers[" + to_string(0) + "]";		// done this as I have array of texture units in shader
            glUniform1i(glGetUniformLocation(shaderProgram, textureString.c_str()), scene.pModels[modelIndex].textures[0]);  // textureIndex is texture unit
            glUniform1i(glGetUniformLocation(shaderProgram, "bUseTexture"), true);
            glUniform1i(glGetUniformLocation(shaderProgram, "numberOfTextures"), 1);
        }

        //if (scene.pModels[modelIndex].ModelFileName != "beholder") {
        //    scene.pModels[modelIndex].textures[0] = textureID;
        //    glActiveTexture(GL_TEXTURE0 + scene.pModels[modelIndex].textures[0]);   // 0 is texture unit
        //    glBindTexture(GL_TEXTURE_2D, scene.pModels[modelIndex].textures[0]);
        //    std::string textureString = "textureSamplers[" + to_string(0) + "]";		// done this as I have array of texture units in shader
        //    glUniform1i(glGetUniformLocation(shaderProgram, textureString.c_str()), scene.pModels[modelIndex].textures[0]);  // textureIndex is texture unit
        //    glUniform1i(glGetUniformLocation(shaderProgram, "bUseTexture"), true);
        //    glUniform1i(glGetUniformLocation(shaderProgram, "numberOfTextures"), 1);
        //}
    }
    //textureCreator.CreateTextureFrom24BitBMP(model.textureFilePaths[textureIndex], model.textures[textureIndex]);



    glEnable(GL_BLEND);                                 // For transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ------------------------------------------Texture---------------------------------------

    // -----------------------------------------------LUA----------------------------------------------
    
    cLua lua;
    lua_State* state = luaL_newstate();
    lua.InitLua(state);
    //lua.ExecuteLuaScript(state, "game_logic.lua");      // Need to implement this script game_logic.lua

    // -----------------------------------------------LUA----------------------------------------------

    for (int modelIndex = 0; modelIndex != scene.pModels.size(); modelIndex++) {
        if (scene.pModels[modelIndex].ModelFileName == "torch") {
            cLightManager::sLights light;
            light.position = glm::vec3(scene.pModels[modelIndex].pMeshTransform.x, scene.pModels[modelIndex].pMeshTransform.y + 50, scene.pModels[modelIndex].pMeshTransform.z);
            light.ambient = glm::vec4(0.0);
            light.atten = glm::vec4(0.0, 0.0001, 0.0001, 1000);
            light.color = glm::vec4(1.0, 0.4, 0.0, 1.0);
            light.diffuse = glm::vec4(1.0);
            light.specular = glm::vec4(1.0);
            light.direction = glm::vec4(0.0);
            light.param1 = glm::vec4(0.0, 0.0, 1.0, 0.0);
            light.param2 = glm::vec4(1.0, 0.0, 0.0, 0.0);
            lightManager.lights.push_back(light);
        }
    }

    cLightManager::sLights light;
    light.position = glm::vec3(0.0, 100000000000, 0);
    light.ambient = glm::vec4(0.0);
    light.atten = glm::vec4(0.0, 0.00000000000001, 0.000000000001, 100000000);
    light.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
    light.diffuse = glm::vec4(1.0);
    light.specular = glm::vec4(1.0);
    light.direction = glm::vec4(0.0);
    light.param1 = glm::vec4(0.0, 0.0, 1.0, 0.0);
    light.param2 = glm::vec4(1.0, 0.0, 0.0, 0.0);
    lightManager.lights.push_back(light);

    /*cLightManager::sLights s1;
    light.position = glm::vec3(6254.0, 620.0, 6741.0);
    light.ambient = glm::vec4(0.0);
    light.atten = glm::vec4(0.0, 0.00000000000001, 0.000000000001, 100000000);
    light.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
    light.diffuse = glm::vec4(1.0);
    light.specular = glm::vec4(1.0);
    light.direction = glm::vec4(0.0, 90.0, 0.0, 0.0);
    light.param1 = glm::vec4(1.0, 5.0, 5.0, 0.0);
    light.param2 = glm::vec4(1.0, 0.0, 0.0, 0.0);
    lightManager.lights.push_back(s1);


    cLightManager::sLights s2;
    light.position = glm::vec3(6254.0, 620.0, 6711.0);
    light.ambient = glm::vec4(0.0);
    light.atten = glm::vec4(0.0, 0.00000000000001, 0.000000000001, 100000000);
    light.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
    light.diffuse = glm::vec4(1.0);
    light.specular = glm::vec4(1.0);
    light.direction = glm::vec4(0.0, 90.0, 0.0, 0.0);
    light.param1 = glm::vec4(1.0, 5.0, 5.0, 0.0);
    light.param2 = glm::vec4(1.0, 0.0, 0.0, 0.0);
    lightManager.lights.push_back(s2);

    cLightManager::sLights s3;
    light.position = glm::vec3(6254.0, 620.0, 6781.0);
    light.ambient = glm::vec4(0.0);
    light.atten = glm::vec4(0.0, 0.00000000000001, 0.000000000001, 100000000);
    light.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
    light.diffuse = glm::vec4(1.0);
    light.specular = glm::vec4(1.0);
    light.direction = glm::vec4(0.0, 90.0, 0.0, 0.0);
    light.param1 = glm::vec4(1.0, 5.0, 5.0, 0.0);
    light.param2 = glm::vec4(1.0, 0.0, 0.0, 0.0);
    lightManager.lights.push_back(s3);*/

    // Render loop
    while (!glfwWindowShouldClose(window)) {

        // Input handling
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        glfwGetWindowSize(window, &flyCam.camWidth, &flyCam.camHeight);

        std::string cameraPositionInTitle = "Camera Location: (" + to_string(flyCam.camLocation.x) + ", " + to_string(flyCam.camLocation.y) + ", " + to_string(flyCam.camLocation.z) + ") Camera Speed: " + to_string(flyCam.camSpeed) + " Camera Roll: " + to_string(flyCam.camRoll) + " Cam yaw: " + to_string(flyCam.camYaw) + " Cam pitch: " + to_string(flyCam.camPitch);
        glfwSetWindowTitle(window, cameraPositionInTitle.c_str());

        endTime = glfwGetTime();
        deltaTime = endTime - startTime;
        //std::cout << deltaTime << " Time passed" << std::endl;
        
        flyCam.cameraMatrix(45.0f, 1000.0f, 1200000.0f, shaderProgram, "camMatrix", window);

        // Rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);   // Enable depth testing
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader program and draw the triangle
        glUseProgram(shaderProgram);

        //lightMover.MoveForward();
        //lightMover.MoveUp();
        //lightMover.MoveRight();

        // ------------------------------------------------------------------------------------------------------------------------------
        // You can call movement functions from light mover class for lights here now and then call turn on lights function of light manager
        lightManager.TurnOnLights(shaderProgram, lightManager.lights.size());
        // ------------------------------------------------------------------------------------------------------------------------------
        // You can create player objects here and make them move from here
        /*cPlayer player(scene.pModels[0]);
        player.SetSpeed(1000.0f);
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                player.MoveForward();
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                player.MoveBackward();
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                player.MoveLeft();
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                player.MoveRight();
            }
        }
        std::cout << "Player pos: (" << player.GetLocation().x  << ", " << player.GetLocation().y << ", " << player.GetLocation().z << ")" << std::endl;*/
        // ------------------------------------------------------------------------------------------------------------------------------

        /*if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            flyCam.camLocation = glm::vec3()
        }*/

        //glBindVertexArray(VAO);
        //int offset = 0;
        //for (int index = 0; index != scene.pModels.size(); index++) {
        //
        //    glm::mat4 model = scene.pModels[index].CreateModelMatrix(shaderProgram, scene.pModels[index]);      // Creation of model matrix with arguements passed in sceneFile.txt
        //    scene.pModels[index].GenerateTransformedVertices(model);            // this is here because collisions want transformed vertices
       
        //}

        // Cube map object position should go with camera (scene.pModels[2] is cubeMapObject)
        for (int i = 0; i != scene.pModels.size(); i++) {
            if (scene.pModels[i].bIsCubeMap) {
                scene.pModels[i].pMeshTransform.x = flyCam.camLocation.x;
                scene.pModels[i].pMeshTransform.y = flyCam.camLocation.y;
                scene.pModels[i].pMeshTransform.z = flyCam.camLocation.z;
            }
        }
        
        for (int i = 0; i != scene.pModels.size(); i++) {
            if (scene.pModels[i].bIsWireframe) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else {
                shader.SetSceneView(window);        // Press 1, 2 or 3 for different viewModes like wireframe, fill or point
            }
            renderer.Render(shaderProgram, &scene.pModels[i]);
        }

        // Swap buffers and poll IO events (keys pressed/released, mouse moved, etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // -----------------------------------------------LUA----------------------------------------------
    
    lua_close(state);   // Lua cleanup

    // -----------------------------------------------LUA----------------------------------------------



    // Cleanup
    VAOManager.VAOVBOCleanup();
    
    // Terminate GLFW
    glfwTerminate();
    return 0;
}