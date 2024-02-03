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
struct Patient
{
   string name;
   string id;
   string gender;
   string dob;
   string address;
   string phone;
   Patient *next;
};

struct Appointment
{
   string patientId;
   string date;
   string time;
};

struct MedicalRecord
{
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
   infile.open("patient_file.txt");
   
   if (infile.is_open())
   {
      string line;
      while (getline(infile, line))
      {
         stringstream ss(line);
         string name, id, gender, dob, address, phone;

         // Assuming each field is separated by a comma
         getline(ss, name, ',');
         getline(ss, id, ',');
         getline(ss, gender, ',');
         getline(ss, dob, ',');
         getline(ss, address, ',');
         getline(ss, phone);

         Patient newPatient = {name, id, gender, dob, address, phone, NULL};
         addPatientToList(newPatient);
      }
      infile.close();
   }
   else
      cout << "!!!Error To Read Patient Record!!!\n";
}

// Function to write the linked list to the file
void writeListToFile()
   {
   ofstream outfile("patient_file.txt");
   if (outfile.is_open()) 
   {
      Patient *cur = head;
      while (cur != NULL)
      {
         outfile << cur->name << ","
                 << cur->id << "," 
                 << cur->gender << ","
                 << cur->dob << ","
                 << cur->address << ","
                 << cur->phone << endl;
         cur = cur->next;
      }
      outfile.close();
   }
   else
      cout << "!!!Error To Write Patient Record!!!\n";
}

// Function Add new patient to patient file
void addPatientToFile()
   {
   cout << "\n---Add New Patient To The List---\n";
   cin.ignore();
   Patient newPatient;
   cout << "Enter patient name: ";
   getline(cin, newPatient.name);
   cout << "Enter patient ID: ";
   cin >> newPatient.id;
   cout << "Enter patient gender (Male or Female): ";
   cin >> newPatient.gender;
   cout << "Enter patient date of birth (dd/mm/yyyy): ";
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
void displayPatientRecord()
{
   cout << "\n---Patient Record---\n";
   Patient *cur = head;
   if (cur == NULL)
      cout << "The list is empty. Please add patient to the list.\n";
   else
   {
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
}

// Edit patient record
void editPatientRecord()
{
   cout << "In progress.\n";
}

// Delete patient from patient list
void deletePatientFromRecord(queue<Appointment>& appointmentQueue)
{
   string patientID;
   cout << "Enter patient ID to delete: ";
   cin >> patientID;
   
   // Remove patient from linked list
   Patient *cur = head, *prev = NULL;
   while (cur != NULL && cur->id != patientID)
   {
      prev = cur;
      cur = cur->next;
   }
   
   if (cur == NULL)
   {
      cout << "!!!Patient Not Found In List!!!\n";
      return;
   }
   
   // If the patient is found, unlink the node from the linked list
   if (prev == NULL)
       head = cur->next;
   else
      prev->next = cur->next;

   delete cur;  // Free memory

   ifstream infile("patient_file.txt");
   ofstream tempFile("temp.txt");
   string line;
   bool found = false;

   if (infile.is_open() && tempFile.is_open())
   {
      while (getline(infile, line))
      {
         // Assuming patient ID is the second field in the line
         stringstream ss(line);
         string temp;
         getline(ss, temp, ','); // Skip name
         getline(ss, temp, ',');
         
         if (temp != patientID) 
            tempFile << line << endl;
         else
            found = true;
      }
      infile.close();
      tempFile.close();

      // Replace old patient file with new file if patient is found
      if (found)
      {
         remove("patient_file.txt");
         rename("temp.txt", "patient_file.txt");
         cout << "-#-Patient Record Deleted Successfully-#-\n";
      }
      else
      {
         cout << "!!!Patient Not Found!!!\n";
         remove("temp.txt");
      }
   }
   else
      cout << "!!!Error Opening File!!!\n";
}

// Reset patient list
void erasePatientRecord()
{
   cout << "In progress.\n";
}

// Function prototype for writing appointment to file
void writeAppointmentToFile(const Appointment& newAppointment);

//NO 2 - Schedule a patient appointment
void schedulePatientAppointment(queue<Appointment>& appointmentQueue) {
    cout << "---Schedule a Patient Appointment---\n";
    
    // Collect appointment details from the user
    Appointment newAppointment;
    cout << "Enter patient ID: ";
    cin >> newAppointment.patientId;
    cout << "Enter appointment date (dd/mm/yyyy): ";
    cin >> newAppointment.date;
    cout << "Enter appointment time: ";
    cin >> newAppointment.time;

    // Enqueue the appointment into the appointmentQueue
    appointmentQueue.push(newAppointment);

    // Write appointment to file
    writeAppointmentToFile(newAppointment);
    
    cout << "-#-Appointment Scheduled Successfully-#-\n";
}

// Function to write the appointment to the file
void writeAppointmentToFile(const Appointment& newAppointment) {
    ofstream outfile("appointment.txt", ios::app); // Open file in append mode
    if (outfile.is_open()) {
        outfile << newAppointment.patientId << ","
                << newAppointment.date << "," 
                << newAppointment.time << endl;
        outfile.close();
    } else {
        cout << "!!!Error To Write Appointment!!!\n";
    }
}

//NO 9 - Display appointment schedule.
void displayAppointmentSchedule(const queue<Appointment>& appointmentQueue) {
    cout << "\n---Appointment Schedule---\n";

    // Check if the appointment queue is empty
    if (appointmentQueue.empty()) {
        cout << "There are no scheduled appointments.\n";
        return;
    }

    // Print a header for the schedule
    cout << "No. | Patient ID | Date | Time\n";
    cout << "----|------------|------|-------\n";

    int count = 1;  // Keep track of the appointment number

    // Iterate through the appointment queue using a temporary queue
    queue<Appointment> tempQueue = appointmentQueue;
    while (!tempQueue.empty()) {
        Appointment appointment = tempQueue.front();
        tempQueue.pop();

        cout << count++ << " | " << appointment.patientId << " | "
             << appointment.date << " | " << appointment.time << endl;
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
void displayPatientRecord();
void displayAppointmentSchedule(const queue<Appointment>& appointmentQueue);
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
                schedulePatientAppointment(appointmentQueue);
                break;
            case 3:
                displayPatientRecord();
                cout << "---Please Select Your Choice---\n";
                cout << "1. Edit Patient Record.\n";
                cout << "2. Delete Patient From Record.\n";
                cout << "3. Erase From Record.\n";
                cout << "4. Back To Main Menu.\n";
                cout << "Your Choice: ";
                int c3choice;
                cin >> c3choice;
                
                switch (c3choice)
                {
                  case 1:
                     editPatientRecord();
                     break;
                  case 2:
                     deletePatientFromRecord(appointmentQueue);
                     break;
                  case 3:
                     erasePatientRecord();
                     break;
                  case 4:
                     break;
                  default:
                     cout << "Invalid choice. Please try again.\n";
               }
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
                displayPatientRecord();
                break;
            case 9:
                displayAppointmentSchedule(appointmentQueue);
                break;
            case 10:
                //addEmergencyCase();
                break;
            case 11:
                //processEmergencyCases();
                break;
            case 12:
                cout << "---Exiting the system. Goodbye!---" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

    } while (choice != 12);

    //saveAppointmentsToFile();
    //saveMedicalRecordsToFile();

    return 0;
}

// Function definitions...
void displayMainMenu() {
    cout << "\n---Main Menu---" << endl;
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


