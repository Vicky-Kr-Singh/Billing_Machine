# 🍽️ Console-Based Restaurant Billing System (C++)

A C++ console application that loads menu data from a CSV file, displays food categories and items, accepts user orders (by number or name), calculates totals, and generates a formatted customer bill.  
This project demonstrates **file handling, vectors, maps, OOP, and console UI logic** in C++.

---

## 🚀 Features

- Reads `Category, Item, Price` from a CSV file.
- Displays unique categories dynamically.
- User can choose a **category** by:
  - Number (e.g., `2`)
  - Name (e.g., `Chinese`)
- User can choose an **item** by:
  - Number (e.g., `1`)
  - Name (e.g., `Fried Rice`)
- Supports multi-word names using `getline(cin >> ws, ...)`.
- Accumulates repeated items and updates totals.
- Clean formatted bill output with quantities and line totals.
- Case-insensitive matching for category & item names.

---

## 🧠 Program Flow
                START PROGRAM
                       │
                       ▼
        Instantiate GenerateBill (constructor)
                - Open CSV file
                - Skip header
                - Load Category, Item, Price
                       │
                       ▼
                  Call ShowMenu()
                       │
                       ▼
                while (Continue)
                       │
                       ▼
      Print Unique Categories (1 -> Indian, 2 -> Chinese...)
                       │
                       ▼
     Prompt: "Select Category" (number or name)
                       │
                       ▼
     Match category → List all items in that category
                       │
                       ▼
     Prompt: "Select Item" (number or name)
     Prompt: "Enter Quantity"
                       │
                       ▼
     Add item to finalValue map (accumulate totals)
                       │
                       ▼
     Prompt: "more" (add more items)
               or
            "next" (generate bill)
                       │
           ┌──────────┴──────────┐
           │                     │
        more                  next
           │                     ▼
           │            Print formatted bill
           │            Display totals
           │            Set Continue = false
           └───────────────────────┐
                                   ▼
                          Program Ends


📘 Example Output
Available Categories:
1 -> Indian
2 -> Chinese
3 -> Beverages

Select a Category: Chinese

Items in Chinese:
1    Fried Rice                 120.00
2    Hakka Noodles              140.00

Select an Item: Fried Rice
Enter Quantity: 2

Type 'more' or 'next': next

==============================================
                VICKY RESTAURANT                
==============================================

Item                Unit Price   Qty   Total
----------------------------------------------
Fried Rice          120.00       2     240.00
----------------------------------------------
TOTAL               1            2     240.00
==============================================
        THANK YOU! VISIT AGAIN
==============================================


