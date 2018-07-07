#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

template <typename T>
std::vector<T> copyIfInAnyRange(const std::vector<T> &values,
                                std::vector<std::pair<T, T>> ranges,
                                std::function<bool(T, T, T)> checker) {
  std::vector<T> v(values.size());

  std::function<bool(T)> comparator = [ranges, checker](const T &e) {
    for (const auto &range : ranges) {
      if (checker(e, range.first, range.second)) {
        return true;
      }
    }

    return false;
  };

  auto end = std::copy_if(values.begin(), values.end(), v.begin(), comparator);
  v.resize(end - v.begin());

  return v;
}

int main(void) {
  const std::vector<int> values{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<std::pair<int, int>> ranges{{0, 2}, {6, 9}};

  auto result = copyIfInAnyRange<int>(
      values, ranges, [](int x, int a, int b) { return x >= a && x <= b; });

  for (const auto &d : result) {
    std::cout << d << std::endl;
  }
}
