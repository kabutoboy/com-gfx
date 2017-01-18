#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

#include "my/point.hpp"

using namespace std;

MyPoint::MyPoint() {

}
MyPoint::MyPoint(initializer_list<float> given) {
	this->data.assign(given);
}

MyPoint::MyPoint(vector<float> given) {
	this->data = given;
}

// NON-MODIFYING
float MyPoint::at(int i) {
	return data.at(i);
}

int MyPoint::size() {
	return data.size();
}

auto MyPoint::begin() {
	return data.begin();
}

auto MyPoint::end() {
	return data.end();
}

MyPoint *MyPoint::copy() {
	MyPoint *b = new MyPoint(data);
	return b;
}

void MyPoint::dump(string prefix) {
	cout << prefix;
	cout << "{";
	int n = data.size();
	for (int i = 0; i < n; i++) {
		cout << data[i];
		if (i < n-1) {
			cout << ", ";
		}
	}
	cout << "}";
	cout << endl;
}

// MODIFYING
void MyPoint::assign(initializer_list<float> given) {
	this->data.assign(given);
}

void MyPoint::assign(vector<float> given) {
	this->data = given;
}

void MyPoint::resize(int n) {
  data.resize(n);
}

void MyPoint::set(int i, float val) {
	data[i] = val;
}

void MyPoint::scale(float amount, MyPoint *center) {
	transform(data.begin(), data.end(), center->begin(), data.begin(), [amount](const float &data_i, const float &center_i) {
		// data[i] = amount * (data[i] - center->get(i)) + center->get(i);
		return center_i + amount * (data_i - center_i);
          // return fma(amount, data_i - center_i, center_i);
	});
}

MyPoint *MyPoint::add(MyPoint *b) {
	vector<float> *a = &data;
	transform(a->begin(), a->end(), b->begin(), a->begin(), [](const float &a_i, const float &b_i) {
		return a_i + b_i;
	});
	return this;
}

MyPoint *MyPoint::sub(MyPoint *b) {
	vector<float> *a = &data;
	transform(a->begin(), a->end(), b->begin(), a->begin(), [](const float &a_i, const float &b_i) {
		return a_i - b_i;
	});
	return this;
}

MyPoint *MyPoint::abs() {
	for_each(data.begin(), data.end(), [](float &x) {
		x = std::abs(x);
	});
	return this;
}

// STATIC
MyPoint *MyPoint::add(MyPoint *a, MyPoint *b) {
	return a->copy()->add(b);
}

MyPoint *MyPoint::sub(MyPoint *a, MyPoint *b) {
	return b->copy()->sub(b);
}

MyPoint *MyPoint::subAbs(MyPoint *a, MyPoint *b) {
	return b->copy()->sub(b)->abs();
}