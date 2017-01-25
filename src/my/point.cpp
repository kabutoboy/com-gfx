#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

#include "my/point.hpp"

MyPoint::MyPoint() {}

MyPoint::MyPoint(std::initializer_list<float> given) {
  this->data.assign(given);
}

MyPoint::MyPoint(std::vector<float> given) { this->data = given; }

// NON-MODIFYING
float MyPoint::at(int i) { return data.at(i); }

int MyPoint::size() { return data.size(); }

auto MyPoint::begin() { return data.begin(); }

auto MyPoint::end() { return data.end(); }

MyPoint *MyPoint::copy() { return new MyPoint(data); }

void MyPoint::dump(std::string prefix) {
  std::cout << prefix;
  std::cout << "{";
  int n = data.size();

  for (int i = 0; i < n; i++) {
    std::cout << data[i];

    if (i < n - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "}";
  std::cout << '\n';
}

// MODIFYING
void MyPoint::assign(std::initializer_list<float> given) {
  this->data.assign(given);
}

void MyPoint::assign(std::vector<float> given) { this->data = given; }

void MyPoint::resize(int n) { data.resize(n); }

void MyPoint::set(int i, float val) { data[i] = val; }

void MyPoint::scale(float amount, MyPoint *center) {
  std::transform(data.begin(), data.end(), center->begin(), data.begin(),
                 [amount](const float &data_i, const float &center_i) {
                   return center_i + amount * (data_i - center_i);
                 });
}

MyPoint *MyPoint::add(MyPoint *b) {
  std::vector<float> *a = &data;
  std::transform(a->begin(), a->end(), b->begin(), a->begin(),
                 [](const float &a_i, const float &b_i) { return a_i + b_i; });
  return this;
}

MyPoint *MyPoint::sub(MyPoint *b) {
  std::vector<float> *a = &data;
  std::transform(a->begin(), a->end(), b->begin(), a->begin(),
                 [](const float &a_i, const float &b_i) { return a_i - b_i; });
  return this;
}

MyPoint *MyPoint::abs() {
  std::for_each(data.begin(), data.end(), [](float &x) { x = std::abs(x); });
  return this;
}

// STATIC
MyPoint *MyPoint::add(MyPoint *a, MyPoint *b) { return a->copy()->add(b); }

MyPoint *MyPoint::sub(MyPoint *a, MyPoint *b) { return b->copy()->sub(b); }

MyPoint *MyPoint::subAbs(MyPoint *a, MyPoint *b) {
  return b->copy()->sub(b)->abs();
}

MyPoint *MyPoint::rgb(int hex) {
  return new MyPoint({(float)(0xFF & (hex >> 16)) / 255.f,
                      (float)(0xFF & (hex >> 8)) / 255.f,
                      (float)(0xFF & (hex)) / 255.f});
}
