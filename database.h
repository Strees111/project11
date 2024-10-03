#ifndef PROJECT11_DATABASE_H
#define PROJECT11_DATABASE_H

#include "List.h"
#include "Flight.h"
#include <fstream>
#include <iomanip>

class DataBase {
private:
    List<Flight> data;

    List<Flight>::Node *mergeSortRec(List<Flight>::Node *node);

    void split(List<Flight>::Node *source, List<Flight>::Node **frontRef, List<Flight>::Node **backRef);

    List<Flight>::Node *sortedMerge(List<Flight>::Node *a, List<Flight>::Node *b);

    List<Flight>::Node *sortedMerge1(List<Flight>::Node *a, List<Flight>::Node *b);

    void split1(List<Flight>::Node *source, List<Flight>::Node **frontRef, List<Flight>::Node **backRef);

    List<Flight>::Node *mergeSortRec1(List<Flight>::Node *node);

public:
    DataBase();

    ~DataBase();

    void add(const Flight &flight);

    void delete_ID(int id);

    void clear();

    void print();

    void load(const char *name_file);

    void save(const char *name_file) const;

    void schedule(const char *str, const char *date);

    void from(const char *air_dep, const char *air_arr, const char *date);

    void find(const char *air_dep, const char *air_arr);

    void buy(const char *number_of_flight, const char *date);

    void export_(std::ofstream &os);

    void sort_by_date_time_and_number_and_airfare_and_quantity();

    void sort_by_date_time_and_airfare();
};

void DataBase::add(const Flight &flight) {
    data.push_back(flight);
}

void DataBase::delete_ID(int id) {
    if (data.head == nullptr) {
        return;
    }
    if (data.head->data.id == id) {
        data.pop_front();
        return;
    }
    List<Flight>::Node *p = data.head;
    while (p->next != nullptr && p->next->data.id != id) {
        p = p->next;
    }
    if (p->next != nullptr) {
        List<Flight>::Node *q = p->next;
        if (p->next == data.tail) {
            p->next = nullptr;
            data.tail = p;
        } else {
            p->next = q->next;
        }
        delete q;
    }
}

void DataBase::clear() {
    List<Flight>::Node *p = data.head;
    List<Flight>::Node *q = nullptr;
    while (p != nullptr) {
        if (p->data.number_of_tickets == 0) {
            q = p->next;
            delete_ID(p->data.id);
            p = q;
        } else {
            p = p->next;
        }
    }
}

void DataBase::print() {
    sort_by_date_time_and_number_and_airfare_and_quantity();
    for (List<Flight>::Node *p = data.head; p != nullptr; p = p->next) {
        std::cout << p->data.id << ", " << p->data.flight_number << ", " << p->data.departure_airport << ", "
                  << p->data.arrival_airport << ", " << p->data.departure_date.year << '.'
                  << p->data.departure_date.month / 10
                  << p->data.departure_date.month % 10
                  << '.'
                  << p->data.departure_date.day / 10 << p->data.departure_date.day % 10 << ' '
                  << p->data.departure_time.hour / 10 << p->data.departure_time.hour % 10 << ':'
                  << p->data.departure_time.minute / 10 << p->data.departure_time.minute % 10 << ", "
                  << p->data.arrival_date.year / 10 << p->data.arrival_date.year % 10 << '.'
                  << p->data.arrival_date.month / 10 << p->data.arrival_date.month % 10 << '.'
                  << p->data.arrival_date.day / 10 << p->data.arrival_date.day % 10 << ' '
                  << p->data.arrival_time.hour / 10 << p->data.arrival_time.hour % 10 << ':'
                  << p->data.arrival_time.minute / 10 << p->data.arrival_time.minute % 10 << ", "
                  << p->data.number_of_tickets << ", " << std::fixed << std::setprecision(2) << p->data.airfare
                  << std::endl;
    }
}

void DataBase::export_(std::ofstream &os) {
    sort_by_date_time_and_number_and_airfare_and_quantity();
    for (List<Flight>::Node *p = data.head; p != nullptr; p = p->next) {
        os << p->data.flight_number << ", " << p->data.departure_airport << ", "
           << p->data.arrival_airport << ", " << p->data.departure_date.year
           << '.' << p->data.departure_date.month / 10 << p->data.departure_date.month % 10
           << '.'
           << p->data.departure_date.day / 10 << p->data.departure_date.day % 10 << ' '
           << p->data.departure_time.hour / 10 << p->data.departure_time.hour % 10 << ':'
           << p->data.departure_time.minute / 10 << p->data.departure_time.minute % 10 << ", "
           << p->data.arrival_date.year / 10 << p->data.arrival_date.year % 10 << '.' << p->data.arrival_date.month / 10
           << p->data.arrival_date.month % 10 << '.'
           << p->data.arrival_date.day / 10 << p->data.arrival_date.day % 10 << ' ' << p->data.arrival_time.hour / 10
           << p->data.arrival_time.hour % 10 << ':' << p->data.arrival_time.minute / 10
           << p->data.arrival_time.minute % 10 << p->data.number_of_tickets << ", " << std::fixed
           << std::setprecision(2) << p->data.airfare
           << std::endl;
    }
}

void DataBase::schedule(const char *str, const char *date) {
    Flight::date d(date);
    sort_by_date_time_and_number_and_airfare_and_quantity();
    for (List<Flight>::Node *p = data.head; p != nullptr; p = p->next) {
        if (strcmp(p->data.departure_airport, str) == 0 && p->data.departure_date.year == d.year &&
            p->data.departure_date.month == d.month && p->data.departure_date.day == d.day) {
            std::cout << p->data.flight_number << ", " << p->data.arrival_airport << ", "
                      << p->data.departure_time.hour / 10 << p->data.departure_time.hour % 10
                      << ":" << p->data.departure_time.minute / 10 << p->data.departure_time.minute % 10 << std::endl;
        }
    }
}

void DataBase::from(const char *air_dep, const char *air_arr, const char *date) {
    Flight::date d(date);
    int i = 0;
    sort_by_date_time_and_airfare();
    for (List<Flight>::Node *p = data.head; p != nullptr; p = p->next) {
        if (p->data.number_of_tickets > 0 && strcmp(p->data.departure_airport, air_dep) == 0 &&
            strcmp(p->data.arrival_airport, air_arr) == 0 && p->data.departure_date.year == d.year &&
            p->data.departure_date.month == d.month && p->data.departure_date.day == d.day) {
            std::cout << p->data.flight_number << ", " << p->data.departure_airport << ", "
                      << p->data.arrival_airport << ", " << p->data.departure_date.year << '.'
                      << p->data.departure_date.month / 10
                      << p->data.departure_date.month % 10
                      << '.'
                      << p->data.departure_date.day / 10 << p->data.departure_date.day % 10 << ' '
                      << p->data.departure_time.hour / 10 << p->data.departure_time.hour % 10 << ':'
                      << p->data.departure_time.minute / 10 << p->data.departure_time.minute % 10 << ", "
                      << p->data.arrival_date.year / 10 << p->data.arrival_date.year % 10 << '.'
                      << p->data.arrival_date.month / 10 << p->data.arrival_date.month % 10 << '.'
                      << p->data.arrival_date.day / 10 << p->data.arrival_date.day % 10 << ' '
                      << p->data.arrival_time.hour / 10 << p->data.arrival_time.hour % 10 << ':'
                      << p->data.arrival_time.minute / 10 << p->data.arrival_time.minute % 10 << ", "
                      << p->data.number_of_tickets << ", " << std::fixed << std::setprecision(2) << p->data.airfare
                      << std::endl;
            ++i;
        }
    }
    if (i == 0) {
        std::cout << "no tickets" << std::endl;
    }
}

void DataBase::find(const char *air_dep, const char *air_arr) {
    List<Flight>::Node *min_direct_flight = nullptr;
    for (List<Flight>::Node *p = data.head; p != nullptr; p = p->next) {
        if (strcmp(air_dep, p->data.departure_airport) == 0 && strcmp(air_arr, p->data.arrival_airport) == 0) {
            if (min_direct_flight == nullptr) {
                min_direct_flight = p;
            }
            if (p->data.airfare < min_direct_flight->data.airfare) {
                min_direct_flight = p;
            }
        }
    }
    float min_connecting_flight = 1.0f / 0.0f;
    List<Flight>::Node *first = nullptr;
    List<Flight>::Node *second = nullptr;
    for (List<Flight>::Node *p = data.head; p != nullptr; p = p->next) {
        if (strcmp(p->data.departure_airport, air_dep) == 0) {
            for (List<Flight>::Node *q = data.head; q != nullptr; q = q->next) {
                if (strcmp(q->data.arrival_airport, air_arr) == 0 &&
                    strcmp(p->data.arrival_airport, q->data.departure_airport) == 0) {
                    if (p->data.airfare + q->data.airfare < min_connecting_flight) {
                        min_connecting_flight = p->data.airfare + q->data.airfare;
                        first = p;
                        second = q;
                    }
                }
            }
        }
    }
    if (min_direct_flight == nullptr && first == nullptr) {
        std::cout << "no tickets" << std::endl;
    } else if (min_direct_flight == nullptr && first != nullptr) {
        std::cout << first->data.flight_number << ", " << first->data.departure_airport << ", "
                  << first->data.arrival_airport << ", " << first->data.departure_date.year << '.'
                  << first->data.departure_date.month / 10
                  << first->data.departure_date.month % 10
                  << '.'
                  << first->data.departure_date.day / 10 << first->data.departure_date.day % 10 << ' '
                  << first->data.departure_time.hour / 10 << first->data.departure_time.hour % 10 << ':'
                  << first->data.departure_time.minute / 10 << first->data.departure_time.minute % 10 << ", "
                  << first->data.arrival_date.year / 10 << first->data.arrival_date.year % 10 << '.'
                  << first->data.arrival_date.month / 10 << first->data.arrival_date.month % 10 << '.'
                  << first->data.arrival_date.day / 10 << first->data.arrival_date.day % 10 << ' '
                  << first->data.arrival_time.hour / 10 << first->data.arrival_time.hour % 10 << ':'
                  << first->data.arrival_time.minute / 10 << first->data.arrival_time.minute % 10 << ", "
                  << first->data.number_of_tickets << ", " << std::fixed << std::setprecision(2) << first->data.airfare
                  << std::endl;
        std::cout << second->data.flight_number << ", " << second->data.departure_airport << ", "
                  << second->data.arrival_airport << ", " << second->data.departure_date.year << '.'
                  << second->data.departure_date.month / 10
                  << second->data.departure_date.month % 10
                  << '.'
                  << second->data.departure_date.day / 10 << second->data.departure_date.day % 10 << ' '
                  << second->data.departure_time.hour / 10 << second->data.departure_time.hour % 10 << ':'
                  << second->data.departure_time.minute / 10 << second->data.departure_time.minute % 10 << ", "
                  << second->data.arrival_date.year / 10 << second->data.arrival_date.year % 10 << '.'
                  << second->data.arrival_date.month / 10 << second->data.arrival_date.month % 10 << '.'
                  << second->data.arrival_date.day / 10 << second->data.arrival_date.day % 10 << ' '
                  << second->data.arrival_time.hour / 10 << second->data.arrival_time.hour % 10 << ':'
                  << second->data.arrival_time.minute / 10 << second->data.arrival_time.minute % 10 << ", "
                  << second->data.number_of_tickets << ", " << std::fixed << std::setprecision(2)
                  << second->data.airfare
                  << std::endl;
    } else if (min_direct_flight != nullptr && first == nullptr) {
        std::cout << min_direct_flight->data.flight_number << ", " << min_direct_flight->data.departure_airport << ", "
                  << min_direct_flight->data.arrival_airport << ", " << min_direct_flight->data.departure_date.year
                  << '.' << min_direct_flight->data.departure_date.month / 10
                  << min_direct_flight->data.departure_date.month % 10
                  << '.'
                  << min_direct_flight->data.departure_date.day / 10 << min_direct_flight->data.departure_date.day % 10
                  << ' '
                  << min_direct_flight->data.departure_time.hour / 10
                  << min_direct_flight->data.departure_time.hour % 10 << ':'
                  << min_direct_flight->data.departure_time.minute / 10
                  << min_direct_flight->data.departure_time.minute % 10 << ", "
                  << min_direct_flight->data.arrival_date.year / 10 << min_direct_flight->data.arrival_date.year % 10
                  << '.'
                  << min_direct_flight->data.arrival_date.month / 10 << min_direct_flight->data.arrival_date.month % 10
                  << '.'
                  << min_direct_flight->data.arrival_date.day / 10 << min_direct_flight->data.arrival_date.day % 10
                  << ' '
                  << min_direct_flight->data.arrival_time.hour / 10 << min_direct_flight->data.arrival_time.hour % 10
                  << ':'
                  << min_direct_flight->data.arrival_time.minute / 10
                  << min_direct_flight->data.arrival_time.minute % 10 << ", "
                  << min_direct_flight->data.number_of_tickets
                  << ", " << std::fixed << std::setprecision(2) << min_direct_flight->data.airfare
                  << std::endl;
    } else if (min_direct_flight != nullptr && first != nullptr) {
        if (min_direct_flight->data.airfare > min_connecting_flight) {
            std::cout << first->data.flight_number << ", " << first->data.departure_airport << ", "
                      << first->data.arrival_airport << ", " << first->data.departure_date.year << '.'
                      << first->data.departure_date.month / 10
                      << first->data.departure_date.month % 10
                      << '.'
                      << first->data.departure_date.day / 10 << first->data.departure_date.day % 10 << ' '
                      << first->data.departure_time.hour / 10 << first->data.departure_time.hour % 10 << ':'
                      << first->data.departure_time.minute / 10 << first->data.departure_time.minute % 10 << ", "
                      << first->data.arrival_date.year / 10 << first->data.arrival_date.year % 10 << '.'
                      << first->data.arrival_date.month / 10 << first->data.arrival_date.month % 10 << '.'
                      << first->data.arrival_date.day / 10 << first->data.arrival_date.day % 10 << ' '
                      << first->data.arrival_time.hour / 10 << first->data.arrival_time.hour % 10 << ':'
                      << first->data.arrival_time.minute / 10 << first->data.arrival_time.minute % 10 << ", "
                      << first->data.number_of_tickets << ", " << std::fixed << std::setprecision(2)
                      << first->data.airfare
                      << std::endl;
            std::cout << second->data.flight_number << ", " << second->data.departure_airport << ", "
                      << second->data.arrival_airport << ", " << second->data.departure_date.year << '.'
                      << second->data.departure_date.month / 10
                      << second->data.departure_date.month % 10
                      << '.'
                      << second->data.departure_date.day / 10 << second->data.departure_date.day % 10 << ' '
                      << second->data.departure_time.hour / 10 << second->data.departure_time.hour % 10 << ':'
                      << second->data.departure_time.minute / 10 << second->data.departure_time.minute % 10 << ", "
                      << second->data.arrival_date.year / 10 << second->data.arrival_date.year % 10 << '.'
                      << second->data.arrival_date.month / 10 << second->data.arrival_date.month % 10 << '.'
                      << second->data.arrival_date.day / 10 << second->data.arrival_date.day % 10 << ' '
                      << second->data.arrival_time.hour / 10 << second->data.arrival_time.hour % 10 << ':'
                      << second->data.arrival_time.minute / 10 << second->data.arrival_time.minute % 10 << ", "
                      << second->data.number_of_tickets << ", " << std::fixed << std::setprecision(2)
                      << second->data.airfare
                      << std::endl;
        } else {
            std::cout << min_direct_flight->data.flight_number << ", " << min_direct_flight->data.departure_airport
                      << ", "
                      << min_direct_flight->data.arrival_airport << ", " << min_direct_flight->data.departure_date.year
                      << '.' << min_direct_flight->data.departure_date.month / 10
                      << min_direct_flight->data.departure_date.month % 10
                      << '.'
                      << min_direct_flight->data.departure_date.day / 10
                      << min_direct_flight->data.departure_date.day % 10 << ' '
                      << min_direct_flight->data.departure_time.hour / 10
                      << min_direct_flight->data.departure_time.hour % 10 << ':'
                      << min_direct_flight->data.departure_time.minute / 10
                      << min_direct_flight->data.departure_time.minute % 10 << ", "
                      << min_direct_flight->data.arrival_date.year / 10
                      << min_direct_flight->data.arrival_date.year % 10 << '.'
                      << min_direct_flight->data.arrival_date.month / 10
                      << min_direct_flight->data.arrival_date.month % 10 << '.'
                      << min_direct_flight->data.arrival_date.day / 10 << min_direct_flight->data.arrival_date.day % 10
                      << ' '
                      << min_direct_flight->data.arrival_time.hour / 10
                      << min_direct_flight->data.arrival_time.hour % 10 << ':'
                      << min_direct_flight->data.arrival_time.minute / 10
                      << min_direct_flight->data.arrival_time.minute % 10 << ", "
                      << min_direct_flight->data.number_of_tickets
                      << ", " << std::fixed << std::setprecision(2) << min_direct_flight->data.airfare
                      << std::endl;
        }
    }
}

void DataBase::buy(const char *number_of_flight, const char *date) {
    Flight::date d(date);
    List<Flight>::Node *n = data.head;
    for (List<Flight>::Node *p = data.head; p != nullptr; p = p->next) {
        if (strcmp(p->data.flight_number, number_of_flight) == 0 && p->data.departure_date.year == d.year &&
            p->data.departure_date.month == d.month &&
            p->data.departure_date.day == d.day) {
            if (p->data.airfare <= n->data.airfare) {
                n = p;
            }
        }
    }
    if (n->data.number_of_tickets != 0) {
        --n->data.number_of_tickets;
        std::cout << std::fixed << std::setprecision(2) << n->data.airfare << std::endl;
    } else {
        std::cout << "no tickets" << std::endl;
    }
}

void DataBase::sort_by_date_time_and_number_and_airfare_and_quantity() {
    data.head = mergeSortRec(data.head);
}

List<Flight>::Node *DataBase::mergeSortRec(List<Flight>::Node *node) {
    if (!node || !node->next) return node;
    List<Flight>::Node *left;
    List<Flight>::Node *right;
    split(node, &left, &right);
    left = mergeSortRec(left);
    right = mergeSortRec(right);
    return sortedMerge(left, right);
}

void DataBase::split(List<Flight>::Node *source, List<Flight>::Node **frontRef, List<Flight>::Node **backRef) {
    List<Flight>::Node *fast = source->next;
    List<Flight>::Node *slow = source;
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

List<Flight>::Node *DataBase::sortedMerge(List<Flight>::Node *a, List<Flight>::Node *b) {
    List<Flight>::Node *result;
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    int time_a = a->data.departure_time.hour * 60 + a->data.departure_time.minute;
    int time_b = b->data.departure_time.hour * 60 + b->data.departure_time.minute;
    int date_a = JulianDate(a->data.departure_date);
    int date_b = JulianDate(b->data.departure_date);
    if ((date_a < date_b) || (date_a == date_b && time_a < time_b) ||
        (date_a == date_b && time_a == time_b && strcmp(a->data.flight_number, b->data.flight_number) < 0) ||
        (date_a == date_b && time_a == time_b && strcmp(a->data.flight_number, b->data.flight_number) == 0 &&
         a->data.airfare < b->data.airfare)) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}

void DataBase::sort_by_date_time_and_airfare() {
    data.head = mergeSortRec1(data.head);
}

List<Flight>::Node *DataBase::mergeSortRec1(List<Flight>::Node *node) {
    if (!node || !node->next) return node;
    List<Flight>::Node *left;
    List<Flight>::Node *right;
    split1(node, &left, &right);
    left = mergeSortRec1(left);
    right = mergeSortRec1(right);
    return sortedMerge1(left, right);
}

void DataBase::split1(List<Flight>::Node *source, List<Flight>::Node **frontRef, List<Flight>::Node **backRef) {
    List<Flight>::Node *fast = source->next;
    List<Flight>::Node *slow = source;
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

List<Flight>::Node *DataBase::sortedMerge1(List<Flight>::Node *a, List<Flight>::Node *b) {
    List<Flight>::Node *result;
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    int time_a = a->data.departure_time.hour * 60 + a->data.departure_time.minute;
    int time_b = b->data.departure_time.hour * 60 + b->data.departure_time.minute;
    if ((time_a < time_b) || (time_a == time_b && a->data.airfare < b->data.airfare)) {
        result = a;
        result->next = sortedMerge1(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge1(a, b->next);
    }
    return result;
}

void DataBase::load(const char *name_file) {
    std::ifstream in_file(name_file, std::ios_base::binary);
    if (!in_file.is_open()) {
        std::cout << "Can not open database" << std::endl;
        return;
    }
    data.clear();
    while (in_file) {
        Flight flight;
        in_file.read(reinterpret_cast<char *>(&flight.id), sizeof(flight.id));
        in_file.read(flight.flight_number, sizeof(flight.flight_number));
        in_file.read(flight.departure_airport, sizeof(flight.departure_airport));
        in_file.read(flight.arrival_airport, sizeof(flight.arrival_airport));
        in_file.read(reinterpret_cast<char *>(&flight.departure_date), sizeof(flight.departure_date));
        in_file.read(reinterpret_cast<char *>(&flight.arrival_date), sizeof(flight.arrival_date));
        in_file.read(reinterpret_cast<char *>(&flight.departure_time), sizeof(flight.departure_time));
        in_file.read(reinterpret_cast<char *>(&flight.arrival_time), sizeof(flight.arrival_time));
        in_file.read(reinterpret_cast<char *>(&flight.number_of_tickets), sizeof(flight.number_of_tickets));
        in_file.read(reinterpret_cast<char *>(&flight.airfare), sizeof(flight.airfare));
        if (in_file) {
            data.push_back(flight);
        }
    }
    in_file.close();
}

void DataBase::save(const char *name_file) const {
    std::ofstream out_file(name_file, std::ios_base::binary);
    if (!out_file.is_open()) {
        std::cout << "Can not write to file" << std::endl;
        return;
    }
    for (List<Flight>::Node *p = data.head; p != nullptr; p = p->next) {
        out_file.write(reinterpret_cast<const char *> (&p->data.id), sizeof(p->data.id));
        out_file.write(p->data.flight_number, sizeof(p->data.flight_number));
        out_file.write(p->data.departure_airport, sizeof(p->data.departure_airport));
        out_file.write(p->data.arrival_airport, sizeof(p->data.arrival_airport));
        out_file.write(reinterpret_cast<const char *>(&p->data.departure_date), sizeof(p->data.departure_date));
        out_file.write(reinterpret_cast<const char *>(&p->data.arrival_date), sizeof(p->data.arrival_date));
        out_file.write(reinterpret_cast<const char *>(&p->data.departure_time), sizeof(p->data.departure_time));
        out_file.write(reinterpret_cast<const char *>(&p->data.arrival_time), sizeof(p->data.arrival_time));
        out_file.write(reinterpret_cast<const char *>(&p->data.number_of_tickets), sizeof(p->data.number_of_tickets));
        out_file.write(reinterpret_cast<const char *>(&p->data.airfare), sizeof(p->data.airfare));
    }
    out_file.close();
}

DataBase::~DataBase() = default;

DataBase::DataBase() = default;

#endif
