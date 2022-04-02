// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
  std::string s = "";
    TStack<char, 100> st;
    std::map<char, int> pr;
    pr['('] = 0;
    pr[')'] = 0;
    pr['+'] = 1;
    pr['-'] = 1;
    pr['*'] = 2;
    pr['/'] = 2;
    for (int i = 0; i < inf.size(); i++) {
        if (pr.find(inf[i]) == pr.end()) {
            s += inf[i];
            s += ' ';
        } else {
        if (inf[i] == ')') {
            while (st.Get() != '(') {
                s += st.Get();
                s += ' ';
                st.pop();
            }
            st.pop();
        } else {
        if (inf[i] == '(' || st.Empty()) {
            st.push(inf[i]);
        } else {
            if (pr[inf[i]] > pr[st.Get()]) {
            st.push(inf[i]);
            } else {
                        while (pr[inf[i]] <= pr[st.Get()]) {
                            if (!st.Empty()) {
                            s += st.Get();
                            s += ' ';
                            st.pop();
                            }
                        }
                        st.push(inf[i]);
                    }
                }
            }
        }
    }
    while (!st.Empty()) {
        s += st.Get();
        s += ' ';
        st.pop();
    }
    s.pop_back();
    return s;
  return std::string("");
}

int eval(std::string pref) {
  TStack<int, 100> st;
    int a1, a2, res, i = 0;
    while (i < pref.size()) {
        if (pref[i] >= '0') {
            st.push(pref[i] - '0');
        }
        else {
            if (pref[i] != ' ') {
                a2 = st.Get();
                st.pop();
                a1 = st.Get();
                st.pop();
                switch (pref[i]) {
                    case '+':
                        res = a1 + a2;
                        break;
                    case '-':
                        res = a1 - a2;
                        break;
                    case '*':
                        res = a1 * a2;
                        break;
                    case '/':
                        res = a1 / a2;
                        break;
                    }
                st.push(res);
            }
        }
        i++;
    }
    return st.Get();
  return 0;
}
