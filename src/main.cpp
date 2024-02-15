#include <iostream>
#include <string>

class Exp {};
class Stm {};

class IdExp : public Exp {
public:
  std::string id;
  IdExp(std::string i) : id(i) {}
};

class NumExp : public Exp {
public:
  int num;
  NumExp(int n) : num(n) {}
};

class OpExp : public Exp {
public:
  Exp* left;
  Exp* right;
  int oper;
  static int Plus, Minus, Times, Div;
  OpExp(Exp* l, int o, Exp* r) : left(l), right(r), oper(o) {}
};

class EseqExp : public Exp {
public:
  Stm* stm;
  Exp* exp;
  EseqExp(Stm* s, Exp* e) : stm(s), exp(e) {}
};

class ExpList {};

class PairExpList : public ExpList {
public:
  Exp* head;
  ExpList* tail;
  PairExpList(Exp* h, ExpList* t) : head(h), tail(t) {}
};

class LastExpList : public ExpList {
public:
  Exp* head;
  LastExpList(Exp* h) : head(h) {}
};

class CompoundStm : public Stm {
public:
  Stm* stm1;
  Stm* stm2;
  CompoundStm(Stm* s1, Stm* s2) : stm1(s1), stm2(s2) {}
};

class AssignStm : public Stm {
public:
  std::string id;
  Exp* exp;
  AssignStm(std::string i, Exp* e) : id(i), exp(e) {}
};

class PrintStm : public Stm {
public:
  ExpList* exps;
  PrintStm(ExpList* e) : exps(e) {}
};

int OpExp::Plus = 1, OpExp::Minus = 2, OpExp::Times = 3, OpExp::Div = 4;

int main(int argc, char const* argv[]) {
    Stm* prog = new CompoundStm(
        new AssignStm("a", new OpExp(new NumExp(5), OpExp::Plus, new NumExp(3))),
        new CompoundStm(
            new AssignStm(
                "b", new EseqExp(
                         new PrintStm(new PairExpList(
                             new IdExp("a"),
                             new LastExpList(new OpExp(
                                 new IdExp("a"), OpExp::Minus, new NumExp(1))))),
                         new OpExp(new NumExp(10), OpExp::Times, new IdExp("a")))),
            new PrintStm(new LastExpList(new IdExp("b")))));

    std::cout << "hi" << "\n";
    return 0;
}