# 🧾 Tesco Payslip Calculator (C)

A console-based payslip calculator written in C. Enter daily hours worked across a 7-day week and the program calculates gross pay, PAYE tax, PRSI tax, and net pay — then lets you save and retrieve payslips as `.txt` files.

---

## ✨ Features

- Calculates **gross pay** from standard and Sunday premium hours
- Automatically deducts **unpaid breaks** based on hours worked per day
- Calculates **PAYE tax** with standard rate band and tax credits
- Calculates **PRSI tax** with tapered credit for lower earners
- **Saves payslips** to a date-stamped `.txt` file
- **Retrieves and displays** previously saved payslips by date

---

## 💰 Pay & Tax Rules

| Rule | Detail |
|---|---|
| Standard pay rate | €14.44 / hr |
| Sunday premium rate | €21.66 / hr (1.5×) |
| Break deduction | 1 hr if ≥ 7 hrs worked; 0.5 hr if 6–7 hrs worked |
| PAYE standard band | €846.16/week at 20%; above that at 40% |
| PAYE tax credit | €76.93 (deducted after PAYE is calculated) |
| PRSI rate | 4.2% of gross pay |
| PRSI credit | Tapered €12 credit for earnings between €352–€424 |
| PRSI threshold | No PRSI on earnings ≤ €352 |

---

## 🚀 Getting Started

### Compile

```bash
gcc payslip.c -o payslip
```

Or with MSVC on Windows:
```bash
cl payslip.c
```

### Run

```bash
./payslip
```

---

## 🖥️ Menu

```
----------------MENU-----------------
Enter 1 to create a new payslip
Enter 2 to save a payslip to file
Enter 3 to display a previous payslip
Enter -1 to exit
```

**Option 1 — Create Payslip**
Enter the payslip date, then hours worked for each day of the week (Sunday through Saturday). Hours must be between 0 and 20. The payslip is displayed in the console.

**Option 2 — Save to File**
Saves the most recently created payslip to a `.txt` file named `Payslip_DD-MM-YYYY.txt`.

**Option 3 — Display Previous Payslip**
Enter a date to load and print a previously saved payslip file.

---

## 📄 Sample Output

```
======================================
            TESCO PAYSLIP
             5/4/2025
======================================
Hours worked: 37.50
Standard Pay: 487.35
Premium Pay: 86.64
--------------------------------------
Gross Pay: 573.99
PAYE tax: 38.07
PRSI tax: 9.13
--------------------------------------
Total pay: 526.79
======================================
```

---

## 📁 Project Structure

```
payslip.c                   # Main source file
Payslip_DD-MM-YYYY.txt      # Generated payslip files (created at runtime)
```

---

## 🛠️ Built With

- **C** (C99 standard)
- Standard libraries: `stdio.h`
