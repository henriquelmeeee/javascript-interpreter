#pragma once

#ifndef LEXER
#define LEXER

#include "Forward.h"
#include <algorithm>

enum TokenType {
  EQUALS,
  END,
  STRING,
};

class Token {
  public:
    TokenType type;
    const char* ch;

    Token(TokenType _type, const char* _ch) : type(_type), ch(_ch) {}
};

extern std::vector<char> special_chars;

class Lexer {
  public:
    const char* code;
    unsigned short position;
    std::vector<Token> tokens;
    std::string buffer;
    
    Lexer(const char* _code) : code(_code),  position(0) {
      cout << "Lexer object created" << endl;
    }

    char inline Current() {
      return code[position];
    }

    bool handle_possible_keyword(const char* str) {
      return true;
    }

    bool Next() {
      ++position;
      if(code[position] == 0)
        return false;
      return true;
    }

    bool is_special_char(char ch) {
      if(std::find(special_chars.begin(), special_chars.end(), special_chars) == special_chars.end())
        return false;
      return true;
    }

    bool handle_special_char(char ch) {
      switch(ch) {
        case '=':
          {
            cout << "EQUALS token found" << endl;
            tokens.push_back(Token(EQUALS, &ch));
            return true; break;
          };
        case ';':
          {
            cout << "SEMICOLON token found" << endl;
            tokens.push_back(Token(END, &ch));
            return true; break;
          };
      };

      return false;
    }

    bool NextToken() {
      cout << "NextToken() called" << endl;
      if(is_special_char(Current())) {
        handle_special_char(Current());
        if(!Next())
          return false;
        return true;
      }
      
      while(!is_special_char(Current())) {
        buffer += Current();
        if(!Next())
          return false;
      }

      if(!(handle_possible_keyword(buffer.c_str()))) {
        tokens.push_back(Token(STRING, buffer.c_str()));
      }

      if(!Next())
        return false;

      return true;

    }
};

#endif
