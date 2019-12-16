#include <iostream>

template <typename T>
struct Node
{
	T value;
	Node* next;
};

template <typename T>
class Stack
{
public:
	Stack() : top( nullptr ) {};

	Stack( const Stack& ) = delete;
	Stack& operator=( const Stack& ) = delete;

	Stack( Stack&& );
	Stack& operator=( Stack&& );

	void push( T&& value )
	{
		Node<T>* node = new Node<T>();
		node->value = std::move(value);
		node->next = top;
		top = node;
	}

	void push( const T& value )
	{
		Node<T>* node = new Node<T>();
		node->value = value;
		node->next = top;
		top = node;
	}
	
	const T& head() const
	{
		return top->value;
	}

	Node<T>* get_top() const
	{
		return top;
	}

	void reset()
	{
		top = nullptr;
	}

	template <typename ... Args>
	void push_emplace( Args&&... value )
	{
		for( auto p : std::initializer_list<T>{ value... } )
		{
			Node<T>* node = new Node<T>();
			node->value = p;
			node->next = top;
			top = node;
		}
	}

	T pop()
	{
		T value = top->value;
		Node<T>* tmp = top;
		top = top->next;
		delete tmp;
		return value;
	}

	~Stack()
	{
		while( top )
		{
			Node<T>* tmp = top;
			top = top->next;
			delete tmp;
		}
	}

private:
	Node<T>* top;
};


template<typename T>
Stack<T>::Stack( Stack&& r)
{
	this->top = r.get_top();
	r.reset();
}

template<typename T>
Stack<T>& Stack<T>::operator=( Stack&& r )
{
	this->top = r.get_top();
	r.reset();
	return *this;
}

