#pragma once

#include <utility>

using namespace std;

namespace raii {

template <typename Provider>
class Booking {
private:
    using BookingId = typename Provider::BookingId;

    Provider* provider_;
    BookingId booking_id_;

public:

    Booking(Provider* p, const BookingId& id):
        provider_(p),
        booking_id_(id)
    {}

    Booking(const Booking&) = delete;
    Booking& operator=(const Booking&)= delete;

    Booking(Booking&& other):
        provider_ (other.provider_),
        booking_id_( other.booking_id_)
    {}

    Booking& operator=(Booking&& other) {
        std::swap(provider_, other.provider_);
        std::swap(booking_id_, other.booking_id_);
        return *this;
    }


    ~Booking() {
        if (provider_ != nullptr) {
            provider_->CancelOrComplete(*this);
        }
    }

    // Эта функция не требуется в тестах, но в реальной программе она может быть нужна
    BookingId GetId() const;   
};

}//namespace
