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

bool checkParentheses(std::ifstream& file, bool printErrors) { //Print mismatched parens
  char currChar;
  bool isBalanced = false;
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

  if (balance == 0) {
    isBalanced = true;
  }

  if (printErrors) { //only print if in syntax error mode
    while (balance < 0) { //is negative
      std::cout<<") ";
      balance++;
    }

    while (balance > 0) {
      std::cout<<"( ";
      balance--;
    }
  }

  return isBalanced;

}

std::string checkKeywords(std::ifstream& file, bool printKeywords) {
  char currChar;
  std::string possKey;
  std::string wrongKey;
  std::unordered_set<std::string> keywordList;

  file.clear();
  file.seekg(0, ios::beg);  //Clear file and go back to beginning

  while (file.get(currChar)) {
    if (isupper(currChar)) {
      possKey+=currChar;
      if (!isupper(file.peek())) { //if next char is not uppercase, end that possKey
        if (possKey.compare("BEGIN") == 0 || possKey.compare("END") == 0 || possKey.compare("FOR") == 0) {
          keywordList.insert(possKey);
          possKey = "";
        }
        else {
          possKey+=" ";
          wrongKey+=possKey;
          possKey = "";
        }
      }
    }
  }

  if (printKeywords) {
    for (std::unordered_set<std::string>::iterator it=keywordList.begin(); it != keywordList.end(); ++it) {
      std::cout<<*it<<" "; //print each value of set (they are all unique)
    }
  }

  return wrongKey;
}

void keywordErrorHelper(std::ifstream& file) {
  std::cout<<checkKeywords(file, false);
}

void checkLoops(std::ifstream& file, Stack* stack, bool wantDepth) {
  char currChar;
  std::string possKey = "";
  int currDepth = 0;
  int tempDepth = 0;
  int maxDepth = 0;
  bool justPopped = false;
  bool parensBalance = checkParentheses(file, false);

  if (!stack->isEmpty()) {
    std::cout<<"stack is not empty"<<std::endl;
  }

  file.clear();
  file.seekg(0, ios::beg);  //Clear file and go back to beginning

  while (file.get(currChar)) {
    if (isupper(currChar)) {
      possKey+=currChar;
      if (!isupper(file.peek())) { //if next char is not uppercase, end that possKey
        if (possKey.compare("FOR") == 0) { //push fors
          stack->push(possKey);
          possKey = "";
        }
        else if (possKey.compare("BEGIN") == 0) { //push begins
          stack->push(possKey);
          possKey = "";
          if (justPopped) {
            justPopped = false;
            continue;
          }
          if (parensBalance) {
            currDepth++;
          }
        }
        else if (possKey.compare("END") == 0 && stack->peek().compare("BEGIN") == 0) {
          //If you get end and have a begin
          stack->pop(); //pop the begin
          stack->pop(); //pop the for
          justPopped = true;
          possKey = "";
          currDepth--;
          tempDepth++;
          if (currDepth == 0 && tempDepth > maxDepth) {
            maxDepth = tempDepth;
          }
        }
        else if (possKey.compare("END") == 0 && stack->peek().compare("BEGIN") != 0) {
          //if you get end and no begin
          if (!wantDepth) {
            std::cout<<"BEGIN"<<std::endl;
          }
          stack->pop(); //pop the for
          possKey = "";
        }
        else { //If keyword is misspelled, ignore and start over
          possKey = "";
        }
      }
    }
  }

  while (!stack->isEmpty()) {
    if (!wantDepth) {
        std::cout<<"END"<<std::endl;
    }
    if (stack->peek().compare("FOR") == 0) {
      stack->pop();
    }
    else if (stack->peek().compare("BEGIN") == 0) {
      stack->pop();
      stack->pop();
    }
  }

  if (wantDepth) {
    std::cout<<maxDepth<<std::endl;
  }

}

int main() {

  Stack* stack = new Stack();

  std::string fileLocation;
  std::cout<<"Please enter the name of the input file:"<<std::endl;
  std::cin>>fileLocation; //Must convert to cstring, returns const char array
  std::ifstream file(fileLocation.c_str()); //to get input from a filestream; take in location of file as param

  if (file) {

    std::cout<<"\nThe depth of nested loop(s) is ";
    checkLoops(file, stack, true);
    std::cout<<"\n\nKeywords: ";
    checkKeywords(file, true);
    std::cout<<"\nIdentifier: ";
    checkIdentifiers(file);
    std::cout<<"\nConstant: ";
    checkConstants(file);
    std::cout<<"\nOperators: ";
    checkOperators(file);
    std::cout<<"\nDelimiter: "<<checkDelimiters(file)<<std::endl;
    std::cout<<"\nSyntax Error(s): ";
    keywordErrorHelper(file);
    checkParentheses(file, true);
    checkLoops(file, stack, false);
    std::cout<<"\n\n"<<std::endl;

  }
 else {
   std::cout<<"This file does not exist"<<std::endl;
   return -1;
 }
 file.close();
 return 0;

}
