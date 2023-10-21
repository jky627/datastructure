// DS homework 1: Sparse Matrix (using Visual Studio 2019)
// Due 2023/09/23 Complete 2023/09/26
// 組員1: 梁凱晰, s1111646
// 組員2: 鄭岡宜, s1111647

#include <iostream>
#include <fstream>
using namespace std;

fstream file;
//123
//486789
class sparse_matrix {
	const static int MAX = 32;
public:
	int** data;
	int row, col;
	int len = 0;
	//123
	//777
	// branch2
	// 888
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

	void insert(int r, int c, int val) { //把兩個陣列放進新的陣列中
		if (r > row || c > col) {
			return;
		}
		else
		{
			//用data的第0列存入，原陣列的列數、行數、非0的值的數量
			data[len][0] = r;
			data[len][1] = c;
			data[len][2] = val;

			data[0][2] = len;

			//把預計存入data的列的位置往後推
			len++;
		}
	}

	void matrix_to_threeCol(int row, int col, int arr[][12]) { //把稀疏矩陣變成三行陣列//裡面會有insert
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (arr[i][j] != 0) {
					insert(i, j, arr[i][j]);
				}
			}
		}
	}

	void threeCol_plus(sparse_matrix a, sparse_matrix b) {

		//因為i,j不會只用在for迴圈，所以要事先宣告
		int i, j;

		//a、b都從第1列開始檢視，直到a、b其中一個到達data的列數的上限
		for (i = 1, j = 1; i < a.len/*a條件式*/ && j < b.len/*b條件式*/;) { //->插入C的條列

			//計算a第i列和b第j列的編號位置
			int pos_a = a.data[i][0] * a.data[0][1] + a.data[i][1];
			int pos_b = b.data[j][0] * b.data[0][1] + b.data[j][1];

			//如果a的編號位置比較前面，則插入a的第i列
			if (pos_a < pos_b/*裡面會用到insert*/) {
				insert(a.data[i][0], a.data[i][1], a.data[i][2]);
				i++;
			}

			//如果b的編號位置比較前面，則插入b的第j列
			else if (pos_a > pos_b) {
				insert(b.data[j][0], b.data[j][1], b.data[j][2]);
				j++;
			}

			/*如果a、b的編號位置相同且相加後不為0，
			則插入 a第i列的列、行，a+b的值*/
			else if (pos_a == pos_b) {
				//相加後為0
				if (a.data[i][2] + b.data[j][2] != 0) {
					insert(a.data[i][0], a.data[i][1], a.data[i][2] + b.data[j][2]);
				}
				i++;
				j++;
			}
		}

		//將a中剩下的data全部逐列加入到新的三行陣列中
		while (i < a.len) {
			insert(a.data[i][0], a.data[i][1], a.data[i][2]);
			i++;
		}

		//將b中剩下的data全部逐列加入到新的三行陣列中
		while (j < b.len) {
			insert(b.data[j][0], b.data[j][1], b.data[j][2]);
			j++;
		}
	}

	void print()
	{

		cout << "Dimension: " << row << "x" << col << endl;
		cout << "Sparse Matrix:\n \tRow\tColumn\tValue\t\n";
		for (int i = 0; i < len; i++)
		{
			cout << i << "\t" << data[i][0] << "\t " << data[i][1] << "\t " << data[i][2] << endl;
			if (i == 0)
				cout << endl;
		}
		/*印出相加後的稀疏矩陣 ? ? ? ? ? 除了有數字的地方其他補0 ? ? ?不懂完全不懂
		if (k == 1) {
			for (int j = 0; j < row; j++) {
				for (int n = 0; n < col; n++) {
					cout << data[j][n] << "\t";
				}
				cout << endl;
			}
		}*/
	}
};



int main()
{
	file.open("sparse_matrix.txt");
	int a[10][12], b[10][12], c[10][12];
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
	cout << "A+B=\n";
	for (int q = 0; q < 10; q++) {
		for (int k = 0; k < 12; k++) {
			c[q][k] = a[q][k] + b[q][k];
			cout << c[q][k] << "\t";
		}
		cout << endl;
	}

}