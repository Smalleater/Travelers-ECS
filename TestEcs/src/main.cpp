#include <iostream>
#include <string>
#include <chrono>

#include "TRA/ecs/world.hpp"
#include "TRA/ecs/component.hpp"
#include "TRA/ecs/componentLibrary.hpp"

using namespace tra;

constexpr size_t ENTITY_COUNT = ecs::MAX_ENTITIES - 1;

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
		//entities.push_back(ecsWorld.createEntity());

		entities[i] = ecsWorld.createEntity();
		ecsWorld.addComponent<ecs::TestComponent>(entities[i], ecs::TestComponent{});
		ecsWorld.addComponent<ecs::TestNonTrivialComponent>(entities[i], ecs::TestNonTrivialComponent(5, 6.3f, "World Hello"));

		/*ecs::Entity entity = entities[i];
		ecs::EntityData entityData = ecsWorld.getEntityData(entities[i]);

		std::cout << "Create entity\nid: " << entity.id() << "\nversion: " << entity.version() << std::endl;
		std::cout << "Entity data\nArchetype: " << entityData.m_archetype << "\nChunkIndex: " << entityData.m_chunkIndex << "\nRow: " << entityData.m_row << std::endl;

		std::cout << std::endl;*/
	}

	std::cout << "Start remove component" << std::endl;

	for (size_t i = 0; i < ENTITY_COUNT; i++)
	{
		ecsWorld.removeComponent<ecs::TestComponent>(entities[i]);
	}

	std::chrono::time_point end = mainClock.now();
	long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	std::cout << "Duration = " << duration << " ms" << std::endl;

	system("pause");

	/*std::cout << std::endl;

	{
		ecs::EntityData entityData = ecsWorld.getEntityData(entities[0]);
		std::cout << "Entity data before add\nArchetype: " << entityData.m_archetype << "\nChunkIndex: " << entityData.m_chunkIndex << "\nRow: " << entityData.m_row << std::endl;

		ecsWorld.addComponent<ecs::TestComponent>(entities[0], ecs::TestComponent{});

		entityData = ecsWorld.getEntityData(entities[0]);
		std::cout << "Entity data after add\nArchetype: " << entityData.m_archetype << "\nChunkIndex: " << entityData.m_chunkIndex << "\nRow: " << entityData.m_row << std::endl;
	}

	std::cout << std::endl;

	{
		ecs::TestComponent& component = ecsWorld.getComponent<ecs::TestComponent>(entities[0]);
		std::cout << "Component value: m_int= " << component.m_int << " | m_float= " << component.m_float << std::endl;
	}

	std::cout << std::endl;

	{
		ecs::EntityData entityData = ecsWorld.getEntityData(entities[0]);
		std::cout << "Entity data before add\nArchetype: " << entityData.m_archetype << "\nChunkIndex: " << entityData.m_chunkIndex << "\nRow: " << entityData.m_row << std::endl;

		ecsWorld.addComponent<ecs::TestNonTrivialComponent>(entities[0], ecs::TestNonTrivialComponent(5, 6.3f, "World Hello"));

		entityData = ecsWorld.getEntityData(entities[0]);
		std::cout << "Entity data after add\nArchetype: " << entityData.m_archetype << "\nChunkIndex: " << entityData.m_chunkIndex << "\nRow: " << entityData.m_row << std::endl;
	}

	std::cout << std::endl;

	{
		ecs::TestComponent& component = ecsWorld.getComponent<ecs::TestComponent>(entities[0]);
		std::cout << "Component value: m_int= " << component.m_int << " | m_float= " << component.m_float << std::endl;
	}

	std::cout << std::endl;

	{
		ecs::TestNonTrivialComponent& component = ecsWorld.getComponent<ecs::TestNonTrivialComponent>(entities[0]);
		std::cout << "Component value: m_int= " << component.m_int << " | m_float= " << component.m_float << " | m_string= " << component.m_string << std::endl;
	}*/
	
	/*std::cout << std::endl;

	std::cout << "TestComponent Id: " << std::to_string(ecs::TestComponent::getId()) << std::endl;
	std::cout << "TestNonTrivialComponent Id: " << std::to_string(ecs::TestNonTrivialComponent::getId()) << std::endl;

	std::cout << std::endl;

	ecs::TestComponent testComponent;
	ecs::TestNonTrivialComponent testNonTrivialComponent(5, 6.3f, "World Hello");

	std::cout << "TestComponent value: " << testComponent.m_int << " " << testComponent.m_float << " " << testComponent.m_string << std::endl;
	std::cout << "TestNonTrivialComponent value: " << testNonTrivialComponent.m_int << " " << testNonTrivialComponent.m_float << " " << testNonTrivialComponent.m_string << std::endl;

	std::cout << std::endl;

	const ecs::ComponentInfo& TestComponentInfo = ecs::ComponentLibrary::get(ecs::TestComponent::getId());
	const ecs::ComponentInfo& TestNonTrivialComponentInfo = ecs::ComponentLibrary::get(ecs::TestNonTrivialComponent::getId());

	std::cout << "TestComponent info value - size: " << std::to_string(TestComponentInfo.m_size) << " alignement: " 
		<< std::to_string(TestComponentInfo.m_alignment) << " id: " << std::to_string(TestComponentInfo.m_id) << std::endl;

	std::cout << "TestNonTrivialComponent info value: - size: " << std::to_string(TestNonTrivialComponentInfo.m_size) << " alignement: "
		<< std::to_string(TestNonTrivialComponentInfo.m_alignment) << " id: " << std::to_string(TestNonTrivialComponentInfo.m_id) << std::endl;
	
	std::cout << std::endl;

	{
		ecs::EntityData entityData = ecsWorld.getEntityData(entities[0]);
		std::cout << "Entity data before add\nArchetype: " << entityData.m_archetype << "\nChunkIndex: " << entityData.m_chunkIndex << "\nRow: " << entityData.m_row << std::endl;

		ecsWorld.addComponent<ecs::TestComponent>(entities[0], ecs::TestComponent{});

		entityData = ecsWorld.getEntityData(entities[0]);
		std::cout << "Entity data after add\nArchetype: " << entityData.m_archetype << "\nChunkIndex: " << entityData.m_chunkIndex << "\nRow: " << entityData.m_row << std::endl;
	}

	std::cout << std::endl;

	{
		ecs::EntityData entityData = ecsWorld.getEntityData(entities[5]);
		std::cout << "Entity data before add\nArchetype: " << entityData.m_archetype << "\nChunkIndex: " << entityData.m_chunkIndex << "\nRow: " << entityData.m_row << std::endl;

		ecsWorld.addComponent<ecs::TestComponent>(entities[5], ecs::TestComponent{});

		entityData = ecsWorld.getEntityData(entities[5]);
		std::cout << "Entity data after add\nArchetype: " << entityData.m_archetype << "\nChunkIndex: " << entityData.m_chunkIndex << "\nRow: " << entityData.m_row << std::endl;
	}

	std::cout << std::endl;

	{
		ecs::EntityData entityData = ecsWorld.getEntityData(entities[0]);
		std::cout << "Entity data before add\nArchetype: " << entityData.m_archetype << "\nChunkIndex: " << entityData.m_chunkIndex << "\nRow: " << entityData.m_row << std::endl;

		ecsWorld.addComponent<ecs::TestNonTrivialComponent>(entities[0], ecs::TestNonTrivialComponent(5, 6.3f, "World Hello"));

		entityData = ecsWorld.getEntityData(entities[0]);
		std::cout << "Entity data after add\nArchetype: " << entityData.m_archetype << "\nChunkIndex: " << entityData.m_chunkIndex << "\nRow: " << entityData.m_row << std::endl;
	}

	std::cout << std::endl;

	{
		ecs::EntityData entityData = ecsWorld.getEntityData(entities[5]);
		std::cout << "Entity data before remove\nArchetype: " << entityData.m_archetype << "\nChunkIndex: " << entityData.m_chunkIndex << "\nRow: " << entityData.m_row << std::endl;

		ecsWorld.removeComponent<ecs::TestComponent>(entities[5]);

		entityData = ecsWorld.getEntityData(entities[5]);
		std::cout << "Entity data after remove\nArchetype: " << entityData.m_archetype << "\nChunkIndex: " << entityData.m_chunkIndex << "\nRow: " << entityData.m_row << std::endl;
	}*/

	return 0;
}