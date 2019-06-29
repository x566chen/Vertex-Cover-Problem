#include<iostream>
#include <stdlib.h>
#include "stdio.h"
#include <cstdlib>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#define MAX 100


using namespace std;

string coor,coor1,coor2;
const int SIZE_CHAR = 32;
char ch1[SIZE_CHAR + 1] = {0};

double mult(int a1, int a2, int b1, int b2, int c1, int c2)
{
    return (a1-c1)*(b2-c2)-(b1-c1)*(a2-c2);
}

bool intersect(int a1, int a2, int b1, int b2, int c1, int c2, int d1, int d2)
{
    if ( max(a1, b1)<min(c1, d1) )
    {
        return false;
    }
    if ( max(a2, b2)<min(c2, d2) )
    {
        return false;
    }
    if ( max(c1, d1)<min(a1, b1) )
    {
        return false;
    }
    if ( max(c2, d2)<min(a2, b2) )
    {
        return false;
    }
    if ( mult(c1,c2,b1,b2, a1,a2)*mult(b1,b2, d1,d2, a1,a2)<0 )
    {
        return false;
    }
    if ( mult(a1,a2, d1,d2, c1,c2)*mult(d1,d2, b1,b2, c1,c2)<0 )
    {
        return false;
    }
    return true;
}


int main(int argc, char **argv) {
    
    // open /dev/urandom to read
    std::ifstream urandom("/dev/urandom");
    
    // check that it did not fail
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    int m1,m2,m3,m4;
    int k1,k2,k3;
    
    //----------------------------------------
    bool aflag = 0;
    bool bflag = 0;
    bool cflag = 0;
    bool dflag = 0;
    std::string avalue;
    std::string bvalue;
    std::string cvalue;
    std::string dvalue;
    int cint_value1,cint_value2,cint_value3,cint_value4;
    int index;
    int c;
    
    opterr = 0;
    
    // expected options are '-a', '-b', and '-c value'
    while ((c = getopt (argc, argv, "s:n:l:c:")) != -1)
        switch (c)
    {
        case 's':
            aflag = true;
            avalue = optarg;
            cint_value1 = atoi(avalue.c_str());
            break;
        case 'n':
            bflag = true;
            bvalue = optarg;
            cint_value2 = atoi(bvalue.c_str());
            break;
        case 'l':
            cflag = true;
            cvalue = optarg;
            cint_value3 = atoi(cvalue.c_str());
            break;
        case 'c':
            dflag = true;
            dvalue = optarg;
            cint_value4 = atoi(dvalue.c_str());
            break;
        case '?':
            if (optopt == 'c')
                std::cerr << "Error: option -" << optopt
                << " requires an argument." << std::endl;
            else
                std::cerr << "Error: unknown option: " << optopt << std::endl;
            return 1;
        default:
            return 0;
    }
    
    
    
    
    if (optind < argc) {
        std::cout << "Found positional arguments\n";
        for (index = optind; index < argc; index++)
            std::cout << "Non-option argument: " << argv[index] << "\n";
    }
    
    
    if(aflag==1){
        if(cint_value1>=2)
        {
            m1=cint_value1;
        }
        else{
            m1=10;
        }
    }
    else{
        m1=10;
    }
    
    if(bflag==1){
        if(cint_value2>=1)
        {
            m2=cint_value2;
        }
        else{
            m2=5;
        }
    }
    else{
        m2=5;
    }
    
    if(cflag==1){
        if(cint_value3>=5)
        {
            m3=cint_value3;
        }
        else{
            m3=5;
        }
    }
    else{
        m3=5;
    }
    
    if(dflag==1){
        if(cint_value4>=1)
        {
            m4=cint_value4;
        }
        else{
            m4=20;
        }
    }
    else{
        m4=20;
    }
    
    //------------------------------------------
    //  m1=10;//街道数量 2
    //  m2=5;//街道段数 1
    //  m3=5;//sleep time 5
    // m4=20;//坐标上下限 1
    //(b-a+1)+a
    unsigned int numberofS=MAX;
    
    
    while(!std::cin.eof()){
        
        int numerror;
        unsigned int num = 42;
        urandom.read((char*)&num, sizeof(int));
        k1=num%(m1-1)+2;
        //k2=num%(m2)+1;
        k3=num%(m3-4)+5;
        //int num1 = 42;
        // urandom.read((char*)&num1, sizeof(int));
        // k4=num1%m4;
        //   cout<<k1<<"   街道数量"<<endl;
        //cout<<k2<<"    segment of street"<<endl;
        //   cout<<k3<<"    sleep time"<<endl;
        int t=0;
        //  while(t<k1)
        //  {
        int max=m1*m2;
        int v[k1][max][2]; //MAX hang 5 lie
        int x,y,n;
        int numofS=0;
        if(numberofS!=MAX)
        {
            int j;
            for(j=0;j<numberofS;j++)
            {
                std::cout<<"r \"St"<<j<<"\""<<endl;
                
            }
        }
        numberofS=k1;
        while(numofS<k1){
            
            
            unsigned int num3 = 42;
            urandom.read((char*)&num3, sizeof(int));
            k2=num3%(m2)+1;
            //cout<<"\n"<<"k2="<<k2<<endl;
            
            std::cout<<"a"<<" "<<'"'<<"St"<<numofS<<'"'<<" ";
            
            int num11 = 42;
            int num21 = 42;
            urandom.read((char*)&num11, sizeof(int));
            x=num11%m4;
            urandom.read((char*)&num21, sizeof(int));
            y=num21%m4;
            v[numofS][0][0]=x;
            v[numofS][0][1]=y;
            std::cout<<"("<<v[numofS][0][0]<<","<<v[numofS][0][1]<<")";
            
            //----check I
            int point2x,point2y,point1x,point1y;
            
            unsigned int num5 = 42;
            urandom.read((char*)&num5, sizeof(int));
            point2x=num5%m4;
            unsigned int num6 = 42;
            urandom.read((char*)&num6, sizeof(int));
            point2y=num6%m4;
            v[numofS][1][0]=point2x;
            v[numofS][1][1]=point2y;
            point1x=v[numofS][0][0];
            point1y=v[numofS][0][1];
            while(point1x==point2x && point1y==point2y)
            {
                numerror=0;
                numerror++;
                if(numerror<=25)
                {
                    unsigned int num5 = 42;
                    urandom.read((char*)&num5, sizeof(int));
                    point2x=num5%m4;
                    unsigned int num6 = 42;
                    urandom.read((char*)&num6, sizeof(int));
                    point2y=num6%m4;
                    v[numofS][1][0]=point2x;
                    v[numofS][1][1]=point2y;
                    point1x=v[numofS][0][0];
                    point1y=v[numofS][0][1];
                }
                else
                {
                    std::cerr << "Error: generate valid input 25 times\n";
                    return 1;
                }
                
            }
            
            std::cout<<"("<<v[numofS][1][0]<<","<<v[numofS][1][1]<<")";
            
            //  ---------check II
            if (k2 >= 2)
            {
                int point3x,point3y;
                
                point1x=v[numofS][0][0];
                point2x=v[numofS][1][0];
                
                point1y=v[numofS][0][1];
                point2y=v[numofS][1][1];
                unsigned int num7 = 42;
                urandom.read((char*)&num7, sizeof(int));
                point3x=num7%m4;
                v[numofS][2][0]=point3x;
                unsigned int num8 = 42;
                urandom.read((char*)&num8, sizeof(int));
                point3y=num8%m4;
                v[numofS][2][1]=point3y;
                
                
                while (    ((point3y-point2y)*(point2x-point1x) == (point2y-point1y)*(point3x-point2x))
                       && !( (  (point3x-point2x)*(point2x-point1x)>0  && point2x!=point1x  )
                            ||(  (point3y-point2y)*(point2y-point1y)>0  && point2x==point1x )
                            )
                       )
                {
                    int numerror=0;
                    numerror++;
                    if (numerror<=25)
                    {
                        unsigned int num7 = 42;
                        urandom.read((char*)&num7, sizeof(int));
                        point3x=num7%m4;
                        v[numofS][2][0]=point3x;
                        unsigned int num8 = 42;
                        urandom.read((char*)&num8, sizeof(int));
                        point3y=num8%m4;
                        v[numofS][2][1]=point3y;
                        point1x=v[numofS][0][0];
                        point2x=v[numofS][1][0];
                        
                        point1y=v[numofS][0][1];
                        point2y=v[numofS][1][1];
                        
                    }
                    else
                    {
                        std::cerr << "Error: failed to generate valid input for 25 simultaneous attempts\n";
                        return 1;
                    }
                }
                
                std::cout<<"("<<v[numofS][2][0]<<","<<v[numofS][2][1]<<")";
            }
            
            
            
            
            
            
            //---------------
            n=3;
            while(n<=k2){
                
                int num1 = 42;
                int num2 = 42;
                urandom.read((char*)&num1, sizeof(int));
                x=num1%m4;
                urandom.read((char*)&num2, sizeof(int));
                y=num2%m4;
                v[numofS][n][0]=x;
                v[numofS][n][1]=y;
                
                //-------------------check I
                point1x=v[numofS][n-1][0];
                point1y=v[numofS][n-1][1];
                while(point1x==x && point1y==y)
                {
                    numerror=0;
                    numerror++;
                    if(numerror<=25)
                    {
                        unsigned int num11 = 42;
                        urandom.read((char*)&num11, sizeof(int));
                        x=num11%m4;
                        unsigned int num12 = 42;
                        urandom.read((char*)&num12, sizeof(int));
                        y=num12%m4;
                        v[numofS][n][0]=x;
                        v[numofS][n][1]=y;
                        point1x=v[numofS][n-1][0];
                        point1y=v[numofS][n-1][1];
                    }
                    else
                    {
                        std::cerr << "Error: generate valid input 25 times\n";
                        return 1;
                    }
                    
                }
                
                //-----------check II
                
                
                point1x=v[numofS][n-2][0];
                point2x=v[numofS][n-1][0];
                
                point1y=v[numofS][n-2][1];
                point2y=v[numofS][n-1][1];
                
                
                
                while (    ((y-point2y)*(point2x-point1x) == (point2y-point1y)*(x-point2x))
                       && !( (  (x-point2x)*(point2x-point1x)>0  && point2x!=point1x  )
                            ||(  (y-point2y)*(point2y-point1y)>0  && point2x==point1x )
                            )
                       )
                {
                    int numerror=0;
                    numerror++;
                    if (numerror<=25)
                    {
                        unsigned int num13 = 42;
                        urandom.read((char*)&num13, sizeof(int));
                        x=num13%m4;
                        v[numofS][n][0]=x;
                        unsigned int num14 = 42;
                        urandom.read((char*)&num14, sizeof(int));
                        y=num14%m4;
                        v[numofS][n][1]=y;
                        point1x=v[numofS][n-2][0];
                        point2x=v[numofS][n-1][0];
                        
                        point1y=v[numofS][n-2][1];
                        point2y=v[numofS][n-1][1];
                        
                    }
                    else
                    {
                        std::cerr << "Error: failed to generate valid input for 25 simultaneous attempts\n";
                        return 1;
                    }
                }
                
                
                

                
                
                
                
                
                
                
                //------------------
                std::cout<<"("<<v[numofS][n][0]<<","<<v[numofS][n][1]<<")";
                
                n=n+1;
                
            }
            
            
            
            numofS=numofS+1;
            std::cout<<endl;
        }
        
        t=t+1;
        
        
        
        std::cout<<"g"<<endl;
        sleep(k3);
        
    }
    
}
