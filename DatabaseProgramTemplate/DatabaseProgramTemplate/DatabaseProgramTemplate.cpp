#include <iostream>
#include <conio.h>
#include <fstream>
#include "students.h"   // подключаем свою библиотеку работы со связным списком
// список должен хранить данные о вашей предметной области
// и реализовывать функции, согласно вашему заданию
using namespace std;

Student* first = nullptr; // указатель на начало списка

bool auth()
{
	string loginInput;
	string passInput;
	const string correctLogin = "admin";
	const string CorrectPass = "1234";
	system("cls");// функция очистки консоли
	cout << "авторизация\n";
	cout << "Vvedite login: ";
	cin >> loginInput;
	cout << "Vvedite password: ";
	cin >> passInput;
	if (loginInput == correctLogin && passInput == CorrectPass)
	{
		cout << "yspex нажмите любую клавишу";
		_getch(); // просто ждём нажатия любой клавиши
		return true;
	}
	else
	{
		cout << "error не правильный логин или пароль нажмите любую клавишу для закрытия программы";
		_getch();
		return false;
	}

}

void inputValidationId(char* resultInput)   //передаём указатель 
{
	char buffer[50]; //временный буфер для ввода
	do // запускаем бесконечный цикл, который закончится при успешном вводе
	{
		cin >> buffer;
		if (strlen(buffer) != 10) // проверка на то что ввели 10 симловов
		{
			cout << "Номер должен быть ровно 10 символов\n";
			continue;
		}
		Student* t = first; //создаём новый элемент, что можно было посмотреть есть ли кто - то в списке или нет
		bool unique = true; // специальная переменная которая станет потом false если номер существует уже
		while (t != nullptr)
		{
			if (strcmp(t->id, buffer) == 0) //используем специальный метод для сравнения строк, возвращаем 0 если они равны
			{
				cout << "Такой номер уже есть введите другой\n";
				unique = false; //номер не уникальный
				break;
			}
			t = t->next; //переходим к следующему студенту
		}
		// после окончания цикла проверяем переменную unique если true то значит уникальный
		if (unique == true)
		{
			// КОПИРУЕМ СТРОКУ, а не просто присваиваем указатель
			for (int i = 0; buffer[i] != '\0'; i++)
				resultInput[i] = buffer[i];
			resultInput[strlen(buffer)] = '\0';
			break;
		}
	} while (true); // если unique false то повторяем ввод
}

// Функция для ввода строки с проверкой длины и на пустоту и отсуствие пробелов
void inputValidationText(char* resultInput, int maxLen)
{
	char buffer[100]; // временный буфер для ввода
	do
	{
		cin.getline(buffer, 100);
		if (strlen(buffer) == 0)      // проверяем не пусто ли там
		{
			cout << "поле не может быть пустым\n";
		}
		else if (strlen(buffer) > maxLen)       // проверяем не слишком ли много ввёл пользователь
		{
			cout << "не больше " << maxLen << " символов\n";
		}
		else
		{
			// проверяем, есть ли пробел в строке
			bool hasSpace = false;
			for (int i = 0; buffer[i] != '\0'; i++)
			{
				if (buffer[i] == ' ')
				{
					hasSpace = true;
					break;
				}
			}
			if (hasSpace==true)
			{
				cout << "пробел нельзя!\n";
			}
			else
			{
				// копируем в результат
				for (int i = 0; buffer[i] != '\0'; i++)
					resultInput[i] = buffer[i];
				resultInput[strlen(buffer)] = '\0';
				break;
			}
		}
	} while (true);                         // если ошибка повторяем ввод
}

// функция добавления данных
void AddData()
{
	system("cls");
	cout << "Добавление данных:\n";
	Student* s = new Student; // создали новый элемент
	s->next = nullptr; // указали что после него пусто никого нет и можно заносить данные

	cout << "Номер зачётной книжки (ровно 10 символов): ";
	inputValidationId(s->id);   // вызываем валидацию

	cout << "Фамилия (до 14): ";
	inputValidationText(s->fam, 14);
	cout << "Имя (до 11): ";
	inputValidationText(s->name, 11);
	cout << "Отчество (до 12): ";
	inputValidationText(s->otchestvo, 12);
	cout << "Шифр группы (до 14): ";
	inputValidationText(s->shifrGrup, 14);
	cout << "Шифр специальности (до 7): ";
	inputValidationText(s->shifrSpecialnosti, 7);

	// статус — число 0 или 1
	int st;
	do {
		cout << "Статус (1 - учится, 0 - отчислен): ";
		cin >> st;
		if (cin.fail() || (st != 0 && st != 1))
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Ошибка введите 0 или 1\n";
		}
		else break;
	} while (true);
	s->statusStud = (st == 1);

	if (first == nullptr) // если он первый то добавляем
	{
		first = s;
	}
	else
	{
		Student* t = first; // создаём новый элемент, что можно было посмотреть есть ли кто-то в списке или нет
		while (t->next != nullptr) // перебираем список пока не найдём, что следующий элемент не пустой
		{
			t = t->next; // каждый раз переключаемся на новый
		}
		t->next = s; // когда нашли пустой вставляем наши значения
	}
	cout << "dobavleno";
	_getch();
}

// функция печати данных
void PrintData()
{
	system("cls");
	cout << "Список студентов:\n";
	if (first == nullptr)
	{
		cout << "pysto\n";
	}
	else
	{
		Student* t = first; // так же как и выше создаём элемент что бы начать перебор с первого
		int count = 0;
		while (t != nullptr) // пока не будет нуллптр выполняем цикл вывода
		{
			cout << "\n" << ++count << " Зачётка: " << t->id;
			cout << "\n    Фамилия: " << t->fam;
			cout << "\n    Имя: " << t->name;
			cout << "\n    Отчество: " << t->otchestvo;
			cout << "\n    Группа: " << t->shifrGrup;
			cout << "\n    Специальность: " << t->shifrSpecialnosti;
			cout << "\n    Статус: " << (t->statusStud ? "Учится\n" : "Отчислен\n");
			t = t->next;
		}
	}
	cout << "\nдля возврата нажмите любую кнопку";
	_getch();
}

// функция поиска студента по номеру зачётки
void SearchById()
{
	while (true)
	{
		system("cls");
		char idInput[11];
		cout << "vvedite nomer zachetki\n";
		cin >> idInput;
		Student* t = first; // так же как и выше создаём элемент что бы начать перебор с первого
		bool poisk = false;
		while (t != nullptr) //пока не будет равен nullptr то перебираем
		{
			if (strcmp(t->id, idInput) == 0) //используем специальный метод для сравнения строк, возвращаем 0 если они равны
			{
				cout << "\nНайден студент:\n";
				cout << "Зачётка: " << t->id;
				cout << "\nФамилия: " << t->fam;
				cout << "\nИмя: " << t->name;
				cout << "\nОтчество: " << t->otchestvo;
				cout << "\nГруппа: " << t->shifrGrup;
				cout << "\nСпециальность: " << t->shifrSpecialnosti;
				cout << "\nСтатус: " << (t->statusStud ? "Учится" : "Отчислен") << endl;
				poisk = true;
				break;
			}
			t = t->next;
		}
		if (poisk == false)
		{
			cout << "nety takix\n";
			cout << "1 - попробовать снова\n";
			cout << "0 - выход\n";

			char ch = _getch();

			if (ch == '0')
			{
				return;
			}
			_getch();
		}
		else
		{
			cout << "\nдля выхода нажмите любую кнопку";
			_getch();
			return;
		}
	}
}

//функция поиска студента по фамилии 
void SearchByFam()
{
	while (true)
	{
		system("cls");
		char famInput[15];
		cout << "vvedite familia\n";
		cin >> famInput;
		Student* t = first; // так же как и выше создаём элемент что бы начать перебор с первого
		bool poisk = false;
		while (t != nullptr)
		{
			if (strcmp(t->fam, famInput) == 0) //используем специальный метод для сравнения строк, возвращаем 0 если они равны
			{
				cout << t->id << " - " << t->fam << " " << t->name << ", группа " << t->shifrGrup << endl;
				poisk = true;
			}
			t = t->next;
		}
		if (poisk == false)
		{
			cout << "nety takix\n";
			cout << "1 - попробовать снова\n";
			cout << "0 - выход\n";

			char ch = _getch();

			if (ch == '0')
			{
				return;
			}
		}
		else
		{
			cout << "\nдля выхода нажмите любую кнопку";
			_getch();
			return;
		}
	}
}

//поиск студентов по группе
void SearchByGroup()
{
	while (true)
	{
		system("cls");
		char shifrGroupInput[15];
		cout << "vvedite shifr group\n";
		cin >> shifrGroupInput;
		Student* t = first; // так же как и выше создаём элемент что бы начать перебор с первого
		bool poisk = false;
		while (t != nullptr)
		{
			if (strcmp(t->shifrGrup, shifrGroupInput) == 0) //используем специальный метод для сравнения строк, возвращаем 0 если они равны
			{
				cout << t->fam << " " << t->name << " (" << t->id << ")" << endl;
				poisk = true;
			}
			t = t->next;
		}
		if (poisk == false)
		{
			cout << "nety takix\n";
			cout << "1 - попробовать снова\n";
			cout << "0 - выход\n";

			char ch = _getch();

			if (ch == '0')
			{
				return;
			}
		}
		else
		{
			cout << "\nдля выхода нажмите любую кнопку";
			_getch();
			return;
		}
	}
}

void SearchBySpec()
{
	while (true)
	{
		system("cls");
		char specialnostInput[8];
		cout << "vvedite shifr specialnosti\n";
		cin >> specialnostInput;
		Student* t = first; // так же как и выше создаём элемент что бы начать перебор с первого
		bool poisk = false;
		while (t != nullptr)
		{
			if (strcmp(t->shifrSpecialnosti, specialnostInput) == 0) //используем специальный метод для сравнения строк, возвращаем 0 если они равны
			{
				cout << t->fam << " " << t->name << ", группа " << t->shifrGrup << endl;
				poisk = true;
			}
			t = t->next;
		}
		if (poisk == false)
		{
			cout << "nety takix\n";
			cout << "1 - попробовать снова\n";
			cout << "0 - выход\n";

			char ch = _getch();

			if (ch == '0')
			{
				return;
			}
		}
		else
		{
			cout << "\nдля выхода нажмите любую кнопку";
			_getch();
			return;
		}
	}
}

// функция удаления данных
void DeleteData()
{
	system("cls");
	char idInput[11];
	cout << "Введите номер зачётной книжки удаляемого студента\n";
	cin >> idInput;
	if (first == nullptr)
	{
		cout << "Список пуст.\n";
		_getch();
		return;
	}
	// Удаление первого элемента
	if (strcmp(first->id, idInput) == 0) //используем специальный метод для сравнения строк, возвращаем 0 если они равны
	{
		Student* temp = first; //создаём временный элемент в который заносим элемент с найденым айдишником что бы в дальнейшём удалить
		first = first->next; // переходим вперёд на следующий элемент, что бы не потерять где мы остановились
		delete temp; // (освобождаем память) удаляем студента
		cout << "Студент удалён.\n";
		_getch();
		return;
	}
	// Поиск в середине/конце
	Student* prev = first; //создаём указатель и ставим на первый он будет запоминать предыдущего
	Student* curr = first->next; //создаём указатель на второй элемент это наш текущий элемент 
	while (curr != nullptr && strcmp(curr->id, idInput) != 0) // пока текущий элемент НЕ равен nullptr И строка из ТЕКУЩЕГО элемента не станет равна введённому айди
	{														  // то перебираем и ищем
		prev = curr; // перезаписываем текущий элемент в прошлый
		curr = curr->next; // переписываем текущий элемент на следующий
	}
	if (curr != nullptr) // если текущий элемент не равен nullptr то мы 
	{
		prev->next = curr->next; // берём указатель next из предыдущего элемента(prev->next) и перенаправляем на элемент идущий после удалённого(curr->next)
		// как бы перезапимывая, перепрыгивая удаляемый элемент
		delete curr;			 // удаляем элемент
		cout << "Студент удалён.\n";
	}
	else
	{
		cout << "Студент не найден.\n";
	}
	_getch();
}

//// функция редактирования данных
//void EditData()
//{
//	system("cls");
//	cout << "Редактирование данных:\n";
//
//	_getch();
//}

//// функция печати данных по критерию отбора
//void PrintFilteredData()
//{
//	system("cls");
//	cout << "Список студентов - отличников:\n"; // например выводим только отличников
//	// здесь реализуете свой алгоритм
//	_getch();
//}






// функция сохранения данных
bool SaveData()
{
	// ofstream используется для записи в файлы
	ofstream f("students.txt");  // Создадаём файл
	if (f.is_open())
	{


		Student* t = first; // так же как и выше создаём элемент что бы начать перебор с первого
		while (t != nullptr) // пока элемент не будет равен nullptr, выполняем цикл
		{
			f << t->id << '\n';              // номер зачётки
			f << t->fam << '\n';             // фамилия
			f << t->name << '\n';            // имя
			f << t->otchestvo << '\n';       // отчество
			f << t->shifrGrup << '\n';       // шифр группы
			f << t->shifrSpecialnosti << '\n'; // шифр специальности
			f << (t->statusStud ? 1 : 0) << '\n'; // статус (1 или 0)
			t = t->next;
		}
		f.close(); // закрытие файла
		return true;
	}
	else
	{
		cout << "не удалось открыть файл\n";
		return false;
	}
}






//
//// функция печати справки
//void PrintHelp()
//{
//	// Выводите текст справки на экран
//	// Рекомендую создать текстовый файл справки
//	// а здесь прочитать текст из него и вывести в консоль
//	system("cls");
//	cout << "Справка:\n"; // например выводим только отличников
//	// здесь реализуете свой алгоритм справки
//	_getch();
//}
//





// функция загрузки данных
bool LoadData()
{
	// реализуйте здесь алгоритм чтения базы данных из файла
	// возвращайте true, если чтение прошло успешно и false в противном случае
	ifstream f("students.txt");
	if (f.is_open()== false)
	{
		return true;
	}

	// создаём временный буфер для чтения
	char id[11];
	char fam[15];
	char name[12];
	char otch[13];
	char grp[15];
	char spec[8];
	int status;

	while (true)
	{
		// Пытаемся прочитать 7 полей подряд (каждое с новой строки)
		f >> id;
		if (f.eof()) // функция выхода
		{
			break; // если пользователь нажал ctr+Z - завершаем ввод
		}       
		f >> fam;
		f >> name;
		f >> otch;
		f >> grp;
		f >> spec;
		f >> status;

		Student* s = new Student;
		s->next = nullptr;

		int i;
		for (i = 0; id[i] != '\0' && i < 10; i++)
			s->id[i] = id[i];
		s->id[i] = '\0';

		for (i = 0; fam[i] != '\0' && i < 14; i++)
			s->fam[i] = fam[i];
		s->fam[i] = '\0';

		for (i = 0; name[i] != '\0' && i < 11; i++)
			s->name[i] = name[i];
		s->name[i] = '\0';

		for (i = 0; otch[i] != '\0' && i < 12; i++)
			s->otchestvo[i] = otch[i];
		s->otchestvo[i] = '\0';

		for (i = 0; grp[i] != '\0' && i < 14; i++)
			s->shifrGrup[i] = grp[i];
		s->shifrGrup[i] = '\0';

		for (i = 0; spec[i] != '\0' && i < 7; i++)
			s->shifrSpecialnosti[i] = spec[i];
		s->shifrSpecialnosti[i] = '\0';

		s->statusStud = (status == 1);

		if (first == nullptr)
		{
			first = s;
		}
		else
		{
			Student* t = first;
			while (t->next != nullptr)
			{
				t = t->next;
			}
			t->next = s;
		}
	}
	f.close();
	return true;
}





// вывод в консоль меню программы
char MainMenu()
{
	while (true) // бесконечный цикл
	{
		system("cls"); // чистим экран
		cout << "БАЗА ДАННЫХ СТУДЕНТОВ ФИЛИАЛА УДГУ В Г. ВОТКИНСКЕ\n\n"; // выводим название программы, оно у каждого буде свое
		// выводим строки меню, цивра в скобках - клавиша, которую нужно нажать для выбора соответствующего действия
		cout << "[1] Добавить сведения о студенте" << endl;
		cout << "[2] Вывести сведения о студентах" << endl;
		cout << "[3] Поиск студента по номеру зачетной книжки" << endl;
		cout << "[4] Поиск студента по фамилии " << endl;
		cout << "[5] Поиск студента по группе" << endl;
		cout << "[6] Поиск студента по специальности" << endl;
		cout << "[7] Удалить студента по номеру зачетной книжки" << endl;
		cout << "[8] Завершить работу" << endl;

		cout << "Ваш выбор > ";
		char choice = _getch(); // считываем нажатую пользователем клавишу
		if (choice < '1' || choice > '8') // проверяем, соответствует ли клавиша пунктам меню
		{	// если нет, то требуем повторить ввод
			cout << "Такого варианта не существует! Нажмите любую клавишу...";
			_getch();
		}
		else
		{	// если соответствует, то возвращаем в вызываемую программу символ
			// соответствующий нажатой клавише
			return choice;
		}
	}
}

// обработка действий пользователя
void HandleEvents()
{
	char choice = 0;
	while (choice != '8') // цикл пока пользователь не нажал ВЫХОД
	{
		choice = MainMenu(); // определяем, какой пункт меню выбрал пользователь
		// переменная choice будет хранить символ, соответствующий 
		// выбранному пункту меню
		switch (choice) // проверяем какую клавишу нажал пользователь
		{
		case '1': // если 1 то вызываем функцию добавления данных
			AddData();
			break;
		case '2': // если 2 то вызываем функцию вывода данных
			PrintData();
			break;
		case '3': // если 3 то вызываем функцию поиска студента по номеру зачётки
			SearchById();
			break;
		case '4': // если 4 то вызываем функцию поиска студента по фамилии
			SearchByFam();
			break;
		case '5': // если 5 то вызываем функцию поиска студента по группе
			SearchByGroup();
			break;
		case '6': // если 6 то вызываем функцию поиска студентов по специальности
			SearchBySpec();
			break;
		case '7': // если 7 то вызываем функцию удаления студента по айди
			DeleteData();
			break;
		case '8': // // если 1 то выходим
			return;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "");
	if (auth() == true)
	{
		if (!LoadData()) // если чтение базы данных неудачно, то продолжение выполнения программы невозможно
		{	// выводим сообщение об ошибке и выходим с кодом 1
			cout << "Ошибка чтения базы данных\n";
			return 1;
			// как вариант, если базу прочитать невозможно, вы можете создать новую базу данных и продолжить работу
			// с программой
		}
		HandleEvents(); // вызываем функцию обработки нажатий клавиш пользователем
		SaveData(); // при выходе сохраняем данные в базе данных
	}
}