#include <iostream>
#include <locale.h>
//#include <cstdio>
#include <string>     
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iomanip> // для вывода заданной точности


using namespace std;

string types[5] = {"остроугольный", "с тупым углом", "равносторонний", "прямоугольный", "равнобедренный"};

class Tboard{
	public:
//	float angle;
	int length1; 
	int length2;
	int length3;
//	float squire;
	string type;
	
	Tboard(int length1, int length2, int length3, string type){
		this->length1 = length1;
		this->length2 = length2;
		this->length3 = length3;
		this->type = type;
	}
	void printInfo(int mark){
		if (mark != 1){
			cout << endl << "Тип треугольника: " << type << endl << "Его стороны: " << length1 << " " << length2 << " " << length3 << endl;
		}
		else {
			cout << endl << "Тип треугольника: " << types[4] << " " << type << endl << "Его стороны: " << length1 << " " << length2 << " " << length3 << endl;
		}
	}
};

int floatFunction(float angle);

int main(){
setlocale(LC_ALL,"Rus");

random_device rd;
mt19937 gen(rd()); // функция рандома из библиотеки random (srand плохо генерирует числа)
uniform_int_distribution<> distr1(1, 100), distr2(1, 100), distr3(1, 100);

char znachenie, stopcycle;
int a, b, c, mark = 0, znachenie1;
float S, p, alpha, beta, gamma;
int alpha1, beta1, gamma1;
string type;
bool flag = true;

Tboard* board;

do{
cout << "Хотите ввести стороны треугольника сами или задать случайно? " << endl;
cout << "Если хотите ввести самостоятельно нажмите 'y' " << endl;
cin >> znachenie; 
cout << endl;

	if (znachenie == 'y'){
//		do {
	cout << "Введите стороны вручную: " << endl;
tryAgain:	
	cout << "a= "; 
	cin >> a;
	cout << "b= ";
	cin >> b;
	cout << "c= ";
	cin >> c;
	cout << endl;
		if (a + b <= c || b + c <= a || a + c <= b){
			cout << "Введены некорректные значения ! Пожалуйста введите длины заного." << endl;
			goto tryAgain;
		}		
	//	}while (a + b <= c || b + c <= a || a + c <= b);
	}
	else {
		do {
		a = distr1(gen);
		b = distr2(gen);
		c = distr3(gen);
		}while (a + b <= c || b + c <= a || a + c <= b);
	}

cout << "Задайте точность углов ";
cin >> znachenie1; 
cout << endl;
	if (znachenie1 < 0){
		cout << "Будут выведены углы округленные до целого числа " << endl;
		cout << endl;
		znachenie1 = 0;
	}

p = (float)(a + b + c)/2;
S = sqrt(p*(p-a)*(p-b)*(p-c));

alpha = acos((pow(b,2) + pow(c,2) - pow(a,2))/(2*b*c))*180/M_PI;
beta = acos((pow(a,2) + pow(c,2) - pow(b,2))/(2*a*c))*180/M_PI;
gamma = acos((pow(a,2) + pow(b,2) - pow(c,2))/(2*a*b))*180/M_PI;

//cout << a << " " << b << " " << c << endl;
//cout << alpha << " " << beta << " " << gamma << endl;

alpha1 = floatFunction(alpha) + znachenie1;
//cout << "число знаков угла альфа = " << alpha1 << endl;
beta1 = floatFunction(beta) + znachenie1;
//cout << "число знаков угла бета = " << beta1 << endl;
gamma1 = floatFunction(gamma) + znachenie1;
//cout << "число знаков угла гамма = " << gamma1 << endl;

if ((pow(a,2) + pow(b,2) - pow(c,2) == 0) || (pow(c,2) + pow(b,2) - pow(a,2) == 0) || (pow(a,2) + pow(c,2) - pow(b,2) == 0)){
	cout << "Задан " << types[3] << " треугольник" << endl;
	cout << "С углами ";
	cout << setprecision(alpha1) << alpha << " ";
	cout << setprecision(beta1) << beta << " ";
	cout << setprecision(gamma1) << gamma << endl;
	type = types[3];
}
else{
	if (alpha == 60, beta == 60, gamma == 60){
	cout << "Задан " << types[2] << " треугольник,\nуглы которого равны 60ти градусам" << endl;
	type = types[2];
	}
	else{
		if (alpha > 90 || beta > 90 || gamma > 90){
			if (a != b && a != c && b != c){
				cout << "Задан треугольник " << types[1] << endl;
				cout << "Его углы:  ";
				cout << setprecision(alpha1) << alpha << " ";
				cout << setprecision(beta1) << beta << " ";
				cout << setprecision(gamma1) << gamma << endl;
				type = types[1];
			}
			else{
				cout << "Задан треугольник " << types[4] << " " << types[1] << endl;
				cout << "Его углы:  ";
				cout << setprecision(alpha1) << alpha << " ";
				cout << setprecision(beta1) << beta << " ";
				cout << setprecision(gamma1) << gamma << endl;
				type = types[1];
				mark = 1;
			}	
		}
		else{
			if (a != b && a != c && b != c){
				cout << "Задан " << types[0] << " треугольник" << endl;
				cout << "Его углы: ";
				cout << setprecision(alpha1) << alpha << " ";
				cout << setprecision(beta1) << beta << " ";
				cout << setprecision(gamma1) << gamma << endl;
				type = types[0];
			}
			else{
				cout << "Задан " << types[4] << " " << types[0] << " треугольник" << endl;
				cout << "Его углы: ";
				cout << setprecision(alpha1) << alpha << " ";
				cout << setprecision(beta1) << beta << " ";
				cout << setprecision(gamma1) << gamma << endl;
				type = types[0];
				mark = 1;
			}
		}
	}
}

board = new Tboard(a, b, c, type);
board->printInfo(mark);
cout << "Площадь равна " << S << endl;
cout << "Полупериметр равен " << p << endl;

cout << "\nХотите продолжить? y/n ";
cin >> stopcycle; 
cout << endl;
	
if (stopcycle == 'n'){
	flag = false;
	}

}while(flag);

return 0;
}

int floatFunction(float angle){
int i = 0;
//int k = 10;
	for (i; i <= 3; i++){
	
		if (int(angle) > 0){
	
			angle /= 10;
		//cout << angle << " " << int(angle) << endl;	
		}
			else
			break;								
	}
	return i;
}



