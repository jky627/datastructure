#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

double answer(string s);

class digstack {
private:
	int top;
	int capacity;
	double* digit;
public:
	digstack() :top(-1), capacity(10) {
		digit = new double[capacity];
	}
	void push(double val);
	double pop();
	double cur();
	void show();
};
void digstack::push(double val) {
	if (top + 1 == capacity) {
		cout << "dig stack is full!" << endl;
		capacity = capacity * 2;
		double* temp = new double[capacity];
		copy(digit, digit + top + 1, temp);
		delete[] digit;
		digit = temp;
	}
	digit[++top] = val;
}
double digstack::pop() {
	if (top == -1) {
		cout << "dig stack is empty!" << endl;
		return 0;
	}
	return digit[top--];
}
double digstack::cur() {//�^�Ƿ�e�̤W�誺�B�⤸
	return digit[top];
}
void digstack::show() {
	cout << "dig stack:" << endl;
	for (int i = top; i >= 0; i--) {
		cout << digit[i] << endl;
	}
}

class operstack {
private:
	int top;
	int capacity;
	char* operators;
public:
	//�T�{stack���O�_�����A��
	bool has_left = false;
	operstack() :top(-1), capacity(10) {
		operators = new char[capacity];
	}
	void push(char oper);
	char pop();
	bool isEmpty();
	char cur();
};
void operstack::push(char oper) {
	if (top + 1 == capacity) {
		cout << "oper stack is full!" << endl;
		capacity = capacity * 2;
		char* temp = new char[capacity];
		copy(operators, operators + top + 1, temp);
		delete[] operators;
		operators = temp;
	}
	operators[++top] = oper;
}
char operstack::pop() {
	if (top == -1) {
		cout << "oper stack is empty!" << endl;
		return 0;
	}
	return operators[top--];
}
bool operstack::isEmpty() {
	return (top == -1);
}
char operstack::cur() {//�^�Ƿ�e�̤W�誺�B��l
	return operators[top];
}

int main() {
	//�Эק令�ۤv�M�խ����Ǹ�
	cout << "By 1091650" << endl << endl;
	string s;
	cout << "�п�J�⦡:" << endl;
	cin >> s;
	cout << "����:" << endl;
	cout << answer(s) << endl;
	cout << endl;
	system("pause");
	return 0;
}

bool isDigit(char c) { //�T�{�O�_���Ʀr(�B�⤸)
	return (c >= '0' && c <= '9');
}

bool isOp(char c) { //�T�{�O�_���B��l
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(');
}

int priority(char c) {// �^�ǹB��l���u���h��
	switch (c) {
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	case '^':  return 3;
	default: return 0;
	}
}

//�B��
double calculate(double val1, double val2, char oper) {
	//cout << "�⦡:" << val1 << oper << val2 << endl;
	if (oper == '+')  return val1 + val2;
	if (oper == '-')  return val1 - val2;
	if (oper == '*')  return val1 * val2;
	if (oper == '/')  return val1 / val2;
	if (oper == '^')  return pow(val1, val2);
}

double answer(string s) {
	digstack digs;
	operstack opers;
	int pos = 0;

	while (/*�r���٨S��Ū��*/) {
		char spot = s[pos];
		if (/*�p�G�O�{�bŪ�쪺�O�Ʀr*/isDigit(spot)) {
			digs.push(spot - 48);
			while (/*Ū����m(pos)���U�@�Ӥ��e�]�O�Ʀr*/isDigit(s[pos + 1])) {
				//��stack�̳̤W�誺�Ʀrpop�X�ӡA�[�W�@�Ӧ�ƨå[�W�U�@�Ӥ��e��A�A�s�^stack
				//���U�@�Ӧ�mŪ��
			}
		}
		else {
			//�Ʀr�O�t�� ���p1.
			if (/* �{�bŪ�쪺�O�'-'&&�{�b��m�O�b�̫e�� */spot == '-' && pos == 0) {
				//��U�@��Ʀr�ܦ��t���A�s�istack
				digs.push(-(s[pos + 1] - 48));
				//���U�@�Ӧ�mŪ
				pos++;
				while (/*Ū����m(pos)���U�@�Ӥ��e�]�O�Ʀr*/) {
					//��stack�̪��Ʀrpop�X�ӥ[�W�@�Ӧ�ƫ�B�A�[�W�u�t���v�U�@�ӼƦr�A�A�s�^�hstack

					//���U�@�Ӧ�mŪ

				}
			}
			//�Ʀr�O�t�� ���p2.
			else if (/*�p�G�O�{�bŪ�쪺�O�'-'&&�W�@�Ӧ�m�����e�O�B�⤸+-/*^(*/) {
				//�P���p1.�ۦP




			}
			else {
				//�S���p:
				if (/*�{�bŪ���쪺�O'^' �åBoper stack�̤W�誺���e�]�O'^'*/) {
					//�]���O�k���X�B�̥k�䪺'^'�n���B�z
				}
				//�S���p: Ū����'('
				else if (/* Ū����'('*/) {


				}
				//�S���p: Ū����')'
				else if (/*Ū����')'*/) {
					if (/*oper stack���S�����A��*/) {
						cout << "�ʤ֥��A��" << endl;
						exit(1);
					}
					else {
						while (/*����Ū���쥪�A������*/) {

							//���B��
						}
						//�⥪�A��pop�X�h(�{�bstack���S�����A��)


					}
				}
				else {
					while (/*�p�GŪ�쪺�B��l���h�� <= stack�̪��̤W�h���B��l���h��(�ϥ�priority)*/) {

						//���B��
						//Pop�X�@�ӹB��l

						//Pop�X��ӹB�⤸


						//�i��p��(�ϥ�calculate)

						//�N���G�s�Jdig stack

					}
					//�N�{�bŪ�쪺�B��lpush�ioper stack
					opers.push(spot);
				}
			}
		}
		//���U�@�Ӧ�mŪ
		pos++;
	}

	//�⦡Ū�������A����oper stack���Ҧ��B��l
	while (/*��oper stack���O�Ū�*/) {
		//�S���p:
		if (/*�J�쥪�A��*/) {
			cout << "�ʤ֥k�A��" << endl;
			exit(1);
		}

		//����B��



	}
	return (digs.cur()/*dig stack���̫�ѤU�������N�O�⦡�����G*/);
}
