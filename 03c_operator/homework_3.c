/*1、判断一个不超过10000的数的位数*/
#include <stdio.h>

int main(  )
    {
        int number;
        printf( "请输入一个不超过4位的数字\n" );
        scanf( "%d",&number );

        if( number<=9 )
            printf( "1位\n" );
        else if( number>9&&number<=99 )
            printf( "2位\n" );
        else if( number>99&&number<=999 )
            printf( "3位\n" );
        else if( number>999&&number<=9999 )
            printf( "4位\n" );
        else
            printf( "ERROR:输入超过要求范围!\n" );

        return 0;
        
    }

/*2、输入24小时制时间，输出12小时制时间*/
#include <stdio.h>

int main(  )
    {
        int hour,miniter;
        printf( "请输入时间( EX: 23:39 )\n" );
        scanf( "%d:%d",&hour,&miniter );

        if( hour<12 )
            printf( "AM %d:%d\n",hour,miniter );
        else if( hour==12 )
            printf( "PM %d:%d\n",hour,miniter );
        else if( hour==24 )
            {
                if( miniter!=0 )
                    printf( "ERROR:应当输入0:%d\n",miniter );
                else
                     printf( "AM 0:00\n" );
            }
        else
            printf( "PM %d:%d\n",hour-12,miniter );

        return 0;
        
    }

/*3、比较两个年份的早晚*/
#include <stdio.h>

int main(  )
    {
        int a[ 3 ];
        int b[ 3 ];
        
        printf( "请输入第一个日期:( EX:1999-3-18 )\n" );
        for( int i=0;i<3;++i )
            scanf( "%d%*c",&a[ i ] );             
         printf( "请输入第二个日期:( EX:1999-3-18 )\n" );
        for( int i=0;i<3;++i )
            scanf( "%d%*c",&b[ i ] );
         
        if( a[ 0 ]<b[ 0 ] )
            printf( "%d-%d-%d更早\n",a[ 0 ],a[ 1 ],a[ 2 ] );
        else if( a[ 0 ]>b[ 0 ] )
            printf( "%d-%d-%d更早\n",b[ 0 ],b[ 1 ],b[ 2 ] );
        else
            {
                if( a[ 1 ]<b[ 1 ] )
                    printf( "%d-%d-%d更早\n",a[ 0 ],a[ 1 ],a[ 2 ] );
                else if( a[ 1 ]>b[ 1 ] )
                    printf( "%d-%d-%d更早\n",b[ 0 ],b[ 1 ],b[ 2 ] );
                else
                    {
                        if( a[ 2 ]<b[ 2 ] )
                            printf( "%d-%d-%d更早\n",a[ 0 ],a[ 1 ],a[ 2 ] );
                        else if( a[ 2 ]>b[ 2 ] )
                            printf( "%d-%d-%d更早\n",b[ 0 ],b[ 1 ],b[ 2 ] );
                        else
                            printf( "两个年份一样\n" );
                    }
            }

        return 0;
        
    }

/*4、求个人所得税*/
#include <stdio.h>

int main(  )
    {
        float salary;  //工资
        float insure;  //三险一金
        float tax;       //个人所得税
        
        printf( "请输入工资和三险一金的数额\n" );
        scanf( "%f%f",&salary,&insure );

        float temp;
        temp=salary-insure-2000;
        if( temp<=0 )
            tax=0.0;
        if( temp<=500 )
            tax=temp*0.05;
        else if( temp<=2000 )
            tax=25+( temp-500 )*0.1;
        else if( temp<=5000 )
            tax=175+( temp-2000 )*0.15;
        else if( temp<=20000 )
            tax=625+( temp-5000 )*0.2;
        else if( temp<=40000 )
            tax=3625+( temp-20000 )*0.25;
        else if( temp<=60000 )
            tax=8625+( temp-40000 )*0.3;
        else if( temp<=80000 )
            tax=14625+( temp-60000 )*0.35;
        else if( temp<=100000 )
            tax=21625+( temp-80000 )*0.4;
        else
            tax=29625+( temp-100000 )*0.45;

        printf( "个人所得税为:%g\n",tax );
        return 0;
        
    }









