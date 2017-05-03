#pragma once
#include "PlayerBehaviour.hpp"
#include "../Components/Base/GameObject.hpp"
#include "../Components/Model.hpp"
#include "../Components/Camera.hpp"
#include "../Scenes/Scene.hpp"

namespace GamePlay
{
	class SimpleMazeGenerator : public Behaviour
	{
		Toya::Shader* UnifiedShader;
		GLshort simpleMap[7][7] = {
			{ 1,1,1,1,1,1,1},
			{ 0,0,1,1,1,1,0},
			{ 0,0,1,1,1,1,0},
			{ 0,0,1,1,1,1,0},
			{ 0,0,1,1,1,1,0},
			{ 0,0,1,1,0,1,0},
			{ 0,0,1,1,0,1,0}
		
		};
	public:
		float DistanceOffset, OffsetOnX, OffsetOnZ, BaseHeight;
		int GridWidth = 3, GridHeight = 3;
		SimpleMazeGenerator()
		{
			DistanceOffset = 2;
			OffsetOnX = OffsetOnZ = 0.0f;
			BaseHeight = 0.0f;
			UnifiedShader = new Toya::Shader(DEFAULT_MODEL_VERT_SHADER, DEFAULT_MODEL_FRAG_SHADER);
		}
		void Start() override{
			UnifiedShader->Enable();
			for (int i = 0; i < 7; ++i)
			{
				for (int j = 0; j < 7; ++j)
				{
					if (simpleMap[i][j] == 1) {
						auto obj = new Toya::Components::GameObject();
						auto md = static_cast<Toya::Components::Model*>(obj->transform->AddComponent(new Toya::Components::Model("res/Primitives/cube.obj",true)));
						obj->transform->Position = glm::vec3(i *DistanceOffset + OffsetOnX, BaseHeight, j * DistanceOffset + OffsetOnZ);
						md->BindTexture(Toya::TextureLoader::LoadTexture("res/container.jpg", 0));
						md->BindShader(UnifiedShader);
						Toya::SceneManagement::Scene::activeScene->SceneObjects.push_back(obj);
					}
				}
			}
		}
		void Update() override{
		}
	};
}
