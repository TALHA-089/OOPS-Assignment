#include "Functions.h"
#include<memory>
#include<algorithm>



int main()
{
    cout << endl << endl;

    SYSTEM LogInSystem;
    int login_choice;
    bool loggedIn = false;

    do {
        cout << "\nLogin Menu:\n";
        cout << "\n1. Register\n";
        cout << "\n2. Login\n";
        cout << "\n0. Exit\n";
        cout << "\n\nEnter your choice: ";
        cin >> login_choice;
        cin.ignore();

        switch (login_choice) 
        {
            case 1:

                LogInSystem.setUser();
                break;

            case 2:

                if (LogInSystem.login()) 
                {
                    loggedIn = true; // Set loggedIn to true upon successful login
                    cout << "\n\nLogin successful. Proceeding to main menu...\n";
                } 
                else 
                {
                    cout << "\nLogin failed. Please try again.\n";
                }
                break;

            case 0:

                cout << "\nExiting...\n";
                return 0; // Exit the program

            default:

                cout << "\nInvalid choice. Please try again.\n";
                break;
        }
    } while (!loggedIn); 

     // Main Program Menu
    vector<Student> students = {
        {"Alice", "Section A", "001"},
        {"Bob", "Section B", "002"},
        {"Charlie", "Section C", "003"},
        {"David", "Section D", "004"},
        {"Eva", "Section E", "005"}
    };

    vector<Teacher> teachers = {
        {"Mr. Smith", "Software Engineering"},
        {"Ms. Johnson", "Computer Science"},
        {"Mr. Brown", "Database Management"},
        {"Ms. White", "Network Security"},
        {"Mr. Green", "Algorithms"}
    };

    vector<Room> rooms = {
        {"Room 101", 50},
        {"Room 102", 50},
        {"Room 103", 50},
        {"Lab 1", 50},
        {"Lab 2", 50}
    };

    // Set specific capacity for room "4-19"
    for (auto& room : rooms) {
        if (room.roomNumber == "4-19") {
            room.capacity = 16;
            break;
        }
    }

    vector<Course> courses = {
        {"4-17", "Computer Programming", &teachers[0], "8:30 Monday", &rooms[0]},
        {"4-18", "Intro to Software Engineering", &teachers[1], "9:45 Monday", &rooms[1]},
        {"4-19", "Object Oriented Programming", &teachers[2], "11:00 Monday", &rooms[2]},
        {"Lab 1", "Lab Computing Fundamentals", &teachers[3], "8:30 Tuesday", &rooms[3]},
        {"Lab 2", "Lab DSA", &teachers[4], "10:00 Tuesday", &rooms[4]}
    };

    int choice;

     do {
        // Display menu
        cout << "\nMenu:\n";
        cout << "1. View time table by time and day.\n";
        cout << "2. View time table by day.\n";
        cout << "3. Add students to rooms.\n";
        cout << "4. Remove a student from a room.\n";
        cout << "5. Check room availability for makeup class.\n";
        cout << "6. Switch teacher's room.\n";
        cout << "7. Generate teacher-wise time table.\n";
        cout << "8. Generate section-wise time table.\n";
        cout << "9. Generate room-wise time table.\n";
        cout << "10. Add a new course.\n";
        cout << "0. Exit.\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string time, day;
                cout << "Enter time (HH:MM): ";
                cin >> time;
                cout << "Enter day: ";
                cin >> day;
                displayTimeTableForTime(courses, time, day);
                break;
            }
            case 2: {
                string day;
                cout << "Enter day: ";
                cin >> day;
                displayTimeTableForDay(courses, day);
                break;
            }
            case 3: {
                // Adding students to rooms
                string studentName, courseCode, roomNumber;
                cout << "Enter student name: ";
                cin >> studentName;
                cout << "Enter course code: ";
                cin >> courseCode;
                cout << "Enter room number: ";
                cin >> roomNumber;

                // Find the specified course
                Course* selectedCourse = nullptr;
                for (auto& course : courses) {
                    if (course.courseCode == courseCode && course.room->roomNumber == roomNumber) {
                        selectedCourse = &course;
                        break;
                    }
                }

                if (selectedCourse == nullptr) {
                    cout << "Course with code " << courseCode << " is not being taught in room " << roomNumber << "." << endl;
                } else {
                    // Check if the room has available capacity
                    if (selectedCourse->room->students.size() < selectedCourse->room->capacity) {
                        // Add the student to the room
                        Student newStudent;
                        newStudent.name = studentName;
                        cout << "Enter student roll ID: ";
                        cin >> newStudent.rollID;
                        newStudent.section =  ""; // Assuming section information is not entered manually
                        selectedCourse->room->students.push_back(make_shared<Student>(newStudent));
                        cout << "Student " << studentName << " added to room " << roomNumber << " for course " << selectedCourse->courseName << "." << endl;
                    } else {
                        cout << "Room " << roomNumber << " is full for course " << selectedCourse->courseName << "." << endl;
                    }
                }
                break;
            }
            case 4: {
                string studentName;
                cout << "Enter student name to remove: ";
                cin >> studentName;
                for (auto& room : rooms) {
                    removeStudentFromRoom(room, studentName);
                }
                cout << "Student removed from all rooms successfully.\n";
                break;
            }
            case 5: {
                string roomNumber, time;
                cout << "Enter room number: ";
                cin >> roomNumber;
                cout << "Enter time (HH:MM): ";
                cin >> time;
                if (isRoomAvailableForMakeupClass(courses, roomNumber, time)) {
                    cout << "Room " << roomNumber << " is available for makeup class at " << time << ".\n";
                } else {
                    cout << "Room " << roomNumber << " is not available for makeup class at " << time << ".\n";
                }
                break;
            }
            case 6: {
                string courseCode, newRoomNumber;
                cout << "Enter the course code of the course to switch: ";
                cin >> courseCode;
                cout <<  "Enter the new room number: ";
                cin >> newRoomNumber;
                switchTeacherRoom(courses, courseCode, newRoomNumber, rooms);
                cout << "Teacher's room switched successfully.\n";
                break;
            }
            case 7: {
                generateTeacherWiseTimeTable(courses);
                break;
            }
            case 8: {
                generateSectionWiseTimeTable(courses);
                break;
            }
            case 9: {
                generateRoomWiseTimeTable(courses);
                break;
            }
            case 10: {
                string courseCode, courseName, teacherName, roomNumber, timeSlot, teacherSpecialization;
                cout << "Enter course code: ";
                cin >> courseCode;
                cout << "Enter course name: ";
                cin >> courseName;
                cout << "Enter teacher name: ";
                cin >> teacherName;
                cout << "Enter teacher specialization: ";
                cin >> teacherSpecialization;
                Teacher teacher {teacherName, teacherSpecialization};
               
                cout << "Enter room number: ";
                cin >> roomNumber;
                cout << "Enter time slot (HH:MM Day): ";
                cin >> timeSlot;
                addCourse(courses, courseCode, courseName, teacher, rooms[0], timeSlot); // Just assigning to the first room for simplicity
                break;
            }
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }

    } while (choice != 0);

    cout<<endl<<endl;
    system("pause>0");
    return 0;
}