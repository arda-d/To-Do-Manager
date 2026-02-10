Task Manager (C++)

This project is a console-based task management application written in C++. It allows users to create, remove, list, and complete tasks. Each task includes a title, description, priority level, and deadline.
The application uses object-oriented programming principles and the C++ Standard Library. Tasks are stored in a vector and can be sorted by priority or deadline using STL algorithms and lambda expressions.
To prevent data loss, tasks are automatically loaded from a file when the program starts and saved back to the file when the program exits. File handling is implemented using fstream, and date handling is done with time_t and tm structures.
This project was developed as a learning exercise to practice C++ fundamentals, STL usage, file I/O, and basic time management in a console application.
