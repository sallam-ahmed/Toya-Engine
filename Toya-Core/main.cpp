#include "src/ToyaCore.hpp"
#include "src/Components/MeshRenderer.hpp"

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

Shader* default_shader;
Transform *m;
glm::vec3*lightPos;

void _updateFunction(void)
{


	auto pos = InputManager::GetCursorPosition();	
	double normalizedX = -1.0 + 2.0 * (double)pos.x / Screen::ScreenWidth;
	double normalizedY = 1.0 - 2.0 * (double)pos.y / Screen::ScreenHeight;
	auto p = glm::vec2(normalizedX,-normalizedY);

	if (InputManager::GetKey(KeyCode::Esc))
		Window::Main->Close();
	if (InputManager::GetKey(KeyCode::E))
		Camera::main->Fly(.05f * Time::deltaTime);
	if (InputManager::GetKey(KeyCode::Q))
		Camera::main->Fly(-(.05f * Time::deltaTime));
	if (InputManager::GetKey(KeyCode::RightArrow)|| InputManager::GetKey(KeyCode::D))
		Camera::main->Strafe(-.05f * Time::deltaTime );
	if (InputManager::GetKey(KeyCode::LeftArrow) || InputManager::GetKey(KeyCode::A))
		Camera::main->Strafe((.05f * Time::deltaTime));
	if (InputManager::GetKey(KeyCode::W))
		Camera::main->Walk((.05f * Time::deltaTime));
	if (InputManager::GetKey(KeyCode::S))
		Camera::main->Walk(-(.05f * Time::deltaTime));
	if (InputManager::GetKey(KeyCode::Alpha1))
		lightPos->x++;
	if (InputManager::GetKey(KeyCode::Alpha2))
		lightPos->y++;
	if (InputManager::GetKey(KeyCode::Alpha3))
		lightPos->z++;
	if (InputManager::GetKey(KeyCode::Alpha4))
		lightPos->x--;
	if (InputManager::GetKey(KeyCode::Alpha5))
		lightPos->y--;
	if (InputManager::GetKey(KeyCode::Alpha6))
		lightPos->z--;
	Camera::main->UpdateViewMatrix();
	auto fp = Camera::main->transform->GetComponent<FPSCameraController>();
	fp->ProcessMouseEvent(InputManager::GetDeltaX(), InputManager::GetDeltaY());
	auto viewMatrix = Camera::main->GetWorldToViewMatrix();
	auto projectionMatrix = Camera::main->GetProjcetionMatrix();
	default_shader->Enable();
	default_shader->SetUniformMat4("_viewMatrix", viewMatrix);
	default_shader->SetUniformMat4("_projectionMatrix", projectionMatrix);
}

void main(void)
{

	Window* window = new Window("Toya Engine!",500,500);
	InputManager input_manager = InputManager(window);
	default_shader = new Shader(LIGHT_VERT_SHADER, LIGHT_FRAG_SHADER);
	default_shader->Enable();
	InputManager::SetCursorLockState(LockState::Locked);
	#pragma region Camera Init
	auto WorldUp = glm::vec3(0, 1, 0);
	GameObject* MainCameraObject = new GameObject();
	auto ve = glm::vec3(0,0,10);
	MainCameraObject->transform->Position = ve;
	MainCameraObject->transform->AddComponent(new Camera(window, WorldUp));
	auto fpCamObj = static_cast<FPSCameraController*>(MainCameraObject->transform->AddComponent(new FPSCameraController(Camera::main)));
	fpCamObj->xSenstivity = 1.0f;
	fpCamObj->ySenstivity = 1.0f;
	fpCamObj->ConstrainX = false;
	fpCamObj->ConstrainY = true;
	fpCamObj->MaxYMovement = 89.0f;
	fpCamObj->MinYMovement = -89.0f;
	fpCamObj->EnableXMovement = fpCamObj->EnableYMovement = true;
	Camera::main->Projection = ProjectionMode::Perspective;
	Camera::main->SetProjection();
	Camera::main->UpdateViewMatrix();
	auto viewMatrix = Camera::main->GetWorldToViewMatrix();
	auto projectionMatrix = Camera::main->GetProjcetionMatrix();
#pragma endregion
	
	//RenderManager::RenderInitialize();

	glClearColor(.2f, .3f, .4f, 1.0f);
#if 1
	GLfloat cubeVertices[] = {
		// Positions         Coords			Normals
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, +1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, +1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, +1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, +1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, +1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, +1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f, 0.0f, -1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	+1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	+1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	+1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	+1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	+1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	+1.0f, 0.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	  -1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	  -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	  -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	  -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	  -1.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	  -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	    0.0f, +1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,	    0.0f, +1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	   0.0f,  +1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	   0.0f,  +1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	   0.0f,  +1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	   0.0f,  +1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,		 0.0f, -1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,		 0.0f, -1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,		0.0f,  -1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,		0.0f,  -1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,		 0.0f, -1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,		 0.0f, -1.0f, 0.0f
	};
	GLuint cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glBindVertexArray(0);
	/****************************************************************************************************/
	Texture2D *boxTex  = TextureLoader::LoadTexture("res/container.jpg", 0, true);
	Texture2D *boxTex2 = TextureLoader::LoadTexture("res/960.jpg", 1, true);
#endif
	//Shader* skyBoxShader = new Shader(SKYBOX_VERT_SHADER, SKYBOX_FRAG_SHADER);
	lightPos = new glm::vec3(5, 4, 1);
	/********************************************************/
	//auto SkyBox = new Graphics::CubeMap();
	//SkyBox->texture_faces.push_back(CUBEMAP_RIGHT);
	//SkyBox->texture_faces.push_back(CUBEMAP_LEFT);
	//SkyBox->texture_faces.push_back(CUBEMAP_TOP);
	//SkyBox->texture_faces.push_back(CUBEMAP_BOTTOM);
	//SkyBox->texture_faces.push_back(CUBEMAP_FRONT);
	//SkyBox->texture_faces.push_back(CUBEMAP_BACK);
	//SkyBox->TextureId = -1;
	//fprintf(stdout, "SkyBox Id Before %u\n", SkyBox->TextureId);
	//TextureLoader::LoadCubeMapTexture(SkyBox);
	//fprintf(stdout, "SkyBox Id %u\n", SkyBox->TextureId);
	/*******************************************************************/

	//GLfloat skyboxVertices[] = {
	//	// Positions          
	//	-1.0f, 1.0f, -1.0f,
	//	-1.0f, -1.0f, -1.0f,
	//	1.0f, -1.0f, -1.0f,
	//	1.0f, -1.0f, -1.0f,
	//	1.0f, 1.0f, -1.0f,
	//	-1.0f, 1.0f, -1.0f,

	//	-1.0f, -1.0f, 1.0f,
	//	-1.0f, -1.0f, -1.0f,
	//	-1.0f, 1.0f, -1.0f,
	//	-1.0f, 1.0f, -1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	-1.0f, -1.0f, 1.0f,

	//	1.0f, -1.0f, -1.0f,
	//	1.0f, -1.0f, 1.0f,
	//	1.0f, 1.0f, 1.0f,
	//	1.0f, 1.0f, 1.0f,
	//	1.0f, 1.0f, -1.0f,
	//	1.0f, -1.0f, -1.0f,

	//	-1.0f, -1.0f, 1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	1.0f, 1.0f, 1.0f,
	//	1.0f, 1.0f, 1.0f,
	//	1.0f, -1.0f, 1.0f,
	//	-1.0f, -1.0f, 1.0f,

	//	-1.0f, 1.0f, -1.0f,
	//	1.0f, 1.0f, -1.0f,
	//	1.0f, 1.0f, 1.0f,
	//	1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f, -1.0f,

	//	-1.0f, -1.0f, -1.0f,
	//	-1.0f, -1.0f, 1.0f,
	//	1.0f, -1.0f, -1.0f,
	//	1.0f, -1.0f, -1.0f,
	//	-1.0f, -1.0f, 1.0f,
	//	1.0f, -1.0f, 1.0f
	//};
	//GLuint skyboxVAO, skyboxVBO;
	//glGenVertexArrays(1, &skyboxVAO);
	//glGenBuffers(1, &skyboxVBO);
	//glBindVertexArray(skyboxVAO);
	//glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), BUFFER_OFFSET(0));
	//glBindVertexArray(0);
	RenderManager::RenderInitialize();;

	//Shader *mockShader = new Shader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER);
	do
	{
		window->Clear();
		default_shader->Enable();
#if 1
		default_shader->SetUniform3f("eyePosition", Camera::main->transform->Position);
		default_shader->SetUniform4f("lightColor", Color::Green);
		default_shader->SetUniform3f("lightPosition",*lightPos);
		default_shader->SetUniformMat4("_modelMatrix", Matrix4x4(glm::translate(glm::vec3(0,0,0))));
		boxTex->Bind();
		default_shader->SetUniform1i("texture_diffuse", boxTex->TextureUnit);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		boxTex->Unbind();
		boxTex2->Bind();
		default_shader->SetUniform1i("texture_diffuse", boxTex2->TextureUnit);
		auto mdx = Matrix4x4(glm::translate(glm::vec3(2, 2, 2)));
		default_shader->SetUniformMat4("_modelMatrix",mdx);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		boxTex2->Unbind();
		glBindVertexArray(0);
#endif
	//	 Draw skybox as last
		//mockShader->Enable();
		RenderManager::RenderUpdateLoop();
		/*********************************************************************************************************/
		//skyBoxShader->Disable();
		window->Update(&_updateFunction);
	} while (!window->Closed());
	delete MainCameraObject;
	glfwTerminate();
}
