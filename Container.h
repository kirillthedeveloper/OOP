#pragma once
#include <cmath>
#include <assert.h>
#include <cstdint>
#include <iostream>

using namespace std;

template<class T>
class Container {
public:
	Container();
	Container(int size);
	Container(Container<T> const &other);
	~Container();

	T& operator[] (const int index) const;

	int get_size() const;
	bool is_empty() const;

	void push_back(T const &value);
	void pop_back();
	void clear();
private:
	int size, capacity;
	T *buffer;

	void reserve(int capacity);
};

template<class T>
Container<T>::Container() : size(0), capacity(0), buffer(new T[capacity]) {}

template<class T>
Container<T>::Container(int size): size(0), capacity(size), buffer(new T[capacity]) {}

template<class T>
Container<T>::Container(Container<T> const &other): size(other.size), capacity(other.capacity), buffer(new T[capacity]) {
	for (int i = 0; i < size; ++i) {
		buffer[i] = T(other[i]);
	}
}

template<class T>
Container<T>::~Container() {
	if (buffer != nullptr) {
		delete[] buffer;
		buffer = nullptr;
	}
}

template<class T>
T& Container<T>::operator [] (const int i) const {
	if (i >= size) throw exception("Invalid index.\n");
	return (T&)buffer[i];
}

template<class T>
int Container<T>::get_size() const {
	return size;
}

template<class T>
bool Container<T>::is_empty() const {
	return (size == 0);
}

template<class T>
void Container<T>::push_back(T const &value) {
	if (size == capacity) {
		reserve(capacity * 2 + 1);
	}

	buffer[size] = T(value);
	size++;
}

template<class T>
void Container<T>::pop_back()
{
	if (size == 0) throw exception("Invalid memory access.\n");

	this->operator[](size - 1).~T();
	--size;
}

template<class T>
void Container<T>::clear() {
	int s = get_size();
	for (int i = 0; i < s; i++) {
		pop_back();
	}

	size = 0;
	capacity = 0;
	delete[] buffer;
	buffer = nullptr;
}

template<class T>
void Container<T>::reserve(int capacity) {
	if (this->capacity > capacity) return;
	T *new_buffer = new T[capacity];
	this->capacity = capacity;
	if (size != 0) {
		for (int i = 0; i < size; ++i) {
			new_buffer[i] = buffer[i];
		}
	}

	delete[] buffer;
	buffer = new_buffer;
}
