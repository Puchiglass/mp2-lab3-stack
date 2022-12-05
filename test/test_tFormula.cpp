#include "gtest.h"
#include "TFormula.h"

TEST(TArithmeticExpression, can_create_expression)
{
  string ex = "(a+b*c)*(c/d-e)";
  ASSERT_NO_THROW(TArithmeticExpression example(ex));
}

TEST(TArithmeticExpression, can_get_infix_form_of_expression)
{
  string ex = "(a+b*c)*(c/d-e)";
  TArithmeticExpression example(ex);
  EXPECT_EQ(ex, example.GetInfix());
}

TEST(TArithmeticExpression, can_get_postfix_form_of_expression)
{
  string ex1 = "(ab+b*c)*(c/d-e)";
  string ex2 = "1+22*(3-2)-4";
  string ex3 = "1+2/(30-3)";
  TArithmeticExpression example1(ex1);
  TArithmeticExpression example2(ex2);
  TArithmeticExpression example3(ex3);

  EXPECT_EQ("ab b c * + c d / e - * ", example1.GetPostfix());
  EXPECT_EQ("1 22 3 2 - * + 4 - ", example2.GetPostfix());
  EXPECT_EQ("1 2 30 3 - / + ", example3.GetPostfix());
}

TEST(TArithmeticExpression, can_get_operands_of_expression_without_const_and_with_one_symb)
{
  string str = "(a+b*c)*(c/d-e)";
  TArithmeticExpression example(str);
  ASSERT_NO_THROW(example.GetOperands());
  vector<string> res;
  vector<string> ex = example.GetOperands();
  res.push_back("a");
  res.push_back("b");
  res.push_back("c");
  res.push_back("d");
  res.push_back("e");
  for (int i = 0; i < 5; i++)
    EXPECT_EQ(res[i], ex[i]);
}

TEST(TArithmeticExpression, can_get_operands_of_expression_without_const_and_with_several_symb)
{
  string str = "(apo+b*cn)*(cn/d-e)";
  TArithmeticExpression example(str);
  ASSERT_NO_THROW(example.GetOperands());
  vector<string> res;
  vector<string> ex = example.GetOperands();
  res.push_back("apo");
  res.push_back("b");
  res.push_back("cn");
  res.push_back("d");
  res.push_back("e");
  for (int i = 0; i < 5; i++)
    EXPECT_EQ(res[i], ex[i]);
}

TEST(TArithmeticExpression, can_get_operands_of_expression_with_one_const_and_with_one_symb)
{
  string str = "(a+b*c)*(6/d-e)";
  TArithmeticExpression example(str);
  ASSERT_NO_THROW(example.GetOperands());
  vector<string> res;
  vector<string> ex = example.GetOperands();
  res.push_back("6");
  res.push_back("a");
  res.push_back("b");
  res.push_back("c");
  res.push_back("d");
  res.push_back("e");
  for (int i = 0; i < 5; i++)
    EXPECT_EQ(res[i], ex[i]);
}

TEST(TArithmeticExpression, can_get_operands_of_expression_with_consts_and_with_several_symb)
{
  string str = "(20+bp*c)*(17.64/d-em)";
  TArithmeticExpression example(str);
  ASSERT_NO_THROW(example.GetOperands());
  vector<string> res;
  vector<string> ex = example.GetOperands();
  res.push_back("17.64");
  res.push_back("20");
  res.push_back("bp");
  res.push_back("c");
  res.push_back("d");
  res.push_back("em");
  for (int i = 0; i < 5; i++)
    EXPECT_EQ(res[i], ex[i]);
}

TEST(TArithmeticExpression, can_calculate_expession_without_const)
{
  string str = "(a+b*c)*(c/d-e)";
  TArithmeticExpression example(str);
  map<string, double> op;
  op.emplace("a", 2.0);
  op.emplace("b", 4.0);
  op.emplace("c", 7.0);
  op.emplace("d", 6.0);
  op.emplace("e", 5.0);
  double res = example.Calculate(op);
  EXPECT_EQ(-114, int(res));
}

TEST(TArithmeticExpression, can_calculate_expession_with_const)
{
  string str = "(a+b*c)*(12.67/d-e)";
  TArithmeticExpression example(str);
  map<string, double> op;
  op.emplace("a", 2.0);
  op.emplace("b", 4.0);
  op.emplace("c", 7.0);
  op.emplace("d", 6.0);
  op.emplace("e", 5.0);
  double res = example.Calculate(op);
  EXPECT_EQ(-86, int(res));
}