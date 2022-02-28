#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    //variabile diverse
    int i, j, k;

    //diferite variabile care modifica proprietatile tablei;
    int height=9, width=9, mines=10;


    //creare tabla si umplerea ei cu spatii goale
    int table[height+2][width+2];
    for (i=0; i<height+2; i++)
        for (j=0; j<width+2; j++)
            table[i][j]=0;


    //pozitionarea minelor
    k=1;
    while (k<=mines)
    {
        i=rand() % height + 1;
        j=rand() % width + 1;
        if (table[i][j]!=9)
        {
            table[i][j]=9;
            k++;
        }
    }


    //stabilirea numarului de mine de langa fiecare spatiu
    for (i=1; i<=height; i++)
        for (j=1; j<=width; j++)
            if (table[i][j]==0)
            {
                k=0;
                if (table[i-1][j-1]==9)
                    k++;
                if (table[i][j-1]==9)
                    k++;
                if (table[i+1][j-1]==9)
                    k++;
                if (table[i-1][j]==9)
                    k++;
                if (table[i+1][j]==9)
                    k++;
                if (table[i-1][j+1]==9)
                    k++;
                if (table[i][j+1]==9)
                    k++;
                if (table[i+1][j+1]==9)
                    k++;
                table[i][j]=k;
            }


    //afisare tabla in consola
    for (i=1; i<=height; i++)
    {
        for (j=1; j<=width; j++)
            cout<<table[i][j]<<"  ";
        cout<<endl<<endl;
    }
    return 0;
}
