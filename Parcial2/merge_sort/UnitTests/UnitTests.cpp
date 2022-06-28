#include "pch.h"
#include "CppUnitTest.h"
#include "../arreglo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:

		TEST_METHOD(TestArreglo)
		{
			Arreglo<int> arreglo;

			Assert::AreEqual(0, arreglo.tamano());

			arreglo.agregar(1);
			arreglo.agregar(2);
			arreglo.agregar(3);
			arreglo.agregar(4);
			arreglo.agregar(5);

			Assert::AreEqual(3, arreglo.obtener(2));
			Assert::AreEqual(5, arreglo.tamano());
		}
		
		TEST_METHOD(TestOrdenamiento)
		{
			Arreglo<int> arreglo;

			arreglo.agregar(3);
			arreglo.agregar(1);
			arreglo.agregar(2);

			arreglo.ordenar();

			int n1 = arreglo.obtener(0);
			int n2 = arreglo.obtener(1);
			int n3 = arreglo.obtener(2);

			Assert::AreEqual(1, n1);
			Assert::AreEqual(2, n2);
			Assert::AreEqual(3, n3);
		}
	};
}
