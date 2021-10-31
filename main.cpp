#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
using namespace std;


/*class Bank will store all the information about the acxcount and the respective functions to manipulate them.*/
 

class Bank
{
  protected:
  long account_no;
  int balance;
  char name[100];
  char acc_type[100];
  char address[100];
  static int account_holder;
 
  void generate_accountno()
  {
    account_no = 12320 + account_holder; 
    account_holder++;
  }
  public:
  void set_details();
  void updatebalance(int,int);
  void search(int);
  void displayallcustomer();
  void display_name(int);
  void display_address(int);
  void display_balance(int);
  void deleteCustomer(int);
  void deposit();
  void withdrawal();

};
/*set_details will ask the user and initialise all the data members.*/

void Bank :: set_details()
{ 
  fstream f;
  f.open("Accountno.txt",ios::ate);
  

  cout<<"Enter the name of customer"<<endl;
  cin.getline(name,100);
  cout<<"Enter the account type: (Savings/Current)\n";
  cin.getline(acc_type,100);
  cout<<"Please enter the address\n";
  cin.getline(address,100);
  generate_accountno();
  cout<<"Your account number is "<<account_no<<endl;
  cout<<"Please enter the initial balance\n";
  cin>>balance;
  ofstream fout;
  fout.open("customer.txt",ios :: app);
  fout.write((char *)this,sizeof(*this));
  
  cout<<"New customer added successfully\n"<<endl;
  fout.close();

}

/*display_name will check all the customer records and if the given account number matches the record in the file then it prints the name of the account holder.*/

void Bank :: display_name(int a)
{
  ifstream fin;
  fin.open("customer.txt",ios :: in);
  if(!fin)
  cout<<"File not found";
  else
  {
    int r=0;
    fin.read((char *)this,sizeof(*this));
    while(!fin.eof()){
      if(a == account_no){
      r++;
      cout<<"Account holder: "<<name<<endl;
      }
      fin.read((char *)this,sizeof(*this));
    
      
      }
      if (r==0)
      cout<<"Invalid account number"<<endl;

  }
fin.close();

  
  
}

/*display_balance will check all the customer records and if the given account number matches the record in the file then it prints the balance of the account holder.*/

void Bank :: display_balance(int a)
{
  ifstream fin;
  fin.open("customer.txt",ios :: in);
  if(!fin)
  cout<<"File not found";
  else
  {
    int r=0;
    fin.read((char *)this,sizeof(*this));
    while(!fin.eof()){
      if(a == account_no){
      r++;
      cout<<"Account Balance: Rs"<<balance<<endl;
      }
      fin.read((char *)this,sizeof(*this));
    
      
      }
      if (r==0)
      cout<<"Invalid account number"<<endl;

  }
fin.close();

}
/*display_address will check all the customer records and if the given account number matches the record in the file then it prints the address of the account holder.*/

void Bank :: display_address(int a)
{
  ifstream fin;
  fin.open("customer.txt",ios :: in);
  if(!fin)
  cout<<"File not found";
  else
  {
    int r=0;
    fin.read((char *)this,sizeof(*this));
    while(!fin.eof()){
      if(a == account_no){
      r++;
      cout<<"Account holder's address: "<<address<<endl;
      }
      fin.read((char *)this,sizeof(*this));
    
      
      }
      if (r==0)
      cout<<"Invalid account number"<<endl;

  }
fin.close();

}
/*displayallcustomers will read all the customer records from the file.*/
void Bank :: displayallcustomer()
{
  ifstream fin;
  fin.open("customer.txt",ios :: in);
  if(!fin)
  cout<<"File not found";
  else
  {
    fin.read((char *)this,sizeof(*this));
    while(!fin.eof()){
      cout<<"Account holder: "<<name<<endl;
      cout<<"Account type: "<<acc_type<<endl;
      cout<<"Account Balance: Rs"<<balance<<endl;
      cout<<"Account holder's address: "<<address<<endl<<endl;
      
      
       
      
      fin.read((char *)this,sizeof(*this));
      
      
      }

  }
fin.close();
}
/*search will check if the account exists in the file and print the details if the account exists.*/

void Bank :: search(int a)
{
  int r=0;
  fstream fin;
  fin.open("customer.txt",ios :: in);
  fin.read((char *)this,sizeof(*this));
  while(!fin.eof()){
      
      if(a == account_no){
        r++;
        cout<<"Account exists."<<endl;
        cout<<"Account holder: "<<name<<"  ";
        cout<<"Account type: "<<acc_type<<"  ";
        cout<<"Account Balance: Rs"<<balance<<"  ";
        cout<<"Account holder's address: "<<address<<"  "<<endl;
        }
      fin.read((char *)this,sizeof(*this));}
     if(r==0)
     cout<<"No user with this account.\n"<<endl;
      fin.close();
}

/*withdrawal function will ask the user for the account number amount for deposit and update the balance accordingly in the file.*/

void Bank :: withdrawal()
{
    int account;
    cout<<"Please enter the account for withdrawal"<<endl;
    cin>>account;
    int c,r=0;
    fstream file;
    file.open("customer.txt",ios::in | ios :: out | ios :: ate);
    file.seekg(0);
    file.read((char *)this,sizeof(*this));
    while(!file.eof())
    {
      if(account == account_no)
      {
        r++;
        cout<<"Enter the amount to be withdrawn"<<endl;
        cin>>c;
        if(balance>=c)
        {
          balance = balance -c;
          file.seekp((int)file.tellg()-sizeof(*this));
          file.write((char *)this,sizeof(*this));
          cout<<"Withdrawal successful. "<<endl;
          
          

        }
        else
        {
          cout<<"Insufficient Balance"<<endl;

        }

      }
      file.read((char *)this,sizeof(*this));

    }
    if(r==0)
    cout<<"Account does not exist."<<endl;
  file.close();

    
}

/*deposit function will ask the user for the amount and update the balance accordingly in the file.*/
void Bank :: deposit()
{
    int account,c,r=0;
    cout<<"Please enter the account for deposit"<<endl;
    cin>>account;
    fstream file;
    file.open("customer.txt",ios::in | ios :: out | ios :: app);
    file.seekg(0);
    file.read((char *)this,sizeof(*this));
    while(!file.eof())
    {
      if(account == account_no)
      {
        r++;
        cout<<"Enter the amount to be deposited"<<endl;
        cin>>c;
        balance = balance + c;
        file.seekp((int)file.tellg()-sizeof(*this));
        file.write((char *)this,sizeof(*this));
      }
    file.read((char *)this,sizeof(*this));
    }
    if(r==0)
    cout<<"Invalid account number."<<endl;
    file.close();
    
}
/*deleteCustomer function will delete the customer record from the file.*/
void Bank :: deleteCustomer(int a)
  {
 ifstream fin;
 ofstream fout;
 fin.open("customer.txt",ios :: in);
 fout.open("tempfile.txt",ios :: out);
 fin.read((char *)this,sizeof(*this));
 while(!fin.eof())
 {
   if(a != account_no)
   {
     fout.write((char *)this,sizeof(*this));

   }
    fin.read((char *)this,sizeof(*this));
 }
 fin.close();
 fout.close();
 remove("customer.txt");
 rename("tempfile.txt","customer.txt");
}
int Bank :: account_holder = 0;

/* select function will give all the different options user has.*/

int select()
{
   int ch;
   cout<<"Please select from the following oerations: "<<endl;
   cout<<"1.Add a new user"<<endl;
   cout<<"2.Delete the existing user. "<<endl;
   cout<<"3.Perform withdrawal operation. "<<endl;
   cout<<"4.Perform deposit operation. "<<endl;
   cout<<"5.Check if account exists."<<endl;
   cout<<"6.Print the address of customer with the given account number."<<endl;
   cout<<"7.Print the balance of customer with the given account number."<<endl;
   cout<<"8.Print the name of customer with the given account number."<<endl;
   cout<<"9.Print the record of customer with the given account number."<<endl;
   cout<<"10.Display all the customer. "<<endl;
   cout<<"11.Exit."<<endl;
   cin>>ch;
   return ch;
   
}



int main()
{
  Bank b;
  int a;
  int ch; 
  /*This loop will run until user wants to exit.*/
  while(1){
  ch = select();
  switch (ch)
  {
   
    case 1:
    cin.ignore();
    b.set_details();
    break;

    case 2:
    cout<<"Enter the user account number whose account you want to delete"<<endl;
    cin>>a;
    b.deleteCustomer(a);
    break;

    case 3:
    b.withdrawal();
    break;

    case 4:
    b.deposit();
    break;

    case 5:
    cout<<"Please enter the account number that you want to search "<<endl;
    cin>>a;
    b.search(a);
    break;

    case 6:
    cout<<"Please enter the account number "<<endl;
    cin>>a;
    b.display_address(a);
    break;

    case 7:
    cout<<"Please enter the account number "<<endl;
    cin>>a;
    b.display_balance(a);
    break;

    case 8:
    cout<<"Please enter the account number "<<endl;
    cin>>a;
    b.display_name(a);
    break;

    case 9:
    cout<<"Please enter the account number "<<endl;
    cin>>a;
    b.display_name(a);
    b.display_address(a);
    b.display_balance(a);
    break;

    case 10:
    b.displayallcustomer();
    break;
  
    case 11:
    cout<<"Thanks for using the application"<<endl;
    exit(0);

    default :
    cout<<"Invalid choice"<<endl;
   
  }
  sleep(50);
  }
  return 0;
}

  

