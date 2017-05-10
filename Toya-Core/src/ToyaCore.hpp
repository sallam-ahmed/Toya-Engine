#pragma once
/*Add here whatever you want to use in your main driver*/
#include "Math/Math.hpp"
#include "Graphics/ToyaGraphics.hpp"
#include "Input/InputManager.hpp"
#include "Components/ToyaComponents.hpp"
#include "Utils/ToyaUtils.hpp"
#include "CoreDrivers/ToyaCoreDrivers.hpp"
#include "src/Scenes/Scene.hpp"
#include "src/Behaviours/Behaviours.h"


#define DEFAULT_VERT_SHADER "Shaders/Default/VertexShader.glsl"
#define DEFAULT_FRAG_SHADER "Shaders/Default/FragmentShader.glsl"

#define LIGHT_VERT_SHADER "Shaders/LightShaders/LightEnabledVertexShader.glsl"
#define LIGHT_FRAG_SHADER "Shaders/LightShaders/LightEnabledFragmentShader.glsl"

inline Toya::Components::GameObject* CreateObject(char* _name)
{
	Toya::Components::GameObject *obj = new Toya::Components::GameObject();
	obj->name = _name;
	Toya::SceneManagement::Scene::activeScene->SceneObjects.push_back(obj);
	return obj;
}

inline Toya::Components::GameObject* GetObject(char* _name)
{
	for (auto i : Toya::SceneManagement::Scene::activeScene->SceneObjects)
	{
		if (i->name == _name)
			return i;
	}
	return nullptr;
}

inline void InitDefaults()
{
	Toya::ShaderManager::DefaultTexture = Toya::TextureLoader::LoadTexture(PRIMITIVE_DIFFUSE_TEXTURE, 0);
	Toya::ShaderManager::DefaultModelShader = Toya::ShaderManager::LoadShader(DEFAULT_MODEL_VERT_SHADER, DEFAULT_MODEL_FRAG_SHADER);
}