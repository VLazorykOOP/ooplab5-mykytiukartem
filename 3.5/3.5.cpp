#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cctype>

class String {
protected:
    char* data;
    static int count;
public:
    // Конструктор за замовчуванням
    String() {
        data = new char[1];
        data[0] = '\0';
        ++count;
        std::cout << "Об'єкт String створено. Всього: " << count << "\n";
    }

    // Конструктор з const char*
    String(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
        ++count;
        std::cout << "Об'єкт String створено з const char*. Всього: " << count << "\n";
    }

    // Конструктор копіювання
    String(const String& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
        ++count;
        std::cout << "Об'єкт String скопійовано. Всього: " << count << "\n";
    }

    // Деструктор
    virtual ~String() {
        delete[] data;
        --count;
        std::cout << "Об'єкт String знищено. Залишилось: " << count << "\n";
    }

    // Оператор присвоювання
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        }
        std::cout << "Викликано оператор присвоювання.\n";
        return *this;
    }

    // Введення з клавіатури
    virtual void inputFromKeyboard() {
        char buffer[256];
        std::cout << "Введіть рядок: ";
        std::cin.getline(buffer, 256);
        delete[] data;
        data = new char[strlen(buffer) + 1];
        strcpy(data, buffer);
    }

    // Зчитування з файлу
    virtual void inputFromFile(std::ifstream& file) {
        char buffer[256];
        if (file.getline(buffer, 256)) {
            delete[] data;
            data = new char[strlen(buffer) + 1];
            strcpy(data, buffer);
        }
    }

    // Випадкова генерація
    virtual void inputRandom() {
        int len = rand() % 10 + 1;
        delete[] data;
        data = new char[len + 1];
        for (int i = 0; i < len; ++i)
            data[i] = 'a' + rand() % 26;
        data[len] = '\0';
    }

    // Вивід
    virtual void print() const {
        std::cout << "Рядок: " << data << "\n";
    }

    // Перевантаження оператора виводу
    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        os << s.data;
        return os;
    }

    // Перевантаження оператора введення
    friend std::istream& operator>>(std::istream& is, String& s) {
        char buffer[256];
        is.getline(buffer, 256);
        delete[] s.data;
        s.data = new char[strlen(buffer) + 1];
        strcpy(s.data, buffer);
        return is;
    }
};

int String::count = 0;

class DigitString : public String {
public:
    // Конструктор за замовчуванням
    DigitString() : String() {
        std::cout << "Викликано конструктор DigitString за замовчуванням.\n";
    }

    // Конструктор з const char*
    DigitString(const char* str) {
        if (isDigitsOnly(str)) {
            data = new char[strlen(str) + 1];
            strcpy(data, str);
        } else {
            data = new char[1];
            data[0] = '\0';
        }
        ++count;
        std::cout << "Об'єкт DigitString створено.\n";
    }

    // Конструктор копіювання
    DigitString(const DigitString& other) : String(other) {
        std::cout << "DigitString скопійовано.\n";
    }

    // Деструктор
    ~DigitString() override {
        std::cout << "DigitString знищено.\n";
    }

    // Оператор присвоювання
    DigitString& operator=(const DigitString& other) {
        String::operator=(other);
        std::cout << "Викликано присвоювання DigitString.\n";
        return *this;
    }

    // Перевірка чи всі символи — цифри
    bool isDigitsOnly(const char* str) {
        for (int i = 0; str[i]; ++i)
            if (!isdigit(str[i])) return false;
        return true;
    }

    // Введення з клавіатури з перевіркою
    void inputFromKeyboard() override {
        char buffer[256];
        std::cout << "Введіть рядок з цифр: ";
        std::cin.getline(buffer, 256);
        if (isDigitsOnly(buffer)) {
            delete[] data;
            data = new char[strlen(buffer) + 1];
            strcpy(data, buffer);
        } else {
            std::cout << "Недопустимий рядок. Дані не змінено.\n";
        }
    }

    // Зчитування з файлу з перевіркою
    void inputFromFile(std::ifstream& file) override {
        char buffer[256];
        if (file.getline(buffer, 256) && isDigitsOnly(buffer)) {
            delete[] data;
            data = new char[strlen(buffer) + 1];
            strcpy(data, buffer);
        } else {
            std::cout << "Недопустимі дані у файлі.\n";
        }
    }

    // Випадкова генерація числового рядка
    void inputRandom() override {
        int len = rand() % 10 + 1;
        delete[] data;
        data = new char[len + 1];
        for (int i = 0; i < len; ++i)
            data[i] = '0' + rand() % 10;
        data[len] = '\0';
    }

    // Вивід
    void print() const override {
        std::cout << "DigitString: " << data << "\n";
    }
};

// Тестова функція
void testClasses() {
    std::cout << "\n--- Тестування класів ---\n";
    String s1("Привіт");
    s1.print();

    String s2;
    s2.inputRandom();
    s2.print();

    DigitString d1("12345");
    d1.print();

    DigitString d2;
    d2.inputRandom();
    d2.print();

    String* ptr = new DigitString("67890");
    ptr->print();
    delete ptr;
}

// Головна функція
int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    testClasses();

    std::cout << "\n--- Введення з клавіатури ---\n";
    String userString;
    userString.inputFromKeyboard();
    userString.print();

    DigitString userDigitString;
    userDigitString.inputFromKeyboard();
    userDigitString.print();

    std::ifstream file("input.txt");
    if (file) {
        std::cout << "\n--- Зчитування з файлу ---\n";
        String s3;
        s3.inputFromFile(file);
        s3.print();

        DigitString d3;
        d3.inputFromFile(file);
        d3.print();
    } else {
        std::cout << "Файл 'input.txt' не знайдено.\n";
    }

    return 0;
}