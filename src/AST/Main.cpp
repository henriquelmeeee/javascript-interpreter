#include "Main.h"

Value ASTNode::execute(Scope *s) {
  return Value(false);
}

Value Identifier::execute(Scope *s) {
  //return s->GetVariableByName(m_identifier);
  return Value(Null);
}

Value ExpressionStatement::execute(Scope* s) {
  return m_expression->execute(s);
}

Value AssignmentExpression::execute(Scope *s) {
  auto lhs_result = m_lhs->execute(s);
  auto rhs_result = m_rhs->execute(s);

  switch(m_op) {
    case Plus:
      {
        //return Value(Value(lhs_result + rhs_result));
        return Value(Null);
        break;
      };

    default:
      {
        return Value(Null);
      };
  }
}

Value VariableDeclaration::execute(Scope* s) {
  //return s->SetVariable(name, value);
  return Value(Null);
};
