#pragma once
#include <ctime>
#include "Shapes.h"

enum class ShapeType {
	Point = 0,
	Circle,
	Rect,
	Square,
	Polyline,
	Polygon,
	Size
};


class ShapeFactory {
public:
	const static int max_range = 101;

	static shared_ptr<Shape> get_shape(ShapeType type) {
		Shape *shape = nullptr;
		srand((unsigned)time(NULL));
		switch (type) {
			case ShapeType::Point: {
				shape = new Point((float)rand(), (float)rand());
				break;
			}
			case ShapeType::Circle: {
				Point p = Point((float)rand(), (float)rand());
				float radius = (float)rand();
				shape = new Circle(radius, p);
				break;
			}
			case ShapeType::Rect: {
				Point a = Point((float)rand(), (float)rand());
				Point b = Point((float)rand(), (float)rand());
				shape = new Rect(a, b);
				break;
			}
			case ShapeType::Square: {
				Point p = Point((float)rand(), (float)rand());
				float size = (float)rand();
				shape = new Square(p, size);
				break;
			}
			case ShapeType::Polyline: {
				Container<Point> container;
				Polyline *tmp = new Polyline(container);
				int range = rand() % max_range;
				for (int i = 0; i < range; ++i) {
					Point p = Point((float)rand(), (float)rand());
					tmp->add_point(p);
				}
				shape = tmp;
				break;
			}
			case ShapeType::Polygon: {
				Container<Point> container;
				Polyline pl = Polyline(container);
				int range = rand() % max_range;
				for (int i = 0; i < range; ++i) {
					Point p = Point((float)rand(), (float)rand());
					pl.add_point(p);
				}
				Polygon *polygon = new Polygon(pl);
				shape = polygon;
				break;
			}
		}

		return shared_ptr<Shape>(shape);
	}
};