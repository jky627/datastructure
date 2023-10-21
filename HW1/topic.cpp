//組員1.  
//組員2.  

#include <iostream>
#include <fstream>
using namespace std;

fstream file;

class sparse_matrix {
	const static int MAX = 32;
public:
	int** data;
	int row, col;
	int len = 0;

	//三行陣列的建構式
	sparse_matrix(int r, int c) {
		row = r;//原本陣列的列數
		col = c;//原本陣列的行數

		//宣告動態二維陣列，結果為data[32][3]
		data = new int* [MAX];
		for (int i = 0; i < MAX; i++)
			data[i] = new int[3];

		//用data的第0列存入，原陣列的列數、行數、非0的值的數量
		data[len][0] = r;
		data[len][1] = c;
		data[len][2] = len;

		//把預計存入data的列的位置往後推
		len++;
	}

	void insert(int r, int c, int val) {
	}

	void matrix_to_threeCol(int row, int col, int arr[][12]) {


	}

	void threeCol_plus(sparse_matrix a, sparse_matrix b) {

		//因為i,j不會只用在for迴圈，所以要事先宣告
		int i, j;

		//a、b都從第1列開始檢視，直到a、b其中一個到達data的列數的上限
		for (i = 1, j = 1;/*a條件式*/&&/*b條件式*/;) {

			//計算a第i列和b第j列的編號位置
			int pos_a = a.data[i][0] * a.data[0][1] + a.data[i][1];
			int pos_b = b.data[j][0] * b.data[0][1] + b.data[j][1];

			//如果a的編號位置比較前面，則插入a的第i列
			if () {

			}

			//如果b的編號位置比較前面，則插入b的第j列
			else if () {

			}

			/*如果a、b的編號位置相同且相加後不為0，
			則插入 a第i列的列、行，a+b的值*/
			else if () {

				//相加後不為0
				if () {

				}

			}
		}

		//將a中剩下的data全部逐列加入到新的三行陣列中
		while (i < a.len) {
		}

		//將b中剩下的data全部逐列加入到新的三行陣列中
		while (j < b.len) {
		}
	}

	void print()
	{
	}
};



int main()
{
	file.open("sparse_matrix.txt");
	int a[10][12], b[10][12];
	char judge;
	if (!file) {
		cout << "Failed to open file.\n";
		system("PAUSE");
		exit(1);
	}
	else {
		if (file >> judge, judge != 'A')
			exit(1);

		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 12; j++)
				file >> a[i][j];

		if (file >> judge, judge != 'B')
			exit(1);

		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 12; j++)
				file >> b[i][j];
	}

	sparse_matrix sparse_a(10, 12);
	sparse_a.matrix_to_threeCol(sparse_a.row, sparse_a.col, a);
	cout << "Sparse Martix A:" << endl;
	sparse_a.print();

	sparse_matrix sparse_b(10, 12);
	sparse_b.matrix_to_threeCol(sparse_b.row, sparse_b.col, b);
	cout << "Sparse Martix B:" << endl;
	sparse_b.print();

	sparse_matrix sparse_a_plus_b(sparse_a.row, sparse_a.col);
	sparse_a_plus_b.threeCol_plus(sparse_a, sparse_b);
	cout << "Sparse Martix A+B:" << endl;
	sparse_a_plus_b.print();
}