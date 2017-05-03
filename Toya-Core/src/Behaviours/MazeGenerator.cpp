#include "MazeGenerator.hpp"


namespace GamePlay
{
	namespace Behaviours
	{


		MazeGenerator::MazeGenerator()
		{
		}


		MazeGenerator::~MazeGenerator()
		{
		}

		void MazeGenerator::Start()
		{
			this->Generate(GridWidth,GridHeight);
		}

		void MazeGenerator::Update()
		{

		}

		void MazeGenerator::Generate(int mazeWidth, int mazeHeight)
		{
			for (auto i = 0;i < mazeWidth; i++)
			{
				for(auto j = 0; j < mazeHeight; j++)
				{
					
				}
			}
		}

	}
}