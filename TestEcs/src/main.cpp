#include <iostream>
#include <string>
#include <chrono>

#include "TRA/ecs/world.hpp"
#include "TRA/ecs/component.hpp"
#include "TRA/ecs/componentLibrary.hpp"

using namespace tra;

constexpr size_t ENTITY_COUNT = 10;

TRA_REGISTER_COMPONENT(TestComponent,
	int m_int = 2;
	float m_float = 0.1f;
)

TRA_REGISTER_COMPONENT(TestNonTrivialComponent,
	int m_int;
	float m_float;
	std::string m_string;

	TestNonTrivialComponent(int _int, float _float, std::string _string) : m_int(_int), m_float(_float), m_string(_string) {}
)

int main()
{
	ecs::World ecsWorld;

	std::cout << "TestComponent\n";
	std::cout << "sizeof: " << sizeof(ecs::TestComponent) << "\n";
	std::cout << "align:  " << alignof(ecs::TestComponent) << "\n";

	std::cout << "TestNonTrivialComponent\n";
	std::cout << "sizeof: " << sizeof(ecs::TestNonTrivialComponent) << "\n";
	std::cout << "align:  " << alignof(ecs::TestNonTrivialComponent) << "\n";

	system("pause");

	std::cout << std::endl;

	std::vector<ecs::Entity> entities;
	entities.resize(ENTITY_COUNT, ecs::NULL_ENTITY);

	std::chrono::high_resolution_clock mainClock;
	std::chrono::time_point start = mainClock.now();

	for (size_t i = 0; i < ENTITY_COUNT; i++)
	{
		entities[i] = ecsWorld.createEntity();
		ecsWorld.addComponent(entities[i], ecs::TestComponent{});
		ecsWorld.addComponent(entities[i], ecs::TestNonTrivialComponent(5, 6.3f, "World Hello"));
	}

	std::cout << "Start remove component" << std::endl;

	ecs::TestComponent testComponent = ecsWorld.getComponent<ecs::TestComponent>(entities[5]);
	std::cout << "Befor set value int: " << testComponent.m_int << " float: " << testComponent.m_float << std::endl;

	testComponent.m_int = 26;
	testComponent.m_float = 3.654f;

	ecsWorld.setComponent(entities[5], testComponent);

	testComponent = ecsWorld.getComponent<ecs::TestComponent>(entities[5]);
	std::cout << "After set value int: " << testComponent.m_int << " float: " << testComponent.m_float << std::endl;

	for (size_t i = 0; i < ENTITY_COUNT; i++)
	{
		ecsWorld.destroyEntity(entities[i]);
	}

	std::chrono::time_point end = mainClock.now();
	long long duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Duration = " << duration << " microseconds" << std::endl;

	system("pause");

	return 0;
}