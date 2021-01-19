#include <string>
using namespace std;

class Coord;
class Rect;
class Polar;

class Coord {
public:
	void set_origin(char _origin[], int l);
	void set_name(char _name[], int l);
	void show();
private:
	char* origin;
	char* name;
	int originL;
	int nameL;
};

class Polar : public  Coord {
private:
	double distance;
	double angle;
public:
	Polar(double distance, double angle);
	void show();
	double getx();
	double gety();
	Polar operator +(const Polar& p);
	Polar operator -(const Polar& p);
	operator Rect();
};

class Rect : public  Coord {
private:
	double x;
	double y;
public:
	Rect(double x, double y);
	void show();
	Rect operator+(const Rect& r);
	Rect operator-(const Rect& r);
	operator Polar();
};

class Matrix_COO {
private:
	string input;
	int* rowArr;
	int* colArr;
	double* valArr;
	int nnz;
public:
	Matrix_COO(string filePath);
	~Matrix_COO();
	void show();
};

class Exception {
public:
	Exception();
};

class FileOpenException : public Exception {
public:
	FileOpenException();
};

class NotIntegerException : public Exception {
public:
	NotIntegerException();
};

class EndOfFileException : public Exception {
public:
	EndOfFileException();
};