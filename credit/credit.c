#include <cs50.h>
#include <stdio.h>
#include<math.h>

bool checksum(long n, int count);

int main(void)
{
    long cardno = get_long("what's your card no.: ");//asking user for card no.
    int count = 0;
    long ocardno = cardno;
    while (ocardno != 0)//counting the no. of digits
    {
        ocardno /= 10;
        count++;
    }

    int fd = cardno / pow(10, (count - 1)); // storing the first digit in a vriable
    int f2d = cardno / pow(10, (count - 2)); // storing first 2 digits of the card

    if ((count == 13 || count == 16) && checksum(cardno, count) && (fd == 4))//for visa
    {
        printf("VISA\n");
    }
    else if ((count == 16) && checksum(cardno, count) && (f2d == 51 || f2d == 52 || f2d == 53 || f2d == 54
             || f2d == 55))//for mastercard
    {
        printf("MASTERCARD\n");
    }
    else if ((count == 15) && checksum(cardno, count) && (f2d == 34 || f2d == 37))//for american express
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }


}

bool checksum(long n, int count)// checksum through luhn,s algorithm
{
    int rem1 = 0;
    int rem2 = 0;
    int r1;
    int r2;
    long on = n;// storing the no. in another variable for further process

    for (int i = 0; i < count; i++)
    {
        n /= 10;//making the no. a digit lessar

        r1 = n % 10; // now taking the last digit of obtained no.

        if (((r1 * 2) / 10) != 0)//if the digit multiplied with 2 and no. is 2 digits, then the no.s digits will add up
        {
            int rx1 = (r1 * 2) % 10;

            r1 = (2 * r1) / 10;

            r1 += rx1;
            rem1 += r1;
        }

        else
        {
            rem1 += r1 * 2;//when no. is not a 2 digit no. it will simply add up!!
        }
        n /= 10; //again making the no. a digit lessar

        r2 = on % 10; //now taking the last digit

        rem2 += r2;//and adding up the no.
        on /= 100;//now taking the next digit after 2 digits
    }



    if ((rem1 + rem2) % 10 == 0) //now checking if the obtained no. last digit 0
    {
        return 1;//if the checksum is true
    }
    else
    {
        return 0;//if the check sum is false
    }
}