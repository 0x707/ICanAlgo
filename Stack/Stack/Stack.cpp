#include <iostream>

struct sNode
{
	int value;
	sNode* other_node;
};

class Stack
{
public:
	Stack() : peak_{ nullptr }, elements_number_{ 0 } {}
	~Stack();

	Stack(const Stack&) = delete;
	Stack(Stack&&) = delete;
	Stack& operator=(const Stack&) = delete;
	Stack& operator=(Stack&&) = delete;

	unsigned push(int value);
	unsigned pop();
	int popAndGet();

	int getPeakValue() const;
private:
	sNode * peak_;
	unsigned elements_number_;
	friend void printStack(const Stack&);
};

Stack::~Stack()
{
	while (peak_ != nullptr) {
		sNode* to_remove = peak_;
		peak_ = peak_->other_node;
		delete to_remove;
	}
}

unsigned Stack::push(int value)
{
	sNode* new_node = new sNode{ value, nullptr };

	if (peak_ != nullptr)
		new_node->other_node = peak_;
	peak_ = new_node;

	return ++elements_number_;
}

unsigned Stack::pop()
{
	if (peak_ != nullptr) {
		sNode* node_to_remove = peak_;
		peak_ = peak_->other_node;
		delete node_to_remove;
		return --elements_number_;
	}
	throw std::domain_error("Error: empty stack");
}

int Stack::popAndGet()
{
	if (peak_ != nullptr) {
		int former_peak_value = getPeakValue();
		pop();
		return former_peak_value;
	}
	throw std::domain_error("Error: empty stack");
}

int Stack::getPeakValue() const
{
	if (peak_ != nullptr)
		return peak_->value;
	throw std::domain_error("Error: empty stack");
}

void printStack(const Stack& stack)
{
	if (stack.peak_ == nullptr)
		throw std::domain_error("Error: empty stack");

	sNode* hold_stack = stack.peak_;
	while (hold_stack != nullptr) {
		std::cout << hold_stack->value << ' ';
		hold_stack = hold_stack->other_node;
	}
}

int main()
{
	try {
		Stack stack;
		stack.push(9);
		std::cout << stack.push(3) << std::endl;
		stack.push(0);
		stack.push(7);
		stack.push(0);
		stack.push(7);
		printStack(stack);
		std::cout << std::endl;

		std::cout << stack.pop() << std::endl;
		printStack(stack);
		std::cout << std::endl;

		std::cout << stack.popAndGet() << std::endl;
		printStack(stack);
		std::cout << std::endl;
		std::cout << stack.popAndGet() << std::endl;
		printStack(stack);
	}
	catch (const std::domain_error& err) {
		std::cerr << err.what() << std::endl;
	}

	return 0;
}