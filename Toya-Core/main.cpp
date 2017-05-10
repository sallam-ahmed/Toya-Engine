#include "src/ToyaCore.hpp"

using namespace Toya;
using namespace Graphics;
using namespace Renderers;
using namespace Input;
using namespace Math;
using namespace Components;
using namespace Utils;
using namespace CoreDrivers;

#define BOX_TEST 0

SceneManagement::Scene activeScene;

void _updateFunction(void)
{
	if (InputManager::GetKey(KeyCode::Esc))
		Window::Main->Close();

	if (InputManager::GetKey(KeyCode::P))
		system("pause");
}
void main(void)
{
	Window* window = new Window("Toya Engine - Simple PacMan CG-17",800,600);
	InputManager input_manager = InputManager(window);
	
	#pragma region Camera Init

	auto MainCameraObject = CreateObject("Main Camera");

	MainCameraObject->transform->Position = glm::vec3(2,5,10);
	MainCameraObject->transform->AddComponent(new Camera(window, activeScene.WorldUp));
	Camera::main->transform->Attach(new GamePlay::CameraController());
	MainCameraObject->transform->AddComponent(new AudioSource());
	
	#pragma endregion
	
	#pragma region Player
	
	auto playerObject = CreateObject("Player");
	
	playerObject->transform->Position = glm::vec3(-3,0,0);
	playerObject->transform->Scale = glm::vec3(1, 1, 1);
	auto sp = static_cast<Model*>(playerObject->transform->AddComponent(new Model("res/Player/Player.obj")));
	auto v = new BoxCollider();
	playerObject->transform->AddComponent(v);
	v->init();
	sp->BindTexture(TextureLoader::LoadTexture("res/Player/body.jpg", 0));
	playerObject->transform->Attach(new GamePlay::PlayerBehaviour());
	auto pointLight = static_cast<GamePlay::PointLight*>(playerObject->transform->Attach(new GamePlay::PointLight()));
	pointLight->LightColor = Color::Red;
	playerObject->transform->AddComponent(new AudioSource(false));

	#pragma endregion

	#pragma region Maze Generator
	auto mazeController = CreateObject("MazeGenerator");
	mazeController->transform->Attach(new GamePlay::SimpleMazeGenerator());
	#pragma endregion

	#pragma region Light Sys
	auto dirLight = CreateObject("Sun");
	
	dirLight->transform->Position = glm::vec3(-3, 5, 0);
	dirLight->transform->Rotate(glm::vec3(0, 1, 0), 45.0f);
	dirLight->transform->Attach(new GamePlay::DirectionalLight());
	
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
	
	InitDefaults();

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
