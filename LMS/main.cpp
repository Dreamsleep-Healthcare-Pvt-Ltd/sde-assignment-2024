#include <iostream>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <list>

using namespace std;

class User{
private:
    string number;
    string name;
public:
    User(const string& name,const string& number){
        this->name=name;
        this->number=number;
    }
    friend class LibrarySystem;
};

class Book{
private:
    string name;
    int quantity;
public:
    Book(string const& name,const int& quantity){
        this->name=name;
        this->quantity=quantity;
    }
    friend class LibrarySystem;
};

class LibrarySystem{
private:
    unordered_map<string,string> users;
    unordered_map<string,int> books;
    unordered_map<string,list<string>> borrowRegister;
    int password=1234567;
public:
    void addUser(User& obj){
        if(users.find(obj.number)!=users.end()){
            cout<<"Already Registered with Library!!"<<endl;
        }
        else{
            users[obj.number]=obj.name;
            cout<<"User "<<obj.name<< " Registered Successfully"<<endl;
        }
    }
    void addBook(Book& obj){
        if(books.find(obj.name)!=books.end()){
            //Already Registered
            cout<<"Already have the current Book"<<endl;
        }
        else{
            books[obj.name]=obj.quantity;
            cout<<"Book"<<obj.name<< "added Successfully to Inventory"<<endl;
        }
    }
    void viewUsers(){
        for(auto it:users){
            cout<<it.first<<" "<<it.second<<endl;
        }
    }
    void viewBooks(){
        for(auto it:books){
            cout<<it.first<<" "<<it.second<<endl;
        }
    }

    pair<bool,int> searchBook(string name){
        auto it=books.find(name);
        if(it!=books.end()){
            return make_pair(true,it->second);
        }
        return make_pair(false,0);
    }

    bool isValidUser(const string& number){
        if(users.find(number)!=users.end()) return true;
        return false;
    }

    void borrowBook(const string &number,const string& bookTitle){
        if(isValidUser(number)){
                pair<bool,int> res=searchBook(bookTitle);
            if(res.first && res.second>0){
                borrowRegister[number].push_back(bookTitle);
                books[bookTitle]--;
                cout<<"Book "<<bookTitle<<" borrowed successfully"<<endl;
            }
            else if(res.second==0){
                cout<<"Stock finished"<<endl;
            }
            else{
                cout<<"Invalid Book Title"<<endl;
            }
        }
        else{
            cout<<"Invalid User"<<endl;
        }
    }

    void returnBook(const string& userNumber, const string& bookTitle) {
        auto it = borrowRegister.find(userNumber);
        if (it != borrowRegister.end()) {
            auto& bks = it->second;
            bks.remove(bookTitle);
            books[bookTitle]++;
            cout << "Book" <<bookTitle<<" returned by user " << userNumber << endl;

        } else {
            cout << "User " <<userNumber<<" not found." << endl;
        }
    }

    void displayBorrowedBooks(const string& userNumber) {
        auto it = borrowRegister.find(userNumber);
        if (it != borrowRegister.end()) {
            cout << "Books borrowed by user " << userNumber << ":" << endl;
            for (auto& book : it->second) {
                cout << " - " << book << endl;
            }
        } else {
            cout << "User " << userNumber << " has not borrowed any books." << endl;
        }
    }


    bool passwordVerify(int pwd){
        return pwd==password? true:false;
    }
};

int main(){
    LibrarySystem lms;

    while(1){
        int options;
        cout<<"1.Add Users"<<endl;
        cout<<"2.Add Books"<<endl;
        cout<<"3.View Books"<<endl;
        cout<<"4.View Users"<<endl;
        cout<<"5.Borrow Book"<<endl;
        cout<<"6.Return Book"<<endl;
        cout<<"7.View User Bucket"<<endl;
        cout<<"8.Exit Application"<<endl;
        cin>>options;
        switch(options){
            case 1:{
                    string name,number;
                    cout<<"Enter Name of new User: "; cin>>name;
                    cout<<"Enter Number of new User: "; cin>>number;
                    User newUser(name,number);
                    lms.addUser(newUser);
                    sleep(1);
                    system("cls");
            }break;
            case 2:{
                    string name;
                    int quantity;
                    cout<<"Enter Name of new Book: "; cin>>name;
                    cout<<"Enter quantity: "; cin>>quantity;
                    Book newBook(name,quantity);
                    lms.addBook(newBook);
                    sleep(1);
                    system("cls");
            }break;
            case 3:{
                lms.viewBooks();
            }break;
            case 4:{
                lms.viewUsers();
            }break;
            case 5:{
                string name,number;
                cout<<"Enter Name of Book: "; cin>>name;
                cout<<"Enter Number User: "; cin>>number;
                lms.borrowBook(number,name);
                sleep(1);
                system("cls");
            }break;
            case 6:{
                cout<<"For Returning a Book please provide:"<<endl;
                string name,number;
                cout<<"Enter Name of Book: "; cin>>name;
                cout<<"Enter Number User: "; cin>>number;
                lms.returnBook(number,name);
                sleep(1);
                system("cls");
            }break;
            case 7:{
                cout<<"See your Borrowed Books:"<<endl;
                string number;
                cout<<"Enter Number of User: "; cin>>number;
                lms.displayBorrowedBooks(number);
            }break;
            case 8:{
                exit(0);
            }break;
            default:{
                cout<<"Wrong Input"<<endl;
            }break;
        }
    }

    return 0;
}
