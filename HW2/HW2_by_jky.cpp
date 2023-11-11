#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

double answer(string s);//全域變數

class digstack {//運算元stack
private:
	int top;//最上面的~?
	int capacity;//容量
	double* digit;//指標數字
public:
	digstack() :top(-1), capacity(10) {///這個部分的目的是在建立 digstack 類別的物件時對成員變數 top 和 capacity 進行初始化。
		digit = new double[capacity];
	}
	void push(double val);//放入函數的宣告
	double pop();///這是函數的宣告
	double cur();
	void show();
};
void digstack::push(double val) {/*///這是void push(double val)函數的定義拉!
								 ::是作用域運算符（Scope Resolution Operator）。
								 它的主要目的是指定某個實體（變數、函數、類別、命名空間等）屬於哪個範圍（作用域）。*/
	if (top + 1 == capacity) {
		cout << "dig stack is full!" << endl;
		capacity = capacity * 2;//擴充空間，老師上課說的方法
		double* temp = new double[capacity];
		copy(digit, digit + top + 1, temp);
		delete[] digit;
		digit = temp;
	}
	digit[++top] = val;//把我現在讀到的digit放入運算元digit[]這個陣列
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

class operstack {//運算子stack
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
	void push(char oper);//運算子的放入
	char pop();
	bool isEmpty();
	char cur();
};
void operstack::push(char oper) {//運算子放入
	if (top + 1 == capacity) {//top就是我最上面的位置//top應該要是-1才對(?
		cout << "oper stack is full!" << endl;
		capacity = capacity * 2;
		char* temp = new char[capacity];//建立新的空間(老師課的
		copy(operators, operators + top + 1, temp);
		delete[] operators;
		operators = temp;
	}
	operators[++top] = oper;
}
char operstack::pop() {//運算子彈出
	if (top == -1) {//我知道
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
	cout << "By 1111647" << endl << endl;
	string s;//我的算式，是字串(by char)
	cout << "請輸入算式:" << endl;
	cin >> s;
	cout << "答案:" << endl;
	cout << answer(s) << endl;//把我輸入的算式帶入函式//然後就跳跳跳//明天給我用出來喔
	cout << endl;
	system("pause");//看毋
	return 0;
}

bool isDigit(char c) { //確認是否為數字(運算元)
	return (c >= '0' && c <= '9');//就代表是true/// (c >= '0' && c <= '9') ? true : false;我自己是這樣
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

double answer(string s) {//浮點數//答案//從這邊開始
	digstack digs;//運算元digstack這個類別的物件
	operstack opers;//運算子
	int pos = 0;//現在的位置
	int dpo1, dpo2, dpu, oppo, final = 0;///oppo的是operators pop出來的,final是我後面運算的結果

	while (pos < s.length()/*字串還沒有讀完*/) {///不是空的時候，最後一個字元是\0啦白癡
		char spot = s[pos];//宣告一個字元spot，把s字串中的第pos這個位子的char給spot這個字元
		if (isDigit(spot) == true/*如果是現在讀到的是數字*/) {///我有動過
			digs.push(spot - 48);//因為是char所以要減48這樣才是數字///digs這個成員要放入push(spot-48)就是我現在的這個運算元
			while (isDigit(s[pos]) == true && isDigit(s[pos + 1]) == true/*讀取位置(pos)的下一個內容也是數字*/) {
				dpo1 = digs.pop();///我打的但不確定	//把stack裡最上方的數字pop出來，52是兩個char
				digs.push(s[pos] * 10 + dpo1);							///為甚麼在這邊要加上一個位數並加上下一個內容後，再存回stack??
				pos++;//換下一個位置讀取///知道了懂
			}
		}
		else {
			//數字是負數 情況1.
			if (spot == '-' && pos == 0/* 現在讀到的是減號'-'&&現在位置是在最前面 */) {
				//把下一位數字變成負的，存進stack
				digs.push(-(s[pos + 1] - 48));///變成負的數字
				pos++;//換下一個位置讀


				while (isDigit(s[pos]) == true && isDigit(s[pos + 1]) == true/*讀取位置(pos)的下一個內容也是數字*/) {
					dpo1 = digs.pop();//把stack裡的數字pop出來加上一個位數後、再加上「負的」下一個數字，再存回去stack-52
					digs.push(s[pos] * 10 - dpo1);				///為甚麼在這邊要加上一個位數並加上下一個內容後，再存回stack??
					int dp;///我digit stack裡面被pop出來的東西要設一個變數
					dp = digs.pop();
					///加加加完了之後記就放進去這樣，dp要加上一個一個位數然後在加上下一個內容再存回去
					pos++;//換下一個位置讀				
				}
			}
			//數字是負數 情況2.
			else if (isOp(s[pos]) == '-' && isOp(s[pos - 1] == '+' || '-' || '/' || '*' || '^' || '(')/*如果是現在讀到的是減號'-'&&上一個位置的內容是運算元+-/*^(*/) {
				//與情況1.相同///一樣就抄




			}
			else {
				//特殊情況:
				if (s[pos] == '^' && opers.cur() == '^')/*現在讀取到的是'^' 並且oper stack最上方的內容也是'^'*/ {///後面的要怎麼打拉!!!??????////對不起我會了就很笨
					dpo1 = digs.pop();//因為是右結合、最右邊的'^'要先處理///要把最上面的pop出跟運算元去做運算，兩個都是要pop出來
					dpo2 = digs.pop();
					int sam = 1;//這是我次方完的結果
					for (int i = 0; i > dpo1; i++) {///用一個迴圈去算dpo2^dpo1
						sam = sam * dpo2;
					}
				}
				//特殊情況: 讀取到'('
				else if (s[pos] == '('/* 讀取到'('*/) {//運算子直接放進去
					opers.push(s[pos]);
					pos++;//繼續下一個位置去讀取

				}
				//特殊情況: 讀取到')'///就不需要放入直接先跳出兩個做運算直到出現又括號'('為止
				else if (s[pos] == ')'/*讀取到')'*/) {
					if (opers.has_left == false/*oper stack內沒有左括號*/) {///不懂為甚麼因為operators[]是private那這樣我要怎麼知道去讀取裡面的東西
						cout << "缺少左括號" << endl;
						exit(1);
					}
					else {
						while (s[pos] == '('/*直到讀取到左括號為止*/) {

							oppo = opers.pop();//Pop出一個運算子//將結果存入dig stack//做運算///做完再把他放進去,這邊不太妙喔跟想的不一樣，看goodnotes

							dpo1 = digs.pop();//Pop出兩個運算元
							dpo2 = digs.pop();


							final = calculate(dpo1, dpo2, oppo);//進行計算(使用calculate)

							digs.push(final);


						}
						opers.pop();//把左括號pop出去(現在stack內沒有左括號)
					}
				}
				else {
					while (priority(s[pos]) <= priority(opers.cur())/*如果讀到的運算子的層級 <= stack裡的最上層的運算子的層級(使用priority)*/) {

						//做運算///怎樣做運算，跟去計算是有什麼差別拉ㄍㄋㄋ
						oppo = opers.pop();//Pop出一個運算子

						dpo1 = digs.pop();//Pop出兩個運算元
						dpo2 = digs.pop();


						final = calculate(dpo1, dpo2, oppo);//進行計算(使用calculate)

						digs.push(final);//將結果存入dig stack

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
	while (opers.cur() != ' '/*當oper stack不是空的*/) {
		//特殊情況:
		if (s[pos] == '('/*遇到左括號*/) {
			cout << "缺少右括號" << endl;
			exit(1);
		}

		oppo = opers.pop();//Pop出一個運算子

		dpo1 = digs.pop();//Pop出兩個運算元
		dpo2 = digs.pop();


		final = calculate(dpo1, dpo2, oppo);//進行計算(使用calculate)

		digs.push(final);//將結果存入dig stack//執行運算



	}
	return (digs.cur()/*dig stack內最後剩下的元素就是算式的結果*/);
}
