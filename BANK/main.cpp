#include <iostream>
#include <unordered_map>
#include <string>
#include <list>
#include <vector>
#include <unistd.h>
#include <cstdlib>


using namespace std;
namespace validation
{
bool agree()
{
    cout<<"Agree to Open Account?\n Type [Y/y] for Yes\n Type [N/n] for No"<<endl;
    char yn;
    cin>>yn;
    if(yn=='Y' || yn=='y')
    {
        return true;
    }
    return false;
}
string AccGen(const string& num)
{
    return "BSHDFC"+num;
}

string accountSelection()
{
    cout<<"Choose Account type:"<<endl;
    cout<<"1.SAVINGS"<<endl;
    cout<<"2.CURRENT"<<endl;
    int opt;
    cin>>opt;
    if(opt==2) return "CURRENT";
    return "SAVINGS";
}
string branchSelection()
{
    cout<<"Choose Branch Loaction:"<<endl;
    cout<<"1.BANGALORE"<<endl;
    cout<<"2.BOKARO"<<endl;
    int opt;
    cin>>opt;
    if(opt==1) return "BANGALORE";
    return "BOKARO";
}
bool genderSelection()
{
    cout<<"Choose Gender:"<<endl;
    cout<<"1.MALE"<<endl;
    cout<<"2.FEMALE"<<endl;
    int opt;
    cin>>opt;
    if(opt==1) return 1;
    return 0;
}

int initialDeposit(){
    int a;
    cout<<"Initial Deposit Amount:";
    cin>>a;
    return a;
}
}
using namespace validation;

class UserAccount
{
private:
    string accountNumber;
    string accountType;
    string accountHolderName;
    string branch;
    int totalFDs;
    int age;
    int balance;
    float interestRate;
    bool gender;
public:
    UserAccount(const string& mobileNumber,const string& name,int age)
    {
        this->accountNumber=AccGen(mobileNumber);
        this->accountHolderName=name;
        this->accountType=accountSelection();
        system("cls");
        this->branch=branchSelection();
        system("cls");
        this->totalFDs=0;
        this->balance=initialDeposit();
        this->age=age;
        this->gender=genderSelection();
        system("cls");
        this->interestRate=accountType=="SAVINGS" ? 4:0;
        cout<<"New Account Opened Congratulations "<<name<<endl;
        sleep(2);
        system("cls");
    }

    string getAccountNumber()
    {
        return this->accountNumber;
    }
    string getAccountName()
    {
        return this->accountHolderName;
    }
    friend class FixedDeposit;
    friend class BankSystem;
};

class FixedDeposit
{
private:
    string accountNumber;
    float fdInterestRate;
    int FDAmount;
    int duration;
    float interest;

public:
    FixedDeposit(UserAccount& obj,int amount,int duration)
    {
        this->accountNumber=obj.accountNumber;
        this->FDAmount=amount;
        this->duration=duration;

        if(duration<=3)
        {
            interest=7;
            if(agree())
            {
                openFD(obj,amount,duration);
            }
        }
        else if(duration<=5)
        {
            interest=7.2;
            if(agree())
            {
                openFD(obj,amount,duration);
            }
        }
        else if(duration<=10)
        {
            interest=7.5;
            if(agree())
            {
                openFD(obj,amount,duration);
            }
        }
        else
        {
            interest=7.9;
            if(agree())
            {
                openFD(obj,amount,duration);
            }
        }

    }


    void openFD(UserAccount& obj,int amount,int duration)
    {
        fdInterestRate=interest;
        if(obj.age>=60)
        {
            this->fdInterestRate+=0.25;
        }
        if(obj.gender==0)
        {
            this->fdInterestRate+=0.1;
        }
        cout<<"FD Opened for "<<obj.accountNumber<<endl;
        cout<<"Final Amount after "<<duration<<" Years: "<<amount+(amount*fdInterestRate*duration)/100<<endl;
        sleep(2);
        system("cls");
    }


    string getAccountNumber() const
    {
        return this->accountNumber;
    }

    int getFAmount() const
    {
        return this->FDAmount;
    }

    float getInterestRate() const
    {
        return this->fdInterestRate;
    }
    friend class BankSystem;
};

class BankSystem
{
private:
    unordered_map<string, UserAccount*> bankRegister;
    unordered_map<string,list<FixedDeposit*>> fixedRegister;
public:
    void addToBankRegister(UserAccount* user)
    {
        bankRegister[user->accountNumber] = user;
    }

    void addToFixedRegister(FixedDeposit* fd)
    {
        fixedRegister[fd->getAccountNumber()].push_back(fd);
    }

    void display()
    {
        for (const auto& entry : bankRegister)
        {
            cout << "Account Number: " << entry.first << ", Holder Name: " << entry.second->accountHolderName << endl;
        }
    }

    void displayFD()
    {
        for (const auto& entry : fixedRegister)
        {
            cout << "Account Number: " << entry.first << endl;
            for (const FixedDeposit* fd : entry.second)
            {
                cout << "FD Amount: " << fd->getFAmount() << endl;
                cout << "FD Interest Rate: " << fd->getInterestRate() << "%" << endl;
                cout << "FD Maturity Amount:" << fd->FDAmount+(fd->FDAmount*fd->fdInterestRate*fd->duration)/100<<endl;
                cout<<endl;
            }
            cout << "----------------------------------" << endl;
        }
    }

    UserAccount* searchUser(const string& accountNumber)
    {
        auto it = bankRegister.find(accountNumber);
        if (it != bankRegister.end())
        {
            return it->second;
        }
        return nullptr;
    }

    bool searchAccount(const string& accNum)
    {
        if(bankRegister.find(accNum)!=bankRegister.end())
        {
            return true;
        }
        return false;
    }


};


int main()
{
    BankSystem bankSystem;

    while (true)
    {
        cout << "Menu Options:" << endl;
        cout << "1. Add User Account" << endl;
        cout << "2. Open Fixed Deposit" << endl;
        cout << "3. Display User Accounts" << endl;
        cout << "4. Display Fixed Deposits" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string mobileNumber, name;
            int age;
            cout << "Enter Mobile Number: ";
            cin >> mobileNumber;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Age: ";
            cin >> age;
            UserAccount* user = new UserAccount(mobileNumber, name, age);
            bankSystem.addToBankRegister(user);
            break;
        }
        case 2:
        {
            string mobileNumber;
            int amount, duration;
            cout << "Enter Account Number: ";
            cin >> mobileNumber;
            cout << "Enter FD Amount: ";
            cin >> amount;
            cout << "Enter Duration (years): ";
            cin >> duration;

            string accNum=AccGen(mobileNumber);
            if (bankSystem.searchAccount(accNum))
            {
                UserAccount* user=bankSystem.searchUser(accNum);
                FixedDeposit* fd = new FixedDeposit(*user,amount, duration);
                bankSystem.addToFixedRegister(fd);
            }
            else
            {
                cout << "Account not found!" << endl;
            }
            break;
        }
        case 3:
            bankSystem.display();
            break;
        case 4:
            bankSystem.displayFD();
            break;
        case 5:
            cout << "Exiting..." << endl;
            exit(0);
        default:
            cout << "Invalid option, please try again." << endl;
        }

        cout << endl;
    }
    return 0;
}
