#include "PriorityStack.h"
#include "LockFreeStack.h"
using namespace std;

int main()
{    
	PriorityStack<string>* stack = new PriorityStack<string>();
	stack->Push(2, "Archer");
	stack->Push(7, "Angel");
	stack->Push(3, "Griffin");
	stack->Push(2, "Stone Gargoyle");
	stack->Push(3, "Roc");
	stack->Push(7, "Behemoth");
	stack->Push(5, "Genie");
	stack->Push(6, "Psychic Elemental");
	stack->Push(1, "Gnoll");
	cout << "Stack: " << endl;
	stack->PrintStack();
	cout << endl;
	cout << "Length: " << stack->Length();
	stack->Clear();
}