#pragma once
#include "Base/IManager.hpp"
#include <string>
#include <map>
#include "../Components/Model.hpp"

namespace Toya
{
	namespace CoreDrivers
	{
#define RSC_PATH "Resources/"
		class AssetManager : public IManager
		{
		public:
			AssetManager() = default;

			static std::string ResourcesPath;
			static std::string dataPath;
			static std::map<size_t, Components::Model*> m_ModelBank;
				void Init() override{
					ResourcesPath = RSC_PATH;
				}
				void Update() override{

				}
				AssetManager* GetInstance() override{
					return new AssetManager();
				}
		};
	}
}
