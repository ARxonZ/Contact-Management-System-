# 📇 Contact Management System (C++)

A simple, menu-driven **file-based Contact Management System** written in C++. Users can add, view, search and delete contacts, and all data is stored permanently in a text file using C++ file handling (`fstream`).

## ✨ Features

- **Add Contact** – name, phone, email and address (with phone validation and duplicate check)
- **View All Contacts** – neat table with auto-generated IDs
- **Search Contact** – by name (partial, case-insensitive) or phone number
- **Delete Contact** – by ID or phone number, with confirmation
- **Save to File** – data is saved automatically after every change and on exit
- **Persistent storage** – contacts are reloaded every time the program starts

## 🛠️ Tech Stack

- Language: C++ (C++11 or later)
- Concepts: file handling (`ifstream` / `ofstream`), structures, vectors, string handling, input validation

## 📁 Project Structure

```
contact-management-system/
├── main.cpp               # Complete source code
├── sample_contacts.txt    # Sample data (rename to contacts.txt to try it)
├── .gitignore
└── README.md
```

## 🚀 How to Run

**Requirements:** a C++ compiler such as `g++`.

```bash
# 1. Clone the repository
git clone https://github.com/<your-username>/contact-management-system.git
cd contact-management-system

# 2. Compile
g++ -std=c++17 -o contact_manager main.cpp

# 3. Run
./contact_manager        # Linux / macOS
contact_manager.exe      # Windows
```

## 📖 Menu

```
==============================
   CONTACT MANAGEMENT SYSTEM
==============================
 1. Add Contact
 2. View All Contacts
 3. Search Contact
 4. Delete Contact
 5. Save to File
 6. Exit
```

## 💾 Data Format

Contacts are stored in `contacts.txt` (created automatically), one per line, separated by `|`:

```
ID|Name|Phone|Email|Address
1|Rahul Sharma|9876543210|rahul@gmail.com|123, MG Road, Delhi - 110001
```

## 🖥️ Sample Output

```
ID   NAME                  PHONE           EMAIL                       ADDRESS
------------------------------------------------------------------------------------------
1    Rahul Sharma          9876543210      rahul@gmail.com             123, MG Road, Delhi - 110001
2    Priya Verma           9123456780      priya@gmail.com            45, Park Street, Kolkata
3    Amit Singh            9988776655      amit@gmail.com             78, Lake Road, Pune
```

##Future Improvements

- Edit/update contact option
- Sort contacts by name
- Export to CSV
- Basic GUI

##Author

**<Your Name>** – [GitHub](https://github.com/<your-username>)

---
If you found this useful, give the repo a star!
