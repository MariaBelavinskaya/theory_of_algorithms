#include <iostream>
#include <ctime>
#include <random>
#include <cmath>
using namespace std;

bool ferma(long long x);
bool MillerRabinTest(long n, int k);
bool SoloveiShtrassenTest(long n, int k);
int Jacobi(int a, int n);

int main()
{
    setlocale(LC_ALL, "Russian");
    auto n = 0;
    auto choice = 0;
    auto choice2 = 0;
    auto k = 0;
    cout << "Введите число, которое надо проверить: " << endl;
    cin >> n;
    cout << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Выберите способ, которым хотите реализовать проверку числа:" << endl << "1.Тест Ферма" << endl;
        cout << "2.Тест Соловея-Штрассена" << endl << "3.Тест Миллера-Рабина" << endl;
        cin >> choice;
        if (choice == 1) {
            if (ferma(n) == true) {
                cout << "Число простое" << endl;
            }
            else {
                cout << "Число не простое" << endl;
            }
        }

        if (choice == 2) {
            cout << "Введите количество проверок k: " << endl;
            cin >> k;
            cout << endl;
            if (SoloveiShtrassenTest(n, k) == true) {
                cout << "Число простое" << endl;
            }
            else {
                cout << "Число не простое" << endl;
            }
        }

        if (choice == 3) {
            cout << "Введите количество проверок k: " << endl;
            cin >> k;
            cout << endl;
            if (MillerRabinTest(n, k) == true) {
                cout << "Число простое" << endl;
            }
            else {
                cout << "Число не простое" << endl;
            }
        }
        cout << "Хотите ли вы проверить еще одним методом?" << endl << "1.Да" << endl << "2.Нет" << endl;
        cin >> choice2;
        cout << endl;
        if (choice2 == 2) {
            break;
        }
    }
    return 0;
}

long long gcd(long long a, long long b) { 
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
long long mul(long long a, long long b, long long m) { 
    if (b == 1)
        return a;
    if (b % 2 == 0) {
        long long t = mul(a, b / 2, m);
        return (2 * t) % m;
    }
    return (mul(a, b - 1, m) + a) % m;
}
long long pows(long long a, long long b, long long m) { 
    if (b == 0)
        return 1;
    if (b % 2 == 0) {
        long long t = pows(a, b / 2, m);
        return mul(t, t, m) % m;
    }
    return (mul(pows(a, b - 1, m), a, m)) % m;
}
bool ferma(long long x) {
    if (x < 2)
        return false;
    if (x == 2)
        return true;
    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
        long long a = (rand() % (x - 2)) + 2;
        if (gcd(a, x) != 1)
            return false;
        if (pows(a, x - 1, x) != 1)
            return false;
    }
    return true;
}
bool MillerRabinTest(long n, int k) {  

    if (n == 2 || n == 3)
        return true;

    
    if (n < 2 || n % 2 == 0)
        return false;

    
    long t = n - 1;

    int s = 0;

    while (t % 2 == 0)
    {
        t /= 2;
        s += 1;
    }

    
    for (int i = 0; i < k; i++)
    {
       
        random_device rd;

        mt19937 gen(rd());

        std::uniform_int_distribution<> uniformIntDistribution(2, n - 2);

        long a;

        do
        {
            a = uniformIntDistribution(gen);
        } while (a < 2 || a >= n - 2);

        long x = pows(a, t, n);

        
        if (x == 1 || x == n - 1)
            continue;

        
        for (int r = 1; r < s; r++)
        {
          
            x = pows(x, 2, n);

            
            if (x == 1)
                return false;

            if (x == n - 1)
                break;
        }

        if (x != n - 1)
            return false;
    }

    
    return true;
}
bool SoloveiShtrassenTest(long n, int k) {   
    auto b = 0;
    auto c = 0;

    if (n == 2 || n == 3)
        return true;

    if (n < 2 || n % 2 == 0)
        return false;


   
    for (int i = 0; i < k; i++)
    {
       
        random_device rd;

        mt19937 gen(rd());

        std::uniform_int_distribution<> uniformIntDistribution(2, n - 1);

        int a;

        a = uniformIntDistribution(gen);

        if (gcd(n, a) > 1) { 
            return false;
        }

        b = (n - 1) / 2;
        long x = pows(a, b, n);


        if (x == Jacobi(a, n)) {
            return true;
        }
        else {
            return false;
        }
    }

    
    return true;
}

int Jacobi(int a, int n) {
    auto k = 0;
    auto s = 1;
    auto a1 = a;
    if (a == 0) {
        return 0;
    }
    if (a == 1) {
        return 1;
    }
    while (a1 % 2 == 0) {
        k += 1;
        a1 = a1 / 2;
    }
    if (k % 2 == 0) {
        s = 1;
    }
    else if ((n % 8 == 1) || (n % 8 == 7)) {
        s = 1;
    }
    else {
        s = -1;
    }
    if ((n % 4 == 3) && (a1 % 4 == 3)) {
        s = -s;
    }
    if (a1 == 1) {
        return s;
    }
    else {
        return Jacobi((n % a1), a1);
    }
}
