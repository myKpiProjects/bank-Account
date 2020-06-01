#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace std;

// класс счёта
class Account {
private:
  // поле с балансом
  double balance;

public:
  // конструктор по умолчанию
  //   (нужен для создания массива)
  Account() {
    this->balance = 0.0;
  }

  // конструктор с заданным изначальным балансом
  Account(double balance) {
    // если баланс < 0 -- выводим сообщение
    //   и скидываем его к 0
    if (balance < 0.0) {
      cout << "invalid balance, setting to 0";
      cout << endl;
      balance = 0.0;
    }
    this->balance = balance;
  }

  // перегрузка оператора +
  //   добавляем сумму к балансу
  Account& operator+(double d) {
    this->balance += d;
    return *this;
  }

  // перегрузка оператора -
  //   отнимаем сумму от баланса
  Account& operator-(double d) {
    // если сумма < баланса -- выводим сообщение
    //   и ничего не делаем
    if (d <= balance) {
      this->balance -= d;
    } else {
      cout << "required amount exceeds the balance";
      cout << endl;
    }
    return *this;
  }

  // метода вывода баланса
  void printBalance() {
    cout << "balance = " << balance << endl;
  }

  // метод получения баланса
  double getBalance() {
    return balance;
  }
};

// вненяя функция подсчёта общей суммы
double totalBalance(Account accounts[], int n) {
  double total = 0.0;
  for (int i = 0; i < n; i++) {
    total += accounts[i].getBalance();
  }
  return total;
}

int main() {
  srand(time(NULL));

  cout << "hello world" << endl;

  const int nAccounts = 5;
  Account accounts[nAccounts];
  cout << "initial:" << endl;
  for (int i = 0; i < nAccounts; i++) {
    accounts[i] = Account(100 + rand() % 900);
    cout << "account #" << (i + 1) << ": ";
    accounts[i].printBalance();
  }

  while (true) {
    cout << endl;
    cout << "available options:" << endl;
    cout << "1) give money" << endl;
    cout << "2) take money" << endl;
    cout << "3) calc total" << endl;
    cout << "5) exit" << endl;
    cout << endl;

    int opt;
    cout << "i want to: ";
    cin >> opt;

    // оборачиваем логику в try-catch,
    //   чтобы ловить исключения
    try {
      switch (opt) {
      case 1:
        {
          int k;
          cout << "enter account id (1 - 5): ";
          cin >> k;
          if (k < 1 || k > nAccounts) {
            throw logic_error("invalid account id");
          }

          double d;
          cout << "enter amount: ";
          cin >> d;
          if (d < 0.0) {
            throw logic_error("amount < 0");
          }

          accounts[k - 1] + d;
          cout << "Done." << endl;
          accounts[k - 1].printBalance();
        }
        break;
      case 2:
        {
          int k;
          cout << "enter account id (1 - 5): ";
          cin >> k;
          if (k < 1 || k > nAccounts) {
            throw logic_error("invalid account id");
          }

          double d;
          cout << "enter amount: ";
          cin >> d;

          accounts[k - 1] - d;
          cout << "Done." << endl;
          accounts[k - 1].printBalance();
        }
        break;
      case 3:
        {
          double total = totalBalance(accounts, nAccounts);
          cout << "total balance = " << total << endl;
        }
        break;
      case 5:
        cout << "bye!" << endl;
        return 0;
      }
    } catch (exception& e) {
      // выводим информацию об ошибке
      cout << endl;
      cout << endl;
      cout << "error: " << e.what() << endl;
    }
  }

  return 0;
}
