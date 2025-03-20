//Написать программу класса Рациональных чисел, которая выводит сложение, 
//вычитание, умножение и деление рациональных чисел и сокращение дроби. + Создать матрицу с 
//рациональными числами и их операциями над ними.

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
class rational {
public:
    rational() : numerator(0), denominator(1) {};
    rational(int num, int denom) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero.");
        }
        norm();
    };
    rational input_rational();
    rational add(const rational& b) const;
    rational operator+(const rational& b) const;
    rational operator-(const rational& b) const;
    rational operator*(const rational& b) const;
    rational operator/(const rational& b) const;
    rational sub(const rational& b) const;
    rational mul(const rational& b) const;
    rational div(const rational& b) const;
    rational reverse() const;
    void norm();
    int gcd(int a, int b); //Вычисление НОД по алгоритму Евклида
    void show_rational();
private:
    int numerator;
    int denominator;
};

// Метод для нормализации дроби
void rational::norm() {
    int commonDivisor = gcd(abs(numerator), abs(denominator));
    numerator /= commonDivisor;
    denominator /= commonDivisor;

    // Убедимся, что знаменатель положительный
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

// Ручная реализация GCD (алгоритм Евклида)
int rational::gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

rational rational::input_rational() {
    cout << "Vvedite numerator: ";
    cin >> numerator;
    cout << "Vvedite denominator: ";
    cin >> denominator;
    return rational(numerator, denominator);
}

rational rational::add(const rational& b) const {
    int newNumerator = numerator * b.denominator + b.numerator * denominator;
    int newDenominator = denominator * b.denominator;
    return rational(newNumerator, newDenominator);
}

rational rational:: operator+(const rational& b) const {
    int newNumerator = numerator * b.denominator + b.numerator * denominator;
    int newDenominator = denominator * b.denominator;
    return rational(newNumerator, newDenominator);
}

rational rational::sub(const rational& b) const {
    int newNumerator = numerator * b.denominator - b.numerator * denominator;
    int newDenominator = denominator * b.denominator;
    return rational(newNumerator, newDenominator);
}

rational rational:: operator-(const rational& b) const {
    int newNumerator = numerator * b.denominator - b.numerator * denominator;
    int newDenominator = denominator * b.denominator;
    return rational(newNumerator, newDenominator);
}

rational rational::mul(const rational& b) const {
    int newNumerator = numerator * b.numerator;
    int newDenominator = denominator * b.denominator;
    return rational(newNumerator, newDenominator);
}
rational rational:: operator*(const rational& b) const {
    int newNumerator = numerator * b.numerator;
    int newDenominator = denominator * b.denominator;
    return rational(newNumerator, newDenominator);
}

rational rational::reverse() const {
    return rational(denominator, numerator);
}

rational rational::div(const rational& b) const {
    rational c = b.reverse();
    return mul(c);
}

rational rational:: operator/(const rational& b) const {
    rational c = b.reverse();
    return mul(c);
}

void rational::show_rational() {
    if (denominator == 1) {
        cout << numerator;
    }
    else {
        cout << numerator << "/" << denominator;
    }
}

class Matrix
{
public:
    Matrix() : rows(0), cols(0) {}
    Matrix(int r, int c) : rows(r), cols(c), data(r, vector<rational>(c)) {}
    void input_matrix();
    void show_matrix();
    Matrix operator+(const Matrix& d) const;
    Matrix operator-(const Matrix& d) const;
    Matrix operator*(const Matrix& d) const;
    Matrix operator/(const Matrix& d) const;
    void set_data(const vector<vector<rational>>& values);
private:
    int rows;
    int cols;
    vector<vector<rational>> data;
};

void Matrix::input_matrix() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int num, denom;
            cout << "Vvedite numerator: ";
            cin >> num;
            cout << "Vvedite denomerator: ";
            cin >> denom;
            data[i][j] = rational(num, denom);
        }
    }
}

void Matrix::show_matrix() {
    cout << "Matrix" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j].show_rational();
            cout << " ";
        }
        cout << endl;
    }
}

Matrix Matrix::operator+(const Matrix& d) const
{
    if (rows != d.rows || cols != d.cols)
    {
        throw invalid_argument("Matrices must have the same dimensions to be added.");
    }
    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            res.data[i][j] = data[i][j] + d.data[i][j];
        }
    }
    return res;
}

Matrix Matrix::operator-(const Matrix& d) const
{
    if (rows != d.rows || cols != d.cols)
    {
        throw invalid_argument("Matrices must have the same dimensions to be added.");
    }
    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            res.data[i][j] = data[i][j] - d.data[i][j];
        }

    }
    return res;
}

Matrix Matrix:: operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw invalid_argument("Invalid matrices dimensions for multiplication");
    }
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            result.data[i][j] = rational(0, 1);
            for (int k = 0; k < cols; k++) {
                result.data[i][j] = result.data[i][j] + (data[i][k] * other.data[k][j]);
            }
        }
    }
    return result;
}

Matrix Matrix:: operator/(const Matrix& other) const {
    if (cols != other.rows) {
        throw invalid_argument("Invalid matrices dimensions for multiplication");
    }
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            result.data[i][j] = rational(0, 1);
            for (int k = 0; k < cols; k++) {
                result.data[i][j] = result.data[i][j] + (data[i][k] * other.data[k][j]);
            }
        }
    }
    return result;
}

void Matrix::set_data(const vector<vector<rational>>& values) {
    if (values.size() != rows || values[0].size() != cols) {
        throw invalid_argument("Invalid dimensions for matrix data.");
    }
    data = values;
}

int main() {
    try {
        rational a(1, 2);
        rational b(1, 4);
        Matrix c(2, 2);
        rational v(1, 3);
        rational w(2, 5);
        vector<vector<rational>> values = {
            {a, b},
            {w, v}
        };
        c.set_data(values); // Установка данных
        c.show_matrix();
        Matrix d(2, 2);
        vector<vector<rational>> values1 = {
            {b, a},
            {b, a}
        };
        d.set_data(values1); // Установка данных
        d.show_matrix();
        Matrix f = c + d;
        cout << "Summa: ";
        f.show_matrix();
        Matrix f2 = c - d;
        cout << "Raznost: ";
        f2.show_matrix();
        Matrix f3 = c * d;
        cout << "Proizvedenie: ";
        f3.show_matrix();
        cout << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    char r;
    cin >> r;
    return 0;
}