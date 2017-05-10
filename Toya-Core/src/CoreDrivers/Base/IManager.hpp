#pragma once
namespace Toya
{
	namespace CoreDrivers
	{
		class IManager
		{
		public:
			IManager() = default;
			virtual ~IManager();
			virtual void Init() = 0;
			virtual void Update() = 0;
			virtual IManager* GetInstance() = 0;
		};
	}
}
