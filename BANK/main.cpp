#include <iostream>
using namespace std;
namespace validation{
    bool agree(){
        cout<<"Agree to Open Account?\n Type [Y/y] for Yes\n Type [N/n] for No"<<endl;
        char yn;
        cin>>yn;
        if(yn=='Y' || yn=='y'){
            return true;
        }
        return false;
    }
    string AccGen(const string& num){
        return "BSHDFC"+num;
    }

    string accountSelection(){
        cout<<"Choose Account type:"<<endl;
        cout<<"1.SAVINGS"<<endl;
        cout<<"2.CURRENT"<<endl;
        int opt;
        cin>>opt;
        if(opt==2) return "CURRENT";
        return "SAVINGS";
    }
    string branchSelection(){
        cout<<"Choose Branch Loaction:"<<endl;
        cout<<"1.BANGALORE"<<endl;
        cout<<"2.BOKARO"<<endl;
        int opt;
        cin>>opt;
        if(opt==1) return "BANGALORE";
        return "BOKARO";
    }
}
using namespace validation;

class UserAccount{
private:
    string accountNumber;
    string accountType;
    string accountHolderName;
    string branch;
    int age;
    int balance;
    float interestRate;
public:
    UserAccount(const string& mobileNumber,const string& name,int age){
        this->accountNumber=AccGen(mobileNumber);
        this->accountHolderName=name;
        this->accountType=accountSelection();
        this->branch=branchSelection();
        this->balance=0;
        this->age=age;
        this->interestRate=accountType=="SAVINGS" ? 3:0;
    }
    friend class FixedDeposit;

};

class FixedDeposit{
private:
    string accountNumber;
    int fdInterestRate;
    int FDAmount;
    int duration;
    float interest;

public:
    void openFD(UserAccount& obj,int amount,int duration){
        cout<<"FD Opened"<<endl;
    }
    FixedDeposit(UserAccount& obj,int amount,int duration){
        if(duration<=3){
            interest=7;
            cout<<"Final Amount after Duration Years: "<<amount+(amount*interest*duration)/100;
            if(agree()){
                openFD(obj,amount,duration);
            }
        }
        else if(duration<=5){
            interest=7.2;
            cout<<"Final Amount after Duration Years: "<<amount+(amount*interest*duration)/100;
            if(agree()){
                openFD(obj,amount,duration);
            }
        }
        else if(duration<=10){
            interest=7.5;
            cout<<"Final Amount after Duration Years: "<<amount+(amount*interest*duration)/100;
            if(agree()){
                openFD(obj,amount,duration);
            }
        }
        else{
            interest=7.9;
            cout<<"Final Amount after Duration Years: "<<amount+(amount*interest*duration)/100;
            if(agree()){
                openFD(obj,amount,duration);
            }
        }
    }
};


int main()
{

    return 0;
}
