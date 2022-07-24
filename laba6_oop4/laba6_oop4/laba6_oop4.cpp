#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include<Windows.h>
#include <stack>
#include<queue>
using namespace std;


class Medicine{

public:
	string title;
	int day;
	int month;
	int year;
	Medicine() : title("Антигриппин"), day(1), month(1), year(2024){}
	Medicine(string t, int d, int m, int y) : title(t), day(d), month(m), year(y) {}
	Medicine(const Medicine& m) {
		this->title = m.title;
		this->day = m.day;
		this->month = m.month;
		this->year = m.year;
	}
	void SetTitle(string t) { title = t; }
	void SetDay(int d) { day = d; }
	void SetMonth(int m) { month = m; }
	void SetYear(int y) { year = y; }
	string GetTitle() { return title; }
	int GetDay() { return day; }
	int GetMonth() { return month; }
	int GetYear() { return year; }
	void operator=(const Medicine& newMed) {
		this->title = newMed.title;
		this->day = newMed.day;
		this->month = newMed.month;
		this->year = newMed.year;
	}
	void ShowDate() {
		cout << day << "-" << month << "-" << year;
	}
	//friend ostream& operator<<(ostream& s, Medicine& med);

};
//перегрузка оператора < 
bool operator< (const Medicine& med1, const Medicine& med2) {
	return (med1.day + (med1.month) * 30 + (med1.year) * 365) > (med2.day + (med2.month) * 30 + (med2.year) * 365);
}
bool operator> (const Medicine& med1, const Medicine& med2) {
	return (med1.day + (med1.month) * 30 + (med1.year) * 365) > (med2.day + (med2.month) * 30 + (med2.year) * 365);
}

class Order {
private:
	Medicine medicine;
	string surname;
public:
	Order() : medicine(), surname("Котягова") {}
	Order(Medicine& m, string s) : medicine(m), surname(s){}
	Order(const Order& order) {
		this->medicine = order.medicine;
		this->surname = order.surname;
	}
	void SetMedicine(Medicine& m) { medicine = m; }
	void SetSurname(string s) { surname = s; }
	Medicine& GetMedicine() { return medicine; }
	string GetSurname() { return surname; }
};
class CovidVaccine : public Medicine{
private:
	bool taken;
	int number;
public:
	CovidVaccine() : taken(false), Medicine("CovidVaccine", 1,1,2025), number(111){}
	CovidVaccine(int n) : taken(false), Medicine("CovidVaccine", 1, 1, 2025), number(n) {}
	bool isTaken() { return taken; }
	void TakeVaccine() { taken = true; }
	void SetNumber(int n) { number = n; }
	int GetNumber() { return number; }
};

void ShowMedicines(priority_queue<Medicine> medicines) {
	cout << "+---------------------------------+" << endl;
	cout << setw(20) << "Название препарата" << "|" << "Срок годности" << "|" << endl;
	cout << "+---------------------------------+" << endl;

	while (!medicines.empty()) {
		cout << setw(20) << medicines.top().title << "|   " 
			<< (medicines.top().day > 9 ? "" : "0") << medicines.top().day << "."
			<< (medicines.top().month > 9 ? "" : "0") << medicines.top().month << "."
			<< medicines.top().year
			<< "|" << "\n";
		medicines.pop();
	}
	cout << "+---------------------------------+" << endl;
}

void ShowOrders(queue<Order> orders) {
	cout << "+----------------------------------------+" << endl;
	cout << setw(20) << "Название препарата" << "|" << setw(20)<< "Фамилия заказчика" << "|" << endl;
	cout << "+----------------------------------------+" << endl;

	while (!orders.empty()) {
		cout << setw(20) << orders.front().GetMedicine().GetTitle() << "|"
			<<setw(20)<<orders.front().GetSurname()
			<< "|" << "\n";
		orders.pop();
	}
	cout << "+----------------------------------------+" << endl;
}

void ShowVaccines(stack<CovidVaccine> vaccines) {
	cout << "+----------------------------------------+" << endl;
	cout << setw(20) << "Вакцина" << "|" << setw(20) << "Номер вакцины" << "|" << endl;
	cout << "+----------------------------------------+" << endl;

	while (!vaccines.empty()) {
		cout << setw(20) << vaccines.top().title  << "|"
			<< setw(20) << vaccines.top().GetNumber()
			<< "|" << "\n";
		vaccines.pop();
	}
	cout << "+----------------------------------------+" << endl;
}

void AddMedicine(priority_queue<Medicine>& medicines) {
	cout << "Введите название препарата: ";
	string title;
	int d, m, y;
	cin >> title;
	cout << "Введите срок годности препарата: ";
	cin >> d;
	cin >> m;
	cin >> y;
	medicines.push(Medicine(title, d, m, y));
}

void AddOrder(queue<Order>& orders, priority_queue<Medicine> medicines){
	ShowMedicines(medicines);
	cout << "Выберите препарат: ";
	string title;
	cin >> title;
	while (!medicines.empty()) {
		if (medicines.top().title == title) break;
		medicines.pop();
	}
	if (medicines.empty()) cout << "Препарат не был найден" << endl;
	else {
		cout << "Введите фамилию заказчика: ";
		string surname;
		cin >> surname;
		Medicine m = medicines.top();
		orders.push(Order(m, surname));
	}
}

void AddVaccine(stack<CovidVaccine>& vaccines) {
	cout << "Введите номер вакцины: ";
	int num;
	cin >> num;
	vaccines.push(CovidVaccine(num));
}

void EditMedicine(priority_queue<Medicine>& medicines, priority_queue<Medicine> meds) {
	ShowMedicines(meds);
	priority_queue < Medicine, vector<Medicine>, less<vector<Medicine>::value_type>> medicinesBuffer;
	cout << "Выберите препарат: ";
	string title;
	cin >> title;
	while (!meds.empty()) {
		if (meds.top().title == title) break;
		medicinesBuffer.push(meds.top());
		meds.pop();
	}
	if (meds.empty()) cout << "Препарат не был найден" << endl;
	else {
		Medicine m = meds.top();
		cout << "Выберите поле для редактирования:" << endl;
		cout << "1. Название" << endl;
		cout << "2. День из срока годности" << endl;
		cout << "3. Месяц из срока годности" << endl;
		cout << "4. Год из срока годности" << endl;
		cout << "5. Выход" << endl;
		int menu;
		int working = 1;
		while (working) {
			cin >> menu;
			switch (menu)
			{
			case 1: {
				cout << "Введите новое название: ";
				string title;
				cin >> title;
				m.SetTitle(title);
				working = 0;
				break;
			}
			case 2: {
				cout << "Введите новый день: ";
				int d;
				cin >> d;
				m.SetDay(d);
				working = 0;
				break;
			}
			case 3: {
				cout << "Введите новый месяц: ";
				int mo;
				cin >> mo;
				m.SetMonth(mo);
				working = 0;
				break;
			}
			case 4: {
				cout << "Введите новый год: ";
				int y;
				cin >> y;
				m.SetYear(y);
				working = 0;
				working = 0;
				break;
			}
			default: {
				working = 0;
				break;
			}
			}
		}
		medicinesBuffer.push(m);
		meds.pop();
		while (!meds.empty()) {
			medicinesBuffer.push(meds.top());
			meds.pop();
		}
		while (!medicines.empty()) {
			medicines.pop();
		}
		while (!medicinesBuffer.empty()) {
			Medicine m = medicinesBuffer.top();
			medicines.push(m);
			medicinesBuffer.pop();
		}
	}
}

void EditOrder(queue<Order>& orders, queue<Order> ord, priority_queue<Medicine> medicines){
	ShowOrders(orders);
	cout << "Введите фамилию заказчика: ";
	string surname;
	cin >> surname;
	queue<Order> ordersBuffer;
	while (!ord.empty()) {
		if (ord.front().GetSurname() == surname) break;
		ordersBuffer.push(ord.front());
		ord.pop();
	}
	if (ord.empty()) cout << "Заказ не был найден" << endl;
	else {
		Order orderToEdit = ord.front();
		cout << "Выберите поле для редактирования:" << endl;
		cout << "1. Фамилия" << endl;
		cout << "2. Препарат" << endl;
		cout << "3. Выход" << endl;
		int menu;
		int working = 1;
		while (working) {
			cin >> menu;
			switch (menu)
			{
			case 1: {
				cout << "Введите новую фамилию: ";
				string sur;
				cin >> sur;
				orderToEdit.SetSurname(sur);
				working = 0;
				break;
			}
			case 2: {
				ShowMedicines(medicines);
				cout << "Выберите препарат: ";
				string title;
				cin >> title;
				while (!medicines.empty()) {
					if (medicines.top().title == title) break;
					medicines.pop();
				}
				if (medicines.empty()) cout << "Препарат не был найден" << endl;
				else {
					Medicine med = medicines.top();
					orderToEdit.SetMedicine(med);
				}
				working = 0;
				break;
			}
			default: {
				working = 0;
				break;
			}
			}
		}
		ordersBuffer.push(orderToEdit);
		ord.pop();
		while (!ord.empty()) {
			ordersBuffer.push(ord.front());
			ord.pop();
		}
		while (!orders.empty()) {
			orders.pop();
		}
		while (!ordersBuffer.empty()) {
			Order b = ordersBuffer.front();
			orders.push(b);
			ordersBuffer.pop();
		}
	}
}

void EditVaccine(stack<CovidVaccine>& vaccines, stack<CovidVaccine> vac){
	ShowVaccines(vaccines);
	stack<CovidVaccine> vacccinesBuffer;
	cout << "Введите номер вакцины: ";
	int num;
	cin >> num;
	while (!vac.empty()) {
		if (vac.top().GetNumber()==num) break;
		vacccinesBuffer.push(vac.top());
		vac.pop();
	}
	if (vac.empty()) cout << "Вакцина не была найдена" << endl;
	else {
		cout << "Введите новый номер: ";
		int nd;
		cin >> nd;
		vac.top().SetNumber(nd);
		while (!vac.empty()) {
			vacccinesBuffer.push(vac.top());
			vac.pop();
		}
		while (!vaccines.empty()) {
			vaccines.pop();
		}
		while (!vacccinesBuffer.empty()) {
			CovidVaccine m = vacccinesBuffer.top();
			vaccines.push(m);
			vacccinesBuffer.pop();
		}
	}
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	priority_queue < Medicine, vector<Medicine>, less<vector<Medicine>::value_type>> medicines;
	queue<Order> orders;
	stack<CovidVaccine> vaccines;

	Medicine m1("Панангин", 2, 3, 2022);//1
	medicines.push(m1);//1
	medicines.push(Medicine());//2
	medicines.push(Medicine("Стопдиар", 12, 12, 2025));//3
	Medicine m4("Ношпа", 24, 3, 2024);
	medicines.push(m4);//4
	Medicine m5("Анальгин", 15, 1, 2023);
	medicines.push(m5);
	Medicine m6("Ирбесартан", 20, 9, 2025);
	medicines.push(m6);
	Medicine m7("Логимакс", 1, 2, 2023);
	medicines.push(m7);//7

	orders.push(Order(m1, "Литвинов"));
	orders.push(Order(m5, "Мороз"));
	orders.push(Order(m6, "Ковалева"));
	orders.push(Order(m4, "Устинова"));

	vaccines.push(CovidVaccine(146));
	vaccines.push(CovidVaccine(456));
	vaccines.push(CovidVaccine(767));
	vaccines.push(CovidVaccine(323));
	vaccines.push(CovidVaccine(988));

	int menu;
	while (true)
	{
		cout << "+-------------------------------------------------------------+" << endl;
		cout << "| 1. Вывести список препаратов                                |" << endl;
		cout << "| 2. Вывести список заказов                                   |" << endl;
		cout << "| 3. Вывести вакцины                                          |" << endl;
		cout << "| 4. Добавить препарат                                        |" << endl;
		cout << "| 5. Добавить заказ                                           |" << endl;
		cout << "| 6. Добавить вакцину                                         |" << endl;
		cout << "| 7. Использовать вакцину                                     |" << endl;
		cout << "| 8. Редактировать препарат                                   |" << endl;
		cout << "| 9. Редактировать заказ                                      |" << endl;
		cout << "| 10. Редактировать вакцину                                   |" << endl;
		cout << "| 11. Выход                                                   |" << endl;
		cout << "+-------------------------------------------------------------+" << endl;
		cin >> menu;
		if (cin.fail()) {//если есть ошибка
			cin.clear();//Очистить биты ошибок
			cout << "Неправильный ввод данных\n";
		}

		switch (menu)
		{
		case 1: {
			ShowMedicines(medicines);
			break;
		}
		case 2: {
			ShowOrders(orders);
			break;
		}
		case 3: {
			ShowVaccines(vaccines);
			break;
		}
		case 4:
		{
			AddMedicine(medicines);
			break;
		}
		case 5:
		{
			AddOrder(orders, medicines);
			break;
		}
		case 6: {
			AddVaccine(vaccines);
			break;
		}
		case 7: {
			vaccines.pop();
			break;
		}
		case 8: {
			EditMedicine(medicines, medicines);
			break;
		}
		case 9: {
			EditOrder(orders, orders, medicines);
			break;
		}
		case 10: {
			EditVaccine(vaccines, vaccines);
			break;
		}
		default:
		{
			return 0;
		}
		}
		system("pause");
		system("cls");
	}
}