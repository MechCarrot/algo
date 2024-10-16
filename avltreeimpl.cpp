// 2.3-2.5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <vector>
#include <math.h>
#include <string>
using namespace std;


class FullName {
public:
    string firstName;
    string lastName;

    FullName() {
        firstName = "";
        lastName = "";
    }
    FullName(string _firstName, string _lastName) {
        firstName = _firstName;
        lastName = _lastName;
    }
    
    FullName operator=(const FullName& other){
        firstName = other.firstName;
        lastName = other.lastName;
        return *this;
    }

    bool operator<(const FullName& other){
        if (lastName == other.lastName)
            return firstName < other.firstName;
        return lastName < other.lastName;
    }
    bool operator>(const FullName& other){
        if (lastName == other.lastName)
            return firstName > other.firstName;
        return lastName > other.lastName;
    }
    bool operator ==(const FullName& other) {
        return lastName == other.lastName && firstName == other.lastName;
    }

    friend ostream& operator<<(ostream& os, const FullName& _FullName);
};

ostream& operator << (ostream& os, const FullName& _FullName) {
    return os << "Last Name : " << _FullName.lastName << " ; First Name : " << _FullName.firstName << "\n";
}


class Doctor {
public:
    Doctor()
    {
        name.firstName = "NULL";
        name.lastName = "NULL";
        specialty = "NULL";
        position = "NULL";
        experience = 0;
        rating = 0.0;
    }
    Doctor(string firstName_, string lastName_, string specialty_, string position_, int experience_, double rating_)
    {
        name.firstName = firstName_;
        name.lastName = lastName_;
        specialty = specialty_;
        position = position_;
        experience = experience_;
        rating = rating_;
    }
    Doctor(FullName _Name, string specialty_, string position_, int experience_, double rating_) {
        name.firstName = _Name.firstName;
        name.lastName = _Name.lastName;
        specialty = specialty_;
        position = position_;
        experience = experience_;
        rating = rating_;
    }

    double getRating() const {
        return rating;
    }

    int getExp() const {
        return experience;
    }
    string getLastName() const {
        return name.lastName;
    }
    string getFirstName() const {
        return name.firstName;
    }
    FullName getName() const {
        return name;
    }
    bool operator==(const Doctor& other) const {
        return (name.firstName == other.name.firstName &&
            name.lastName == other.name.lastName &&
            specialty == other.specialty &&
            position == other.position &&
            experience == other.experience &&
            rating == other.rating);
    }
    bool operator!=(const Doctor& other) const {
        return (name.firstName != other.name.firstName &&
            name.lastName != other.name.lastName &&
            specialty != other.specialty &&
            position != other.position &&
            experience != other.experience &&
            rating != other.rating);
    }

    Doctor operator=(const Doctor& other) {
        name = other.name;
        specialty = other.specialty;
        experience = other.experience;
        rating = other.rating;
        position = other.position;
        return *this;
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
    FullName name;
    string position, specialty;
    int experience;
    double rating;
};

ostream& operator << (ostream& os, const Doctor& d) {
    return os << "Last Name : " << d.name.lastName << "\n" << "first Name : " << d.name.firstName << "\n" << "Specialty: " << d.specialty << "\n" << "Position: " << d.position << "\n" << "Experience: " << d.experience << "\n" << "Rating: " << d.rating << "\n";
}

template <class K, class V>
class Node {
protected:
    K key;
    V value;
    Node* left;
    Node* right;
    Node* parent;
    int height;
public:
    virtual void setKey(K _key) {
        key = _key;
    }
    virtual void setValue(V _value) {
        value = _value;
    }
    virtual void setHeight(int _height) {
        height = _height;
    }
    virtual void setLeft(Node* _left) {
        left = _left;
    }
    virtual void setRight(Node* _right) {
        right = _right;
    }
    virtual void setParent(Node* _parent) {
        parent = _parent;
    }

    virtual Node* getLeft() {
        return left;
    }
    virtual Node* getRight() {
        return right;
    }
    virtual Node* getParent() {
        return parent;
    }
    virtual K getKey() {
        return key;
    }
    virtual V getValue() {
        return value;
    }
    virtual int getHeight() {
        return height;
    }

    Node <K,V>(const Node<K,V>& _Node) : key(_Node.key), value(_Node.value), left(_Node.left), right(_Node.right), parent(_Node.parent), height(_Node.height) {
    }
    Node <K, V>(K _key, V _value) {
        left = right = parent = NULL;
        height = 1;
        key = _key;
        value = _value;
    }
    Node <K, V>() {
        left = right = parent = NULL;
        height = 1;
        key = K(); value = V();
    }

    Node <K, V>* successor() {
        Node<K, V>* ans;
        if (right != NULL) {
            ans = right;
            while (ans->getLeft() != NULL) {
                ans->getLeft();
            }
            return ans;
        }

        ans = parent;
        for (Node <K, V>* cur = this; cur != NULL && ans != NULL; ans = ans->getParent(), cur = cur->getParent()) {
            if (ans->getLeft() == cur)
                return ans;
        }
        return this;
    }
    Node <K, V>* predecessor() {
        Node <K, V>* ans;
        if (left != NULL) {
            ans = left;
            while (ans->getLeft() != NULL) {
                ans = ans->getLeft();
            }
            return ans;
        }

        ans = parent;

        for (Node <K, V>* cur = this; ans != NULL && cur != NULL; ans = ans->getParent(), cur = cur->getParent()) {
            if (ans->getRight() == cur)
                return ans;
        }
        return this;
    }

    void swap(Node <K, V>& _Node) {
        std::swap(key, _Node.key);
        std::swap(value, _Node.value);
        return;
    }

    template <class K, class V>
    friend ostream& operator<<(ostream& os, const Node<K, V>& _Node);
    template <class K, class V>
    friend ostream& operator<<(ostream& os, const Node<K, vector <V>*>& _Node);
};

template<class K, class V>
ostream& operator<<(ostream& os, const Node<K, V>& _Node) {
    return os << "Key : " << _Node.key << " ; Value : " << _Node.value << "\n";
}

template <class K, class V>
ostream& operator<<(ostream& os, const Node<K, vector <V>*>& _Node) {
    return os << "Key : " << _Node.key << " ; Value : " << *_Node.value << "\n";
}

template <class K, class V>
void print(Node <K, V>* _Node) {
    cout << *_Node << "\n";
}

template <class K, class V>
class TreeIterator : public std::iterator<std::input_iterator_tag, K, V>{
private:
    Node <K, V>* ptr;
public:
    TreeIterator() {
        ptr = NULL;
    }
    TreeIterator(Node <K, V>* _ptr) {
        ptr = _ptr;
    }
    TreeIterator(const TreeIterator& it) {
        ptr = it.ptr;
    }

    bool operator==(const TreeIterator& other) {
        return ptr == other.ptr;
    }
    bool operator!=(const TreeIterator& other) {
        return ptr != other.ptr;
    }
    Node <K, V>& operator*() {
        return *ptr;
    }

    TreeIterator& operator++() {
        if (ptr != NULL)
            ptr = ptr->successor();
        return *this;
    }
    TreeIterator operator++(int v) {
        Node<K, V>* p = ptr;
        if (ptr != NULL)
            ptr = ptr->successor();
        return TreeIterator(p);
    }
    TreeIterator& operator--() {
        if (ptr != NULL)
            ptr = ptr->predecessor();
        return *this;
    }
    TreeIterator operator--(int v) {
        Node<K, V>* p = ptr;
        if (ptr != NULL) 
            ptr = ptr->predecessor();
        return TreeIterator(p);
    }
};

template <class K, class V>
class Tree {
protected:
    Node <K, V>* root;
    virtual Node<K, V>* find(K _key, Node<K, V>* cur) {
        if (cur == NULL) return NULL;
        if (cur->getKey() == _key)  return cur;
        if (cur->getKey() > _key) return find(_key, cur->getLeft());
        return find(_key, cur->getRight());
    }
    virtual Node<K, V>* Add_R(Node <K, V>* _Node, Node<K, V>* cur) {
        if (_Node == NULL) return NULL;

        if (root == NULL) return root = _Node;

        if (cur->getKey() > _Node->getKey())
        {
            if (cur->getLeft() != NULL)
                cur->setLeft(Add_R(_Node, cur->getLeft()));
            else
                cur->setLeft(_Node);
            cur->getLeft()->setParent(cur);
        }
        if (cur->getKey() < _Node->getKey())
        {
            if (cur->getRight() != NULL)
                cur->setRight(Add_R(_Node, cur->getRight()));
            else
                cur->setRight(_Node);
            cur->getRight()->setParent(cur);
        }

        if (cur->getKey() == _Node->getKey())
            swap(cur, _Node);
        return cur;
    }
public:
    Tree() {
        root = NULL; 
    }
    virtual Node<K, V>* getRoot() {
        return root;
    }
    virtual Node<K, V>* Add_R(Node <K, V>* _Node) {
        return Add_R(_Node, root);
    }

    //Need refactoring! (to many if statements)
    virtual Node<K, V>* Remove(Node<K, V>* _Node)
    {
        Node<K, V>* el;

        while (_Node->getLeft() != NULL && _Node->getRight() != NULL)
        {
            el = _Node->successor();
            _Node->swap(*el);
            _Node = el;
        }

        el = _Node;

        if (_Node->getRight() == NULL && _Node->getLeft() == NULL)
            el = NULL;

        if (_Node->getRight() != NULL)
            el = _Node->getRight();

        if (_Node->getLeft() != NULL)
            el = _Node->getLeft();

        if (root == _Node) root = el;
        else {
            if (_Node->getParent()->getRight() == _Node)
                _Node->getParent()->setRight(el);
            else
                _Node->getParent()->setLeft(el);
        }
        if (el != NULL) el->setParent(_Node->getParent());

        return _Node;
    }

    virtual Node<K, V>* Add(K _key, V _value) {
        Node <K, V>* el = new Node<K, V>;
        el->setKey(_key);
        el->setValue(_value);
        return Add_R(el);
    }
    virtual Node<K, V>* Add(K _key) {
        Node <K, V>* el = new Node<K, V>;
        el->setKey(_key);
        return Add_R(el);
    }
    virtual Node<K, V>* Remove(TreeIterator <K, V>& it) {
        return Remove(&(*it));
    }

    virtual Node<K, V>* Min(Node <K, V>* cur = NULL) {
        if (root == NULL) return NULL;
        if (cur == NULL) cur = root;
        while (cur->getLeft() != NULL) {
            cur = cur->getLeft();
        }
        return cur;
    }
    virtual Node<K, V>* Max(Node <K, V>* cur = NULL) {
        if (root == NULL) return NULL;
        if (cur == NULL) cur = root;
        while (cur->getRight() != NULL) {
            cur = cur->getRight();
        }
        return cur;
    }

    TreeIterator<K, V> begin() {
        return TreeIterator<K, V>(Min()); 
    }
    TreeIterator<K, V> end() { 
        return TreeIterator<K, V>(Max()); 
    }

    virtual void InOrder(Node<K, V>* _Node, void(*f)(Node<K, V>*)) 
    {
        if (_Node != NULL && _Node->getLeft() != NULL)
            InOrder(_Node->getLeft(), f);
        if (_Node != NULL)
            f(_Node);
        if (_Node != NULL && _Node->getRight() != NULL)
            InOrder(_Node->getRight(), f);
    }
    virtual void InOrder(TreeIterator<K, V> it, void(*f)(Node<K, V>*))
    {
        while (it != end()) {
            f(&*it);
            it++;
        }
    }
    virtual void PostOrder(Node<K, V>* _Node, void(*f)(Node<K, V>*))
    {
        if (_Node != NULL && _Node->getLeft() != NULL)
            PostOrder(_Node->getLeft(), f);
        if (_Node != NULL && _Node->getRight() != NULL)
            PostOrder(_Node->getRight(), f);
        if (_Node != NULL)
            f(_Node);
    }
    virtual void PostOrder(TreeIterator<K, V> it, void(*f)(Node<K, V>*))
    {
        while (it != end()) {
            f(&*it);
            it--;
        }
    }
};

template <class K, class V>
class AVLTree : public Tree<K, V>{
protected:

    int bFactor(Node <K, V>* _Node) {
        int hRight = 0, hLeft = 0;
        if (_Node->getRight() != NULL)
            hRight = _Node->getRight()->getHeight();
        if (_Node->getLeft() != NULL)
            hLeft = _Node->getLeft()->getHeight();
        return hRight - hLeft;
    }
    void fixHeight(Node <K, V>* _Node) {
        int hLeft = 0, hRight = 0;
        if (_Node->getLeft() != NULL) {
            hLeft = _Node->getLeft()->getHeight();
        }
        if (_Node->getRight() != NULL) {
            hRight = _Node->getRight()->getHeight();
        }
        int hFinal = 0;
        if (hLeft > hRight) {
            _Node->setHeight(hLeft + 1);
        }
        else {
            _Node->setHeight(hRight + 1);
        }
    }


    Node<K, V>* RotateLeft(Node<K, V>* q)
    {

        Node<K, V>* _Node = q->getRight();

        if (root == q) {
            root = _Node; 
        }
        else {
            if (q->getParent()->getRight() == q)
                q->getParent()->setRight(_Node);
            else
                q->getParent()->setLeft(_Node);
        }
        _Node->setParent(q->getParent());
        q->setParent(_Node);

        q->setRight(_Node->getLeft());
        if (_Node->getLeft() != NULL) {
            _Node->getLeft()->setParent(q);
        }
        _Node->setLeft(q);

        fixHeight(q);
        fixHeight(_Node);

        return _Node;
    }
    Node <K, V>* RotateRight(Node <K, V>* _Node) {
        Node<K, V>* q = _Node->getLeft();

        if (_Node == root) {
            root = q;
        }
        else {
            if (_Node->getParent()->getRight() == _Node)
                _Node->getParent()->setRight(q);
            else
                _Node->getParent()->setLeft(q);
        }
        q->setParent(_Node->getParent());
        _Node->setParent(q);
        _Node->setLeft(q->getRight());
        if (q->getRight() != NULL) {
            q->getRight()->setParent(_Node);
        }
        q->setRight(_Node);
        fixHeight(_Node);
        fixHeight(q);
        return q;
    }

    Node<K, V>* Balance(Node<K, V>* _Node)
    {

        fixHeight(_Node);
        if (bFactor(_Node) == 2)
        {
            if (bFactor(_Node->getRight()) < 0) RotateRight(_Node->getRight());
            return RotateLeft(_Node);
        }
        if (bFactor(_Node) == -2)
        {
            if (bFactor(_Node->getLeft()) > 0)  RotateLeft(_Node->getLeft());
            return RotateRight(_Node);
        }
        return _Node;
    }

    virtual Node<K, V>* Add_R(Node<K, V>* _Node, Node<K, V>* cur)
    {
        _Node = Tree<K, V>::Add_R(_Node, cur);
        if (cur != NULL)
            return Balance(cur);
        return _Node;
    }
public:
    using Tree<K, V>::root;

    AVLTree() : Tree<K, V>() {}

    virtual Node<K, V>* Add_R(Node<K, V>* _Node){
        _Node = Add_R(_Node, root);
        return _Node;
    }

    virtual Node<K, V>* Add(K _key, V _value){
        Node<K, V>* _Node = new Node<K, V>;
        _Node->setKey(_key);
        _Node->setValue(_value);
        return Add_R(_Node);
    }

    virtual Node<K, V>* Add(K _key){
        Node<K, V>* _Node = new Node<K, V>;
        _Node->setKey(_key);
        return Add_R(_Node);
    }

    virtual Node<K, V>* Remove(Node<K, V>* _Node){
        Node<K, V>* _Node1 = Tree<K, V>::Remove(_Node);
        Node<K, V>* _Node2 = _Node1->getParent();
        while (_Node2 != NULL)
        {
            Balance(_Node2);
            _Node2 = _Node2->getParent();
        }
        return _Node1;
    }

    virtual Node<K, V>* Remove(TreeIterator<K, V>& it){
        return Remove(&(*it));
    }

    virtual void InOrder(Node<K, V>* _Node, void(*f)(Node<K, V>*)) {
        Tree<K, V>::InOrder(_Node, f);
    }

    virtual void InOrder(TreeIterator<K, V> it, void(*f)(Node<K, V>*)){
        Tree<K, V>::InOrder(it, f);
    }

    virtual void PostOrder(Node<K, V>* _Node, void(*f)(Node<K, V>*)){
        Tree<K, V>::PostOrder(_Node, f);
    }

    virtual void PostOrder(TreeIterator<K, V> it, void(*f)(Node<K, V>*)) {
        Tree<K, V>::PostOrder(it, f);
    }
};


template <class K, class V>
class MultiAVLTree : private AVLTree<K, vector<V>*>
{
protected:
    virtual Node<K, vector<V>*>* Add_R(Node<K, vector<V>*>* _Node, Node<K, vector<V>*>* cur){
        if (_Node == NULL) 
            return NULL;

        if (root == NULL) 
            return root = _Node;

        if (cur->getKey() > _Node->getKey())
        {
            if (cur->getLeft() != NULL)
                cur->setLeft(Add_R(_Node, cur->getLeft()));
            else
                cur->setLeft(_Node);
            cur->getLeft()->setParent(cur);
        }
        if (cur->getKey() < _Node->getKey())
        {
            if (cur->getRight() != NULL)
                cur->setRight(Add_R(_Node, cur->getRight()));
            else
                cur->setRight(_Node);
            cur->getRight()->setParent(cur);
        }

        if (cur->getKey() == _Node->getKey())
        {
            vector<V>* vec = _Node->getValue();
            for (auto it = vec->begin(); it != vec->end(); it++)
                cur->getValue()->push_back(*it);
        }

        if (cur != NULL)
            AVLTree<K, vector<V>*>::Balance(cur);
        return cur;
    }
public:
    using Tree<K, vector<V>*>::root;
    MultiAVLTree() :AVLTree<K, vector<V>*>() {}

    virtual Node<K, vector<V>*>* Add_R(Node<K, vector<V>*>* _Node){
        _Node = Add_R(_Node, root);
    }
    virtual Node<K, vector<V>*>* Add(K _key, vector<V>* _value){
        Node<K, vector<V>*>* _Node = new Node<K, vector<V>*>*;
        _Node->setKey(_key);
        _Node->setValue(_value);
        return Add_R(_Node);
    }
    virtual Node<K, vector<V>*>* Add(K _key){
        Node<K, vector<V>*>* _Node = new Node<K, vector<V>*>*;
        _Node->setKey(_key);
        return Add_R(_Node);
    }

    virtual Node<K, vector<V>*>* Remove(Node<K, vector<V>*>* _Node){
        return AVLTree<K, vector<V>*>::Remove(_Node);
    }
    virtual Node<K, vector<V>*>* Remove(TreeIterator<K, vector<V>*>& it){
        return AVLTree<K, vector<V>*>::Remove(&(*it));
    }

    virtual Node<K, vector<V>*>* operator[](K _key){
        return Tree<K, vector<V>*>::Find(_key);
    }

    virtual void InOrder(Node<K, V>* _Node, void(*f)(Node<K, V>*)) {
        Tree<K, V>::InOrder(_Node, f);
    }
    virtual void InOrder(TreeIterator<K, V> it, void(*f)(Node<K, V>*)){
        Tree<K, V>::InOrder(it, f);
    }
    virtual void PostOrder(Node<K, V>* _Node, void(*f)(Node<K, V>*)){
        Tree<K, V>::PostOrder(_Node, f);
    }
    virtual void PostOrder(TreeIterator<K, V> it, void(*f)(Node<K, V>*)){
        Tree<K, V>::PostOrder(it, f);
    }
};


template <class K, class V>
class SplayTree : protected AVLTree<K, V>
{
protected:
    Node<K, V>* Add_R(Node<K, V>* _Node, Node<K, V>* cur){
        return AVLTree<K, V>::Add_R(_Node, cur);
    }
    Node<K, V>* Splay(Node<K, V>* _Node)
    {
        while (root != _Node)
        {
            if (_Node->getParent()->getRight() == _Node)
                AVLTree<K, V>::RotateLeft(_Node->getParent());
            else
                AVLTree<K, V>::RotateRight(_Node->getParent());
        }
        root = _Node;
        
        return root;
    }
public:
    using Tree<K, V>::root;

    SplayTree() : AVLTree<K, V>() {}

    Node<K, V>* GetRoot() { 
        return root;
    }

    Node<K, V>* Add_R(Node<K, V>* _Node) {
        _Node = Add_R(_Node, root);
        return _Node;
    }
    Node<K, V>* Add(K _key, V _value)
    {
        Node<K, V>* _Node = new Node<K, V>;
        _Node->setKey(_key);
        _Node->setValue(_value);
        return Add_R(_Node);
    }
    Node<K, V>* Add(K _key) {
        Node<K, V>* _Node = new Node<K, V>;
        _Node->setKey(_key);
        return Add_R(_Node);
    }

    Node<K, V>* Find(Node<K, V>* _Node){
        return Splay(_Node);
    }
    Node<K, V>* Find(K _key, V _value)
    {
        Node<K, V>* _Node = new Node<K, V>;
        _Node->setKey(_key);
        _Node->setValue(_value);
        return Splay(_Node);
    }
    Node<K, V>* Find(K _key)
    {
        return Splay(Tree<K, V>::Find(_key, root));
    }

    Node<K, V>* Remove(Node<K, V>* _Node)
    {
        return Tree<K, V>::Remove(_Node);
    }
    virtual Node<K, V>* Remove(TreeIterator<K, V>& it)
    {
        return Tree<K, V>::Remove(&(*it));
    }

    virtual void InOrder(Node<K, V>* _Node, void(*f)(Node<K, V>*))  {
        Tree<K, V>::InOrder(_Node, f);
    }
    virtual void InOrder(TreeIterator<K, V> it, void(*f)(Node<K, V>*)) {
        Tree<K, V>::InOrder(it, f);
    }
    virtual void PostOrder(Node<K, V>* _Node, void(*f)(Node<K, V>*)){
        Tree<K, V>::PostOrder(_Node, f);
    }
    virtual void PostOrder(TreeIterator<K, V> it, void(*f)(Node<K, V>*)){
        Tree<K, V>::PostOrder(it, f);
    }
};

signed main(){
    FullName a1("Nikita", "d"), b1("Denis", "Petrusevich"), c1("Petr", "tr"), d1("Vasya", "Sviridov"), e1("Valeriy", "Babushkin");
    Doctor a(a1,"surgeon", "junior", 1, 60), b(b1, "neuro-surgeon", "teamlead", 10, 100), c(c1,"therapist", "middle", 2, 80), d(d1, "therapist", "middle", 3, 75), e(e1, "dentist", "senior", 15, 100);

    AVLTree<FullName, Doctor> AVL;
    AVL.Add(a1, a);
    AVL.Add(b1, b);
    AVL.Add(c1, c);
    AVL.Add(d1, d);
    cout << "\nAVL InOrder: " << "\n";
    AVL.InOrder(AVL.getRoot(), print);
    cout << "\nAVL PostOrder: \n";
    AVL.PostOrder(AVL.getRoot(), print);
        cout << "\n";

    cout << "\nMIN-MAX \n";
    cout << *AVL.Max() << "\n";
    cout << *AVL.Min() << "\n";
    
    /*
    */
    
    SplayTree<FullName, Doctor> splay;

    splay.Add(a.getName(), a);
    splay.Add(b.getName(), b);
    splay.Add(c.getName(), c);
    splay.Add(d.getName(), d);
    splay.Add(e.getName(), e);
    cout << "Splay InOrder:" << "\n";
    splay.InOrder(splay.GetRoot(), print);
   
    cout << "Splay PostOrder:" << "\n";

    splay.PostOrder(splay.GetRoot(), print);
   

    return 0;
}
