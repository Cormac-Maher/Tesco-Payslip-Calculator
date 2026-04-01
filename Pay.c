#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define TAX_CREDIT 76.93
#define PAYRATE 14.44
#define STANDARD_BAND 846.16

typedef struct {
	float weeklyHrs;
	float premiumHrs;
	float grossPay;
	float totalTax;
	float totalPay;
	int day, month, year;
} PayslipT;

void createPayslip(PayslipT* p);
void savePayslipToFile(PayslipT p);
float calculatePAYETax(float grossPay);
float calculatePRSITax(float grossPay);

//void displayPayslip(PayslipT p);

float payRate[3] = { PAYRATE, PAYRATE * 1.5, PAYRATE * 2 };

void main()
{
	int choice;
	PayslipT p;

	do
	{
		printf("----------------MENU-----------------\n");
		printf("Enter 1 to create a new payslip\n");
		printf("Enter 2 to save a payslip to file\n");
		printf("Enter 3 to display a previous payslip\n");
		printf("Enter -1 to exit\n");
		scanf("%d", &choice);

		if (choice == 1) {
			createPayslip(&p);
		}
		else if (choice == 2) {
			savePayslipToFile(p);
		}
		else if (choice == 3) {
//			displayPayslip(p);
		}

	} while (choice != -1);
}

void createPayslip(PayslipT *p) {

	char days[7][10] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	float hrsWorked = 0; 
	p->weeklyHrs = 0;
	p->premiumHrs = 0;

	printf("Enter payslip date (DD MM YYYY): ");
	scanf("%d %d %d", &p->day, &p->month, &p->year);

	for (int i = 0; i < 7; i++) {

		do {
			printf("Hours worked on %s: ", days[i]);
			scanf("%f", &hrsWorked);
		} while (hrsWorked < 0 || hrsWorked > 20);

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
			p->premiumHrs += hrsWorked;			// Sunday hours are paid at a 1.5x rate
		}
		else
		{
			p->weeklyHrs += hrsWorked;
		}
		hrsWorked = 0;
	}

	p->grossPay = (p->weeklyHrs * payRate[0]) + (p->premiumHrs * payRate[1]);				// Calculate total pay before tax
	p->totalTax = calculatePAYETax(p->grossPay) + calculatePRSITax(p->grossPay);
	p->totalPay = p->grossPay - p->totalTax;                                                  
;																							// Calculate total pay after tax

	printf("\n======================================\n");
	printf("            TESCO PAYSLIP            \n");
	printf("Payslip Date: %02d/%02d/%04d\n", p->day, p->month, p->year);
	printf("======================================\n");
	printf("Hours worked: %.2f\n", p->weeklyHrs + p->premiumHrs);
	printf("Standard Pay: %.2f\n", p->weeklyHrs * PAYRATE);
	printf("Premium Pay: %.2f\n", p->premiumHrs * PAYRATE * 1.5);
	printf("--------------------------------------\n");
	printf("Gross Pay: %.2f\n", p->grossPay);
	printf("PAYE tax: %.2f\n", calculatePAYETax(p->grossPay));
	printf("PRSI tax: %.2f\n", calculatePRSITax(p->grossPay));
	printf("--------------------------------------\n");
	printf("Total pay: %.2f\n", p->totalPay);
	printf("======================================\n\n");
}                                                    

void savePayslipToFile(PayslipT p) 
{
	FILE* file;

	file = fopen("TescoPayslips.txt", "a");

	if (file == NULL) {
		printf("Error opening file!\n");
		return;
	}

	fprintf(file, "\n======================================\n");
	fprintf(file, "            TESCO PAYSLIP            \n");
	fprintf(file, "Payslip Date: %02d/%02d/%04d\n", p.day, p.month, p.year);
	fprintf(file, "======================================\n");
	fprintf(file, "Hours worked: %.2f\n", p.weeklyHrs + p.premiumHrs);
	fprintf(file, "Standard Pay: %.2f\n", p.weeklyHrs * PAYRATE);
	fprintf(file, "Premium Pay: %.2f\n", p.premiumHrs * PAYRATE * 1.5);
	fprintf(file, "--------------------------------------\n");
	fprintf(file, "Gross Pay: %.2f\n", p.grossPay);
	fprintf(file, "PAYE tax: %.2f\n", calculatePAYETax(p.grossPay));
	fprintf(file, "PRSI tax: %.2f\n", calculatePRSITax(p.grossPay));
	fprintf(file, "--------------------------------------\n");
	fprintf(file, "Total pay: %.2f\n", p.totalPay);
	fprintf(file, "======================================\n");
}

float calculatePAYETax(float grossPay) 
{
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
