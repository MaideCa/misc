
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void MergeSort(vector<T>& InList)
{
	if (InList.size() < 2)
	{
		return;
	}

	const size_t HalfSize = (InList.size() / 2) + ((InList.size() % 2) ? 0 : 1);

	vector<T> Left;
	Left.reserve(HalfSize);
	vector<T> Right;
	Right.reserve(HalfSize);

	for (size_t i = 0; i < InList.size(); ++i)
	{
		if ((i % 2) == 0)
		{
			Left.push_back(InList[i]);
		}
		else
		{
			Right.push_back(InList[i]);
		}
	}

	MergeSort(Left);
	MergeSort(Right);

	InList = MergeVectorsSorted(Left, Right);
}

template<typename T>
vector<T> MergeVectorsSorted(const vector<T>& A, const vector<T>& B)
{
	vector<T> SortedVector;

	if (A.empty())
	{
		SortedVector = B;
		return SortedVector;
	}
	else if (B.empty())
	{
		SortedVector = A;
		return SortedVector;
	}

	SortedVector.reserve(A.size() + B.size());

	size_t AIndex = 0;
	size_t BIndex = 0;

	while (AIndex < A.size() && BIndex < B.size())
	{
		if (A[AIndex] <= B[BIndex])
		{
			SortedVector.push_back(A[AIndex]);
			++AIndex;
		}
		else
		{
			SortedVector.push_back(B[BIndex]);
			++BIndex;
		}
	}

	for (; AIndex < A.size(); ++AIndex)
	{
		SortedVector.push_back(A[AIndex]);
	}
	for (; BIndex < B.size(); ++BIndex)
	{
		SortedVector.push_back(B[BIndex]);
	}

	return SortedVector;
}

int main()
{
	vector<int> MyUnsortedVec = {1, 9, 100, 4, 8, 7, 2, 8, -1};
	MergeSort(MyUnsortedVec);
	for (const auto& Value : MyUnsortedVec)
	{
		cout << Value << endl;
	}
}

