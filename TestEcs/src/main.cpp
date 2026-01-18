#include <iostream>
#include <string>

#include "TRA/ecs/world.hpp"
#include "TRA/ecs/component.hpp"
#include "TRA/ecs/componentLibrary.hpp"

using namespace tra;

TRA_REGISTER_COMPONENT(TestComponent,
	int m_int = 2;
	float m_float = 0.1f;
	std::string m_string = "Hello World";
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

	ecs::Entity entity = ecsWorld.createEntity();
	std::cout << "Create entity\nid: " << entity.id() << "\nversion: " << entity.version() << std::endl;

	std::cout << std::endl;
	ecsWorld.deleteEntity(entity);
	std::cout << "Entity deleted" << std::endl;
	std::cout << std::endl;

	entity = ecsWorld.createEntity();
	std::cout << "Create entity\nid: " << entity.id() << "\nversion: " << entity.version() << std::endl;

	std::cout << std::endl;

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

	return 0;
}