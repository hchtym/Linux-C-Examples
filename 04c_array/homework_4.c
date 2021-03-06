/*1、输出输入的非负整数的最大值*/
#include <stdio.h>
int main(  )
    {
        int input;
        int max=-1;
        
        printf( "Please input integers end with 0 or minus\n" );
        while( scanf( "%d",&input )&&input>0 )
            {
                if( input>max )
                    max=input;
            }
        printf( "the max is %d\n",max);
        return 0;
    }

/*2、计算两个整数的最大公约数*/
#include<stdio.h>
int main(  )
    {
        int int_one,int_two,result;
        printf( "Please input two integers\n" );
        scanf( "%d%d",&int_one,&int_two );
        if( int_one>int_two )
            {
                int temp=int_one;
                int_one=int_two;
                int_two=temp;
            }
        if( int_two%int_one==0 )
            result=int_one;
        else
            {
                for( int i=int_one/2;i>0;++i )
                    {
                        if( int_two%i==0 )
                            {
                                result=i;
                                break;
                            }
                    }
            }
        printf( "最大公约数为%d\n",result );
        return 0;
    }

/*3、万年历
  输入年份和月份，打印该年该月的月历
 */
#include <stdio.h>
#include <stdbool.h>
int main(  )
    {
        int year;
        int month;
        int m_month[ 12 ]={31,28,31,30,31,30,31,31,30,31,30,31};
        printf( "请输入年份和月份\n" );
        scanf( "%d%d",&year,&month );

        short int week_day;
        bool is_leap_year=0;
        long sum=0;
        
        is_leap_year= (year%400==0||(year%4==0&&year%100!=0));
        if( is_leap_year )
            m_month[ 1 ]=29;

        sum = (year*365 + year/4 -year/100 +year/400);
        for( int i=0;i<month-1;++i )
            sum+=m_month[ i ];
        week_day=sum%7;
        //printf( "第一天为:%d\n",week_day );

        bool is_blank=0;  //用于在日历第一行输出空格
        short int count=0;  //用于累计日历一行输出的日期数，满7回车
        printf( "日  一  二  三  四  五  六\n" );

        for( int i=1;i<=m_month[ month-1 ];  )
            {
                if( !is_blank )      //在第一行输出空格
                    {
                        for( int j=1;j<=week_day;++j )
                            printf( "    " );
                        is_blank=1;
                    }
                if( i<=7-week_day )   //在第一行输出日期，此时conut=0导致回车
                       {
                           for( int j=1;j<=7-week_day;++j )
                           {
                               printf( "%2d  ",i );
                               ++i;
                           }
                       }
                else                      //其他行输出日期
                   {
                       printf( "%2d  ",i );
                       ++count;
                       ++i;
                   }
               
                if( count%7==0 )    //其他行满7输出换行符
                    {
                        printf( "\n" );
                        count=0;
                    }
                    
            }
        printf( "\n" );
        return 0;
    }


/*4、二进制查看器*/
#include <stdio.h>
#include <stdbool.h>
int main()
    {
        int input,temp;
        bool memory[ 32 ]={0}; 
        
        printf( "Please input an integer \n" );
        scanf( "%d",&input );
        temp=input;
        int bites=0;
        
        while( temp&&bites<32 )
            {
                if( temp&1 )
                    memory[ bites ]=1;
                else
                    memory[ bites ]=0;
                
                temp=temp>>1;
                ++bites;
            }

        for( int i=31;i>-1;--i )
            printf( "%d",memory[ i ] );
        printf( "\n" );

        return 0; 
    }
/*
  另一种使用左移的方法:
  for( int i=0;i<sizeof( int )*8;++i )
  {
  if( x>=0 )printf( "0" );
  else printf( "1" );
  x<<=1;
  }
 */

/*5、网络新手B1FF消息公告转换*/
#include <stdio.h>
int main(  )
    {
        char message[ 100 ];
        printf( "Please input a message with lenght small than 100\n" );
        int i=0;
        while( scanf("%c",&message[ i ])&&message[ i ]!='\n' )
                ++i;
        
        for( int j=0;j<i;++j )
            {
                switch( message[ j ] )
                    {
                    case 'A':
                    case 'a':
                        message[ j ]='4';break;
                    case 'B':
                    case 'b':
                        message[ j ]='8';break;
                    case 'E':
                    case 'e':
                        message[ j ]='3';break;
                    case 'I':
                    case 'i':
                        message[ j ]='1';break;
                    case 'O':
                    case 'o':
                        message[ j ]='0';break;
                    case 'S':
                    case 's':
                        message[ j ]='5';break;
                    default:
                        {
                            if( 'a'<=message[ j ]&&message[ j ]<=122 )
                                message[ j ] -=32;
                        }
                    }
            }
        for( int j=0;j<i;++j )
            {
                printf( "%c",message[ j ] );
            }
        printf( "!!!!!!!!!!\n");
        return 0; 
  }

/*6、凯撒加密*/
#include <stdio.h>
int main(  )
    {
        char message[ 100 ];    //存储用户输入信息
        int n;                             //存储移位量
        printf( "Please input the bites to move\n" );
        scanf( "%d%*c",&n );
         
        printf( "Please input a message with lenght small than 100\n" );
        int i=0;
        while(scanf( "%c",&message[ i ] )&&message[ i ]!='\n')
            ++i;
     
        for( int j=0;j<i;++j )
            {
                if( ('A'<=message[ j ]&&message[ j ]<='Z'))
                    message[ j ]=( ( message[ j ]-'A' )+n )%26+'A';
                else if( ('a'<=message[ j ]&&message[ j ]<='z') )
                    message[ j ]=( ( message[ j ]-'a' )+n )%26+'a';      
            }

        printf( "%s",message );
        return 0;
    }

/*7、约瑟夫问题*/
/*方法就是每剔除一个人的时候,按照往后的顺序
 重新放入到数组中,再重复进行*/
#include <stdio.h>
int main(  )
    {
        int i,j;
        int count;
        char peop_ary[10];
        char temp_ary[ 10 ];
        char eatchar;
        printf( "请输入人数\n" );
        scanf( "%d%c",&count,&eatchar );
        printf( "请输入各人的代号(代号为单个字母,中间不要添加空格 )\n" );
        for( i=0;i<count;++i )
            scanf( "%c",&peop_ary[ i ] );

        int t,k;
        printf( "被杀的顺序为:\n" );
        
        for( i=0;i<count;++i )
            {
                j=0;
                t=8%(count-i);
                if( t!=0 )
                    printf( "%c ",peop_ary[ t-1 ] );
                else
                    printf( "%c ",peop_ary[ count-i-1 ] );
                 
                k=t;
                while( k<count-i )
                    {
                        temp_ary[ j ]=peop_ary[ k ];
                        ++j;
                        ++k;
                    }
                k=0;
                while( k<t )
                    {
                        temp_ary[ j ]=peop_ary[ k ];
                        ++j;
                        ++k;
                    }
                k=0;
                while( k<count-i-1 )
                    {
                        peop_ary[ k ]=temp_ary[ k ];
                       ++k;
                    }                
            }
        printf( "\n" );
        return 0;
        
    }
/*约瑟夫问题*/
/*使用一个标志数组，若已经被杀则为1,然后计数的时候直接跳过为1的项*/
#include <stdio.h>
#include <stdbool.h>
#define HUMEN    4
int main(  )
        {
                bool  humen[ HUMEN ]={0};
                short int i=0,j=0,count=0;
                for( j=0;j<HUMEN;++j )
                        {
                                while( count<=8 )
                                        {
                                                if( !humen[ i ] )
                                                {
                                                        ++count;
                                                        if( !(count%8) )
                                                        {
                                                           printf( "%d ",i+1 );
                                                           humen[ i ]=1;
                                                           break;    //此次计数完毕，跳出本次循环
                                                        }
                                                }
                                                ++i;
                                                i %=4;
                                        }
                                count=0;
                                
                        }
                printf( "\n" );
                return 0;
                
        }
