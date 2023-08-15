#pragma once

#ifndef LEXER
#define LEXER

#include "Forward.h"
#include <algorithm>

enum TokenType {
  EQUALS,
  END,
  _STRING,
  KEYWORD,
  IDENTIFIER,
};

class Token {
  public:
    TokenType type;
    const char* ch;

    Token(TokenType _type, const char* _ch) : type(_type), ch(_ch) {}
};

class Lexer {
  public:
    const char* code;
    unsigned short position;
    std::vector<Token> tokens;
    std::string buffer;
    std::vector<char> special_chars;
    
    Lexer(const char* _code, std::vector<char> _special_chars) : code(_code),  position(0), special_chars(_special_chars) {
      cout << "[LEXER] Lexer object created" << endl;
    }

    char inline Current() {
      return code[position];
    }

    bool handle_possible_keyword(const char* str) {
      return false;
    }

    bool Next() {
      position++;
      if(code[position] == 0)
        return false;
      return true;
    }

    bool is_special_char(char ch) {
      if(std::find(special_chars.begin(), special_chars.end(), ch) == special_chars.end())
        return false;
      return true;
    }

    bool handle_special_char(char ch) {
      switch(ch) {
        case '=':
          {
            cout << "[LEXER] EQUALS" << endl;
            tokens.push_back(Token(EQUALS, &ch));
            return true; break;
          };
        case ';':
          {
            cout << "[LEXER] SEMICOLON" << endl;
            tokens.push_back(Token(END, &ch));
            return true; break;
          };
        case ' ':
          {
            return true; break;
          };
      };

      return false;
    }

    bool NextToken() {
      cout << "[LEXER] NextToken() called" << endl;
      cout << "[LEXER] Actual char: " << Current() << endl << endl;
      if(is_special_char(Current())) {
        handle_special_char(Current());
        if(!Next())
          return false;
        return true;
      }
      
      while(! (is_special_char(Current())) ) {
        buffer += Current();
        if(!Next()) {
          return false;
        }
      }
      
      cout << "[LEXER] Valid buffer found: " << buffer << endl;

      if(!(handle_possible_keyword(buffer.c_str()))) {
        tokens.push_back(Token(_STRING, buffer.c_str()));
      }

      buffer.clear();
      
      if(!Next())
        return false;

      return true;
    }
};

#endif
