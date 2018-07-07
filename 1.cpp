#include <iostream>
#include <list>

// mock
class Shape {
public:
  virtual float area() { return 0; }
};

struct ColoredShape {
  Shape shape; // I see no reason to why shape could not be a reference
  unsigned int color;
};

class ShapeList {
public:
  void append(ColoredShape *cs);
  unsigned int commonColor();
  ~ShapeList();

private:
  std::list<ColoredShape *> shapes_;
};

void ShapeList::append(ColoredShape *cs) { shapes_.push_back(cs); }

unsigned int ShapeList::commonColor() {
  if (shapes_.empty()) {
    throw "empty list";
  }

  // max_color can also be found with std::map (in a single loop over shapes_)
  unsigned int max_color = 0;
  float max_area = 0;
  for (const auto &s : shapes_) {
    float area = 0;
    for (const auto &s1 : shapes_) {
      if (s.color == s1.color) {
        area += s.shape.area();
      }
    }

    if (area >= max_area) {
      max_color = s.color;
      max_area = area;
    }
  }

  return max_color;
}

ShapeList::~ShapeList() {
  for (const auto &shape : shapes_) {
    delete shape;
  }
}

int main(void) {
  ShapeList sl;
  sl.append(new ColoredShape);

  try {
    std::cout << sl.commonColor() << std::endl;

  } catch (const char e[]) {
    std::cout << e << std::endl;
  }
}
