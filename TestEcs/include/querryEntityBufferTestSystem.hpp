#ifndef QUERRY_ENTITY_BUFFER_TEST_SYSTEM_HPP
#define QUERRY_ENTITY_BUFFER_TEST_SYSTEM_HPP

#include "TRA/ecs/engine.hpp"
#include "common.hpp"

struct QuerryEntityBufferTestSystem : public ecs::ISystem
{
	void update(ecs::Engine* _engine) override
	{
		std::vector<ecs::Entity> queryResult;
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent0>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent0>()->queryEntityWithout<TestComponent1>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent0, TestComponent2>()->queryEntityWithout<TestComponent1>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent1>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent1, TestComponent3>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent1, TestComponent3>()->queryEntityWithout<TestComponent0>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent2>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent2, TestComponent4>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent2, TestComponent4>()->queryEntityWithout<TestComponent1>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent3>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent3, TestComponent5>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent3, TestComponent5>()->queryEntityWithout<TestComponent2>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent4>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent4, TestComponent6>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent4, TestComponent6>()->queryEntityWithout<TestComponent3>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent5>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent5, TestComponent7>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent5, TestComponent7>()->queryEntityWithout<TestComponent4>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent6>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent6, TestComponent8>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent6, TestComponent8>()->queryEntityWithout<TestComponent5>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent7>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent7, TestComponent9>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent7, TestComponent9>()->queryEntityWithout<TestComponent6>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent8>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent8, TestComponent10>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent8, TestComponent10>()->queryEntityWithout<TestComponent7>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent9>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent9, TestComponent11>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent9, TestComponent11>()->queryEntityWithout<TestComponent8>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent10>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent10, TestComponent12>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent10, TestComponent12>()->queryEntityWithout<TestComponent9>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent11>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent11, TestComponent13>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent11, TestComponent13>()->queryEntityWithout<TestComponent10>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent12>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent12, TestComponent14>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent12, TestComponent14>()->queryEntityWithout<TestComponent11>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent13>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent13, TestComponent15>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent13, TestComponent15>()->queryEntityWithout<TestComponent12>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent14>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent14, TestComponent16>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent14, TestComponent16>()->queryEntityWithout<TestComponent13>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent15>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent15, TestComponent17>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent15, TestComponent17>()->queryEntityWithout<TestComponent14>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent16>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent16, TestComponent18>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent16, TestComponent18>()->queryEntityWithout<TestComponent15>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent17>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent17, TestComponent19>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent17, TestComponent19>()->queryEntityWithout<TestComponent16>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent18>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent18, TestComponent20>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent18, TestComponent20>()->queryEntityWithout<TestComponent17>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent19>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent19, TestComponent21>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent19, TestComponent21>()->queryEntityWithout<TestComponent18>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent20>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent20, TestComponent22>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent20, TestComponent22>()->queryEntityWithout<TestComponent19>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent21>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent21, TestComponent23>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent21, TestComponent23>()->queryEntityWithout<TestComponent20>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent22>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent22, TestComponent24>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent22, TestComponent24>()->queryEntityWithout<TestComponent21>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent23>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent23, TestComponent25>()->getEntities();
		queryResult = _engine->queryEntity()->queryEntityWith<TestComponent39, TestComponent41>()->queryEntityWithout<TestComponent38>()->getEntities();
	}
};

#endif
