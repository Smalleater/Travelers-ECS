#include <thread>
#include <chrono>

#include "TRA/ecs/engine.hpp"

#include "common.hpp"

#include "component.hpp"
#include "addTestComponentSystem.hpp"
#include "querryEntityBufferTestSystem.hpp"

struct CreateEntitySystem : public ecs::ISystem
{
	void update(ecs::Engine* _engine) override
	{
		for (size_t i = 0; i < ENTITY_COUNT; i++)
		{
			entities[i] = _engine->createEntity();
		}
	}
};

struct GetTestComponentSystem : public ecs::ISystem
{
	void update(ecs::Engine* _engine) override
	{
		TestComponent0 testComponent;
		for (size_t i = 0; i < ENTITY_COUNT; i++)
		{
			if (_engine->entityHasComponent<TestComponent0>(entities[i]))
			{
				testComponent = _engine->getEntityComponent<TestComponent0>(entities[i]);
				++testComponent.test;
				--testComponent.test;
			}
		}
	}
};

struct QuerryWithTestSystem : public ecs::ISystem
{
	void update(ecs::Engine* _engine) override
	{
		std::vector<ecs::Entity> queryResult;
		queryResult = _engine->queryEntityWith<TestComponent0>(entities);
		queryResult = _engine->queryEntityWith<TestComponent1>(entities);
		queryResult = _engine->queryEntityWith<TestComponent0, TestComponent2>(entities);
	}
};

struct QuerryWithoutTestSystem : public ecs::ISystem
{
	void update(ecs::Engine* _engine) override
	{
		std::vector<ecs::Entity> queryResult;
		queryResult = _engine->queryEntityWithout<TestComponent0>(entities);
		queryResult = _engine->queryEntityWithout<TestComponent1>(entities);
		queryResult = _engine->queryEntityWithout<TestComponent0, TestComponent2>(entities);
	}
};


struct RemoveTestComponentSystem : public ecs::ISystem
{
	void update(ecs::Engine* _engine) override
	{
		for (size_t i = 0; i < ENTITY_COUNT; i++)
		{
			_engine->removeComponentFromEntity<TestComponent0>(entities[i]);
		}
	}
};

struct DeleteEntitySystem : public ecs::ISystem
{
	void update(ecs::Engine* _engine) override
	{
		for (size_t i = 0; i < ENTITY_COUNT; i++)
		{
			_engine->deleteEntity(entities[i]);
		}
	}
};

int main()
{
	std::cout << "Create ECS\n";
	ecs::Engine ecsEngine;

	CreateEntitySystem createEntity;
	createEntity.update(&ecsEngine);

	AddTestComponentSystem addTestComponent;
	addTestComponent.update(&ecsEngine);

	//ecsEngine.addBeginUpdateSystem<CreateEntitySystem>();
	//ecsEngine.addBeginUpdateSystem<AddTestComponentSystem>();
	//ecsEngine.addBeginUpdateSystem<GetTestComponentSystem>();
	//ecsEngine.addBeginUpdateSystem<QuerryWithTestSystem>();
	//ecsEngine.addBeginUpdateSystem<QuerryWithoutTestSystem>();
	ecsEngine.addBeginUpdateSystem<QuerryEntityBufferTestSystem>();

	//ecsEngine.addEndUpdateSystem<RemoveTestComponentSystem>();
	//ecsEngine.addEndUpdateSystem<DeleteEntitySystem>();

	std::cout << "End Init\n";

	while (true)
	{
		auto start = std::chrono::high_resolution_clock::now();

		ecsEngine.beginUpdate();

		ecsEngine.endUpdate();

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		std::cout << "Update duration: " << duration << " microseconds\n";
	}

	return 0;
}