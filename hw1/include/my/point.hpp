#ifndef MY_POINT_
#define MY_POINT_

#include <initializer_list>
#include <string>
#include <vector>

using namespace std;

class MyPoint {

public:

	MyPoint();
	MyPoint(initializer_list<float>);
	MyPoint(vector<float>);

  // NON-MODIFYING
	float at(int);
	int size();
	auto begin();
	auto end();
	MyPoint *copy();
	void dump(string = "");

	// MODIFYING
	void assign(initializer_list<float>);
	void assign(vector<float>);
  void resize(int);
	void set(int, float);
	void scale(float, MyPoint*);
	MyPoint *add(MyPoint*);
	MyPoint *sub(MyPoint*);
	MyPoint *abs();

  // STATIC
	static MyPoint *add(MyPoint*, MyPoint*);
	static MyPoint *sub(MyPoint*, MyPoint*);
	static MyPoint *subAbs(MyPoint*, MyPoint*);

protected:

	vector<float> data;

};

#endif
