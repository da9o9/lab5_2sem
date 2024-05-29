#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>
#include <string>


// Класс Employee
class Employee {
public:
    std::string fullName;
    std::string date;
    std::string position;
    double oklad;

    // Конструкторы
    Employee() : fullName(""), date(""), position(""), oklad(0.0) {}
    Employee(const std::string& fn, const std::string& hd, const std::string& pos, double bs)
        : fullName(fn), date(hd), position(pos), oklad(bs) {}

    // Конструктор копирования
    Employee(const Employee& other)
        : fullName(other.fullName), date(other.date), position(other.position), oklad(other.oklad) {}

    // Конструктор перемещения
    Employee(Employee&& other) noexcept
        : fullName(std::move(other.fullName)), date(std::move(other.date)), position(std::move(other.position)), oklad(other.oklad) {
        other.oklad = 0.0;
    }

    // Оператор присваивания с копированием
    Employee& operator=(const Employee& other) {
        if (this == &other) return *this;
        fullName = other.fullName;
        date = other.date;
        position = other.position;
        oklad = other.oklad;
        return *this;
    }

    // Оператор присваивания с перемещением
    Employee& operator=(Employee&& other) noexcept {
        if (this == &other) return *this;
        fullName = std::move(other.fullName);
        date = std::move(other.date);
        position = std::move(other.position);
        oklad = other.oklad;
        other.oklad = 0.0;
        return *this;
    }

    // Перегруженная операция вставки в поток
    friend std::ostream& operator<<(std::ostream& os, const Employee& emp) {
        os << emp.fullName << ", " << emp.date << ", " << emp.position << ", " << emp.oklad;
        return os;
    }

    // Операторы сравнения для std::set
    bool operator<(const Employee& other) const {
        return oklad < other.oklad;
    }

    bool operator==(const Employee& other) const {
        return fullName == other.fullName && date == other.date && position == other.position && oklad == other.oklad;
    }
};

// Специализация std::hash для класса Employee
namespace std {
    template<>
    struct hash<Employee> {
        std::size_t operator()(const Employee& emp) const {
            return hash<std::string>()(emp.fullName) ^ hash<std::string>()(emp.date) ^ hash<std::string>()(emp.position) ^ hash<double>()(emp.oklad);
        }
    };
}

// Функция для чтения данных из файла и заполнения контейнера
void readFromFile(const std::string& filename, std::list<Employee>& employees) {
    std::ifstream infile(filename);
    std::string fullName, date, position;
    double oklad;

    while (infile >> std::ws, std::getline(infile, fullName, ',')) {
        std::getline(infile, date, ',');
        std::getline(infile, position, ',');
        infile >> oklad;
        infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем оставшуюся часть строки
        employees.emplace_back(fullName, date, position, oklad);
    }
}

// Функция для записи данных в файл
void writeToFile(const std::string& filename, const std::list<Employee>& employees, const std::vector<Employee>& employeesVec, const std::set<Employee>& employeeSet, const std::unordered_set<Employee>& employeeUnorderedSet) {
    std::ofstream outfile(filename);

    // Исходный контейнер
    outfile << "Исходный контейнер (list):" << std::endl;
    for (const auto& emp : employees) {
        outfile << emp << std::endl;
    }

    // Отсортированный контейнер
    outfile << "\nОтсортированный контейнер (list):" << std::endl;
    for (const auto& emp : employees) {
        outfile << emp << std::endl;
    }
    // Скопированный контейнер
        outfile << "\nСкопированный контейнер (vector):" << std::endl;
        for (const auto& emp : employeesVec) {
            outfile << emp << std::endl;
        }

        // Контейнер std::set
        outfile << "\nКонтейнер std::set:" << std::endl;
        for (const auto& emp : employeeSet) {
            outfile << emp << std::endl;
        }

        // Контейнер std::unordered_set
        outfile << "\nКонтейнер std::unordered_set:" << std::endl;
        for (const auto& emp : employeeUnorderedSet) {
            outfile << emp << std::endl;
        }
    }

    int main() {
        // Создаем исходный контейнер list
        std::list<Employee> employees;

        // Читаем данные из файла input.txt
        readFromFile("input.txt", employees);

        // Сортируем контейнер по окладу
        employees.sort([](const Employee& a, const Employee& b) {
            return a.oklad < b.oklad;
        });

        // Копируем данные из list в vector
        std::vector<Employee> employeesVec;
        std::copy(employees.begin(), employees.end(), std::back_inserter(employeesVec));

        // Копируем данные из list в set и unordered_set
        std::set<Employee> employeeSet(employees.begin(), employees.end());
        std::unordered_set<Employee> employeeUnorderedSet(employees.begin(), employees.end());

        // Записываем данные в файл output.txt
        writeToFile("output.txt", employees, employeesVec, employeeSet, employeeUnorderedSet);

        return 0;
    }


