#include "Functions.h"
#include <fstream> // For file handling
#include <sstream> // For string stream


int main()
{
    vector <Student> students;
    vector <Room> rooms;
    vector <Course> courses;
    vector <Teacher> teachers;
    
    ofstream StudentsFile("Students.txt");
    StudentsFile << "Talha Section-A 01" << endl;
    StudentsFile << "Usman Section-A 02" << endl;
    StudentsFile << "Hamza Section-A 03" << endl;
    StudentsFile << "Hannan Sectio-B 04" << endl;
    StudentsFile << "Abbas Section-B 05" << endl;
    StudentsFile.close();
    
    ofstream TeachersFile("Teachers.txt");
    TeachersFile << "Tamim Testing,PHD 10" << endl;
    TeachersFile << "Raja AI,PHD 11" << endl;
    TeachersFile << "Waleed SE,MS 12" << endl;
    TeachersFile << "Sadaf OHS,MS 13" << endl;
    TeachersFile.close();
    
    ofstream CoursesFile("Courses.txt");
    CoursesFile << "CSC-113 Programming Raja 04-19 8:30->10:30 Monday Section-A" << endl;
    CoursesFile << "CSC-114 OOPS Tamim 04-18 10:35->12:35 Monday Section-A" << endl;
    CoursesFile << "CSC-115 Maths Waleed 04-17 2:30->5:30 Monday Section-A" << endl;
    
    CoursesFile << "CSC-114 OOPS Tamim 04-18 10:35->12:35 Tuesday Section-A" << endl;
    CoursesFile << "CSC-113 Programming Raja 04-19 2:30->3:30 Tuesday Section-A" << endl;
    CoursesFile << "CSC-115 Maths Waleed 04-17 3:30->5:30 Tuesday Section-A" << endl;
    
    CoursesFile << "CSC-116 OHS Sadaf 04-17 9:30->11:30 Wednesday Section-A" << endl;
    CoursesFile << "CSC-115 Maths Waleed 04-19 12:30->1:30 Wednesday Section-A" << endl;
    
    CoursesFile << "CSC-115 Maths Waleed 04-17 2:30->5:30 Thursday Section-A" << endl;
    
    CoursesFile << "CSC-113 Programming Raja 04-19 10:30->12:30 Monday Section-B" << endl;
    CoursesFile << "CSC-114 OOPS Tamim 04-18 12:35->2:25 Monday Section-B" << endl;
    CoursesFile << "CSC-115 Maths Waleed 04-17 2:30->5:30 Monday Section-B" << endl;
    
    CoursesFile << "CSC-114 OOPS Tamim 04-18 3:35->5:35 Tuesday Section-B" << endl;
    CoursesFile << "CSC-113 Programming Raja 04-19 8:30->9:30 Tuesday Section-B" << endl;
    CoursesFile << "CSC-115 Maths Waleed 04-17 10:30->12:30 Tuesday Section-B" << endl;
    
    CoursesFile << "CSC-116 OHS Sadaf 04-17 11:30->2:30 Wednesday Section-B" << endl;
    CoursesFile << "CSC-115 Maths Waleed 04-19 9:30->10:30 Wednesday Section-B" << endl;
    
    CoursesFile << "CSC-115 Maths Waleed 04-17 2:30->5:30 Friday Section-B" << endl;
    
    CoursesFile.close();
    
    ofstream RoomsFile("Rooms.txt");
    RoomsFile << "Classroom-A 04-19 5" << endl;
    RoomsFile << "Classroom-B 04-18 5" << endl;
    RoomsFile << "Classroom-C 04-17 5" << endl;
    RoomsFile.close();
    
    
    
    // Read students' data from file
    ifstream studentsFile("Students.txt");
    string line;
    
    while (getline(studentsFile, line))
    {
        stringstream ss(line);
        string name, section;
        int rollNumber;
        ss >> name >> section >> rollNumber;
        Student student;
        student.Name = name;
        student.studentSection = section;
        student.ID = rollNumber;
        students.push_back(student);
    }
    
    studentsFile.close();

    // Read rooms' data from file
    ifstream roomsFile("Rooms.txt");
    while (getline(roomsFile, line))
    {
        stringstream ss(line);
        string name, code;
        int capacity;
        ss >> name >> code >> capacity;
        Room room;
        room.name = name;
        room.code = code;
        room.capacity = capacity;
        rooms.push_back(room);
    }
    
    roomsFile.close();

    // Read teachers' data from file
    ifstream teachersFile("Teachers.txt");
    while (getline(teachersFile, line)) 
    {
        stringstream ss(line);
        string name, specialization;
        int ID;
        ss >> name >> specialization >> ID;
        Teacher teacher;
        teacher.Name = name;
        teacher.ID = ID;
        teacher.specialization = specialization;
        teachers.push_back(teacher);
    }
    
    teachersFile.close();

    // Read courses' data from file
    ifstream coursesFile("Courses.txt");
    while (getline(coursesFile, line))
    {
        stringstream ss(line);
        string code, name, teacherName, roomCode, timeSlot, Day, section;
        ss >> code >> name >> teacherName >> roomCode >> timeSlot >> Day >> section;
        Course course;
        course.code = code;
        course.name = name;
        course.timeslot = timeSlot;
        course.Day = Day;
        course.section = section;

        // Find teacher
        auto it = find_if(teachers.begin(), teachers.end(), [teacherName](const Teacher& teacher) {
        return teacher.Name == teacherName;
    });
        
    if (it != teachers.end()) 
    {
        course.teacher = &(*it);
    } 
    else
    {
        cout << "\n\nError: Teacher not found for course " << code << endl;
        continue; // Skip this course
    }

    // Find room
    auto roomIt = find_if(rooms.begin(), rooms.end(), [roomCode](const Room& room) {
        return room.code == roomCode;
    });
    if (roomIt != rooms.end()) 
    {
        course.room = &(*roomIt);
    } 
    else 
    {
        cout << "\n\nError: Room not found for course " << code << endl;
        continue; // Skip this course
    }
    courses.push_back(course);
}
coursesFile.close();

    // Generate timetables
    int choice;
    do 
    {
        // Display menu
        cout << "\nMenu:\n";
        cout << "1. View teacher-wise time table\n";
        cout << "2. View section-wise time table\n";
        cout << "3. View room-wise time table\n";
        cout << "4. Student-Wise time table\n";
        cout << "5. Query: Day-Wise timetable\n";
        cout << "6. Query: Who is Teaching at What Day and Time\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) 
        {
            case 1:
                generateTeacherWiseTimeTable(courses);
                break;
            case 2:
                generateSectionWiseTimeTable(courses);
                break;
            case 3:
                generateRoomWiseTimeTable(courses);
                break;
            case 4:
                generateStudentWiseTimeTable(courses);
                break;
            case 5:
                viewDailyTimetable(courses);
                break;
            case 6:
                query1(courses);
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }

    } while (choice != 0);

    return 0;
}


