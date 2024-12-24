// A commercial flight has N rows with M seats in each row. The seats are available in three different categories
// namely first-class, business class, and economy class. The rows from 1 to K are of first-class category, rows from
// k+1 to P, are of business-class, and the rows from P+1 to N are economy-class. The information about the
// availability of seats is stored in a 2D matrix of int data type where 0 indicates the seat is available and 1 indicates
// the seat is occupied. Write a program that can be used to perform the following tasks:
// ● Determine overall available seats.
// ● Determine Category wise available seats.
// ● If the seats are available, then perform the following tasks:
// o Prompt the user to enter category (a numeric value). Category should be treated as a row
// number.
// o Prompt the user to enter the seat number (a numeric value). Seat number should be treated
// as column number.
// o Determine whether the seat is available or not. If it is available, then reserve it by storing
// 1 on that index location, otherwise display a message about unavailability of the seat.
#include<iostream>
using namespace std;


int main()
{
    const int N=3,M=6;
int arr[N][M]={
    {0, 1, 0, 0, 1, 0},
	{0, 0, 1, 0, 1, 0},
	{1, 0, 0, 1, 0, 0},
};
int seats[3]={0,0,0};
int k=1,p=2;
for(int i=0;i<N;i++)
{
    for(int j=0;j<M;j++)
    {
        if(arr[i][j]==0)
        {
         if(i<k)seats[0]++;
         else if(i>=k && i<p)seats[1]++;
         else seats[2]++;   
        }
    }
}
	int totalseats =seats[0]+seats[1]+seats[2];
    char choice=' ';

    bool flag=true;
    while(flag)
    {
    cout << "\nTotal seats   " << totalseats<<endl;
	cout << "\n1 - Firstclass    " << seats[0] << endl;
	cout << "\n2 - Business      " << seats[1] << endl;
	cout << "\n3 - Economy       " << seats[2] << endl;
	cout << "\nEnter Y if u wanna reserve a seat : ";
	cin >> choice;
    if(choice=='Y' || choice=='y')
    {
        int cat;
        std::cout<<"\n Please state the Category : ";
        std::cin>>cat;
        if(cat==1 && seats[0])
        {
            for(int i=0;i<k;i++)
            {
             for(auto j=0;j<M;j++)
             {
                if(arr[i][j]==0)
                std::cout<<"\n Seat No : "<<j<<" is Available \n";
             }
            }
            int num=-1;
            std::cout<<"\n Enter Seat Number : ";
            std::cin>>num;
            arr[0][num]=1;
            std::cout<<"\n Seat reserved\n";
            seats[0]--;
            totalseats--;
        }
        else if(cat==2 && seats[1])
        {
           for(int i=k;i<p;i++)
            {
             for(auto j=0;j<M;j++)
             {
                if(arr[i][j]==0)
                std::cout<<"\n Seat No : "<<j<<" is Available \n";
             }
            }
            int num=-1;
            std::cout<<"\n Enter Seat Number : ";
            std::cin>>num;
            arr[1][num]=1;
            std::cout<<"\n Seat reserved\n";
            seats[1]--;
            totalseats--;

        }
        else if(cat==3 && seats[2])
        {
           for(int i=p;i<N;i++)
            {
             for(auto j=0;j<M;j++)
             {
                if(arr[i][j]==0)
                std::cout<<"\n Seat No : "<<j<<" is Available \n";
             }
            }
            int num=-1;
            std::cout<<"\n Enter Seat Number : ";
            std::cin>>num;
            arr[2][num]=1;
            std::cout<<"\n Seat reserved\n";
            seats[2]--;
            totalseats--;
        }
        else std::cout<<"\n Seat Nae hai sojao \n";
    }
    else flag=false;
    }
}
