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
  std::vector<std::string> stackList;
public:
  std::string peek();
  void push(std::string item);
  void pop();
  bool isEmpty();
};

void Stack::push(std::string item){
  stackList.push_back(item);
}
void Stack::pop(){
  stackList.pop_back();
}

std::string Stack::peek(){
  return stackList.back();
}
bool Stack::isEmpty(){
  return stackList.empty();
}

#endif
