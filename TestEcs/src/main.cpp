#include <iostream>

#include "TRA/ecs/world.hpp"

using namespace tra;

int main()
{
	ecs::World ecsWorld;

	ecs::Entity entity = ecsWorld.createEntity();
	std::cout << "Create entity\nid: " << entity.id() << "\nversion: " << entity.version() << std::endl;

	ecsWorld.deleteEntity(entity);
	std::cout << "Entity deleted" << std::endl;

	entity = ecsWorld.createEntity();
	std::cout << "Create entity\nid: " << entity.id() << "\nversion: " << entity.version() << std::endl;

	return 0;
}