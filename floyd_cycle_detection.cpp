#include <iostream>

struct LLNode
{
	LLNode* NextNode;
	int Value;

	explicit LLNode(int InValue = 0)
		: NextNode(nullptr)
		, Value(InValue)
	{
	}
};

LLNode* CreateLoopingList(int Entries, int LoopPosition)
{
	if (Entries < 1)
		return nullptr;

	LLNode* const StartNode = new LLNode(1);
	LLNode* CurrentNode = StartNode;
	LLNode* LoopStart = nullptr;

	std::cout << "Creating Node 1 at address " << CurrentNode << std::endl;
	if (LoopPosition == 1)
	{
		LoopStart = CurrentNode;
	}

	for (int i = 2; i <= Entries; ++i)
	{
		CurrentNode->NextNode = new LLNode(i);
		CurrentNode = CurrentNode->NextNode;
		std::cout << "Creating Node " << i << " at address " << CurrentNode << std::endl;
		if (LoopPosition == i)
		{
			LoopStart = CurrentNode;
		}
	}

	// If we know where to loop, set our last element to point into the loop start
	if (LoopStart)
	{
		std::cout << "Pointing Node " << CurrentNode->Value << " at address " << LoopStart << std::endl;
		CurrentNode->NextNode = LoopStart;
	}

	return StartNode;
}

LLNode* FindLoopingPoint(LLNode* const StartNode)
{
	if (!StartNode)
		return nullptr;

	// If the node points at itself, we found the loop
	if (StartNode->NextNode == StartNode)
		return StartNode;

	LLNode* Iterator1 = StartNode;
	LLNode* Iterator2 = StartNode;

	while (true)
	{
		// If we hit a nullptr, we don't have an infinite loop
		Iterator1 = Iterator1->NextNode;
		Iterator2 = Iterator2->NextNode;
		if (!Iterator2)
			return nullptr;
		Iterator2 = Iterator2->NextNode;

		if (!Iterator1 || !Iterator2)
			return nullptr;

		if (Iterator1 == Iterator2)
			break;
	}

	Iterator1 = StartNode;

	while (true)
	{
		// Let N be the node where we meet
		// Our loop is at Node N-1
		if (Iterator1 == Iterator2)
			return Iterator2;

		Iterator1 = Iterator1->NextNode;
		Iterator2 = Iterator2->NextNode;
	}
}

void DeleteLoopingList(LLNode* const StartNode)
{
	if (StartNode == nullptr)
		return;

	LLNode* CurrentNode = StartNode;

	// Break our loop if we have one
	LLNode* StartOfLoop = FindLoopingPoint(StartNode);
	if (StartOfLoop)
	{
		bool bEnteredLoop = false;

		while (CurrentNode)
		{
			if (CurrentNode->NextNode == StartOfLoop)
			{
				if (!bEnteredLoop)
				{
					bEnteredLoop = true;
				}
				else
				{
					std::cout << "Clearing Loop at Node " << CurrentNode << " pointing at " << CurrentNode->NextNode << std::endl;
					CurrentNode->NextNode = nullptr;
					break;
				}
			}
			CurrentNode = CurrentNode->NextNode;
		}
	}

	// Can now delete the list until there are no more nodes
	CurrentNode = StartNode;
	while (CurrentNode)
	{
		LLNode* NextNode = CurrentNode->NextNode;
		std::cout << "Deleting Node " << CurrentNode->Value << " at " << CurrentNode << " with next node of " << CurrentNode->NextNode << std::endl;
		delete CurrentNode;
		CurrentNode = NextNode;
	}
}

void RunProgram(int Entries, int LoopEntry)
{
	std::cout << "Attempting to create a linked-list of " << Entries << " nodes, with a loop at " << LoopEntry << std::endl;

	LLNode* LinkedList = CreateLoopingList(Entries, LoopEntry);
	if (!LinkedList)
	{
		std::cout << "Could not create a list with a size of " << Entries << std::endl;
	}
	else
	{
		LLNode* LoopNode = FindLoopingPoint(LinkedList);
		if (LoopNode)
		{
			std::cout << "Loop detected at node " << LoopNode << " which has a value of " << LoopNode->Value << std::endl;
		}
		else
		{
			std::cout << "No loop detected" << std::endl;
		}

		DeleteLoopingList(LinkedList);
	}

	std::cout << "Finished" << std::endl << std::endl;
}

int main(int argc, char* argv[])
{
	// Run our simulation under a few different settings
	RunProgram(7, 4);
	RunProgram(7, 3);
	RunProgram(10, 5);
	RunProgram(10, 1);
	RunProgram(10, 9);
	RunProgram(10, 10);
	RunProgram(1, 1);
	RunProgram(1, -1);
	RunProgram(2, -1);

	// Test bad values
	RunProgram(0, 0);
	RunProgram(-1, -1);
	return 0;
}
