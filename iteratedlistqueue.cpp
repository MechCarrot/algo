#include <iostream>
#include <fstream>

using namespace std;



class Exception : public exception
{
protected:
	char* str;
public:
	Exception(const char* s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception()
	{
		delete[] str;
	}

	virtual void print()
	{
		cout << "Exception: " << str << "; " << what();
	}
};

class IteratorNullException : public Exception
{
public:
	IteratorNullException(const char* s) : Exception(s) {}
	IteratorNullException(const IteratorNullException& c) : Exception(c) {}

	virtual void print()
	{
		cout << str;
	}
};


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
	double getX(double x_) {
		return x_;
	}
	double getY(double y_) {
		return y_;
	}

	bool operator==(const Point2D& other) const {
		return ((x == other.x) && (y == other.y));
	}

	bool operator<(const Point2D& other) const {
		return sqrt(x * x + y * y) < sqrt(other.x * other.x + other.y * other.y);
	}
	bool operator>(const Point2D&other) const {
		return sqrt(x * x + y * y) > sqrt(other.x * other.x + other.y * other.y);
	}

	friend ostream& operator << (ostream& os, const Point2D& p);
	~Point2D() {};
};

ostream& operator << (ostream& os, const Point2D& p) {
	return os << "x: " << p.x << " ; y: " << p.y << "\n";
}


template <class T>
class IteratedLinkedList;

template <class T>
class Queue;

template <class T>
class OrderedQueue;

template <class T>
class ListIterator;

template <class T>
class Element
{
	//элемент связного списка
private:
	//указатель на предыдущий и следующий элемент
	Element* next;
	Element* prev;

	//информация, хранимая в поле
	T field;
public:
	Element(T value = 0, Element<T>* next_ptr = NULL, Element<T>* prev_ptr = NULL)
	{
		field = value; next = next_ptr; prev = prev_ptr;
	}
	//доступ к полю *next
	virtual Element* getNext() { return next; }
	virtual void setNext(Element* value) { next = value; }

	//доступ к полю *prev
	virtual Element* getPrevious() { return prev; }
	virtual void setPrevious(Element* value) { prev = value; }

	//доступ к полю с хранимой информацией field
	virtual T getValue() { return field; }
	virtual void setValue(T value) { field = value; }

	template<class T> friend ostream& operator<< (ostream& ustream, Element<T>& obj);

};

template<class T>
ostream& operator << (ostream& ustream, Element<T>& obj)
{
	ustream << obj.field;
	return ustream;
}

template <class T>
class LinkedListParent
{
protected:
	//достаточно хранить начало и конец
	Element<T>* head;
	Element<T>* tail;
	//для удобства храним количество элементов
	int num;
public:
	virtual int Number() { return num; }

	virtual Element<T>* getBegin() { return head; }

	virtual Element<T>* getEnd() { return tail; }

	LinkedListParent()
	{
		//конструктор без параметров
		cout << "\nParent constructor";
		head = NULL; tail = NULL;
		num = 0;
	}

	ListIterator<T> begin() {
		ListIterator<T> it = head;
		return head;
	}

	ListIterator<T> end() {
		ListIterator<T> it = tail;
		return tail;
	}

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
	virtual Element<T>* push(T value) = 0;

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
	virtual Element<T>* pop() = 0;

	virtual ~LinkedListParent()
	{
		Element<T>* current = head;
		while (current != NULL) {
			Element<T>* next = current->getNext();
			delete current;
			current = next;
		}
		head = tail = NULL;
		cout << "\nParent destructor";
	}

	//получение элемента по индексу - какова асимптотическая оценка этого действия?
	virtual Element<T>* operator[](int i)
	{
		//индексация
		if (i<0 || i>num) return NULL;

		//ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
		Element<T>* cur = head;
		for (int k = 0; k < i; k++)
		{
			cur = cur->getNext();
		}
		return cur;
	}

	template<class T> friend ostream& operator<< (ostream& ustream, LinkedListParent<T>& obj);
	template<class T> friend istream& operator>> (istream& ustream, LinkedListParent<T>& obj);
};

template<class T>
ostream& operator << (ostream& ustream, LinkedListParent<T>& obj)
{
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.num << "\n";
		for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext())
			ustream << current->getValue() << " ";
		return ustream;
	}

	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
		ustream << "arr[" << i << "] = " << current->getValue() << "\n";

	return ustream;
}

template<class T>
istream& operator >> (istream& ustream, LinkedListParent<T>& obj)
{
	//чтение из файла и консоли совпадают
	int len;
	ustream >> len;
	//здесь надо очистить память под obj, установить obj.num = 0
	double v = 0;
	for (int i = 0; i < len; i++)
	{
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}

//дописать класс итератора по списку
template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
public:

	friend class IteratedLinkedList<ValueType>;
	friend class Queue<ValueType>;
	friend class OrderedQueue<ValueType>;

	//конструкторы
	ListIterator() { ptr = NULL; }
	ListIterator(Element<ValueType>* p) { ptr = p; }
	ListIterator(const ListIterator& it) { ptr = it.ptr; }

	//методы работы с итераторами
	//присваивание
	ListIterator& operator=(const ListIterator& it) { ptr = it.ptr; return *this; }
	ListIterator& operator=(Element<ValueType>* p) { ptr = p; return *this; }

	//проверка итераторов на равенство
	bool operator!=(ListIterator const& other) const { return ptr != other.ptr; }
	bool operator==(ListIterator const& other) const { return ptr == other.ptr; }
	//получить значение
	Element<ValueType>& operator*()
	{
		if (ptr == NULL)
			throw IteratorNullException("Iterator is pointing to NULL");
		return *ptr;
	}

	//перемещение с помощью итераторов
	ListIterator& operator++()
	{
		if (ptr->getNext() == NULL)
			throw IteratorNullException("Iterator is pointing to NULL");
		ptr = ptr->getNext();
		return *this;
	}
	ListIterator& operator--()
	{
		if (ptr->getPrevious() == NULL)
			throw IteratorNullException("Iterator is pointing to NULL");
		ptr = ptr->getPrevious();
		return *this;
	}
	ListIterator& operator++(int v)
	{
		if (ptr->getNext() == NULL)
			throw IteratorNullException("Iterator is pointing to NULL");
		ptr = ptr->getNext();
		return *this;
	}
	ListIterator& operator--(int v)
	{
		if (ptr->getPrevious() == NULL)
			throw IteratorNullException("Iterator is pointing to NULL");
		ptr = ptr->getPrevious();
		return *this;
	}

private:
	//текущий элемент
	Element<ValueType>* ptr;
};

//класс итерируемый список - наследник связного списка, родитель для Очереди и Стека
template <class T>
class IteratedLinkedList : public LinkedListParent<T>
{
public:
	using LinkedListParent<T>::head;
	using LinkedListParent<T>::tail;
	using LinkedListParent<T>::num;

	IteratedLinkedList() : LinkedListParent<T>() { cout << "\nIteratedLinkedList constructor"; }
	virtual ~IteratedLinkedList() {
		Element<T>* current = head;
		while (current != NULL) {
			Element<T>* next = current->getNext();
			delete current;
			current = next;
		}
		head = tail = NULL;
		cout << "\nIteratedLinkedList destructor";
	}


	ListIterator<T> begin() { ListIterator<T> it = LinkedListParent<T>::head; return it; }
	ListIterator<T> end() { ListIterator<T> it = LinkedListParent<T>::tail; return it; }
};

template <class T>
class Queue : public IteratedLinkedList<T>
{
public:
	using LinkedListParent<T>::head;
	using LinkedListParent<T>::tail;
	using LinkedListParent<T>::num;

	Queue() : IteratedLinkedList<T>() { cout << "\nQueue constructor!\n"; }
	ListIterator<T> begin()
	{
		ListIterator<T> it(head);
		return it;
	}
	ListIterator<T> end()
	{
		ListIterator<T> it(tail);
		return it;
	}

	virtual Element<T>* push(T value)
	{
		if (head == NULL) {
			head = tail = new Element<T>(value);
			return head;
		}

		Element <T>* tmp = new Element<T>(value);
		tmp->setPrevious(tail);
		tmp->getPrevious()->setNext(tmp);
		tail = tmp;
		return tail;
	}

	Element<T>* pop() {
		if (head == NULL) {
			return NULL;
		}

		Element<T>* ans = head;
		if (head == tail)
		{
			head = tail = NULL;
			num = 0;
			return ans;
		}

		Element<T>* tmp = head;
		tmp = tmp->getNext();
		tmp->getPrevious()->setNext(NULL);
		tmp->setPrevious(NULL);
		head = tmp;
		num--;
		return ans;
	}

	Queue<T>& filter(bool (*predicate)(T))
	{
		Queue<T> ans;
		for (Element<T>* current = head; current != tail; current = current->getNext())
			if (predicate(current->getValue()))
				ans.push(current->getValue());

		return &ans;
	}

	~Queue() {
		Element<T>* el = head;
		while (el != NULL) {
			Element<T>* tmp = el->getNext();
			delete el;
			el = tmp;
		}
		head = tail = NULL;
		cout << "\nQueue's destructor is finished\n";
	}

	template <class T1>
	friend ostream& operator << (ostream& s, Queue<T1>& q);
};

template <class T1>
ostream& operator << (ostream& s, Queue<T1>& q)
{
	auto it = q.begin();
	while (it != q.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << *it << " ";
	return s;
}

template <class T>
class OrderedQueue : public Queue<T> {
public:

	using LinkedListParent<T>::head;
	using LinkedListParent<T>::tail;
	using LinkedListParent<T>::num;

	OrderedQueue() : Queue<T>() { cout << "\nOrdered queue constructor!\n"; }
	~OrderedQueue() { cout << "\n OrderedQueue destructor\n"; }

	ListIterator<T> begin()
	{
		ListIterator<T> it(head);
		return it;
	}
	ListIterator<T> end()
	{
		ListIterator<T> it(tail);
		return it;
	}

	void insert(T value)
	{
		num++;
		ListIterator<T> it = end();

		if (head == NULL)
		{
			Queue<T>::push(value);
			return;
		}

		if (value < it.ptr->getValue() || value == it.ptr->getValue())
		{
			Queue<T>::push(value);
			return;
		}
		it = begin();
		Element<T>* el = new Element<T>(value);
		if (value > it.ptr->getValue() || value == it.ptr->getValue())
		{
			el->setNext(head);
			el->getNext()->setPrevious(el);
			head = el;
			return;
		}

		while (value < it.ptr->getValue())
			it++;
		el->setNext(it.ptr);
		el->setPrevious(it.ptr->getPrevious());
		it.ptr->getPrevious()->setNext(el);
		it.ptr->setPrevious(el);
		return;
	}

	template <class T1>
	friend ostream& operator << (ostream& s, OrderedQueue<T1>& q);

	template <class T2>
	friend OrderedQueue<T> filter(LinkedListParent<T2>* q, bool (*predicate)(T2));

};

template<class T1>
ostream& operator << (ostream& s, OrderedQueue<T1>& q)
{
	ListIterator<T1> it = q.begin();
	while (it != q.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << *it << " ";
	return s;
}

template <class T2>
OrderedQueue<T2> filter(LinkedListParent<T2>* q, bool (*predicate)(T2))
{
	OrderedQueue<T2> res;
	for (ListIterator<T2> it = (*q).begin(); it != (*q).end(); it++)
	{
		if (predicate((*it).getValue()))
			res.insert((*it).getValue());
	}
	return res;
}

bool firstOctane(Point2D p) {
	if (p.x < 0 && p.y > 0)
		return true;
	return false;
}

int main()
{
	Queue<int> q;
	q.push(1);
	q.push(3);
	q.push(2);
	q.push(15);
	q.push(1231);
	cout << q << "\n";
	cout << *q.pop() << "\n";
	cout << q << "\n";
	q.push(56);
	cout << q << "\n";
	
	OrderedQueue<Doctor> s;
	Doctor dA("nikita", "d", "surgeon", "middle", 3, 70);
	Doctor dB("nikita", "zalivin", "dentist", "senior", 5, 86);
	s.push(dB);
	s.push(dA);
	cout << "\n" << s << "\n";
	OrderedQueue<Point2D> q1;
	Point2D x1(3, 5);
	Point2D x2(123, 243);
	Point2D x3(-2343, 349.4);
	Point2D x4(42.3, 2349.3);
	Point2D x5(33.4, -59);
	Point2D x6(-324, 321);
	Point2D x7(-5, 4);
	q1.insert(x1);
	q1.insert(x2);
	q1.insert(x3);
	q1.insert(x4);
	q1.insert(x5);
	q1.insert(x6);
	q1.insert(x7);
	cout << q1 << "\n";

	LinkedListParent <Point2D>* it = &q1;
	OrderedQueue <Point2D> qFiltered = filter(it, firstOctane);
	cout << qFiltered << "\n";
	char c; cin >> c;
	return 0;
}
