#pragma once

#include "TStack.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

bool isDigit(string& p);
vector<string> split(const string& s, char delim, vector<string>& res);

class TArithmeticExpression
{
protected:
  string infix;
  string postfix;
  vector<string> lexems;
  map<char, int> priority;

  void Parse();
  void ToPostfix();

public:
  TArithmeticExpression(string infx);

  string GetInfix() const;
  string GetPostfix() const;

  map<string, double> operands;

  vector<string> GetOperands() const;
  double Calculate(const map<string, double>& values);
};



void TArithmeticExpression::Parse()
{
  string temp;
  string tmp;

  for (char it : infix)
  {
    if (it != '(' && it != ')' && it != '+' && it != '-' && it != '*' && it != '/')
    {
      tmp += it;
    }
    else
    {
      if (tmp.size() != 0)
      {
        lexems.push_back(tmp);
        tmp.clear();
      }

      temp.clear();
      temp += it;
      lexems.push_back(temp);
    }
  }

  if (tmp.size() != 0)
  {
    lexems.push_back(tmp);
    tmp.clear();
  }
}

void TArithmeticExpression::ToPostfix()
{
  Parse();
  TStack<char> opst(lexems.size() * 2);
  
  for (auto& i : lexems)
  {
    switch (i[0])
    {
    case '(':
      opst.Push(i[0]);
      break;

    case ')':
      while (opst.Top() != '(')
      {
        postfix += opst.Pop();
        postfix += ' ';
      }
      opst.Pop();
      break;

    case '+': case '-': case '*': case '/':
      if (opst.isEmpty() || priority[i[0]] > priority[opst.Top()])
        opst.Push(i[0]);
      else
      {
        while (priority[opst.Top()] >= priority[i[0]])
        {
          postfix += opst.Pop();
          postfix += ' ';
        }
        opst.Push(i[0]);
      }
      break;

    default:
      if (isDigit(i))
      {
        operands.emplace(i, stod(i));
        postfix += i;
        postfix += ' ';
        break;
      }
      else
        operands.emplace(i, 0.0);
      
      postfix += i;
      postfix += ' ';
    }
  }
  
  while (!opst.isEmpty())
  {
    postfix += opst.Pop();
    postfix += ' ';
  }
}

TArithmeticExpression::TArithmeticExpression(string infx) : infix(infx)
{
  priority = { {'(', 0}, {')', 1}, {'+', 2}, {'-', 2}, {'*', 3}, {'/', 3} };
  ToPostfix();
}

string TArithmeticExpression::GetInfix() const
{
  return infix;
}

string TArithmeticExpression::GetPostfix() const
{
  return postfix;
}

vector<string> TArithmeticExpression::GetOperands() const
{
  vector<string> op;
  for (const auto& i : operands)
    op.push_back(i.first);
  return op;
}

double TArithmeticExpression::Calculate(const map<string, double>& values)
{
  if (values.size() == 0) throw "Expression can't be calculcaleted";

  vector<string> oper = GetOperands();
  map<string, double> variables;
  
  for (auto& it : oper)
  {
    if (it != "")
    {
      if (it[0] != '(' && it[0] != ')' && it[0] != '+' && it[0] != '-' && it[0] != '*' && it[0] != '/')
      {
        if (variables.find(it) != variables.end() && operands[it] == 0.0)
          variables.emplace(it, values.at(it));
        else
        {
          if (isDigit(it))
            variables.emplace(it, stod(it));
          else
            variables.emplace(it, values.at(it));
        }
      }
    }
  }

  TStack<double> st(postfix.size());
  double leftOperand, rightOperand;
  vector<string> spl;
  split(postfix, ' ', spl);
  
  for (auto& lex : spl)
  {
    switch (lex[0])
    {
    case '+':
      rightOperand = st.Pop();
      leftOperand = st.Pop();
      st.Push(leftOperand + rightOperand);
      break;
    
    case '-':
      rightOperand = st.Pop();
      leftOperand = st.Pop();
      st.Push(leftOperand - rightOperand);
      break;
    
    case '*':
      rightOperand = st.Pop();
      leftOperand = st.Pop();
      st.Push(leftOperand * rightOperand);
      break;
    
    case '/':
      rightOperand = st.Pop();
      leftOperand = st.Pop();
      st.Push(leftOperand / rightOperand);
      break;
    
    default:
      st.Push((variables[lex]));
    }
  }
  
  return st.Pop();
}

bool isDigit(string& p)
{
  size_t size = p.size();

  if (size >= 2 && p[0] == '0')
    return false;

  for (int i = 0; i < size; i++)
  {
    if (p[i] >= '0' && p[i] <= '9')
      continue;
    else if (p[i] == '.')
    {
      int j = 0;
      while (j != i)
      {
        if (p[j] < '0' || p[j] > '9')
          return false;
        else
          j++;
      }
    }
    else
      return false;
  }
  
  return true;
}

vector<string> split(const string& s, char delim, vector<string>& res)
{
  if (res.size() != 0)
    res.clear();
  string tmp;
  
  for (auto& it : s)
  {
    if (it != delim)
      tmp += it;
    else
    {
      if (tmp.size() != 0)
        res.push_back(tmp);
      tmp.clear();
    }
  }

  if (tmp.size() != 0)
    res.push_back(tmp);
  
  return res;
}