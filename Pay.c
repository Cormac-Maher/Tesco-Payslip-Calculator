#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define TAX_CREDIT 76.93
#define PAYRATE 14.44
#define STANDARD_BAND 846.16

float calculateTax(float grossPay);
float calculatePAYETax(float grossPay);
float calculatePRSITax(float grossPay);
void createPayslip();
void savePayslipToFile();


float hrsWorked, weeklyHrs = 0, premiumHrs = 0, grossPay, holidayHours, totalTax, totalPay;
float payRate[3] = { PAYRATE, PAYRATE * 1.5, PAYRATE * 2 };
char days[7][10] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

void main()
{
	int choice;

	do
	{
		printf("Please 1 to create a new payslip\n");
		printf("Enter 2 to save a payslip to file\n");
		printf("Please 3 to display all previous payslips\n");
		printf("Please -1 to exit\n");
		scanf("%d", &choice);

		if (choice == 1) {
			createPayslip();
		}
		else if (choice == 2) {
			savePayslipToFile();
		}
		else if (choice == 3) {
			createPayslip();
		}

	} while (choice != -1);
}

void createPayslip() {

	for (int i = 0; i < 7; i++) {
		printf("How many hours did you work on %s? ", days[i]);
		scanf("%f", &hrsWorked);
		if (hrsWorked >= 7)
		{
			hrsWorked -= 1;          // 1 hour unpaid break for 7 or more hours worked
		}
		else if (hrsWorked == 6)
		{
			hrsWorked -= 0.5;       // 0.5 hour unpaid break for 6 hours worked
		}
		if (i == 0)
		{
			premiumHrs += hrsWorked;			// Sunday hours are paid at a 1.5x rate
		}
		else
		{
			weeklyHrs += hrsWorked;
		}
		hrsWorked = 0;
	}

	grossPay = (weeklyHrs * payRate[0]) + (premiumHrs * payRate[1]);          // Calculate total pay before tax
	totalTax = calculatePAYETax(grossPay) + calculatePRSITax(grossPay);												// Calculate total tax
	totalPay = grossPay - totalTax;																							// Calculate total pay after tax

	printf("\n==========PROTOTYPE PAYSLIP===========\n");
	printf("======================================\n");
	printf("Hours worked: %.2f\n", weeklyHrs + premiumHrs);
	printf("Pay before tax: %.2f\n", grossPay);

	printf("PAYE tax: %.2f\n", calculatePAYETax(grossPay));
	printf("PRSI tax: %.2f\n", calculatePRSITax(grossPay));

	printf("Total pay: %.2f\n", totalPay);

	printf("======================================\n");
}

void savePayslipToFile() 
{
	FILE* file;

	file = fopen("TescoPayslips.txt", "a");

	if (file == NULL) {
		printf("Error opening file!\n");
		return;
	}

	fprintf(file, "==========PROTOTYPE PAYSLIP===========\n");
	fprintf(file, "======================================\n");
	fprintf(file, "Hours worked: %.2f\n", weeklyHrs + premiumHrs);
	fprintf(file, "Pay before tax: %.2f\n", grossPay);

	fprintf(file, "PAYE tax: %.2f\n", calculatePAYETax(grossPay));
	fprintf(file, "PRSI tax: %.2f\n", calculatePRSITax(grossPay));

	fprintf(file, "Total pay: %.2f\n", totalPay);
	fprintf(file, "======================================\n");
	fclose(file);
	printf("Payslip saved successfully!\n");
}

float calculatePAYETax(float grossPay) {
	float PAYE_tax = 0, upperBand;
	if (grossPay > STANDARD_BAND) {
		upperBand = (grossPay - STANDARD_BAND) * 0.4;
		PAYE_tax = (STANDARD_BAND * 0.2) + upperBand;
	}
	else
	{
		PAYE_tax = grossPay * 0.2;
	}

	PAYE_tax -= TAX_CREDIT;
	if (PAYE_tax < 0) PAYE_tax = 0;
	return PAYE_tax;
}
float calculatePRSITax(float grossPay) 
{
	float PRSI_tax = 0, PRSI_credit = 12 * (1 - ((grossPay - 352) / 72));
	if (grossPay <= 352) {
		PRSI_tax = 0;
	}
	else if (grossPay >= 352.01 && grossPay <= 424) {
		PRSI_tax = (grossPay * 0.042) - PRSI_credit;
		if (0 > PRSI_tax) PRSI_tax = 0;
	}
	else if (grossPay >= 424.01) {
		PRSI_tax = grossPay * 0.042;
	}
	return PRSI_tax;
}


float calculateTax(float grossPay) {
	float PAYE_tax = 0, PRSI_tax = 0, upperBand;
	float PRSI_credit = 12 * (1 - ((grossPay - 352) / 72));

	if (grossPay > STANDARD_BAND) {
		upperBand = (grossPay - STANDARD_BAND) * 0.4;
		PAYE_tax = (STANDARD_BAND * 0.2) + upperBand;
	}
	else
	{
		PAYE_tax = grossPay * 0.2;
	}

	PAYE_tax -= TAX_CREDIT;
	if (PAYE_tax < 0) PAYE_tax = 0;

	if (grossPay <= 352) {
		PRSI_tax = 0;
	}
	else if (grossPay >= 352.01 && grossPay <= 424) {
		PRSI_tax = (grossPay * 0.042) - PRSI_credit;
		if (0 > PRSI_tax) PRSI_tax = 0;
	}
	else if (grossPay >= 424.01) {
		PRSI_tax = grossPay * 0.042;
	}

	printf("PAYE tax: %.2f\n", PAYE_tax);
	printf("PRSI tax: %.2f\n", PRSI_tax);

	return PAYE_tax + PRSI_tax;
}
