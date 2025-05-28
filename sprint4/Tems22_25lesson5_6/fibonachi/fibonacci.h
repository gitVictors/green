#pragma once
#include <utility>

// Реализуйте эту функцию.
// Реализуйте эту функцию.
inline std::pair<int, int> FibonacciRec(int n) {
  
  std::pair<int, int> res = {0,0};

  //корнер-кейс
  if (n == 0 )
    return {0,n+1};
  
  n = n - 1;
  
  res = FibonacciRec(n);

  return {res.second, res.first + res.second};
}


inline int Fibonacci(int n) {
    if (n == 0) {
        return 0;
    }
    return FibonacciRec(n).first;
}