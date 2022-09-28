#include "pch.h"
#include "CppUnitTest.h"
#include "../Stacks/PriorityStack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StackUnitTests
{
	TEST_CLASS(StackUnitTests)
	{
	public:
		TEST_METHOD(EmptyTest)
		{
			PriorityStack<string>* stack = new PriorityStack<string>();
			Assert::IsTrue(stack->IsEmpty());
		}

		TEST_METHOD(NonEmptyTest)
		{
			PriorityStack<string>* stack = new PriorityStack<string>();
			stack->Push(42, "text");
			Assert::IsFalse(stack->IsEmpty());
		}

		TEST_METHOD(ClearTest)
		{
			PriorityStack<string>* stack = new PriorityStack<string>();
			stack->Push(42, "text");
			stack->Clear();
			Assert::AreEqual(true, stack->IsEmpty());
		}

		TEST_METHOD(EmptyStackPopExceptionTest)
		{
			PriorityStack<string>* stack = new PriorityStack<string>();
			auto func = [stack] { stack->Pop(); };
			Assert::ExpectException<std::length_error>(func);
		}

		TEST_METHOD(LengthTest)
		{
			PriorityStack<int>* stack = new PriorityStack<int>();
			stack->Push(1, 1);
			stack->Push(1, 2);
			stack->Push(1, 3);
			stack->Push(1, 4);
			stack->Push(1, 41);
			stack->Pop();
			stack->Pop();
			Assert::AreEqual(3, stack->Length());
		}

		TEST_METHOD(StringStackTest)
		{
			PriorityStack<string>* stack = new PriorityStack<string>();
			stack->Push(4, "champions,");
			stack->Push(1, "friend");
			stack->Push(3, "my");
			stack->Push(10, "We");
			stack->Push(4, "the");
			stack->Push(4, "are");

			string result = stack->Pop();
			result.append(" " + stack->Pop());
			result.append(" " + stack->Pop());
			result.append(" " + stack->Pop());
			result.append(" " + stack->Pop());
			result.append(" " + stack->Pop());

			string assert = "We are the champions, my friend";
			Assert::AreEqual(assert, result);
		}

		TEST_METHOD(StringStackTest2)
		{
			PriorityStack<string>* stack = new PriorityStack<string>();
			stack->Push(1, "one");
			stack->Push(1, "two");
			stack->Push(2, "second priority");
			stack->Push(3, "first priority");
			stack->Push(1, "three");

			string result = stack->Pop();
			result.append(" " + stack->Pop());
			result.append(" " + stack->Pop());
			result.append(" " + stack->Pop());
			result.append(" " + stack->Pop());

			string assert = "first priority second priority three two one";
			Assert::AreEqual(assert, result);
		}
	};
}
