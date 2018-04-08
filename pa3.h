#ifndef pa3_h
#define pa3_h
#include <string>
#include <vector>

using namespace std;

class Stack {
private:
  std::vector<std::string> stackList;
public:
  std::string peek();
  void push(std::string item);
  void pop();
  bool isEmpty();
};


#endif
