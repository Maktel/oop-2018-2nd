#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

class Container {
public:
  friend std::istream &operator>>(std::istream &is, Container &c) {
    int d;
    is >> d;
    c.ints_.push_back(d);

    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, Container &c) {
    os << *(c.ints_.rbegin());
    c.ints_.pop_back();

    return os;
  }

  Container operator+(const Container &c) const {
    Container n;
    n.ints_.resize(ints_.size() + c.ints_.size());
    auto it = n.ints_.begin();
    std::copy(ints_.begin(), ints_.end(), it);
    std::advance(it, ints_.size());
    std::copy(c.ints_.begin(), c.ints_.end(), it);

    return n;
  }

  Container &operator+=(const int val) {
    for (auto &d : ints_) {
      d += val;
    }

    return *this;
  }

  int &operator[](const unsigned int index) {
    if (index >= ints_.size()) {
      throw std::out_of_range("Index out of range");
    }

    return ints_[index];
  }

private:
  std::vector<int> ints_;
};

int main(void) {
  Container c1, c2;
  std::cin >> c1 >> c2;
  c1 += 5;

  Container c3 = c1 + c2;
  std::cout << c3 << " " << c3;
}
