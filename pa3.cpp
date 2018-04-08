#include "pa3.h"
#include <iostream>
#include <string>
#include <fstream> //to read and write from files
#include <vector>
#include <map>
#include <iterator>

using namespace std;

void Stack::push(std::string item){
  stackList.push_back(item);
}
void Stack::pop(){
  stackList.pop_back();
}

std::string Stack::peek(){ //returns the last elemnt in the stack
  return stackList.back();
}
bool Stack::isEmpty(){
  return stackList.empty();
}

void checkKeyword(std::ifstream& file, Stack* stack) {
  std::string line;
  char currChar;
  std::string possKey;

  while (file.get(currChar)) { //returns true if file
    if (isupper(currChar) != 0) {  //if the char is uppercase
      if (file.peek() == ' ' || file.peek() == '\n') { //if next char is a space or new line
      //if ((currChar + 1) != ' ' && !file.eof()) {
         //std::cout<<currChar;
         possKey+=currChar;
         std::cout<<"pushing "<<possKey<<" to stack"<<std::endl;
         stack->push(possKey);
         possKey = "";
     }
     else {
       possKey+=currChar;
       //append to string
     }
      //check if it is a keyword
  }
 }
}

int main() {

  Stack* stack = new Stack();

  std::string fileLocation;
  std::cout<<"Please enter the name of the input file:"<<std::endl;
  std::cin>>fileLocation; //Must convert to cstring, returns const char array
  std::ifstream file(fileLocation.c_str()); //to get input from a filestream; take in location of file as param

  if (file) {
    checkKeyword(file, stack);
  }
 else {
   std::cout<<"This file does not exist"<<std::endl;
   return -1;
 }

 file.close();

 std::cout<<"\nThe depth of nested loop(s) is "<<std::endl;
 std::cout<<"\nKeywords: "<<std::endl;
 std::cout<<"Identifier: "<<std::endl;
 std::cout<<"Constant: "<<std::endl;
 std::cout<<"Operators: "<<std::endl;
 std::cout<<"Delimiter: "<<std::endl;
 std::cout<<"\nSyntax Error(s): "<<std::endl;

  return 0;
}
