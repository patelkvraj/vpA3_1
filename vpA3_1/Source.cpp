/*
AUTHOR:
_______

	Vraj K Patel

TOTAL FILES THE PROGRAM CONTAINS:
_________________________________

	Total files:	1
		1) Source.cpp


ABOUT THE PROGRAM:
__________________

	Part - 2
		Created on	:	11/19/2022
		Title (Name):	Assignment 3 (Part 1)
		Description	:	A program that computes and displays the charges for a patient's hospital stay 
						and write the report it creates to a file (named: "hospital.txt"). First, the program 
						ask if the patient was admitted as an inpatient or an outpatient.
						If the patient was an inpatient, the following data should enter:
							> The number of days spent in the hospital
							> The daily rate
							> Charges for hospital services (lab tests, etc.)
							> Hospital medication charges
						If the patient was an outpatient, the following data should be entered:
							> Charges for hospital services (lab tests, etc.)
							> Hospital medication charges
		Purpose		:	This program will compute patient's hospital charges (bill)
		Challenges	:	-


REVISION HISTORY:
_________________

	Date:				By:				Action:
	-------------------------------------------
*	11/19/2022			VP				I created the program and added code documentation.
*	11/20/2022			VP				I edited "About the program" section of the code documentation. I added a if/else statment for in-patient and out-patient. 
										Also, I added a loop that will repeat until the user enters a valid response for  if/else statement. I declared the variables
										used for In-patient. I added user prompts and cin statements for In-patient.
	11/20/2022			VP				I added a while loop (with switch statement inside it) inside validateData() function. I called validateData() function for each
										user response for In-patient. I changed the 2 parameter type from "string" to "char" in validateData() function. I added user 
										prompts and cin statements for Out-patient. I added the comment about validateData() function. I declared both overloaded patientCharges() function and added comment.	
										I created "hospital.txt" file for streaming data. I wrote appropriate code to stream data (total hospital charges) to the file. 
										I wrote the code to open, use and close the "hospital.txt" file.
	11/23/22			VP				I added design to "hospital.txt" file for better UX experience. I added two decimal notation setprecision() for floating-point values. 
	Later "Revision History" is on on GitHub
*/

// For every function
/*
Name:
Purpose:
Input:	// If any
Output:	// If any
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

/*	Function prototypes */
double validateData(double, char);
double patientCharges(int, double, double, double);		//	In-patient
double patientCharges(double, double);					//	out-patient

int main() {

	cout << "This program will compute patient hospital charges.\n";

	/* Declaring variables */
	string which_patient;			//	To hold patient's status (In-patient or Out-patient)

	ofstream outfile;				//	Define an instance of ofstream class
	outfile.open("hospital.txt");	//	Open a file

	/*** The loop will repeat until the user enters a valid response ***/
	while (true) {
		cout << "Enter 'I' for in-patient or 'O' for out-patient: ";
		cin >> which_patient;

		/** In-patient **/
		if (which_patient == "I" || which_patient == "i") {	//	Both alphabet cases works 
			
			/* Declaring variables */
			int days;										//	To hold days, a patient has spent in the hospital
			double room_rate,								//	To hold room's rate at the hospital
				   other_charges,							//	To hold a patient's other charges
				   med_charges;								//	To hold a patient's medication charges

			cout << "\n\n*********In-patient*********\n";
			
			cout << "\nNumber of days in the hospital: ";
			cin >> days;
			validateData(days, 'D');

			cout << "\nDaily room rate: $";
			cin >> room_rate;
			validateData(room_rate, 'R');

			cout << "\nLab fees and other service charges: $";
			cin >> other_charges;
			validateData(other_charges, 'O');

			cout << "\nMedication charges: $";
			cin >> med_charges;
			validateData(med_charges, 'M');

			patientCharges(days, room_rate, other_charges, med_charges);

			/* Streaming data to a file */
			outfile << "**************************\n";
			outfile << "Hospital Billing Statement\n";
			outfile << "**************************\n\n";
			outfile << setprecision(2) << fixed;					//	Decimal notation
			outfile << "Room charges    $" << setw(8) << room_rate << endl;	
			outfile << "Lab & Services  $" << setw(8) << other_charges << endl;
			outfile << "Medication      $" << setw(8) << med_charges << endl;
			outfile << "__________________________" << endl;
			outfile << "Total charges   $" << setw(8) << patientCharges(days, room_rate, other_charges, med_charges) << "\n\n";
			outfile << "**************************";
			
			cout << "\n=> The billing report has been written to the hospital.txt file.";
			break;													//	To skip the while loop
		}
		/** Out-patient **/
		else if (which_patient == "O" || which_patient == "o") {	//	Both alphabet cases works 

			/* Declaring variables */
			double other_charges,									//	To hold a patient's other charges
				   med_charges;										//	To hold a patient's medication charges

			cout << "\n\n*********Out-patient*********\n";
			
			cout << "\nLab fees and other service charges: $";
			cin >> other_charges;
			validateData(other_charges, 'O');

			cout << "\nMedication charges: $";
			cin >> med_charges;
			validateData(med_charges, 'M');

			/* Streaming data to a file */
			outfile << "**************************\n";
			outfile << "Hospital Billing Statement\n";
			outfile << "**************************\n\n";
			outfile << setprecision(2) << fixed;	//	Decimal notation
			outfile << "Lab & Services  $" << setw(8) << other_charges << endl;
			outfile << "Medication      $" << setw(8) << med_charges << endl;
			outfile << "__________________________" << endl;
			outfile << "Total charges   $" << setw(8) << patientCharges(other_charges, med_charges) << "\n\n";
			outfile << "**************************";
			
			cout << "\n=> The billing report has been written to the hospital.txt file.";
			break;									//	To skip the while loop
		}
		/** In case anything goes wrong **/
		else {
			cout << "\nWarning: Please enter a valid response.\n\n";
		}
	}

	outfile.close();	//	Close a file
	cout << "\n\n";		//	To have some space at the end of the program
	return 0;			//	No return 
}	//	End of the main function

/*
****************************************************
Name	:	validateData()
Purpose	:	To valid no user input is less than zero
Input	:	double, char
Output	:	double
****************************************************
*/
double validateData(double number, char which_charge) {
	while (number < 0) {
		cout << "\nWarning: Please enter a valid response.\n\n";

		/** A switch statement to give the user another attempt to enter a valid reponse **/
		switch (which_charge) {
			case 'D': {	//	Room's rate at the hospital
				cout << "Number of days in the hospital: ";
				cin >> number;
				break;
			}			
			case 'R': {	//	Room's rate at the hospital
				cout << "Daily room rate: $";
				cin >> number;
				break;
			}
			case 'O': {	//	A patient's other charges
				cout << "Lab fees and other service charges: $";
				cin >> number;
				break;
			}
			case 'M': {	//	A patient's medication charges
				cout << "Medication charges: $";
				cin >> number;
				break;
			}
			default: {	//	In case something goes wrong
				cout << "\nWarning: Something went wrong. Please run the program again.";
			}
		}
	}
	return number;		//	Return the valid reponse
}

/*
****************************************************
Name	:	patientCharges()
Purpose	:	To calculate the total hospital charges of a patient 
Input	:	int, double, double, double
Output	:	double
****************************************************
*/
double patientCharges(int days, double room_rate, double other_charges, double med_charges) {
	return ((days * room_rate) + other_charges + med_charges) ;	//	Return the total charges
}

/*
Name	:	patientCharges()
Purpose	:	To calculate the total hospital charges of a patient
Input	:	double, double
Output	:	double
*/
double patientCharges(double other_charges, double med_charges) {
	return (other_charges + med_charges) ;	//	Return the total charges
}



