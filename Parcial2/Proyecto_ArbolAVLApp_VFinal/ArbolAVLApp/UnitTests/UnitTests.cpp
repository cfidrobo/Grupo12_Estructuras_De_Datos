#include "pch.h"
#include "CppUnitTest.h"
#include "../funciones.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(TestMethod1) {
			std::string cedula1 = "1725906968";
			std::string cedula2 = "1725906969";

			Assert::IsTrue(Funciones::cedula_valida(cedula1));
			Assert::IsFalse(Funciones::cedula_valida(cedula2));
		}
		
		TEST_METHOD(TestMethod2) {
			std::string a = "hola";
			std::string b = " hola ";
			Assert::IsTrue(Funciones::cadenas_iguales(a, b));
		}
	};
}
