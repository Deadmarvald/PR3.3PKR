#include "pch.h"
#include "CppUnitTest.h"
#include "../PR3.3PKR/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UT33PKR
{
	TEST_CLASS(UT33PKR)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int t;
			int N = 3;
			Note* n = new Note[N];

			n[0].secondname = "1";

			t = Search(n, N, "1");

			Assert::AreEqual(t, -1);
		}
	};
}