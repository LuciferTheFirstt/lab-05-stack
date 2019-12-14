#include <iostream>


template <typename T>
class stack
{
  struct Node
    {
        T value;
        Node *next;
    };
   Node *top;
public:
  stack(): top(nullptr){};
  stack(const stack&) = delete;
  stack& operator=(const stack&) = delete;

  void push(T&& value)
   {
     Node *node = new Node;
     node->velue =p;
     node->next=top;
     top=node;
   }

  void push(const T& value)
  {
    Node *node = new Node;
    node->value = value;
    node->next = top;
    top = node;
  }

  void pop()
  {
   T value = top->value;
    Node *tmp = top;
    top = top->next;
    delete tmp;
  }

  const T& head() const
  {
   return top->value;
  }

  template <typename ... Args>

  void push_emplace(Args&&... value)
  {
    for (auto p : std::initializer_list<T>{value...})
    {
        Node *node = new Node;
        node->value = p;
        node->next = top;
        top = node;
    }
  }

  void push(T&& value)
  {
    Node *node = new Node;
    node->value = value;
    node->next = top;
    top = node;
  }

  T pop()
  {
   T value = top->value;
    Node *tmp = top;
    top = top->next;
    delete tmp;
    return value;
  }

  ~stack()
  {
    while (top)
    {
        Node *tmp = top;
        top = top->next;
        delete tmp;
    }
  }
};
