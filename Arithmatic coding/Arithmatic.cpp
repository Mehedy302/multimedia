#include<iostream>
#include<fstream>
#include<math.h>
#include<ctype.h>
#include <iomanip>
#include<string.h>
using namespace std;
double probab[256];
char input[10000];
void clac_probab(){

    int asscii[256];
    int track[256];

    double L = 0.0;
    double lower[256];
    double upper[256] ;
    double savelower[256];
    double saveupper[256] ;
    double up=1.0;
    double low = 0.0;

    for (int i = 0; i< 256;i++)
    {

        asscii[i]  =0;
        probab[i] = 0.0;

    }


    int count= 0;
    char c;
    ifstream inFile;

    inFile.open("input_acm.txt");

    if(inFile.is_open()){


        while(inFile >> noskipws >> c){
            if(isprint(c)){
                input[count] = c;
                asscii[(int)c] = asscii[(int)c] + 1;
                count  = count + 1;
            }

        }

        }
    else{

        cout<<"Can't Open File"<<"\n";
    }



       cout<<"numbers of character : "<<count<<"\n";

       for(int i = 0;i < 256;i++)
       {
           probab[i]  = round(((asscii[i]/(float)count)*10000.0)/10000.0);


       }

       for(int i = 0;i < 256;i++)
       {
           probab[i]  = asscii[i]/(float)count;


       }

        cout<<"Char \t"<<"Lower"<<"\t"<<"Upper\n";
        int j  = 0;
       for(int i = 0;i < 256;i++)
       {

           if (probab[i]!=0)
           {
               track[j] = i;
               lower[i] = L;
               savelower[i] = lower[i];

               upper[i] = lower[i] + probab[i];
               L  = upper[i];
               saveupper[i]  = upper[i];

               cout<<(char)i<<"\t"<<lower[i]<<"\t"<<upper[i]<<endl;
               j = j + 1;
           }

       }






       char current;
       for (int i = 0 ;i < count-1;i++)
       {

           current = input[i];
           low = lower[current];
           up = upper[current];
           L = low;
           double calc = 0;

           for(int k = 0; k<j;k++ )
           {


               calc = (upper[track[k]]- lower[track[k]])*probab[current];
               lower[track[k]] = L;

               upper[track[k]] = lower[track[k]] + calc;
               L  = upper[track[k]];
           }






       }

       ofstream out;
       out.open("aleout.txt");


       double runL = (upper[track[j-1]] + lower[track[0]])/2;
       out<<std::setprecision(15)<<runL;

        out.close();

        runL = 0;

       cout<<"Arithmatic Length Encodding = "<<std::setprecision(10)<<runL<<endl;

       ifstream inputR;
       inputR.open("aleout.txt");
       inputR>>runL;





       cout<<"Arithmatic Length Decodding  "<<endl;
       for(int  i =0; i< strlen(input);i++){
           for(int k = 0; k< j;k++)
           {


           if(runL<saveupper[track[k]] && runL>=savelower[track[k]])
           {
               cout<<(char)track[k]<<"\t"<<std::setprecision(10)<<runL<<endl;

               runL = (runL- savelower[track[k]])/(probab[track[k]]);



               break;
           }

           else{
            continue;
           }

           }




       }


}

int main()
{

    clac_probab();

}
