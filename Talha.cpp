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
    vector<Student> students;
    vector<Teacher> teachers;
    vector<Room> rooms;
    vector<Course> courses;

    // Set specific capacity for room "4-19"
    for (auto& room : rooms) 
    {
        if (room.code == "4-19")
        {
            room.capacity = 16;
            break;
        }
    }

    int choice;

    do 
    {
        // Display menu
        cout << "\nMenu:\n";
        cout << "\n1. View time table by time and day.\n";
        cout << "\n2. View time table by day.\n";
        cout << "\n3. Add students to rooms.\n";
        cout << "\n4. Remove a student from a room.\n";
        cout << "\n5. Check room availability for makeup class.\n";
        cout << "\n6. Switch teacher's room.\n";
        cout << "\n7. Generate teacher-wise time table.\n";
        cout << "\n8. Generate section-wise time table.\n";
        cout << "\n9. Generate room-wise time table.\n";
        cout << "\n10. Add a new course.\n";
        cout << "\n0. Exit.\n";
        cout << "\n\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) 
        {
        case 1: 
        {
            string time, day;
            cout << "\n\nEnter time (HH:MM): ";
            getline(cin, time);
            cout << "\n\nEnter day: ";
            getline(cin, day);
            displayTimeTableForTime(courses, time, day);
            break;
        }
        case 2: 
        {
            string day;
            cout << "\n\nEnter day: ";
            getline(cin, day);
            displayTimeTableForDay(courses, day);
            break;
        }
        case 3: 
        {
            // Adding students to rooms
            string studentName, courseCode, roomNumber;
            cout << "\n\nEnter student name: ";
            getline(cin, studentName);
            cout << "\n\nEnter course code: ";
            getline(cin, courseCode);
            cout << "\n\nEnter room number: ";
            getline(cin, roomNumber);
            // Find the specified course
            Course* selectedCourse = nullptr;
            for (auto& course : courses) 
            {
                if (course.code == courseCode && course.room->code == roomNumber)
                {
                    selectedCourse = &course;
                    break;
                }
            }

            if (selectedCourse == nullptr) 
            {
                cout << "\n\nCourse with code " << courseCode << " is not being taught in room " << roomNumber << "." << endl;
            }
            else 
            {
                // Check if the room has available capacity
                if (selectedCourse->room->students.size() < selectedCourse->room->capacity) 
                {
                    // Add the student to the room
                    Student newStudent;
                    newStudent.Name = studentName;
                    cout << "\n\nEnter student roll ID: ";
                    cin >> newStudent.ID;
                    cin.ignore();
                    newStudent.studentSection = ""; // Assuming section information is not entered manually
                    selectedCourse->room->students.push_back(make_shared<Student>(newStudent));
                    cout << "\n\nStudent " << studentName << " added to room " << roomNumber << " for course " << selectedCourse->name << "." << endl;
                }
                else 
                {
                    cout << "\n\nRoom " << roomNumber << " is full for course " << selectedCourse->name << "." << endl;
                }
            }
            break;
        }
        case 4: 
        {
            string studentName;
            cout << "\n\nEnter student name to remove: ";
            getline(cin, studentName);
            for (auto& room : rooms)
            {
                removeStudentFromRoom(room, studentName);
            }
            cout << "\n\nStudent removed from all rooms successfully.\n";
            break;
        }
        case 5: 
        {
            string roomNumber, time;
            cout << "\n\nEnter room number: ";
            getline(cin, roomNumber);
            cout << "\n\nEnter time (HH:MM): ";
            getline(cin, time);
            if (isRoomAvailableForMakeupClass(courses, roomNumber, time)) 
            {
                cout << "\n\nRoom " << roomNumber << " is available for makeup class at " << time << ".\n";
            }
            else
            {
                cout << "\n\nRoom " << roomNumber << " is not available for makeup class at " << time << ".\n";
            }
            break;
        }
        case 6: 
        {
            string courseCode, newRoomNumber;
            cout << "\n\nEnter the course code of the course to switch: ";
            getline(cin, courseCode);
            cout << "\n\nEnter the new room number: ";
            getline(cin, newRoomNumber);
            switchTeacherRoom(courses, courseCode, newRoomNumber, rooms);
            cout << "\n\nTeacher's room switched successfully.\n";
            break;
        }
        case 7: 
        {
            generateTeacherWiseTimeTable(courses);
            break;
        }
        case 8: 
        {
            generateSectionWiseTimeTable(courses);
            break;
        }
        case 9: 
        {
            generateRoomWiseTimeTable(courses);
            break;
        }
        case 10:
        {
            string courseCode, courseName, teacherName, roomNumber, timeSlot, teacherSpecialization;
            cout << "Enter course code: ";
            getline(cin, courseCode);
            cout << "Enter course name: ";
            getline(cin, courseName);
            cout << "Enter teacher name: ";
            getline(cin, teacherName);
            cout << "Enter teacher specialization: ";
            getline(cin, teacherSpecialization);
            Teacher teacher(teacherName, teacherSpecialization);

            cout << "Enter room number: ";
            getline(cin, roomNumber);
            cout << "Enter time slot (HH:MM Day): ";
            getline(cin, timeSlot);
            addCourse(courses, courseCode, courseName, teacher, rooms[0], timeSlot); // Just assigning to the first room for simplicity
            break;
        }
        case 0:
            cout << "\nExiting...\n";
            break;
        default:
            cout << "\nInvalid choice. Please enter a valid option.\n";
            break;
        }

    } while (choice != 0);

    cout << endl << endl;
    system("pause>0");
    return 0;
}
