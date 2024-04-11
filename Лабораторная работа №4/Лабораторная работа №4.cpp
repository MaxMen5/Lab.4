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
    int position = 0;
    Node<T>* now = nullptr;
    Node<T>* first = nullptr;
    Node<T>* last = nullptr;

    void toIndex(int index) {
        if (abs(index - position) > (counting - 1 - index)) {
            now = last;
            position = counting - 1;
        }
        if (abs(index - position) > index) {
            now = first;
            position = 0;
        }
        if (index > position) { for (int i = 0; i < index - position; i++) { now = now->next; } }
        else { for (int i = 0; i < position - index; i++) { now = now->prev; } }
        position = index;
    }

    void add(T info) {
        Node<T>* node = new Node<T>();
        node->info = info;
        if (counting == 0) {
            first = node;
            last = node;
            now = node;
        }
        else {
            node->prev = last;
            last->next = node;
            last = node;
        }
        counting++;
    }

    void insert(int index, T info) {
        if (index < 0 || index > counting) { throw 0; }
        if (index == counting) {
            add(info);
            return;
        }
        toIndex(index);
        Node<T>* node = new Node<T>();
        node->info = info;
        node->prev = now->prev;
        now->prev = node;
        node->next = now;
        if (node->prev != nullptr) { node->prev->next = node; }
        else { first = node; }
        counting++;
        position++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= counting) { throw 0; }
        toIndex(index);
        Node<T>* del = now;
        if (last == first) {
            clear();
            return;
        }
        if (del == last) {
            last = last->prev;
            last->next = nullptr;
            now = last;
            position--;
        }
        else if (del == first) {
            first = first->next;
            first->prev = nullptr;
            now = first;
        }
        else {
            now = now->next;
            del->next->prev = del->prev;
            del->prev->next = del->next;
        }
        delete del;
        counting--;
    }

    T elementAt(int index) {
        if (index < 0 || index >= counting) { throw 0; }
        toIndex(index);
        return now->info;
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
        now = nullptr;
        position = 0;
        counting = 0;
    }
};

void removeRegion(string reg, List<Info> &list) {
    for (int i = 0; i < list.count(); i++) { 
        if (list.elementAt(i).region == reg) { 
            list.removeAt(i); 
            i--;
        } 
    }
}

void sortPeople(List<Info> list) {
    List<Info> listreg;
    for (int i = 0; i < list.count(); i++) {
        bool inList = false;
        for (int j = 0; j < listreg.count(); j++) {
            if (listreg.elementAt(j).region == list.elementAt(i).region) {
                listreg.now->info.people += list.elementAt(i).people;
                inList = true;
                break;
            }
        }
        if (!inList) { listreg.add(list.elementAt(i)); }
    }
    for (int i = 0; i < listreg.count(); i++) {
        for (int j = 0; j < listreg.count() - 1; j++) {
            if (listreg.elementAt(j).people < listreg.elementAt(j + 1).people) {
                swap(listreg.now->prev->info, listreg.now->info);
            }
        }
    }
    for (int i = 0; i < listreg.count(); i++) { cout << listreg.elementAt(i).region << endl; }
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
    system("chcp 1251>NULL");
    instruction();
    List<Info> list;
        while (true) {
            try {
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
            catch (int error) { if (error == 0) { cout << "Введен некорректный индекс!\n"; } }
        }
}
