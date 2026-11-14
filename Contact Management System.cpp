// Contact Management System (file-based) - C++
// Features: add, view, search, delete contacts. Data is saved automatically to contacts.txt

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string DATA_FILE = "contacts.txt";
const char DELIM = '|';

struct Contact {
    int id;
    string name;
    string phone;
    string email;
    string address;
};

// ---------- helpers ----------
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c) { return tolower(c); });
    return s;
}

string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// The delimiter must not appear inside stored text
string sanitize(string s) {
    replace(s.begin(), s.end(), DELIM, '/');
    return trim(s);
}

bool isValidPhone(const string &p) {
    if (p.size() < 7 || p.size() > 15) return false;
    for (char c : p)
        if (!isdigit(static_cast<unsigned char>(c))) return false;
    return true;
}

string readLine(const string &prompt) {
    string line;
    cout << prompt;
    getline(cin, line);
    return sanitize(line);
}

// ---------- file handling ----------
vector<Contact> loadContacts() {
    vector<Contact> contacts;
    ifstream file(DATA_FILE);
    if (!file) return contacts; // first run: no file yet

    string line;
    while (getline(file, line)) {
        if (trim(line).empty()) continue;
        stringstream ss(line);
        string idStr;
        Contact c;
        getline(ss, idStr, DELIM);
        getline(ss, c.name, DELIM);
        getline(ss, c.phone, DELIM);
        getline(ss, c.email, DELIM);
        getline(ss, c.address, DELIM);
        try {
            c.id = stoi(idStr);
        } catch (...) {
            continue; // skip corrupted line
        }
        contacts.push_back(c);
    }
    return contacts;
}

bool saveContacts(const vector<Contact> &contacts) {
    ofstream file(DATA_FILE, ios::trunc);
    if (!file) {
        cout << "Error: could not write to " << DATA_FILE << "\n";
        return false;
    }
    for (const Contact &c : contacts) {
        file << c.id << DELIM << c.name << DELIM << c.phone << DELIM
             << c.email << DELIM << c.address << "\n";
    }
    return true;
}

int nextId(const vector<Contact> &contacts) {
    int maxId = 0;
    for (const Contact &c : contacts) maxId = max(maxId, c.id);
    return maxId + 1;
}

// ---------- display ----------
void printTable(const vector<Contact> &list) {
    cout << "\n" << left << setw(5) << "ID" << setw(22) << "NAME"
         << setw(16) << "PHONE" << setw(28) << "EMAIL" << "ADDRESS\n";
    cout << string(90, '-') << "\n";
    for (const Contact &c : list) {
        cout << left << setw(5) << c.id << setw(22) << c.name.substr(0, 20)
             << setw(16) << c.phone << setw(28) << c.email.substr(0, 26)
             << c.address << "\n";
    }
    cout << "\n";
}

// ---------- operations ----------
void addContact(vector<Contact> &contacts) {
    Contact c;
    cout << "\n--- Add Contact ---\n";

    c.name = readLine("Name    : ");
    if (c.name.empty()) {
        cout << "Name cannot be empty.\n";
        return;
    }

    c.phone = readLine("Phone   : ");
    if (!isValidPhone(c.phone)) {
        cout << "Invalid phone number (use 7-15 digits only).\n";
        return;
    }

    for (const Contact &x : contacts) {
        if (x.phone == c.phone) {
            cout << "A contact with this phone number already exists.\n";
            return;
        }
    }

    c.email = readLine("Email   : ");
    c.address = readLine("Address : ");
    c.id = nextId(contacts);

    contacts.push_back(c);
    if (saveContacts(contacts))
        cout << "Contact added and saved (ID " << c.id << ").\n";
}

void viewContacts(const vector<Contact> &contacts) {
    cout << "\n--- All Contacts ---";
    if (contacts.empty()) {
        cout << "\nNo contacts found.\n";
        return;
    }
    printTable(contacts);
    cout << "Total: " << contacts.size() << " contact(s)\n";
}

void searchContact(const vector<Contact> &contacts) {
    cout << "\n--- Search Contact ---\n";
    string key = toLower(readLine("Enter name or phone number: "));
    if (key.empty()) {
        cout << "Search term cannot be empty.\n";
        return;
    }

    vector<Contact> found;
    for (const Contact &c : contacts) {
        if (toLower(c.name).find(key) != string::npos ||
            c.phone.find(key) != string::npos)
            found.push_back(c);
    }

    if (found.empty())
        cout << "No matching contact found.\n";
    else {
        printTable(found);
        cout << found.size() << " match(es) found.\n";
    }
}

void deleteContact(vector<Contact> &contacts) {
    cout << "\n--- Delete Contact ---\n";
    if (contacts.empty()) {
        cout << "No contacts to delete.\n";
        return;
    }

    string input = readLine("Enter contact ID or phone number to delete: ");
    auto it = find_if(contacts.begin(), contacts.end(), [&](const Contact &c) {
        return to_string(c.id) == input || c.phone == input;
    });

    if (it == contacts.end()) {
        cout << "Contact not found.\n";
        return;
    }

    cout << "Delete \"" << it->name << "\" (" << it->phone << ")? (y/n): ";
    string confirm;
    getline(cin, confirm);
    if (toLower(trim(confirm)) == "y") {
        contacts.erase(it);
        if (saveContacts(contacts)) cout << "Contact deleted and saved.\n";
    } else {
        cout << "Deletion cancelled.\n";
    }
}

void showMenu() {
    cout << "\n==============================\n"
         << "   CONTACT MANAGEMENT SYSTEM\n"
         << "==============================\n"
         << " 1. Add Contact\n"
         << " 2. View All Contacts\n"
         << " 3. Search Contact\n"
         << " 4. Delete Contact\n"
         << " 5. Save to File\n"
         << " 6. Exit\n"
         << "------------------------------\n"
         << "Enter choice: ";
}

int main() {
    vector<Contact> contacts = loadContacts();
    cout << "Loaded " << contacts.size() << " contact(s) from " << DATA_FILE << "\n";

    while (true) {
        showMenu();
        string choice;
        getline(cin, choice);
        choice = trim(choice);

        if (cin.eof()) break;

        if (choice == "1") addContact(contacts);
        else if (choice == "2") viewContacts(contacts);
        else if (choice == "3") searchContact(contacts);
        else if (choice == "4") deleteContact(contacts);
        else if (choice == "5") {
            if (saveContacts(contacts)) cout << "Contacts saved to " << DATA_FILE << ".\n";
        } else if (choice == "6") {
            saveContacts(contacts); // always persist before exit
            cout << "Data saved. Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice. Please enter a number from 1 to 6.\n";
        }
    }
    return 0;
}
