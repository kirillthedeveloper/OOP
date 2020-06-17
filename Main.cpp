#include <iostream>
#include <ctime>
#include "Container.h"
#include "Base.h"
#include "Shapes.h"
#include "ShapeFactory.h"

using namespace std;

int main() {
	srand((int)time(NULL));
	Container<shared_ptr<Shape>> shapes;
	int shapes_count = 20;
	for (int i = 0; i < shapes_count; ++i) {
		shared_ptr<Shape> s = ShapeFactory::get_shape(ShapeType(i % (uint8_t)ShapeType::Size));
		shapes.push_back(s);
	}

	cout << "Shape count = " << Shape::get_count() << endl;

	getchar();

	for (int i = 0; i < shapes_count; ++i) {
		cout << "shapes[" << i << "]" << endl;
		cout << *shapes[i] << endl;
	}

	getchar();

	shapes.clear();
	cout << "Shape count = " << Shape::get_count() << endl;

	getchar();

	return 0;
}