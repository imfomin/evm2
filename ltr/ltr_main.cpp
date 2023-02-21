#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

class ltr_matrix {
public:
	ltr_matrix() {
		m_data = nullptr;
		m_size = 0;
	}
	ltr_matrix(const ltr_matrix& other) {
		alloc(other.size());

		for (int i = 0; i < size(); ++i) {
			this->operator[](i) = other[i];
		}
	}
	ltr_matrix(ltr_matrix&& other) noexcept {
		m_data = other.m_data;
		m_size = other.m_size;

		other.m_data = nullptr;
		other.m_size = 0;
	}
	ltr_matrix& operator =(const ltr_matrix& other) {
		if (this == &other) return *this;

		if (size() != other.size()) {
			clear();
			alloc(other.size());
		}

		for (int i = 0; i < size(); ++i) {
			this->operator[](i) = other[i];
		}

		return *this;
	}
	ltr_matrix& operator =(ltr_matrix&& other) noexcept {
		if (this == &other) return *this;

		clear();

		m_data = other.m_data;
		m_size = other.m_size;

		other.m_data = nullptr;
		other.m_size = 0;

		return *this;
	}
	void clear() {
		if (m_data) delete m_data;
		m_size = 0;
	}
	~ltr_matrix() {
		clear();
	}
	int& operator[](size_t index) const {
		if (index >= m_size) throw 1;

		return m_data[index];
	}

	size_t size() const {
		return m_size;
	}
	size_t dim() const {
		return 0.5f * (-1 + sqrt(8 * m_size + 1));
	}

	ltr_matrix operator +(const ltr_matrix& other) const {
		if (size() != other.size()) throw 1;

		ltr_matrix sum;
		sum.alloc(size());

		for (int i = 0; i < size(); ++i) {
			sum[i] = this->operator[](i) + other[i];
		}

		return sum;
	}

	int pos(int i, int j) const {
		if (i > j) return -1;

		else return (2 * dim() - i + 1) * i / 2 - i + j;
	}
	ltr_matrix operator *(const ltr_matrix& other) const {
		if (size() != other.size()) throw 1;

		ltr_matrix sum;
		sum.alloc(size());

		for (int i = 0, index = 0; i < size(); ++i) {
			for (int j = i; j < size(); ++j) {
				sum[index] = 0;
				for (int k = 0; k < size(); ++k) {
					if (i > k || k > j) continue;

					std::cout << pos(i, j) << ' ' << pos(i, k) << ' ' << pos(k, j) << std::endl;
					sum[index] += this->operator[](pos(i, k)) + other[pos(k, j)];
				}
				index++;
			}
		}

		return sum;
	}

	friend std::ostream& operator <<(std::ostream&, const ltr_matrix&);
	friend std::istream& operator >>(std::istream&, ltr_matrix&);
private:
	int* m_data;
	size_t m_size;

	void alloc(size_t size) {
		m_data = new int[size];
		m_size = size;
	}
};

std::ostream& operator <<(std::ostream& stream, const ltr_matrix& matrix) {
	size_t index = 0;
	for (int i = 0; i < matrix.dim(); ++i) {
		for (int j = 0; j < i; ++j) {
			stream << "  ";
		}
		for (int j = 0; j < matrix.dim() - i; ++j) {
			stream << matrix[index++] << ' ';
		}
		stream << '\n';
	}

	return stream;
}

std::istream& operator >>(std::istream& stream, ltr_matrix& matrix) {
	matrix.clear();

	size_t dim;
	stream >> dim;

	matrix.m_size = dim * (dim + 1) / 2;
	matrix.m_data = new int[matrix.m_size];

	for (int i = 0; i < matrix.size(); ++i) {
		stream >> matrix[i];
	}

	return stream;
};

int main() {
	std::ifstream in("mdata.txt");

	ltr_matrix A, B;
	in >> A >> B;
	std::cout << A << B << A * B << std::endl;

	in.close();

	return 0;
}