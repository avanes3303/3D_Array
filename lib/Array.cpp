#include "Array.h"

ThreeDimensionalArray::ThreeDimensionalArray(size_t x, size_t y, size_t z)
        : x_size_(x)
        , y_size_(y)
        , z_size_(z) {
    total_size_ = (x_size_ * y_size_ * z_size_ * 17 + 7) / 8;
    data_ = new uint8_t[total_size_]();
}

ThreeDimensionalArray::ThreeDimensionalArray(const ThreeDimensionalArray& arr)
        : x_size_(arr.x_size_)
        , y_size_(arr.y_size_)
        , z_size_(arr.z_size_) {
    total_size_ = (x_size_ * y_size_ * z_size_ * 17 + 7) / 8;
    data_ = new uint8_t[total_size_]();
    for (size_t i = 0; i < total_size_; ++i) {
        data_[i] = arr.data_[i];
    }
}

ThreeDimensionalArray& ThreeDimensionalArray::operator=(const ThreeDimensionalArray& other) {
    if (this != &other) {
        delete[] data_;
        x_size_ = other.x_size_;
        y_size_ = other.y_size_;
        z_size_ = other.z_size_;
        total_size_ = (x_size_ * y_size_ * z_size_ * 17 + 7) / 8;
        data_ = new uint8_t[total_size_]();
        for (size_t i = 0; i < total_size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    return *this;
}

ThreeDimensionalArray::CoordinateX::CoordinateX(uint8_t* data, size_t x_size, size_t y_size, size_t z_size,
                                                size_t bit_index)
 : data_(data), x_size_(x_size), y_size_(y_size), z_size_(z_size), bit_index_(bit_index) {}

ThreeDimensionalArray::CoordinateY::CoordinateY(uint8_t* data, size_t x_size, size_t y_size, size_t z_size,
                                                size_t bit_index)
 : data_(data), x_size_(x_size), y_size_(y_size), z_size_(z_size), bit_index_(bit_index) {}

ThreeDimensionalArray::CoordinateZ::CoordinateZ(uint8_t* data, size_t x_size, size_t y_size, size_t z_size,
                                                size_t bit_index)
 : data_(data), x_size_(x_size), y_size_(y_size), z_size_(z_size), bit_index_(bit_index) {}

void ThreeDimensionalArray::CoordinateZ::SetBits(size_t start, size_t end, uint32_t value) {
    for (size_t bit = start; bit <= end; ++bit) {
        SetBit(bit, (value >> (bit - start)) & 1);
    }
}

uint32_t ThreeDimensionalArray::CoordinateZ::GetBits(size_t start, size_t end) const {
    uint32_t result = 0;
    for (size_t bit = start; bit <= end; ++bit) {
        result |= (GetBit(bit) << (bit - start));
    }

    return result;
}

void ThreeDimensionalArray::CoordinateZ::SetBit(size_t bit_index, uint8_t value) {
    size_t byte_index = (bit_index) >> 3;
    size_t bit_offset = (bit_index) & 7;

    data_[byte_index] &= ~(1 << bit_offset);
    data_[byte_index] |= (value & 1) << bit_offset;
}

uint8_t ThreeDimensionalArray::CoordinateZ::GetBit(size_t bit_index) const {
    size_t byte_index = (bit_index) >> 3;
    size_t bit_offset = (bit_index) & 7;
    return (data_[byte_index] >> bit_offset) & 1;
}

ThreeDimensionalArray::CoordinateZ& ThreeDimensionalArray::CoordinateZ::operator=(uint32_t value) {
    SetBits(bit_index_ * 17, bit_index_ * 17 + 16, value);
    return *this;
}

ThreeDimensionalArray::CoordinateZ::operator uint32_t() const {
    return GetBits(bit_index_ * 17, bit_index_ * 17 + 16);
}

ThreeDimensionalArray::CoordinateZ ThreeDimensionalArray::CoordinateY::operator[](size_t k) {
    return CoordinateZ(data_, x_size_, y_size_, z_size_, bit_index_ + k);
}

ThreeDimensionalArray::CoordinateY ThreeDimensionalArray::CoordinateX::operator[](size_t j) {
    return CoordinateY(data_, x_size_, y_size_, z_size_, bit_index_ + j * z_size_);
}

ThreeDimensionalArray::CoordinateX ThreeDimensionalArray::operator[](size_t i) const {
    return CoordinateX(data_, x_size_, y_size_, z_size_, i * y_size_ * z_size_);
}

ThreeDimensionalArray ThreeDimensionalArray::make_array(size_t x, size_t y, size_t z) {
    return ThreeDimensionalArray(x, y, z);
}

std::istream& operator>>(std::istream& input, ThreeDimensionalArray& arr) {
    for (size_t i = 0; i < arr.x_size_; ++i) {
        for (size_t j = 0; j < arr.y_size_; ++j) {
            for (size_t k = 0; k < arr.z_size_; ++k) {
                uint32_t value;
                input >> value;
                arr[i][j][k] = value;
            }
        }
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const ThreeDimensionalArray& arr) {
    for (size_t i = 0; i < arr.x_size_; ++i) {
        for (size_t j = 0; j < arr.y_size_; ++j) {
            for (size_t k = 0; k < arr.z_size_; ++k) {
                output << arr[i][j][k] << " ";
            }
        }
    }

    return output;
}

ThreeDimensionalArray ThreeDimensionalArray::operator*(uint32_t scalar) const {
    ThreeDimensionalArray result(x_size_, y_size_, z_size_);

    for (size_t i = 0; i < x_size_; ++i) {
        for (size_t j = 0; j < y_size_; ++j) {
            for (size_t k = 0; k < z_size_; ++k) {
                result[i][j][k] = (*this)[i][j][k] * scalar;
            }
        }
    }

    return result;
}

ThreeDimensionalArray ThreeDimensionalArray::operator+(const ThreeDimensionalArray& other) const {
    ThreeDimensionalArray result(x_size_, y_size_, z_size_);

    for (size_t i = 0; i < x_size_; ++i) {
        for (size_t j = 0; j < y_size_; ++j) {
            for (size_t k = 0; k < z_size_; ++k) {
                result[i][j][k] = (*this)[i][j][k] + other[i][j][k];
            }
        }
    }

    return result;
}

ThreeDimensionalArray ThreeDimensionalArray::operator-(const ThreeDimensionalArray& other) const {
    ThreeDimensionalArray result(x_size_, y_size_, z_size_);

    for (size_t i = 0; i < x_size_; ++i) {
        for (size_t j = 0; j < y_size_; ++j) {
            for (size_t k = 0; k < z_size_; ++k) {
                result[i][j][k] = (*this)[i][j][k] - other[i][j][k];
            }
        }
    }

    return result;
}

size_t ThreeDimensionalArray::GetSize() {
    return this->total_size_;
}

ThreeDimensionalArray::~ThreeDimensionalArray() {
    delete[] data_;
}