# STUDENT_RECORD_MANAGEMENT_SYSTEM
A complete Student Record Management System built in C using CSV-based storage. Supports adding, updating, deleting, searching, analytics, toppers, report card generation, and login authentication — all implemented using core C features like structures, file handling, string parsing, and modular functions.

📚 Student Record Management System (C Project)

A complete Student Record Management System built in C, using CSV file handling, structures, and modular programming.
This project manages student data with full CRUD operations, analytics, toppers, and detailed report card generation — all done using pure C (no external libraries).

🚀 Features
🔹 Student Data Management

Add new student records

Duplicate roll-number check

Update existing records

Delete a record safely (via temp file overwrite)

🔹 Search

Search student by roll number

Search student by name

🔹 Analytics

Overall class topper

Subject-wise topper

Students scoring less than 50% (Needs Guidance)

Mean marks for all subjects

🔹 Report Card Generator

Generates a complete formatted report card containing:

Student details

Subject-wise marks

Total marks

Percentage

Grade (A–E)

🔹 File Handling

All data stored in records.csv

Safe update & delete using temp-file method

CSV parsing using sscanf()

🔹 Login System

Basic admin login using password verification

🧠 Concepts Used
✔ Structures (struct)

To store name, roll number, class, phone number, email, marks, and percentage.

✔ File Handling

Using:

fopen(), fgets(), fputs(), fprintf(), sscanf(), remove(), rename()

✔ String Manipulation

strcmp() for comparisons

scanf with advanced format specifiers

Multi-word string input with " %[^\n]"

✔ Modular Programming

5+ clean functions, each handling a separate feature.

✔ Defensive Programming

Empty file handling

Input validation

Duplicate checks

Subject validation

Error-safe updating and deleting

🗂 CSV Data Format
Name,Roll_No,Class,Phone_no,E-Mail,Eng,Phy,Chem,Maths,C.S,Percent


Each student entry is appended as a new line.

🖥 How to Run
1️⃣ Compile
gcc main.c -o student_system

2️⃣ Run
./student_system

3️⃣ Default Password
admin123

⭐ If you like this project

Give the repository a star ⭐ on GitHub — it motivates future improvements!
