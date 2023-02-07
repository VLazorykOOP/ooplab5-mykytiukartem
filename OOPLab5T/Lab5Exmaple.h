#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
int mainExample1();
int mainExample2();
int mainExample3();
int mainExample4();
int mainExample5();
using namespace std;
// 
class ObjInner {
	int n;
	static int n_objinner;
public:
	ObjInner() {
		n = ++n_objinner;
		cout << " ObjInner Ctor n= " << n << endl;
	}
	ObjInner(const ObjInner& s) {
		n = ++n_objinner;
		cout << " ObjInner Ctor Copy  n= " << n << endl;
	}
	~ObjInner() {
		cout << " ObjInner Dtor  n = " << n << endl;
	}
};
class ObjInner2 {
public:
	ObjInner2() {
		cout << " ObjInner2 Ctor  +++++++++++++ " << endl;
	}
	ObjInner2(ObjInner2& s) {

		cout << " ObjInner2 Ctor Copy " << endl;
	}
	~ObjInner2() {
		cout << " ObjInner2 Dtor " << endl;
	}
};
class ObjInner3 {
public:
	ObjInner3() {
		cout << " ObjInner3 Ctor " << endl;
	}
	ObjInner3(ObjInner3& s) {

		cout << " ObjInner3 Ctor Copy " << endl;
	}
	~ObjInner3() {
		cout << " ObjInner3 Dtor " << endl;
	}
};
class Base {
	int data_base=0;
	class InnerBase {
		static int n_innerbase;
	public:
		InnerBase() {
			cout << " InnerBase Ctor " << endl;
		}

		~InnerBase() {
			cout << " InnerBase Dtor " << endl;
		}
	};
	InnerBase obj;
	ObjInner obj1, obj2;
	ObjInner2 oobj2, oobj22;
	ObjInner3 oobj3;
	InnerBase obj_2;
	ObjInner obj1_2;

public:
	Base() {
		cout << " Base Ctor " << endl;
	}
	Base(ObjInner& inobj, ObjInner2& inobj2) : oobj2(inobj2), obj2(inobj) {
		cout << " Base Ctor : ObjInner& inobj, ObjInner2& inobj2  " << endl;
	}
	Base(ObjInner3& in3, ObjInner& inobj, ObjInner2& inobj2) : oobj3(in3), oobj2(inobj2), obj2(inobj) {
		cout << " Base Ctor : ObjInner3& in, ObjInner& inobj, ObjInner2& inobj2  " << endl;
	}
	Base(int in) : data_base(in) {
		cout << " Base Ctor " << endl;
	}
	virtual ~Base() {
		cout << " Base Dtor " << endl;
	}
};
class Drv : public Base {    // 1)  public  2) protected
	int data_drv;
	ObjInner obj2;
public:
	Drv() {
		cout << " Drv Ctor " << endl;
	}
	Drv(ObjInner& inobj, ObjInner2& inobj2) : Base(inobj, inobj2) {
		cout << " Drv Ctor : ObjInner& inobj, ObjInner2& inobj2  " << endl;
	}
	~Drv() {
		cout << " Drv Dtor " << endl;
	}
};
class D2 : public Drv {
	int data_drv;
	ObjInner obj2;
public:
	D2() {
		cout << " D2 Ctor " << endl;
	}
	D2(ObjInner& inobj, ObjInner2& inobj2) : Drv(inobj, inobj2) {
		cout << " Drv Ctor : ObjInner& inobj, ObjInner2& inobj2  " << endl;
	}
	~D2() {
		cout << " D2 Dtor " << endl;
	}
};
//
//
///
struct PIB
{
	string fname;
	string name;
	string lname;
	PIB() {
		fname = "NoFirstName";
		name = "NoName";
		lname = "NoLastName";
		cout << "Default constructor PIB \n";
	}
	PIB(string fn) {
		fname = "NoFirstName";
		name = fn;
		lname = "NoLastName";
		cout << "Constructor PIB(string fn) \n";
	}
	PIB(string fn[3]) {
		fname = fn[0];
		name = fn[1];
		lname = fn[2];
		cout << "Constructor PIB(string fn[]) \n";
	}
	PIB(const PIB& s) {
		fname = s.fname;
		name = s.name;
		lname = s.lname;
		cout << "Constructor Copy PIB(const PIB &) \n";
	}
	PIB(PIB&& s) {
		fname = s.fname;
		name = s.name;
		lname = s.lname;
		cout << " Constructor Move PIB(PIB &&) \n";
		s.fname = "NoFirstName";
		s.name = "NoName";
		s.lname = "NoLastName";
	}
	PIB(const char* fn, const char* n, const char* ln) {
		fname = fn;
		name = n;
		lname = ln;
		cout << " Constructor  PIB(const char * ... ) \n";
	}
	~PIB() {
		cout << "Destructor ~PIB() \n";
	}

	PIB& operator=(const PIB& s)
	{
		fname = s.fname;
		name = s.name;
		lname = s.lname;
		cout << " PIB operator=(PIB &) \n";
		return *this;
	}
	string toString() {
		string ts = "PIB: " + fname + "  " + name + "  " + lname + " ";
		return ts;
	}
	bool operator==(PIB& b) {
		return 	name == b.name &&
			fname == b.fname && lname == b.lname ? true : false;

	}
	void Input() {
		cout << "Input fname "; cin >> fname;
		cout << "Input name ";  cin >> name;
		cout << "Input lname "; cin >> lname;
	}
	friend ostream& operator<<(ostream& os, PIB& a);
	friend istream& operator>>(istream& os, PIB& a);
};
//
class Person {
protected:
	int age, weight;
	PIB* name;
public:
	Person() {
		age = 0;
		weight = 0;
		name = nullptr;
		cout << " Default constructor Person \n";
	}
	Person(int a, int w, string n) {
		age = a;
		weight = w;
		name = new PIB;
		name->name = n;
		cout << " Constructor  Person(int a, int w, string n) \n";
	}
	Person(int a, int w, PIB& n) {
		age = a;
		weight = w;
		name = new PIB;
		name->fname = n.fname;
		name->name = n.name;
		name->lname = n.lname;
		cout << " Constructor  Person(int a, int w, PIB &n) \n";
	}
	Person(const Person& n) {
		age = n.age;
		weight = n.weight;
		name = new PIB;
		name->fname = n.name->fname;
		name->name = n.name->name;
		name->lname = n.name->lname;
		cout << " Constructor Copy  Person(const Person& n) \n";
	}
	Person(Person&& n) {
		age = n.age;
		weight = n.weight;
		name = n.name;
		n.name = nullptr;
		n.age = 0;
		n.weight = 0;
		cout << " Constructor Move Person(Person&& n) \n";
	}
	Person& operator=(const Person& s) {
		age = s.age;
		weight = s.weight;
		name = new PIB;
		name->fname = s.name->fname;
		name->name = s.name->name;
		name->lname = s.name->lname;
		cout << " operator=(const Person& s) Copy \n";
		return *this;
	}
	Person& operator=(Person&& s) {
		age = s.age;
		weight = s.weight;
		name = s.name;
		s.name = nullptr;
		s.age = 0;
		s.weight = 0;
		cout << " operator=( Person&& s) Move \n";
		return *this;
	}
	~Person() {
		if (name != nullptr) delete name;
		cout << "Destructor Person\n";
	}

	void setAge(int a) {
		if (a >= 0 && a <= 200)
			age = a;
		else
			cout << "Age " << a << " not allow,  age is " << age << endl;;
	}
	void setWeight(int w) {
		if (w <= 0 || w > 300)
			weight = w;
		else
			cout << "Weight " << w << " not exist,  weight is " << weight << endl;;
	}
	string toString() {
		string r, a, w;
		a = to_string(age);
		w = to_string(weight);
		if (name == nullptr) r = " No set name  age: " + a + " weight: " + w;
		else r = name->toString() + " age: " + a + " weight: " + w;
		return r;
	}
	void Input() {
		if (name == nullptr) name = new PIB;
		name->Input();
		cout << "Input age ";  while (!(cin >> age) || (age < 0 || age > 200)) {
			cin.clear();
			cin.ignore(MAXSHORT, '\n');
			fflush(stdin);
			cout << "bad  input age is 1 to 200 \n";
		};
		cout << "Input weight ";  while (!(cin >> weight) || (weight < 0 || weight > 300)) {
			cin.clear();
			cin.ignore(MAXSHORT, '\n');
			fflush(stdin);
			cout << "bad  input weight is 1 to 300 \n";
		};
	}
	friend ostream& operator<<(ostream& os, Person& a);
	friend istream& operator>>(istream& os, Person& a);
};
//
class Adult : public Person {
	long long ID;
	int numChild;
	string* nameChild;
public:
	Adult() {
		ID = 0;
		nameChild = nullptr;
		cout << " Default constructor Adult \n";
	}
	Adult(int a, int w, PIB& pib, long long i, int kC, string* nameC) :
		Person(a, w, pib) {
		ID = i;
		numChild = kC;
		if (kC > 0) {
			nameChild = new string[kC];
			for (int i = 0; i < numChild; i++)
				nameChild[i] = nameC[i];
		}
		cout << "Adult(int a, int w, PIB & pib, long long i, int kC, string *nameC ) \n";
	}
	Adult(const Adult& s) : Person(s) {
		ID = s.ID;
		numChild = s.numChild;
		if (numChild > 0)
		{
			nameChild = new string[numChild];
			for (int i = 0; i < numChild; i++)
				nameChild[i] = s.nameChild[i];
		}
		cout << " Constructor Copy  Adult(const Adult &s)   \n";
	}
	Adult(Adult&& s) {
		age = s.age;
		weight = s.weight;
		name = s.name;
		s.name = nullptr;
		s.age = 0;
		s.weight = 0;
		ID = s.ID;
		numChild = s.numChild;
		nameChild = s.nameChild;
		s.numChild = 0;
		s.nameChild = nullptr;
		cout << " Constructor Move Adult( Adult &&s)   \n";
	}
	~Adult()
	{
		if (nameChild != nullptr) delete[] nameChild;
		cout << "\tDestructor Adult\n";
	}
	Adult& operator=(const Adult& s) {
		this->Person::operator=(s);
		ID = s.ID;
		numChild = s.numChild;
		if (numChild > 0)
		{
			nameChild = new string[numChild];
			for (int i = 0; i < numChild; i++)
				nameChild[i] = s.nameChild[i];
		}
		cout << "  Adult& operator =(const Adult &s)   \n";
		return *this;
	}
	Adult& operator=(Adult&& s) {
		age = s.age;
		weight = s.weight;
		if (name) delete name;
		name = s.name;
		s.name = nullptr;
		s.age = 0;
		s.weight = 0;
		ID = s.ID;
		numChild = s.numChild;
		if (nameChild) delete[] nameChild;
		nameChild = s.nameChild;
		s.numChild = 0;
		s.nameChild = nullptr;
		cout << "  Adult& operator =(Adult &&s)   \n";
		return *this;
	}

	void setID(long long i) {
		if (i > 0) 	ID = i;
		else ID = 0;
	}
	string toString()
	{
		string sID;
		sID = to_string(ID);
		string s = Person::toString() + " ID: " + sID;
		string nd = " nd = " + to_string(numChild) + " : ";
		if (numChild > 0) {
			for (int i = 0; i < numChild; i++)
				nd += nameChild[i] + "  ";
			s += nd;
		}
		return s;
	}
	void Input() {
		Person::Input();
		cout << "Input ID ";
		while (!(cin >> ID) || ID < 0) {
			cin.clear();
			cin.ignore(MAXSHORT, '\n');
			fflush(stdin);
			cout << "bad  input ID  \n";
		};
		cout << "Input num Child ";
		while (!(cin >> numChild) || numChild < 0) {
			cin.clear();
			cin.ignore(MAXSHORT, '\n');
			fflush(stdin);
			cout << "bad  input numChild  \n";
		};
		if (numChild > 0)
		{
			if (nameChild != nullptr) delete[] nameChild;
			nameChild = new string[numChild];
			for (int i = 0; i < numChild; i++)
			{
				cout << "Input Name Child ";
				cin >> nameChild[i];
			}
		}
	}
	void Output() {
		cout << toString() << endl;
	}
	Adult operator+(int i)
	{
		Adult t(*this);
		t.age += i;
		return t;
	}
	friend ostream& operator<<(ostream& os, Adult& a);
	friend istream& operator>>(istream& os, Adult& a);

};
