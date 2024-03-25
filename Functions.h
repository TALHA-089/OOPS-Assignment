#pragma once
#include "Classes.h"
#include<vector>
#include<map>
#include<array>

// Function declarations
void generateTeacherWiseTimeTable(const vector<Course>& courses);
void generateSectionWiseTimeTable(const vector<Course>& courses);
void generateRoomWiseTimeTable(const vector<Course>& courses);
void displayTimeTableForTime(const vector<Course>& courses, const string& time, const string& day);
void displayTimeTableForDay(const vector<Course>& courses, const string& day);
void displayTimeTable(const vector<Course>& timeTable);
void addStudentsToRoom(Room& room, const vector<Student>& students);
void displayStudentsPerRoom(const vector<Room>& rooms);
void removeStudentFromRoom(Room& room, const string& studentName);
bool isRoomAvailableForMakeupClass(const vector<Course>& courses, const string& roomNumber, const string& time);
void switchTeacherRoom(vector<Course>& courses, const string& courseCode, const string& newRoomNumber, vector<Room>& rooms);
void addCourse(vector<Course>& courses, const string& courseCode, const string& courseName, Teacher& teacher, Room& room, const string& timeSlot);
void addStudentsToRoom(std::shared_ptr<Room>& room, const std::vector<std::shared_ptr<Student> >& students);



void generateTeacherWiseTimeTable(const vector<Course>& courses)
{
    map <string, vector<Course> > teacherTimeTable;

    for (const auto& course : courses)
    {
        teacherTimeTable[course.teacher->Name].push_back(course);
    }

    for (const auto& entry : teacherTimeTable)
    {
        cout << "\n\nTeacher: " << entry.first << endl;
        displayTimeTable(entry.second);
        cout << endl << endl;
    }
}

void generateSectionWiseTimeTable(const vector<Course>& courses)
{
    map <string, vector<Course> > sectionTimeTable;

    for (const auto& course : courses)
    {
        sectionTimeTable[course.room->code].push_back(course);
    }

    for (const auto& entry : sectionTimeTable)
    {
        cout << "\n\nRoom: " << entry.first << endl;
        displayTimeTable(entry.second);
        cout << endl << endl;
    }
}

void generateRoomWiseTimeTable(const vector<Course>& courses)
{
    map <string, vector<Course> > roomTimeTable;

    for (const auto& course : courses)
    {
        roomTimeTable[course.room->code].push_back(course);
    }

    for (const auto& entry : roomTimeTable)
    {
        cout << "\n\nRoom: " << entry.first << endl;
        displayTimeTable(entry.second);
        cout << endl << endl;
    }
}

void displayTimeTableForTime(const vector<Course>& courses, const string& time, const string& day)
{
    cout << "\n\nCourses at " << time << " on " << day << ": " << endl;

    for (const auto& course : courses)
    {
        if (course.timeslot == time + " " + day) {
            cout << "\n\nCourse: " << course.name << ", Teacher: " << course.teacher->Name << endl;
        }
    }
}

void displayTimeTableForDay(const vector<Course>& courses, const string& day)
{
    cout << "\n\nTime table for " << day << ": " << endl;

    for (const auto& course : courses)
    {
        if (course.timeslot.find(day) != string::npos)
        {
            cout << "\n\nCourse: " << course.name << ", Time: " << course.timeslot << ", Teacher: " << course.teacher->Name << endl;
        }
    }
}

void displayTimeTable(const vector<Course>& timeTable)
{
    for (const auto& course : timeTable)
    {
        cout << "\n\nCourse: " << course.name << ", Time: " << course.timeslot << ", Room: " << course.room->code << endl;
    }
}

void addStudentsToRoom(Room& room, const vector<Student>& students)
{
    for (const auto& student : students)
    {
        room.students.push_back(make_shared<Student>(student)); // Changed to use make_shared
    }
}

void displayStudentsPerRoom(const vector<Room>& rooms)
{
    for (const auto& room : rooms)
    {
        cout << "\n\nStudents in " << room.code << ":" << endl;

        if (!room.students.empty())
        {
            for (const auto& student : room.students)
            {
                cout << "- " << student->Name << " (" << student->studentSection << ")" << endl;
            }
        }
        else
        {
            cout << "\n\nNo students in this room." << endl;
        }
        cout << endl;
    }
}

void removeStudentFromRoom(Room& room, const string& studentName)
{
    auto it = room.students.begin();

    while (it != room.students.end())
    {
        if ((*it)->Name == studentName) // Perform case-sensitive comparison
        {
            it = room.students.erase(it);
            cout << "\n\nStudent " << studentName << " removed from room " << room.code << " successfully.\n";
            return; // Student found and removed, exit the function
        }
        else
        {
            ++it;
        }
    }
    // If the function reaches here, it means the student was not found in the room
    cout << "\n\nStudent " << studentName << " not found in room " << room.code << ".\n";
}
bool isRoomAvailableForMakeupClass(const vector<Course>& courses, const string& roomNumber, const string& time)
{
    for (const auto& course : courses)
    {
        if (course.room->code == roomNumber && course.timeslot == time)
        {
            return false;
        }
    }
    return true;
}
void switchTeacherRoom(vector<Course>& courses, const string& courseCode, const string& newRoomNumber, vector<Room>& rooms)
{
    for (auto& course : courses)
    {
        if (course.code == courseCode)
        {
            course.room = nullptr;
            for (auto& room : rooms)
            {
                if (room.code == newRoomNumber)
                {
                    course.room = &room;
                    break;
                }
            }

            if (course.room == nullptr)
            {
                cout << "\n\nRoom " << newRoomNumber << " not found!" << endl;
            }
            break;
        }
    }
}

void addCourse(vector<Course>& courses, const string& courseCode, const string& courseName, Teacher& teacher, Room& room, const string& timeSlot) {
    // Check if the room is available at the given time slot
    for (const auto& course : courses)
    {
        if (course.room->code == room.code && course.timeslot == timeSlot)
        {
            cout << "\n\nRoom " << room.code << " is not available at the given time slot." << endl;
            return; // Return if the room is not available
        }
    }

    // Create the new course and add it to the list of courses
    Course newCourse;
    newCourse.code = courseCode;
    newCourse.name = courseName;
    newCourse.teacher = &teacher;
    newCourse.room = &room;
    newCourse.timeslot = timeSlot;
    courses.push_back(newCourse);

    cout << "\n\nCourse " << courseName << " added successfully." << endl;
    return; // Return to main menu loop
}
