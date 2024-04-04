#include <iostream>
using namespace std;

void instruction() {
    cout << "Для добавления элемента в список, введите 1\n";
    cout << "Для вставки в данную позицию списка данного значения, введите 2\n";
    cout << "Для удаления из списка элемента в данной позиции, введите 3\n";
    cout << "Для доступа к информационной части элемента в данной позиции, введите 4\n";
    cout << "Для подсчета количества элементов в списке, введите 5\n";
    cout << "Для удаления всех элементов списка, введите 6\n";
    cout << "Для вывода наименований регионов по убыванию суммарной численности населения, введите 7\n";
    cout << "Для удаления всех элементов одного региона, введите 8\n";
    cout << "Для завершения работы программы, введите 0\n\n";
}

struct Info {
    string city = "";
    string region = "";
    int people = 0;
};

template <typename T>
struct Node {
    T info;
    Node* next = nullptr;
    Node* prev = nullptr;
};

template <typename T>
struct List {
    int counting = 0;
    Node<T>* first = nullptr;
    Node<T>* last = nullptr;

    void add(T info) {
        Node<T>* node = new Node<T>();
        node->info = info;
        if (counting == 0) {
            first = node;
            last = node;
        }
        else {
            node->prev = last;
            last->next = node;
            last = node;
        }
        counting++;
    }

    void insert(int index, T info) {
        if (index < 0 || index > counting) { return; }
        if (index == counting) {
            add(info);
            return;
        }
        Node<T>* now = first;
        for (int i = 0; i < index; i++) { now = now->next; }
        Node<T>* node = new Node<T>();
        node->info = info;
        node->prev = now->prev;
        now->prev = node;
        node->next = now;
        if (node->prev != nullptr) { node->prev->next = node; }
        else { first = node; }
        counting++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= counting) { return; }
        Node<T>* del = first;
        for (int i = 0; i < index; i++) { del = del->next; }
        if (last == first) {
            clear();
            return;
        }
        if (del == last) {
            last = last->prev;
            last->next = nullptr;
        }
        else if (del == first) {
            first = first->next;
            first->prev = nullptr;
        }
        else {
            del->next->prev = del->prev;
            del->prev->next = del->next;
        }
        delete del;
        counting--;
    }

    T elementAt(int index) {
        if (index < 0 || index >= counting) {
            Info error;
            return error;
        }
        Node<T>* node = first;
        for (int i = 0; i < index; i++) { node = node->next; }
        return node->info;
    }

    int count() { return counting; }

    void clear() {
        int kol = counting;
        for (int i = 0; i < kol; i++) {
            Node<T>* del = first;
            first = first->next;
            delete del;
        }
        last = nullptr;
        counting = 0;
    }
};

void removeRegion(string reg, List<Info> &list) {
    Node<Info>* node = list.first;
    int kol = list.counting;
    for (int i = 0; i < kol; i++) {
        if (node->info.region == reg) {
            Node<Info>* del = node;
            node = node->next;
            if (del == list.first) {
                if (list.first->next == nullptr) {
                    list.clear();
                    break;
                }
                list.first = list.first->next;
                list.first->prev = nullptr;
            }
            else if (del == list.last) {
                list.last = list.last->prev;
                list.last->next = nullptr;
            }
            else {
                node->prev = del->prev;
                del->prev->next = node;
            }
            delete del;
            list.counting--;
        }
        else { node = node->next; }
    }
}

void sortPeople(List<Info> startlist) {
    List<Info> listcopy, list;
    Node<Info>* copy = startlist.first;
    for (int i = 0; i < startlist.counting; i++) {
        listcopy.add(copy->info);
        copy = copy->next;
    }

    Node<Info>* node = listcopy.first;
    while (node != nullptr) {
        Node<Info>* now = node->next;
        for (int i = 0; i < listcopy.counting - 1; i++) {
            if (node->info.region == now->info.region) {
                node->info.people += now->info.people;
                now = now->next;
                listcopy.removeAt(i + 1);
                i--;
            }
            else {
                now = now->next;
            }
        }
        list.add(node->info);
        node = node->next;
        listcopy.removeAt(0);
    }

    int point = 1;
    while (point != 0) {
        point = 0;
        Node<Info>* element = list.first;
        for (int i = 0; i < list.counting - 1; i++) {
            if (element->info.people < element->next->info.people) {
                swap(element->info, element->next->info);
                point++;
            }
            element = element->next;
        }
    }

    copy = list.first;
    for (int i = 0; i < list.counting; i++) {
        cout << copy->info.region << endl;
        copy = copy->next;
    }
}

Info put() {
    Info info;
    cout << "Введите город: ";
    cin >> info.city;
    cout << "Введите регион: ";
    cin >> info.region;
    cout << "Введите население: ";
    cin >> info.people;
    return info;
}

void out(Info info) {
    cout << "Город: " << info.city << "\n";
    cout << "Регион: " << info.region << "\n";
    cout << "Население: " << info.people << "\n";
}

int main() {
    setlocale(LC_ALL, "ru");
    instruction();
    List<Info> list;
    while (true) {
        cout << "\nВведите команду: ";
        int parameter;
        string reg; 
        cin >> parameter;
        switch (parameter) {
        case 1:
            list.add(put());
            break;
        case 2:
            cout << "Введите индекс: ";
            cin >> parameter;
            list.insert(parameter, put());
            break;
        case 3:
            cout << "Введите индекс: ";
            cin >> parameter;
            list.removeAt(parameter);
            break;
        case 4:
            cout << "Введите индекс: ";
            cin >> parameter;
            out(list.elementAt(parameter));
            break;
        case 5:
            cout << "Количество элементов: " << list.count();
            break;
        case 6:
            list.clear();
            break;
        case 7:
            sortPeople(list);
            break;
        case 8:
            cout << "Введите регион: ";
            cin >> reg;
            removeRegion(reg, list);
            break;
        case 0:
            return 0;
        default:
            cout << "Неизвестная команда!";
        }
    }
}
