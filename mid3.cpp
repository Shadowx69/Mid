#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Reservation
{
public:
    string customerName;
    string reservationTime;
    int numberOfGuests;

    Reservation(string name, string time, int guests)
        : customerName(name), reservationTime(time), numberOfGuests(guests) {}
};

class Restaurant
{
private:
    vector<string> availableSlots;
    vector<Reservation> reservations;

public:
    Restaurant()
    {
        availableSlots = {"18:00", "19:00", "20:00", "21:00"};
    }

    void displayAvailableSlots()
    {
        cout << "Available Time Slots:\n";
        for (const auto &slot : availableSlots)
        {
            cout << slot << "\n";
        }
    }

    bool makeReservation(string name, string time, int guests)
    {

        for (auto it = availableSlots.begin(); it != availableSlots.end(); ++it)
        {
            if (*it == time)
            {
                reservations.push_back(Reservation(name, time, guests));

                availableSlots.erase(it);
                return true;
            }
        }
        return false;
    }

    bool cancelReservation(string name, string time)
    {
        bool reservationFound = false;
        for (auto it = reservations.begin(); it != reservations.end();)
        {
            if (it->customerName == name && it->reservationTime == time)
            {
                it = reservations.erase(it);
                reservationFound = true;

                availableSlots.push_back(time);
            }
            else
            {
                ++it;
            }
        }
        return reservationFound;
    }
};

int main()
{
    Restaurant myRestaurant;
    string customerName, reservationTime;
    int numberOfGuests;

    while (true)
    {
        cout << "\nWelcome to the Restaurant Reservation System\n";
        myRestaurant.displayAvailableSlots();

        cout << "Please enter your name: ";
        getline(std::cin, customerName);

        cout << "Select a time slot: ";
        getline(std::cin, reservationTime);

        cout << "Enter the number of guests: ";
        cin >> numberOfGuests;
        cin.ignore();

        if (myRestaurant.makeReservation(customerName, reservationTime, numberOfGuests))
        {
            cout << "Reservation made successfully!\n";
        }
        else
        {
            cout << "Sorry, that time slot is not available. Please try another one.\n";
        }

        cout << "Would you like to cancel a reservation? (yes/no): ";
        string response;
        getline(std::cin, response);
        if (response == "yes")
        {
            cout << "Please enter the name used for the reservation: ";
            getline(cin, customerName);

            cout << "Please enter the time slot of the reservation: ";
            getline(cin, reservationTime);

            if (myRestaurant.cancelReservation(customerName, reservationTime))
            {
                cout << "Reservation cancelled successfully.\n";
            }
            else
            {
                cout << "No reservation found under that name and time slot.\n";
            }
        }
    }

    return 0;
}
