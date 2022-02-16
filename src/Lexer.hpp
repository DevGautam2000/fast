//
// Created by Gautam Saha on 16/02/22.
//

#pragma once
#include <vector>
#include <string>


namespace fastlexer{

using namespace std;

enum TokenType{
  WHITESPACE,
  IDENTIFIER,
  INTEGER,
  STRING,
  OPERATOR,
  ESCAPE_SEQUENCE
};

static const char *sTokenTypeStrings[] = {
    "WHITESPACE",
    "IDENTIFIER",
    "INTEGER",
    "STRING",
    "OPERATOR",
    "ESCAPE_SEQUENCE"
};

class Token{
public:
  enum TokenType token_type{WHITESPACE};
  string token_text;
  size_t token_line_number{0};

  void debugPrint() const ;

};

class Lexer{

public:
  vector<Token>  parse(const string &inFunMain);

private:
  static void endToken(Token &token,vector<Token> &tokens) ;
};
}