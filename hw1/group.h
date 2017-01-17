#include "drawable.h"

class MyGroup : public MyDrawable {
protected:
	vector<MyDrawable*> children;
public:
	GMyroup();
	void add(MyDrawable*);
	void draw() override;
	void scale(float) override;
	void rotate(float) override;
	void translate(MyPoint*) override;
};
