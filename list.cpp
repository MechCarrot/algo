#include <iostream>
#include <list>
#include <cmath>
using namespace std;

 
class Doctor {
public:
	Doctor()
	{
		firstName = "NULL";
		lastName = "NULL";
		specialty = "NULL";
		position = "NULL";
		experience = 0;
		rating = 0.0;
	}
	Doctor(string firstName_, string lastName_, string specialty_, string position_, int experience_, double rating_)
	{
		firstName = firstName_;
		lastName = lastName_;
		specialty = specialty_;
		position = position_;
		experience = experience_;
		rating = rating_;
	}
	void print() const {
		cout << "Name: " << firstName << "\n";
		cout << "Surname: " << lastName << "\n";
		cout << "Specialty: " << specialty << "\n";
		cout << "Position: " << position << "\n";
		cout << "Experience: " << experience << "\n";
		cout << "Rating: " << rating << "\n";
	}
 
	double getRating() const {
		return rating;
	}
 
	int getExp() const {
		return experience;
	}
	string getLastName() const {
		return lastName;
	}
	string getFirstName() const {
		return firstName;
	}
 
	bool operator==(const Doctor& other) const {
		return (firstName == other.firstName &&
			lastName == other.lastName &&
			specialty == other.specialty &&
			position == other.position &&
			experience == other.experience &&
			rating == other.rating);
	}
	bool operator!=(const Doctor& other) const {
		return (firstName != other.firstName &&
			lastName != other.lastName &&
			specialty != other.specialty &&
			position != other.position &&
			experience != other.experience &&
			rating != other.rating);
	}
 
	bool operator<(const Doctor& other) const {
		if (getRating() != other.getRating()) {
			return getRating() < other.getRating();
		}
		if (getExp() != other.getExp()) {
			return getExp() < other.getExp();
		}
		if (getLastName() != other.getLastName()) {
			return getLastName() < other.getLastName();
		}
		return getFirstName() < other.getFirstName();
	}
	bool operator>(const Doctor& other) const {
		if (getRating() != other.getRating()) {
			return getRating() > other.getRating();
		}
		if (getExp() != other.getExp()) {
			return getExp() > other.getExp();
		}
		if (getLastName() != other.getLastName()) {
			return getLastName() > other.getLastName();
		}
		return getFirstName() > other.getFirstName();
	}
	friend ostream& operator << (ostream& os, const Doctor& d);
private:
	string firstName, lastName, position, specialty;
	int experience;
	double rating;
};


ostream& operator << (ostream& os, const Doctor& d) {
	return os << "Name: " << d.firstName << "\n" << "Surname: " << d.lastName << "\n" << "Specialty: " << d.specialty << "\n" << "Position: " << d.position << "\n" << "Experience: " << d.experience << "\n" << "Rating: " << d.rating << "\n";
}

class Point2D {
public:
	double x, y;

	Point2D() {
		x = 0;
		y = 0;
	}
	Point2D(double x_, double y_) {
		x = x_;
		y = y_;
	}
	void setX(double x_) {
		x = x_;
	}
	void setY(double y_) {
		y = y_;
	}
	double getX() {
		return x;
	}
	double getY() {
		return y;
	}

    bool operator<(const Point2D& other) const {
		if (sqrt(x*x + y*y) < sqrt(other.x * other.x + other.y * other.y))
            return true;
        return false;
	}
	bool operator>(const Point2D& other) const {
		if (sqrt(x*x + y*y) > sqrt(other.x * other.x + other.y * other.y))
            return true;
        return false;
	}
    bool operator==(const Point2D& other) const {
		if (x == other.x && y == other.y)
            return true;
        return false;
	}
    friend ostream& operator <<(ostream& os, const Point2D& p);
	~Point2D() {};
};

ostream& operator <<(ostream& os, const Point2D& p) {
    return os << "X: " << p.x << "; " << "Y: " << p.y << "\n";
}

template <class T>
void insert(list <T> &lst, T element) {
    auto p = lst.begin();
    while(p != lst.end()){
        if(*p > element)
            break;
        p++;
    }
    lst.insert(p, element);
}

template <class T>
void push(list <T>& lst, T element) {
    auto p = lst.begin();
    if(lst.empty() || element == *p) {
        lst.push_front(element);
        return;
    }
    while (p != lst.end()) {
        if(*p > element){
            lst.insert(p, element);
            return;
        }
        p++;
    }
    lst.push_back(element);
}

template <class T>
T pop(list <T>& lst) {
    auto p = lst.begin();
    T ans = *p;
    lst.erase(p);
    return ans;
}

bool checkPoint2D(Point2D p) {
    if(p.getX() < 0 && p.getY() > 0)
        return true;
    return false;
}

template <class T>
list <T> filter(const list<T> lst, bool (*predicate)(T)) {
    list <T> ans;
    auto p = lst.begin();
    while(p != lst.end()){
        if(predicate(*p))
            ans.push_back(*p);
        p++;
    }
    return ans;
}

template <class T>
ostream& operator <<(ostream& s, list<T>& lst) {
    for(auto it = lst.begin(); it != lst.end(); it++){
        cout << *it << " ";
    }
    return s;
}

signed main() {
    list <Point2D> lstP;
    Point2D p1(5,6);
    Point2D p2(-1, 8);
    Point2D p3(-4.5, 6.8);
    Point2D p4(1, 1);
    Point2D p5(9, 3);
    push(lstP, p1);
    push(lstP, p2);
    push(lstP, p3);
    push(lstP, p4);
    push(lstP, p5);
    cout << lstP << "\n";
    list <Point2D> lstFiltered = filter(lstP, checkPoint2D);
    cout << lstFiltered << "\n";
    
    list <Doctor> lst;
    Doctor dA("nikita", "d", "surgeon", "middle", 3, 70);
	Doctor dB("nikita", "zalivin", "dentist", "senior", 5, 86);
    Doctor dC("petr", "aba", "neurosurgeon", "lead", 10, 100);
    Doctor dD("ivan", "ivanov", "therapist", "junior", 1, 60);
    push(lst, dA);
    push(lst, dB);
    push(lst, dC);
    push(lst, dD);
    cout << lst << "\n";

    cout << "Pop functions: \n";
    for (int i = 0; i < 4; i++) {
        cout << pop(lst) << "\n";
    }
    cout << "\n";

    Doctor dE("firstname", "secondname", "doctor", "intern", 0, 45);
    push(lst, dE);
    cout << lst << "\n"; //only dE

    cout << "Hello world!" << "\n";
    return 0;
}