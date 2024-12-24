#include<iostream>


int main()
{
int size=5;
// std::cin>>size;
// {x,x,x,x,x}
// int*arr=new int[size]{1,2,3,4,5};
int **arr= new int*[size];
for(auto i=0;i<size;i++)
arr[i]=new int[i];
}  
class point
{
    private:
    int x, y;
    point(int x, int y)
    {
        this->x=x;
        this->y=y;
    }
}

