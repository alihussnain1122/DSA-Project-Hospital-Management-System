#include<iostream>
#include<fstream>
#include<sstream>
#include<conio.h>
#include<unordered_map>
#include<list>
#include<string>
#include <windows.h>
#include "linked_list.h"
#include "queue.h"
#include "stack.h"
using namespace std;
    const string BOLD="\033[1m";
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string BLUE = "\033[34m";
    const string RESET = "\033[0m";
    // Merge Sort for Sorting Names
void merge(string arr[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    string leftArr[n1], rightArr[n2];

    for (int i = 0; i < n1; ++i) leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) arr[k++] = leftArr[i++];
        else arr[k++] = rightArr[j++];
    }

    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];
}

void mergeSort(string arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
    //BST class
    class Node {
    public:
    string name;
    string id;
    string cnic;
    Node* left;
    Node* right;
    Node(string name, string id, string cnic) : name(name),
     id(id), cnic(cnic), left(nullptr), right(nullptr) {}
};
struct doc {
    string name;
    string profession;

    doc() : name(""), profession("") {}
    doc(const string& n, const string& p) : name(n), profession(p) {}
};

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    void insert(const string& name,string id,string cnic) {
        root = insertNode(root, name,id,cnic);
    }

    bool search(const string& name) {
        return searchNode(root, name);
    }

    void display() {
        inorderTraversal(root);
    }

private:
   Node* insertNode(Node* node, const string& name, const string& id, const string& cnic) {
    if (node == nullptr) {
        return new Node(name, id, cnic);
    }

    if (name < node->name) {
        node->left = insertNode(node->left, name, id, cnic);
    } else if (name > node->name) {
        node->right = insertNode(node->right, name, id, cnic);
    }

    return node;
}

bool searchNode(Node* node, const string& name) {
    if (node == nullptr) {
        return false;
    }

    if (name == node->name) {
        return true;
    } else if (name < node->name) {
        return searchNode(node->left, name);
    } else {
        return searchNode(node->right, name);
    }
}


    

    void inorderTraversal(Node* node) {
    if (node != nullptr) {
        inorderTraversal(node->left);
        cout << "Name: " << node->name << "\n ID: " << node->id << "\n CNIC: " << node->cnic << endl;
        inorderTraversal(node->right);
    }
}

};
// Patient Class
class Patient {
public:
    string name;
    int id;
    string cnic;

    Patient() {}

    void inputDetails() {
        cout << "Enter Patient's Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Patient's ID: ";
        cin >> id;
        cout << "Enter Patient's CNIC: ";
        cin >> cnic;
    }

    void saveToFile() {
        ofstream patientFile("patients_data.txt", ios::app);
        if (patientFile.is_open()) {
            patientFile << name << "\n" << id << "\n" << cnic << "\n";
            patientFile.close();
            cout << "Patient details saved to the file successfully!" << endl;
        } else {
            cout << "Unable to open the file to save patient details!" << endl;
        }
    }

    void viewReport() {
        string cnic;
        cout<<"Enter the CNIC to view the Patient's Report: ";
        cin>>cnic;
        ifstream reportFile("patient_reports.txt");
        if (reportFile.is_open()) {
            string line;
            bool found = false;

            while (getline(reportFile, line)) {
                if (line == cnic) {
                    cout << "\nPatient Report for CNIC: " << cnic << "\n";
                    cout << "CNIC       : " << line << endl;
                    getline(reportFile, line); cout << "ID         : " << line << endl;
                    getline(reportFile, line); cout << "Name       : " << line << endl;
                    getline(reportFile, line); cout << "Blood Group: " << line << endl;
                    getline(reportFile, line); cout << "Sex        : " << line << endl;
                    getline(reportFile, line); cout << "Symptoms   : " << line << endl;
                    getline(reportFile, line); cout << "Disease    : " << line << endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "No report found for patient with CNIC: " << cnic << endl;
            }
            reportFile.close();
        } else {
            cout << "Unable to open the report file!" << endl;
        }
    }

    void viewBill() {
    string inputCnic;
    cout << "Enter CNIC: ";
    cin >> inputCnic;

    ifstream billFile("patient_bills.txt");
    bool found = false;
    if (billFile.is_open()) {
        string line;
        while (getline(billFile, line)) {
            if (line.find(inputCnic) != string::npos) {
                found = true;
                cout << "\nBill details for Patient with CNIC " << inputCnic << ":\n";
                cout << line << endl;  // Bill ID line
                for (int i = 0; i < 4; i++) {
                    getline(billFile, line);
                    cout << line << endl;  // Print bill details
                }
                break;
            }
        }
        if (!found) {
            cout << "No bill found for patient with CNIC: " << inputCnic << endl;
        }
        billFile.close();
    } else {
        cout << "Unable to open the bill file!" << endl;
    }
}


    void updateDetails() {
        cout << "Updating Details for " << name << endl;
        cout << "Enter new details for " << name << " (Name, ID, CNIC): ";
        cin.ignore();
        getline(cin, name);
        cin >> id >> cnic;
        saveToFile();
        cout << "Patient details updated and saved successfully." << endl;
    }

    void requestAppointment() {
        ofstream appointmentFile("appointments.txt", ios::app);
        if (appointmentFile.is_open()) {
            appointmentFile << name << "\n" << cnic << "\n";  // Save name and CNIC for the appointment
            appointmentFile.close();
            cout << "Appointment requested "<< endl;
        } else {
            cout << "Unable to open the appointment file!" << endl;
        }
    }
};

// Receptionist Class
class Receptionist {
public:
    Queue<string> appointmentQueue;
    string patientsFile = "patients.txt";  // File to store patient information

    // Add a patient to the appointment queue and save to file, with CNIC uniqueness check
    void addPatient(const string& name, const string& id, const string& cnic) {
        // Check if CNIC already exists in the file
        if (isCNICExist(cnic)) {
            cout << "Patient with CNIC " << cnic << " already exists!" << endl;
            return;
        }

        // Add patient to appointment queue
        appointmentQueue.enqueue(name);
        cout << "Patient " << name << " added to the appointment queue." << endl;

        // Save patient details to the file
        ofstream patientFile(patientsFile, ios::app);
        if (patientFile.is_open()) {
            patientFile << name << "\n" << id << "\n" << cnic << "\n";  // Store name, id, and cnic
            patientFile.close();
            cout << "Patient " << name << " with CNIC " << cnic << " added to the system." << endl;
        } else {
            cout << "Unable to open the patient file!" << endl;
        }
    }

    // Function to check if a CNIC already exists in the file
    bool isCNICExist(const string& cnic) {
        ifstream patientFile(patientsFile);
        if (patientFile.is_open()) {
            string line;
            while (getline(patientFile, line)) {
                size_t pos = line.find(cnic);
                if (pos != string::npos) {
                    patientFile.close();
                    return true;  // CNIC found in the file
                }
            }
            patientFile.close();
        } else {
            cout << "Unable to open the patient file!" << endl;
        }
        return false;
    }

    // Schedule appointment for a patient and save to file
    void scheduleAppointment() {
    string cnic,name;
    cout << "Enter the CNIC of the patient: ";
    cin >> cnic;
    cout<<"Enter the Patient's name: ";
    cin>>name;
    // Check if CNIC exists in the patient file
    if (!isCNICExist(cnic)) {
        cout << "Patient with CNIC " << cnic << " does not exist in the system!" << endl;
        return;  // Exit the function if CNIC is not found
    }

    // Check if the appointment has already been scheduled for this CNIC
    if (isAppointmentScheduled(cnic)) {
        cout << "Appointment for patient with CNIC " << cnic << " is already scheduled." << endl;
        return;  // Exit the function if appointment is already scheduled
    }

    // Proceed to schedule the appointment if CNIC is found and no duplicate appointment
    cout << "Scheduling appointment for patient with CNIC " << cnic << "..." << endl;

    // Save the scheduled appointment to a file
    ofstream appointmentFile("appointments.txt", ios::app);
    if (appointmentFile.is_open()) {
        appointmentFile << cnic << "\n";  // Store the appointment details
        appointmentFile.close();
        cout << "Appointment successfully scheduled for " << name<<": "<<cnic << "." << endl;
    } else {
        cout << "Unable to open the appointment file! Please try again later." << endl;
    }
}

// Function to check if the appointment is already scheduled for a CNIC
bool isAppointmentScheduled(const string& cnic) {
    ifstream appointmentFile("appointments.txt");
    if (appointmentFile.is_open()) {
        string line;
        while (getline(appointmentFile, line)) {
            if (line == cnic) {
                appointmentFile.close();
                return true;  // Appointment already scheduled for this CNIC
            }
        }
        appointmentFile.close();
    } else {
        cout << "Unable to open the appointment file!" << endl;
    }
    return false;  // No appointment found for this CNIC
}


    // View all appointments from the file
    void viewAppointments() {
    ifstream appointmentFile("appointments.txt");
    
    // Check if the file is open
    if (appointmentFile.is_open()) {
        string line;
        cout << "Appointments in the queue:" << endl;
        
        // If file is not empty, read each line and display it
        if (appointmentFile.peek() == ifstream::traits_type::eof()) {
            cout << "No appointments found." << endl;  // Handle empty file
        } else {
            while (getline(appointmentFile, line)) {
                if (!line.empty()) {  // Check for non-empty lines
                    cout << line << endl;
                }
            }
        }
        
        appointmentFile.close();
    } else {
        cout << "Unable to open the appointment file!" << endl;
    }
}


    // Undo last action (e.g., remove last patient added)
    void undo() {
        cout << "Undoing the last action." << endl;
        // Remove the last entry from the patient file
        ifstream inFile(patientsFile);
        ofstream outFile("temp.txt");
        string line;
        string lastPatient;
        while (getline(inFile, line)) {
            lastPatient = line;  // Save the last patient for undo
        }
        // Now, copy all but the last patient to the temp file
        inFile.clear();
        inFile.seekg(0, ios::beg);

        while (getline(inFile, line)) {
            if (line != lastPatient) {
                outFile << line << "\n";  // Copy the rest of the file
            }
        }

        inFile.close();
        outFile.close();

        // Replace the original file with the updated file
        remove(patientsFile.c_str());
        rename("temp.txt", patientsFile.c_str());

        cout << "Last action undone. Patient " << lastPatient << " removed from the queue." << endl;
    }

    // Get the appointment queue (if needed)
    Queue<string>& getAppointmentQueue() {
        return appointmentQueue;
    }
};

// Graph class integrated into the Doctor class
class Doctor {
private:
    unordered_map<string, list<string>> patientAppointments; // Graph structure

public:
    // Add a patient to the doctor's appointment list (connect patient to doctor)
    void addPatientAppointment(const string& doctorName, const string& patientName) {
        patientAppointments[doctorName].push_back(patientName);
    }

    // Remove a patient from the doctor's appointment list (disconnect patient from doctor)
    void removePatientAppointment(const string& doctorName, const string& patientName) {
        patientAppointments[doctorName].remove(patientName);
    }

    // Display all appointments of the doctor (graph visualization)
    void displayAppointments(const string& doctorName) {
        cout << "Appointments for Dr. " << doctorName << ":" << endl;
        for (const auto& patient : patientAppointments[doctorName]) {
            cout << "- " << patient << endl;
        }
    }

    // Generate a report for a patient
    void generateAndSaveReport() {
    string cnic;
    bool patientFound = false;

    // Take CNIC input from the user
    cout << "Enter the Patient's CNIC: ";
    cin >> cnic;

    // Open the patient file and check if the CNIC exists
    ifstream patientFile("patients.txt");
    string line;
    while (getline(patientFile, line)) {
        if (line == cnic) {
            patientFound = true;
            break;
        }
    }
    patientFile.close();

    // If CNIC found, proceed with report generation
    if (patientFound) {
        Patient patient;
        string sex, bp_group, disease, symptoms;
        
        // Collect the patient's details
        patient.cnic = cnic;
        cout << "Enter the Patient's ID: ";
        cin >> patient.id;
        cout << "Enter the Patient's Name: ";
        cin.ignore();  // Clear input buffer
        getline(cin, patient.name);
        cout << "Enter the Patient's Sex: ";
        cin >> sex;
        cout << "Enter the Blood group of Patient: ";
        cin >> bp_group;
        cout << "Enter the symptoms of disease: ";
        cin.ignore();
        getline(cin, symptoms);
        cout << "Enter the Patient's disease: ";
        getline(cin, disease);

        // Create the report string
        string report = patient.cnic + "\n" + to_string(patient.id) + "\n" + patient.name + "\n" + bp_group + "\n" + sex + "\n" + symptoms + "\n" + disease + "\n";
        
        // Save the report to file
        ofstream reportFile("patient_reports.txt", ios::app);
        if (reportFile.is_open()) {
            reportFile << report;
            cout << "Doctor is generating a report and saving it for: " << patient.name << endl;
        } else {
            cout << "Unable to open report file!" << endl;
        }
        reportFile.close();
    } else {
        cout << "No patient found with the CNIC: " << cnic << endl;
    }
}
void viewTimeTable() {  //time table
        cout <<BOLD<<RED<< "Doctor's Weekly Time Table:" << RESET<<endl;
        cout <<BOLD<<BLUE<< "--------------------------------" << endl;
        cout << "Monday    : 9:00 AM - 12:00 PM" << endl;
        cout << "Tuesday   : 10:00 AM - 2:00 PM" << endl;
        cout << "Wednesday : 9:00 AM - 12:00 PM" << endl;
        cout << "Thursday  : 10:00 AM - 2:00 PM" << endl;
        cout << "Friday    : 9:00 AM - 12:00 PM" << endl;
        cout << "Saturday  : 10:00 AM - 1:00 PM" << endl;
        cout <<BOLD<<RED<< "Sunday    : Closed" << endl;
        cout <<BOLD<<BLUE<< "--------------------------------" << RESET<<endl;
    }
//bill generating function
void generateBill(Patient& patient) {
    string inputCnic;
    cout << "Enter Patient CNIC: ";
    cin >> inputCnic;

    // Check if the CNIC exists in the patient data file
    ifstream patientFile("patients.txt");
    bool found = false;
    string line;
    while (getline(patientFile, line)) {
        if (line == inputCnic) {
            found = true;
            break;
        }
    }
    patientFile.close();

    if (!found) {
        cout << "No patient found with CNIC: " << inputCnic << endl;
        return;  // Exit if CNIC does not match
    }

    // If CNIC exists, proceed to bill generation
    // Generate a random 4-digit bill ID
    int billID = rand() % 9000 + 1000;

    // Fixed consultation fee
    double consultationFee = 500.0;

    // User input for treatment fee
    double treatmentFee;
    cout << "Enter the treatment fee for the patient: ";
    cin >> treatmentFee;

    // Calculate total bill
    double totalBill = consultationFee + treatmentFee;

    // Save the bill to a file
    ofstream billFile("patient_bills.txt", ios::app);
    if (billFile.is_open()) {
        billFile << "Bill ID: " << billID << "\n"
                 << "CNIC: " << inputCnic << "\n"
                 << "Total Bill: " << totalBill << "\n"
                 << "Consultation Fee: " << consultationFee << "\n"
                 << "Treatment Fee: " << treatmentFee << "\n\n";
        cout << "Bill generated for patient with CNIC: " << inputCnic << " and Bill ID: " << billID << endl;
    } else {
        cout << "Unable to generate the bill!" << endl;
    }
    billFile.close();
}


   void viewPatientQueue(Queue<string>& patientQueue) {
    // Load patient data from the file into the queue
    ifstream patientFile("patients.txt");
    string line;
    
    if (!patientFile.is_open()) {
        cout << "Unable to open the patient data file!" << endl;
        return;
    }

    // Read patient names from the file and add them to the queue
    while (getline(patientFile, line)) {
        patientQueue.enqueue(line);  // Assuming each line contains the patient's name or relevant data
    }

    patientFile.close();

    // Now, display the doctor’s patient queue
    cout << "Doctor's Patient Queue:" << endl;
    while (!patientQueue.isEmpty()) {
        cout << patientQueue.dequeue() << endl;  // Display and remove each patient from the queue
    }
}


    // Function to check if a patient is connected to a doctor (appointment exists)
    bool isPatientAssigned(const string& doctorName, const string& patientName) {
        for (const string& patient : patientAppointments[doctorName]) {
            if (patient == patientName) {
                return true;
            }
        }
        return false;
    }

    // Function to display the doctor's connections (appointments)
    void displayDoctorConnections() {
        for (const auto& entry : patientAppointments) {
            cout << "Doctor " << entry.first << " has appointments with: ";
            for (const auto& patient : entry.second) {
                cout << patient << " ";
            }
            cout << endl;
        }
    }
};
// Manager Class
class Manager {
private:
    doc* d;  // Array of Doctor structs
    string* doctors;
    string* receptionists;
    BST patientRecords; // Use BST for patient records
    int doctorCount, receptionistCount;
    int doctorCapacity, receptionistCapacity;

    void expandDoctors() {
        doctorCapacity *= 2;
        string* newDoctors = new string[doctorCapacity];
        for (int i = 0; i < doctorCount; ++i)
            newDoctors[i] = doctors[i];
        delete[] doctors;
        doctors = newDoctors;
    }

    void expandReceptionists() {
        receptionistCapacity *= 2;
        string* newReceptionists = new string[receptionistCapacity];
        for (int i = 0; i < receptionistCount; ++i)
            newReceptionists[i] = receptionists[i];
        delete[] receptionists;
        receptionists = newReceptionists;
    }

    void saveToFile(const string& fileName, const string& data) {
        ofstream outFile(fileName, ios::app);
        if (outFile) {
            outFile << data << endl;
            outFile.close();
        } else {
            cout << "Error opening file: " << fileName << endl;
        }
    }

public:
    Manager() : doctorCount(0), receptionistCount(0), doctorCapacity(2), receptionistCapacity(2) {
        doctors = new string[doctorCapacity];
        receptionists = new string[receptionistCapacity];
    }

    ~Manager() {
        delete[] doctors;
        delete[] receptionists;
    }

   void addDoctor() {
    if (doctorCount >= doctorCapacity)
        expandDoctors();

    cout << "Enter Doctor's Name: ";
    cin.ignore();  // Ignore any leftover newline characters
    getline(cin, doctors[doctorCount]);  // Store doctor's name

    cout << "Enter Doctor's Profession: ";
    string profession;
    getline(cin, profession);  // Store doctor's profession

    // Save both name and profession to the file
    string doctorInfo = doctors[doctorCount] + ", " + profession;
    saveToFile("doctors.txt", doctorInfo);

    doctorCount++;
    cout << "Doctor added and saved to file successfully.\n";
}


    void addReceptionist() {
        if (receptionistCount >= receptionistCapacity)
            expandReceptionists();
        cout << "Enter Receptionist's Name: ";
        cin.ignore();
        getline(cin, receptionists[receptionistCount++]);
        saveToFile("receptionists.txt", receptionists[receptionistCount - 1]);
        cout << "Receptionist added and saved to file successfully.\n";
    }

    // void addPatient() {
    //     cout << "Enter Patient's Name: ";
    //     cin.ignore();
    //     string name;
    //     getline(cin, name);
    //     patientRecords.insert(name); // Using BST to add patient
    //     saveToFile("patients.txt", name);
    //     cout << "Patient added and saved to file successfully.\n";
    // }

    void searchPatient() {
        cout << "Enter Patient's CNIC to Search: ";
        cin.ignore();
        string cnic;
        getline(cin, cnic);
        patientRecords.search(cnic);
    }

void displayDoctors() {
    ifstream inFile("doctors.txt");
    string name, profession;
    bool doctorFound = false;
    while (getline(inFile, name, ',') && std::getline(inFile, profession)) {
        cout <<BOLD<<BLUE<< "Name: " <<RESET<< name <<BOLD<<BLUE<< "  Profession: " <<RESET<< profession << std::endl;
        doctorFound=true;
    }

    if (doctorFound==false) {
        cout << "No doctors available.\n";
    }
}



    void displayReceptionists() {
        if (receptionistCount == 0) cout << "No receptionists available.\n";
        else {
            cout << "Receptionists:\n";
            for (int i = 0; i < receptionistCount; ++i) cout << receptionists[i] << endl;
        }
    }

 void displayPatients() {
    ifstream inFile("patients.txt");
    if (!inFile) {
        cout << "Error opening patients.txt file.\n";
        return;
    }

    string name, id, cnic;
    while (getline(inFile, name) && getline(inFile, id) && getline(inFile, cnic)) {
        patientRecords.insert(name, id, cnic);  // Insert each patient's data into BST
    }
    inFile.close();

    // Now display the patient records stored in BST
    patientRecords.display();
}



    void sortDoctors() {
        if (doctorCount > 0) {
            mergeSort(doctors, 0, doctorCount - 1);
            cout << "Doctors sorted alphabetically.\n";
        } else cout << "No doctors to sort.\n";
    }

    void sortReceptionists() {
        if (receptionistCount > 0) {
            mergeSort(receptionists, 0, receptionistCount - 1);
            cout << "Receptionists sorted alphabetically.\n";
        } else cout << "No receptionists to sort.\n";
    }

    void assignShifts() {
        cout << "Assigning shifts to staff...\n";
        cout << "Doctors: " << doctorCount << " shifts assigned.\n";
        cout << "Receptionists: " << receptionistCount << " shifts assigned.\n";
    }

    void viewHospitalStatistics() {
        cout << "\n--- Hospital Statistics ---\n";
        cout << "Total Doctors: " << doctorCount << endl;
        cout << "Total Receptionists: " << receptionistCount << endl;
    }
};
void print_name() {
    cout<<BOLD<<BLUE;
    cout << " U   U  EEEEE  TTTTT    M   M  EEEEE  DDDD    I   CCCC   AAAAA  RRRR   EEEEE\n";
    cout << " U   U  E        T      MM MM  E      D   D   I   C      A   A  R   R  E    \n";
    cout << " U   U  EEEE     T      M M M  EEEE   D   D   I   C      AAAAA  RRRR   EEEE \n";
    cout << " U   U  E        T      M   M  E      D   D   I   C      A   A  R  R   E    \n";
    cout << " UUUUU  EEEEE    T      M   M  EEEEE  DDDD    I   CCCC   A   A  R   R  EEEEE\n"<<RESET;
}

int main() {
    print_name();
    cout << "Press any key to continue..." << std::endl;
    cin.get();
    Sleep(1000);
    system("cls");
    cout <<GREEN<<BOLD<< "\n\tWelcome to the UET MediCare!" << endl;
    cout <<BOLD<<RED<< "\t==============================\n";
    cout <<GREEN<<BOLD<< "\tPowered by: Doctor's Hospital\n"<<RESET;
    Receptionist receptionist;
    Doctor doctor;

    Patient patient;
    Manager manager;
    string pname, pid, pcnic;
    int roleChoice;
    string doctorName, patientName;

    while (true) {
        cout << "\nSelect Your Role:\n";
        cout << "1. Manager\n2. Doctor\n3. Patient\n4. Receptionist\n5. Exit\n";
        cout << "Enter your choice (1-5): ";
        cin >> roleChoice;
        system("cls");
        Sleep(1000);
        switch (roleChoice) {
        case 1: { // Manager functionalities
            cout <<BOLD<<BLUE<< "\n===== Manager Dashboard =====\n"<<RESET;
            cout << "1. Add Doctor\n2. Add Receptionist\n3. View Hospital Statistics\n";
            cout << "4. Display Doctors\n5. Display Receptionists\n";
            cout << "6. Display Patients\n7. Sort Doctors\n8. Sort Receptionists\n";
            cout << "9. Assign Shifts\n10.Go to Main Menu\n11. Exit\n";
            int managerChoice;
            cin >> managerChoice;

            switch (managerChoice) {
            case 1:
                manager.addDoctor();
                break;
            case 2:
                manager.addReceptionist();
                break;
            case 3:
                manager.viewHospitalStatistics();
                break;
            case 4:
                manager.displayDoctors();
                break;
            case 5:
                manager.displayReceptionists();
                break;
            case 6:
                manager.displayPatients();
                break;
            case 7:
                manager.sortDoctors();
                break;
            case 8:
                manager.sortReceptionists();
                break;
            case 9:
                manager.assignShifts();
                break;
            case 10:
            return main();
            break;
            case 11:
             system("cls");
            cout <<BOLD<<RED<< "Exiting the UET MediCare System...\n"<<RESET;
            Sleep(1500);
            exit(0);
            break;
            default:
                cout <<RED<<BOLD<< "Invalid choice.\n"<<RESET;
            }
            break;
        }

        case 2: { // Doctor functionalities
            cout <<BOLD<<BLUE<< "\n===== Doctor's Dashboard =====\n"<<RESET;
            cout << "1. Add Patient Appointment\n2. Remove Patient Appointment\n3. Display Appointments\n";
            cout << "4. Generate Report\n5. View Patient Queue\n6. Check Patient Assignment\n";
            cout << "7. Display All Doctor Connections\n8. Go to Main Menu\n9. Generate Patient's Bill\n10. View Time Table\n11. Exit\n";
            int doctorChoice;
            cin >> doctorChoice;

            switch (doctorChoice) {
            case 1:
                cout << "Enter Doctor's Name: ";
                cin >> doctorName;
                cout << "Enter Patient's Name: ";
                cin >> patientName;
                doctor.addPatientAppointment(doctorName, patientName);
                cout << "Appointment added successfully.\n";
                break;
            case 2:
                cout << "Enter Doctor's Name: ";
                cin >> doctorName;
                cout << "Enter Patient's Name: ";
                cin >> patientName;
                doctor.removePatientAppointment(doctorName, patientName);
                cout << "Appointment removed successfully.\n";
                break;
            case 3:
                cout << "Enter Doctor's Name to view appointments: ";
                cin >> doctorName;
                doctor.displayAppointments(doctorName);
                break;
            case 4:
                doctor.generateAndSaveReport();
                break;
            case 5:
                doctor.viewPatientQueue(receptionist.getAppointmentQueue());
                break;
            case 6:
                cout << "Enter Doctor's Name: ";
                cin >> doctorName;
                cout << "Enter Patient's Name: ";
                cin >> patientName;
                if (doctor.isPatientAssigned(doctorName, patientName)) {
                    cout << patientName << " is assigned to Dr. " << doctorName << endl;
                } else {
                    cout << patientName << " is NOT assigned to Dr. " << doctorName << endl;
                }
                break;
            case 7:
                doctor.displayDoctorConnections();
                break;
            case 8:
                return main();
                break;
            case 9:
            doctor.generateBill(patient);
            break;
            case 10:
            doctor.viewTimeTable();
            break;
            case 11:
             system("cls");
            cout <<BOLD<<RED<< "Exiting the UET MediCare System...\n"<<RESET;
            Sleep(1500);
            exit(0);
            default:
                cout <<BOLD<<RED<< "Invalid choice.\n"<<RESET;
            }
            break;
        }

        case 3: { // Patient functionalities
            cout <<BOLD<<BLUE<< "\n===== Patient's Dashboard =====\n"<<RESET;
            cout << "1. View Report\n2. View Bill\n3. Update Details\n4. Request Appointment\n5. Go to Main Menu\n6. Exit";
            int patientChoice;
            cin >> patientChoice;

            switch (patientChoice) {
            case 1:
                patient.viewReport();
                break;
            case 2:
                patient.viewBill();
                break;
            case 3:
                patient.updateDetails();
                break;
            case 4:
                patient.requestAppointment();
                break;
            case 5:
            return main();
            break;
            case 6:
             system("cls");
            cout <<BOLD<<RED<< "Exiting the UET MediCare System...\n"<<RESET;
            Sleep(1500);
            exit(0);
            default:
                cout <<BOLD<<RED<< "Invalid choice.\n"<<RESET;
            }
            break;
        }

        case 4: { // Receptionist functionalities
           cout <<BOLD<<BLUE<< "\n===== Receptionist's Dashboard =====\n"<<RESET;
            cout << "1. Add Patient\n2. Schedule Appointment\n3. View Appointments\n4. Undo Last Action\n5. Go to Main Menu\n6. Exit";
            int receptionistChoice;
            cin >> receptionistChoice;

            switch (receptionistChoice) {
            case 1:
                cout << "Enter the Patient's name: ";
                cin.ignore(); // To clear the input buffer
                getline(cin, pname);
                cout << "Enter the Patient's id: ";
                cin >> pid;
                cout << "Enter the Patient's CNIC: ";
                cin >> pcnic;

                receptionist.addPatient(pname, pid, pcnic);
                break;
            case 2:
                receptionist.scheduleAppointment();
                break;
            case 3:
                receptionist.viewAppointments();
                break;
            case 4:
                receptionist.undo();
                break;
            case 5:
            return main();
            break;
            case 6:
             system("cls");
             cout <<BOLD<<RED<< "Exiting the UET MediCare System...\n"<<RESET;
             Sleep(1500);
            exit(0);
            default:
                cout <<BOLD<<RESET<< "Invalid choice.\n"<<RESET;
            }
            break;
        }
        case 5:
        system("cls");
         cout <<BOLD<<RED<< "Exiting the UET MediCare System...\n"<<RESET;
        Sleep(1500);
           
            return 0;
        default:

            cout <<BOLD<<RED<< "Invalid choice. Please try again.\n";
        }
    }
}
