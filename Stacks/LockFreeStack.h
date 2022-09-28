#pragma once
#include <optional>
#include <vector>
#include <mutex>
#include <thread>

template <class T>
class LockFreeStack
{
public:
	// ����������� ����� � �������� ��������
	LockFreeStack(int capacity)
	{
		stack->resize(capacity);
	}
	// �������� ������� � ����
	void Push(T value)
	{
		mutex.lock();
		stack->at(length) = value;
		++length;
		mutex.unlock();
	}
	// ����� ������� �� ����� � ������������ �����������
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
	// ���������, ������ �� ����
	bool IsEmpty()
	{
		return length == 0;
	}
	// ������� ����
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