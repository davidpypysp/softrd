#include "stdafx.h"
#include "CppUnitTest.h"

#include "clipping.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace softrd;

namespace softrd_test
{
	TEST_CLASS(Clipping)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			vec4 v1(3, 3, 3, 5);
			vec4 v2(1, 1, 1, -3);
			LinePrimitive line;
			line.v[0].position = v1;
			line.v[1].position = v2;
			bool flag = ClipLineNegativeW(&line);
		}

		TEST_METHOD(TestMethod2)
		{
			int a = 1;
			int b = 2;
			Assert::AreEqual(a, 1);
		}

	};
}