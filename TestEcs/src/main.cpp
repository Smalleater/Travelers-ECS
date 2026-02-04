#include <iostream>
#include <string>
#include <chrono>

#include "TRA/ecs/world.hpp"
#include "TRA/ecs/component.hpp"
#include "TRA/ecs/tag.hpp"

using namespace tra;

constexpr size_t ENTITY_COUNT = 100000;

TRA_ECS_REGISTER_TAG(TestTag1);
TRA_ECS_REGISTER_TAG(TestTag2);

TRA_ECS_REGISTER_COMPONENT(TestComponent,
	int m_int = 2;
	float m_float = 0.1f;
)

TRA_ECS_REGISTER_COMPONENT(TestNonTrivialComponent,
	int m_int;
	float m_float;
	std::string m_string;

	TestNonTrivialComponent(int _int, float _float, std::string _string) : m_int(_int), m_float(_float), m_string(_string) {}
)

struct SystemTest : public ecs::ISystem
{
	void update(ecs::World* _world) override
	{
		for (size_t i = 0; i < 7; i++)
		{
			for (auto& [entity, nonTrivialComponentPtr] : _world->queryEntities(
				ecs::WithComponent<ecs::TestNonTrivialComponent>{}, 
				ecs::WithoutComponent<>{}))
			{
				/*std::cout << "EntityId: " << std::to_string(entity.id()) << " ComponentValue: int-" << nonTrivialComponentPtr->m_int
					<< " float-" << nonTrivialComponentPtr->m_float << " string-" << nonTrivialComponentPtr->m_string << std::endl;*/
			}
		}
	}
};

int main()
{
	ecs::World ecsWorld;

	ecsWorld.addSystem(std::make_unique<SystemTest>());

	std::cout << "TestComponent\n";
	std::cout << "sizeof: " << sizeof(ecs::TestComponent) << "\n";
	std::cout << "align:  " << alignof(ecs::TestComponent) << "\n";

	std::cout << "TestNonTrivialComponent\n";
	std::cout << "sizeof: " << sizeof(ecs::TestNonTrivialComponent) << "\n";
	std::cout << "align:  " << alignof(ecs::TestNonTrivialComponent) << "\n";

	std::cout << std::endl;

	std::vector<ecs::Entity> entities;
	entities.resize(ENTITY_COUNT, ecs::NULL_ENTITY);

	std::chrono::high_resolution_clock mainClock;
	
	for (size_t i = 0; i < ENTITY_COUNT; i++)
	{
		entities[i] = ecsWorld.createEntity();

		ecsWorld.addComponent(entities[i], ecs::TestComponent{});
		ecsWorld.addComponent(entities[i], ecs::TestNonTrivialComponent(5, 6.3f, "World Hello"));
		ecsWorld.addTag<ecs::TestTag1>(entities[i]);
		ecsWorld.addTag<ecs::TestTag2>(entities[i]);
	}

	std::cout << "Start remove component" << std::endl;

	std::cout << std::endl;
	std::cout << "Query: " << std::endl;
	std::cout << std::endl;

	std::chrono::time_point start = mainClock.now();

	ecsWorld.updateSystems();

	std::chrono::time_point end = mainClock.now();
	long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Duration = " << duration << " ms" << std::endl;

	for (size_t i = 0; i < ENTITY_COUNT; i++)
	{ 
		ecsWorld.removeComponent<ecs::TestComponent>(entities[i]);
		ecsWorld.removeTag<ecs::TestTag1>(entities[i]);
		ecsWorld.removeComponent<ecs::TestNonTrivialComponent>(entities[i]);
		ecsWorld.removeTag<ecs::TestTag2>(entities[i]);
	}

	for (size_t i = 0; i < ENTITY_COUNT; i++)
	{
		ecsWorld.destroyEntity(entities[i]);
	}

	return 0;
}