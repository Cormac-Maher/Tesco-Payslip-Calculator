const TAX_CREDIT = 76.93;
const PAYRATE = 14.44;
const STANDARD_BAND = 846.16;


function printPayslip() {
    const hours = [
        +document.getElementById("sun").value,
        +document.getElementById("mon").value,
        +document.getElementById("tue").value,
        +document.getElementById("wed").value,
        +document.getElementById("thu").value,
        +document.getElementById("fri").value,
        +document.getElementById("sat").value
    ];

    const pSlip = calculatePayslip(hours);
    displayPayslip(pSlip);
}

function displayPayslip(pSlip) {
    const output = `
========== PAYSLIP ==========
\nTotal Hours Worked: ${pSlip.totalHours.toFixed(2)}
\nWeekly Hours: ${pSlip.weeklyHrs.toFixed(2)}
\nPremium (Sunday) Hours: ${pSlip.premiumHrs.toFixed(2)}
\n
\nTotal Pay Before Tax: €${pSlip.totalPay.toFixed(2)}
\nTax Paid (PAYE + PRSI): €${pSlip.tax.toFixed(2)}

\nNet Pay: €${pSlip.netPay.toFixed(2)}
\nAnnual Net Pay: €${pSlip.annualNet.toFixed(2)}
=============================`;

    document.getElementById("paySlip").textContent = output;
}




function calculatePayslip(hoursArray) {
    let weeklyHrs = 0;
    let premiumHrs = 0;

    const payRate = [PAYRATE, PAYRATE * 1.5,PAYRATE * 2];

    for (let i = 0; i < 7; i++) {
        let hrsWorked = hoursArray[i];

        if (hrsWorked >= 7) {
            hrsWorked -= 1;
        } else if (hrsWorked === 6) {
            hrsWorked -= 0.5;
        }  
        if (i === 0) {
            premiumHrs += hrsWorked;
        } else {
            weeklyHrs += hrsWorked;
        }
    }

    const totalPay = (weeklyHrs * payRate[0]) + (premiumHrs * payRate[1]);
    const tax = calculateTax(totalPay);
    const netPay = totalPay - tax;

    return {
        weeklyHrs,
        premiumHrs,
        totalHours: weeklyHrs + premiumHrs,
        totalPay,
        tax,
        netPay,
        annualNet: netPay * 52
    };
}


function calculateTax(grossPay) {
    let PAYE_tax = 0;
    let PRSI_tax = 0;
    let upperBand;

    const PRSI_credit = 12 * (1 - ((grossPay - 352) / 72));

    if (grossPay > STANDARD_BAND) {
        upperBand = (grossPay - STANDARD_BAND) * 0.4;           // Calculating PAYE
        PAYE_tax = (STANDARD_BAND * 0.2) + upperBand;
    } else {
        PAYE_tax = grossPay * 0.2;
    }

    PAYE_tax -= TAX_CREDIT;
    if (PAYE_tax < 0) PAYE_tax = 0;

    
    if (grossPay <= 352) {                      // Calculating PRSI
        PRSI_tax = 0;
    } else if (grossPay >= 352.01 && grossPay <= 424) {
        PRSI_tax = (grossPay * 0.042) - PRSI_credit;
        if (PRSI_tax < 0) PRSI_tax = 0;
    } else if (grossPay >= 424.01) {
        PRSI_tax = grossPay * 0.042;
    }

    return PAYE_tax + PRSI_tax;
}
