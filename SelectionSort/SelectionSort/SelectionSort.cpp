#include <iostream>
using namespace std;

struct sHero
{
	char const* name_;
	unsigned level_;
};

inline bool operator<(const sHero& lhs, const sHero& rhs)
{
	return lhs.level_ < rhs.level_;
}

inline bool operator>(const sHero& lhs, const sHero& rhs)
{
	return rhs < lhs;
}

inline bool operator<=(const sHero& lhs, const sHero& rhs)
{
	return !(lhs > rhs);
}

inline bool operator>=(const sHero& lhs, const sHero& rhs)
{
	return !(rhs > lhs);
}

class Heroes
{
public:
	explicit Heroes(unsigned size);
	Heroes(const sHero*, unsigned size);
	Heroes(const std::initializer_list<sHero>&);
	~Heroes() { delete[] heroes_list_; }
	Heroes(Heroes&&) noexcept;

	Heroes(const Heroes&) = delete;
	Heroes& operator=(const Heroes&) = delete;
	Heroes& operator=(Heroes&&) = delete;

	sHero& operator[](unsigned);
	const sHero& operator[](unsigned) const;

	void removeElement(unsigned index);

	void printHeroesList() const;
	const unsigned size() const { return size_; }
private:
	sHero * heroes_list_;
	unsigned size_;
	void isIndexInRange(unsigned) const;
};

Heroes::Heroes(unsigned size)
	: heroes_list_{ new sHero[size] }
	, size_{ size }
{
}

Heroes::Heroes(const sHero* heroes, unsigned size)
{
	size_ = size;
	heroes_list_ = new sHero[size];
	for (unsigned i = 0; i < size; ++i)
		heroes_list_[i] = heroes[i];
}

Heroes::Heroes(const std::initializer_list<sHero>& heroes)
{
	size_ = heroes.size();
	heroes_list_ = new sHero[heroes.size()];
	unsigned index = -1;
	for (auto const & elem : heroes)
		heroes_list_[++index] = elem;
}

Heroes::Heroes(Heroes&& other) noexcept
	: heroes_list_{ other.heroes_list_ }
	, size_{ other.size_ }
{
	other.heroes_list_ = nullptr;
	other.size_ = 0;
}

sHero& Heroes::operator[](unsigned index)
{
	isIndexInRange(index);
	return heroes_list_[index];
}

const sHero& Heroes::operator[](unsigned index) const
{
	isIndexInRange(index);
	return heroes_list_[index];
}

void Heroes::removeElement(unsigned index)
{
	isIndexInRange(index);

	if (size_ > 1) {
		sHero* new_smaller_list = new sHero[size_ - 1];
		sHero* old_list_holder = heroes_list_;
		for (unsigned i = 0, j = 0; j < size_ - 1; ++i, ++j) {
			if (i != index || size_ == 1)
				new_smaller_list[j] = old_list_holder[i];
			else
				new_smaller_list[j] = old_list_holder[++i];
		}

		heroes_list_ = new_smaller_list;
		delete[] old_list_holder;
	}

	--size_;
}

void Heroes::printHeroesList() const
{
	for (unsigned i = 0; i < size_; ++i)
		cout << heroes_list_[i].name_ << " - " << heroes_list_[i].level_ << ".\n";
}

void Heroes::isIndexInRange(unsigned index) const
{
	if (index > size_ - 1)
		throw std::out_of_range("Index out of range");
}

unsigned findLowestLevel(const Heroes& heroes)
{
	sHero lowest_level = heroes[0];
	unsigned lowest_level_index = 0;
	for (unsigned i = 0; i < heroes.size(); ++i) {
		if (lowest_level >= heroes[i]) {
			lowest_level = heroes[i];
			lowest_level_index = i;
		}
	}
	return lowest_level_index;
}

Heroes selectionSort(Heroes&& heroes)
{
	Heroes sorted_heroes{ heroes.size() };
	unsigned lowest_level, index = 0;

	while (heroes.size() != 0) {
		lowest_level = findLowestLevel(heroes);
		sorted_heroes[index++] = heroes[lowest_level];
		heroes.removeElement(lowest_level);
	}

	return sorted_heroes;
}

int main()
{
	try {
		Heroes heroes{
			{ "Jaina", 25 },{ "Sonya", 64 },{ "Junkrat", 36 },
		{ "Genji", 100 },{ "Valla", 70 },{ "Maiev", 10 }
		};

		heroes.printHeroesList();

		std::cout << std::endl;

		selectionSort(std::move(heroes)
		).printHeroesList();
	}
	catch (const std::out_of_range& err) {
		std::cerr << err.what() << std::endl;
	}

	return 0;
}