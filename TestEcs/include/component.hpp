#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>
#include <cstdint>

#include "TRA/ecs/iComponent.hpp"

#include "common.hpp"

struct TestComponent0 : ecs::IComponent { uint16_t test = 2006; std::string string = "Hello"; };
struct TestComponent1 : ecs::IComponent { std::string string = "HelloWorld"; };
struct TestComponent2 : ecs::IComponent { uint64_t test0 = 2006, test1 = 2006, test2 = 2006, test3 = 2006, test4 = 2006, test5 = 2006; };
struct TestComponent3 : ecs::IComponent { int32_t value = 42; std::string name = "Component3"; };
struct TestComponent4 : ecs::IComponent { float x = 1.0f, y = 2.0f, z = 3.0f; };
struct TestComponent5 : ecs::IComponent { bool active = true; };
struct TestComponent6 : ecs::IComponent { double position[3] = { 0.0, 0.0, 0.0 }; };
struct TestComponent7 : ecs::IComponent { uint8_t level = 5; std::string description = "Level7"; };
struct TestComponent8 : ecs::IComponent { int64_t id = 123456789; };
struct TestComponent9 : ecs::IComponent { std::string message = "TestComponent9"; bool enabled = false; };

struct TestComponent10 : ecs::IComponent { uint32_t count = 10; std::string label = "Component10"; };
struct TestComponent11 : ecs::IComponent { float speed = 3.14f; };
struct TestComponent12 : ecs::IComponent { double matrix[4] = { 1.0, 0.0, 0.0, 1.0 }; };
struct TestComponent13 : ecs::IComponent { bool visible = true; std::string tag = "C13"; };
struct TestComponent14 : ecs::IComponent { int16_t code = 14; };
struct TestComponent15 : ecs::IComponent { uint64_t data[2] = { 150, 250 }; };
struct TestComponent16 : ecs::IComponent { float pos[3] = { 0.1f, 0.2f, 0.3f }; };
struct TestComponent17 : ecs::IComponent { std::string name = "Component17"; int32_t value = 1700; };
struct TestComponent18 : ecs::IComponent { bool flag = false; uint16_t id = 18; };
struct TestComponent19 : ecs::IComponent { double x = 1.1, y = 2.2, z = 3.3; };

struct TestComponent20 : ecs::IComponent { int8_t small = -20; };
struct TestComponent21 : ecs::IComponent { std::string description = "Component21"; uint32_t score = 2100; };
struct TestComponent22 : ecs::IComponent { float vec[2] = { 2.2f, 3.3f }; };
struct TestComponent23 : ecs::IComponent { bool enabled = true; std::string label = "C23"; };
struct TestComponent24 : ecs::IComponent { uint64_t values[3] = { 24, 48, 72 }; };
struct TestComponent25 : ecs::IComponent { double angle = 25.5; };
struct TestComponent26 : ecs::IComponent { int32_t health = 260; };
struct TestComponent27 : ecs::IComponent { std::string title = "Component27"; bool active = false; };
struct TestComponent28 : ecs::IComponent { float coordinates[3] = { 2.8f, 5.6f, 8.4f }; };
struct TestComponent29 : ecs::IComponent { uint16_t level = 29; std::string info = "C29"; };

struct TestComponent30 : ecs::IComponent { int64_t bigNumber = 300000; };
struct TestComponent31 : ecs::IComponent { bool isAlive = true; float velocity = 31.31f; };
struct TestComponent32 : ecs::IComponent { std::string data = "Component32"; };
struct TestComponent33 : ecs::IComponent { double coords[3] = { 3.3, 6.6, 9.9 }; };
struct TestComponent34 : ecs::IComponent { uint32_t id = 34; bool active = false; };
struct TestComponent35 : ecs::IComponent { int16_t code = 350; };
struct TestComponent36 : ecs::IComponent { float matrix[4] = { 0.36f, 0.36f, 0.36f, 0.36f }; };
struct TestComponent37 : ecs::IComponent { std::string name = "C37"; int32_t points = 370; };
struct TestComponent38 : ecs::IComponent { bool flag = true; uint64_t data = 380; };
struct TestComponent39 : ecs::IComponent { double pos[3] = { 3.9, 7.8, 11.7 }; };

struct TestComponent40 : ecs::IComponent { uint8_t rank = 40; };
struct TestComponent41 : ecs::IComponent { std::string description = "C41"; float x = 4.1f; };
struct TestComponent42 : ecs::IComponent { int32_t value = 420; bool active = false; };
struct TestComponent43 : ecs::IComponent { double coords[2] = { 4.3, 8.6 }; };
struct TestComponent44 : ecs::IComponent { uint64_t id = 440; std::string label = "C44"; };
struct TestComponent45 : ecs::IComponent { float speed = 4.5f; bool enabled = true; };
struct TestComponent46 : ecs::IComponent { int16_t code = 460; };
struct TestComponent47 : ecs::IComponent { std::string name = "Component47"; };
struct TestComponent48 : ecs::IComponent { double values[3] = { 4.8, 9.6, 14.4 }; };
struct TestComponent49 : ecs::IComponent { bool active = true; uint32_t score = 490; };

struct TestComponent50 : ecs::IComponent { int8_t small = -50; };
struct TestComponent51 : ecs::IComponent { std::string info = "C51"; };
struct TestComponent52 : ecs::IComponent { float vec[2] = { 5.2f, 10.4f }; };
struct TestComponent53 : ecs::IComponent { bool enabled = false; std::string label = "C53"; };
struct TestComponent54 : ecs::IComponent { uint64_t values[3] = { 54, 108, 162 }; };
struct TestComponent55 : ecs::IComponent { double angle = 55.5; };
struct TestComponent56 : ecs::IComponent { int32_t health = 560; };
struct TestComponent57 : ecs::IComponent { std::string title = "Component57"; bool active = false; };
struct TestComponent58 : ecs::IComponent { float coordinates[3] = { 5.8f, 11.6f, 17.4f }; };
struct TestComponent59 : ecs::IComponent { uint16_t level = 59; std::string info = "C59"; };

struct TestComponent60 : ecs::IComponent { int64_t bigNumber = 600000; };
struct TestComponent61 : ecs::IComponent { bool isAlive = true; float velocity = 61.61f; };
struct TestComponent62 : ecs::IComponent { std::string data = "Component62"; };
struct TestComponent63 : ecs::IComponent { double coords[3] = { 6.3, 12.6, 18.9 }; };
struct TestComponent64 : ecs::IComponent { uint32_t id = 64; bool active = false; };
struct TestComponent65 : ecs::IComponent { int16_t code = 650; };
struct TestComponent66 : ecs::IComponent { float matrix[4] = { 0.66f, 0.66f, 0.66f, 0.66f }; };
struct TestComponent67 : ecs::IComponent { std::string name = "C67"; int32_t points = 670; };
struct TestComponent68 : ecs::IComponent { bool flag = true; uint64_t data = 680; };
struct TestComponent69 : ecs::IComponent { double pos[3] = { 6.9, 13.8, 20.7 }; };

struct TestComponent70 : ecs::IComponent { uint8_t rank = 70; };
struct TestComponent71 : ecs::IComponent { std::string description = "C71"; float x = 7.1f; };
struct TestComponent72 : ecs::IComponent { int32_t value = 720; bool active = false; };
struct TestComponent73 : ecs::IComponent { double coords[2] = { 7.3, 14.6 }; };
struct TestComponent74 : ecs::IComponent { uint64_t id = 740; std::string label = "C74"; };
struct TestComponent75 : ecs::IComponent { float speed = 7.5f; bool enabled = true; };
struct TestComponent76 : ecs::IComponent { int16_t code = 760; };
struct TestComponent77 : ecs::IComponent { std::string name = "Component77"; };
struct TestComponent78 : ecs::IComponent { double values[3] = { 7.8, 15.6, 23.4 }; };
struct TestComponent79 : ecs::IComponent { bool active = true; uint32_t score = 790; };

struct TestComponent80 : ecs::IComponent { int8_t small = -80; };
struct TestComponent81 : ecs::IComponent { std::string info = "C81"; };
struct TestComponent82 : ecs::IComponent { float vec[2] = { 8.2f, 16.4f }; };
struct TestComponent83 : ecs::IComponent { bool enabled = false; std::string label = "C83"; };
struct TestComponent84 : ecs::IComponent { uint64_t values[3] = { 84, 168, 252 }; };
struct TestComponent85 : ecs::IComponent { double angle = 85.5; };
struct TestComponent86 : ecs::IComponent { int32_t health = 860; };
struct TestComponent87 : ecs::IComponent { std::string title = "Component87"; bool active = false; };
struct TestComponent88 : ecs::IComponent { float coordinates[3] = { 8.8f, 17.6f, 26.4f }; };
struct TestComponent89 : ecs::IComponent { uint16_t level = 89; std::string info = "C89"; };

struct TestComponent90 : ecs::IComponent { int64_t bigNumber = 900000; };
struct TestComponent91 : ecs::IComponent { bool isAlive = true; float velocity = 91.91f; };
struct TestComponent92 : ecs::IComponent { std::string data = "Component92"; };
struct TestComponent93 : ecs::IComponent { double coords[3] = { 9.3, 18.6, 27.9 }; };
struct TestComponent94 : ecs::IComponent { uint32_t id = 94; bool active = false; };
struct TestComponent95 : ecs::IComponent { int16_t code = 950; };
struct TestComponent96 : ecs::IComponent { float matrix[4] = { 0.96f, 0.96f, 0.96f, 0.96f }; };
struct TestComponent97 : ecs::IComponent { std::string name = "C97"; int32_t points = 970; };
struct TestComponent98 : ecs::IComponent { bool flag = true; uint64_t data = 980; };
struct TestComponent99 : ecs::IComponent { double pos[3] = { 9.9, 19.8, 29.7 }; };

#endif
