#pragma once

#include <array>
#include <stdexcept>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0): size_(a_size) {
        if (a_size > N){
            throw invalid_argument("a_size to much");
        }
    }

    T& operator[](size_t index){
        if (index >= size_) throw out_of_range("Index out of range");
        return arr_vect_[index];
    }

    const T& operator[](size_t index) const{
        if (index >= size_) throw out_of_range("Index out of range");
        return arr_vect_[index];
    }

    typename array<T,N>::iterator begin(){
        return arr_vect_.begin();
    }

    typename array<T,N>::iterator end(){
        return (arr_vect_.begin() + size_);

    }

    typename array<T,N>::const_iterator begin() const{
        return arr_vect_.begin();
    }


    typename array<T,N> ::const_iterator end() const{
        return arr_vect_.begin() + size_;
    }

    size_t Size() const{
        return size_;
    }
    size_t Capacity() const{
        return N;
    }

    void PushBack(const T& value){
        if (size_ >= N){
            throw std::overflow_error("StackVector is full");
        }
        arr_vect_[size_++] = value;
    }

    T PopBack(){
        if (size_ == 0){
            throw std::underflow_error("StackVector is empty");
        }
        return arr_vect_[--size_];
    }

private:
    std::array<T,N> arr_vect_;
    size_t size_ = 0;

};
