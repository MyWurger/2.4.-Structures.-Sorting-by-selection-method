/*******************************************************************************
 * Л А Б О Р А Т О Р Н А Я   Р А Б О Т А  №4  З А   2   С Е М Е С Т Р   С  +  +*
 *-----------------------------------------------------------------------------*
 * Project Type  : Win64 Console Application                                   *
 * Project Name  : Вариант1                                                    *
 * File Name     : Вариант1.CPP                                                *
 * Programmer(s) : Викулов Д.Г.                                                *
 * Modifyed By   :                                                             *
 * Created       : 16/04/22                                                    *
 * Last Revision : 19/04/22                                                    *
 * Comment(s)    : Считывает структуру из файла. Производит проверку времени   *
 *                 и бортового номера. Сортирует запись с использованием       *
 *                 индексной сортировки методом выбора в порядке возрастания   *
 *                 виремени посадки; печатает результат в виде таблицы         *
 *******************************************************************************/

#include<iostream>                                 // стандартные потоки ввода/вывода  
#include<fstream>                                  // файловые потоки ввода/вывода
#include<iomanip>                                  // библиотека с модификатором setw
using namespace std;                               // используем пространство имён std

/***************************************************************/
/*          Г Л О Б А Л Ь Н Ы Е   К О Н С Т А Н Т Ы            */
/***************************************************************/
const int Maxlen = 15;                             // неизменяемая максимальная длина массивов структур

/***************************************************************/
/*          Г Л О Б А Л Ь Н Ы Е   П Е Р Е М Е Н Н Ы Е          */
/***************************************************************/
struct Plane                    // строка массива из файла
{ 
	string time;                // время посадки
	string type;                // марка ЛА
	string number;              // бортовой номер
	string city;                // пункт отправления
};

struct IndexItem                 //строка индексного массива
{
	int ind;                     //индекс == № записи == № элемента в массиве
	string key;                  //для символьного ключа
				                 //int key;	//для числового ключа
};

/*******************************************************************/
/*                    Н А Б О Р    Т Е С Т О В                     */
/*******************************************************************/
//const char* FNAME = "Faila_Net.txt";             // путь к файлу через константный указатель
//const char* FNAME = "Pustota.txt";
//const char* FNAME = "Kolichestvo_Ne_Chislo.txt";
//const char* FNAME = "Kolichestvo_Null.txt";
//const char* FNAME = "Kolichestvo_Less_Null.txt";
//const char* FNAME = "Kolichestvo_Ravno_1.txt";
//const char* FNAME = "Vremya_Pervaya_Stroka_Bigger.txt";
//const char* FNAME = "Vremya_Pervaya_Stroka_Less.txt";
//const char* FNAME = "Vremua_Bigger.txt";
//const char* FNAME = "Vremua_Less.txt";
//const char* FNAME = "Chasu_Ne_chislo.txt";
//const char* FNAME = "Minutu_Ne_chislo.txt";
//const char* FNAME = "Net_Dvoetochia.txt";
//const char* FNAME = "Chasu_Bigger_3.txt";
//const char* FNAME = "Vtoraya_Chasu_Bigger_3_1.txt";
//const char* FNAME = "Vtoraya_Chasu_Bigger_3_2.txt";
//const char* FNAME = "Minutu_Pervaya_Bigger6_1.txt";
//const char* FNAME = "Minutu_Pervaya_Bigger7_1.txt";
//const char* FNAME = "Dvoetochie_Ne_Na_Svoem_Meste.txt";
//const char* FNAME = "Bortovoy_Number_Ne_S_Б.txt";
//const char* FNAME = "Bortovoy_Number_S_Angl_Bukvu.txt";
//const char* FNAME = "Stoit_Ne_Tire.txt";
//const char* FNAME = "Net_Tire.txt";
//const char* FNAME = "V_Konce_Ne_Cifra.txt";
//onst char* FNAME = "Pervaya_Stroka_Nomera_Bolshe_6.txt";
//const char* FNAME = "Ne_Pervaya_Stroka_Nomera_Bolshe_6.txt";
//const char* FNAME = "Vse_Verno.txt";
const char* FNAME = "Vse_Verno_Podrobno.txt";

/***************************************************************/
/*          П Р О Т О Т И П Ы    Ф У Н К Ц И Й                 */
/***************************************************************/
// чтение структур из файла
void InputStruct(Plane* Posadka            // указатель на массив структур
	, int &realLen                         // реальный размер массива структур
	, int &ErrNo);                         // номер ошибки для изменения

// печать структуры из файла
void PrintStruct(Plane Posadka[]          // указатель на массив структур
	, int realLen);                       // длина массива структур

// заполнение индексного массива
void FillIndexVec(Plane* Posadka          // указатель на массив структур
	, IndexItem IndexVec[]                // указатель на индексный массив
	, int realLen);                       // длина массива структур
 
// печать индексного массива
void PrintIndexVec(IndexItem IndexVec[]   // указатель на индексный массив
	, int realLen);                       // длина массива структур (и индексного тоже)

// сортировка индексного массива
void SortIndexVec(IndexItem* IndexVec     // указатель на индексный массив
	, int realLen);                       // длина массива структур (и индексного тоже)

// печать исходного массива в отсортированном виде
void Zamena(Plane* Posadka                // указатель на массив структур  
	, IndexItem IndexVec[]                // указатель на индексный массив
	, int realLen);                       // длина массива структур (и индексного тоже)

// проверка на ошибки
void Proverka(Plane* Posadka              // указатель на массив структур                
	, int& ErrNo                          // номер ошибки для изменения
	, int realLen                         // длина массива структур
	, int tnumb                           // количество цифр в записи времени
    , int lnum);                          // количество цифр в записи бортового номера

// печать сообщения об ошибке
void PrintMessage(int xErrCode            // код ошибки
	, const char* FName);                 // имя файла с ошибкой

/**************************************************************/
/*            О С Н О В Н А Я   П Р О Г Р А М М А             */
/**************************************************************/
int main()
{
	system("color F0");                   // делаем консоль светлой
	setlocale(LC_ALL, "Rus");             // подключаем русский язык
	system("cls");                        // чистим консоль перед выводом
    // объявление и инициализация переменных                    
	int tnumb = 0;                        // количество элементов в поле время
	int lnum = 0;                         // количество элементов в поле бортовой номер
	int realLen = 0;                      // реальный размер массива структур( и индексного)
	int ErrNo = 0;                        // код ошибки
	Plane Posadka[Maxlen];                // массив структур
	cout << "\n" << setw(55) << char(' ') << "СЧИТЫВАНИЕ ИЗ ФАЙЛА\n";   // setw(55)-заполнение 55 клеток символом char(' ')
	// передача массива (указателя) в функцию и изменение массива
	InputStruct(Posadka, realLen, ErrNo);         
	IndexItem IndexVec[Maxlen];               //индексный массив с ключами

	if (ErrNo == 0)                           // ошибок нет
	{
		tnumb = ((Posadka[0].time).length()); // длина поля time в первой структуре массива
		lnum = (Posadka[0].number).length();  // длина поля бортовой номер в первой структуре массива

		// передача массива (указателя) в функцию и проверка времени и номера борта
		Proverka(Posadka, ErrNo, realLen, tnumb, lnum);
	}// if

	if (ErrNo == 0)                           // ошибок нет
	{
		cout << "\n\t\tmain:\n\n";
		// передача массива (указателя) в функцию и печать массива структур
		PrintStruct(Posadka, realLen);
		cout << "Количество элементов в поле <время>: " << tnumb << endl;
		cout << "Количество символов в поле <бортовой номер>: " << lnum << endl;

		/*************************************************************
		*                   ИНДЕКСНАЯ СОРТИРОВКА                     *
		**************************************************************/
		cout << "\n"<<setw(55)<<char(' ') << "ИНДЕКСНАЯ СОРТИРОВКА\n";    // setw(55)-заполнение 55 клеток символом char(' ')
		cout << "\n\tЗаполненный индексный массив \n\nIndexVec: \n";
		// передача массивов (указателей) в функцию и заполнение индексного массива с ключом
		FillIndexVec(Posadka, IndexVec, realLen);
		// передача массива (указателя) в функцию и печать индексного массива
		PrintIndexVec(IndexVec, realLen);
		// передача индексного массива (указателя) в функцию и сортировка по возрастанию времени посадки
		SortIndexVec(IndexVec, realLen);
		cout << "\nОтсортированный IndexVec:\n";
		// передача индексного массива (указателя) в функцию и печать индексного массива 
		PrintIndexVec(IndexVec, realLen);
		cout << "\nМассив <Posadka>, упорядоченный только по time:\n";
		// передача массивов (указателей) в функцию и печать изменённого массива структур
		Zamena(Posadka, IndexVec, realLen);
	}// if
	else // ErrNo!=0
	{
		PrintMessage(ErrNo, FNAME);                                      // печатаем сведения об ошибке
	}// else
	system("pause");
	return 0;
}// main()


 /***************************************************/
 /*             РЕАЛИЗАЦИЯ ФУНКЦИЙ                  */
 /***************************************************/
 /*-------------------------------------------------*/
 /* заполнение индексного массива */
 /*-------------------------------*/
void FillIndexVec(Plane* Posadka                                          // указатель на массив структур
	, IndexItem IndexVec[]                                                // указатель на индексный массив с ключом
	, int realLen)                                                        // реальная длина массива структур (и индексного)
{
	int i = 0;
	for (i = 0; i < realLen; i++)   
	{
		IndexVec[i].ind = i;                                              // в поле индексов помещаем индекс
		IndexVec[i].key = Posadka[i].time;                                // ключом в каждой строке будет поле времени структур исходного массива
	}// for  
	return;
}// FillIndexVec()

 /*-------------------------------------------------*/
 /* чтение структур из файла */
 /*--------------------------*/
void InputStruct(Plane* Posadka                                          // указатель на массив структур
	, int& realLen                                                       // реальная длина массива для изменения
	, int& ErrNo)                                                        // код ошибки
{
	int i = 0;                                                           // счётчик. Число реально считанных записей
	ifstream fin;                                                        // объявление объекта для потокового введения данных из файла
	fin.open(FNAME);                                                     // связываем обЪект с файлом. Открываем для чтения
	if (!fin.is_open())                                                  //файл не найден
	{
		ErrNo = 1;
		fin.close();                                                     // закрыть файл
		return;                                                          // возвращаем значение, соответствующее типу
	}// if

	if (fin.peek() == EOF)                                               // файл пуст
	{
		ErrNo = 2;
		fin.close();                                                     // закрыть файл
		return;                                                          // возвращаем значение, соответствующее типу
	}// if

	fin >> realLen;                                                      // считывание реальной длины - первой строки файла
	if (fin.fail())                                                      // реальная длинав файле - <нечисло>
	{
		ErrNo = 3;
		fin.close();                                                     // закрыть файл
		return;                                                          // возвращаем значение, соответствующее типу
	}// if

	if ((realLen < 1))                                                   // не имеет смысла продолжать
	{
		ErrNo = 4;
		fin.close();                                                     // закрыть файл
		return;                                                          // возвращаем значение, соответствующее типу
	}// if

	cout << "Количество прибывших самолётов: " << realLen;               // эхо-печать
	cout << endl;
	cout << "\n\t\tInputStruct:\n\n"; 
	while (!fin.eof())                                                   // пока файл не кончился
	{
		fin >> (Posadka + i)->time                                       // считаваем по пробелам и помещаем в соответствующие поля
			>> (Posadka + i)->type
			>> (Posadka + i)->number
			>> (Posadka + i)->city;
		i++;
	}// while
	fin.close();
	// передача массива (указателя) в функцию и печать массива структур в самой функции считывания
	PrintStruct(Posadka, realLen);
	return;
}// InputStruct()

 /*-------------------------------------------------*/
 /* проверка времени и номера */
 /*---------------------------*/
void Proverka(Plane* Posadka                                             // указатель на массив структур
	, int& ErrNo                                                         // код ошибки для изменения
	, int realLen                                                        // реальная длина реальная длина массива
	, int tnumb                                                          // длина поля времени первой строки массива структур
    , int lnum)                                                          // длина поля бортового номера первой строки массива структур
{
	int i = 0;                                                           // счётчики
	int j = 0;                                                           
	int schet = 0;                                                       // для контроля наличия двоеточия
	//контроль времени посадки
	if (tnumb !=5)                                                       // сначала смотрим соответствие первой строки. В записи времени должно быть 5 цифр
	{
		ErrNo = 5;
		return;                                                          // возвращаем значение, соответствующее типу
	}// if

	for (i = 0; i < realLen; i++)                                        // идём по всем строкам массива
	{
		if ((Posadka[i].time).length() != tnumb)                         // если первая строка идеальна, длины остальных сравниваем с ней. Ошибка, если не равны
		{
			ErrNo = 6;
			return;                                                      // возвращаем значение, соответствующее типу
		}// if

		schet = 0;                                                       // перешли на новую строку - обнулили счётчик элементов <не двоеточие>
		for (j = 0; j < tnumb; j++)
		{
			if ((Posadka[i].time[j] < '0' || Posadka[i].time[j] > '9')&&( Posadka[i].time[j]!=':'))    // проверка того, что все, кроме <:> - цифры
			{
				ErrNo = 7;
				return;                                                                                // возвращаем значение, соответствующее типу
			}// if  

			if (Posadka[i].time[j] != ':')                                                             // нет двоеточия
			{
				schet = schet + 1;                                                                     // элемент не двоиточие => увеличили счётчик
			}// if
		}// for j

		if (schet == tnumb)                                                                            // нет двоеточия. Количество элементов не двоиточие равно максмальному
		{ 
			ErrNo = 8;
			return;                                                                                    // возвращаем значение, соответствующее типу
		}// if

		if ((Posadka[i].time[0] >= '3')||((Posadka[i].time[0]=='2')&&(Posadka[i].time[1]>='4')))       // главная цифра времени <3. Если она равна 2, то вторая цифра не может быть больше 3
		{
			ErrNo = 9;
			return;                                                                                    // возвращаем значение, соответствующее типу
		}// if

		if (Posadka[i].time[3] >= '6')                                                                 // первая цифра минут не может быть больше 5, 60 минут уже нет
		{
			ErrNo = 10;
			return;                                                                                    // возвращаем значение, соответствующее типу
		}// if
	}// for i

	// проверка бортового номера

	if (lnum != 6)
	{
		ErrNo = 14;             
		return;                                                                                        // возвращаем значение, соответствующее типу
	}// if

	for (i = 0; i < realLen; i++)                                                                      // идём по всем строкам массива
	{
		if ((Posadka[i].number).length() != lnum)                                                      // если первая строка идеальна, длины остальных сравниваем с ней. Ошибка, если не равны
		{
			ErrNo = 15;
			return;                                                                                    // возвращаем значение, соответствующее типу
		}// if

		if (Posadka[i].number[0] != 'Б')                                                               // если первый символ в бортовом номере не <Б>
		{
			ErrNo = 11;
			return;                                                                                    // возвращаем значение, соответствующее типу
		}// if

		if (Posadka[i].number[1] != '-')                                                               // если второй символ в бортовом номере не <->
		{
			ErrNo = 12;
			return;                                                                                    // возвращаем значение, соответствующее типу
		}// if

		for (j = 2; j <lnum; j++)                                                                      // идём до конца поля бортового номера
		{
			if ((Posadka[i].number[j] < '0' || Posadka[i].number[j] > '9'))                            // проверяем на цифры конечные элементы номера
			{
				ErrNo = 13;
				return;                                                                                // возвращаем значение, соответствующее типу
			}// if
		}// for j
	} // for i
	return;                                                                                            // возвращаем значение, соответствующее типу
}// Proverka()


 /*-------------------------------------------------*/
 /* печать                      */
 /* считанного массива структур */
 /* в виде таблицы              */
 /*-----------------------------*/
void PrintStruct(Plane Posadka[]                                                                       // указатель на массив структур
	, int realLen)                                                                                     // реальный размер массива
{
	setlocale(0, "C");                                                                                 //отключаем русский язык
	int i = 0;
	cout << char(218) << setw(25) << setfill((char)196)<< (char)194 << setw(25) << (char)194 <<  setw(25) << (char)194                                           // выводим верхнюю строку шапки
		<< setw(25) << (char)194 << setw(25) << (char)191 << endl
		<< (char)179 << "          Number        " << (char)179 << "    Time of landing     " << (char)179 << "        Bort type       "
		<< (char)179 << "       Bort Number      " << (char)179 << "    Point of depature   " << (char)179 << endl; // выводим единичные отступы вниз            // setw(16) - ширина заполнения
	cout << (char)195 << setw(25) << (char)197 << setw(25) << (char)197 << setw(25) <<
		(char)197 << setw(25) << (char)197
		<< setw(25) << (char)180 << setfill(' ') << endl;                                                                                                        // выводим нижнюю строку шапки

	for (i = 0; i < realLen; i++)                                                                                                                                // печатаем значения и разделители по всем строкам
	{
		        
		cout << (char)179 << setw(13) << i << setw(12) << (char)179
			<< setw(15) << Posadka[i].time << setw(10) << (char)179
			<< setw(16);
		setlocale(LC_ALL, "Rus");                                                                     // подключаем русский язык
		cout << Posadka[i].type;                                                                      // выводим русские символы в поле
		setlocale(0, "C");                                                                            //отключаем русский язык
		cout << setw(9) << (char)179
			<< setw(15);
		setlocale(LC_ALL, "Rus");                                                                     // подключаем русский язык
		cout << Posadka[i].number;                                                                    // выводим русские символы в поле
		setlocale(0, "C");                                                                            //отключаем русский язык
		cout << setw(10) << (char)179
			 << setw(18);
		setlocale(LC_ALL, "Rus");                                                                     // подключаем русский язык
		cout << Posadka[i].city;                                                                      // выводим русские символы в поле
		setlocale(0, "C");                                                                            //отключаем русский язык
		cout << setw(7) << (char)179 << endl;                                                         // вывод строчки за значениями по середине
		cout << (char)195 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196             // заполнение нижней строчки ячейки значений			
		    << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)197 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << char(196)
			<< (char)197 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 
			<< (char)196 << (char)196 << (char)196 <<(char)196 << (char)196 << (char)196 << (char)196 << (char)196 
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)197
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)197 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)196 << (char)196 << (char)196 << (char)196
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)180 << endl;
	}// for
	setlocale(LC_ALL, "Rus");                                                                          // подключаем русский язык для печати русских слов в консоль
	return;                                                                                            // возвращаем значение, соответствующее типу
}// PrintStruct()


 /*-------------------------------------------------*/
 /* печать                      */
 /* индексного массива структур */
 /* в виде таблицы              */
 /*-----------------------------*/
void PrintIndexVec(IndexItem IndexVec[]                                                                // указатель на индексный массив с ключом
	, int realLen)                                                                                     // реальный размер индексного массива
{
	setlocale(0, "C");                                                                                 //отключаем русский язык
	int i = 0;
	cout << char(218) << setw(15) << setfill((char)196) << (char)194 << setw(22) << (char)191  << endl // выводим верхнюю строку шапки
		<< (char)179 << "     Number   " << (char)179 << "   Time of landing   " << (char)179 << endl; // выводим разделители столбцов 
	cout << (char)195 << setw(15) << (char)197 << setw(22)<< (char)180 << setfill(' ') << endl;        // выводим нижнюю строку шапки

	for (i = 0; i < realLen; i++)
	{
		cout << (char)179 << setw(8) << IndexVec[i].ind << setw(7) << (char)179                        // заполнение таблицы
			 << setw(13) << IndexVec[i].key << setw(9) << (char)179 <<endl;
		cout << (char)195 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			 << (char)196 << (char)196                                                                 // заполнение нижней строчки ячейки значений	
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)197 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)180 << endl;
	}// for

	setlocale(LC_ALL, "Rus");                                                                          // подключаем русский язык для вывода записей на русском
	return;                                                                                            // возвращаем значение, соответствующее типу
}

 /*-------------------------------------------------*/
 /* сортировка                  */
 /* индексного массива структур */
 /* по возрастанию времени      */
 /* методом выбора              */
 /*-----------------------------*/
void SortIndexVec(IndexItem* IndexVec                                                                 // указатель на индексный массив с ключом
	, int realLen)                                                                                    // реальный размер индексного массива
{
	string Min;                               // минимальный элемент с учётом того, что работаем со строками
	int jMin;                                 // индекс минимального элемента
	int iSort;                                // граница отсортированной области
	int i = 0;                                // счётчики
	int j = 0;
	string Temp;                              // для перемещения
	int Help;     

	for (iSort = 0; iSort < realLen - 1; iSort++)        // пока не дошли до конца
	{
		// первую строку из неупорядоченных назначаем минимальной
		Min = IndexVec[iSort].key;
		jMin = iSort;                                    // её индекс

		// ищем минимальный элемент в оставшейся части массива
		for (j = iSort + 1; j < realLen; j++)
		{
			if (IndexVec[j].key < Min)                   // очередной кандидат на минимальный
			{
				// запоминаем минимальную строку и её номер
				Min = IndexVec[j].key;
				jMin = j;
			}// if

		}// for j
		// нашли минимум в неупорядоченной части массива
		// ставим его на место первого в неупорядоченной части массива
		// меняем элементы местами
		Temp = IndexVec[iSort].key;
		IndexVec[iSort].key = IndexVec[jMin].key;
		IndexVec[jMin].key = Temp;

		Help = IndexVec[iSort].ind;
		IndexVec[iSort].ind = IndexVec[jMin].ind;
		IndexVec[jMin].ind = Help;
	}// for
	return;                                              // возвращаем значение, соответствующее типу
}// SortIndexVec()

 /*-------------------------------------------------*/
 /* печать                      */
 /* иcходного  массива структур */
 /* в виде таблицы в            */
 /* упорядоченной форме         */
 /*-----------------------------*/
void Zamena(Plane* Posadka                               // указатель на массив структур
	, IndexItem IndexVec[]                               // указатель на индексный массив с ключом
	, int realLen)                                       // реальный размер массивов
{
	setlocale(0, "C");                                   // отключаем русский язык
	int i = 0;
	cout << char(218) << setw(25) << setfill((char)196) << (char)194 << setw(25) << (char)194 << setw(25) << (char)194  // выводим верхнюю строку шапки
		<< setw(25) << (char)194 << setw(25) << (char)191 << endl
		<< (char)179 << "          Number        " << (char)179 << "    Time of landing     " << (char)179 << "        Bort type       " // шапка и разделители столбцов
		<< (char)179 << "       Bort Number      " << (char)179 << "    Point of depature   " << (char)179 << endl;    
	cout << (char)195 << setw(25) << (char)197 << setw(25) << (char)197 << setw(25) <<                                  // выводим единичные отступы вниз            //setw(16) - ширина заполнения
		(char)197 << setw(25) << (char)197 
		<< setw(25) << (char)180 << setfill(' ') << endl; // выводим нижнюю строку шапки
	for (i = 0; i < realLen; i++)
	{

			cout << (char)179 << setw(13) << IndexVec[i].ind << setw(12) << (char)179
				<< setw(15) << (Posadka + IndexVec[i].ind)->time << setw(10) << (char)179
				<< setw(16);
			setlocale(LC_ALL, "Rus");                    // подключаем русский язык
			cout << Posadka[IndexVec[i].ind].type;       // берем поле с отсортированным индексом
			setlocale(0, "C");                           // отключаем русский язык
			cout << setw(9) << (char)179
				<< setw(9);
			setlocale(LC_ALL, "Rus");                    // подключаем русский язык
			cout << ' ' << Posadka[IndexVec[i].ind].number;
			setlocale(0, "C");                           // отключаем русский язык
			cout << setw(10) << (char)179
				<< setw(18);
			setlocale(LC_ALL, "Rus");                    // подключаем русский язык
			cout << Posadka[IndexVec[i].ind].city;
			setlocale(0, "C");                           // отключаем русский язык
			cout << setw(7) << (char)179 << endl;        // вывод строчки за значениями по середине
			cout << (char)195 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
				<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196   // заполнение нижней строчки ячейки значений			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196<< (char)196 << (char)196
				<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
				<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
				<< (char)197 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
				<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
				<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << char(196)
				<< (char)197 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
				<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
				<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196
				<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)197
				<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
				<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
				<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
				<< (char)197 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
				<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
				<< (char)196 << (char)196 << (char)196 << (char)196
				<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)180 << endl;
	}// for
	setlocale(LC_ALL, "Rus");       // подключаем русский язык
	return;                         // возвращаем значение, соответствующее типу
}// Zamena()

 /*-------------------------------------------------*/
 /* сообщения об ошибках */
 /*-----------------------*/
void PrintMessage(int xErrCode      // код ошибки
	, const char* FNAME)            // имя файла с ошибкой
{
	// расшифровка кода возврата в текст сообщения об ошибке
	switch (xErrCode)
	{
		cout << "/ PrintMessage:\n";

	case 1: cout << "Файл " << FNAME << " не найден;\n";
		break;
	case 2: cout << "Файл " << FNAME << " пустой;\n";
		break;
	case 3: cout << "В файле " << FNAME << " количество элементов не является числом;\n";
		break;
	case 4: cout << "В файле " << FNAME << " число элементов 0 или отрицательно;\n";
		break;
	case 5: cout << "В файле " << FNAME << " формат времени некорректен. Используйте <две цифры: две цифры>;\n";
		break;
	case 6: cout << "В файле " << FNAME << " формат времени некорректен. Введено больше или меньше 5 элементов;\n";
		break;
	case 7: cout << "В файле " << FNAME << " в диапазоне времени есть нечисло;\n";
		break;
	case 8: cout << "В файле " << FNAME << " нет двоеточия-разделителя;\n";
		break;
	case 9: cout << "В файле " << FNAME << " ошибка ввода количества часов;\n";
		break;
	case 10: cout << "В файле " << FNAME << " ошибка при указании минут;\n";
		break;
	case 11: cout << "В файле " << FNAME << " бортовой номер должен начинаться с буквы <Б>;\n";
		break;
	case 12: cout << "В файле " << FNAME << " в бортовом номере после буквы <Б> должно стоять тире;\n";
		break;
	case 13: cout << "В файле " << FNAME << " бортовой номер должен оканчиваться цифрами;\n";
		break;
	case 14: cout << "В файле " << FNAME << " в первой строке бортовой номер слишком длинный;\n";
		break;
	case 15: cout << "В файле " << FNAME << " формат бортового номера некорректен, введено больше или меньше 6 символов;\n";
		break;
	default:
		break;
	}// switch

	return;                               // возврат значения соответственно типу
}// PrintMessage()