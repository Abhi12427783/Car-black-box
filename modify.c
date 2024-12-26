/*
Name:Abhiram A M
Description:Modify a value
Date:30/09/2024
Sample i/p:Enter the number 10
Sample o/p:After modifying,num is 15
*/
#include<stdio.h>
int modify(int n)
{
//modifying the value
int num = 5 + n;
return num;
}
int main()
{
int n;
printf("Enter the number : ");
scanf("%d",&n);
//printing and calling the function
printf("After modifying,num is %d",modify(n));
}
