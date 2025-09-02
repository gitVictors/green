#pragma once
#include "flight_provider.h"
#include "hotel_provider.h"

#include <string>
#include <vector>

class Trip {
private:
    HotelProvider& hotel_provider_;
    FlightProvider& flight_provider_;

public:
    using BookingId = int;


    std::vector<BookingId> flights;
    std::vector<BookingId> hotels;

    Trip(HotelProvider& hp, FlightProvider& fp):
        hotel_provider_(hp),
        flight_provider_(fp)
    {}



    Trip(const Trip& other) noexcept:
        hotel_provider_(other.hotel_provider_),
        flight_provider_(other.flight_provider_),
        flights(other.flights),
        hotels(other.hotels)
    {}

    Trip(Trip&& other) noexcept :
        hotel_provider_(other.hotel_provider_),
        flight_provider_(other.flight_provider_),
        flights( std::move(other.flights)),
        hotels(std::move(other.hotels))
    {
    }

    Trip& operator=(const Trip& other) =delete;
    Trip& operator=(Trip&& other) = delete;


    void Cancel(){

        for (auto& id : hotels) {
            hotel_provider_.Cancel(id);
        }
        hotels.clear();

        for (auto& id : flights) {
            flight_provider_.Cancel(id);
        }
        flights.clear();

    }

    ~Trip(){
        Cancel();
    }


};

class TripManager {
public:
    using BookingId = std::string;
    struct BookingData {
        std::string city_from;
        std::string city_to;
        std::string date_from;
        std::string date_to;
    };

    Trip Book(const BookingData&) {

        Trip trip(hotel_provider_, flight_provider_);
        {
            FlightProvider::BookingData flight_booking_data;
            trip.flights.push_back(flight_provider_.Book(flight_booking_data));
        }
        {
            HotelProvider::BookingData hotel_booking_data;
            trip.hotels.push_back(hotel_provider_.Book(hotel_booking_data));
        }
        {
            FlightProvider::BookingData flight_booking_data;
            trip.flights.push_back(flight_provider_.Book(flight_booking_data));
        }
        return trip;
    }

    void Cancel(Trip& trip) {
        trip.Cancel();
    }

private:
    HotelProvider hotel_provider_;
    FlightProvider flight_provider_;
};
