// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int Priority(char operation) {
  std::pair<char, int> priority[6];
  switch (operation) {
  case'(':
    priority[0].first = '(';
    priority[0].second = 0;
  case')':
    priority[1].first = ')';
    priority[1].second = 1;
  case'+':
    priority[2].first = '+';
    priority[2].second = 2;
  case'-':
    priority[3].first = '-';
    priority[3].second = 2;
  case'*':
    priority[4].first = '*';
    priority[4].second = 3;
  case'/':
    priority[5].first = '/';
    priority[5].second = 3;
  }
  int p = -1;
  for (int j = 0; j < 6; ++j) {
    if (operation == priority[j].first) {
      p = priority[j].second;
      break;
    }
  }
  return p;
}
std::string Spaces(const std::string& str) {
  if (str.length() <= 2)
    return str;
  int n = 2 - str.length() % 2;
  std::string adStr(str, 0, n);
  for (auto it = str.begin() + n; it != str.end();) {
    adStr += ' '; adStr += *it++;;
  }
  return adStr;
}
std::string infx2pstfx(std::string inf) {
  std::string postfixStr;
  TStack<char, 100> stack;
  for (auto& operation : inf) {
    int priority = Priority(operation);
    if (priority == -1) {
      postfixStr += operation;
    } else {
      if (stack.get() < priority || priority == 0 || stack.isEmpty()) {
        stack.push(operation);
      } else if (operation == ')') {
        char character = stack.get();
        while (Priority(character) >= priority) {
          postfixStr += character;
          stack.pop();
          character = stack.get();
        }
        stack.pop();
      } else {
        char character = stack.get();
        while (Priority(character) >= priority) {
          postfixStr += character;
          stack.pop();
          character = stack.get();
        }
        stack.push(operation);
      }
    }
  }
  while (!stack.isEmpty()) {
    postfixStr += stack.get();
    stack.pop();
  }
  postfixStr = Spaces(postfixStr);
  return postfixStr;
}
int calculate(const int& a, const int& b, const int& oper) {
  switch (oper) {
  default:
    break;
  case'+': return a + b;
  case'-': return a - b;
  case'*': return a * b;
  case'/': return a / b;
  }
  return 0;
}
int eval(std::string pref) {
  TStack<int, 100> stack;
  std::string number = "";
  for (size_t i = 0; i < pref.size(); i++) {
    if (Priority(pref[i]) == -1) {
      if (pref[i] == ' ') {
        continue;
      } else if (isdigit(pref[i + 1])) {
        number += pref[i];
        continue;
      } else {
        number += pref[i];
        stack.push(atoi(number.c_str()));
        number = "";
      }
    } else {
      int b = stack.get();
      stack.pop();
      int a = stack.get();
      stack.pop();
      stack.push(calculate(a, b, pref[i]));
    }
  }
  return stack.get();
}
