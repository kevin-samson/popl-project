#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
using namespace std;

class Employee
{
public:
    string employee_name;
    double pay;
    string employee_id;
    Employee(string employee_id, string employee_name, double pay)
    {
        this->employee_id = employee_id;
        this->employee_name = employee_name;
        this->pay = pay;
    }
};

class Student
{
public:
    string student_name;
    double tuition_fees_paid;
    string c1;
    string c2;
    string c3;
    string student_id;
    Student(string student_id, string student_name, double tuition_fees_paid, string c1, string c2, string c3)
    {
        this->student_id = student_id;
        this->student_name = student_name;
        this->tuition_fees_paid = tuition_fees_paid;
        this->c1 = c1;
        this->c2 = c2;
        this->c3 = c3;
    }
};

class TeachingAssistant : public Student
{

public:
    string course_teaching;
    TeachingAssistant(string student_id, string student_name, double tuition_fees_paid, string c1, string c2, string c3, string course_teaching) : Student(student_id, student_name, tuition_fees_paid, c1, c2, c3)
    {
        this->course_teaching = course_teaching;
    }
};

class Instructor : public Employee
{

public:
    string course_teaching;
    Instructor(string employee_id, string employee_name, double pay, string course_teaching) : Employee(employee_id, employee_name, pay)
    {
        this->course_teaching = course_teaching;
    }
};

class School
{
    vector<Student> students;
    vector<Instructor> instructors;
    vector<TeachingAssistant> teaching_assistants;
    vector<Employee> employees;

public:
    void add_student(string student_id, string student_name, double tuition_fees_paid, string c1, string c2, string c3)
    {
        Student student(student_id, student_name, tuition_fees_paid, c1, c2, c3);
        students.push_back(student);
    }

    void add_instructor(string employee_id, string employee_name, double pay, string course_teaching)
    {
        Instructor instructor(employee_id, employee_name, pay, course_teaching);
        instructors.push_back(instructor);
    }

    void add_employee(string employee_id, string employee_name, double pay)
    {
        Employee employee(employee_id, employee_name, pay);
        employees.push_back(employee);
    }

    void add_teaching_assistant(string student_id, string student_name, double tuition_fees_paid, string c1, string c2, string c3, string course_teaching)
    {
        TeachingAssistant teaching_assistant(student_id, student_name, tuition_fees_paid, c1, c2, c3, course_teaching);
        teaching_assistants.push_back(teaching_assistant);
    }

    void read_students(string filename)
    {
        ifstream file(filename);
        string student_id;
        string student_name;
        double tuition_fees_paid;
        string c1;
        string c2;
        string c3;
        while (file >> student_id >> student_name >> tuition_fees_paid >> c1 >> c2 >> c3)
        {
            add_student(student_id, student_name, tuition_fees_paid, c1, c2, c3);
        }
        file.close();
    }

    void read_employees(string filename)
    {
        ifstream file(filename);
        string employee_id;
        string employee_name;
        double pay;
        while (file >> employee_id >> employee_name >> pay)
        {
            add_employee(employee_id, employee_name, pay);
        }
        file.close();
    }

    void read_instructor(string filename)
    {
        ifstream file(filename);
        string inst_id;
        string course_teaching;
        while (file >> inst_id >> course_teaching)
        {
            // check if the id is a student or employee
            if (inst_id.at(0) == 'S')
            {
                for (int i = 0; i < students.size(); i++)
                {
                    if (students[i].student_id == inst_id)
                    {
                        add_teaching_assistant(students[i].student_id, students[i].student_name, students[i].tuition_fees_paid, students[i].c1, students[i].c2, students[i].c3, course_teaching);
                        break;
                    }
                }
            }
            else if (inst_id.at(0) == 'E')
            {
                for (int i = 0; i < employees.size(); i++)
                {
                    if (employees[i].employee_id == inst_id)
                    {
                        add_instructor(employees[i].employee_id, employees[i].employee_name, employees[i].pay, course_teaching);
                        break;
                    }
                }
            }
            else
            {
                cout << "Invalid id" << endl;
            }
        }
        file.close();
    }

    void list_employee_id_and_pay()
    {
        for (int i = 0; i < employees.size(); i++)
        {
            if (employees[i].employee_id.at(0) == 'E')
            {
                cout << employees[i].employee_id << " " << employees[i].pay << endl;
            }
        }
    }

    void list_teaching_assistant()
    {
        for (int i = 0; i < teaching_assistants.size(); i++)
        {
            cout << teaching_assistants[i].student_id << " " << teaching_assistants[i].student_name << " " << teaching_assistants[i].course_teaching << endl;
        }
    }

    void list_not_teaching_assistant()
    {
        // list all students who are not teaching assistants
        for (int i = 0; i < students.size(); i++)
        {
            bool is_ta = false;
            for (int j = 0; j < teaching_assistants.size(); j++)
            {
                if (students[i].student_id == teaching_assistants[j].student_id)
                {
                    is_ta = true;
                    break;
                }
            }
            if (!is_ta)
            {
                cout << students[i].student_id << " " << students[i].student_name << endl;
            }
        }
    }

    void list_students()
    {
        for (int i = 0; i < students.size(); i++)
        {
            // print all the details of the student
            cout << students[i].student_id << " " << students[i].student_name << " " << students[i].tuition_fees_paid << " " << students[i].c1 << " " << students[i].c2 << " " << students[i].c3 << endl;
        }
    }

    void write_to_file(string filename)
    {
        ofstream file(filename);
        // list of employees and their pay
        file << "List of employee id and the pay" << endl;
        for (int i = 0; i < employees.size(); i++)
        {
            if (employees[i].employee_id.at(0) == 'E')
            {
                file << employees[i].employee_id << " " << employees[i].pay << endl;
            }
        }

        // add few lines
        file << endl;
        file << endl;
        // list of teaching assistants
        file << "List of teaching assistants" << endl;
        for (int i = 0; i < teaching_assistants.size(); i++)
        {
            file << teaching_assistants[i].student_id << " " << teaching_assistants[i].student_name << " " << teaching_assistants[i].course_teaching << endl;
        }

        // add few lines
        file << endl;
        file << endl;
        // list of students who are not teaching assistants
        file << "List of students who are not teaching assistants" << endl;
        for (int i = 0; i < students.size(); i++)
        {
            bool is_ta = false;
            for (int j = 0; j < teaching_assistants.size(); j++)
            {
                if (students[i].student_id == teaching_assistants[j].student_id)
                {
                    is_ta = true;
                    break;
                }
            }
            if (!is_ta)
            {
                file << students[i].student_id << " " << students[i].student_name << endl;
            }
        }

        // add few lines
        file << endl;
        file << endl;

        // list of all students
        file << "List of all students " << endl;
        for (int i = 0; i < students.size(); i++)
        {
            file << students[i].student_id << " " << students[i].student_name << " " << students[i].tuition_fees_paid << " " << students[i].c1 << " " << students[i].c2 << " " << students[i].c3 << endl;
        }
    }
};

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "Usage: " << argv[0] << " <student_file> <employee_file> <instructor_file>" << endl;
        return 1;
    }

    School school;
    school.read_students(argv[1]);
    school.read_employees(argv[2]);
    school.read_instructor(argv[3]);
    cout << "List of employee id and the pay" << endl;
    school.list_employee_id_and_pay();
    cout << endl;
    cout << "List of teaching assistants" << endl;
    school.list_teaching_assistant();
    cout << endl;
    cout << "List of students who are not teaching assistants" << endl;
    school.list_not_teaching_assistant();
    cout << endl;
    cout << "List of all students " << endl;
    school.list_students();
    school.write_to_file("output.txt");
    return 0;
}