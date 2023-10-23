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
double digstack::cur() {//回傳當前最上方的運算元
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
	//確認stack內是否有左括號
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
char operstack::cur() {//回傳當前最上方的運算子
	return operators[top];
}

int main() {
	//請修改成自己和組員的學號
	cout << "By 1091650" << endl << endl;
	string s;
	cout << "請輸入算式:" << endl;
	cin >> s;
	cout << "答案:" << endl;
	cout << answer(s) << endl;
	cout << endl;
	system("pause");
	return 0;
}

bool isDigit(char c) { //確認是否為數字(運算元)
	return (c >= '0' && c <= '9');
}

bool isOp(char c) { //確認是否為運算子
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(');
}

int priority(char c) {// 回傳運算子的優先層級
	switch (c) {
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	case '^':  return 3;
	default: return 0;
	}
}

//運算
double calculate(double val1, double val2, char oper) {
	//cout << "算式:" << val1 << oper << val2 << endl;
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

	while (/*字串還沒有讀完*/) {
		char spot = s[pos];
		if (/*如果是現在讀到的是數字*/isDigit(spot)) {
			digs.push(spot - 48);
			while (/*讀取位置(pos)的下一個內容也是數字*/isDigit(s[pos + 1])) {
				//把stack裡最上方的數字pop出來，加上一個位數並加上下一個內容後，再存回stack
				//換下一個位置讀取
			}
		}
		else {
			//數字是負數 情況1.
			if (/* 現在讀到的是減號'-'&&現在位置是在最前面 */spot == '-' && pos == 0) {
				//把下一位數字變成負的，存進stack
				digs.push(-(s[pos + 1] - 48));
				//換下一個位置讀
				pos++;
				while (/*讀取位置(pos)的下一個內容也是數字*/) {
					//把stack裡的數字pop出來加上一個位數後、再加上「負的」下一個數字，再存回去stack

					//換下一個位置讀

				}
			}
			//數字是負數 情況2.
			else if (/*如果是現在讀到的是減號'-'&&上一個位置的內容是運算元+-/*^(*/) {
				//與情況1.相同




			}
			else {
				//特殊情況:
				if (/*現在讀取到的是'^' 並且oper stack最上方的內容也是'^'*/) {
					//因為是右結合、最右邊的'^'要先處理
				}
				//特殊情況: 讀取到'('
				else if (/* 讀取到'('*/) {


				}
				//特殊情況: 讀取到')'
				else if (/*讀取到')'*/) {
					if (/*oper stack內沒有左括號*/) {
						cout << "缺少左括號" << endl;
						exit(1);
					}
					else {
						while (/*直到讀取到左括號為止*/) {

							//做運算
						}
						//把左括號pop出去(現在stack內沒有左括號)


					}
				}
				else {
					while (/*如果讀到的運算子的層級 <= stack裡的最上層的運算子的層級(使用priority)*/) {

						//做運算
						//Pop出一個運算子

						//Pop出兩個運算元


						//進行計算(使用calculate)

						//將結果存入dig stack

					}
					//將現在讀到的運算子push進oper stack
					opers.push(spot);
				}
			}
		}
		//換下一個位置讀
		pos++;
	}

	//算式讀取結束，執行oper stack內所有運算子
	while (/*當oper stack不是空的*/) {
		//特殊情況:
		if (/*遇到左括號*/) {
			cout << "缺少右括號" << endl;
			exit(1);
		}

		//執行運算



	}
	return (digs.cur()/*dig stack內最後剩下的元素就是算式的結果*/);
}
