#include <math.h> 
#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include "Header.h";

const double PI = 4 * atan(1);
const double DEG_2_RAD = PI / 180;
const double RAD_2_DEG = 180 / PI;

// Q1 coord
void Coord::set_origin(char _origin[], int l) {
	originL = l;
	origin = _origin;
}

void Coord::set_name(char _name[], int l) {
	nameL = l;
	name = _name;
}

void Coord::show() {
	cout << "name: ";
	for (int i = 0; i < nameL; i++) {
		cout << name[i];
	}
	cout << ", origin: ";
	for (int i = 0; i < originL; i++) {
		cout << origin[i];
	}
	cout << endl;
}


// Q1 polar
Polar::Polar(double _distance, double _angle) {
	distance = _distance;
	angle = _angle;
}

void Polar::show() {
	cout << "distance: " << distance << ", angle: " << angle << endl;
}

double Polar::getx() {
	return distance * tan(angle * DEG_2_RAD);
}

double Polar::gety() {
	return distance * sin(angle * DEG_2_RAD);
}

Polar::operator Rect() {
	double x = getx();
	double y = gety();
	Rect r(x, y);
	return r;
}

Polar Polar::operator+(const Polar& p) {
	Polar polar(p.distance, p.angle);
	Rect r1(getx(), gety());
	Rect r2 = polar;
	Rect r3 = r1 + r2;

	return r3;
}

Polar Polar::operator-(const Polar& p) {
	Polar polar(p.distance, p.angle);
	Rect r1(getx(), gety());
	Rect r2 = polar;
	Rect r3 = r1 - r2;

	return r3;
}

// Q1 rect
Rect::Rect(double _x, double _y) {
	x = _x;
	y = _y;
}

void Rect::show() {
	cout << "x: " << x << ", y: " << y << endl;
}

Rect::operator Polar() {
	double distance = sqrt(pow(x, 2) + pow(y, 2));
	double angle = 0;
	if (x > 0) angle = atan(y / x) * RAD_2_DEG;
	else if (x < y && y >= 0) angle = (atan(y / x) + PI) * RAD_2_DEG;
	else if (x < 0 && y < 0) angle = (atan(y / x) - PI) * RAD_2_DEG;
	else if (x == 0 && y < 0) angle = PI * RAD_2_DEG;
	else if (x == 0 && y == 0) angle = 0;
	Polar p(distance, angle);
	return p;
}

Rect Rect::operator+(const Rect & r) {
	Rect rect(r.x, r.y);
	rect.x += x;
	rect.y += y;
	return rect;
}

Rect Rect::operator-(const Rect & r) {
	Rect rect(r.x, r.y);
	rect.x = x - rect.x;
	rect.y = y - rect.y;
	return rect;
}

// Q2 swaps_arr
template <typename T, typename T2>

void swaps_arr(T a1[], T2 a2[], int index) { // interchanges the values of the two array arguments sent to it from index 0 to N
	for (int i = 0; i <= index; i++) {
		T temp = a1[i];
		a1[i] = a2[i];
		a2[i] = temp;
	}
}

// Q3,Q4 matrix
Matrix_COO::Matrix_COO(string fileName) {
	try {
		ifstream MatrixFile(fileName);
		if (!MatrixFile.good()) { // open the file with that name (if it cannot, then throw an exception
			throw (FileOpenException());
		}

		double _rows;
		double _cols;
		int rows;
		int cols;
		double val;
		int rowIndex = 1;
		int colIndex = 1;

		MatrixFile >> _rows;
		MatrixFile >> _cols;

		if (_rows != (int)_rows || _cols != (int)_cols) throw (NotIntegerException()); // be sure that first two entries are integers
		else {
			rows = _rows;
			cols = _cols;
		}

		nnz = 0;

		for (int i = 0; i < rows * cols; i++) {
			if (MatrixFile.peek() == EOF) throw(EndOfFileException()); // EOF check

			MatrixFile >> val;

			if (val != 0) nnz++; // count for the number of non - zero elements(NNZ)

			if (colIndex == cols) {
				colIndex = 1;
				rowIndex++;
			}
			else colIndex++;
		}

		MatrixFile.seekg(3); // take the iterator to the beginning of the file
		rowArr = new int[nnz]; // allocate memory for three arrays
		colArr = new int[nnz];
		valArr = new double[nnz];
		colIndex = 1; rowIndex = 1;
		int nnzIndex = 0;

		for (int i = 0; i < rows * cols; i++) { // 
			MatrixFile >> val;

			if (val != 0) {
				rowArr[nnzIndex] = rowIndex;
				colArr[nnzIndex] = colIndex;
				valArr[nnzIndex] = val;
				nnzIndex++;
			}

			if (colIndex == cols) {
				colIndex = 1;
				rowIndex++;
			}
			else colIndex++;
		}

		show();

		cout << "successfully read" << endl;
	}
	catch (FileOpenException ex) {
		cout << "can not open file" << endl;
	}
	catch (NotIntegerException ex) {
		cout << "first two entries are not integers" << endl;
	}
	catch (EndOfFileException ex) {
		cout << "End of file before matrix entries" << endl;
	}
}

void Matrix_COO::show() {
	for (int i = 0; i < nnz; i++) {
		cout << rowArr[i] << " " << colArr[i] << " " << valArr[i] << endl;
	}
}

Matrix_COO::~Matrix_COO() {
	delete[] rowArr;
	delete[] colArr;
	delete[] valArr;
}

// exceptions
Exception::Exception() {
}

FileOpenException::FileOpenException() : Exception() {
}

NotIntegerException::NotIntegerException() : Exception() {
}

EndOfFileException::EndOfFileException() : Exception() {
}


// main
int main() {

	Coord c;
	char name[] = { 'M','i','c','r','o','m','i','p','s' };
	char origin[] = { 'B','y','t','e','v','i','l','l','e' };
	c.set_name(name, sizeof(name));
	c.set_origin(origin, sizeof(origin));
	c.show();

	Rect r1(-1, 1);
	Rect r2(1, 2);
	Rect r3 = r1 + r2;
	Rect r4 = r1 - r2;
	r1.show();
	r2.show();
	r3.show();
	r4.show();

	Polar p1(1, 135);
	Polar p2(1, 45);
	Polar p3 = p1 + p2;
	Polar p4 = p1 - p2;
	p1.show();
	p2.show();
	p3.show();
	p4.show();

	Polar p5 = r1;
	Rect r5 = p1;

	int a[] = { 100, 200 };
	double b[] = { 2.2323, 4.4 };
	float cc[] = { 2234.2323, 4234.4 };
	swaps_arr<int, double>(a, b, 0);
	swaps_arr<int, float>(a, cc, 0);

	Matrix_COO m1("q3-input.txt");
	Matrix_COO m2("q4-input-exc2.txt");
	Matrix_COO m3("q4-input-exc3.txt");

	return 0;
}
