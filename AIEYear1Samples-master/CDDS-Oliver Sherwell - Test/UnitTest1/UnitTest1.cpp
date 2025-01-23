#include "pch.h"
#include "CppUnitTest.h"

#include "DynamicArray.h"
#include "HashTable.h"
#include "Critter.h"

#include "raylib.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(HashTableTest)
	{
	public:
		
		TEST_METHOD(SquidsTest) {
			Texture2D Squiddies = LoadTexture("../CDDS_Optimise/res/9.png");

			HashTable tablehash;
			tablehash["Squids"] = &Squiddies;

			Assert::AreSame(tablehash["Squids"]->id, Squiddies.id);
		}

		TEST_METHOD(JelliesTest) {
			Texture2D Jellyfish = LoadTexture("../CDDS_Optimise/res/10.png");

			HashTable tablehash;
			tablehash["jellies"] = &Jellyfish;

			Assert::AreSame(tablehash["jellies"]->id, Jellyfish.id);
		}
	};

	TEST_CLASS(DynamicArrayTest) {

	public:

		TEST_METHOD(Adding)
		{

			DynamicArray critterArray;
			Critter crits;

			for (int i = 0; i < 10; i++) { // Will add 10 critters to the array 
				critterArray.PushBack(crits);
			}

			Assert::AreEqual(true, critterArray[9].IsDead());
		}
	};
}
