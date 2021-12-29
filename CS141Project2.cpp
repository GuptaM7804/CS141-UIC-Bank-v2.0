//
//Author: Manav Gupta, UIC, Spring 2021
//Assignment: Project 2 Part 1
//

// include all nescessary headers
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std; //don't have to type 'std::' over and over

// create multiple functions for easier and cleaner looking code
// prints accounts and balances with parameters for numbers that correspond with the accounts and balances
void printAccBal(int acc, double bal)
{
    cout << std::fixed;
    cout << std::setprecision(2);
    cout << "Account " << acc << ": balance $" << bal << endl;
}

// takes numbers from the code (could be variables, inputs, etc.) and adds them to a file
void outputAccBal(ofstream& outfile, int acc, double bal)
{
    outfile << std::fixed;
    outfile << std::setprecision(2);
    outfile << acc << " " << bal << endl;
}

//
// checkArrays
//
// Required function that currently outputs to console, but when submitted
// to gradescope this function will be replaced by one that performs more
// extensive checks to make sure the data was input correctly.
//
// NOTE: this function is required as part of assignment.
//
void checkArrays(int accounts[], double balances[], int N)
{
   cout << std::fixed;
   cout << std::setprecision(2);

   cout << "** Checking arrays..." << endl;
   cout << "1. " << accounts[0] << ", $" << balances[0] << endl;
   cout << N << ". " << accounts[N-1] << ", $" << balances[N-1] << endl;
}

//
//search
//
//Given an array of N accounts in ascending order, searches for
//the account that matches "acct". If found, the index of that
//account is returned; if not found -1 is returned.
//
int search(int accounts[], int N, int acct)
{
    for (int i = 0; i < N; i++)
    {
        if (accounts[i] == acct)
        {
            return i;
        }
    }
    return -1;
}

//
//maxBalance
//
//Given an array of N balances, searches for the highest balances
//and returns the index of this balance. If there's a tie, the
//first(smaller) index is returned. Assumes N > 0.
int maxBalance(double balances[], int N)
{
    double max;
    max = balances[0];
    int index = 0;
    for (int i = 1; i < N; i++)
    {
        if (balances[i] > max)
        {
            max = balances[i];
            index = i;
        }
    }
    return index;
}

// prints accounts and balances that occur between a given range of 2 numbers (of accounts)(inclusive)
void lowHighRange(int accounts[], double balances[], int N, int low, int high)
{
    for (int i = 0; i < N; i++)
    {
       if (accounts[i] >= low && accounts[i] <= high)// if the number 'low' is less than or equal to an account number
           // and the number 'high' is greater than or equal to an account number, then the first account until 
           // the last account between these two numbers are printed.
       {
           printAccBal(accounts[i], balances[i]);
       }
    }
}

void listNegBalAcc(int accounts[], double balances[], int N)
{
    for (int i=0; i < N; i++)
    {
        if (balances[i] < 0)
        {
            printAccBal(accounts[i], balances[i]);
        }
    }
}

double totalBal(double balances[], int N)
{
    double total = 0.00;
    
    for (int i = 0; i < N; i++)
    {
        if (balances[i] > 0)
        {
            total += balances[i];
        }
    }
    return total;
}

int maxAccNo(int accounts[], int N)
{
    int max;
    max = accounts[0];
    for (int i = 1; i < N; i++)
    {
        if (accounts[i] > max)
        {
            max = accounts[i];
        }
    }
    return max;
}


int main()
{
    cout << "** Welcome to UIC Bank v2.0 **" << endl;
    string filename; //string variable for filename entered by user
    cout << "Enter bank filename> " << endl;
    cin >> filename; //keyboard input
    ifstream infile; //assign variable to file, ifstream is for reading from the file

    infile.open(filename); //open file
    
    if (!infile.good()) //if file does not exist then an error message will be given and the code will stop running
    {
        cout << "** Inputting account data..." << endl;
        cout << "**Error: unable to open input file '" << filename << "'" << endl;
        return 0; // stop further reading of the code and end running
    }
    
    cout << "** Inputting account data..." << endl; 

    int size, accountNum; // declare variables for size of dynamic arrays and accoutnNum, a variable to get input out from a file
    //for accounts array
    double balance; //variable to get input out from a file for the array of balances
 
    infile >> size; //get size, first number in the file is the size/N
    int *accounts = new int[size]; //create dynamic array of size[size]
    double *balances = new double[size]; //same as above
    for (int i = 0; i < size; i++){
        infile >> accountNum; //input from file into variable accountNum
        accounts[i] = accountNum; //the dynamic array = the variable which stores the information of the file
        infile >> balance; //same as above
        balances[i] = balance;// same as above
    }
    //call function checkArrays
    checkArrays(accounts, balances, size);
       
    infile.close(); //close the file
   
    
    cout << "** Processing user commands..." << endl;
    cout << "Enter command (+, -, ?, ^, *, <, $, add, del, x): " << endl;    
    
    string sig; // declare sign/command as a character variable sig
    ofstream outfile; // ofstream to write into the file and declare variable outfile to open and close file
    
    cin >> sig; // user input for the command
    while (sig != "x") { // while loop makes sure that while the exit command isn't entered, 
        // code will keep running and asking for further commands
        
        if (sig == "+") { // if the user input is '+' ... (to deposit to the bank)
            int accNo; // declare accNo as an integer variable
            double amount; // declare amount as a double variable as it has decimals

            cin >> accNo; // read for accNo from user
            cin >> amount; // read for amount from user

            int index = 0;//declare variable index
            index = search(accounts, size, accNo); //call search function and make 'index' = to the index/i we get from the function
            // searching in accoutns[], size is acquired from the file, accNo is user inputted integer

            if (index == -1) // if index is -1, ie: no account number matches the inputted account number
            {
                cout << "** Invalid account, transaction ignored" << endl; //then the transaction will be ignored and the
                // for loop will loop around back to the start.
            }
            else { //else...
                balances[index] += amount; //the balance with that index will be added by the amount given by the user
                printAccBal(accounts[index], balances[index]); //print function is called, prints the user inputted accounts
                //and the updated balance for that account
            }
        }
        else if (sig == "-") { //same as above but for "-"
            int accNo; 
            double amount; 

            cin >> accNo;
            cin >> amount; 

            int index = 0;
            index = search(accounts, size, accNo);

            if (index == -1)
            {
                cout << "** Invalid account, transaction ignored" << endl;
            }
            else {
                balances[index] -= amount;
                printAccBal(accounts[index], balances[index]);
            }
        }

        else if (sig == "?") { // the '?' character entered by the user outputs the bank details for that account
            int accNo;

            cin >> accNo; // user enters account number for the account whose balance/details they want

            int index = 0;//same as above
            index = search(accounts, size, accNo);
            if (index == -1)
            {
                cout << "** Invalid account, transaction ignored" << endl;
            }
            else
            {
                printAccBal(accounts[index], balances[index]); //instead of changing the balance like above, just prints it normally
            }
        }

        else if (sig == "^") // if entered character by user is '^', then the account with the most amount of money is outputted
        { 
            int index = maxBalance(balances, size); //variable index is created and = the maxBalanxe function's index
            printAccBal(accounts[index], balances[index]); // prints the account and balance corresponding with that index
        }

        else if (sig == "*") // if entered character by the user is '*', then the details of all bank accounts are outputted
        { 
           int low; //low variable created for the floor of the range
           int high; //high variable created for the ceiling of the range

           cin >> low; //get input from the user
           cin >> high; // get input from the user

           lowHighRange(accounts, balances, size, low, high); //function is called
        }
        
        else if (sig == "<")
        {
            listNegBalAcc(accounts, balances, size);
        }
        
        else if (sig == "$")
        {
            double totalSum = 0.0;
            totalSum = totalBal(balances, size);
            cout << "Total deposits: $" << totalSum << endl;
        }
        
        else if (sig == "add")
        {
            int* newAccounts = new int[size+1];
            double* newBalances = new double[size+1];

            for (int i = 0; i < size; i++)
            {
                newAccounts[i] = accounts[i];
                newBalances[i] = balances[i];
            }

            int accNum = 0;
            accNum = maxAccNo(accounts, size);

            newAccounts[size] = accNum + 1;
            newBalances[size] = 0.00;
            
            size += 1;
            
            delete []accounts;
            delete []balances;

            balances = newBalances;
            accounts = newAccounts;

            cout << "Added account " << accounts[size-1] << ": balance $" << balances[size-1] << endl;
        }
        
        else if (sig == "del")
        {
            int acct = 0;
            
            cin >> acct;
            
            int index = 0; //same as above
            index = search(accounts, size, acct);
            if (index == -1)
            {
                cout << "** Invalid account, transaction ignored" << endl;
            }
            else
            {
                int* newAccounts = new int[size-1];
                double* newBalances = new double[size-1];
                
                int pos = 0;
                pos = search(accounts, size, acct);
                
                for (int i = 0; i < pos; i++)
                {
                    newAccounts[i] = accounts[i];
                    newBalances[i] = balances[i];     
                }
                
                size -= 1;
                
                for (int i = pos; i < size; i++)
                {
                    newAccounts[i] = accounts[i+1];
                    newBalances[i] = balances[i+1];
                }
                
                delete []accounts;
                delete []balances;
                
                balances = newBalances;
                accounts = newAccounts;
                
                cout << "Deleted account " << acct << endl;
            }
        }

        else { // if none of the above commands are given
            cout << "** Invalid command, try again..." << endl; // invalid command is outputted and...
        }
        
        cout << "Enter command (+, -, ?, ^, *, <, $, add, del, x): " << endl; // user is prompted for further instructions
        cin >> sig;
    }
    outfile.open(filename); // outfile opens the file entered by user
    
//     for (int i = 0; i < size; i++)
//     {
//         cout << accounts[i] << " " << balances[i] << endl;
//     }
  
    if (!outfile.good()) //if outfile is not good/ the inputted file doesn't exist or there is an error opening...
    {
        cout << "** Error, unable to open output file '" << filename << "'" << endl; //the code is unable to operate further
        delete []accounts; // delete the two arrays so no memory leaks are detected/occur
        delete []balances;
        return 0; // and then it stops running
    }
    
    outfile << size << endl;// inupt the size of the arrays/first number from the file back into the outfile.
    
    for (int i = 0; i < size; i++)
    {
        outputAccBal(outfile, accounts[i], balances[i]); //input all the accounts and balances back into the file through the
        //outputAccBal function
    }
    
    outfile.close(); // outfile is closed
    
    delete []accounts; //delete the two arrays so that no memory leak is detected/occurs 
    delete []balances;
    
    cout << "** Saving account data..." << endl;
    cout << "** Done **" << endl;
    
    return 0; //stop the code
}