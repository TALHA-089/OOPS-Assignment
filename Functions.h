#ifndef Functions_h
#define Functions_h

#pragma once
#include "Classes.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

extern vector<Student> students;
extern vector<Teacher> teachers;
extern vector<Room> rooms;
extern vector<Course> courses;

// Function declarations
void generateTeacherWiseTimeTable(const vector<Course>& courses);
void generateSectionWiseTimeTable(const vector<Course>& courses);
void generateRoomWiseTimeTable(const vector<Course>& courses);
void viewDailyTimetable(const vector<Course>& courses);
void queryStudentTimetable(const vector<Course>& courses);
void generateStudentWiseTimeTable(const vector<Course>& courses);

void generateTeacherWiseTimeTable(const vector<Course>& courses)
{
    map<string, vector<Course> > teacherTimeTable;

    for (const auto& course : courses)
    {
        teacherTimeTable[course.teacher->Name].push_back(course);
    }

    for (const auto& entry : teacherTimeTable)
    {
        cout << "\nTeacher: " << entry.first << endl;
        for (const auto& course : entry.second)
        {
            cout <<"\nRoom: " << course.room->code <<", Time: " << course.timeslot << ", Day: " << course.Day << endl;
        }
    }
}

void generateRoomWiseTimeTable(const vector<Course>& courses)
{
    map<string, vector<Course> > roomTimeTable;

    for (const auto& course : courses)
    {
        roomTimeTable[course.room->code].push_back(course);
    }

    for (const auto& entry : roomTimeTable)
    {
        cout << "\nRoom: " << entry.first << endl;
        for (const auto& course : entry.second)
        {
            cout << "Course: " << course.code << " - " << course.name << ", Teacher: " << course.teacher->Name <<", Time: " << course.timeslot << ", Day: " << course.Day << " " << course.section << endl;
        }
    }
}

void generateSectionWiseTimeTable(const vector<Course>& courses)
{
    map<string, vector<Course> >  sectionTimeTable;

    for (const auto& course : courses)
    {
        sectionTimeTable[course.section].push_back(course);
    }

    for (const auto& entry : sectionTimeTable)
    {
        cout << "\n" << entry.first << endl;
        for (const auto& course : entry.second)
        {
            cout << "Course: " << course.code << " - " << course.name << ", Teacher: " << course.teacher->Name <<", Time: " << course.timeslot << ", Day: " << course.Day << endl;

        }
    
    }
}

void viewDailyTimetable(const vector<Course>& courses)
{
    string day;
    cout << "\nEnter day (e.g., Monday, Tuesday, etc.): ";
    getline(cin, day);

    cout << "\nTimetable for " << day << ":" << endl;

    for (const auto& course : courses)
    {
        if (course.Day == day)
        {
            cout << "Course: " << course.code << " - " << course.name << ", Time: " << course.timeslot << ", Room: " << course.room->code << ", Teacher: " << course.teacher->Name << ", " << course.section << endl;
        }
    }
}

void query1(const vector <Course>& courses)
{
    string Day, f_time, t_time;
    cout<<"\n\nEnter the Day: ";
    getline(cin,Day);
    cout<<"\n\nEnter Start Timeslot: ";
    cin >> f_time >> t_time;
    string timeSlot;
    timeSlot = f_time + "->" + t_time;
    
    for(const auto &it : courses)
    {
        if(it.Day == Day)
        {
            if(it.timeslot == timeSlot)
            {
                cout << "\n" << it.teacher->Name <<" is the one taking the Class on " << Day << " at " << timeSlot << endl;
                break;
            }
        }
    }
}

void generateStudentWiseTimeTable(const vector<Course>& courses)
{
    string Section_choice;
    string Section;
    map <string, vector<Course> >StudentTimeTable;
    
    for(const auto &course : courses)
    {
        StudentTimeTable[course.section].push_back(course);
    }
    
    cout<<"\n\nChoose the Section of the Student A or B: ";
    cin>>Section_choice;
    cin.ignore();
    Section = "Section-" + Section_choice;
    
    for(const auto &it : StudentTimeTable)
    {
        if(Section == it.first)
        {
            cout << it.first << ": " << endl;
            for(const auto& course : it.second)
            {
                cout << "Course: " << course.code << " - " << course.name << ", Teacher: " << course.teacher->Name <<", Time: " << course.timeslot << ", Day: " << course.Day << endl;

            }
        }
        
    }
    
}

#endif
