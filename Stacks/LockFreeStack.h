#pragma once
#include <optional>
#include <vector>
#include <mutex>
#include <thread>

template <class T>
class LockFreeStack
{
public:
	// конструктор стэка с заданной емкостью
	LockFreeStack(int capacity)
	{
		stack->resize(capacity);
	}
	// добавить элемент в стэк
	void Push(T value)
	{
		mutex.lock();
		stack->at(length) = value;
		++length;
		mutex.unlock();
	}
	// взять элемент из стэка с максимальным приоритетом
	T Pop()
	{
		mutex.lock();
		if (length == 0)
		{
			throw std::length_error("Stack is empty!");
		}
		--length;
		auto temp = stack->at(length).value();
		stack->at(length) = std::nullopt;
		mutex.unlock();
		return temp;
	}
	// проверяет, пустой ли стэк
	bool IsEmpty()
	{
		return length == 0;
	}
	// очищает стэк
	void Clear()
	{
		clearLock.lock();
		if (length == 0)
		{
			clearLock.unlock();
			return;
		}
		for (int i = length - 1; i >= 0; --i)
		{
			stack->at(i) = std::nullopt;
			--length;
		}
		clearLock.unlock();
	}
private:
	std::vector<std::optional<T>>* stack = new vector<std::optional<T>>();
	std::atomic<int> length = 0;
	std::mutex mutex;
	std::mutex clearLock;
};