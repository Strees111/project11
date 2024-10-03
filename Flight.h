#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <cstring>

struct Flight {
    int id = 0;
    char flight_number[8];
    char departure_airport[4];
    char arrival_airport[4];

    struct time {
        int hour;
        int minute;

        explicit time(const char *str);
    };

    struct date {
        int year;
        int month;
        int day;

        explicit date(const char *str);
    };

    date departure_date;
    date arrival_date;
    time departure_time;
    time arrival_time;
    int number_of_tickets = 0;
    float airfare = 0;

    Flight();

    Flight(const char *number, const char *dep_airport, const char *arr_airport, const char *dep_date,
           const char *dep_time,
           const char *arr_date, const char *arr_time, int quantity, float price);

    ~Flight() = default;
};

Flight::date::date(const char *str) {
    int index = 0;
    int counter = 0;
    for (size_t i = 0; i < strlen(str); ++i) {
        if ((str[i] < '0' && str[i] != '.') || str[i] > '9') {
            std::cout << "Wrong date format: " << str << std::endl;
            break;
        }
        char a[5];
        a[index++] = str[i];
        if (str[i] == '.') {
            switch (counter) {
                case 0:
                    day = atoi(a);
                    if (day < 1 || day > 31) {
                        std::cout << "Day value is invalid: " << day << std::endl;
                    }
                    break;
                case 1:
                    month = atoi(a);
                    if (month < 1 || month > 12) {
                        std::cout << "Month value is invalid: " << month << std::endl;
                    }
                    break;
            }
            for (int j = 0; j < 5; ++j) {
                a[j] = '\0';
            }
            index = 0;
            ++counter;
        }
        if (str[i + 1] == '\0' && counter == 2) {
            year = atoi(a);
            if (year < 2000 || year > 9999) {
                std::cout << "Year value is invalid: " << year << std::endl;
                break;
            }
        }
    }
}


Flight::Flight(const char *number, const char *dep_airport, const char *arr_airport, const char *dep_date,
               const char *dep_time,
               const char *arr_date, const char *arr_time, int quantity, float price) : departure_date(dep_date),
                                                                                        arrival_date(arr_date),
                                                                                        departure_time(dep_time),
                                                                                        arrival_time(arr_time),
                                                                                        number_of_tickets(quantity),
                                                                                        airfare(price) {
    static int id_number;
    this->id = ++id_number;
    memcpy(this->flight_number, number, 7);
    this->flight_number[7] = '\0';
    memcpy(this->departure_airport, dep_airport, 3);
    this->departure_airport[3] = '\0';
    memcpy(this->arrival_airport, arr_airport, 3);
    this->arrival_airport[3] = '\0';
}

Flight::Flight()
        : flight_number{}, departure_airport{}, arrival_airport{}, departure_date{"11.11.2000"},
          arrival_date{"11.11.2000"}, departure_time{"11:11"}, arrival_time{"11:11"} {}

Flight::time::time(const char *str) {
    int index = 0;
    int counter = 0;
    for (size_t i = 0; i < strlen(str); ++i) {
        if (str[i] < '0' || (str[i] > '9' && str[i] != ':')) {
            std::cout << "Wrong time format: " << str << std::endl;
            break;
        }
        char a[5];
        a[index++] = str[i];
        if (str[i] == ':' && counter == 0) {
            hour = atoi(a);
            if (hour < 0 || hour > 23) {
                std::cout << "Time value is invalid: " << str << std::endl;
                break;
            }
            for (int j = 0; j < 5; ++j) {
                a[j] = '\0';
            }
            index = 0;
            ++counter;
        }
        if (str[i + 1] == '\0' && counter == 1) {
            minute = atoi(a);
            if (minute < 0 || minute > 59) {
                std::cout << "Time value is invalid: " << str << std::endl;
                break;
            }
        }
    }
}

int JulianDate(const Flight::date &date) {
    int a = (14 - date.month) / 12;
    int y = date.year + 4800 - a;
    int m = date.month + 12 * a - 3;
    int JD = date.day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    return JD;
}

bool CheakDate(const Flight::time &departure, const Flight::time &arrival, const Flight::date &departure1,
               const Flight::date &arrival1) {
    if (JulianDate(departure1) <= JulianDate(arrival1)) {
        if ((departure.hour * 60 + departure.minute) < (arrival.hour * 60 + arrival.minute)) {
            return true;
        }
    }
    return false;
}

#endif //FLIGHT_H
