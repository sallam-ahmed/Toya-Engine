#include "src/ToyaCore.hpp"

#include "src/GamePlay/PlayerBehaviour.hpp"
#include "src/GamePlay/Camera/TPSCamera.hpp"
#include "src/GamePlay/Camera/FPSCamera.hpp"
#include "src/GamePlay/Camera/CameraController.hpp"
#include "src/GamePlay/SimpleRoomGenerator.h"

using namespace Toya;
using namespace Graphics;
using namespace Renderers;
using namespace Input;
using namespace Math;
using namespace Components;
using namespace Utils;
using namespace CoreDrivers;

#define DEFAULT_VERT_SHADER "Shaders/Default/VertexShader.glsl"
#define DEFAULT_FRAG_SHADER "Shaders/Default/FragmentShader.glsl"

#define LIGHT_VERT_SHADER "Shaders/LightShaders/LightEnabledVertexShader.glsl"
#define LIGHT_FRAG_SHADER "Shaders/LightShaders/LightEnabledFragmentShader.glsl"

#define BATCH_RENDERER 1
#define BOX_TEST 0

Shader* default_shader;
Transform *m;
glm::vec3*lightPos;
std::vector<GameObject*> sceneObjects;
SceneManagement::Scene activeScene;


GameObject* CreateObject(char* _name)
{
	GameObject *obj = new GameObject();
	obj->name = _name;
	SceneManagement::Scene::activeScene->SceneObjects.push_back(obj);
	return obj;
}
GameObject* GetObject(char* _name)
{
	for(auto i : SceneManagement::Scene::activeScene->SceneObjects)
	{
		if (i->name == _name)
			return i;
	}
	return nullptr;
}

void _updateFunction(void)
{
/*
	auto pos = InputManager::GetCursorPosition();	
	double normalizedX = -1.0 + 2.0 * (double)pos.x / Screen::ScreenWidth;
	double normalizedY = 1.0 - 2.0 * (double)pos.y / Screen::ScreenHeight;
	auto p = glm::vec2(normalizedX,-normalizedY);*/

	if (InputManager::GetKey(KeyCode::Esc))
		Window::Main->Close();

	if (InputManager::GetKey(KeyCode::P))
		system("pause");
}
void main(void)
{

	Window* window = new Window("Toya Engine!",500,500);
	InputManager input_manager = InputManager(window);

	#pragma region Camera Init
	
	auto MainCameraObject = CreateObject("Main Camera");
	MainCameraObject->transform->Position = glm::vec3(2,5,10);
	MainCameraObject->transform->AddComponent(new Camera(window, activeScene.WorldUp));
	Camera::main->transform->Attach(new GamePlay::CameraController());
	

	#pragma endregion
	
	#pragma region Player
	
	auto playerObject = CreateObject("Player");
	playerObject->transform->Position = glm::vec3(0,0,0);
	playerObject->transform->Scale = glm::vec3(1, 1, 1);
	auto sp = static_cast<Model*>(playerObject->transform->AddComponent(new Model("res/Sphere.obj")));
	sp->BindTexture(TextureLoader::LoadTexture("res/Sphere2.jpg", 0));
	
	playerObject->transform->Attach(new GamePlay::PlayerBehaviour());

	#pragma endregion

	#pragma region Maze Generator
	auto mazeController = CreateObject("MazGenerator");
	mazeController->transform->Attach(new GamePlay::SimpleMazeGenerator());
	#pragma endregion

#if BOX_TEST
	/*****************************************************************/
	GLfloat cubeVertices[] = {
		// Positions          // Texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	/*****************************************************************/
	// Setup cube VAO
	GLuint cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);
	/*****************************************************************/
	auto boxTex2 = TextureLoader::LoadTexture("res/container2.jpg", 0);
	auto boxTex = TextureLoader::LoadTexture("res/container.jpg",0);
	//auto sphereTex = TextureLoader::LoadTexture("res/Sphere.jpg", 0);
	
	auto boxShader2 = new Shader(LIGHT_VERT_SHADER, LIGHT_FRAG_SHADER);
	auto boxShader = new Shader(LIGHT_VERT_SHADER, LIGHT_FRAG_SHADER);
	
	//sceneTextures.push_back(sphereTex);

#endif


	activeScene.SceneStart();
	do
	{
		window->Clear();
#if BOX_TEST
		boxShader->Enable();
		boxShader->SetUniformMat4("_viewMatrix", Camera::main->GetWorldToViewMatrix());
		boxShader->SetUniformMat4("_projectionMatrix", Camera::main->GetProjcetionMatrix());
		glBindVertexArray(cubeVAO);
		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, boxTex->m_TextureId);*/
		boxTex->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		boxShader->Disable();
#endif
		activeScene.SceneUpdate();
	
		window->Update(&_updateFunction);

	} while (!window->Closed());

	activeScene.SceneEnd();

	glfwTerminate();
}
