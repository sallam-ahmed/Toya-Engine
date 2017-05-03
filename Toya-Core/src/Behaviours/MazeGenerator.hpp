#pragma once
#include "../Components/Base/Transform.hpp"
#include "../Input/InputManager.hpp"
using namespace Toya;
using namespace Toya::Input;

namespace GamePlay
{
	namespace Behaviours
	{
		
	class MazeGenerator : public Components::Behaviour
	{
	public:
		MazeGenerator();
		~MazeGenerator();
		void Start() override;
		void Update() override;
		void Generate(int mazeWidth, int mazeHeight);
		
		int GridHeight = 50, GridWidth = 50;
	};

	}
}
