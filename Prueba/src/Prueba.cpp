#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ios;

#include <iomanip>
using std::setw;

#include <fstream>
using std::fstream;

#include <cstdlib>
using std::exit; // exit function prototype

#include <string>
using std::string;

#include <stdio.h>
#include <string.h>

class Account
{
public:
    Account( int accountNumberValue, string lastNameValue, string firstNameValue, double balanceValue )
    {
       setAccountNumber( accountNumberValue );
       setLastName( lastNameValue );
       setFirstName( firstNameValue );
       setBalance( balanceValue );
    }

    int getAccountNumber() const
    {
       return accountNumber;
    }
    void setAccountNumber( int accountNumberValue )
    {
       accountNumber = accountNumberValue; // should validate
    }
    string getLastName() const
    {
       return lastName;
    }
    void setLastName( string lastNameString )
    {
       const char *lastNameValue = lastNameString.data();
       strncpy( lastName, lastNameValue, 5 );
       lastName[ 5 ] = '\0';
    }

    string getFirstName() const
    {
       return firstName;
    }

    void setFirstName( string firstNameString )
    {
       const char *firstNameValue = firstNameString.data();
       strncpy( firstName, firstNameValue, 5 );
       firstName[ 5 ] = '\0';
    }
    double getBalance() const
    {
       return balance;
    }
    void setBalance( double balanceValue )
    {
       balance = balanceValue;
    }

private:
   int accountNumber;
   char lastName[ 15 ];
   char firstName[ 10 ];
   double balance;
};


int main()
{
   fstream outCredit( "credit.dat", ios::out | ios::binary );

   // exit program if fstream cannot open file
   if ( !outCredit )
   {
      cerr << "File could not be opened." << endl;
      exit( 1 );
   } // end if

   Account client(1,"AAAAA","BBBBB",1.2);

   // seek position in file of user-specified record
   outCredit.seekp( ( client.getAccountNumber() - 1 ) * sizeof( Account ) );

   // write user-specified information in file
   outCredit.write( reinterpret_cast< const char * >( &client ),sizeof( Account ) );

   return 0;
}
