#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Registration {
    string fname;
    string lname;
    string dob;
    string ph_no;
    string username;
    string password;
};
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}
bool isValidPhoneNumber(const string& str) {
    for (char c : str) {
        if (!isDigit(c) && c != '+' && c != '-' && c != ' ') {
            return false;
        }
    }
    return true;
}

void createAccount() {
    ofstream out("login.txt", ios::out);
    if (out.fail()) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    Registration reg;
    cout << "Enter your first name: ";
    getline(cin, reg.fname);

    cout << "Enter your last name: ";
    getline(cin, reg.lname);

    cout << "Enter your date of birth (YYYY-MM-DD): ";
    getline(cin, reg.dob);

    cout << "Enter your phone number: ";
    getline(cin, reg.ph_no);
    while (!isValidPhoneNumber(reg.ph_no)) {
        cout << "Invalid phone number. Please try again: ";
        getline(cin, reg.ph_no);
    }

    cout << "Create your username: ";
    getline(cin, reg.username);

    cout << "Create your password: ";
    getline(cin, reg.password);

    string re_password;
    cout << "Retype your password: ";
    getline(cin, re_password);
    while (reg.password != re_password) {
        cout << "Passwords do not match. Retype your password: ";
        getline(cin, re_password);
    }

    out << reg.fname << endl;
    out << reg.lname << endl;
    out << reg.dob << endl;
    out << reg.ph_no << endl;
    out << reg.username << endl;
    out << reg.password << endl;

    cout << "Account created successfully!" << endl;

    out.close();
}

void logIn() {
    string username, password;
    cout << "Enter your username: ";
    getline(cin, username);

    cout << "Enter your password: ";
    getline(cin, password);

    ifstream in("login.txt",ios::in);
    if (in.fail()) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    Registration reg;
    bool found = false;
    while (getline(in, reg.fname)) {
        getline(in, reg.lname);
        getline(in, reg.dob);
        getline(in, reg.ph_no);
        getline(in, reg.username);
        getline(in, reg.password);

        if (reg.username == username && reg.password == password) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Login successful!" << endl;
        cout << "Name: " << reg.fname << " " << reg.lname << endl;
        cout << "Date of Birth: " << reg.dob << endl;
        cout << "Phone Number: " << reg.ph_no << endl;
    } else {
        cout << "Invalid username or password." << endl;
    }

    in.close();
}

int main() {
    int choice;
    while (true) {
        cout << "1. Log In" << endl;
        cout << "2. Create Account" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  

        switch (choice) {
            case 1:
                logIn();
                break;
            case 2:
                createAccount();
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }
}
