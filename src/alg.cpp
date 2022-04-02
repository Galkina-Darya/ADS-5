// Copyright 2021 NNTU-CS
	#ifndef INCLUDE_TSTACK_H_
	#define INCLUDE_TSTACK_H_
	
	template<typename T, int size>
	class TStack {
	 private:
	    T arr[100];
	    int top;
	 public:
	    TStack() : top(-1) { }
	    T get() const {
	      return arr[top];
	    }
	    bool isEmpty() const {
	      return top == -1;
	    }
	    void pop() {
	      if (top >= 0) top--;
	    }
	    void push(T item) {
	      if (top < size - 1) arr[++top] = item;
	    }
	};
	#endif  // INCLUDE_TSTACK_H_

// Copyright 2021 NNTU-CS
	#include <string>
	#include <map>
	#include "tstack.h"
	int getPrior(char sim) {
	  switch (sim) {
	    case '(':return 0;
	    case ')':return 1;
	    case '+':return 2;
	    case '-':return 2;
	    case '*':return 3;
	    case '/':return 3;
	    case ' ':return -2;
	    default:return -1;
	  }
	}
	
	void razdel(char sim, std::string* str) {
	  *str += sim;
	  *str += ' ';
	}
	int Calc(int a, int b, char c) {
	  switch (c) {
	    case '+':
	      return b + a;
	    case '-':
	      return b - a;
	    case '*':
	      return b * a;
	    case '/':
	      return b / a;
	    default:
	      throw "Error perform actions!";
	  }
	}
	
	std::string infx2pstfx(std::string inf) {
	  TStack<char, 128> stack1;
	  std::string res = "";
	  for (int i = 0; i < inf.length(); i++) {
	    if (getPrior(inf[i]) == -1) {
	      if (i < inf.length() && getPrior(inf[i + 1]) == -1) {
	        while (i < inf.length() && getPrior(inf[i]) == -1) {
	          res += inf[i];
	          i++;
	        }
	        res += ' ';
	      } else {
	        razdel(inf[i], &res);
	      }
	      continue;
	    }
	    if (stack1.isEmpty() || getPrior(inf[i]) == 0
	        || getPrior(inf[i]) > getPrior(stack1.get())) {
	      stack1.push(inf[i]);
	    } else {
	      if (getPrior(inf[i]) == 1) {
	        while (getPrior(stack1.get()) != 0) {
	          razdel(stack1.get(), &res);
	          stack1.pop();
	        }
	        stack1.pop();
	      } else if (getPrior(inf[i]) <= getPrior(stack1.get())) {
	        while (getPrior(stack1.get()) > 1) {
	          razdel(stack1.get(), &res);
	          stack1.pop();
	        }
	        stack1.push(inf[i]);
	      }
	    }
	  }
	  while (!stack1.isEmpty()) {
	    if (getPrior(stack1.get()) > 1) {
	      razdel(stack1.get(), &res);
	    }
	    stack1.pop();
	  }
	  res.pop_back();
	  return res;
	}
	int eval(std::string post) {
	  TStack<int, 100> stack2;
	  for (int i = 0; i < post.length(); i++) {
	    int r = i;
	    std::string temp = "";
	    while (getPrior(post[r]) == -1) {
	      temp += post[r];
	      r++;
	    }
	    i = r;
	    if (getPrior(post[i]) > 1) {
	      int a = stack2.get();
	      stack2.pop();
	      int b = stack2.get();
	      stack2.pop();
	      stack2.push(Calc(a, b, post[i]));
	    }
	    if (temp != "") {
	      stack2.push(std::stoi(temp));
	    }
	  }
	  return stack2.get();
	}

