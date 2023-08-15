#pragma once

#ifndef PARSER
#define PARSER

#include "Forward.h"
#include "AST.h"
#include "Scope.h"
#include "Lexer.h"
#include "Variable.h"

class Parser {
  public:
    std::vector<Token> tokens;
    unsigned int current;
    Program* program;

    Scope* main_scope;
    Scope* actual_scope;

    std::vector<ASTNode*> main_elements;

    Parser(std::vector<Token> _tokens) : tokens(_tokens) {
      this->program = new Program();
      this->main_scope = new Scope(main_elements, (ForwardScope*)nullptr);
      program->append(this->main_scope);
      this->actual_scope = this->main_scope;
    }

    Token Current() {
      return tokens[current];
    }

    Token PreviousToken() {
      return tokens[current-1];
    }

    void NextToken() {
      if(tokens.size()-1 < current+1) {
        cout << "EOL not found\n"; exit(1);
      }
      ++current;
    }

    void Consume(TokenType type) {
      if(tokens[current].type == type)
        return;
      cout << "Expected '" << type << "', get '" << tokens[current].type << "'\n";
      exit(1);
    }

    bool match(TokenType type) {
      if(tokens[current].type == type)
        return true;
      return false;
    }
    
    bool DeclareLocalVariable() {
      actual_scope->append((ASTNode*)new Variable(Value(true), new Identifier("teste")));
      cout << "DeclareVariable()" << endl;
      return true;
    }

    bool DeclareAndInitializeVariable() {
      return false;
    }

    bool execute() {
      switch(Current().type) {
        case KEYWORD:
          {
            NextToken();
            if(match(IDENTIFIER)) {
              NextToken();
              if(match(END)) {
                DeclareLocalVariable();
              } else if(match(EQUALS)) {
                NextToken();
                DeclareAndInitializeVariable();
              }
            };
            break;
          };
        case END:
          return false;
      };
      return true;
    }

};

#endif
