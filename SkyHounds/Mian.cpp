/* my second program in C++
with more comments */
//
#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

void readFile (){
	ifstream in;
	in.open("test.txt");

	string line;
	while(!in.fail()){
		getline(in, line);
		cout << line << endl;
	}

	in.close();
}

void printMsg()
{
	cout << "A void Function..aka a procedure \n";
}

void cinExample()
{
	int i;
	cout << "Please enter an integer value: ";
	cin >> i;
	cout << "The value you entered is " << i;
	cout << " and its double is " << i*2 << ".\n";
}

int subtraction (int a, int b)
{
	int r;
	r=a-b;
	return (r);
}

void stringStreamExample ()
{
	string mystr;
	float price=0;
	int quantity=0;
	cout << "Enter price: ";
	getline (cin,mystr);
	stringstream(mystr) >> price;
	cout << "Enter quantity: ";
	getline (cin,mystr);
	stringstream(mystr) >> quantity;
	cout << "Total price: " << price*quantity <<
	endl;
}


int main ()
{
	printMsg();
	readFile();

	int x=5, y=3, z;
	z = subtraction (7,2);
	cout << "The first result is " << z << '\n';
	cout << "The second result is " << subtraction (7,2) << '\n';
	cout << "The third result is " << subtraction (x,y) << '\n';
	z= 4 + subtraction (x,y);
	cout << "The fourth result is " << z << '\n';
	// Sleep(1000);

	int n = 0;
	while ( n>-10) {
		cout << n << ", ";
		--n;
	}

	//cinExample();
	stringStreamExample ();
	int ll;
	cin >> ll;
	//std::cin.ignore();
	return 0;
}