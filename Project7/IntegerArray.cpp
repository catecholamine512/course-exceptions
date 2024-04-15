#include "IntegerArray.h"
#include <exception>
#include <limits>


IntegerArray::IntegerArray(int length) : IntegerArray() {
	if (length < 0) throw bad_length(); // if this throws, nothing is allocated, but the destructor won't be called either
	if (length == 0) return; // the default initializer already took care of that case
	_length = length;
	_data = new int[_length]();
}

IntegerArray::IntegerArray(const IntegerArray& source) : IntegerArray(source._length) { // a copy constructor can assume a valid source object, hence the usual checks could be skipped
	for (size_t i = 0; i < _length; ++i) {
		_data[i] = source._data[i];
	}
}

IntegerArray::~IntegerArray() {
	delete[] _data; // even if _data == nullptr, this is valid
}

int& IntegerArray::operator[](int i) {
	if (i < 0 || i >= _length) throw bad_range();
	return _data[i];
}

void IntegerArray::realloc(int new_length_i) {
	if (new_length_i < 0) throw bad_length();
	delete[] _data;
	size_t new_length = new_length_i;
	int* new_data = ((new_length != 0) ? new int[new_length]() : nullptr);
	_length = new_length;
	_data = new_data;
}

void IntegerArray::resize(int new_length_i) {
	if (new_length_i == _length) return;
	if (new_length_i < 0) throw bad_length();
	if (new_length_i == 0) {
		delete[] _data;
		_data = nullptr;
		_length = 0;
		return;
	}
	size_t new_length = new_length_i;
	int* new_data = new int[new_length]();
	size_t min = (new_length < _length) ? new_length : _length;
	for (size_t i = 0; i < min; ++i) { // min could be zero, in which case the loop is empty
		new_data[i] = _data[i];
	}
	delete[] _data;
	_length = new_length;
	_data = new_data;
}

int IntegerArray::search(const int v) const {
	for (size_t i = 0; i < _length; ++i) {
		if (_data[i] == v) return i;
	}
	return -1;
}

void IntegerArray::insert(int before, int value) {
	if (before < 0 || before > _length) throw bad_range();
	if (_length == std::numeric_limits<int>::max()) throw bad_range(); // overflow check
	int new_length = _length + 1;
	int* new_data = new int[new_length]();
	for (size_t i = 0; i < before; ++i) new_data[i] = _data[i]; // `before` should be <= `_length` after the above checks
	new_data[before] = value;
	for (size_t i = before + 1; i < new_length; ++i) new_data[i] = _data[i - 1];
	delete[] _data;
	_length = new_length;
	_data = new_data;
}

void IntegerArray::push_start(int value) {
	this->insert(0, value);
}

void IntegerArray::push_end(int value) {
	this->insert(_length, value);
}

void IntegerArray::remove(int at) {
	if (at < 0 || at >= _length) throw bad_range(); // also covers the case _length == 0
	int new_length = _length - 1;
	if (new_length == 0) {
		delete[] _data;
		_length = 0;
		_data = nullptr;
		return;
	}
	int* new_data = new int[new_length]();
	for (size_t i = 0; i < at; ++i) new_data[i] = _data[i];
	for (size_t i = at + 1; i < _length; ++i) new_data[i - 1] = _data[i];
	delete[] _data;
	_length = new_length;
	_data = new_data;
}

std::ostream& operator<<(std::ostream& output, const IntegerArray& a) {
	output << "[";
	for (size_t i = 0; i < a._length; ++i) {
		output << a._data[i] << ", ";
	}
	output << "]";
	return output;
}

