#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Dovidnyk {
public:
    string name;
    string vlasnyk;
    string phone;
    string adress;
    string rid;

    void input() {
        cout << "назва фірми: ";
        getline(cin, name);
        cout << "власник: ";
        getline(cin, vlasnyk);
        cout << "телефон: ";
        getline(cin, phone);
        cout << "адреса: ";
        getline(cin, adress);
        cout << "рід діяльності: ";
        getline(cin, rid);
    }

    void display() const {
        cout << "назва фірми: " << name << endl;
        cout << "власник: " << vlasnyk << endl;
        cout << "телефон: " << phone << endl;
        cout << "адреса: " << adress << endl;
        cout << "рід діяльності: " << rid << endl;
    }

    string to_string() const {
        return name + ";" + vlasnyk + ";" + phone + ";" + adress + ";" + rid;
    }

    void from_string(const string& line) {
        size_t pos = 0, prev = 0;
        vector<string> polia;
        while ((pos = line.find(';', prev)) != string::npos) {
            polia.push_back(line.substr(prev, pos - prev));
            prev = pos + 1;
        }
        polia.push_back(line.substr(prev));
        if (polia.size() == 5) {
            name = polia[0];
            vlasnyk = polia[1];
            phone = polia[2];
            adress = polia[3];
            rid = polia[4];
        }
    }
};

void add_record(const string& filename) {
    Dovidnyk zapys;
    cin.ignore();
    zapys.input();

    ofstream vytid(filename, ios::app);
    vytid << zapys.to_string() << endl;
    vytid.close();
}

void read_all(const string& filename, vector<Dovidnyk>& zapisany) {
    ifstream vhid(filename);
    string line;
    while (getline(vhid, line)) {
        Dovidnyk zapys;
        zapys.from_string(line);
        zapisany.push_back(zapys);
    }
    vhid.close();
}

void search_records(const vector<Dovidnyk>& zapisany, const string& znach, int pole) {
    for (const auto& zapys : zapisany) {
        if ((pole == 1 && zapys.name == znach) ||
            (pole == 2 && zapys.vlasnyk == znach) ||
            (pole == 3 && zapys.phone == znach) ||
            (pole == 4 && zapys.rid == znach)) {
            zapys.display();
        }
    }
}

int main() {
    const string filename = "dovidnyk.txt";
    int choice;

    do {
        cout << "меню" << endl;
        cout << "1. додати запис" << endl;
        cout << "2. показати всі записи" << endl;
        cout << "3. пошук за фірмою" << endl;
        cout << "4. пошук за власником" << endl;
        cout << "5. пошук за телефоном" << endl;
        cout << "6. пошук за діяльністю" << endl;
        cout << "0. вихід" << endl;
        cout << "вибір: ";
        cin >> choice;

        vector<Dovidnyk> zapisany;

        switch (choice) {
        case 1:
            add_record(filename);
            break;
        case 2:
            read_all(filename, zapisany);
            for (const auto& z : zapisany) z.display();
            break;
        case 3: {
            string znach;
            cin.ignore();
            cout << "Nazva firmy: ";
            getline(cin, znach);
            read_all(filename, zapisany);
            search_records(zapisany, znach, 1);
            break;
        }
        case 4: {
            string znach;
            cin.ignore();
            cout << "власник: ";
            getline(cin, znach);
            read_all(filename, zapisany);
            search_records(zapisany, znach, 2);
            break;
        }
        case 5: {
            string znach;
            cin.ignore();
            cout << "телфон: ";
            getline(cin, znach);
            read_all(filename, zapisany);
            search_records(zapisany, znach, 3);
            break;
        }
        case 6: {
            string znach;
            cin.ignore();
            cout << "рід діяльностi: ";
            getline(cin, znach);
            read_all(filename, zapisany);
            search_records(zapisany, znach, 4);
            break;
        }
        case 0:
            cout << "вихід з програми" << endl;
            break;
        default:
            cout << "спробуйте зе раз" << endl;
        }

    } while (choice != 0);

    return 0;
}
