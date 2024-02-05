/*Budiman Private Hospital Patient Management System
If you have error running this program, please use
g++ generic compiler for jGRASP.
If problem persist, you can use online c++ compiler.*/

#include <iostream>
#include <cctype>
#include <queue>
#include <cstddef>  // Add this header for NULL
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <algorithm> // For swap

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

struct EmergencyCase {
    string name;
    string description;
    int priority;
    EmergencyCase* next;
};

Patient *head = NULL;

// No.1 Add new patient to linked list
void addPatientToList(const Patient& newPatient)
{
   Patient *newNode = new Patient(newPatient);
   newNode->next = head;
   head = newNode;
}

// No.1,3,8 Read patient record from file and add to linked list
void readPatientFile()
{
   ifstream infile;
   infile.open("patients.txt");
   
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

//no 9 - read appointment from appointment.txt
void loadAppointmentsFromFile(queue<Appointment>& appointmentQueue) {
    ifstream infile("appointment.txt");
    if (!infile.is_open()) {
        cout << "Error: Unable to open appointment file.\n";
        return;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string patientID, date, time;
        if (getline(iss, patientID, ',') &&
            getline(iss, date, ',') &&
            getline(iss, time)) {
            Appointment appointment = {patientID, date, time};
            appointmentQueue.push(appointment);
        } else {
            cout << "Error: Invalid appointment format.\n";
        }
    }

    infile.close();
}

// No.1 Write the linked list to the file
void writeListToFile()
   {
   ofstream outfile("patients.txt");
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

// No.1 Add new patient to patient file
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

// No.3,8 Display all patient records from the linked list
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

// No.3 Update patient file after edit
void updatePatientFile()
{
   ofstream outfile("patients.txt");
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
   cout << "-#-Patient Record Updated Successfully-#-" << endl;
}

// No.3 Edit patient record
void editPatientRecord()
{
   cout << "\n---Edit Patient Record---\n";
   string patientID;
   cout << "Enter patient ID to edit: ";
   cin >> patientID;

   // Find the patient in the linked list
   Patient *cur = head;
   bool found = false;
   while (cur != NULL)
   {
      if (cur->id == patientID) 
      {
         found = true;
         break;
      }
      cur = cur->next;
   }

   if (!found)
   {
      cout << "Patient not found." << endl;
      return;
   }

   // Editing menu
   cout << "\n---Edit this patient---\n";
   cout << "Name: " << cur->name << endl
        << "ID: " << cur->id << endl
        << "Gender: " << cur->gender << endl
        << "Date of Birth: " << cur->dob << endl
        << "Address: " << cur->address << endl
        << "Phone: " << cur->phone << endl;
   cout << "What would you like to edit?" << endl;
   cout << "1. Name" << endl;
   cout << "2. ID" << endl;
   cout << "3. Gender" << endl;
   cout << "4. Date of Birth" << endl;
   cout << "5. Address" << endl;
   cout << "6. Phone" << endl;
   cout << "7. Back To Menu" << endl;
   cout << "Enter choice: ";
   int editchoice;
   cin >> editchoice;
   cin.ignore(); // Clear the newline character from the input buffer
   switch (editchoice)
   {
      case 1:
         cout << "Enter new name: ";
         getline(cin, cur->name);
         break;
      case 2:
         cout << "Enter new ID: ";
         cin >> cur->id;
         break;  
      case 3:
         cout << "Enter new gender (Male or Female): ";
         cin >> cur->gender;
         break;
      case 4:
         cout << "Enter new date of birth (dd/mm/yyyy): ";
         cin >> cur->dob;
         break;
      case 5:
         cout << "Enter new address: ";
         getline(cin, cur->address);
         break;
      case 6:
         cout << "Enter new phone: ";
         cin >> cur->phone;
         break;
      case 7:
         break;
      default:
         cout << "Invalid choice. Please try again." << endl;
   }
}

// No.3 Delete patient from patient list
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

   ifstream infile("patients.txt");
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
         remove("patients.txt");
         rename("temp.txt", "patients.txt");
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

// No.3 Reset patient list
void erasePatientRecord()
{
   cout << "\n---Erasing All Patient Records---\n";
    
   // Delete all patient records in the linked list
   Patient *cur = head;
   while (head != NULL)
   {
      cur = head; // Get the first node
      head = head->next; // Move head to the next node
      delete cur; // Delete the cur node
   }
    
   // Ensure the head is null after deletion of all nodes
   head = NULL;
    
   // Clear the patient records file
   ofstream outfile("patients.txt", ios::trunc); // Open file in truncate mode to clear it
   if (outfile.is_open())
   {
      outfile.close(); // Close the file after clearing
      cout << "-#-All Patient Records Erased Successfully-#-\n";
   }
   else
      cout << "!!!Error To Clear Patient Records File!!!\n";
}

// No.4 Bubble sort to sort patient record
void bubbleSortLinkedList(bool byName = true, bool ascending = true)
{
   if (head == NULL || head->next == NULL) return; // List is empty or has one element

   bool swapped;
   Patient *cur;
   Patient *lastPtr = NULL;

   do
   {
      swapped = false;
      cur = head;

      while (cur->next != lastPtr)
      {
         bool condition = byName ?
            (ascending ? cur->name > cur->next->name : cur->name < cur->next->name) :
            (ascending ? cur->id > cur->next->id : cur->id < cur->next->id);

         if (condition)
         {
            swap(cur->name, cur->next->name);
            swap(cur->id, cur->next->id);
            swap(cur->gender, cur->next->gender);
            swap(cur->dob, cur->next->dob);
            swap(cur->address, cur->next->address);
            swap(cur->phone, cur->next->phone);
            swapped = true;
         }
         cur = cur->next;
      }
      lastPtr = cur;
   } while (swapped);
}

// No.4 Sort patient record
void sortPatientRecord()
{
   // User interface for sort patient record
   cout << "\n---Sorting Patient List---\n";
   cout << "1. Sort by patient name in ascending order\n";
   cout << "2. Sort by patient name in descending order\n";
   cout << "3. Sort by ID in ascending order\n";
   cout << "4. Sort by ID in descending order\n";
   cout << "Choose sorting option: ";
   int sortchoice;
   cin >> sortchoice;

   switch (sortchoice)
   {
      case 1:
         cout << "---Sort Patient Record By Name In Ascending Order---\n";
         bubbleSortLinkedList(true, true);
         break;
      case 2:
         cout << "---Sort Patient Record By Name In Descending Order---\n";
         bubbleSortLinkedList(true, false);
         break;
      case 3:
         cout << "---Sort Patient Record By ID In Ascending Order---\n";
         bubbleSortLinkedList(false, true);
         break;
      case 4:
         cout << "---Sort Patient Record By ID In Descending Order---\n";
         bubbleSortLinkedList(false, false);
         break;
      default:
         cout << "Invalid choice. Please select a valid option.\n";
   }

   cout << "-#-Patient records sorted.-#-\n";
   displayPatientRecord();
}

// No.5 Search for patient from patient record
void searchPatient()
{
   cout << "\n---Searching For Patient---\n";
   string searchTerm;
   cout << "Enter patient name or ID: ";
   cin.ignore(); // Ignore newline left in the input buffer
   getline(cin, searchTerm); // Use getline to allow spaces in names

   bool found = false;
   Patient *cur = head;
   cout << "\n-#-Search Results-#-\n";
   while (cur != NULL) 
   {
      if (cur->name.find(searchTerm) != string::npos || cur->id.find(searchTerm) != string::npos)
      {
         // Display matching patient
         cout << "Name: " << cur->name << ", "
              << "ID: " << cur->id << ", "
              << "Gender: " << cur->gender << ", "
              << "Birthdate: " << cur->dob << ", "
              << "Address: " << cur->address << ", "
              << "Phone: " << cur->phone << endl;
         found = true;
      }
      cur = cur->next;
   }

   if (!found)
      cout << "---No Patient Found From Record---\n";
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

void updateAppointment(queue<Appointment>& appointmentQueue) {
    // Check if there are any appointments
    if (appointmentQueue.empty()) {
        cout << "There are no appointments to update." << endl;
        return;
    }

    // Display the current appointment schedule
    displayAppointmentSchedule(appointmentQueue);

    // Ask the user for the appointment number to update
    int appointmentNumber;
    cout << "Enter the number of the appointment to update: ";
    cin >> appointmentNumber;

    // Check if the entered appointment number is valid
    if (appointmentNumber < 1 || appointmentNumber > appointmentQueue.size()) {
        cout << "Invalid appointment number. Please try again." << endl;
        return;
    }

    // Find the appointment to update
    queue<Appointment> tempQueue = appointmentQueue;
    Appointment appointmentToUpdate;
    for (int i = 1; i < appointmentNumber; ++i) {
        tempQueue.pop();
    }
    appointmentToUpdate = tempQueue.front();

    // Display the details of the selected appointment
    cout << "Selected Appointment:" << endl;
    cout << "Patient ID: " << appointmentToUpdate.patientId << endl;
    cout << "Date: " << appointmentToUpdate.date << endl;
    cout << "Time: " << appointmentToUpdate.time << endl;

    // Ask the user for the new date and time
    cout << "Enter the new date (dd/mm/yyyy): ";
    cin >> appointmentToUpdate.date;
    cout << "Enter the new time: ";
    cin >> appointmentToUpdate.time;

    // Update the appointment in the queue
    appointmentQueue.pop();  // Remove the old appointment
    appointmentQueue.push(appointmentToUpdate);  // Add the updated appointment

    // Inform the user that the appointment has been updated
    cout << "Appointment updated successfully." << endl;
}

//6. View and update appointments
void viewAndUpdateAppointments(queue<Appointment>& appointmentQueue) {
    int choice;
    do {
        cout << "\n---View and Update Appointments---" << endl;
        cout << "1. View Appointment Schedule." << endl;
        cout << "2. Update Appointment." << endl;
        cout << "3. Cancel Appointment." << endl;
        cout << "4. Back to Main Menu." << endl;
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayAppointmentSchedule(appointmentQueue); //display appointment schedule
                break;
            case 2:
                updateAppointment(appointmentQueue); //update the appointment schedule
                break;
            case 3:
                //cancelAppointment(appointmentQueue);
                break;
            case 4:
                cout << "---Returning to Main Menu---" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 4);
}

void addEmergencyCase(EmergencyCase*& head) {
    EmergencyCase* newCase = new EmergencyCase;
    cin.ignore();

    cout << "Enter patient name: ";
    getline(cin, newCase->name);

    cout << "Enter description of the emergency: ";
    getline(cin, newCase->description);

    cout << "Enter priority (1-10): ";
    cin >> newCase->priority;

    newCase->next = NULL;

    // Insert into the linked list based on priority
    if (!head || newCase->priority > head->priority) {
        newCase->next = head;
        head = newCase;
    } else {
        EmergencyCase* current = head;
        while (current->next && newCase->priority <= current->next->priority) {
            current = current->next;
        }
        newCase->next = current->next;
        current->next = newCase;
    }

    cout << "Emergency case added successfully.\n";
}

void processEmergencyCases(EmergencyCase*& head) {
    if (!head) {
        cout << "No emergency cases to process.\n";
        return;
    }

    EmergencyCase* current = head;

    cout << "Processing emergency cases:\n";
    cout << "Patient: " << current->name << ", Description: " << current->description << ", Priority: " << current->priority << "\n";

    head = current->next;
    delete current;

    cout << "Emergency case processed successfully.\n";
}

void displayEmergencyCases(EmergencyCase* head) {
    if (!head) {
        cout << "No emergency cases to display.\n";
        return;
    }

    cout << "Emergency Cases:\n";
    while (head) {
        cout << "Patient: " << head->name << ", Description: " << head->description << ", Priority: " << head->priority << "\n";
        head = head->next;
    }
}



void saveToFile(EmergencyCase* head) {
    ofstream outfile("emergency_cases.txt");

    if (outfile.is_open()) {
        while (head) {
            outfile << head->name << "," << head->description << "," << head->priority << "\n";
            head = head->next;
        }
        outfile.close();
        cout << "Emergency cases saved to file.\n";
    } else {
        cout << "Unable to open file for writing.\n";
    }
}

void loadFromFile(EmergencyCase*& head) {
    ifstream infile("emergency_cases.txt");

    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            stringstream ss(line);
            string name, description;
            int priority;

            getline(ss, name, ',');
            getline(ss, description, ',');
            ss >> priority;

            EmergencyCase* newCase = new EmergencyCase{ name, description, priority, NULL };

            // Insert into the linked list based on priority
            if (!head || newCase->priority > head->priority) {
                newCase->next = head;
                head = newCase;
            } else {
                EmergencyCase* current = head;
                while (current->next && newCase->priority <= current->next->priority) {
                    current = current->next;
                }
                newCase->next = current->next;
                current->next = newCase;
            }
        }
        infile.close();
        cout << "Emergency cases loaded from file.\n";
    } else {
        // Create the file if it doesn't exist
        ofstream outfile("emergency_cases.txt");
        outfile.close();

        cout << "No existing file found. Starting with an empty list.\n";
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
void sortPatientRecord();
void searchForPatient();
void viewAndUpdateAppointments(const queue<Appointment>& appointmentQueue); //
void enterAndAccessMedicalRecords();
void displayPatientRecord(); //
void displayAppointmentSchedule(const queue<Appointment>& appointmentQueue); //
void addEmergencyCase();
void processEmergencyCases();

int main() {
    // Load patient records from file into the linked list
    readPatientFile();
    loadAppointmentsFromFile(appointmentQueue);
    //loadMedicalRecordsFromFile();
    EmergencyCase* emergencyQueue = NULL;
    loadFromFile(emergencyQueue);

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
                int c3choice;
                do
                {
                  displayPatientRecord();
                  cout << "---Please Select Your Choice---\n";
                  cout << "1. Edit Patient Record.\n";
                  cout << "2. Delete Patient From Record.\n";
                  cout << "3. Erase Patient Record.\n";
                  cout << "4. Back To Main Menu.\n";
                  cout << "Your Choice: ";
                  cin >> c3choice;
                
                  switch (c3choice)
                  {
                     case 1:
                        editPatientRecord();
                        updatePatientFile();
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
                        continue;
                  }
               } while (c3choice != 4);
               break;
            case 4:
                sortPatientRecord();
                break;
            case 5:
                searchPatient();
                break;
            case 6:
                viewAndUpdateAppointments(appointmentQueue);
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
                addEmergencyCase(emergencyQueue);
                break;
            case 11:
                processEmergencyCases(emergencyQueue);
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
