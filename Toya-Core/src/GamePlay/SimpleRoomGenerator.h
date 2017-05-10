#pragma once
#include "PlayerBehaviour.hpp"
#include "../Components/Base/GameObject.hpp"
#include "../Components/Model.hpp"
#include "../Components/Camera.hpp"
#include "../Scenes/Scene.hpp"
#include "../Components/BoxCollider.hpp"
#include "PacPoint.hpp"
#include <string>
#include "PointLight.hpp"


namespace GamePlay
{
	class SimpleMazeGenerator : public Behaviour
	{
		
		GLshort simpleMap[13][13] = {
			{ 1, 1,1, 1,1, 0,0,0,1,1,1,1, 1 },
			
			{ 1, 0,0,0, 1,0,0, 0, 1,0,0,0, 1 },
			{ 1, 0,0,0, 1,0,1, 0, 1,0,0,0, 1 },
			{ 1, 0,0,1, 1,1,0, 1, 1,0,0,0, 1 },
				 	 	 	 	  
			{ 1, 0,0,0, 0,1,1, 1, 0,0,0,0, 1 },
			{ 0, 0,0,0, 0,0,0, 0, 0,0,0,0, 0 },
			{ 0, 0,0,0, 0,0,0, 0, 0,0,0,0, 0 },
			
			{ 0, 0,0,0, 0,1,1, 0, 1,0,0,1, 0 },
			{ 1, 1,1,0, 0,1,1, 1, 1,1,0,0, 1 },
				 	 	 	 	  
			{ 1, 0,0,1, 1,0,0, 0, 1,1,0,0, 1 },
			{ 1, 0,0,0, 0,0,1, 0, 0,0,0,0, 1 },
			{ 1, 0,0,0, 0,0,0, 0, 0,0,0,0, 1 },
				 	 		   
			{ 1, 1,1,1, 1,0,0, 0, 1,1,1,1, 1 }
		
		};
		GLshort cgMap[35][35] = {
			{ 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1 },
			{ 1,4,0,0,0,0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0,4,1 },
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,3,0,0, 0,0 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,3,0,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,4 ,1 ,0 ,3 ,0 ,0 ,0 ,0 ,0,0 ,0 ,0 ,0 , 4 ,1, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,3,0,0, 0,0 ,0 ,0 ,0 ,3 ,3 ,3 ,0 ,1 ,0 ,3 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0, 1, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,3,0,0, 0,0 ,0 ,0 ,0 ,3 ,0 ,3 ,0 ,1 ,0 ,3 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0, 1, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,3,0,0, 0,0 ,0 ,1 ,1 ,1 ,1 ,0 ,0 ,1 ,0 ,3 ,0 ,0 ,3 ,0 ,0, 0 ,0 ,0 ,0, 0, 1, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,3,0,0, 0,0 ,0 ,1 ,4 ,0 ,3 ,0 ,0 ,1 ,0 ,3 ,0 ,0 ,3 ,0 ,0, 0 ,0 ,0 ,0 ,0, 1, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,3,0,0, 0,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,3 ,0 ,0 ,3 ,0 ,0, 0 ,0 ,0 ,0 ,4, 1, 0 ,0 ,0 ,0 ,0,1 },
			{ 0,0,0,3,0,0, 0,0 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,3 ,0 ,0 ,3 ,0 ,1, 1 ,1 ,1 ,1 ,1 ,1, 0 ,0 ,0 ,0 ,0,1 },
			{ 0,0,0,3,0,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,3 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0,1 },
			{ 2,0,0,3,0,0, 3,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,0 ,0 ,0 ,0 ,0 ,3 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0,1 },
			{ 0,0,0,3,0,0, 0,0 ,0 ,0 ,0,1 ,1 ,1 ,1 ,1 , 0 ,0 ,0 ,0 ,3 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0, 0 ,0 ,0 ,0 ,0,1 },
			{ 0,0,0,3,0,0, 0,0 ,0 ,0 ,0,1 ,4 ,0 ,0 ,0 , 0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1, 1,  0, 0 ,0 ,0 ,0,0,1 },
			{ 1,0,0,3,0,0, 0,0 ,0 ,0 ,0,1 ,0 ,0 ,3 ,3 , 0 ,0 ,1 ,0 ,0 ,0 ,0 ,3 ,0 ,0 ,1, 0, 1, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,3,0,0, 0,0 ,0 ,0 ,0,1 ,0 ,3 ,3 ,0 , 0 ,0 ,1 ,1 ,1 ,0 ,0 ,3 ,0 ,0 ,1, 4, 0, 1 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,3,0,0, 0,3 ,0 ,0 ,0,1 ,0 ,3 ,0 ,3 , 0 ,0 ,0 ,0 ,1 ,0 ,0 ,3 ,0 ,0 ,1, 0, 0, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,3,0,0, 0,3 ,0 ,0 ,0,1 ,0 ,3 ,0 ,0 , 0 ,0 ,0 ,0 ,1 ,0 ,0 ,3 ,0 ,0 ,1, 0, 0, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,3,3,3, 3,3 ,0 ,0 ,0,1 ,0 ,3 ,0 ,0 , 0 ,0 ,0 ,0 ,0 ,0 ,0 ,3 ,0 ,0 ,1, 0, 0, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,0,3,0, 0,0 ,0 ,0 ,0,1 ,0 ,3 ,0 ,0 , 0 ,0 ,0 ,0 ,0 ,0 ,0 ,3 ,0 ,0 ,1, 0 ,0, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,0,3,0, 0,0 ,0 ,0 ,0,1 ,0 ,3 ,0 ,0 , 0 ,0 ,1 ,1 ,1 ,1 ,0 ,3 ,0 ,0 ,1, 0 ,0, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,0,3,0, 0,0 ,0 ,0 ,0,1 ,0 ,3 ,0 ,0 , 0 ,0 ,0 ,0 ,3 ,0 ,0 ,3 ,0 ,0 ,1, 0,  0, 0 ,0,0, 0, 0,1 },
			{ 1,0,0,0,3,0, 0,0 ,0 ,0 ,0,1 ,0 ,3 ,0 ,0 , 0 ,0 ,0 ,3 ,0 ,3 ,3 ,3 ,0 ,0 ,1, 0, 0, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,0,3,0, 0,0 ,0 ,0 ,0,1 ,3 ,3 ,3 ,3 , 0 ,0 ,0 ,0 ,3 ,0 ,0 ,0 ,0 ,0 ,1, 0, 0, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,0,3,0, 0,0 ,0 ,0 ,0,1 ,0 ,0 ,0 ,0 , 0 ,0 ,0 ,3,0 ,0 ,0 ,0 , 1 ,1, 1, 1, 1, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,0,3,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,3 ,0 ,0, 0 ,0 ,0 ,0 ,0, 0, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,0,0,0,3,3, 3,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3, 0 ,0 ,0 ,0 ,0, 0, 0 ,0 ,0 ,0 ,0,1 },
			{ 1,4,0,0,0,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,4,1 },
			{ 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1, 1 },

		};
		GLshort cgMap2[35][35]={
			{ 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1},
			{ 1,0,0,0,0,0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,3,0,0, 0,0 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0,0 ,0 ,0 ,0 ,0,  1, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0, 1, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0, 1, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1, 1 ,1 ,1 ,0 ,0, 1, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1, 0 ,0 ,0 ,0 ,0, 1, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1, 0 ,0 ,0 ,0 ,0, 1, 0 ,0 ,0 ,0 ,0,1},
			{ 0,0,0,0,0,0, 0,0 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,1, 1 ,1 ,1 ,1 ,1 ,1, 0 ,0 ,0 ,0 ,0,1},
			{ 0,0,0,0,0,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0,1},
			{ 2,0,0,0,0,1, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0,1},
			{ 0,0,0,0,0,0, 0,0 ,0 ,0 ,0,0 ,0 ,1 ,0 ,0 , 0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,1 ,1 ,1 ,0 ,0, 0 ,0 ,0 ,0 ,0,1},
			{ 0,0,0,0,0,0, 0,0 ,0 ,0 ,0,0 ,1 ,1 ,0 ,0 , 0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1, 0,  0, 0 ,0 ,0 ,0,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0,1 ,0 ,1 ,0 ,0 , 0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1, 0, 0, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0,0 ,0 ,1 ,0 ,0 , 0 ,0 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,1, 0, 0, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0,0 ,0 ,1 ,0 ,0 , 0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1, 0, 0, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0,0 ,0 ,1 ,0 ,0 , 0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1, 0, 0, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0,0 ,0 ,1 ,0 ,0 , 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1, 0, 0, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0,0 ,0 ,1 ,0 ,0 , 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1, 0 ,0, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0,0 ,0 ,1 ,0 ,0 , 0 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,0 ,0 ,1, 0 ,0, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0,0 ,0 ,1 ,0 ,0 , 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1, 0,  0, 0 ,0,0, 0, 0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0,0 ,0 ,1 ,0 ,0 , 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1, 0, 0, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0,0 ,0 ,1 ,0 ,0 , 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1, 0, 0, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0,1 ,1 ,1 ,1 ,1 , 0 ,0 ,0 ,0,0 ,0 ,0 ,0 ,0 ,0 ,1, 0, 0, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0, 0, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0, 0, 0 ,0 ,0 ,0 ,0,1},
			{ 1,0,0,0,0,0, 0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 ,0,1},
			{ 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1, 1 },

		};
		float xp, zp;
	public:
		float DistanceOffset, OffsetOnX, OffsetOnZ, BaseHeight;
		int GridWidth = 3, GridHeight = 3;
		SimpleMazeGenerator()
		{
			DistanceOffset = 2;
			OffsetOnX = OffsetOnZ = 0.0f;
			BaseHeight = 0.0f;
			GridWidth = GridHeight = 35;
			xp = zp = -3;
		}
		void Start() override{
			for (int i = 0; i < GridWidth; ++i)
			{
				for (int j = 0; j < GridHeight; ++j)
				{
					if (cgMap[i][j] == 1) {
						auto obj = new Toya::Components::GameObject();
						auto md = static_cast<Toya::Components::Model*>(obj->transform->AddComponent(new Toya::Components::Model("res/Primitives/primitive_cube.obj",true)));
						obj->transform->Position = glm::vec3(i *DistanceOffset + OffsetOnX, BaseHeight, j * DistanceOffset + OffsetOnZ);
						obj->tag = "Brick";
						fprintf(stdout, "Created Object %d,%d. \n", i,j);
						md->BindTexture(Toya::ShaderManager::DefaultTexture);
						auto ob = static_cast<BoxCollider*>(obj->transform->AddComponent(new BoxCollider()));
						ob->init();

						Toya::SceneManagement::Scene::activeScene->SceneObjects.push_back(obj);
					}
					else if(cgMap[i][j] == 2)
					{
						xp = i;
						zp = j;
					}
					else if(cgMap[i][j] == 3)
					{
						auto point = new GameObject();
						auto md = static_cast<Toya::Components::Model*>(point->transform->AddComponent(new Toya::Components::Model("res/Primitives/primitive_sphere.obj", true)));
						point->transform->Position = glm::vec3(i *DistanceOffset + OffsetOnX, BaseHeight-.5f, j * DistanceOffset + OffsetOnZ);
						point->tag = "PacPoint";
						point->transform->Scale = glm::vec3(.5, .5, .5);
						md->BindTexture(Toya::ShaderManager::DefaultTexture);
						auto ob = static_cast<BoxCollider*>(point->transform->AddComponent(new BoxCollider()));
						ob->init();
						point->transform->Attach(new PacPoint());
						Toya::SceneManagement::Scene::activeScene->SceneObjects.push_back(point);
					}
					else if(cgMap[i][j] == 4)
					{
						auto light = new GameObject();
						light->transform->Position = glm::vec3(i *DistanceOffset + OffsetOnX, BaseHeight + .3f, j * DistanceOffset + OffsetOnZ);
						auto pLight = static_cast<PointLight*>(light->transform->Attach(new PointLight()));
						pLight->LightColor = Color(1.0f, 1.0f, 0.0f, 1.0f);
					
						Toya::SceneManagement::Scene::activeScene->SceneObjects.push_back(light);
					}

				}
			}
			//Creating floor
			auto obj = new GameObject();
			obj->name = "Floor";
			auto md = static_cast<Toya::Components::Model*>(obj->transform->AddComponent(new Toya::Components::Model("res/Primitives/primitive_plane.obj", true)));
			obj->transform->Scale = glm::vec3(GridWidth + 20, 1, GridHeight + 20);
			obj->transform->Position = glm::vec3(GridWidth, -1.0f, GridHeight);
			md->BindTexture(Toya::TextureLoader::LoadTexture("res/textures/ground.jpg"));
			Toya::SceneManagement::Scene::activeScene->SceneObjects.push_back(obj);

			Toya::FindGameObject("Player")->transform->Position = glm::vec3(xp * DistanceOffset + OffsetOnX, BaseHeight, zp * DistanceOffset + OffsetOnZ);
			
			Camera::main->transform->GetComponent<AudioSource>()->Play("res/Audio/bg.mp3");
		}
		void OnEnable() override{
		}
		void Update() override{
		}
	};
}
