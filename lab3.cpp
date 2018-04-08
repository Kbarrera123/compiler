#include <iostream>
#include <fstream> //to read and write from files
#include <vector>
#include <map>
#include <iterator>


int main() {
  //prints exactly as in files
  //By input
  std::string fileLocation;
  std::cout<<"Please input file name"<<std::endl;
  std::cin>>fileLocation; //Must convert to cstring, returns const char array
  std::ifstream file(fileLocation.c_str()); //to get input from a filestream; take in location of file as param

  std::string word;
  std::map<std::string, int> wordFrequency;

  while (file>>word) {
    wordFrequency[word]++; //hashes the word, increases frequency, does everything

  }
  for(std::map<std::string, int>::iterator it=wordFrequency.begin(); it != wordFrequency.end(); ++it) {
    std::cout<<it->first<<" Frequency: "<<it->second<<std::endl;
  }
  file.close();

  return 0;
}

//Hash map:: unordered set, takes in value pair
//Next week: Parsing unordered set
//Don't have to worry about printing each frequency
