#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define TAX_CREDIT 76.93
#define PAYRATE 14.44
#define STANDARD_BAND 846.16

float calculateTax(float grossPay);

void main()
{
	float hrsWorked, weeklyHrs = 0, premiumHrs = 0, totalPay, holidayHours;
	float payRate[3] = { PAYRATE, PAYRATE*1.5, PAYRATE*2};
	char days[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

	for (int i = 0; i < 7; i++){
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

	totalPay = (weeklyHrs * payRate[0]) + (premiumHrs * payRate[1]);          // Calculate total pay before tax


	printf("\n==========PROTOTYPE PAYSLIP===========\n");
	printf("======================================\n");
	printf("Your total hours worked is: %.2f\n", weeklyHrs + premiumHrs);

	printf("Your total pay before tax is is: %.2f\n", totalPay);
	printf("Your gross pay after tax is is: %.2f", totalPay - calculateTax(totalPay));


	printf("\n======================================\n");


}

float calculateTax(float grossPay) {
	float PAYE_tax = 0, PRSI_tax = 0, upperBand;
	float PRSI_credit = 12*(1-((grossPay-352)/72));

	if (grossPay > STANDARD_BAND) {
		upperBand = (grossPay - STANDARD_BAND)*0.4;
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
		PRSI_tax = (grossPay*0.042) - PRSI_credit;
		if (0 > PRSI_tax) PRSI_tax = 0;
	}
	else if (grossPay >= 424.01) {
		PRSI_tax = grossPay * 0.042;
	}

	printf("PAYE tax: %.2f\n", PAYE_tax);
	printf("PRSI tax: %.2f\n", PRSI_tax);
	
	return PAYE_tax + PRSI_tax;
}