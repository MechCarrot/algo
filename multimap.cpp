#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;
class User {
private:
    string firstName;
    string secondName;
public:
    User() {
        firstName = "None";
        secondName = "None";
    }
    User(string a, string b) {
        firstName = a;
        secondName = b;
    }

    string getFirstName() {
        return firstName;
    }
    string getSecondName() {
        return secondName;
    }
    bool operator<(const User& other) const {
        if (secondName < other.secondName)
            return true;
        if (secondName == other.secondName && firstName < other.firstName)
            return true;
        return false;
    }
    bool operator>(const User& other) const {
        if (secondName > other.secondName)
            return true;
        if (secondName == other.secondName && firstName > other.firstName)
            return true;
        return false;
    }
    bool operator==(const User& other) const {
        return (firstName == other.firstName) && (secondName == other.secondName);
    }
    friend ostream& operator<<(ostream& os, const User& user) {
        os << user.firstName << " " << user.secondName;
        return os;
    }
};
class Doctor {
private:
    double rating;
    int awards;
public:
    Doctor() {
        rating = -1;
        awards = -1;
    }
    Doctor(double r, int a) {
        rating = r;
        awards = a;
    }
    double getRating() {
        return rating;
    }
    int getAwards() {
        return awards;
    }

    bool operator<(const Doctor& other) const {
        if (rating < other.rating)
            return true;
        if (rating == other.rating && awards < other.awards)
            return true;
        return false;
    }
    bool operator>(const Doctor& other) const {
        if (rating > other.rating)
            return true;
        if (rating == other.rating && awards > other.awards)
            return true;
        return false;
    }
    bool operator==(const Doctor& other) const {
        return (rating == other.rating) && (awards == other.awards);
    }
    friend ostream& operator<<(ostream& os, const Doctor& doctor) {
        os << doctor.rating << " " << doctor.awards;
        return os;
    }
};


template <typename V, typename K>
V findElementByKey(const map<K, V>& m, const K& key) {
    typename map<K, V>::const_iterator it = m.find(key);
    if (it != m.end()) {
        return it->second;
    }
    else {
        return V(); //можно сгенерировать исключение
    }
}

template <typename V, typename K>
V findElementByKey(const multimap<K, V>& m, const K& key) {
    typename multimap<K, V>::const_iterator it = m.find(key);
    if (it != m.end()) {
        return it->second;
    }
    else {
        return V(); //можно сгенерировать исключение
    }
}

template <typename V, typename K>
K findKeyByValue(const map<K, V>& m, const V& value) {
    typename map<K, V>::const_iterator it;
    for (it = m.begin(); it != m.end(); ++it) {
        if (it->second == value) {
            return it->first;
        }
    }
    return K();
}

template <typename V, typename K>
K findKeyByValue(const multimap<K, V>& m, const V& value) {
    typename multimap<K, V>::const_iterator it;
    for (it = m.begin(); it != m.end(); ++it) {
        if (it->second == value) {
            return it->first;
        }
    }
    return K();
}

template <typename V, typename K>
void printTree(const map<K, V>& m) {
    cout << "--------MAP--------\n";
    typename map<K, V>::const_iterator it;
    int i = 0;
    for (it = m.begin(); it != m.end(); it++) {
        cout << i << ". " << it->first << " " << it->second << "\n";
        i++;
    }
    cout << "--------END--------\n";
    return;
}

template <typename V, typename K>
void printTree(const multimap<K, V>& m) {
    cout << "--------MULTIMAP--------\n";
    typename multimap<K, V>::const_iterator it;
    int i = 0;
    for (it = m.begin(); it != m.end(); it++) {
        cout << i << ". " << it->first << " " << it->second << "\n";
        i++;
    }
    cout << "----------END-----------\n";
    return;
}

template <typename V, typename K>
map<K, V> filter(const map<K, V>& m, const V& threshold) {
    map<K, V> filteredMap;

    typename map<K, V>::const_iterator it;
    for (it = m.begin(); it != m.end(); ++it) {
        if (it->second > threshold) {
            filteredMap.insert(*it);
        }
    }
    return filteredMap;
}

template <typename V, typename K>
multimap<K, V> filter(const multimap<K, V>& m, const V& threshold) {
    multimap<K, V> filteredMap;

    typename multimap<K, V>::const_iterator it;
    for (it = m.begin(); it != m.end(); ++it) {
        if (it->second > threshold) {
            filteredMap.insert(*it);
        }
    }
    return filteredMap;
}

template <typename V, typename K>
void insertEl(map<K, V>& m, const K& key, const V& value) {
    auto result = m.insert(make_pair(key, value));
    if (!result.second) {
        throw runtime_error("key already exists");
    }
    return;
}

template <typename V, typename K>
vector<V> getUnique(const map<K, V>& m) {
    set<V> uniqueValues;
    typename map<K, V>::const_iterator it;
    for (it = m.begin(); it != m.end(); ++it) {
        uniqueValues.insert(it->second);
    }
    vector<V> result(uniqueValues.begin(), uniqueValues.end());
    return result;
}

template <typename V, typename K>
vector<V> getEqual(const multimap<K, V>& m, K key) {
    vector<V> vec;
    pair<typename multimap<K, V>::const_iterator,
        typename multimap<K, V>::const_iterator>
        range = m.equal_range(key);

    for (typename multimap<K, V>::const_iterator it = range.first; it != range.second; ++it) {
        vec.push_back(it->second);
    }
    return vec;
}
int main()
{
    /*
        cerr << "Error: " << e.what() << "\n";

    }
    */
    Doctor a(70, 2), b(100, 10), c(85, 6), d(56, 3), e(100, 15);
    User a1("Nikita", "d"), b1("Denis", "Petrusevich"), c1("Petr", "tr"), d1("Vasya", "Sviridov"), e1("Valeriy", "Babushkin");
    map<User, Doctor> m;
    try {
        insertEl(m, a1, a);
        insertEl(m, b1, b);
        insertEl(m, c1, c);
        insertEl(m, d1, d);
        insertEl(m, e1, e);
    }
    catch (runtime_error e) {
        cerr << "Error : " << e.what() << "\n";
    }
    User aboba = findKeyByValue(m, Doctor(70, 2));
    cout << aboba << "\n";
    Doctor aboba1 = findElementByKey(m, User("Nikita", "Denisov"));
    cout << aboba1 << "\n";
    Doctor testval = Doctor(86, 2);
    map<User, Doctor> filteredMap = filter(m, testval);
    printTree(m);

    cout << "\nAfter fillter (86, 2) :" << "\n";
    printTree(filteredMap);
    vector <Doctor> vec = getUnique(m);
    cout << "\nunique : \n";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << "\n";
    }


    //добавление такого же элемента (генерируется исключение)
    //insertEl(m, a1, a);


    //2.2 (нахождение по ключу, значению, filter, print, getEqual)
    multimap <User, Doctor> newMap;
    newMap.insert(make_pair(a1, a));
    newMap.insert(make_pair(b1, b));
    newMap.insert(make_pair(c1, c));
    newMap.insert(make_pair(d1, d));
    newMap.insert(make_pair(e1, e));
    newMap.insert(make_pair(a1, Doctor(100, 999)));
    printTree(newMap);
    vector <Doctor> newVec = getEqual(newMap, a1);
    cout << "\n";
    cout << "Equal elements :" << "\n";
    for (int i = 0; i < newVec.size(); i++) {
        cout << newVec[i] << "\n";
    }

}