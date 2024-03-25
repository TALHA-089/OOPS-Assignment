#pragma once
#include<iostream>
#include<string>
#include<list>

using namespace std;


class Person;
class Thing;
class Student;
class Teacher;
class Course;
class Room;
class User;

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
    Room* room;
};

class User 
{
    private:
    string username;
    string password;

    public:

    User(string Username, string Password)
    {
        username = Username;
        password = Password;
    }

    bool authenticate(string Username, string Password) 
    {
        return (username == Username && password == Password);
    }

    string getUsername()
    {
        return username;
    }
};

class SYSTEM 
{
    private:

    User* currentUser; //Pointer to the Current User

    public:
    SYSTEM()
    {
        currentUser = nullptr;
    }

    void setUser() 
    {
        string username, password;
        cout << "\n\nEnter username: ";
        cin >> username;
        cout << "\n\nEnter password: ";
        cin >> password;
        currentUser = new User(username, password);
        cout << "\n\nAccount created successfully!\n";
    }

    bool login()
    {
        string username, password;
        cout << "\n\nEnter username: ";
        cin >> username;
        cout << "\n\nEnter password: ";
        cin >> password;

        if (currentUser != nullptr) 
        {
            if (currentUser->authenticate(username, password)) 
            {
                cout << "\n\nLogin successful. Welcome, " << currentUser->getUsername() << "!\n";
                return true;
            }
            else
            {
                cout << "\n\nLogin unsuccessful. Please try again.\n";
                return false;
            }
        }
    }
    
    ~SYSTEM() 
    {
        delete currentUser; //Current user was dynamically allocated using the keyword 'new'
    }
};
