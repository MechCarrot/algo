#include <iostream>
#include <array>
#include <vector>
#include <queue>

using namespace std;

template <class V> class FibonacciHeap;

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
            return getRating() > other.getRating();
        }
        if (getExp() != other.getExp()) {
            return getExp() > other.getExp();
        }
        if (getLastName() != other.getLastName()) {
            return getLastName() < other.getLastName();
        }
        return getFirstName() < other.getFirstName();
    }
	bool operator>(const Doctor& other) const {
		if (getRating() != other.getRating()) {
			return getRating() < other.getRating();
		}
		if (getExp() != other.getExp()) {
			return getExp() < other.getExp();
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

template<typename T>
void print_queue(T& q) {
    while (!q.empty()) {
        cout << q.top() << "\n";
        q.pop();
    }
    std::cout << '\n';
}



template <class T>
class Node
{
private:
	T value;
	int degree = 0;
	bool marked;
	Node <T>* prev;
	Node <T>* next;
	Node <T>* parent;
	Node <T>* child;
public:
	friend class FibonacciHeap<T>;
	T getValue() { return value; }
	void setValue(T v) { value = v; }

	Node<T>* getPrev() { return prev; }
	Node<T>* getNext() { return next; }
	Node<T>* getChild() { return child; }
	Node<T>* getParent() { return parent; }

	bool isMarked() { return marked; }
	bool hasChild() { return child; }
	bool hasParent() { return parent; }

	int operator<(Node N)
	{
		return (value < N.getValue());
	}

	int operator>(Node N)
	{
		return (value > N.getValue());
	}

	void print()
	{
		cout << value;
	}
};

template <class T>
void print(Node<T>* N)
{
	cout << N->getValue() << "\n";
}

//куча (heap)
template <class T>
class Heap
{
private:
	//массив
	T* arr;
	//сколько элементов добавлено
	int len;
	//сколько памяти выделено
	int size;
public:

	//доступ к вспомогательным полям кучи и оператор индекса
	int getCapacity() { return size; }
	int getCount() { return len; }

	T& operator[](int index)
	{
		if (index < 0 || index >= len)
			;//?

		return arr[index];
	}

	//конструктор
	Heap<T>(int MemorySize = 100)
	{
		arr = new T[MemorySize];
		len = 0;
		size = MemorySize;
	}

	//поменять местами элементы arr[index1], arr[index2]
	void Swap(int index1, int index2)
	{
		if (index1 <= 0 || index1 >= len)
			;
		if (index2 <= 0 || index2 >= len)
			;
		//здесь нужна защита от дурака

		T temp;
		temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}

	//скопировать данные между двумя узлами

	//функции получения левого, правого дочернего элемента, родителя или их индексов в массиве

	int GetLeftChildIndex(int index)
	{
		if (index < 0 || index * 2 + 1 >= len)
			return -1;
		//здесь нужна защита от дурака
		return index * 2 + 1;
	}

	int GetRightChildIndex(int index)
	{
		if (index < 0 || index * 2 + 2 >= len)
			return -1;
		//здесь нужна защита от дурака

		return index * 2 + 2;
	}

	int GetParentIndex(int index)
	{
		if (index <= 0 || index >= len)
			return -1;
		//здесь нужна защита от дурака

		if (index % 2 == 0)
			return index / 2 - 1;
		return index / 2;
	}

	//восстановление свойств кучи после удаления или добавления элемента
	void Heapify(int index = 0)
	{
		//то же, что и SiftDown
		int leftChild;
		int rightChild;
		int largestChild;

		leftChild = GetLeftChildIndex(index);
		rightChild = GetRightChildIndex(index);


		if (leftChild < 0)
			return;

		switch (rightChild)
		{
		case -1:
			if (arr[index] < arr[leftChild])
			{
				Swap(index, leftChild);
				Heapify(leftChild);
			}
			break;
		default:
			int Max = (arr[leftChild] > arr[rightChild]) ? leftChild : rightChild;
			//нужно сравнить элементы и при необходимости произвести просеивание вниз
			if (arr[index] < arr[Max])
			{
				Swap(index, Max);
				Heapify(Max);
			}
			break;
		}
	}

	//просеить элемент вверх
	void SiftUp(int index = -1)
	{
		if (index == -1) index = len - 1;

		//нужно сравнить элементы и при необходимости произвести просеивание вверх
		int parent_index = GetParentIndex(index);
		if (parent_index < 0) return;

		if (arr[parent_index] < arr[index])
		{
			Swap(parent_index, index);
			SiftUp(parent_index);
		}
	}


	void push(T v)
	{
		//if(len==size) throw ...
		arr[len] = v;
		len++;
		SiftUp();
	}
	T ExtractMax()
	{
		//исключить максимум и запустить просеивание кучи
		//if(len==0) throw ...
		T res = arr[0];
		Swap(0, len - 1);
		len--;
		Heapify();
		return res;
	}
	T Remove(int index)
	{
		T res = arr[index];
		Swap(index, len - 1);
		len--;
		int parent_index = GetParentIndex(index);
		if (parent_index < 0)
		{
			Heapify(index);
			return res;
		}
		if (arr[index] > arr[parent_index])
		{
			Swap(index, parent_index);
			SiftUp(parent_index);
		}
		else
			Heapify(index);
		return res;
	}
};



template <class V> class FibonacciHeap
{
protected:
	Node<V>* heap;
public:

	FibonacciHeap()
	{
		heap = _empty();
	}
	virtual ~FibonacciHeap()
	{
		if (heap) {
			_deleteAll(heap);
		}
	}
	Node<V>* push(V priority)
	{
		Node<V>* ret = _singleton(priority);
		heap = _merge(heap, ret);
		return ret;
	}
	void merge(FibonacciHeap& other)
	{
		heap = _merge(heap, other.heap);
		other.heap = _empty();
	}

	bool isEmpty()
	{
		return heap == NULL;
	}

	V getMaximum()
	{
		return heap->value;
	}

	V removeMaximum()
	{
		Node<V>* old = heap;
		heap = _removeMaximum(heap);
		V ret = old->value;
		delete old;
		return ret;
	}

private:
	Node<V>* _empty() {
		return NULL;
	}

	Node<V>* _singleton(V priority)
	{
		Node<V>* n = new Node<V>;
		n->value = priority;
		n->prev = n->next = n;
		n->degree = 0;
		n->marked = false;
		n->child = NULL;
		n->parent = NULL;
		return n;
	}

	Node<V>* _merge(Node<V>* a, Node<V>* b)
	{
		if (a == NULL)return b;
		if (b == NULL)return a;
		//делаем a бОльшим из двух
		if (a->value < b->value)
		{
			Node<V>* temp = a;
			a = b;
			b = temp;
		}
		Node<V>* an = a->next;
		Node<V>* bp = b->prev;
		a->next = b;
		b->prev = a;
		an->prev = bp;
		bp->next = an;
		return a;
	}

	void _deleteAll(Node<V>* n)
	{
		if (n != NULL) {
			Node<V>* c = n;
			do {
				Node<V>* d = c;
				c = c->next;
				_deleteAll(d->child);
				delete d;
			} while (c != n);
		}
	}

	void _addChild(Node<V>* parent, Node<V>* child)
	{
		child->prev = child->next = child;
		child->parent = parent;
		parent->degree++;
		parent->child = _merge(parent->child, child);
	}

	void _unMarkAndUnParentAll(Node<V>* n)
	{
		if (n == NULL)return;
		Node<V>* c = n;
		do {
			c->marked = false;
			c->parent = NULL;
			c = c->next;
		} while (c != n);
	}

	Node<V>* _removeMaximum(Node<V>* n)
	{
		_unMarkAndUnParentAll(n->child);
		//один узел
		if (n->next == n)
			n = n->child;
		else
		{
			//много узлов, удалить максимум из списка и объединить n->next, n->child (левый ребенок поднялся вверх)
			n->next->prev = n->prev;
			n->prev->next = n->next;
			n = _merge(n->next, n->child);
		}
		if (n == NULL)return n;
		//consolidate()
		Node<V>* trees[64] = { NULL };

		while (true)
		{
			if (trees[n->degree] != NULL)
			{
				Node<V>* t = trees[n->degree];
				if (t == n)break;
				trees[n->degree] = NULL;
				if (n->value > t->value)
				{
					t->prev->next = t->next;
					t->next->prev = t->prev;
					_addChild(n, t);
				}
				else
				{
					t->prev->next = t->next;
					t->next->prev = t->prev;
					if (n->next == n)
					{
						t->next = t->prev = t;
						_addChild(t, n);
						n = t;
					}
					else
					{
						n->prev->next = t;
						n->next->prev = t;
						t->next = n->next;
						t->prev = n->prev;
						_addChild(t, n);
						n = t;
					}
				}
				continue;
			}
			else
			{
				trees[n->degree] = n;
			}
			n = n->next;
		}
		//обновить максимум и вернуть его
		Node<V>* max = n;
		Node<V>* start = n;
		do {
			if (n->value > max->value)
				max = n;
			n = n->next;
		} while (n != start);
		return max;
	}
};



int main()
{
    cout << "Programm is running!\n";
    Doctor dA = Doctor("Nikita", "d", "surgeon", "middle", 5, 70);
    Doctor dB = Doctor("Aboba", "Abobova", "fadfdsafa", "intern", 1, 35);
    Doctor dC = Doctor("Toundra", "Trust", "superdoctor", "senior", 20, 99);

    priority_queue <Doctor> q;

    q.push(dA);
    q.push(dB);
    q.push(dC);

    print_queue(q);

	Heap <Doctor> tree;

	tree.push(dA);
	tree.push(dB);
	tree.push(dC);

	int i = 0;
	while (i < tree.getCount()) {
		Doctor n = tree.ExtractMax();
		cout << n << "\n";
	}

	FibonacciHeap <Doctor> fh;
	fh.push(dA);
	fh.push(dB);
	fh.push(dC);

	for (int i = 0; i < 3; i++)
		cout << fh.removeMaximum()<<" ";

    char c;
    cin >> c;
}
