//
// Created by Gautam Saha on 16/02/22.
//

#include "Lexer.hpp"
#include <iostream>
#include <stdexcept>

namespace fastlexer {
using namespace std;


vector<Token> Lexer::parse(const string &inFunMain) {

  vector<Token> tokens;
  static Token currToken;
  currToken.token_line_number = 1;

  for (char c : inFunMain) {

    if (currToken.token_type == ESCAPE_SEQUENCE) {

      switch (c) {

      case 'n':
      case 'r':
      case 't':
      case '\\':
        currToken.token_text.append(string("\\") + c);
        break;

      default:
        throw runtime_error(string("unknown escape sequence \\") +
                            string(1, c) + " in string on Line: " +
                            to_string(currToken.token_line_number)+".");

      }

      currToken.token_type=STRING;
      continue;
    }

    switch (c) {

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':

      if (currToken.token_type == WHITESPACE)
        currToken.token_type = INTEGER;

      currToken.token_text.append(1, c);
      break;

    // operators
    case '{':
    case '}':
    case '(':
    case ')':
    case '[':
    case ']':
    case '=':
    case ';':

      if (currToken.token_type != STRING) {

        endToken(currToken,tokens);
        currToken.token_type = OPERATOR;
        currToken.token_text.append(1, c);
        endToken(currToken,tokens);

      } else
        currToken.token_text.append(1, c);

      break;

    // white spaces
    case ' ':
    case '\t':
      if (currToken.token_type == STRING) {
        currToken.token_text.append(1,c);
      } else endToken(currToken,tokens);
      break;

    // new line
    case '\r':
    case '\n':
      endToken(currToken,tokens);
      ++currToken.token_line_number;
      break;

      // strings

    case '"':
      if (currToken.token_type != STRING) {

        endToken(currToken,tokens);
        currToken.token_type = STRING;
      } else if (currToken.token_type == STRING)
        endToken(currToken,tokens);
      break;

      // back slash
    case '\\':
      if (currToken.token_type == STRING) {
        currToken.token_type = ESCAPE_SEQUENCE;
      } else {
        endToken(currToken,tokens);
        currToken.token_type = OPERATOR;
        currToken.token_text.append(1, c);
        endToken(currToken,tokens);
      }
      break;

    default:
      auto curr = currToken.token_type;
      if(curr == WHITESPACE || curr == INTEGER){

        endToken(currToken,tokens);
        currToken.token_type=IDENTIFIER;
        currToken.token_text.append(1,c);

      }else currToken.token_text.append(1,c);
      break;
    }
  }
  endToken(currToken,tokens);
  return tokens;
}
void Lexer::endToken(Token &token, vector<Token> &tokens) {

  if (token.token_type != WHITESPACE) {
    tokens.push_back(token);
  }

  token.token_type = WHITESPACE;
  token.token_text.erase();
}

void Token::debugPrint() const  {
  cout << "Token(" << sTokenTypeStrings[token_type] << ", \"" << token_text << "\", " << token_line_number << ")" << endl;
}

} // namespace fastlexer
