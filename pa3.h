#ifndef pa3_h
#define pa3_h
#include <string>
#include <vector>


class Compiler {
private:
  //member variables
public:
  //member functions

};


class Stack {
private:
  std::vector<char> stackList;
public:
  char peek();
  void push(char item);
  void pop();
  bool isEmpty();
};

void Stack::push(char item){
  stackList.push_back(item);
}
void Stack::pop(){
  stackList.pop_back();
}

char Stack::peek(){
  return stackList.back();
}
bool Stack::isEmpty(){
  return stackList.empty();
}

#endif
