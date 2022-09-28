#pragma once

#include <iostream>
using namespace std;

template <class T>
struct StackNode
{
	T value;
	int priority = 0;

	StackNode<T>* next;
};

template <class T>
class PriorityStack
{
public:

	PriorityStack()
	{
		length = 0;
		head = nullptr;
	}

	// добавить элемент в стэк
	void Push(int priority, T value)
	{
		StackNode<T>* data = new StackNode<T>();
		data->value = value;
		data->priority = priority;
		if (IsEmpty())
		{
			head = data;
			++length;
			return;
		}
		++length;
		StackNode<T>* previous = nullptr;
		StackNode<T>* current = head;
		while (current)
		{
			if (priority >= current->priority)
			{
				data->next = current;
				if (previous != nullptr)
				{
					previous->next = data;
				}
				else
				{
					head = data;
				}
				return;
			}
			else if (current->next == nullptr)
			{
				current->next = data;
				data->next = nullptr;
				return;
			}
			previous = current;
			current = current->next;
		}
		previous->next = data;
		return;
	}

	// взять элемент из стэка с максимальным приоритетом
	T Pop()
	{
		if (IsEmpty())
		{
			throw length_error("Stack is empty!");
		}
		--length;
		T res = head->value;
		StackNode<T>* temp = head;
		head = head->next;
		delete temp;
		return res;
	}

	// проверяет, пустой ли стэк
	bool IsEmpty()
	{
		return length == 0;
	}

	// очищает стэк
	void Clear()
	{
		StackNode<T>* previous = nullptr;
		StackNode<T>* current = head;
		while (current)
		{
			previous = current;
			current = current->next;
			delete previous;
			--length;
		}
	}

	void PrintStack()
	{
		StackNode<T>* current = head;
		while (current)
		{
			cout << current->value << " " << current->priority;
			cout << endl;
			current = current->next;
		}
	}

	int Length()
	{
		return length;
	}

private:
	int length;
	StackNode<T>* head;
};
