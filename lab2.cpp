#include <iostream>
#include <fstream> //to read and write from files
#include <vector>

void addWord(std::string word, std::vector<std::string> &wordList, std::vector<int> &frequency) {
  std::cout<<"This is working"<<std::endl;
  for (int i = 0; i < wordList.size(); i++) {
    if (word == wordList[i]) {
      frequency[i]++;
      return;
    }
  }
  wordList.push_back(word);
  frequency.push_back(1);
}

int main() {
  std::string fileLocation;
  std::cout<<"Please input file name"<<std::endl;
  std::cin>>fileLocation; //Must convert to cstring, returns const char array
  std::ifstream file(fileLocation.c_str()); //to get input from a filestream; take in location of file as param

  std::string word;
  std::vector<std::string> wordList;
  std::vector<int> frequency;

  while (file>>word) {
    addWord(word, wordList, frequency);
  }
  for (int i = 0; i < wordList.size(); i++) {
    std::cout<<wordList[i]<<"Frequency"<<frequency[i]<<std::endl;
  }
  file.close();

  return 0;
}
