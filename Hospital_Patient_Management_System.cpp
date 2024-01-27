#include <iostream>
#include <cctype>
#include <queue>
#include <stack>
#include <cstddef>  // Add this header for nullptr
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <queue>

using namespace std;

// Data structures
struct Patient {
    string name;
    string id;
    string gender;
    string dob;
    string address;
    string phone;
};

struct Appointment {
    string patientId;
    string date;
    string time;
};

struct MedicalRecord {
    string patientId;
    string record;
};

// Linked list for patient records
list<Patient> patientList;

// Linked list for appointments
list<Appointment> appointmentList;

// Linked list for medical records
list<MedicalRecord> medicalRecordList;

// Queue for appointment schedule
queue<Appointment> appointmentQueue;

// Priority queue for emergency cases
priority_queue<Appointment, vector<Appointment>, greater<Appointment>> emergencyQueue;

// Function prototypes
void loadPatientsFromFile();
void loadAppointmentsFromFile();
void loadMedicalRecordsFromFile();

void savePatientsToFile();
void saveAppointmentsToFile();
void saveMedicalRecordsToFile();

void displayMainMenu();
void registerNewPatient();
void schedulePatientAppointment();
void viewAndUpdatePatientInformation();
void sortPatientRecords();
void searchForPatient();
void viewAndUpdateAppointments();
void enterAndAccessMedicalRecords();
void displayPatientList();
void displayAppointmentSchedule();
void addEmergencyCase();
void processEmergencyCases();

int main() {
    //loadPatientsFromFile();
    //loadAppointmentsFromFile();
    //loadMedicalRecordsFromFile();

    int choice;

    do {
        displayMainMenu();
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                //registerNewPatient();
                break;
            case 2:
                //schedulePatientAppointment();
                break;
            case 3:
                //viewAndUpdatePatientInformation();
                break;
            case 4:
                //sortPatientRecords();
                break;
            case 5:
                //searchForPatient();
                break;
            case 6:
                //viewAndUpdateAppointments();
                break;
            case 7:
                //enterAndAccessMedicalRecords();
                break;
            case 8:
                //displayPatientList();
                break;
            case 9:
                //displayAppointmentSchedule();
                break;
            case 10:
                //addEmergencyCase();
                break;
            case 11:
                //processEmergencyCases();
                break;
            case 12:
                cout << "Exiting the system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

    } while (choice != 12);

    //savePatientsToFile();
    //saveAppointmentsToFile();
    //saveMedicalRecordsToFile();

    return 0;
}

// Function definitions...
void displayMainMenu() {
    cout << "Main Menu" << endl;
    cout << "Welcome to Budiman Private Hospital Patient Management System." << endl;
    cout << "Please select your choice:" << endl;
    cout << "1. Register a new patient." << endl;
    cout << "2. Schedule a patient appointment." << endl;
    cout << "3. View and update patient information." << endl;
    cout << "4. Sort patient records." << endl;
    cout << "5. Search for a patient." << endl;
    cout << "6. View and update appointments." << endl;
    cout << "7. Enter and access medical records." << endl;
    cout << "8. Display patient list." << endl;
    cout << "9. Display appointment schedule." << endl;
    cout << "10. Add an emergency case." << endl;
    cout << "11. Process emergency cases." << endl;
    cout << "12. Exit." << endl;
}


