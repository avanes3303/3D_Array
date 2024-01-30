#pragma once

#include <iostream>
#include <cstdint>

class ThreeDimensionalArray {
public:
    ThreeDimensionalArray(size_t x, size_t y, size_t z);
    ThreeDimensionalArray(const ThreeDimensionalArray& arr);
    ThreeDimensionalArray& operator=(const ThreeDimensionalArray& other);
    ~ThreeDimensionalArray();

    class CoordinateX;
    class CoordinateY;
    class CoordinateZ;

    CoordinateX operator[](size_t i) const;

    class CoordinateX {
    public:
        CoordinateX(uint8_t* data, size_t x_size, size_t y_size, size_t z_size, size_t bit_index);
        CoordinateY operator[](size_t j);
    private:
        uint8_t* data_;
        size_t x_size_;
        size_t y_size_;
        size_t z_size_;
        size_t bit_index_;
    };

    class CoordinateY {
    public:
        CoordinateY(uint8_t* data, size_t x_size, size_t y_size, size_t z_size, size_t bit_index);
        CoordinateZ operator[](size_t k);
    private:
        uint8_t* data_;
        size_t x_size_;
        size_t y_size_;
        size_t z_size_;
        size_t bit_index_;
    };

    class CoordinateZ {
    public:
        CoordinateZ(uint8_t* data, size_t x_size, size_t y_size, size_t z_size, size_t bit_index);
        CoordinateZ& operator=(uint32_t value);
        operator uint32_t() const;

    private:
        uint8_t* data_;
        size_t x_size_;
        size_t y_size_;
        size_t z_size_;
        size_t bit_index_;

        void SetBits(size_t start_bit_index, size_t end_bit_index, uint32_t value);
        void SetBit(size_t bit_index, uint8_t value);

        uint32_t GetBits(size_t start_bit_index, size_t end_bit_index) const;
        uint8_t GetBit(size_t bit_index) const;
    };

    friend std::istream& operator>>(std::istream& input,ThreeDimensionalArray& arr);
    friend std::ostream& operator<<(std::ostream& output, const ThreeDimensionalArray& arr);

    ThreeDimensionalArray operator*(uint32_t scalar) const;
    ThreeDimensionalArray operator+(const ThreeDimensionalArray& other) const;
    ThreeDimensionalArray operator-(const ThreeDimensionalArray& other) const;

    static ThreeDimensionalArray make_array(size_t x, size_t y, size_t z);
    size_t GetSize();
private:
    uint8_t* data_;
    size_t x_size_;
    size_t y_size_;
    size_t z_size_;
    size_t total_size_;
};
