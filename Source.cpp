/*
Program to read fraction data from a text file and
store them in an array created using memory allocation.
Two structs are used.  One to define a Fraction, one to define a FractionArray.
Author:  Ryan Regan for CSE 153, Fall 2019
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cmath>


using namespace std;



struct Fraction
{
	int numerator;
	int denominator;
};


struct FractionArray
{
	Fraction* fractions;   //this will point to an array of fractions
	int nFractions;        //this will contain the number of elements in the array
};


bool readDataAndShowFractions(string filename, FractionArray& fractions);
bool readDataIntoArray(ifstream* infile, Fraction fractions[], int size);
Fraction newFraction(int num, int denom);
void printFractions(FractionArray fractions);
void reduce(Fraction& f);
int gcd(int x, int y);

//funtions to perform fraction arithmetic
Fraction add(Fraction op1, Fraction op2);
Fraction subtract(Fraction op1, Fraction op2);
Fraction multiply(Fraction op1, Fraction op2);
Fraction divide(Fraction op1, Fraction op2);



//used to convert an integer to a string
//to_string() is defined in the latest version of C++ but is not supported by older compilers

string tostring(int number);
string tostring(Fraction f);
double decdouble(Fraction f);



int main(int argc, char* argv[])
{
	//create two structs, one for each array 
	FractionArray fractions1;
	FractionArray fractions2;
	bool success;

	//initialize and output the first array of Fraction structs
	success = readDataAndShowFractions("fractiondata1.txt", fractions1);
	if (!success)
	{
		cout << "Fraction array could not be constructed from fractiondata1.txt" << endl;
		exit(-1);
	}

	//initialize and output the second array of Fraction structs
	success = readDataAndShowFractions("fractiondata2.txt", fractions2);
	if (!success)
	{
		cout << "Fraction array could not be constructed from fractiondata2.txt" << endl;
		exit(-1);
	}

	//make sure the arrays are of equal size
	if (fractions1.nFractions != fractions2.nFractions)
	{
		cout << "Fraction arrays are not the same size" << endl;
		exit(-1);
	}

	//loop through the Fraction arrays and output the results of
	//adding the fractions at each position
	for (int i = 0; i < fractions1.nFractions; i++)
	{
		Fraction result = add(fractions1.fractions[i],
			fractions2.fractions[i]);
		
		cout << tostring(fractions1.fractions[i]) << " + "
			<< tostring(fractions2.fractions[i]) << " = "
			<< tostring(result) << " or as a decimal: " << setprecision(2) << decdouble(result) << endl;
	}

	for (int i = 0; i < fractions1.nFractions; i++)
	{
		Fraction result = subtract(fractions1.fractions[i],
			fractions2.fractions[i]);
		cout << tostring(fractions1.fractions[i]) << " - "
			<< tostring(fractions2.fractions[i]) << " = "
			<< tostring(result) << " or as a decimal: " << setprecision(2) << decdouble(result) << endl;
	}

	for (int i = 0; i < fractions1.nFractions; i++)
	{
		Fraction result = multiply(fractions1.fractions[i],
			fractions2.fractions[i]);
		cout << tostring(fractions1.fractions[i]) << " * "
			<< tostring(fractions2.fractions[i]) << " = "
			<< tostring(result) << " or as a decimal: " << setprecision(2) << decdouble(result) << endl;
	}

	for (int i = 0; i < fractions1.nFractions; i++)
	{
		Fraction result = divide(fractions1.fractions[i],
			fractions2.fractions[i]);
		cout << tostring(fractions1.fractions[i]) << " / "
			<< tostring(fractions2.fractions[i]) << " = "
			<< tostring(result) << " or as a decimal: " << setprecision(2) << decdouble(result) << endl;
	}


	cin.get();

	return 0;
}


//adds the two fractions together, creates a new Fraction from the result and
//returns it
Fraction add(Fraction op1, Fraction op2)
{
	int num1;
	int num2;
	int denom;

	denom = op1.denominator * op2.denominator;
	num1 = (denom / op1.denominator) * op1.numerator;
	num2 = (denom / op2.denominator) * op2.numerator;

	Fraction result;
	result.numerator = num1 + num2;
	result.denominator = denom;

	reduce(result);
	return result;
}


//subtracts the two fractions together, creates a new Fraction from the result and returns it
Fraction subtract(Fraction op1, Fraction op2)
{
	int num1;
	int num2;
	int denom;

	denom = op1.denominator * op2.denominator;
	num1 = (denom / op1.denominator) * op1.numerator;
	num2 = (denom / op2.denominator) * op2.numerator;

	Fraction result;
	result.numerator = num1 - num2;
	result.denominator = denom;

	reduce(result);
	return result;

}

//multiplies the two fractions together, creates a new Fraction from the result and returns it
Fraction multiply(Fraction op1, Fraction op2)
{
	int num1;
	int num2;
	int denom;

	denom = op1.denominator * op2.denominator;
	num1 = op1.denominator * op1.numerator;
	num2 = op2.denominator * op2.numerator;

	Fraction result;
	result.numerator = num1 * num2;
	result.denominator = denom * denom;

	reduce(result);
	return result;

}

//divided the two fractions together, creates a new Fraction from the result and returns it
Fraction divide(Fraction op1, Fraction op2)
{
	int num1;
	int num2;
	int denom;

	denom = op1.denominator * op2.numerator;
	num1 = op1.denominator * op1.numerator;
	num2 = op2.denominator * op2.numerator;

	Fraction result;
	result.numerator = num1 * num2;
	result.denominator = denom * denom;

	reduce(result);
	return result;
	
}

//reduces the given fraction
//the fields of the given fraction can be changed
//since it is passed by reference
void reduce(Fraction& f)
{
	int factor = gcd(f.numerator, f.denominator);

	f.numerator = f.numerator / factor;
	f.denominator = f.denominator / factor;
}


//returns the greatest common denominator of two values
//(function is recursive)
int gcd(int x, int y)
{
	if (y == 0)
		return x;
	else
		return gcd(y, x % y);


}
Fraction newFraction(int num, int denom)
{
	Fraction f;

	f.numerator = num;
	f.denominator = denom;

	return f;
}

/*
Reads fraction data from the given file into the array
defined in the given struct.
Returns true if successful, false if any errors were encountered.
*/
bool readDataAndShowFractions(string filename, FractionArray& fractions)
{
	//read the size to make the array and create it
	ifstream* infile;
	infile = new ifstream(filename, ios::in);
	if (!infile->is_open())
		return false;

	//read the number of values into the struct variable and make
	//sure it is not 0
	if (*infile >> fractions.nFractions&& fractions.nFractions > 0)
	{
		fractions.fractions = new Fraction[fractions.nFractions];
		readDataIntoArray(infile, fractions.fractions, fractions.nFractions);
	}

	infile->close();
	printFractions(fractions);

	return true;
}


/* Given a pointer to an open file and an array, reads size data from the file
 and populates the array.*/
bool readDataIntoArray(ifstream* infile, Fraction fractions[], int size)
{
	int numerator;
	int denominator;
	double decVal;

	for (int i = 0; i < size; i++)
	{
		// read in the numerator and denominator, checking to see that we are not at
		// the end of file.  Note that this isn't perfectly safe, because if a denominator
		// is missing, our data will be off.

		*infile >> numerator;
		if (infile->eof())
			return false;

		*infile >> denominator;
		if (infile->eof())
			false;

		//Add a struct for the new fraction
		fractions[i] = newFraction(numerator, denominator);
	}

	return true;
}


void printFractions(FractionArray fractions)
{
	cout << "Fraction data from array" << endl;
	for (int i = 0; i < fractions.nFractions; i++)
	{
		cout << tostring(fractions.fractions[i]) << endl;
	}
	cout << endl;
}

// tostring() will convert an int value to a string.
// to_string() is defined in the latest version of C++ but is not supported by older compilers
string tostring(int number)
{
	const int size = sizeof(int) * 4;

	char buf[size + 1];
	sprintf_s(buf, "%d", number);
	return string(buf);
}


string tostring(Fraction f)
{
	string num = tostring(f.numerator);
	string denom = tostring(f.denominator);
	return num + "\\" + denom;
}

// function to make fraction a decimal
double decdouble(Fraction f)
{
	
	double decimal = 1.0 * f.numerator / f.denominator;
	return decimal;
}
