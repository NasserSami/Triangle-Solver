/*
Author: Sami Nasser
Date: January 30,2023
Purpose: This program solves for missing properties of a triangle given its sides and/or angles


*/


#define _USE_MATH_DEFINES
#define BUFFER 100
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>



/*
\fn: toUpper(char str[]) 
\brief: converts an entire c-string to upper case
\param: takens in a c-string and is processed at each index
\return: returns a c-string with modified chars that are upper case
*/
char toUpper(char str[]) 
{
	for (size_t i = 0; i < strlen(str); i++)
	{
		str[i] = toupper(str[i]);
	}
	return str;
}

/*
\fn: toDegrees(double num)
\brief: converts radians to degrees
\param: takes a double that is modified using a conversion formula
\return: returns the final result representing a double in degrees
*/
double toDegrees(double num)
{
	const double DEGREE180 = 180;

	return num *= (DEGREE180 / M_PI);
}

/*
\fn: toRadians(double num)
\brief: converts degrees to radians
\param: takes a double that is modified using a conversion formula
\return: returns the final result representing a double in radians
*/
double toRadians(double num)
{
	const double DEGREE180 = 180;

	return num *= (M_PI / DEGREE180);
}

/*
\fn: getPerimeter(double numA, double numB, double numC)
\brief: calculates the perimeter of a triangle
\param: takes all three double type args and addes them together
\return: returns the final result representing a double as the perimeter
*/
double getPerimeter(double numA, double numB, double numC)
{
	return numA + numB + numC;
}

/*
\fn: getArea(double numA,double numB,double numC)
\brief: calculates the area of a triangle
\param: takes all three double type args and uses them in a formula to find the area
\return: returns the final result representing a double as the area
*/
double getArea(double numA,double numB,double numC)
{
	double s = (numA + numB + numC) / 2;
	
	return sqrt(s * (s - numA) * (s - numB) * (s - numC));
}


/*
\fn: getTypeTriangleLengths(double numA, double numB,double numC)
\brief: finds the type of triangle based on the measurment of the sides
\param: takes all three double type args and uses them to compare the lengths to each other
\return: does not return anything, only prints a statement
*/
void getTypeTriangleLengths(double numA, double numB,double numC)
{
	if (numA == numB == numC)
	{
		printf("equilateral, ");
	}
	else if (numA == numB || numB == numC || numC == numA)
	{
		printf("Isosceles, ");
	}
	else
	{
		printf("Scalene, ");
	}
}

/*
\fn: getTypeTriangleAngle(double alpha, double beta, double gamma)
\brief: finds the type of triangle based on the inside angles
\param: takes all three double type args and compares them to a constant
\return: does not return anything, only prints a statement
*/
void getTypeTriangleAngle(double alpha, double beta, double gamma)
{
	const int D90 = 90;

	if (alpha < D90 && beta < D90 && gamma < D90)
	{
		printf("acute");
	}
	else if (alpha == 90 || beta == 90 || gamma == 90)
	{
		printf("right");
	}
	else
	{
		printf("obtuse");
	}

}

/*
\fn: getTriangleSolution(char str[], double numA, double numB, double numC)
\brief: calculates the solution of a triangle based on the user input and the sides/angles they provide
\param: takes all three double type  and cstring args and uses them in multiple formulas based on the user input
\return: does not return anything, only prints a statement of the final results
*/
void getTriangleSolution(char str[], double numA, double numB, double numC)
{

	double alpha = 0.0; //α
	double beta = 0.0; // β
	double gamma = 0.0;// γ
	double gammaPrime = 0.0;
	double perimeter = 0.0;
	double perimeter2 = 0.0;
	double area = 0.0;
	double area2 = 0.0;
	double numA2 = 0.0;
	double alpha2 = 0.0;

	toUpper(str);

	numA = fabs(numA);
	numB = fabs(numB);
	numC = fabs(numC);

	//the situation based on user input
	if (strcmp(str, "SSS") == 0)
	{
		alpha = acos((numB * numB + numC * numC - numA * numA) / (2 * numB * numC));
		beta = acos((numA * numA + numC * numC - numB * numB) / (2 * numA * numC));
		gamma = M_PI - alpha - beta;

	}
	else if (strcmp(str, "SSA") == 0)
	{

		beta = numC;
		numC = numB;
		numB = numA;

		beta = toRadians(beta);
		gamma = (numC / numB) * sin(beta);

		if (gamma < 1 && numB >= numC)
		{
			gamma = asin(gamma);
			alpha = M_PI - beta - gamma;
			numA = numB * sin(alpha) / sin(beta);

		}
		else if (gamma < 1 && numB < numC)
		{
			gamma = asin(gamma);
			gammaPrime = M_PI - gamma;

			alpha = M_PI - beta - gamma;
			alpha2 = M_PI - beta - gammaPrime;

			numA = numB * sin(alpha) / sin(beta);
			numA2 = numB * sin(alpha2) / sin(beta);

			alpha2 = toDegrees(alpha2);
			gammaPrime = toDegrees(gammaPrime);

			perimeter2 = getPerimeter(numA2, numB, numC);
			area2 = getArea(numA2, numB, numC);

		}


	}
	else if (strcmp(str, "SAS") == 0)
	{
		gamma = numB;
		numB = numC;

		gamma = toRadians(gamma);

		numC = sqrt((numA * numA) + (numB * numB) - (2 * numA * numB * (cos(gamma))));
		alpha = acos(((numB * numB) + (numC * numC) - (numA * numA)) / (2 * numB * numC));
		beta = M_PI - alpha - gamma;

	}
	else if (strcmp(str, "ASA") == 0)
	{
		alpha = numA;
		beta = numC;
		numC = numB;

		alpha = toRadians(alpha);
		beta = toRadians(beta);
		gamma = M_PI - alpha - beta;

		numA = numC * ((sin(alpha)) / (sin(gamma)));
		numB = numC * ((sin(beta)) / (sin(gamma)));

		

	}

	alpha = toDegrees(alpha);
	beta = toDegrees(beta);
	gamma = toDegrees(gamma);

	perimeter = getPerimeter(numA, numB, numC);
	area = getArea(numA, numB, numC);

	//checks to make sure triangle is possible
	if (isnan(alpha) || isnan(beta) || isnan(gamma) || area == 0 || (beta >= 90 && numB <= numC && strcmp(str, "SSA") == 0))
	{
		printf("Format: %s\n", str);
		printf("Impossible triangle\n");

	}
	else
	{
		
		printf("\nFormat: %s\n", str);
		if (strcmp(str, "SSA") == 0 && gammaPrime > 0)
		{
			printf("--> gamma\n");
		}
		printf("%-7s%-10.3lf%-7s%10.3lf\n", "a =", numA, "alpha =", alpha);
		printf("%-7s%-10.3lf%-7s%10.3lf\n", "b =", numB, "beta  =", beta);
		printf("%-7s%-10.3lf%-7s%10.3lf\n", "c =", numC, "gamma =", gamma);
		printf("%s%10.3lf\n", "Perimeter =", perimeter);
		printf("%s%10.3lf\n", "Area      =", area);
		printf("%s", "Type      = ");
		getTypeTriangleLengths(numA, numB, numC);
		getTypeTriangleAngle(alpha, beta, gamma);
		printf("\n");

		if (strcmp(str, "SSA") == 0 && gammaPrime > 0)
		{
			printf("\n");
			printf("--> gamma'\n");
			printf("%-7s%.3lf      %-5s   %.3lf\n", "a =", numA2, "alpha =", alpha2);
			printf("%-7s%.3lf      %-5s   %.3lf\n", "b =", numB, "beta  =", beta);
			printf("%-7s%.3lf      %-5s   %.3lf\n", "c =", numC, "gamma =", gamma);
			printf("%s%10.3lf\n", "Perimeter =", perimeter2);
			printf("%s%10.3lf\n", "Area      =", area2);
			printf("%s", "Type      = ");
			getTypeTriangleLengths(numA2, numB, numC);
			getTypeTriangleAngle(alpha2, beta, gamma);
			printf("\n");
		}

	}
	
	
}

int main()
{
	double valA = 0.0;
	double valB = 0.0;
	double valC = 0.0;
	char anyCharacter = {'\0'};
	int read = 0;
	int isDigit = 0;
	int isPunct = 0;
	bool flag = true;
	char situation[BUFFER + 1] = { '\0' };
	char formatString[BUFFER + 1] = { '\0' };

	printf("TriSolver 1.0.0 (c) 2023, Sam Nasser\n");

	do

	{
		printf("\n-> ");
		gets_s(formatString, BUFFER); // gets everything on one line
		read = sscanf_s(formatString,"%s%lf%lf%lf%c", situation, BUFFER, &valA, &valB, &valC, &anyCharacter);//then sscan_f makes sure it is valid input 
		toUpper(situation);
		isDigit = isdigit(situation[0]);
		isPunct = ispunct(situation[0]);

		//input validation starts here
		if (strcmp(situation, "QUIT") == 0 || strcmp(situation, "BYE") == 0 || strcmp(situation, "EXIT") == 0)
		{
			return EXIT_SUCCESS;
		}
		else if (read != 4 || isDigit != 0 || isPunct != 0)
		{
			printf("Bad command : Format # # #\n");
			printf("where Format = SSS | SAS | ASA | SSA\n");
			printf("\t# = a real number\n");
		}
		else if(strcmp(situation,"SSS") != 0 && strcmp(situation, "SSA") != 0 && strcmp(situation, "SAS") != 0 && strcmp(situation, "ASA") != 0)
		{
			printf("Unknown command triangle format \'%s\'\n", situation);
			
		}
		else
		{
			getTriangleSolution(situation, valA, valB, valC);
		}


	}while (flag);	//loops unit user enters break words above

}