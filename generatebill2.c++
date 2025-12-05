/*Generate Bill: Menu display + accepts number or name for category/items*/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_set>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;
#define PATH "C:\\Users\\vk026\\OneDrive\\Desktop\\C++ PRoject\\Bill\\Full_Food_Menu_100_Items.csv"

string toLowerStr(const string &s)
{
    string t = s;
    transform(t.begin(), t.end(), t.begin(), ::tolower);
    return t;
}

bool isNumber(const string &s)
{
    if (s.empty())
        return false;
    for (char c : s)
        if (!isdigit(c))
            return false;
    return true;
}

class GenerateBill
{
    vector<string> Category;
    vector<string> Item;
    vector<string> Price;

public:
    GenerateBill()
    {
        ifstream file(PATH);
        if (!file.is_open())
        {
            cout << "ERROR: Could not open file: " << PATH << endl;
            return;
        }
        string category, item, price, dummy;
        getline(file, dummy);
        while (getline(file, category, ',') &&
               getline(file, item, ',') &&
               getline(file, price))
        {
            Category.push_back(category);
            Item.push_back(item);
            Price.push_back(price);
        }
    }

    void ShowMenu()
    {
        struct ItemInfo
        {
            int quantity = 0;
            double price = 0.0; 
            double unitprice = 0.0;
        };

        map<string, ItemInfo> finalValue;
        bool Continue = true;

        while (Continue)
        {
            vector<string> List;
            unordered_set<string> seen;
            for (const string &cat : Category)
            {
                if (seen.find(cat) == seen.end())
                {
                    List.push_back(cat);
                    seen.insert(cat);
                }
            }

            cout << "\nAvailable Categories:\n";
            for (size_t i = 0; i < List.size(); ++i)
                cout << i + 1 << " -> " << List[i] << '\n';

            string Option1;
            cout << endl
                 << "Select a Category to Proceed with Order (number or name):->  ";
            getline(cin >> ws, Option1);

            int selectedCatIndex = -1;
            if (isNumber(Option1))
            {
                int opt = stoi(Option1);
                if (opt >= 1 && opt <= (int)List.size())
                    selectedCatIndex = opt - 1;
                else
                {
                    cout << "Invalid category number. Returning to main menu.\n";
                    continue;
                }
            }
            else
            {
                string optLower = toLowerStr(Option1);
                for (size_t i = 0; i < List.size(); ++i)
                    if (toLowerStr(List[i]) == optLower)
                    {
                        selectedCatIndex = (int)i;
                        break;
                    }
                if (selectedCatIndex == -1)
                {
                    cout << "Category name not found. Returning to main menu.\n";
                    continue;
                }
            }

            string selectedCategory = List[selectedCatIndex];

            vector<string> selectedItem;
            vector<int> selectedIndices;
            cout << "\nItems in category '" << selectedCategory << "':\n";
            int y = 1;
            for (size_t x = 0; x < Category.size(); x++)
            {
                if (Category[x] == selectedCategory)
                {
                    double p = 0.0;
                    try
                    {
                        p = stod(Price[x]);
                    }
                    catch (...)
                    {
                        p = 0.0;
                    }
                    cout << left << setw(5) << y
                         << setw(30) << Item[x]
                         << right << setw(10) << fixed << setprecision(2) << p
                         << endl;

                    selectedItem.push_back(Item[x]);
                    selectedIndices.push_back((int)x);
                    y++;
                }
            }

            if (selectedItem.empty())
            {
                cout << "No items available in this category. Returning to main menu.\n";
                continue;
            }

            string Option2;
            cout << endl
                 << "Select an Item to proceed with Order (number or name):->  ";
            getline(cin >> ws, Option2);

            string qtyStr;
            cout << "Enter Quantity:->  ";
            getline(cin >> ws, qtyStr);
            if (!isNumber(qtyStr))
            {
                cout << "Invalid quantity. Returning to main menu.\n";
                continue;
            }
            int Quantity = stoi(qtyStr);
            if (Quantity <= 0)
            {
                cout << "Quantity must be greater than 0. Returning to main menu.\n";
                continue;
            }

            int selIndex = -1;
            if (isNumber(Option2))
            {
                int opt2 = stoi(Option2);
                if (opt2 >= 1 && opt2 <= (int)selectedItem.size())
                    selIndex = opt2 - 1;
                else
                {
                    cout << "Invalid item number. Returning to main menu.\n";
                    continue;
                }
            }
            else
            {
                // match by item name (case-insensitive)
                string optLower = toLowerStr(Option2);
                for (size_t i = 0; i < selectedItem.size(); ++i)
                    if (toLowerStr(selectedItem[i]) == optLower)
                    {
                        selIndex = (int)i;
                        break;
                    }
                if (selIndex == -1)
                {
                    cout << "Item name not found in selected category. Returning to main menu.\n";
                    continue;
                }
            }

            int originalIndex = selectedIndices[selIndex];
            double unitPrice = 0.0;
            try
            {
                unitPrice = stod(Price[originalIndex]);
            }
            catch (...)
            {
                unitPrice = 0.0;
            }
            double totalPrice = unitPrice * Quantity;
            string itemName = selectedItem[selIndex];
            if (finalValue.count(itemName))
            {
                finalValue[itemName].quantity += Quantity;
                finalValue[itemName].price += totalPrice;
            }
            else
            {
                finalValue[itemName] = {Quantity, totalPrice, unitPrice};
            }

            string Next;
            while (true)
            {
                cout << "\nType 'more' to choose more items or 'next' to generate the bill:-> ";
                getline(cin >> ws, Next);
                transform(Next.begin(), Next.end(), Next.begin(), ::tolower);
                if (Next == "next" || Next == "n" || Next == "more" || Next == "m")
                    break;
                cout << "Invalid choice. Please type 'more' or 'next'.\n";
            }

            if (Next == "more" || Next == "m")
            {
                continue;
            }
            else
            {
                cout << endl;
                cout << "\n==============================================\n";
                cout << "                VICKY RESTAURANT                \n";
                cout << "==============================================\n\n";

                cout << left << setw(20) << "Item"
                     << setw(12) << "Unit Price"
                     << setw(10) << "Qty"
                     << setw(12) << "Total"
                     << endl;

                cout << "----------------------------------------------\n";

                double grandTotal = 0.0;
                int totalQuantity = 0;
                int totalItems = 0;

                for (const auto &x : finalValue)
                {
                    double lineTotal = x.second.price;

                    cout << left << setw(20) << x.first
                         << setw(12) << fixed << setprecision(2) << x.second.unitprice
                         << setw(10) << x.second.quantity
                         << setw(12) << fixed << setprecision(2) << lineTotal
                         << endl;

                    grandTotal += lineTotal;
                    totalQuantity += x.second.quantity;
                    totalItems++;
                }

                cout << "----------------------------------------------\n";

                cout << left << setw(20) << "TOTAL"
                     << setw(12) << totalItems
                     << setw(10) << totalQuantity
                     << setw(12) << fixed << setprecision(2) << grandTotal
                     << endl;

                cout << "==============================================\n";
                cout << "       THANK YOU! VISIT AGAIN                 \n";
                cout << "==============================================\n";

                Continue = false;
            }
        } 
    } 
}; 

int main()
{
    GenerateBill Bill;
    Bill.ShowMenu();
    return 0;
}
