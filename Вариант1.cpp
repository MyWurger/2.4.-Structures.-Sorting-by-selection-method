/*******************************************************************************
 * � � � � � � � � � � � �   � � � � � �  �4  � �   2   � � � � � � �   �  +  +*
 *-----------------------------------------------------------------------------*
 * Project Type  : Win64 Console Application                                   *
 * Project Name  : �������1                                                    *
 * File Name     : �������1.CPP                                                *
 * Programmer(s) : ������� �.�.                                                *
 * Modifyed By   :                                                             *
 * Created       : 16/04/22                                                    *
 * Last Revision : 19/04/22                                                    *
 * Comment(s)    : ��������� ��������� �� �����. ���������� �������� �������   *
 *                 � ��������� ������. ��������� ������ � ��������������       *
 *                 ��������� ���������� ������� ������ � ������� �����������   *
 *                 �������� �������; �������� ��������� � ���� �������         *
 *******************************************************************************/

#include<iostream>                                 // ����������� ������ �����/������  
#include<fstream>                                  // �������� ������ �����/������
#include<iomanip>                                  // ���������� � ������������� setw
using namespace std;                               // ���������� ������������ ��� std

/***************************************************************/
/*          � � � � � � � � � �   � � � � � � � � �            */
/***************************************************************/
const int Maxlen = 15;                             // ������������ ������������ ����� �������� ��������

/***************************************************************/
/*          � � � � � � � � � �   � � � � � � � � � �          */
/***************************************************************/
struct Plane                    // ������ ������� �� �����
{ 
	string time;                // ����� �������
	string type;                // ����� ��
	string number;              // �������� �����
	string city;                // ����� �����������
};

struct IndexItem                 //������ ���������� �������
{
	int ind;                     //������ == � ������ == � �������� � �������
	string key;                  //��� ����������� �����
				                 //int key;	//��� ��������� �����
};

/*******************************************************************/
/*                    � � � � �    � � � � � �                     */
/*******************************************************************/
//const char* FNAME = "Faila_Net.txt";             // ���� � ����� ����� ����������� ���������
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
//const char* FNAME = "Bortovoy_Number_Ne_S_�.txt";
//const char* FNAME = "Bortovoy_Number_S_Angl_Bukvu.txt";
//const char* FNAME = "Stoit_Ne_Tire.txt";
//const char* FNAME = "Net_Tire.txt";
//const char* FNAME = "V_Konce_Ne_Cifra.txt";
//onst char* FNAME = "Pervaya_Stroka_Nomera_Bolshe_6.txt";
//const char* FNAME = "Ne_Pervaya_Stroka_Nomera_Bolshe_6.txt";
//const char* FNAME = "Vse_Verno.txt";
const char* FNAME = "Vse_Verno_Podrobno.txt";

/***************************************************************/
/*          � � � � � � � � �    � � � � � � �                 */
/***************************************************************/
// ������ �������� �� �����
void InputStruct(Plane* Posadka            // ��������� �� ������ ��������
	, int &realLen                         // �������� ������ ������� ��������
	, int &ErrNo);                         // ����� ������ ��� ���������

// ������ ��������� �� �����
void PrintStruct(Plane Posadka[]          // ��������� �� ������ ��������
	, int realLen);                       // ����� ������� ��������

// ���������� ���������� �������
void FillIndexVec(Plane* Posadka          // ��������� �� ������ ��������
	, IndexItem IndexVec[]                // ��������� �� ��������� ������
	, int realLen);                       // ����� ������� ��������
 
// ������ ���������� �������
void PrintIndexVec(IndexItem IndexVec[]   // ��������� �� ��������� ������
	, int realLen);                       // ����� ������� �������� (� ���������� ����)

// ���������� ���������� �������
void SortIndexVec(IndexItem* IndexVec     // ��������� �� ��������� ������
	, int realLen);                       // ����� ������� �������� (� ���������� ����)

// ������ ��������� ������� � ��������������� ����
void Zamena(Plane* Posadka                // ��������� �� ������ ��������  
	, IndexItem IndexVec[]                // ��������� �� ��������� ������
	, int realLen);                       // ����� ������� �������� (� ���������� ����)

// �������� �� ������
void Proverka(Plane* Posadka              // ��������� �� ������ ��������                
	, int& ErrNo                          // ����� ������ ��� ���������
	, int realLen                         // ����� ������� ��������
	, int tnumb                           // ���������� ���� � ������ �������
    , int lnum);                          // ���������� ���� � ������ ��������� ������

// ������ ��������� �� ������
void PrintMessage(int xErrCode            // ��� ������
	, const char* FName);                 // ��� ����� � �������

/**************************************************************/
/*            � � � � � � � �   � � � � � � � � �             */
/**************************************************************/
int main()
{
	system("color F0");                   // ������ ������� �������
	setlocale(LC_ALL, "Rus");             // ���������� ������� ����
	system("cls");                        // ������ ������� ����� �������
    // ���������� � ������������� ����������                    
	int tnumb = 0;                        // ���������� ��������� � ���� �����
	int lnum = 0;                         // ���������� ��������� � ���� �������� �����
	int realLen = 0;                      // �������� ������ ������� ��������( � ����������)
	int ErrNo = 0;                        // ��� ������
	Plane Posadka[Maxlen];                // ������ ��������
	cout << "\n" << setw(55) << char(' ') << "���������� �� �����\n";   // setw(55)-���������� 55 ������ �������� char(' ')
	// �������� ������� (���������) � ������� � ��������� �������
	InputStruct(Posadka, realLen, ErrNo);         
	IndexItem IndexVec[Maxlen];               //��������� ������ � �������

	if (ErrNo == 0)                           // ������ ���
	{
		tnumb = ((Posadka[0].time).length()); // ����� ���� time � ������ ��������� �������
		lnum = (Posadka[0].number).length();  // ����� ���� �������� ����� � ������ ��������� �������

		// �������� ������� (���������) � ������� � �������� ������� � ������ �����
		Proverka(Posadka, ErrNo, realLen, tnumb, lnum);
	}// if

	if (ErrNo == 0)                           // ������ ���
	{
		cout << "\n\t\tmain:\n\n";
		// �������� ������� (���������) � ������� � ������ ������� ��������
		PrintStruct(Posadka, realLen);
		cout << "���������� ��������� � ���� <�����>: " << tnumb << endl;
		cout << "���������� �������� � ���� <�������� �����>: " << lnum << endl;

		/*************************************************************
		*                   ��������� ����������                     *
		**************************************************************/
		cout << "\n"<<setw(55)<<char(' ') << "��������� ����������\n";    // setw(55)-���������� 55 ������ �������� char(' ')
		cout << "\n\t����������� ��������� ������ \n\nIndexVec: \n";
		// �������� �������� (����������) � ������� � ���������� ���������� ������� � ������
		FillIndexVec(Posadka, IndexVec, realLen);
		// �������� ������� (���������) � ������� � ������ ���������� �������
		PrintIndexVec(IndexVec, realLen);
		// �������� ���������� ������� (���������) � ������� � ���������� �� ����������� ������� �������
		SortIndexVec(IndexVec, realLen);
		cout << "\n��������������� IndexVec:\n";
		// �������� ���������� ������� (���������) � ������� � ������ ���������� ������� 
		PrintIndexVec(IndexVec, realLen);
		cout << "\n������ <Posadka>, ������������� ������ �� time:\n";
		// �������� �������� (����������) � ������� � ������ ���������� ������� ��������
		Zamena(Posadka, IndexVec, realLen);
	}// if
	else // ErrNo!=0
	{
		PrintMessage(ErrNo, FNAME);                                      // �������� �������� �� ������
	}// else
	system("pause");
	return 0;
}// main()


 /***************************************************/
 /*             ���������� �������                  */
 /***************************************************/
 /*-------------------------------------------------*/
 /* ���������� ���������� ������� */
 /*-------------------------------*/
void FillIndexVec(Plane* Posadka                                          // ��������� �� ������ ��������
	, IndexItem IndexVec[]                                                // ��������� �� ��������� ������ � ������
	, int realLen)                                                        // �������� ����� ������� �������� (� ����������)
{
	int i = 0;
	for (i = 0; i < realLen; i++)   
	{
		IndexVec[i].ind = i;                                              // � ���� �������� �������� ������
		IndexVec[i].key = Posadka[i].time;                                // ������ � ������ ������ ����� ���� ������� �������� ��������� �������
	}// for  
	return;
}// FillIndexVec()

 /*-------------------------------------------------*/
 /* ������ �������� �� ����� */
 /*--------------------------*/
void InputStruct(Plane* Posadka                                          // ��������� �� ������ ��������
	, int& realLen                                                       // �������� ����� ������� ��� ���������
	, int& ErrNo)                                                        // ��� ������
{
	int i = 0;                                                           // �������. ����� ������� ��������� �������
	ifstream fin;                                                        // ���������� ������� ��� ���������� �������� ������ �� �����
	fin.open(FNAME);                                                     // ��������� ������ � ������. ��������� ��� ������
	if (!fin.is_open())                                                  //���� �� ������
	{
		ErrNo = 1;
		fin.close();                                                     // ������� ����
		return;                                                          // ���������� ��������, ��������������� ����
	}// if

	if (fin.peek() == EOF)                                               // ���� ����
	{
		ErrNo = 2;
		fin.close();                                                     // ������� ����
		return;                                                          // ���������� ��������, ��������������� ����
	}// if

	fin >> realLen;                                                      // ���������� �������� ����� - ������ ������ �����
	if (fin.fail())                                                      // �������� ������ ����� - <�������>
	{
		ErrNo = 3;
		fin.close();                                                     // ������� ����
		return;                                                          // ���������� ��������, ��������������� ����
	}// if

	if ((realLen < 1))                                                   // �� ����� ������ ����������
	{
		ErrNo = 4;
		fin.close();                                                     // ������� ����
		return;                                                          // ���������� ��������, ��������������� ����
	}// if

	cout << "���������� ��������� ��������: " << realLen;               // ���-������
	cout << endl;
	cout << "\n\t\tInputStruct:\n\n"; 
	while (!fin.eof())                                                   // ���� ���� �� ��������
	{
		fin >> (Posadka + i)->time                                       // ��������� �� �������� � �������� � ��������������� ����
			>> (Posadka + i)->type
			>> (Posadka + i)->number
			>> (Posadka + i)->city;
		i++;
	}// while
	fin.close();
	// �������� ������� (���������) � ������� � ������ ������� �������� � ����� ������� ����������
	PrintStruct(Posadka, realLen);
	return;
}// InputStruct()

 /*-------------------------------------------------*/
 /* �������� ������� � ������ */
 /*---------------------------*/
void Proverka(Plane* Posadka                                             // ��������� �� ������ ��������
	, int& ErrNo                                                         // ��� ������ ��� ���������
	, int realLen                                                        // �������� ����� �������� ����� �������
	, int tnumb                                                          // ����� ���� ������� ������ ������ ������� ��������
    , int lnum)                                                          // ����� ���� ��������� ������ ������ ������ ������� ��������
{
	int i = 0;                                                           // ��������
	int j = 0;                                                           
	int schet = 0;                                                       // ��� �������� ������� ���������
	//�������� ������� �������
	if (tnumb !=5)                                                       // ������� ������� ������������ ������ ������. � ������ ������� ������ ���� 5 ����
	{
		ErrNo = 5;
		return;                                                          // ���������� ��������, ��������������� ����
	}// if

	for (i = 0; i < realLen; i++)                                        // ��� �� ���� ������� �������
	{
		if ((Posadka[i].time).length() != tnumb)                         // ���� ������ ������ ��������, ����� ��������� ���������� � ���. ������, ���� �� �����
		{
			ErrNo = 6;
			return;                                                      // ���������� ��������, ��������������� ����
		}// if

		schet = 0;                                                       // ������� �� ����� ������ - �������� ������� ��������� <�� ���������>
		for (j = 0; j < tnumb; j++)
		{
			if ((Posadka[i].time[j] < '0' || Posadka[i].time[j] > '9')&&( Posadka[i].time[j]!=':'))    // �������� ����, ��� ���, ����� <:> - �����
			{
				ErrNo = 7;
				return;                                                                                // ���������� ��������, ��������������� ����
			}// if  

			if (Posadka[i].time[j] != ':')                                                             // ��� ���������
			{
				schet = schet + 1;                                                                     // ������� �� ��������� => ��������� �������
			}// if
		}// for j

		if (schet == tnumb)                                                                            // ��� ���������. ���������� ��������� �� ��������� ����� ������������
		{ 
			ErrNo = 8;
			return;                                                                                    // ���������� ��������, ��������������� ����
		}// if

		if ((Posadka[i].time[0] >= '3')||((Posadka[i].time[0]=='2')&&(Posadka[i].time[1]>='4')))       // ������� ����� ������� <3. ���� ��� ����� 2, �� ������ ����� �� ����� ���� ������ 3
		{
			ErrNo = 9;
			return;                                                                                    // ���������� ��������, ��������������� ����
		}// if

		if (Posadka[i].time[3] >= '6')                                                                 // ������ ����� ����� �� ����� ���� ������ 5, 60 ����� ��� ���
		{
			ErrNo = 10;
			return;                                                                                    // ���������� ��������, ��������������� ����
		}// if
	}// for i

	// �������� ��������� ������

	if (lnum != 6)
	{
		ErrNo = 14;             
		return;                                                                                        // ���������� ��������, ��������������� ����
	}// if

	for (i = 0; i < realLen; i++)                                                                      // ��� �� ���� ������� �������
	{
		if ((Posadka[i].number).length() != lnum)                                                      // ���� ������ ������ ��������, ����� ��������� ���������� � ���. ������, ���� �� �����
		{
			ErrNo = 15;
			return;                                                                                    // ���������� ��������, ��������������� ����
		}// if

		if (Posadka[i].number[0] != '�')                                                               // ���� ������ ������ � �������� ������ �� <�>
		{
			ErrNo = 11;
			return;                                                                                    // ���������� ��������, ��������������� ����
		}// if

		if (Posadka[i].number[1] != '-')                                                               // ���� ������ ������ � �������� ������ �� <->
		{
			ErrNo = 12;
			return;                                                                                    // ���������� ��������, ��������������� ����
		}// if

		for (j = 2; j <lnum; j++)                                                                      // ��� �� ����� ���� ��������� ������
		{
			if ((Posadka[i].number[j] < '0' || Posadka[i].number[j] > '9'))                            // ��������� �� ����� �������� �������� ������
			{
				ErrNo = 13;
				return;                                                                                // ���������� ��������, ��������������� ����
			}// if
		}// for j
	} // for i
	return;                                                                                            // ���������� ��������, ��������������� ����
}// Proverka()


 /*-------------------------------------------------*/
 /* ������                      */
 /* ���������� ������� �������� */
 /* � ���� �������              */
 /*-----------------------------*/
void PrintStruct(Plane Posadka[]                                                                       // ��������� �� ������ ��������
	, int realLen)                                                                                     // �������� ������ �������
{
	setlocale(0, "C");                                                                                 //��������� ������� ����
	int i = 0;
	cout << char(218) << setw(25) << setfill((char)196)<< (char)194 << setw(25) << (char)194 <<  setw(25) << (char)194                                           // ������� ������� ������ �����
		<< setw(25) << (char)194 << setw(25) << (char)191 << endl
		<< (char)179 << "          Number        " << (char)179 << "    Time of landing     " << (char)179 << "        Bort type       "
		<< (char)179 << "       Bort Number      " << (char)179 << "    Point of depature   " << (char)179 << endl; // ������� ��������� ������� ����            // setw(16) - ������ ����������
	cout << (char)195 << setw(25) << (char)197 << setw(25) << (char)197 << setw(25) <<
		(char)197 << setw(25) << (char)197
		<< setw(25) << (char)180 << setfill(' ') << endl;                                                                                                        // ������� ������ ������ �����

	for (i = 0; i < realLen; i++)                                                                                                                                // �������� �������� � ����������� �� ���� �������
	{
		        
		cout << (char)179 << setw(13) << i << setw(12) << (char)179
			<< setw(15) << Posadka[i].time << setw(10) << (char)179
			<< setw(16);
		setlocale(LC_ALL, "Rus");                                                                     // ���������� ������� ����
		cout << Posadka[i].type;                                                                      // ������� ������� ������� � ����
		setlocale(0, "C");                                                                            //��������� ������� ����
		cout << setw(9) << (char)179
			<< setw(15);
		setlocale(LC_ALL, "Rus");                                                                     // ���������� ������� ����
		cout << Posadka[i].number;                                                                    // ������� ������� ������� � ����
		setlocale(0, "C");                                                                            //��������� ������� ����
		cout << setw(10) << (char)179
			 << setw(18);
		setlocale(LC_ALL, "Rus");                                                                     // ���������� ������� ����
		cout << Posadka[i].city;                                                                      // ������� ������� ������� � ����
		setlocale(0, "C");                                                                            //��������� ������� ����
		cout << setw(7) << (char)179 << endl;                                                         // ����� ������� �� ���������� �� ��������
		cout << (char)195 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196             // ���������� ������ ������� ������ ��������			
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
	setlocale(LC_ALL, "Rus");                                                                          // ���������� ������� ���� ��� ������ ������� ���� � �������
	return;                                                                                            // ���������� ��������, ��������������� ����
}// PrintStruct()


 /*-------------------------------------------------*/
 /* ������                      */
 /* ���������� ������� �������� */
 /* � ���� �������              */
 /*-----------------------------*/
void PrintIndexVec(IndexItem IndexVec[]                                                                // ��������� �� ��������� ������ � ������
	, int realLen)                                                                                     // �������� ������ ���������� �������
{
	setlocale(0, "C");                                                                                 //��������� ������� ����
	int i = 0;
	cout << char(218) << setw(15) << setfill((char)196) << (char)194 << setw(22) << (char)191  << endl // ������� ������� ������ �����
		<< (char)179 << "     Number   " << (char)179 << "   Time of landing   " << (char)179 << endl; // ������� ����������� �������� 
	cout << (char)195 << setw(15) << (char)197 << setw(22)<< (char)180 << setfill(' ') << endl;        // ������� ������ ������ �����

	for (i = 0; i < realLen; i++)
	{
		cout << (char)179 << setw(8) << IndexVec[i].ind << setw(7) << (char)179                        // ���������� �������
			 << setw(13) << IndexVec[i].key << setw(9) << (char)179 <<endl;
		cout << (char)195 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			 << (char)196 << (char)196                                                                 // ���������� ������ ������� ������ ��������	
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)197 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)180 << endl;
	}// for

	setlocale(LC_ALL, "Rus");                                                                          // ���������� ������� ���� ��� ������ ������� �� �������
	return;                                                                                            // ���������� ��������, ��������������� ����
}

 /*-------------------------------------------------*/
 /* ����������                  */
 /* ���������� ������� �������� */
 /* �� ����������� �������      */
 /* ������� ������              */
 /*-----------------------------*/
void SortIndexVec(IndexItem* IndexVec                                                                 // ��������� �� ��������� ������ � ������
	, int realLen)                                                                                    // �������� ������ ���������� �������
{
	string Min;                               // ����������� ������� � ������ ����, ��� �������� �� ��������
	int jMin;                                 // ������ ������������ ��������
	int iSort;                                // ������� ��������������� �������
	int i = 0;                                // ��������
	int j = 0;
	string Temp;                              // ��� �����������
	int Help;     

	for (iSort = 0; iSort < realLen - 1; iSort++)        // ���� �� ����� �� �����
	{
		// ������ ������ �� ��������������� ��������� �����������
		Min = IndexVec[iSort].key;
		jMin = iSort;                                    // � ������

		// ���� ����������� ������� � ���������� ����� �������
		for (j = iSort + 1; j < realLen; j++)
		{
			if (IndexVec[j].key < Min)                   // ��������� �������� �� �����������
			{
				// ���������� ����������� ������ � � �����
				Min = IndexVec[j].key;
				jMin = j;
			}// if

		}// for j
		// ����� ������� � ��������������� ����� �������
		// ������ ��� �� ����� ������� � ��������������� ����� �������
		// ������ �������� �������
		Temp = IndexVec[iSort].key;
		IndexVec[iSort].key = IndexVec[jMin].key;
		IndexVec[jMin].key = Temp;

		Help = IndexVec[iSort].ind;
		IndexVec[iSort].ind = IndexVec[jMin].ind;
		IndexVec[jMin].ind = Help;
	}// for
	return;                                              // ���������� ��������, ��������������� ����
}// SortIndexVec()

 /*-------------------------------------------------*/
 /* ������                      */
 /* �c�������  ������� �������� */
 /* � ���� ������� �            */
 /* ������������� �����         */
 /*-----------------------------*/
void Zamena(Plane* Posadka                               // ��������� �� ������ ��������
	, IndexItem IndexVec[]                               // ��������� �� ��������� ������ � ������
	, int realLen)                                       // �������� ������ ��������
{
	setlocale(0, "C");                                   // ��������� ������� ����
	int i = 0;
	cout << char(218) << setw(25) << setfill((char)196) << (char)194 << setw(25) << (char)194 << setw(25) << (char)194  // ������� ������� ������ �����
		<< setw(25) << (char)194 << setw(25) << (char)191 << endl
		<< (char)179 << "          Number        " << (char)179 << "    Time of landing     " << (char)179 << "        Bort type       " // ����� � ����������� ��������
		<< (char)179 << "       Bort Number      " << (char)179 << "    Point of depature   " << (char)179 << endl;    
	cout << (char)195 << setw(25) << (char)197 << setw(25) << (char)197 << setw(25) <<                                  // ������� ��������� ������� ����            //setw(16) - ������ ����������
		(char)197 << setw(25) << (char)197 
		<< setw(25) << (char)180 << setfill(' ') << endl; // ������� ������ ������ �����
	for (i = 0; i < realLen; i++)
	{

			cout << (char)179 << setw(13) << IndexVec[i].ind << setw(12) << (char)179
				<< setw(15) << (Posadka + IndexVec[i].ind)->time << setw(10) << (char)179
				<< setw(16);
			setlocale(LC_ALL, "Rus");                    // ���������� ������� ����
			cout << Posadka[IndexVec[i].ind].type;       // ����� ���� � ��������������� ��������
			setlocale(0, "C");                           // ��������� ������� ����
			cout << setw(9) << (char)179
				<< setw(9);
			setlocale(LC_ALL, "Rus");                    // ���������� ������� ����
			cout << ' ' << Posadka[IndexVec[i].ind].number;
			setlocale(0, "C");                           // ��������� ������� ����
			cout << setw(10) << (char)179
				<< setw(18);
			setlocale(LC_ALL, "Rus");                    // ���������� ������� ����
			cout << Posadka[IndexVec[i].ind].city;
			setlocale(0, "C");                           // ��������� ������� ����
			cout << setw(7) << (char)179 << endl;        // ����� ������� �� ���������� �� ��������
			cout << (char)195 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
				<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196   // ���������� ������ ������� ������ ��������			<< (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196<< (char)196 << (char)196
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
	setlocale(LC_ALL, "Rus");       // ���������� ������� ����
	return;                         // ���������� ��������, ��������������� ����
}// Zamena()

 /*-------------------------------------------------*/
 /* ��������� �� ������� */
 /*-----------------------*/
void PrintMessage(int xErrCode      // ��� ������
	, const char* FNAME)            // ��� ����� � �������
{
	// ����������� ���� �������� � ����� ��������� �� ������
	switch (xErrCode)
	{
		cout << "/ PrintMessage:\n";

	case 1: cout << "���� " << FNAME << " �� ������;\n";
		break;
	case 2: cout << "���� " << FNAME << " ������;\n";
		break;
	case 3: cout << "� ����� " << FNAME << " ���������� ��������� �� �������� ������;\n";
		break;
	case 4: cout << "� ����� " << FNAME << " ����� ��������� 0 ��� ������������;\n";
		break;
	case 5: cout << "� ����� " << FNAME << " ������ ������� �����������. ����������� <��� �����: ��� �����>;\n";
		break;
	case 6: cout << "� ����� " << FNAME << " ������ ������� �����������. ������� ������ ��� ������ 5 ���������;\n";
		break;
	case 7: cout << "� ����� " << FNAME << " � ��������� ������� ���� �������;\n";
		break;
	case 8: cout << "� ����� " << FNAME << " ��� ���������-�����������;\n";
		break;
	case 9: cout << "� ����� " << FNAME << " ������ ����� ���������� �����;\n";
		break;
	case 10: cout << "� ����� " << FNAME << " ������ ��� �������� �����;\n";
		break;
	case 11: cout << "� ����� " << FNAME << " �������� ����� ������ ���������� � ����� <�>;\n";
		break;
	case 12: cout << "� ����� " << FNAME << " � �������� ������ ����� ����� <�> ������ ������ ����;\n";
		break;
	case 13: cout << "� ����� " << FNAME << " �������� ����� ������ ������������ �������;\n";
		break;
	case 14: cout << "� ����� " << FNAME << " � ������ ������ �������� ����� ������� �������;\n";
		break;
	case 15: cout << "� ����� " << FNAME << " ������ ��������� ������ �����������, ������� ������ ��� ������ 6 ��������;\n";
		break;
	default:
		break;
	}// switch

	return;                               // ������� �������� �������������� ����
}// PrintMessage()