#include <iostream>
#include <memory>

template <typename T>
class Stack
{
public:
	Stack(){

		this->capacity = this->st_capacity;
	 	this->size = 0;
		this->st_ptr.reset(new T [this->st_capacity]);
	}

	Stack( const Stack& ) = delete;
	Stack& operator=( const Stack& ) = delete;

	Stack( Stack&& );
	Stack& operator=( Stack&& );

	void push( T&& value )
	{
		if (this->isFull()) {
        		throw std::logic_error("Stack is full");
    		}
    		this->size++;
    		std::unique_ptr<T> new_st(new T [this->capacity]);

    		for(int i = 0; i < this->size - 1; i++) {
        		new_st.get()[i] = this->st_ptr.get()[i];
    		}
    		new_st.get()[this->size - 1] = std::move(value);

		this->st_ptr.swap(new_st);
	}

	void push( const T& value )
	{
		if (this->isFull()){
        		throw std::logic_error("Stack is full");
    		}
    		this->size++;

    		std::unique_ptr<T> new_st(new T [this->capacity]);

		for(int i = 0; i < this->size - 1; i++) {
        		new_st.get()[i] = this->st_ptr.get()[i];
    		}
    		new_st.get()[this->size - 1] = value;

    		this->st_ptr.swap(new_st);
	}
	
	const T& head() const
	{
		if (!this->isEmpty())
    			return this->st_ptr.get()[this->size - 1];
    		else
        		throw std::logic_error("Stack is empty");
	}

	bool isEmpty() const {
     		return this->size == 0;
	}

	bool isFull() const {
	     return this->size > 65536;
	}

	template <typename ... Args>
	void push_emplace( Args&&... value )
	{
		T args [] = {value...};

    		for(const auto& e: args) {
        		this->push(e);
    		}
	}

	T pop()
	{
		if(!this->isEmpty()) {
        		this->size--;
    		}
    		else
        		throw std::logic_error("Stack is empty");
	}

	~Stack()= default;

private:
	static const unsigned int st_capacity = 16;
	unsigned int capacity;
	unsigned char size;
	std::unique_ptr<T> st_ptr;
};


template<typename T>
Stack<T>::Stack( Stack&& r)
{
	std::swap(this->capacity, r.capacity);
	std::swap(this->size, r.size);
	std::swap(this->arr_ptr, r.arr_ptr);
}

template<typename T>
Stack<T>& Stack<T>::operator=( Stack&& r )
{
	if(std::move(r) != this) {
        	std::swap(this->capacity, r.capacity);
        	std::swap(this->size, r.size);
        	std::swap(this->arr_ptr, r.arr_ptr);
    	}

    	return *this;
}

