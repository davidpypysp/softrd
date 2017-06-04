#ifndef SOFTRD_UTIL_H_
#define SOFTRD_UTIL_H_

#include <iostream>
#include <sstream>
#include <iomanip>

namespace softrd {

namespace util {

template <typename T>
struct Array {
	int size;
	T *values;

	Array(int size = 0) {
		this->size = size;
		values = nullptr;
		if (size != 0) {
			values = new T[size];
		}

	}

	~Array() {
		delete[] values;
	}



	void Resize(int size) { // be careful that resize may not empty the values
		delete[] values;

		if (size == 0) {
			values = nullptr;
			return;
		}

		this->size = size;
		values = new T[size];
	}

	inline T& operator[](const int index) {
		return values[index];
	}

	void Fill(const T &value) {
		std::fill(values, values + size, value);
	}

	void Empty() {
		memset(values, 0, sizeof(T) * size);
	}

};

inline std::string ToString(const float value, const int precision) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(precision) << value;
	return stream.str();
}


} // namespace util

} // namespace softrd


#endif