#include <stdio.h>
#include "pch.h"
#include "CppUnitTest.h"
#include "../Stacks/LockFreeStack.h"
#include <thread>
#include <string>
#define N 10
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace StackUnitTests
{
	struct ThreadArg
	{
		int id;
		LockFreeStack<int>* stack;
	};

	void AddToStack(ThreadArg* data)
	{
		LockFreeStack<int>* stack = data->stack;
		int id = data->id;
		stack->Push((long)id);
	}

	LockFreeStack<int>* FillStack(LockFreeStack<int>* stack)
	{
		for (int id = N - 1; id >= 0; id--) {
			ThreadArg* data = new ThreadArg();
			data->id = id;
			data->stack = stack;

			thread thr(AddToStack, data);
			thr.join();
		}
		return stack;
	}

	void Pop(LockFreeStack<int>* stack, string *result)
	{
		result->append(to_string(stack->Pop()));
		result->append(" ");
	}

	string PopStack(LockFreeStack<int>* stack)
	{
		string result = "";
		for (int id = N - 1; id >= 0; id--) {
			thread thr(Pop, stack, &result);
			thr.join();
		}
		return result;
	}

	void ClearStack(LockFreeStack<int>* stack)
	{
		stack->Clear();
	}

	TEST_CLASS(StackUnitTests)
	{
	public:
		TEST_METHOD(AddTest)
		{
			LockFreeStack<int>* stack = new LockFreeStack<int>(N);

			stack = FillStack(stack);
			string result = "";
			for (int id = 1; id <= N; id++)
			{
				result.append(to_string(stack->Pop()));
				result.append(" ");
			}
			string assert = "0 1 2 3 4 5 6 7 8 9 ";
			Assert::AreEqual(assert, result);
		}

		TEST_METHOD(EmptyTest)
		{
			LockFreeStack<int>* stack = new LockFreeStack<int>(N);

			stack = FillStack(stack);
			for (int id = 1; id <= N; id++)
			{
				stack->Pop();
			}
			Assert::IsTrue(stack->IsEmpty());
		}

		TEST_METHOD(ClearTest)
		{
			LockFreeStack<int>* stack = new LockFreeStack<int>(N);
			Assert::IsTrue(stack->IsEmpty());

			stack = FillStack(stack);
			Assert::IsFalse(stack->IsEmpty());
			stack->Clear();
			Assert::IsTrue(stack->IsEmpty());
		}

		TEST_METHOD(EmptyStackPopExceptionTest)
		{
			LockFreeStack<int>* stack = new LockFreeStack<int>(N);
			auto func = [stack] { stack->Pop(); };
			Assert::ExpectException<std::length_error>(func);
		}

		TEST_METHOD(PopTest)
		{
			LockFreeStack<int>* stack = new LockFreeStack<int>(N);
			stack = FillStack(stack);
			string result = PopStack(stack);
			string assert = "0 1 2 3 4 5 6 7 8 9 ";
			Assert::AreEqual(assert, result);
		}
	};
};