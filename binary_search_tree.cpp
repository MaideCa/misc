#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

class BSTNode
{
public:
	BSTNode* Left;
	BSTNode* Right;
	int Value;

public:
	BSTNode(int InValue = 0)
		: Left(nullptr)
		, Right(nullptr)
		, Value(InValue)
	{
	}

	~BSTNode()
	{
		delete Left;
		delete Right;
	}

	void AddValueToTree(int ValueToAdd);
	BSTNode* FindNode(int ValueToFind);
};

void BSTNode::AddValueToTree(int ValueToAdd)
{
	if (ValueToAdd < Value)
	{
		if (Left)
		{
			Left->AddValueToTree(ValueToAdd);
		}
		else
		{
			Left = new BSTNode(ValueToAdd);
		}
	}
	else if (ValueToAdd > Value)
	{
		if (Right)
		{
			Right->AddValueToTree(ValueToAdd);
		}
		else
		{
			Right = new BSTNode(ValueToAdd);
		}
	}
}

BSTNode* BSTNode::FindNode(int ValueToFind)
{
	if (ValueToFind < Value)
	{
		return (Left) ? Left->FindNode(ValueToFind) : nullptr;
	}
	else if (ValueToFind > Value)
	{
		return (Right) ? Right->FindNode(ValueToFind) : nullptr;
	}

	return this;
}

int main(int argc, char* argv[])
{
	const int StartingNumber = 10;
	BSTNode Tree = BSTNode(StartingNumber);

	// Add some values to our tree
	std::vector<int> ValueList = {1, 4, 14, 20, 0, -10, 100, -100, 13, 19, 99, 101};
	for (int Value : ValueList)
	{
		Tree.AddValueToTree(Value);
	}
	ValueList.emplace_back(StartingNumber);

	// Seed random with current time
	std::srand(static_cast<unsigned int>(std::time(0)));

	const int ValueToFind = ValueList.at(std::rand() % ValueList.size());

	BSTNode* FoundValue = Tree.FindNode(ValueToFind);
	if (FoundValue)
	{
		std::cout << "Found value " << ValueToFind << " at node " << FoundValue << std::endl;
	}
	else
	{
		std::cout << "Could not find value " << ValueToFind << std::endl;
	}

	return 0;
}
