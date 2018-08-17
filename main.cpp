#include <utility>

#include <utility>

#include <utility>
#include <iostream>

#define PRIME_SIZE 255

using std::cout;
using std::cin;
using std::endl;
using std::string;


class LinkedHashEntry {
private:
    string key;
    string value;
    LinkedHashEntry *next;
public:
    LinkedHashEntry(string key, string value) {
        this->key = std::move(key);
        this->value = std::move(value);
        this->next = nullptr;
    }

    ~LinkedHashEntry() {
        delete this->next;
    }

    string getKey() {
        return key;
    }

    string getValue() {
        return value;
    }

    void setValue(string value) {
        this->value = std::move(value);
    }

    LinkedHashEntry *getNext() {
        return next;
    }

    void setNext(LinkedHashEntry *next) {
        this->next = next;
    }
};



class HashTable // Хеш-таблица, представленная в виде массива элементов (которые в свою очередь представляют список).
{
    LinkedHashEntry *table[PRIME_SIZE]{};

    int hash (const string &temp) {
        char * k = new char [temp.length()+1];
        strcpy (k, temp.c_str());
        int hashsum, i;
        for (hashsum = i = 0; k[i]; i++)
            hashsum = (hashsum * 31) ^ k[i]; // иногда берут 37
        return hashsum % PRIME_SIZE;
    }

public:
    HashTable(){
        for (auto &i : table) {
            i = nullptr;
        }
    }

    ~HashTable(){
        for (auto &i : table) {
            delete i;
        }
    }

    // Вставляет элемент в таблицу
    void push(const string &name, string number){
        int hashNumber = hash(name);
        LinkedHashEntry *list = new LinkedHashEntry(name, std::move(number));
        LinkedHashEntry *place = table[hashNumber];
        if (place == nullptr){
            table[hashNumber] = list;
            return;
        }

        while (place->getNext() != nullptr){
            place = place->getNext();
        }
        place->setNext(list);
    }

    // Получает элемент из таблицы по его имени.
    LinkedHashEntry* find(const string &name){
        int hashNumber = hash (name);
        LinkedHashEntry *result = table[hashNumber];
        if (!result){
            return nullptr;
        }
        while (result->getKey() != name){
            if (!result->getNext()){
                return nullptr;
            }
            result = result->getNext();
        }
        return result;
    }

    void del(const string &name){
        int hashNumber = hash (name);
        LinkedHashEntry *result = table[hashNumber];
        if (!result){
            return;
        }
        if (result->getKey() == name) {
            delete result;
            table[hashNumber] = nullptr;
        } else if (!result->getNext()) {
            return;
        } else {
            while (result->getNext()->getKey() != name){
                if (!result->getNext()->getNext()){
                    return;
                }
                result = result->getNext();
            }
            LinkedHashEntry* temp = result->getNext();
            result->setNext(temp->getNext());
            delete temp;
        }
    }

    void list(){
        for (auto element : table) {
            while (element){
                cout << element->getKey() << " " << element->getValue() << endl;
                element = element->getNext();
            }
        }
    }
};

HashTable newTable;

void newVassal(){
    string name, number;
    cout << "ENTER NAME AND NUMBER: ";
    cin >> name >> number;

    newTable.push(name, number);
}

void killVassal(){
    string name;
    cout << "ENTER NAME: ";
    cin >> name;

    newTable.del(name);
}

void searchNumber(){
    string name;
    cout << "ENTER NAME: ";
    cin >> name;

    LinkedHashEntry * search = newTable.find(name);
    if (search){
        cout << "NUMBER: " << search->getValue() << endl;
    } else {
        cout << "NOT FOUND";
    }
}

void vassalList(){
    newTable.list();
}

//TODO: удалять человека
//TODO: показывать всех
int main(){
    setlocale(LC_ALL,"rus");

    char input;
    cout << "\t***IT'S ULTIMATE SLAVEBOOK EVER***\n" << endl;
    cout << "1. NEW VASSAL" << endl;
    cout << "2. KILL VASSAL" << endl;
    cout << "3. SEARCH VASSAL NUMBER" << endl;
    cout << "4. VASSALS LIST" << endl;
    cout << "5. CLOSE SLAVEBOOK" << endl;

    bool inLoop = true;

    while (inLoop) {
        cout << "\nMAKE YOUR CHOICE: ";
        cin >> input;

        switch (input) {
            case '1': newVassal(); break;
            case '2': killVassal(); break;
            case '3': searchNumber(); break;
            case '4': vassalList(); break;
            case '5': inLoop = false; break;
            default: cout << "YOU BREAK MY CODE!! I'L KILL YOU!1" << endl; inLoop = false;
                break;
        }
    }

    return 0;
}












