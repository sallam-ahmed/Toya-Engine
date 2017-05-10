#pragma once
#include "Base/IManager.hpp"
#include <string>

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
