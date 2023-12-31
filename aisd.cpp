﻿#pragma once
#include <iostream>
#include <fstream>

using namespace std;

double power(double x, int n) {
	if (!n) return 1;
	else if (n >= 1) return x * power(x, n - 1);
	else return 1 / x * power(x, n + 1);
}

int C(int m, int n) {
	if (m == 0 || m == n) return 1;
	else return C(m, n - 1) + C(m - 1, n - 1);
}

inline bool sgn(double x) {
	return x >= 0;
}

double root(double (*f)(double), double a, double b, double ep) {
	if (abs(a - b) < ep) return a;
	double x = (a + b) / 2;
	bool s1 = sgn(f(a)), s2 = sgn(f(b));
	if (sgn(f(x)) != s1) return root(f, a, x, ep);
	else return root(f, x, b, ep);
}

bool isPower(int k, int n) {
	if (k == 1) return true;
	if (!(k % n)) return isPower(k / n, n);
	else return false;
}

int mymin(int* arr, int len) {
	int _min = arr[0];
	if (len > 1) {
		int t = mymin(arr + 1, len - 1);
		_min = t < _min ? t : _min;
	}
	return _min;
}

int countMax(int* arr, int size, int maxElement, int count) {
	if (size == 0)
		return count;
	if (arr[0] == maxElement)
		count++;
	else if (arr[0] > maxElement) {
		count = 1;
		maxElement = arr[0];
	}
	return countMax(arr + 1, size - 1, maxElement, count);
}

void binarySequences(int n, int* arr, int i) {
	if (i == n) {
		for (int i = 0; i < n; i++) {
			cout << arr[i];
		}
		cout << endl;
		return;
	}
	arr[i] = 0;
	binarySequences(n, arr, i + 1);
	arr[i] = 1;
	binarySequences(n, arr, i + 1);
}

int sumPos(ifstream& in) {
	if (in.eof()) return 0;
	int a; in >> a;
	if (a > 0) return a + sumPos(in);
	else return sumPos(in);
}

int formula(ifstream& in) {
	char c;
	in >> c;
	if (c >= '0' && c <= '9') {
		return c - '0';
	}
	if (c == '(') {
		int a = formula(in);
		char operation; in >> operation;
		int b = formula(in);
		switch (operation) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			return a / b;
		}
	}
}

bool check(ifstream& in) {
	char c;
	in.get(c);
	if (c >= '0' && c <= '9') return true;
	if (c != '(') return false;
	if (!check(in)) return false;
	in.get(c);
	if (c != '+' && c != '-' && c != '*' && c != '/') return false;
	if (!check(in)) return false;
	in.get(c);
	if (c != ')') return false;
	return true;
}

bool boolFormula(ifstream& in) {
	char c;
	in.get(c);
	if (c == 'n') return !boolFormula(in);
	if (c == 't') return true;
	if (c == 'f') return false;
	if (c == '(') {
		bool a = boolFormula(in);
		char op = in.get();
		bool b = boolFormula(in);
		if (op == 'a') return a && b;
		if (op == 'o') return a || b;
	}
}

bool isBoolFormula(ifstream& in) {
	char c; in.get(c);
	if (c == 'n') if (isBoolFormula(in)) return true; else return false;
	if (c == 't' || c == 'f') return true;
	if (c != '(') return false;
	if (!isBoolFormula(in)) return false;
	in.get(c);
	if (!(c == 'a' || c == 'o')) return false;
	if (!isBoolFormula(in)) return false;
	in.get(c);
	if (c != ')') return false;
	return true;
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

struct elem {
	int a;
	elem* next;
};

void deleteList(elem*& top) {
	if (!top) return;
	deleteList(top->next);
	delete top;
	top = nullptr;
}

elem* createList(ifstream& in) {
	if (in.eof()) return nullptr;
	elem* top = new elem;
	in >> top->a;
	top->next = createList(in);
	return top;
}

int countx(elem* top, int x) {
	if (top == nullptr) return false;
	return int(x == top->a) + countx(top->next, x);
}

elem* removex(elem*& top, int x) {
	if (top->next == nullptr) return nullptr;
	if (top->a == x) {
		elem* t = top->next;
		delete top;
		top = t;
		return top;
	}
	else {
		top->next = removex(top->next, x);
		return top;
	}
}

void printList(elem* top) {
	while (top != nullptr) {
		cout << top->a << ' ';
		top = top->next;
	}
	cout << endl;
	return;
}

void addyafterx(elem* top, int x, int y) {
	if (top == nullptr) return;
	if (top->a == x) {
		top->next = new elem{ y, top->next };
		top = top->next;
	}
	addyafterx(top->next, x, y);
}

elem* copyList(elem* top) {
	if (top == nullptr) return nullptr;
	return new elem{ top->a, copyList(top->next) };
}

bool isEqual(elem* t1, elem* t2) {
	if (t1 && !t2 || !t1 && t2) return false;
	if (!t1 && !t2) return true;
	if (t1->a == t2->a) return isEqual(t1->next, t2->next);
	else return false;
}

int maxList(elem* q) {
	int m = q->a;
	if (q->next) {
		int r = maxList(q->next);
		m = r > m ? r : m;
	};
	return m;
}

void reverseprint(elem* l) {
	if (l->next) reverseprint(l->next);
	std::cout << l->a << ' ';
}

void delList(elem* l) {
	if (l->next) delList(l->next);
	delete l;
}

elem* unity(elem* t1, elem* t2) {
	elem* top;
	if (t1 && t2) {
		if (t1->a > t2->a) {
			top = new elem{ t2->a, unity(t1, t2->next) };
		}
		else {
			top = new elem{ t1->a, unity(t1->next, t2) };
		}
	}
	else if (t1 && !t2) {
		top = new elem{ t1->a, unity(t1->next, t2) };
	}
	else if (!t1 && t2) {
		top = new elem{ t2->a, unity(t1, t2->next) };
	}
	else return nullptr;
}

struct node {
	node* left;
	node* right;
	int a;
};

int countx(node* top, int x) {
	if (!top) {
		return 0;
	}
	if (top->a == x) {
		return 1 + countx(top->right, x) + countx(top->left, x);
	}
	else {
		return 0 + countx(top->left, x) + countx(top->right, x);
	}
}

int sumTree(node* top) {
	if (!top) return 0;
	return top->a + sumTree(top->left) + sumTree(top->right);
}

int depth(node* top) {
	if (!top) return -1;
	int l = depth(top->left), r = depth(top->right);
	return (l > r ? l : r) + 1;
}

int counton(node* top, int n) {
	if (!top) return 0;
	if (n == 0) return 1;
	return counton(top->left, n - 1) + counton(top->right, n - 1);
}

void deltree(node* top) {
	if (!top->left && !top->right) {
		delete top;
		return;
	}
	deltree(top->left);
	deltree(top->right);
}

node* cpytree(node* top) {
	if (!top) return nullptr;
	return new node{ cpytree(top->left), cpytree(top->right), top->a };
}

bool isequal(node* t1, node* t2) {
	if (!t1 || !t2) return true;
	else if (t1 && !t2 || !t1 && t2) return false;
	if (t1->a == t2->a) {
		return true && isequal(t1->left, t2->left) && isequal(t1->right, t2->right);
	}
	else return false;
}

void addx(node* top, int x) {
	if (top->a <= x) if (top->right == nullptr) top->right = new node{ nullptr, nullptr, x }; else addx(top->right, x);
	else {
		if (top->left == nullptr) top->left = new node{ nullptr,nullptr, x }; else addx(top->left, x);
	}
}

bool search(node* top, int x) {
	if (!top) return false;
	if (top->a == x) return true;
	if (x < top->a) return search(top->left, x);
	else return search(top->right, x);
}

node* deletenode(node* top, int x) {
	if (!top) return nullptr;
	if (top->a == x) {
		if (top->right) {
			node* res = new node{ top->left, top->right->right, top->right->a };
			delete top;
			return res;
		}
		else { delete top; return nullptr; }
	}
	if (x < top->a) top->left = deletenode(top->left, x);
	else top->right = deletenode(top->right, x);
	return top;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

template<class T>
void merge(T* arr, int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	T* Left = new T[n1], * Right = new T[n2];
	for (i = 0; i < n1; i++) {
		Left[i] = arr[left + i];
	}
	for (i = 0; i < n2; i++) {
		Right[i] = arr[mid + 1 + i];
	}

	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2) {
		if (Left[i] <= Right[j]) {
			arr[k] = Left[i];
			i++;
		}
		else {
			arr[k] = Right[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = Left[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = Right[j];
		j++;
		k++;
	}
	delete[] Left; delete[] Right;
}

template<class T>
void merge_sort(T* arr, int n) {
	int current;
	int left;

	for (current = 1; current <= n - 1; current *= 2) {
		for (left = 0; left < n - 1; left += 2 * current) {
			int m = left + current - 1 < n - 1 ? left + current - 1 : n - 1;
			int right = left + 2 * current - 1 ? left + 2 * current - 1 : n - 1;
			merge<T>(arr, left, m, right);
		}
	}
}

//int main() {
//	ifstream in("in.txt");
//	elem* top = createList(in);
//	cout << countx(top, 1) << '\n';
//	printList(top);
//	top = removex(top, 1);
//	addyafterx(top, 2, 3);
//	elem* tc = copyList(top);
//	printList(tc);
//	printList(top);
//	cout << isEqual(top, tc) << ' ' << maxList(top) << '\n'; reverseprint(top);
//	deleteList(top);
//}

int main() {
	ifstream in("in.txt");
	int* arr = new int[8];
	for (int i = 0; i < 8; i++) in >> arr[i];
	cout << countMax(arr, 8, arr[0], 0);
	in.close();
}

//int main() {
//	int n = 8;
//	int* arr = new int[n];
//	for (int i = 0; i < n; i++) cin >> arr[i];
//	node* root = new node{
//		new node{new node{new node{nullptr, nullptr, arr[7]}, nullptr, arr[3]}, new node{nullptr, nullptr, arr[4]}, arr[1]},	new node{new node{nullptr, nullptr, arr[5]},new node{nullptr, nullptr, arr[6]}, arr[2]} , arr[0]
//	};
//	cout << countx(root, 2) << '\n' << sumTree(root);
//}