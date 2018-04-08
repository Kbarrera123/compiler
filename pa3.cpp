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

std::string Stack::peek(){ //returns the last element in the stack
  return stackList.back();
}
bool Stack::isEmpty(){
  return stackList.empty();
}

void checkOperators(std::ifstream& file) { //Prints out each unique operator
  char currChar;
  bool hasPlus = false;
  bool hasMinus = false;
  bool hasMulti = false;
  bool hasEqual = false;
  bool hasInc = false;
  bool hasDiv = false;

  file.clear();
  file.seekg(0, ios::beg);

  while (file.get(currChar)) {
    switch (currChar){
      case '+':
        if (file.peek() == '+') { //if increment operator
          hasInc = true;
          file.seekg(1, std::ios::cur); //move to next char to skip the second +
        }
        else { //if just single plus
          hasPlus = true;
        }
        continue;
      case '-':
        hasMinus = true;
        continue;
      case '/':
        hasDiv = true;
        continue;
      case '*':
        hasMulti = true;
        continue;
      case '=':
        hasEqual = true;
        continue;
      default:
        continue;
    }
  }

  if (hasPlus) {
    std::cout<<"+ ";
  }
  if (hasMinus) {
    std::cout<<"- ";
  }
  if (hasDiv) {
    std::cout<<"/ ";
  }
  if (hasEqual) {
    std::cout<<"= ";
  }
  if (hasInc) {
    std::cout<<"++ ";
  }
  if (hasMulti) {
    std::cout<<"* ";
  }

}

std::string checkDelimiter(std::ifstream& file) { //Returns a string containing the delimeters
  char currChar;
  bool hasSpace = false;
  bool hasSemicolon = false;
  bool hasComma = false;
  std::string delimString;

  file.clear();
  file.seekg(0, ios::beg);  //Clear file and go back to beginning

  while (file.get(currChar)) {
    if (currChar == ' ') {
      hasSpace = true;
    }
    if (currChar == ';') {
      hasSemicolon = true;
    }
    if (currChar == ',') {
      hasComma = true;
    }
  }

  if (hasSpace) {
    delimString+=' ';
  }
  if (hasSemicolon) {
    delimString+=';';
  }
  if (hasComma) {
    delimString+=',';
  }

  return delimString;
}

void checkKeyword(std::ifstream& file, Stack* stack) {
  std::string line;
  char currChar;
  std::string possKey;

  while (file.get(currChar)) { //returns true if file
    if (isupper(currChar) != 0) {  //if the char is uppercase
      if (file.peek() == ' ' || file.peek() == '\n') { //if next char is a space or new line
        possKey+=currChar;
        if(possKey.compare("END") == 0) {
          if (!stack->isEmpty()) {
            std::cout<<"popping "<<stack->peek()<<std::endl;
            stack->pop(); //pop BEGIN
            std::cout<<"popping "<<stack->peek()<<std::endl;
            stack->pop(); //pop FOR
            possKey = "";
          }
          else {
            std::cout<<"Cannot pop; stack is empty."<<std::endl;
            return;
          }
        }
        else { //if not "END", push the keyword to the stack
          std::cout<<"pushing "<<possKey<<" to stack"<<std::endl;
          stack->push(possKey);
          possKey = "";
        }
     }
     else { //if no space, continue appending the char to a string
       possKey+=currChar;
     }
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

    std::cout<<"\nThe depth of nested loop(s) is "<<std::endl;
    std::cout<<"\nKeywords: "<<std::endl;
    std::cout<<"Identifier: "<<std::endl;
    std::cout<<"Constant: "<<std::endl;
    std::cout<<"Operators: ";
    checkOperators(file);
    std::cout<<"\nDelimiter: "<<checkDelimiter(file)<<std::endl;
    std::cout<<"\nSyntax Error(s): "<<std::endl;
  }
 else {
   std::cout<<"This file does not exist"<<std::endl;
   return -1;
 }
 file.close();
 return 0;

}
