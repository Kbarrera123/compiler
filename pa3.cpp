#include "pa3.h"
#include <iostream>
#include <string>
#include <fstream> //to read and write from files
#include <vector>
#include <unordered_set>
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

std::string checkDelimiters(std::ifstream& file) { //Returns a string containing the delimeters
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

void checkIdentifiers(std::ifstream& file) {
  char currChar;
  std::string possId;
  std::unordered_set<std::string> idList;

  file.clear();
  file.seekg(0, ios::beg);  //Clear file and go back to beginning

  while (file.get(currChar)) {
    if (islower(currChar)) { //if char is lowercase
      possId+=currChar;
      if (!islower(file.peek())) { //if next char is not another lowercase char
        idList.insert(possId); //add it to unordered set
        possId = "";
      }
    }
  }

  for (std::unordered_set<std::string>::iterator it=idList.begin(); it != idList.end(); ++it) {
    std::cout<<*it<<" "; //print each value of set (they are all unique)
  }

}

void checkConstants(std::ifstream& file) {
  char currChar;
  std::string possConst;
  std::unordered_set<std::string> constList;

  file.clear();
  file.seekg(0, ios::beg);  //Clear file and go back to beginning

  while (file.get(currChar)) {
    if (isdigit(currChar) != 0) { //if char is a digit
      possConst+=currChar; //append it to a string
      if (!isdigit(file.peek()) ) { //if next char is not another number
        constList.insert(possConst); //add it to unordered set
        possConst = "";
      }
    }
  }

  for (std::unordered_set<std::string>::iterator it=constList.begin(); it != constList.end(); ++it) {
    std::cout<<*it<<" "; //print each value of set (they are all unique)
  }

}

void checkParentheses(std::ifstream& file) { //Print mismatched parens
  char currChar;
  int balance = 0;
  //postive = extra open parens
  //negative = extra closed parens

  file.clear();
  file.seekg(0, ios::beg);  //Clear file and go back to beginning

  while (file.get(currChar)) {
    if (currChar == '(') {
      balance++;
    }
    else if (currChar == ')') {
      balance--;
    }
  }

  while (balance < 0) { //is negative
    std::cout<<")";
    balance++;
  }

  while (balance > 0) {
    std::cout<<"(";
    balance--;
  }

}

int checkKeywords(std::ifstream& file, Stack* stack) {
  char currChar;
  std::string possKey;
  int depth = 0;

  while (file.get(currChar)) { //returns true if file
    if (isupper(currChar)) {  //if the char is uppercase
      if (!isupper(file.peek())) { //if next char is not an uppercase char
        possKey+=currChar;
        if(possKey.compare("END") == 0) {
          if (!stack->isEmpty()) {
            std::cout<<"popping "<<stack->peek()<<std::endl;
            stack->pop(); //pop BEGIN
            if (!stack->isEmpty()) {
              std::cout<<"popping "<<stack->peek()<<std::endl;
              stack->pop(); //pop FOR
            }
            else {
              std::cout<<"Cannot pop; stack is now empty"<<std::endl;
            }
            possKey = "";
          }
          else {
            std::cout<<"Cannot pop; stack is empty."<<std::endl;
            break;
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

 return depth;

}

int main() {

  Stack* stack = new Stack();

  std::string fileLocation;
  std::cout<<"Please enter the name of the input file:"<<std::endl;
  std::cin>>fileLocation; //Must convert to cstring, returns const char array
  std::ifstream file(fileLocation.c_str()); //to get input from a filestream; take in location of file as param

  if (file) {

    std::cout<<"\nThe depth of nested loop(s) is "<<checkKeywords(file, stack)<<std::endl;
    std::cout<<"\nKeywords: "<<std::endl;
    std::cout<<"Identifier: ";
    checkIdentifiers(file);
    std::cout<<"\nConstant: ";
    checkConstants(file);
    std::cout<<"\nOperators: ";
    checkOperators(file);
    std::cout<<"\nDelimiter: "<<checkDelimiters(file)<<std::endl;
    std::cout<<"\nSyntax Error(s): ";
    checkParentheses(file);
    std::cout<<"\n\n"<<std::endl;

  }
 else {
   std::cout<<"This file does not exist"<<std::endl;
   return -1;
 }
 file.close();
 return 0;

}
