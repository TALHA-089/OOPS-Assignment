#ifndef Classes_h
#define Classes_h

#pragma once
#include<iostream>
#include<string>
#include<list>
#include<memory>

using namespace std;


class Person;
class Thing;
class Student;
class Teacher;
class Course;
class Room;


class Person
{
    public:

    string Name;
    int ID;
};

class Thing
{
    public:

    string name;
    string code;
};

class Student : public Person
{
    public:

    string studentSection;

};

class Teacher : public Person
{
    public:

    string specialization;
};

class Room : public Thing
{
    public:

    int capacity;
    list<std::shared_ptr<Student> > students;  //Smart Pointers(Allows Multiple Pointers to point at the Same object)
};

class Course : public Thing
{
    public:

    Teacher* teacher;
    string timeslot;
    string Day;
    string section;
    Room* room;
};


#endif
