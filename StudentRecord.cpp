#include <iostream>
#include <string>
//ios_base::sync_with_stdio(false);
using namespace std;

class student{
	private:
		string rollno,name,add,email,phone;
		double cgpa;
		int semester;
	public:
		student();
		void insert();
		void display();
		string getKey();
};

/********************Constructor*******************/
student::student()
{
	rollno = name = add = email = phone = "";
	cgpa =0.0;
	semester =0;
}
/********************Accessors*********************/
void student::insert()
{
	cout << "Input Regestration Number:\n";
	cin >> rollno;
	cout << "Input Student Name:\n";
	cin >> name;
	cout << "Input Current Semester:\n";
	cin >> semester;
	cout << "Input Address:\n";
	cin >> add;
	cout << "Input email-id:\n";
	cin >> email;
	cout << "Input Phone:\n";
	cin >> phone;
	cout << "Input CGPA (out of 10 in decimals):\n";
	cin >> cgpa;
}
void student::display()
{
	cout << "\nStudent Regestration Number:\t" << rollno;
	cout << "\nStudent Name :\t" << name;
	cout << "\nStudent Address :\t" << add;
	cout << "\nStudent email-id:\t" << email;
	cout << "\nStudent Phone Number:\t" << phone;
	cout << "\nStudent Semester:\t" << semester;
	cout << "\nStudent CGPA :\t" << cgpa;
}

string student::getKey()
{
	return rollno;
}