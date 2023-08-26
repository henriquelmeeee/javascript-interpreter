#pragma once

#include "../Forward.h"
#include "../AST/Main.h"
#include "../Lexer/Lexer.h"

class Parser {
  public:
    std::vector<Token*> m_tokens;
    Token* m_actual_token;
    int m_position = 0;

    Parser(std::vector<Token*> tokens) : m_tokens(tokens) {}

    Token Current() {
      return *(m_tokens[m_position]);
    }

    Token Next() {
      ++m_position;
      return *(m_tokens[m_position]);
    }

    Token Previous() {
      --m_position;
      return *(m_tokens[m_position]);
    }

    void HandleVariable() {
      Next();
      if(Current().m_type != Identifier) {
        throw_err("ParseError: Expected 'Identifier' after variable declaration", Crash);
      }

      if(Next().m_type != Equals) {
        std::cout << "[+] Parser found VariableDeclaration\n";
      }
    }

    void HandleKeyword() {
      if(Current().m_value == "var")
        HandleVariable();
      throw_err(std::string("ParseError: Invalid keyword").c_str(), Crash);
    }

    bool parse() {
      while(Current().m_type != Eof) {
        switch(Current().m_type) {
          case Keyword:
            HandleKeyword();
            break;
          default:
            throw_err("ParseError: Unexpected token", Crash);
        };
      }

      return true;
    }
};
