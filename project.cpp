#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Reservation {
public:
    string name;
    int seatnumber;
    Reservation* next = nullptr;

    Reservation(string name, int seatnumber) : name(name), seatnumber(seatnumber) {}
};

Reservation* head = nullptr;
Reservation* tail = nullptr;

class Vehicle {

    int totalSeats;
    string servicename;
    float fare;
    bool isBooked;
    int* availableseats;

public:
    Vehicle(string servicename, int totalSeats, float fare) : servicename(servicename), totalSeats(totalSeats), fare(fare) , isBooked(false){
        availableseats = new int[totalSeats];
        for (int i = 0; i < totalSeats; ++i) {
            availableseats[i] = i + 1;
        }
    }
   

    ~Vehicle() {
        delete[] availableseats;
    }

    void reserveSeat(string name, int numberOfPassengers, int* seatnumbers);
    void reserveWholeVehicle(string name);
    void cancelReservation();
    void displayStatus();
    bool isVehicleBooked() {return isBooked; }
    string getServicename() { return servicename; }
    float getFare() { return fare; }
    void setFare(float newFare) { fare = newFare; }
};

void Vehicle::reserveSeat(string name, int numberOfPassengers, int* seatnumbers) {
    for (int i = 0; i < numberOfPassengers ; ++i) {
        int seatnumber = seatnumbers[i];
        if (seatnumber < 1 || seatnumber > totalSeats || availableseats[seatnumber - 1] == 0) {
            cout << "Invalid seat number " << seatnumber << ". Please choose a valid or unreserved seat." << endl;
            return;
        }
    }

    if (isBooked) {
        cout << servicename << " is already booked. You cannot reserve individual seats." << endl;
        return;
    }

    float totalCost = numberOfPassengers * fare;

    for (int i = 0; i < numberOfPassengers; ++i) {
        int seatnumber = seatnumbers[i];
        availableseats[seatnumber - 1] = 0;

        Reservation* newNode = new Reservation(name, seatnumber);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next=newNode;
          
            tail = newNode;
        }
    }


    for (int i = 0; i < numberOfPassengers; ++i) {
        cout <<"seat " <<seatnumbers[i] <<" " ;
    }
    cout << "reserved for " << name << ". Total Cost: Rs" << totalCost << endl;
}

void Vehicle::reserveWholeVehicle(string name) {
    if (isBooked) {
        cout << servicename << " is already booked." << endl;
        return;
    }

    isBooked = true;

    if (servicename == "Bus") {
        fare = totalSeats * 1000; 
    }
   if (servicename == "Cab") { }
    cout << servicename << " reserved for " << name << ". Fare: Rs" << fare << " for the whole vehicle." << endl;
}

void Vehicle::cancelReservation() {
    if (!isBooked) {
        cout << servicename << " is not booked." << endl;
        return;
    }

    Reservation* temp = head;
    while (temp != nullptr) {
        Reservation* nextNode = temp->next;
        availableseats[temp->seatnumber - 1] = temp->seatnumber;
        delete temp;
        temp = nextNode;
    }

    head = nullptr;
    tail = nullptr;
    isBooked = false;

    cout << servicename << " reservation canceled." << endl;
}

void Vehicle::displayStatus() {
   
    cout << endl;
    if (!isBooked) {
        cout<<"occupied seats:";
       
    
    Reservation* temp = head;
    while (temp != nullptr) {
        cout << temp->seatnumber << " ";
        temp = temp->next;
    }
    cout << endl;

    cout << "Available Seats: ";
    for (int i = 0; i < totalSeats; ++i) {
        if (availableseats[i] != 0) {
            cout << availableseats[i] << " ";
        }
    }
    cout<<endl;
    
     cout << servicename << " is available for reservation." << endl;
        return;
    }
   else{
    cout << servicename << " is fully booked" ;
    if (head->next != nullptr) {
        cout << " and others.";
    }
   }
    cout << endl;
 
}

int getNumberOfPassengers() {
    int passengers;
    cout << "Enter the number of passengers: ";
    cin >> passengers;
    return passengers;
}

int main() {
    int choice, ch;
    string name;
    string num;
    int numberOfPassengers;
    int* seatnumbers;

    int locationChoice;
    cout << "____________________________________________________" << endl;
    cout << "|                                                  |" << endl;
    cout << "|   welcome to travel agency                       |" << endl;
    cout << "|          your travel buddy:)                     |" << endl;
    cout << "|__________________________________________________|" << endl;
    cout << endl;
    cout << "our services are available for these locations" << endl;

    cout << "select where to travel :" << endl;
    cout << endl;
    cout << "1. From Location Kathmandu to Location Biratnagar" << endl;
    cout << "2. From Location Kathmandu to Location Sinduli" << endl;
    cout << "3. From Location Kathmandu to Location Dhulikhel" << endl;
    cout << "4. From Location Kathmandu to Location Pokhara" << endl;
    cout << endl;
    cout << "Enter your choice: ";
    
    cin >> locationChoice;
  
    
    
    float busFare = 100;
    Vehicle bus("Bus", 36, busFare);

    float cabFare = 2000;
    Vehicle cab("Cab", 1, cabFare);
    switch (locationChoice) {
        case 1:
            bus.setFare(2000);
            cab.setFare(10000);
            break;
        case 2:
            bus.setFare(500);
            cab.setFare(6000);
            break;
        case 3:
            bus.setFare(100);
            cab.setFare(3000);
            break;
        case 4:
            bus.setFare(1000);
            cab.setFare(8000);
            break;
        default:
            cout << "we don't have service in other places" << endl;
    }

    do {
        cout << "1. Bus Service (Fare for a seat: Rs" << bus.getFare() << ")" << endl;
        cout << "2. Cab Service (Fare for a cab: Rs" << cab.getFare() << ")" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;

        Vehicle* currentService;

        switch (ch) {
            case 1:
                currentService = &bus;
                break;

            case 2:
                currentService = &cab;
                break;
            case 0:
                cout << "Exiting the program." << endl;
                continue;
            default:
                cout << "Invalid we have only car and bus option" << endl;
                continue;
        }

        do {
            cout << endl;
            cout << "1. Reserve " << currentService->getServicename() << " Seat(s)" << endl;
            if (currentService->getServicename() == "Bus") {
                cout << "2. Reserve whole " << currentService->getServicename() << endl;
            }
            cout << "3. Cancel Reservation" << endl;
            cout << "4. Display Status" << endl;
            cout << "0. Back to Main Menu" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    cout << "Enter your name: ";
                    cin >> name;
                    cout << "enter your contact number" << endl;
                    cin >> num;
                    if (currentService->getServicename() == "Cab") {
                     currentService->reserveWholeVehicle(name);
                    } else {
                        numberOfPassengers = getNumberOfPassengers();
                        seatnumbers = new int[numberOfPassengers];
                        for (int i = 0; i < numberOfPassengers; ++i) {
                            cout << "Enter seat number for passenger " << i + 1 << ": ";
                            cin >> seatnumbers[i];
                        }
                        currentService->reserveSeat(name, numberOfPassengers, seatnumbers);
                        delete[] seatnumbers;
                    }
                } break;

                case 2:
                    if (currentService->getServicename() == "Bus") {
                        cout << "Reserving the whole bus." << endl;
                        currentService->reserveWholeVehicle(name);
                    } else {
                        cout << "Invalid option for " << currentService->getServicename() << "." << endl;
                    }
                    break;

                case 3:
                    currentService->cancelReservation();
                    break;

                case 4:
                    currentService->displayStatus();
                    break;

                case 0:
                    cout << "Returning to the main menu." << endl;
                    break;

                default:
                    cout << "Invalid choice. Please try again." << endl;
            }

        } while (choice != 0);

    } while (ch != 0);

    cout << endl;
    cout << "hope you liked our service" << endl;

    return 0;
}
