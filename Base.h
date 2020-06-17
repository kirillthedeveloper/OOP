#pragma once
#include <string>
#include <iostream>
#include "Container.h"

class Printable {
public:
	virtual operator std::string() const = 0;
};

class Named : Printable {
public:
	Named(std::string const &name): name(name) {}
protected:
	std::string name;
};

class Shape : public Printable {
public:
	Shape() {
		++shapes_count;
	}

	Shape(Shape const &shape) {
		++shapes_count;
	}

	virtual ~Shape() {
		--shapes_count;
	}
	
	virtual operator std::string() const = 0;

	friend ostream & operator << (ostream &out, Shape const &p) {
		std::cout << (std::string)p;
		return out;
	}

	static int get_count() {
		return shapes_count;
	}

private:
	static int shapes_count;
};

int Shape::shapes_count = 0;