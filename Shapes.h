#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "corecrt_math_defines.h"
#include "Base.h"
#include "Container.h"

class Point : public Shape, Named {
public:
	Point(): Named("Point"), x(x), y(y) {}

	Point(float x, float y): Named("Point"), x(x), y(y) {}

	Point(Point const &other): Named("Point"), x(other.x), y(other.y) {}

	float get_x() const {return x;}

	float get_y() const {return y;}

	operator std::string() const {
		std::ostringstream os;
		os << name << " (" << x << ", " << y << ")";
		return os.str();
	}
private:
	float x, y;
};


class Circle : public Shape, Named {
public:
	Circle(float radius, const Point &center): Named("Circle"), center(center), radius(radius) {
		area = (float)M_PI * radius * radius;
	}

	operator std::string() const {
		std::ostringstream os;
		os << name << " (radius = " << radius << ", area = " << area << ", center = " << (std::string)center << ")";
		return os.str();
	}
private:
	float radius, area;
	Point center;
};


class Rect : public Shape, Named {
public:
	Rect(Point const &a, const Point & b): Named("Rect"), a(a), b(b) {
		area = abs((a.get_x() - b.get_x())*(a.get_y() - b.get_y()));
	}

	operator std::string() const {
		std::ostringstream os;
		os << name << " (Point 1 = " << (std::string)a << ", Point 2 = " << (std::string)b << ", area = " << area << ")";
		return os.str();
	}
private:
	Point a, b;
	float area;
};


class Square : public Shape, Named {
public:
	Square(Point const &center, float size) : Named("Square"), center(center), size(size) {
		area = size*size;
	}

	operator std::string() const {
		std::ostringstream os;
		os << name << " (Center = " << (std::string)center << ", area = " << area << ")";
		return os.str();
	}
private:
	Point center;
	float size, area;
};


class Polyline : public Shape, Named {
public:
	Polyline(Container<Point> &points) : Named("Polyline"), points(points) {
	}

	void add_point(Point &p) {
		points.push_back(p);
	}

	float get_length() const {
		if (points.get_size() < 2)
			return 0;

		float length = 0;
		for (int i = 0; i < points.get_size() - 1; ++i) {
			Point a = points[i];
			Point b = points[i + 1];
			length += sqrt(
				pow(a.get_x() - b.get_x(), 2) +
				pow(a.get_y() - b.get_y(), 2));
		}

		return length;
	}

	Point& get_start_point() const {
		return points[0];
	}

	operator std::string() const {
		std::ostringstream os;
		os << name << " (Length = " << get_length() << ", Points = [";
		for (int i = 0; i < points.get_size(); ++i) {
			os << (std::string)points[i] << " ";
		}
		os << "])";
		return os.str();
	}
private:
	Container<Point> points;
};


class Polygon : public Shape, Named {
public:
	Polygon(Polyline &border) : Named("Polygon"), border(border) {
		this->border.add_point(border.get_start_point());
	}

	operator std::string() const {
		std::ostringstream os;
		os << name << "(" << (std::string)border << ")";
		return os.str();
	}
private:
	Polyline border;
};