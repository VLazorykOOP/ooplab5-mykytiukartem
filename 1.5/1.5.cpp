#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Quadrilateral {
protected:
    double a, b, c, d;
    static int count;

public:
    Quadrilateral(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {
        cout << "[Quadrilateral] Створено об'єкт.\n";
        count++;
    }

    virtual ~Quadrilateral() {
        cout << "[Quadrilateral] Знищено об'єкт.\n";
        count--;
    }

    static int getCount() {
        return count;
    }

    virtual double getPerimeter() const {
        return a + b + c + d;
    }

    virtual double getArea() const {
        return 0; // Площа загального чотирикутника невідома
    }

    virtual void print() const {
        cout << "Чотирикутник зі сторонами: " << a << ", " << b << ", " << c << ", " << d << endl;
    }
};

int Quadrilateral::count = 0;

class Rectangle : public Quadrilateral {
protected:
    double width, height;

public:
    Rectangle(double width, double height) : Quadrilateral(width, height, width, height), width(width), height(height) {
        cout << "[Rectangle] Створено об'єкт.\n";
    }

    ~Rectangle() override {
        cout << "[Rectangle] Знищено об'єкт.\n";
    }

    double getArea() const override {
        return width * height;
    }

    double getPerimeter() const override {
        return 2 * (width + height);
    }

    void print() const override {
        cout << "Прямокутник: ширина = " << width << ", висота = " << height << endl;
    }
};

class Square : public Rectangle {
public:
    Square(double side) : Rectangle(side, side) {
        cout << "[Square] Створено об'єкт.\n";
    }

    ~Square() override {
        cout << "[Square] Знищено об'єкт.\n";
    }

    void print() const override {
        cout << "Квадрат зі стороною: " << width << endl;
    }
};

void inputFromKeyboard() {
    double w, h;
    cout << "Введіть ширину і висоту прямокутника: ";
    cin >> w >> h;
    Rectangle r(w, h);
    r.print();
    cout << "Площа: " << r.getArea() << ", Периметр: " << r.getPerimeter() << "\n\n";
}

void inputFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Не вдалося відкрити файл.\n";
        return;
    }
    double w, h;
    fin >> w >> h;
    Rectangle r(w, h);
    r.print();
    cout << "Площа: " << r.getArea() << ", Периметр: " << r.getPerimeter() << "\n\n";
    fin.close();
}

void inputRandom() {
    srand(time(nullptr));
    double side = rand() % 20 + 1;
    Square s(side);
    s.print();
    cout << "Площа: " << s.getArea() << ", Периметр: " << s.getPerimeter() << "\n\n";
}

int main() {
    cout << "\n--- Тестування чотирикутників ---\n";
    Quadrilateral* q = new Quadrilateral(1, 2, 3, 4);
    q->print();
    cout << "Периметр: " << q->getPerimeter() << "\n\n";
    delete q;

    cout << "--- Ввід з клавіатури ---\n";
    inputFromKeyboard();

    cout << "--- Ввід з файлу ---\n";
    inputFromFile("data.txt");

    cout << "--- Випадкове створення квадрата ---\n";
    inputRandom();

    cout << "Загальна кількість об'єктів: " << Quadrilateral::getCount() << endl;

    return 0;
}