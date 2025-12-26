#ifndef ADD_TEST_COMPONENT_SYSTEM_HPP
#define ADD_TEST_COMPONENT_SYSTEM_HPP

#include "TRA/ecs/engine.hpp"

#include "common.hpp"
#include "component.hpp"

struct AddTestComponentSystem : public ecs::ISystem
{
    void update(ecs::Engine* _engine) override
    {
        TestComponent0 c0;   TestComponent1 c1;   TestComponent2 c2;   TestComponent3 c3;   TestComponent4 c4;
        TestComponent5 c5;   TestComponent6 c6;   TestComponent7 c7;   TestComponent8 c8;   TestComponent9 c9;
        TestComponent10 c10; TestComponent11 c11; TestComponent12 c12; TestComponent13 c13; TestComponent14 c14;
        TestComponent15 c15; TestComponent16 c16; TestComponent17 c17; TestComponent18 c18; TestComponent19 c19;
        TestComponent20 c20; TestComponent21 c21; TestComponent22 c22; TestComponent23 c23; TestComponent24 c24;
        TestComponent25 c25; TestComponent26 c26; TestComponent27 c27; TestComponent28 c28; TestComponent29 c29;
        TestComponent30 c30; TestComponent31 c31; TestComponent32 c32; TestComponent33 c33; TestComponent34 c34;
        TestComponent35 c35; TestComponent36 c36; TestComponent37 c37; TestComponent38 c38; TestComponent39 c39;
        TestComponent40 c40; TestComponent41 c41; TestComponent42 c42; TestComponent43 c43; TestComponent44 c44;
        TestComponent45 c45; TestComponent46 c46; TestComponent47 c47; TestComponent48 c48; TestComponent49 c49;
        TestComponent50 c50; TestComponent51 c51; TestComponent52 c52; TestComponent53 c53; TestComponent54 c54;
        TestComponent55 c55; TestComponent56 c56; TestComponent57 c57; TestComponent58 c58; TestComponent59 c59;
        TestComponent60 c60; TestComponent61 c61; TestComponent62 c62; TestComponent63 c63; TestComponent64 c64;
        TestComponent65 c65; TestComponent66 c66; TestComponent67 c67; TestComponent68 c68; TestComponent69 c69;
        TestComponent70 c70; TestComponent71 c71; TestComponent72 c72; TestComponent73 c73; TestComponent74 c74;
        TestComponent75 c75; TestComponent76 c76; TestComponent77 c77; TestComponent78 c78; TestComponent79 c79;
        TestComponent80 c80; TestComponent81 c81; TestComponent82 c82; TestComponent83 c83; TestComponent84 c84;
        TestComponent85 c85; TestComponent86 c86; TestComponent87 c87; TestComponent88 c88; TestComponent89 c89;
        TestComponent90 c90; TestComponent91 c91; TestComponent92 c92; TestComponent93 c93; TestComponent94 c94;
        TestComponent95 c95; TestComponent96 c96; TestComponent97 c97; TestComponent98 c98; TestComponent99 c99;

        for (size_t i = 0; i < ENTITY_COUNT; i++)
        {
            int start = i % 100;

            switch (start)
            {
            case 0:  _engine->addComponentToEntity<TestComponent0>(entities[i], c0);   _engine->addComponentToEntity<TestComponent1>(entities[i], c1);   _engine->addComponentToEntity<TestComponent2>(entities[i], c2);   break;
            case 1:  _engine->addComponentToEntity<TestComponent1>(entities[i], c1);   _engine->addComponentToEntity<TestComponent2>(entities[i], c2);   _engine->addComponentToEntity<TestComponent3>(entities[i], c3);   break;
            case 2:  _engine->addComponentToEntity<TestComponent2>(entities[i], c2);   _engine->addComponentToEntity<TestComponent3>(entities[i], c3);   _engine->addComponentToEntity<TestComponent4>(entities[i], c4);   break;
            case 3:  _engine->addComponentToEntity<TestComponent3>(entities[i], c3);   _engine->addComponentToEntity<TestComponent4>(entities[i], c4);   _engine->addComponentToEntity<TestComponent5>(entities[i], c5);   break;
            case 4:  _engine->addComponentToEntity<TestComponent4>(entities[i], c4);   _engine->addComponentToEntity<TestComponent5>(entities[i], c5);   _engine->addComponentToEntity<TestComponent6>(entities[i], c6);   break;
            case 5:  _engine->addComponentToEntity<TestComponent5>(entities[i], c5);   _engine->addComponentToEntity<TestComponent6>(entities[i], c6);   _engine->addComponentToEntity<TestComponent7>(entities[i], c7);   break;
            case 6:  _engine->addComponentToEntity<TestComponent6>(entities[i], c6);   _engine->addComponentToEntity<TestComponent7>(entities[i], c7);   _engine->addComponentToEntity<TestComponent8>(entities[i], c8);   break;
            case 7:  _engine->addComponentToEntity<TestComponent7>(entities[i], c7);   _engine->addComponentToEntity<TestComponent8>(entities[i], c8);   _engine->addComponentToEntity<TestComponent9>(entities[i], c9);   break;
            case 8:  _engine->addComponentToEntity<TestComponent8>(entities[i], c8);   _engine->addComponentToEntity<TestComponent9>(entities[i], c9);   _engine->addComponentToEntity<TestComponent10>(entities[i], c10); break;
            case 9:  _engine->addComponentToEntity<TestComponent9>(entities[i], c9);   _engine->addComponentToEntity<TestComponent10>(entities[i], c10); _engine->addComponentToEntity<TestComponent11>(entities[i], c11); break;
            case 10: _engine->addComponentToEntity<TestComponent10>(entities[i], c10); _engine->addComponentToEntity<TestComponent11>(entities[i], c11); _engine->addComponentToEntity<TestComponent12>(entities[i], c12); break;
            case 11: _engine->addComponentToEntity<TestComponent11>(entities[i], c11); _engine->addComponentToEntity<TestComponent12>(entities[i], c12); _engine->addComponentToEntity<TestComponent13>(entities[i], c13); break;
            case 12: _engine->addComponentToEntity<TestComponent12>(entities[i], c12); _engine->addComponentToEntity<TestComponent13>(entities[i], c13); _engine->addComponentToEntity<TestComponent14>(entities[i], c14); break;
            case 13: _engine->addComponentToEntity<TestComponent13>(entities[i], c13); _engine->addComponentToEntity<TestComponent14>(entities[i], c14); _engine->addComponentToEntity<TestComponent15>(entities[i], c15); break;
            case 14: _engine->addComponentToEntity<TestComponent14>(entities[i], c14); _engine->addComponentToEntity<TestComponent15>(entities[i], c15); _engine->addComponentToEntity<TestComponent16>(entities[i], c16); break;
            case 15: _engine->addComponentToEntity<TestComponent15>(entities[i], c15); _engine->addComponentToEntity<TestComponent16>(entities[i], c16); _engine->addComponentToEntity<TestComponent17>(entities[i], c17); break;
            case 16: _engine->addComponentToEntity<TestComponent16>(entities[i], c16); _engine->addComponentToEntity<TestComponent17>(entities[i], c17); _engine->addComponentToEntity<TestComponent18>(entities[i], c18); break;
            case 17: _engine->addComponentToEntity<TestComponent17>(entities[i], c17); _engine->addComponentToEntity<TestComponent18>(entities[i], c18); _engine->addComponentToEntity<TestComponent19>(entities[i], c19); break;
            case 18: _engine->addComponentToEntity<TestComponent18>(entities[i], c18); _engine->addComponentToEntity<TestComponent19>(entities[i], c19); _engine->addComponentToEntity<TestComponent20>(entities[i], c20); break;
            case 19: _engine->addComponentToEntity<TestComponent19>(entities[i], c19); _engine->addComponentToEntity<TestComponent20>(entities[i], c20); _engine->addComponentToEntity<TestComponent21>(entities[i], c21); break;
            case 20: _engine->addComponentToEntity<TestComponent20>(entities[i], c20); _engine->addComponentToEntity<TestComponent21>(entities[i], c21); _engine->addComponentToEntity<TestComponent22>(entities[i], c22); break;
            case 21: _engine->addComponentToEntity<TestComponent21>(entities[i], c21); _engine->addComponentToEntity<TestComponent22>(entities[i], c22); _engine->addComponentToEntity<TestComponent23>(entities[i], c23); break;
            case 22: _engine->addComponentToEntity<TestComponent22>(entities[i], c22); _engine->addComponentToEntity<TestComponent23>(entities[i], c23); _engine->addComponentToEntity<TestComponent24>(entities[i], c24); break;
            case 23: _engine->addComponentToEntity<TestComponent23>(entities[i], c23); _engine->addComponentToEntity<TestComponent24>(entities[i], c24); _engine->addComponentToEntity<TestComponent25>(entities[i], c25); break;
            case 24: _engine->addComponentToEntity<TestComponent24>(entities[i], c24); _engine->addComponentToEntity<TestComponent25>(entities[i], c25); _engine->addComponentToEntity<TestComponent26>(entities[i], c26); break;
            case 25: _engine->addComponentToEntity<TestComponent25>(entities[i], c25); _engine->addComponentToEntity<TestComponent26>(entities[i], c26); _engine->addComponentToEntity<TestComponent27>(entities[i], c27); break;
            case 26: _engine->addComponentToEntity<TestComponent26>(entities[i], c26); _engine->addComponentToEntity<TestComponent27>(entities[i], c27); _engine->addComponentToEntity<TestComponent28>(entities[i], c28); break;
            case 27: _engine->addComponentToEntity<TestComponent27>(entities[i], c27); _engine->addComponentToEntity<TestComponent28>(entities[i], c28); _engine->addComponentToEntity<TestComponent29>(entities[i], c29); break;
            case 28: _engine->addComponentToEntity<TestComponent28>(entities[i], c28); _engine->addComponentToEntity<TestComponent29>(entities[i], c29); _engine->addComponentToEntity<TestComponent30>(entities[i], c30); break;
            case 29: _engine->addComponentToEntity<TestComponent29>(entities[i], c29); _engine->addComponentToEntity<TestComponent30>(entities[i], c30); _engine->addComponentToEntity<TestComponent31>(entities[i], c31); break;
            case 30: _engine->addComponentToEntity<TestComponent30>(entities[i], c30); _engine->addComponentToEntity<TestComponent31>(entities[i], c31); _engine->addComponentToEntity<TestComponent32>(entities[i], c32); break;
            case 31: _engine->addComponentToEntity<TestComponent31>(entities[i], c31); _engine->addComponentToEntity<TestComponent32>(entities[i], c32); _engine->addComponentToEntity<TestComponent33>(entities[i], c33); break;
            case 32: _engine->addComponentToEntity<TestComponent32>(entities[i], c32); _engine->addComponentToEntity<TestComponent33>(entities[i], c33); _engine->addComponentToEntity<TestComponent34>(entities[i], c34); break;
            case 33: _engine->addComponentToEntity<TestComponent33>(entities[i], c33); _engine->addComponentToEntity<TestComponent34>(entities[i], c34); _engine->addComponentToEntity<TestComponent35>(entities[i], c35); break;
            case 34: _engine->addComponentToEntity<TestComponent34>(entities[i], c34); _engine->addComponentToEntity<TestComponent35>(entities[i], c35); _engine->addComponentToEntity<TestComponent36>(entities[i], c36); break;
            case 35: _engine->addComponentToEntity<TestComponent35>(entities[i], c35); _engine->addComponentToEntity<TestComponent36>(entities[i], c36); _engine->addComponentToEntity<TestComponent37>(entities[i], c37); break;
            case 36: _engine->addComponentToEntity<TestComponent36>(entities[i], c36); _engine->addComponentToEntity<TestComponent37>(entities[i], c37); _engine->addComponentToEntity<TestComponent38>(entities[i], c38); break;
            case 37: _engine->addComponentToEntity<TestComponent37>(entities[i], c37); _engine->addComponentToEntity<TestComponent38>(entities[i], c38); _engine->addComponentToEntity<TestComponent39>(entities[i], c39); break;
            case 38: _engine->addComponentToEntity<TestComponent38>(entities[i], c38); _engine->addComponentToEntity<TestComponent39>(entities[i], c39); _engine->addComponentToEntity<TestComponent40>(entities[i], c40); break;
            case 39: _engine->addComponentToEntity<TestComponent39>(entities[i], c39); _engine->addComponentToEntity<TestComponent40>(entities[i], c40); _engine->addComponentToEntity<TestComponent41>(entities[i], c41); break;
            case 40: _engine->addComponentToEntity<TestComponent40>(entities[i], c40); _engine->addComponentToEntity<TestComponent41>(entities[i], c41); _engine->addComponentToEntity<TestComponent42>(entities[i], c42); break;
            case 41: _engine->addComponentToEntity<TestComponent41>(entities[i], c41); _engine->addComponentToEntity<TestComponent42>(entities[i], c42); _engine->addComponentToEntity<TestComponent43>(entities[i], c43); break;
            case 42: _engine->addComponentToEntity<TestComponent42>(entities[i], c42); _engine->addComponentToEntity<TestComponent43>(entities[i], c43); _engine->addComponentToEntity<TestComponent44>(entities[i], c44); break;
            case 43: _engine->addComponentToEntity<TestComponent43>(entities[i], c43); _engine->addComponentToEntity<TestComponent44>(entities[i], c44); _engine->addComponentToEntity<TestComponent45>(entities[i], c45); break;
            case 44: _engine->addComponentToEntity<TestComponent44>(entities[i], c44); _engine->addComponentToEntity<TestComponent45>(entities[i], c45); _engine->addComponentToEntity<TestComponent46>(entities[i], c46); break;
            case 45: _engine->addComponentToEntity<TestComponent45>(entities[i], c45); _engine->addComponentToEntity<TestComponent46>(entities[i], c46); _engine->addComponentToEntity<TestComponent47>(entities[i], c47); break;
            case 46: _engine->addComponentToEntity<TestComponent46>(entities[i], c46); _engine->addComponentToEntity<TestComponent47>(entities[i], c47); _engine->addComponentToEntity<TestComponent48>(entities[i], c48); break;
            case 47: _engine->addComponentToEntity<TestComponent47>(entities[i], c47); _engine->addComponentToEntity<TestComponent48>(entities[i], c48); _engine->addComponentToEntity<TestComponent49>(entities[i], c49); break;
            case 48: _engine->addComponentToEntity<TestComponent48>(entities[i], c48); _engine->addComponentToEntity<TestComponent49>(entities[i], c49); _engine->addComponentToEntity<TestComponent50>(entities[i], c50); break;
            case 49: _engine->addComponentToEntity<TestComponent49>(entities[i], c49); _engine->addComponentToEntity<TestComponent50>(entities[i], c50); _engine->addComponentToEntity<TestComponent51>(entities[i], c51); break;
            case 50: _engine->addComponentToEntity<TestComponent50>(entities[i], c50); _engine->addComponentToEntity<TestComponent51>(entities[i], c51); _engine->addComponentToEntity<TestComponent52>(entities[i], c52); break;
            case 51: _engine->addComponentToEntity<TestComponent51>(entities[i], c51); _engine->addComponentToEntity<TestComponent52>(entities[i], c52); _engine->addComponentToEntity<TestComponent53>(entities[i], c53); break;
            case 52: _engine->addComponentToEntity<TestComponent52>(entities[i], c52); _engine->addComponentToEntity<TestComponent53>(entities[i], c53); _engine->addComponentToEntity<TestComponent54>(entities[i], c54); break;
            case 53: _engine->addComponentToEntity<TestComponent53>(entities[i], c53); _engine->addComponentToEntity<TestComponent54>(entities[i], c54); _engine->addComponentToEntity<TestComponent55>(entities[i], c55); break;
            case 54: _engine->addComponentToEntity<TestComponent54>(entities[i], c54); _engine->addComponentToEntity<TestComponent55>(entities[i], c55); _engine->addComponentToEntity<TestComponent56>(entities[i], c56); break;
            case 55: _engine->addComponentToEntity<TestComponent55>(entities[i], c55); _engine->addComponentToEntity<TestComponent56>(entities[i], c56); _engine->addComponentToEntity<TestComponent57>(entities[i], c57); break;
            case 56: _engine->addComponentToEntity<TestComponent56>(entities[i], c56); _engine->addComponentToEntity<TestComponent57>(entities[i], c57); _engine->addComponentToEntity<TestComponent58>(entities[i], c58); break;
            case 57: _engine->addComponentToEntity<TestComponent57>(entities[i], c57); _engine->addComponentToEntity<TestComponent58>(entities[i], c58); _engine->addComponentToEntity<TestComponent59>(entities[i], c59); break;
            case 58: _engine->addComponentToEntity<TestComponent58>(entities[i], c58); _engine->addComponentToEntity<TestComponent59>(entities[i], c59); _engine->addComponentToEntity<TestComponent60>(entities[i], c60); break;
            case 59: _engine->addComponentToEntity<TestComponent59>(entities[i], c59); _engine->addComponentToEntity<TestComponent60>(entities[i], c60); _engine->addComponentToEntity<TestComponent61>(entities[i], c61); break;
            case 60: _engine->addComponentToEntity<TestComponent60>(entities[i], c60); _engine->addComponentToEntity<TestComponent61>(entities[i], c61); _engine->addComponentToEntity<TestComponent62>(entities[i], c62); break;
            case 61: _engine->addComponentToEntity<TestComponent61>(entities[i], c61); _engine->addComponentToEntity<TestComponent62>(entities[i], c62); _engine->addComponentToEntity<TestComponent63>(entities[i], c63); break;
            case 62: _engine->addComponentToEntity<TestComponent62>(entities[i], c62); _engine->addComponentToEntity<TestComponent63>(entities[i], c63); _engine->addComponentToEntity<TestComponent64>(entities[i], c64); break;
            case 63: _engine->addComponentToEntity<TestComponent63>(entities[i], c63); _engine->addComponentToEntity<TestComponent64>(entities[i], c64); _engine->addComponentToEntity<TestComponent65>(entities[i], c65); break;
            case 64: _engine->addComponentToEntity<TestComponent64>(entities[i], c64); _engine->addComponentToEntity<TestComponent65>(entities[i], c65); _engine->addComponentToEntity<TestComponent66>(entities[i], c66); break;
            case 65: _engine->addComponentToEntity<TestComponent65>(entities[i], c65); _engine->addComponentToEntity<TestComponent66>(entities[i], c66); _engine->addComponentToEntity<TestComponent67>(entities[i], c67); break;
            case 66: _engine->addComponentToEntity<TestComponent66>(entities[i], c66); _engine->addComponentToEntity<TestComponent67>(entities[i], c67); _engine->addComponentToEntity<TestComponent68>(entities[i], c68); break;
            case 67: _engine->addComponentToEntity<TestComponent67>(entities[i], c67); _engine->addComponentToEntity<TestComponent68>(entities[i], c68); _engine->addComponentToEntity<TestComponent69>(entities[i], c69); break;
            case 68: _engine->addComponentToEntity<TestComponent68>(entities[i], c68); _engine->addComponentToEntity<TestComponent69>(entities[i], c69); _engine->addComponentToEntity<TestComponent70>(entities[i], c70); break;
            case 69: _engine->addComponentToEntity<TestComponent69>(entities[i], c69); _engine->addComponentToEntity<TestComponent70>(entities[i], c70); _engine->addComponentToEntity<TestComponent71>(entities[i], c71); break;
            case 70: _engine->addComponentToEntity<TestComponent70>(entities[i], c70); _engine->addComponentToEntity<TestComponent71>(entities[i], c71); _engine->addComponentToEntity<TestComponent72>(entities[i], c72); break;
            case 71: _engine->addComponentToEntity<TestComponent71>(entities[i], c71); _engine->addComponentToEntity<TestComponent72>(entities[i], c72); _engine->addComponentToEntity<TestComponent73>(entities[i], c73); break;
            case 72: _engine->addComponentToEntity<TestComponent72>(entities[i], c72); _engine->addComponentToEntity<TestComponent73>(entities[i], c73); _engine->addComponentToEntity<TestComponent74>(entities[i], c74); break;
            case 73: _engine->addComponentToEntity<TestComponent73>(entities[i], c73); _engine->addComponentToEntity<TestComponent74>(entities[i], c74); _engine->addComponentToEntity<TestComponent75>(entities[i], c75); break;
            case 74: _engine->addComponentToEntity<TestComponent74>(entities[i], c74); _engine->addComponentToEntity<TestComponent75>(entities[i], c75); _engine->addComponentToEntity<TestComponent76>(entities[i], c76); break;
            case 75: _engine->addComponentToEntity<TestComponent75>(entities[i], c75); _engine->addComponentToEntity<TestComponent76>(entities[i], c76); _engine->addComponentToEntity<TestComponent77>(entities[i], c77); break;
            case 76: _engine->addComponentToEntity<TestComponent76>(entities[i], c76); _engine->addComponentToEntity<TestComponent77>(entities[i], c77); _engine->addComponentToEntity<TestComponent78>(entities[i], c78); break;
            case 77: _engine->addComponentToEntity<TestComponent77>(entities[i], c77); _engine->addComponentToEntity<TestComponent78>(entities[i], c78); _engine->addComponentToEntity<TestComponent79>(entities[i], c79); break;
            case 78: _engine->addComponentToEntity<TestComponent78>(entities[i], c78); _engine->addComponentToEntity<TestComponent79>(entities[i], c79); _engine->addComponentToEntity<TestComponent80>(entities[i], c80); break;
            case 79: _engine->addComponentToEntity<TestComponent79>(entities[i], c79); _engine->addComponentToEntity<TestComponent80>(entities[i], c80); _engine->addComponentToEntity<TestComponent81>(entities[i], c81); break;
            case 80: _engine->addComponentToEntity<TestComponent80>(entities[i], c80); _engine->addComponentToEntity<TestComponent81>(entities[i], c81); _engine->addComponentToEntity<TestComponent82>(entities[i], c82); break;
            case 81: _engine->addComponentToEntity<TestComponent81>(entities[i], c81); _engine->addComponentToEntity<TestComponent82>(entities[i], c82); _engine->addComponentToEntity<TestComponent83>(entities[i], c83); break;
            case 82: _engine->addComponentToEntity<TestComponent82>(entities[i], c82); _engine->addComponentToEntity<TestComponent83>(entities[i], c83); _engine->addComponentToEntity<TestComponent84>(entities[i], c84); break;
            case 83: _engine->addComponentToEntity<TestComponent83>(entities[i], c83); _engine->addComponentToEntity<TestComponent84>(entities[i], c84); _engine->addComponentToEntity<TestComponent85>(entities[i], c85); break;
            case 84: _engine->addComponentToEntity<TestComponent84>(entities[i], c84); _engine->addComponentToEntity<TestComponent85>(entities[i], c85); _engine->addComponentToEntity<TestComponent86>(entities[i], c86); break;
            case 85: _engine->addComponentToEntity<TestComponent85>(entities[i], c85); _engine->addComponentToEntity<TestComponent86>(entities[i], c86); _engine->addComponentToEntity<TestComponent87>(entities[i], c87); break;
            case 86: _engine->addComponentToEntity<TestComponent86>(entities[i], c86); _engine->addComponentToEntity<TestComponent87>(entities[i], c87); _engine->addComponentToEntity<TestComponent88>(entities[i], c88); break;
            case 87: _engine->addComponentToEntity<TestComponent87>(entities[i], c87); _engine->addComponentToEntity<TestComponent88>(entities[i], c88); _engine->addComponentToEntity<TestComponent89>(entities[i], c89); break;
            case 88: _engine->addComponentToEntity<TestComponent88>(entities[i], c88); _engine->addComponentToEntity<TestComponent89>(entities[i], c89); _engine->addComponentToEntity<TestComponent90>(entities[i], c90); break;
            case 89: _engine->addComponentToEntity<TestComponent89>(entities[i], c89); _engine->addComponentToEntity<TestComponent90>(entities[i], c90); _engine->addComponentToEntity<TestComponent91>(entities[i], c91); break;
            case 90: _engine->addComponentToEntity<TestComponent90>(entities[i], c90); _engine->addComponentToEntity<TestComponent91>(entities[i], c91); _engine->addComponentToEntity<TestComponent92>(entities[i], c92); break;
            case 91: _engine->addComponentToEntity<TestComponent91>(entities[i], c91); _engine->addComponentToEntity<TestComponent92>(entities[i], c92); _engine->addComponentToEntity<TestComponent93>(entities[i], c93); break;
            case 92: _engine->addComponentToEntity<TestComponent92>(entities[i], c92); _engine->addComponentToEntity<TestComponent93>(entities[i], c93); _engine->addComponentToEntity<TestComponent94>(entities[i], c94); break;
            case 93: _engine->addComponentToEntity<TestComponent93>(entities[i], c93); _engine->addComponentToEntity<TestComponent94>(entities[i], c94); _engine->addComponentToEntity<TestComponent95>(entities[i], c95); break;
            case 94: _engine->addComponentToEntity<TestComponent94>(entities[i], c94); _engine->addComponentToEntity<TestComponent95>(entities[i], c95); _engine->addComponentToEntity<TestComponent96>(entities[i], c96); break;
            case 95: _engine->addComponentToEntity<TestComponent95>(entities[i], c95); _engine->addComponentToEntity<TestComponent96>(entities[i], c96); _engine->addComponentToEntity<TestComponent97>(entities[i], c97); break;
            case 96: _engine->addComponentToEntity<TestComponent96>(entities[i], c96); _engine->addComponentToEntity<TestComponent97>(entities[i], c97); _engine->addComponentToEntity<TestComponent98>(entities[i], c98); break;
            case 97: _engine->addComponentToEntity<TestComponent97>(entities[i], c97); _engine->addComponentToEntity<TestComponent98>(entities[i], c98); _engine->addComponentToEntity<TestComponent99>(entities[i], c99); break;
            case 98: _engine->addComponentToEntity<TestComponent98>(entities[i], c98); _engine->addComponentToEntity<TestComponent99>(entities[i], c99); _engine->addComponentToEntity<TestComponent0>(entities[i], c0); break;
            case 99: _engine->addComponentToEntity<TestComponent99>(entities[i], c99); _engine->addComponentToEntity<TestComponent0>(entities[i], c0); _engine->addComponentToEntity<TestComponent1>(entities[i], c1); break;
            }
        }
    }
};

#endif
