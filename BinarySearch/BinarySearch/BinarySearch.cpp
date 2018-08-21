#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int binarySearch(const vector<int>& vec, int target)
{
	if (vec.size() == 0)
		return -1;

	int low = 0;
	int high = vec.size() - 1;

	while (low <= high) {
		int mid = (low + high) / 2;

		if (target > vec[mid])
			low = mid + 1;
		else if (target < vec[mid])
			high = mid - 1;
		else
			return mid;
	}
	return -1;
}

int main()
{
	vector<int> l_test_vec{ 1,2,3,4,5,6,7,8,9 };
	vector<int> l_test_vec_empty{};
	cout << binarySearch(l_test_vec, 8) << endl;
	cout << binarySearch(l_test_vec, 88) << endl;
	cout << binarySearch(l_test_vec_empty, 1) << endl;

	return 0;
}