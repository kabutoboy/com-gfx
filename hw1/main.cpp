#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <valarray>
#include <vector>

//#define PI 3.14159
constexpr float PI = acos(-1);

using namespace std;

template <class T>
class BinaryOperation {
public:
	static T add(T a, T b) {
		return a + b;
	}
	static T sub(T a, T b) {
		return a - b;
	}
	static T subAbs(T a, T b) {
		return abs(a - b);
	}
};

class Point {

protected:
	valarray<float> data;

public:
	// CONSTRUCTORS
    Point(float x) {
        data.resize(1);
        data[0] = x;
    }
	Point(float x, float y) {
		data.resize(2);
		data[0] = x;
		data[1] = y;
	}
	Point(float x, float y, float z) {
		data.resize(3);
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}
	Point() {
		Point(.0, .0);
	}
	Point(valarray<float> &data) {
		this->data = data;
	}

	// NON-MODIFYING
	float get(int i) {
		return data[i];
	}
	int dimensions() {
		return data.size();
	}
	float sumOfPow(float p) {
		return pow(data, p).sum();
	}
	Point copy() {
		Point b(data);
		return b;
	}
	void dump(string prefix = "") {
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
    void resize(int n) {
        data.resize(n);
    }
	void set(int i, float val) {
		data[i] = val;
	}
	void scale(float amount, Point *center) {
		for (int i = 0; i < this->dimensions(); i++) {
			data[i] = amount * (data[i] - center->get(i)) + center->get(i);
		}
	}
	Point *binOp(Point *b, float (*op)(float, float)) {
		int n = this->dimensions();
		if (b->dimensions() == n) {
			for (int i = 0; i < n; i++) {
				data[i] = op(get(i), b->get(i));
			}
		}
		return this;
	}
	Point *add(Point *b) {
		return binOp(b, BinaryOperation<float>::add);
	}
	Point *sub(Point *b) {
		return binOp(b, BinaryOperation<float>::sub);
	}

// STATIC
	static Point binOp(Point *a, Point *b, float (*op)(float, float)) {
		Point c = a->copy();
		c.binOp(b, op);
		return c;
	}
	static Point add(Point *a, Point *b) {
		return binOp(a, b, BinaryOperation<float>::add);
	}
	static Point sub(Point *a, Point *b) {
		return binOp(a, b, BinaryOperation<float>::sub);
	}
	static Point subAbs(Point *a, Point *b) {
		return binOp(a, b, BinaryOperation<float>::subAbs);
	}

};

// class Metric {
// protected:
// 	float p;
// 	float pInv;
// public:
// 	// CONSTRUCTORS
// 	Metric(float p) {
// 		this->p = p;
// 		this->pInv = 1. / p;
// 	}
// 	Metric() {
// 		Metric(2.);
// 	}
// 	// NON-MODIFYING
// 	distance(Point *a, Point *b) {
// 		return pow((Point::subAbs(a, b)).sumOfPow(p), pInv);
// 	}
// };

class Drawable {
public:
	virtual void draw() { }
	virtual void scale(float) = 0;
	virtual void rotate(float) = 0;
	virtual void translate(Point*) = 0;
};

class Polygon : public Drawable {
protected:
	vector<Point> vertices;
	Point color;
	Point position;
	float scl;
	float angle;
public:
	Polygon() {
		// vertices = {};
		color = {0, 0, 0};
		position = {0, 0};
		scl = 1;
		angle = 0;
	}

	// NON-MODIFYING
	void draw() override {
		// glBegin(GL_LINES);
		glBegin(GL_POLYGON);
		glColor3f(color.get(0), color.get(1), color.get(2));
		for (Point v: vertices) {
			glVertex2f(v.get(0), v.get(1));
		}
		glEnd();
	}

	// MODIFYING
	void setColor(int hex) {
		color = {
			(float)(0xFF & (hex >> 16)) / 255,
			(float)(0xFF & (hex >> 8)) / 255,
			(float)(0xFF & (hex)) / 255
		};
	}
	void setColor(float r, float g, float b) {
		color = {r, g, b};
	}
	void setPosition(float x, float y) {
		position = {x, y};
	}
	void scale(float amount) override {
		this->scl *= amount;
		for (Point &v: vertices) {
			v.scale(amount, &position);
		}
	}
	void rotate(float amount) override {
		this->angle += amount;
		for (Point &v: vertices) {
			float x = v.get(0), y = v.get(1);
			v.set(0, x * cos(amount) - y * sin(amount));
			v.set(1, x * sin(amount) + y * cos(amount));
		}
	}
	void translate(Point *amount) override {
		this->position.add(amount);
		for (Point &v: vertices) {
			v.add(amount);
		}
	}
};

class MyRectangle : public Polygon {
public:
	MyRectangle(float w, float h) {
		vertices.resize(4);
		vertices[0] = {(float).5 * (-w), (float).5 * (-h)};
		vertices[1] = {(float).5 * (+w), (float).5 * (-h)};
		vertices[2] = {(float).5 * (+w), (float).5 * (+h)};
		vertices[3] = {(float).5 * (-w), (float).5 * (+h)};
	}
};

class MyEllipse : public Polygon {
public:
	MyEllipse(float a, float b, int n = 0) {
		if (n == 0) {
			// n = 2. * PI * r;
			n = 20;
		}
		vertices.resize(n);
		for (int i = 0; i < n; i++) {
			float angle = 2 * PI * i / n;
			vertices[i] = {a * cos(angle), b * sin(angle)};
		}
	}
};

class Circle : public Polygon {
public:
	Circle(float r, int n = 0) {
		if (n == 0) {
			// n = 2. * PI * r;
			n = 20;
		}
		vertices.resize(n);
		for (int i = 0; i < n; i++) {
			float angle = 2 * PI * i / n;
			vertices[i] = {r * cos(angle), r * sin(angle)};
		}
	}
};

class Flower : public Polygon {
public:
	Flower(float r, float petals, int n = 0) {
		if (n == 0) {
			// n = 2. * PI * r;
			n = 160;
		}
		vertices.resize(n);
		for (int i = 0; i < n; i++) {
			float angle = 2 * PI * i / n;
			vertices[i] = {
				r * sin((float).5 * petals * angle) * cos(angle),
				r * sin((float).5 * petals * angle) * sin(angle)
			};
		}
	}
};

class Group : public Drawable {
protected:
	vector<Drawable*> children;
public:
	Group() {
		// children = {};
	}
	void add(Drawable *child) {
		children.push_back(child);
	}
	void draw() override {
		for (auto c: children) {
			c->draw();
		}
	}
	void scale(float amount) override {
		for (auto c: children) {
			c->scale(amount);
		}
	}
	void rotate(float amount) override {
		for (auto c: children) {
			c->rotate(amount);
		}
	}
	void translate(Point *amount) override {
		for (auto c: children) {
			c->translate(amount);
		}
	}
};

class SunFlower : public Group {
protected:
	Circle seeds1 = {INNER_SEEDS_RADIUS};
	Circle seeds2 = {OUTER_SEEDS_RADIUS};
	Flower petals1 = {RADIUS, NUMBER_OF_PETALS};
	Flower petals2 = {RADIUS, NUMBER_OF_PETALS};
public:
	static float constexpr NUMBER_OF_PETALS = 12;
	static float constexpr RADIUS = 100;
	static float constexpr INNER_SEEDS_RADIUS = 30;
	static float constexpr OUTER_SEEDS_RADIUS = 40;
	SunFlower(float scl = 1, float rotation = 0, Point *translation = new Point{0, 0}) {

		seeds1.setColor(0x5d4239);
		seeds2.setColor(0x795548);
		petals1.setColor(0xffeb3b);
		petals2.setColor(0xffc107);
		petals2.rotate(PI / NUMBER_OF_PETALS);

		add(&petals2);
		add(&petals1);
		add(&seeds2);
		add(&seeds1);

		scale(scl);
		rotate(rotation);
		translate(translation);

	}
};

Group all;

int displayWidth = 600;
int displayHeight = 600;

void init(void)
{
	glClearColor(0.2, 0.2, 0.3, 1.0);
	gluOrtho2D(-250, 250.0, -250.0, 250.0);

	MyRectangle *sky = new MyRectangle(600, 600);
	sky->setColor(0xafe0f7);
	all.add(sky);

	Circle *sunGlow3 = new Circle(130, 130);
	sunGlow3->setColor(0xc0e7f9);
	sunGlow3->translate(new Point{0, 100});
	all.add(sunGlow3);

	Circle *sunGlow2 = new Circle(100, 100);
	sunGlow2->setColor(0xdef2fc);
	sunGlow2->translate(new Point{0, 100});
	all.add(sunGlow2);

	Circle *sunGlow1 = new Circle(80, 80);
	sunGlow1->setColor(0xf0f9fe);
	sunGlow1->translate(new Point{0, 100});
	all.add(sunGlow1);

	Circle *sun = new Circle(70, 70);
	sun->setColor(0xffffff);
	sun->translate(new Point{0, 100});
	all.add(sun);

	MyEllipse *cloud22 = new MyEllipse(30, 15, 70);
	cloud22->setColor(0xfffffc);
	cloud22->translate(new Point{140, 180});
	all.add(cloud22);

	MyEllipse *cloud21 = new MyEllipse(40, 20, 70);
	cloud21->setColor(0xfffffc);
	cloud21->translate(new Point{100, 190});
	all.add(cloud21);

	MyEllipse *cloud2 = new MyEllipse(50, 20, 70);
	cloud2->setColor(0xfffffc);
	cloud2->translate(new Point{-150, 140});
	all.add(cloud2);

	MyEllipse *cloud1 = new MyEllipse(40, 20, 70);
	cloud1->setColor(0xfffffc);
	cloud1->translate(new Point{-100, 150});
	all.add(cloud1);

	MyRectangle *grass = new MyRectangle(600, 400);
	grass->setColor(0x795548);
	grass->translate(new Point{0, -100});
	all.add(grass);

	int m = 20, n = 80;
	for (int i = 0; i < m; i++) {
		Group *row = new Group();
		for (int j = 0; j < n; j++) {
			float r = SunFlower::RADIUS;
			float scl = displayWidth / (2 * r) / n * 8;
			SunFlower *sunFlower = new SunFlower{
                scl,
                2 * PI * (i + j) / (m + n),
                new Point{
                    scl * 2 * r * (n/2 - j) * ((float)(i+1) / m),
                    (float)(100 - 1 * i * i)
                }
            };
			row->add(sunFlower);
		}
		row->scale((float)(i+1) / m);
		all.add(row);
	}
}

void draw()
{
	all.draw();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(displayWidth, displayHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Test OpenGL");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
