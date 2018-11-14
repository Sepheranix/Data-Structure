#include "headers.h"

using namespace std;

int main()
{
	BiTree T;
	CreateBiTree(T);
	cout << "Pre:";
	PreOrderTraverse(T, display);
	cout << endl;
	cout << "Pre2:";
	PreOrderTraverse2(T, display);
	cout << endl;

	cout << "In:";
	InOrderTraverse(T, display);
	cout << endl;
	cout << "In2:";
	InOrderTraverse2(T, display);
	cout << endl;
	cout << "In3:";
	InOrderTraverse3(T, display);
	cout << endl;

	cout << "Pos:";
	PosOrderTraverse(T, display);
	cout << endl;
	cout << "Pos2:";
	PostOrderTraverse2(T, display);
	cout << endl;

	cout << "Level:";
	LevelOrderTraverse(T, display);

	system("pause");
	return 0;
}
