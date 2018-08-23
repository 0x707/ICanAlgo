#include <iostream>

namespace {

	template<typename T>
	T max(const T& first, const T& second)
	{
		return first > second ? first : second;
	}

	template<typename T>
	T min(const T& first, const T& second)
	{
		return first < second ? first : second;
	}
}

int euclideanAlgorithm(int first, int second)
{
	if (first == 0)
		return second;
	if (second == 0)
		return first;

	int greater = max(first, second);
	int lower = min(first, second);
	int remainder = greater % lower;
	return euclideanAlgorithm(lower, remainder);
}

int main()
{
	std::cout << euclideanAlgorithm(1680, 640) << std::endl;
	std::cout << euclideanAlgorithm(1680, 540) << std::endl;
	std::cout << euclideanAlgorithm(1680, 17) << std::endl;
	return 0;
}