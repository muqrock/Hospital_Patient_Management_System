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
    Patient *next;
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

Patient *head = NULL;

// Add new patient to linked list
void addPatientToList(const Patient& newPatient)
{
   Patient *newNode = new Patient(newPatient);
   newNode->next = head;
   head = newNode;
}

// Read patient record from file and add to linked list
void readPatientFile()
{
   ifstream infile;
   infile.open("patient_try.txt");
   
   if (infile.is_open())
   {
      string name, id, gender, dob, address, phone;
      while (infile >> name >> id >> gender >> dob >> address >> phone)
      {
         Patient newPatient = {name, id, gender, dob, address, phone, NULL};
         addPatientToList(newPatient);
      }
      infile.close();
   }
   else
      cout << "!!!Error To Read Patient Record!!!\n";
}

// Function to write the linked list to the file
void writeListToFile() {
   ofstream outfile("patient_try.txt");
   if (outfile.is_open()) 
   {
      Patient *cur = head;
      while (cur != NULL)
      {
         outfile << "Name: " << cur->name << ", "
                 << "ID: " << cur->id << ", " 
                 << "Gender: " << cur->gender << ", "
                 << "Birthdate: " << cur->dob << ", "
                 << "Address: " << cur->address << ", "
                 << "Phone: " << cur-> phone << endl;
         cur = cur->next;
      }
      outfile.close();
   }
   else
      cout << "!!!Error To Write Patient Record!!!\n";
}

// Function Add new patient to patient file
void addPatientToFile() {
    cout << "\n---Add New Patient To The List---\n";
    cin.ignore();
    Patient newPatient;
    cout << "Enter patient name: ";
    getline(cin, newPatient.name);
    cout << "Enter patient ID: ";
    cin >> newPatient.id;
    cout << "Enter patient gender: ";
    cin >> newPatient.gender;
    cout << "Enter patient date of birth: ";
    cin >> newPatient.dob;
    cout << "Enter patient address: ";
    cin.ignore();
    getline(cin, newPatient.address);
    cout << "Enter patient phone number: ";
    cin >> newPatient.phone;

    addPatientToList(newPatient);
    writeListToFile();
    cout << "-#-Patient Record Added Successfully-#-\n";
}

// Display all patient records from the linked list
void displayPatientRecords()
{
   Patient *cur = head;
   while (cur != NULL)
   {
      cout << "Name: " << cur->name << ", "
           << "ID: " << cur->id << ", " 
           << "Gender: " << cur->gender << ", "
           << "Birthdate: " << cur->dob << ", "
           << "Address: " << cur->address << ", "
           << "Phone: " << cur-> phone << endl;
           cur = cur->next;
    }
}

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
void displayPatientRecords();
void displayAppointmentSchedule();
void addEmergencyCase();
void processEmergencyCases();

int main() {
    // Load patient records from file into the linked list
    readPatientFile();
    //loadAppointmentsFromFile();
    //loadMedicalRecordsFromFile();

    int choice;

    do {
        displayMainMenu();
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addPatientToFile();
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
                displayPatientRecords();
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


