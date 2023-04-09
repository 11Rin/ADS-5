// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
const int size = 100;
int getPrior(char ch) {
  switch (ch) {
    case '(':
      return 0;
    case ')':
      return 1;
    case '+':
      return 2;
    case '-':
      return 2;
    case '*':
      return 3;
    case '/':
      return 3;
    case ' ':
      return 4;
  }
  return -1;
}

std::string infx2pstfx(std::string inf) {
  std::string postf;
  TStack<char, size> stack;
  for (auto & symbol : inf) {
    int prior = getPrior(symbol);
    if (prior == -1) {
      postf += symbol;
      postf += ' ';
    } else {
        if (stack.get() < prior || prior == 0 || stack.isEmpty()) {
          stack.push(symbol); }
        else if (symbol == ')') {
          char sm = stack.get();
          while (getPrior(sm) >= prior) {
            postf += sm;
            postf += ' ';
            stack.pop();
            sm = stack.get();
          }
          stack.pop();
        } else {
            char sm = stack.get();
            while (getPrior(sm) >= prior) {
              postf += sm;
              postf += ' ';
              stack.pop();
              sm = stack.get();
            }
            stack.push(symbol);
        }
    }
  }
  while (!stack.isEmpty()) {
    postf += stack.get();
    postf += ' ';
    stack.pop();
  }
  postf.pop_back();
  return postf;
}

int count(const int & a, const int & b, const char & el) {
  switch (el) {
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    case '/':
      return a / b;
  }
  return 0;
}

int eval(std::string pref) {
  TStack<int, size> stack;
  for (auto & el : pref) {
    if (getPrior(el) == 4) {
      continue;
    }
    if (getPrior(el) == -1) {
      char k[2];
      k[0] = el;
      k[1] = '\0';
      int r = atoi(k);
      stack.push(r);
    } else {
        int b = stack.get();
        stack.pop();
        int a = stack.get();
        stack.pop();
        stack.push(count(a, b, el));
      }
  }
  return stack.get();
}
