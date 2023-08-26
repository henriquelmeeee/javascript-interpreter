#pragma once

#include "../Forward.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cctype>

bool isNumeric(const std::string& str) {
  return std::all_of(str.begin(), str.end(), ::isdigit);
}

enum TokenType {
  Identifier,
  Numeric,
  Keyword,
  Equals,
  Semicolon,
  LeftParen,
  RightParen,
  Eof,
};

std::vector<char> special_chars = {';', ' ', '=', '+', '-', '*', '/', '%', '(', ')'};

class Token {
  public:
    TokenType m_type;
    std::string m_value;

    Token(TokenType type, std::string value) : m_type(type), m_value(value) {
    }

};

class Lexer {
  private:
    unsigned int position = 0;
    std::string buffer;

  public:
    const char* code;
    std::vector<Token*> tokens;
    
    Lexer(const char* _code) : code(_code) {}

    char Current() {
      return code[position];
    }

    bool Next() {
      ++position;
      return true;
    }

    bool NextToken() {
      char current = Current();
      if(!current)
        return false;

      switch(current) {
        case '=':
          {
            tokens.push_back(new Token(Equals, "="));
            Next();
            std::cout << "[+] Token: Equals\n";
            return true;
          };
        case ';':
          {
            tokens.push_back(new Token(Semicolon, ";"));
            Next();
            std::cout << "[+] Token: Semicolon\n";
            return true;
          };
        case ' ':
          {
            Next();
            return true;
          };
        default:
          break;
      }

      while(std::find(special_chars.begin(), special_chars.end(), Current()) == special_chars.end()) {
        buffer.push_back(Current());
        Next();
      }
      
      if(buffer == "var") {
        tokens.push_back(new Token(Keyword, "var"));
        std::cout << "[+] Token: Keyword (var)\n";
      } else {
        if(isNumeric(buffer)) {
          tokens.push_back(new Token(Numeric, buffer.c_str()));
          std::cout << "[+] Token: Numeric (" << buffer << ")\n";   
        } else {
          tokens.push_back(new Token(Identifier, buffer.c_str()));
          std::cout << "[+] Token: Identifier (" << buffer << ")\n";
        }
      }
      buffer.clear();

      return true;


    }

    std::vector<Token*> run() {
      while(NextToken());
      tokens.push_back(new Token(Eof, nullptr));
      return tokens;
    }
};
