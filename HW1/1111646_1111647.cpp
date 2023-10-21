// DS homework 1: Sparse Matrix (using Visual Studio 2019)
// Due 2023/09/23 Complete 2023/09/26
// �խ�1: ��ʹ�, s1111646
// �խ�2: �G���y, s1111647

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

	//�T��}�C���غc��  
	sparse_matrix(int r, int c) {
		row = r;//�쥻�}�C���C��
		col = c;//�쥻�}�C�����

		//�ŧi�ʺA�G���}�C�A���G��data[32][3]
		data = new int* [MAX];
		for (int i = 0; i < MAX; i++)
			data[i] = new int[3];

		//��data����0�C�s�J�A��}�C���C�ơB��ơB�D0���Ȫ���
		data[len][0] = r;
		data[len][1] = c;
		data[len][2] = len;

		//��w�p�s�Jdata���C����m�����
		len++;
	}

	void insert(int r, int c, int val) { //���Ӱ}�C��i�s���}�C��
		if (r > row || c > col) {
			return;
		}
		else///�ݫ��]��???
		{
			//��data����0�C�s�J�A��}�C���C�ơB��ơB�D0���Ȫ��ƶq///1
			data[len][0] = r;
			data[len][1] = c;
			data[len][2] = val;

			data[0][2] = len;//�]���A�|�@���b�[val

			//��w�p�s�Jdata���C����m�����
			len++;
		}
	}

	void matrix_to_threeCol(int row, int col, int arr[][12]) { //��}���x�}�ܦ��T��}�C//�̭��|��insert
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (arr[i][j] != 0) {
					insert(i, j, arr[i][j]);
				}
			}
		}
	}

	void threeCol_plus(sparse_matrix a, sparse_matrix b) {

		//�]��i,j���|�u�Φbfor�j��A�ҥH�n�ƥ��ŧi
		int i, j;

		//a�Bb���q��1�C�}�l�˵��A����a�Bb�䤤�@�Ө�Fdata���C�ƪ��W��
		for (i = 1, j = 1; i < a.len/*a����*/ && j < b.len/*b����*/;) { //->���JC�����C

			//�p��a��i�C�Mb��j�C���s����m
			int pos_a = a.data[i][0] * a.data[0][1] + a.data[i][1];///�N�O�ĴX�C���
			int pos_b = b.data[j][0] * b.data[0][1] + b.data[j][1];///�ڭ̬O�@�C�@�C�h�ݪ�

			//�p�Ga���s����m����e���A�h���Ja����i�C
			if (pos_a< pos_b/*�̭��|�Ψ�insert*/) {
				insert(a.data[i][0], a.data[i][1], a.data[i][2]);
				i++;
			}

			//�p�Gb���s����m����e���A�h���Jb����j�C
			else if (pos_a > pos_b) {
				insert(b.data[j][0], b.data[j][1], b.data[j][2]);
				j++;
			}

			/*�p�Ga�Bb���s����m�ۦP�B�ۥ[�ᤣ��0�A
			�h���J a��i�C���C�B��Aa+b����*/
			else if (pos_a == pos_b) {
				//�ۥ[�ᬰ0
				if (a.data[i][2] + b.data[j][2] != 0) {
					insert(a.data[i][0], a.data[i][1], a.data[i][2] + b.data[j][2]);///�P�@�Ӧ�m�ҥH�S�����Y�A�᭱���ȬO��Ӭۥ[
				}
				i++;
				j++;
			}
		}

		//�Na���ѤU��data�����v�C�[�J��s���T��}�C��
		while (i < a.len) {
			insert(a.data[i][0], a.data[i][1], a.data[i][2]);
			i++;
		}

		//�Nb���ѤU��data�����v�C�[�J��s���T��}�C��
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
			cout << i << "\t" << data[i][0] << "\t " << data[i][1]<< "\t " << data[i][2] << endl;
			if (i == 0)///0�O�e���� 0 10 12 9
				cout << endl;
		}
		/*�L�X�ۥ[�᪺�}���x�} ? ? ? ? ? ���F���Ʀr���a���L��0 ? ? ?������������
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