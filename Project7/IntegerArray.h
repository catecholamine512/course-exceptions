#pragma once
#include <exception>
#include <iostream>


class IntegerArray {
	int _length;
	int* _data;

public:
	IntegerArray() : _length(0), _data(nullptr) {};
	IntegerArray(int length);
	IntegerArray(const IntegerArray& source);
	~IntegerArray();
	int& operator[](int index);
	void realloc(int new_length);
	void resize(int new_length);
	void insert(int before, int value);
	void remove(int at);
	int search(const int value) const;
	void push_start(int value);
	void push_end(int value);
	friend std::ostream& operator<<(std::ostream& output, const IntegerArray& a);
};

class bad_range : public std::exception {
public:
	virtual const char* what() { return "bad range exception"; }
};

class bad_length : public std::exception {
public:
	virtual const char* what() { return "bad length exception"; }
};

