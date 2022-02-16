//
// Created by Gautam Saha on 16/02/22.
//


#include "Lexer.hpp"
#include <iostream>
#include <cstdio>

using namespace std;
using namespace fastlexer;

int main(){

  try {
    FILE *fh = fopen("/Users/gautamsaha/Desktop/projects/fast/code/hello.fast", "r");
    if (!fh) { cerr << "Can't find file." << endl; }
    fseek(fh, 0, SEEK_END);
    size_t fileSize = ftell(fh);
    fseek(fh, 0, SEEK_SET);
    string fileContents(fileSize, ' ');
    fread(fileContents.data(), 1, fileSize, fh);

    cout << fileContents << endl << endl;

    Lexer lexer;
    vector<Token> tokens = lexer.parse(fileContents);

    for (const auto& t : tokens) {
      t.debugPrint();
    }
  } catch (exception& err) {
    cerr << "Error: " << err.what() << endl;
    return 2;
  }

  return 0;
}


