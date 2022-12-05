#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>

using namespace std;

struct StudentsList
{
	string fullName = { 0 };
	float gpa = 0;
	string groupNumber = { 0 };
	int familyIncome = 0;
};

StudentsList structureInput(); //для ввода структуры

class List
{
public:
	List();
	~List();

	void pop_front();

	void push_back(StudentsList data);

	void push_front(StudentsList data);

	void push_place();

	int GetSize() { return Size; };

	StudentsList& operator[](const int index);

	bool SaveFile();

	void consoleOutput();

	void subConsolOutput(int index); //вспомогательная для вывода одной структуры

	bool readingFile();

	bool dataSearch();

	void structureChange();

	void pop_record();

	void clear();

private:
	class Node
	{
	public:
		Node* pNext;
		StudentsList data;
		Node(StudentsList data = StudentsList(), Node* pNext = nullptr) { // T data = T() чтобы внутри data небыло мусора 
			this->data = data; //мы ведь когда создаем экземпляр Node в скобках указываем аргументы этого экземпляра.
			this->pNext = pNext; //И чтобы присвоить этим данным какое-то значение надо использовать this а потом данные которые хотим изменить, так как это конструктор
		}
	};

	int Size; //чтобы хранить количество элементов в нашем списке
	Node* head; //чтобы знать существует ли у нас поле. Это очень удобно. Он будет в себе хранить первое поле в списке.
	//это будет целым обьектом. Внутри самого класса. А не выброшанный где-то в памяти
};


List::List() //когда мы только создаем нашь экземпляр класса List в котором хранится Node (поля) мы сразу записываем туда всю информацию
{
	Size = 0;
	head = nullptr;
}

List::~List()
{
	clear();
}

void List::pop_front()
{
	Node* temp = head; //мы берем и копируем наше первое поле, берем его данные, прям из памяти 

	head = head->pNext; //а далее вместо него записываем наше следующее поле

	delete temp;

	Size--;
}

void List::push_back(StudentsList data)
{
	if (head == nullptr)
	{
		head = new Node(data); //так как мы создаем первый элемент нашего List второй аргумент указывать не надо. Ведь это первый сезданный элемент
		//мы записываем сразу в этот указатель новый созданный элемент
	}
	else 
	{
		Node* current = this->head; //это временная переменная для временного перемещения по указателям
		while (current->pNext != nullptr) { //он присвает сначала указатель первого значения head, самого первого поля. Берет у него его значение pNext
			current = current->pNext; //присваивает себе пока значение следующего поля пока не найдет последний 
		}
		current->pNext = new Node(data); //теперь в него записываем новое созданое поле
		//почему это работает
		//это всего лишь указатель на обьект, то есть это не сам элемент а просто указатель на него
		//когда мы изменем значение здесь, то изменеться адрес именного самого элемента в памяти
	}
	Size++;
}

void List::push_front(StudentsList data)
{
	if (head == nullptr)
	{
		head = new Node(data); //так как мы создаем первый элемент нашего List второй аргумент указывать не надо. Ведь это первый сезданный элемент
		//мы записываем сразу в этот указатель новый созданный элемент
	}
	else
	{
		head = new Node(data, head); //так как мы создаем первый элемент нашего List второй аргумент указывать не надо. Ведь это первый сезданный элемент
	}
	Size++;
}

void List::push_place()
{
	int index = 0;
	cout << "На какое место вы хотите записать новые данные\nВвод: ";
	cin >> index;
	StudentsList data = structureInput();
	Node* current = this->head; //это временная переменная для временного перемещения по указателям
	for (int i = 1; i != index - 1 && i <= Size; i++) { //он присвает сначала указатель первого значения head, самого первого поля. Берет у него его значение pNext
		current = current->pNext; //присваивает себе пока значение следующего поля пока не найдет нужный
	}
	//Задача этого цикла быть указателем на элементе перед добавляемым местом
	current->pNext = new Node(data, current->pNext);
	
	Size++;
}

StudentsList& List::operator[](const int index)
{
	int counter = 0;
	Node* current = this->head; //это временная переменная для временного перемещения по указателям
	while (current != nullptr)
	{
		if (counter == index) {
			return current->data;
			//опять же, здесь мы берем просто указатель в котором храниться тот самый элемент и выводим его
		}
		current = current->pNext;
		counter++;
	}
}

bool List::SaveFile()
{
	ofstream fout("MyFile.txt", ios::app);
	if (!fout.is_open() || head == nullptr) return false;

	for (int i = 0; i < Size; i++) {

		for (int j = 0; j < (*this)[i].fullName.length(); j++) {
			if ((*this)[i].fullName[j] == ' ') (*this)[i].fullName.replace(j, 1, "_");
		}
		fout << (*this)[i].fullName << " ";

		fout << (*this)[i].gpa << " ";

		fout << (*this)[i].groupNumber << " ";

		fout << (*this)[i].familyIncome << " ";

		fout << "\n";
	}
	fout.close();
	return true;
}

void List::consoleOutput()
{
	cout << endl << "|               ФИО               |Средний балл|Номер груп.|Доход на человека|\n";
	for (int i = 0; i < Size; i++)
	{
		cout << "|"; 
		cout.width(33); cout << (*this)[i].fullName << "|";

		cout.width(12); cout << (*this)[i].gpa << "|";

		cout.width(11); cout << (*this)[i].groupNumber << "|";

		cout.width(17); cout << (*this)[i].familyIncome << "|" << endl;
	}
}

void List::subConsolOutput(int index)
{
	cout << endl << "|               ФИО               |Средний балл|Номер груп.|Доход на человека|\n";
	cout << "|";
	cout.width(33); cout << (*this)[index].fullName << "|";

	cout.width(12); cout << (*this)[index].gpa << "|";

	cout.width(11); cout << (*this)[index].groupNumber << "|";

	cout.width(17); cout << (*this)[index].familyIncome << "|" << endl;
}

bool List::readingFile()
{
	ifstream fin("MyFile.txt");
	if (!fin.is_open()) return false;

	StudentsList data;
	while (fin)
	{
		fin >> data.fullName;
		for (int i = 0; i < data.fullName.length(); i++) {
			if (data.fullName[i] == '_') data.fullName.replace(i, 1, " ");
		}
		fin >> data.gpa;
		fin >> data.groupNumber;
		fin >> data.familyIncome;
		if (!fin.eof()) { push_back(data); }
	}
	return true;
}

bool List::dataSearch()
{
	string str;
	int temp = 0;
	bool flag = 0;
	cout << "По какому полю вы хотите осуществить поиск?\nВвод: ";

	cout << "		1) Фамилия Имя Отчество\n";
	cout << "		2) Cредний балл студента\n";
	cout << "		3) Номер группы\n";
	cout << "		4) Доход на одного члена семьи\nВвод: ";

	cin >> temp;
	cout << "Введите значение поля\nВвод: ";
	getchar(); getline(cin, str);
	switch (temp)
	{
	case 1:
		for (int i = 0; i < Size; i++)
		{
			if (strcmp((*this)[i].fullName.c_str(), str.c_str()) == 0)
			{
				subConsolOutput(i);
				flag = 1;
			}
		}
		break;

	case 2:
		for (int i = 0; i < Size; i++)
		{
			if ((*this)[i].gpa == stof(str))
			{
				subConsolOutput(i);
				flag = 1;
			}
		}
		break;

	case 3:
		for (int i = 0; i < Size; i++)
		{
			if (strcmp((*this)[i].groupNumber.c_str(), str.c_str()) == 0)
			{
				flag = 1;
				subConsolOutput(i);
			}
		}
		break;

	case 4:
		for (int i = 0; i < Size; i++)
		{
			if ((*this)[i].familyIncome == stoi(str))

			{
				flag = 1;
				subConsolOutput(i);
			}
		}
		break;

	default:
		break;
	}
	if (flag) return 1;
	return 0;
}

void List::structureChange()
{
	cout << endl << "Какую(ой) струкутру(класс) вы хотите изменить\n Ввод: ";
	int i = 0;
	cin >> i; i--;
	(*this)[i] = structureInput();
}

void List::pop_record()
{
	cout << endl << "Какую запись вы хотите удалить? \nВвод: ";
	int index = 0;
	cin >> index; 
	if (index - 1 == 0) 
		pop_front();
	else
	{
		Node* current = this->head, * temp;
		for (int i = 1; i != index - 1 && i <= Size; i++)
		{
			current = current->pNext;
		}
		if (current->pNext->pNext == nullptr) {
			delete current->pNext;
			current->pNext = nullptr;
		}
		else
		{
			temp = current->pNext;
			current->pNext = current->pNext->pNext;
			if (temp != nullptr) delete temp;
		}
		Size--;
	}
}

void List::clear()
{
	while (head != nullptr)
	{
		pop_front();
	}
	Size = 0;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	List lst;

	int menu = 1;
	while (menu)
	{
		cout << endl << "Выберите номер функции" << endl;
		cout << "	1) Добавить новую запись в конец" << endl;
		cout << "	2) Добавить новую запись в начало" << endl;
		cout << "	3) Добавить новую запись на заданное место" << endl;
		cout << "	4) Чтение данных в список из текстового файла" << endl;
		cout << "	5) Запись данных в текстовый файл из списка" << endl;
		cout << "	6) Поиск в списке по заданному параметру" << endl;
		cout << "	7) Изменение -ой структуры из массива (нумерация с 1);" << endl;
		cout << "	8) Удаление -ой структуры из списка" << endl;
		cout << "	9) Удалить все записи" << endl;
		cout << "	10) Вывод на экран списка" << endl;
		cout << "Ввод : ";
		cin >> menu;
		switch (menu)
		{
		case 1:
			
			lst.push_back(structureInput());
			break;

		case 2:

			lst.push_front(structureInput());
			break;

		case 3:
			//сделано не индеально, но сначало надо записать данные
			lst.push_place();
			break; 

		case 4:

			if (lst.readingFile()) cout << "\nСтроки записаны в систему\n";
			else cout << "\nОшибка открытия файла\n";
			break;

		case 5:

			if (lst.SaveFile()) cout << "Структуры записаны в файл" << endl;
			else cout << "Ошибка создания|открытия файла" << endl;
			break;

		case 6:

			if (!lst.dataSearch()) cout << endl << "Не удалось найти структуру" << endl;
			break;

		case 7:

			lst.structureChange();
			cout << endl << "Данные изменены!" << endl;

			break;

		case 8:

			lst.pop_record();
			cout << endl << "Запись удалена!" << endl;
			break;

		case 9:

			lst.clear();
			cout << endl << "Все записи удалены!" << endl;

			break;

		case 10:

			lst.consoleOutput();
			break;

		default:
			break;
		}
	}
	return 0;
}

StudentsList structureInput()
{
	StudentsList Temp;
	cout << endl << "Введите все новые данные" << endl;
	cout << "	Фамилия Имя Отчество\nВвод: ";
	getchar(); getline(cin, Temp.fullName);
	cout << "	Средний балл студента\nВвод: ";
	cin >> Temp.gpa;
	cout << "	Номер группы\nВвод: ";
	cin >> Temp.groupNumber;
	cout << "	Доход на одного члена семьи\nВвод: ";
	cin >> Temp.familyIncome;
	return Temp;
}