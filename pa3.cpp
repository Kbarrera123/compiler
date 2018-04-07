#include "pa3.h"
#include <iostream>
#include <string>
#include <fstream> //to read and write from files
#include <vector>
#include <map>
#include <iterator>

using namespace std;

int main(int argc, char** argv) {

  Stack* stack = new Stack();
  std::string line;
  char currChar;
  //char str[] = "test";
  std::string possKey;

  std::string fileLocation;
  std::cout<<"Please enter the name of the input file:"<<std::endl;
  std::cin>>fileLocation; //Must convert to cstring, returns const char array
  std::ifstream file(fileLocation.c_str()); //to get input from a filestream; take in location of file as param
  //method(argv[1])
  if (file) {
   //Space delimited
   while (file.get(currChar)) { //returns true if file
     // std::cout<<line<<std::endl;
     //std::cout<<charExists;
     //currChar = str[i];
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
  file.close();
 }
 else {
   std::cout<<"This file does not exist"<<std::endl;
   return -1;
 }

 std::cout<<"\nThe depth of nested loop(s) is "<<std::endl;
 std::cout<<"\nKeywords: "<<std::endl;
 std::cout<<"Identifier: "<<std::endl;
 std::cout<<"Constant: "<<std::endl;
 std::cout<<"Operators: "<<std::endl;
 std::cout<<"Delimiter: "<<std::endl;
 std::cout<<"\nSyntax Error(s): "<<std::endl;



  return 0;
}
