#include "pa3.h"
#include <iostream>
#include <fstream> //to read and write from files
#include <vector>
#include <map>
#include <iterator>

using namespace std;

int main(int argc, char** argv) {

  Stack* stack = new Stack();

  std::string fileLocation;
  std::cout<<"Please enter the name of the input file:"<<std::endl;
  std::cin>>fileLocation; //Must convert to cstring, returns const char array
  std::ifstream file(fileLocation.c_str()); //to get input from a filestream; take in location of file as param
  //method(argv[1])

  //Space delimited
  std::string line;
  while (file>>line) { //returns true if file
    std::cout<<line<<std::endl;
  }
  file.close();

  std::cout<<"The depth of nested loop(s) is "<<std::endl;
  std::cout<<"\nKeywords: "<<std::endl;
  std::cout<<"Identifier: "<<std::endl;
  std::cout<<"Constant: "<<std::endl;
  std::cout<<"Operators: "<<std::endl;
  std::cout<<"Delimiter: "<<std::endl;
  std::cout<<"\nSyntax Error(s): "<<std::endl;

}
