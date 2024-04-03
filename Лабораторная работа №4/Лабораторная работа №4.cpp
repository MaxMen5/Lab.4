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

template <typename T1, typename T2, typename T3>
struct Info {
    T1 city;
    T2 region;
    T3 people;
};

template <typename T1, typename T2, typename T3>
struct Node {
    Info <T1, T2, T3> info;
    Node* next = nullptr;
    Node* prev = nullptr;
};

template <typename T1, typename T2, typename T3>
struct List {
    int counting = 0;
    Node< T1, T2, T3 >* first = nullptr;
    Node< T1, T2, T3 >* last = nullptr;

    void add(Info<T1, T2, T3> T) {
        Node< T1, T2, T3 >* node = new Node<T1, T2, T3>();
        node->info.city = T.city;
        node->info.region = T.region;
        node->info.people = T.people;
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

    void insert(int index, Info<T1, T2, T3> T) {
        if (index < 0 || index > counting) { return; }
        if (index == counting) {
            add(T);
            return;
        }
        Node< T1, T2, T3 >* now = first;
        for (int i = 0; i < index; i++) { now = now->next; }
        Node< T1, T2, T3 >* node = new Node<T1, T2, T3>();
        node->info.city = T.city;
        node->info.region = T.region;
        node->info.people = T.people;
        node->prev = now->prev;
        now->prev = node;
        node->next = now;
        if (node->prev != nullptr) { node->prev->next = node; }
        else { first = node; }
        counting++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= counting) { return; }
        Node< T1, T2, T3 >* del = first;
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

    Info<T1, T2, T3> elementAt(int index) {
        if (index < 0 || index >= counting) {
            Info<string, string, int> T;
            T.city = "Ошибка!";
            T.region = "Ошибка!";
            T.people = 0;
            return T;
        }
        Node<T1, T2, T3>* node = first;
        for (int i = 0; i < index; i++) { node = node->next; }
        return node->info;
    }

    int count() { return counting; }

    void clear() {
        int kol = counting;
        for (int i = 0; i < kol; i++) {
            Node<T1, T2, T3>* del = first;
            first = first->next;
            delete del;
        }
        last = nullptr;
        counting = 0;
    }

    void removeRegion(string reg) {
        Node<T1, T2, T3>* node = first;
        int kol = counting;
        for (int i = 0; i < kol; i++) {
            if (node->info.region == reg) {
                Node<T1, T2, T3>* del = node;
                node = node->next;
                if (del == first) {
                    if (first->next == nullptr) {
                        clear();
                        break;
                    }
                    first = first->next;
                    first->prev = nullptr;
                }
                else if (del == last) {
                    last = last->prev;
                    last->next = nullptr;
                }
                else {
                    node->prev = del->prev;
                    del->prev->next = node;
                }
                delete del;
                counting--;
            }
            else { node = node->next; }
        }
    }
    
    void sortPeople() {
        List listcopy, list;
        Node<T1, T2, T3>* copy = first;
        for (int i = 0; i < counting; i++) {
            listcopy.add(copy->info);
            copy = copy->next;
        }

        Node<T1, T2, T3>* node = listcopy.first;
        while (node != nullptr) {
            Node<T1, T2, T3>* now = node->next;
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
            Node<T1, T2, T3>* element = list.first;
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
};

Info<string, string, int> push() {
    Info <string, string, int> T;
    cout << "Введите город: ";
    cin >> T.city;
    cout << "Введите регион: ";
    cin >> T.region;
    cout << "Введите количество населения: ";
    cin >> T.people;
    return T;
}
void out(Info <string, string, int> T) {
    cout << "Город: " << T.city << "\n";
    cout << "Регион: " << T.region << "\n";
    cout << "Население: " << T.people << "\n";
}

int main() {
    setlocale(LC_ALL, "ru");
    instruction();
    List <string, string, int> list;
    while (true) {
        cout << "\nВведите команду: ";
        int parameter;
        string reg, c;
        cin >> parameter;
        switch (parameter) {
        case 1:
            list.add(push());
            break;
        case 2:
            cout << "Введите индекс: ";
            cin >> parameter;
            list.insert(parameter, push());
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
            list.sortPeople();
            break;
        case 8:
            cin >> reg;
            list.removeRegion(reg);
            break;
        case 0:
            return 0;
        default:
            cout << "Неизвестная команда!";
        }
    }
}