/*1、检查一个字符串是否是数字字符串*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
bool is_digit( char* str)
        {
                char *p=str;
                while( *p!='\0' )
                        {
                                if( (*p>='0'&&*p<='9') )
                                        ++p;
                                else if( *p=='+'||*p=='-' )
                                        {
                                                if( p==str )
                                                        ++p;
                                                else
                                                        break;
                                        }
                                else
                                        break;
                        }
                
                if( p-str>=strlen( str ) )
                        return 1;

                return 0;
        }
int main(  )
        {
                char str[ 20 ];
                printf( "请输入一个长度小于20\n" );
                scanf( "%s",str );
                if( is_digit( str ) )
                        printf( "是数字串\n" );
                else
                        printf( "不是数字串\n" );
                return 0;
        }

/*2、检查一个字符串是否是实数字符串*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
bool is_digit( char* str)
        {
                char *p=str;
                short int  count=0;
                while( *p!='\0' )
                        {
                                if( (*p>='0'&&*p<='9') )
                                        ++p;
                                else if( *p=='.' )
                                        {
                                           ++count;
                                           ++p;
                                        }
                                else if( *p=='-'||*p=='+' )
                                        {
                                                if( p==str )
                                                        ++p;
                                                else
                                                        break;
                                        }
                                else
                                        break;
                        }
                if( p-str>=strlen( str )&&count<=1 )
                        return 1;

                return 0;
        }
int main(  )
        {
                char str[ 20 ];
                printf( "请输入一个长度小于20\n" );
                scanf( "%s",str );
                if( is_digit( str ) )
                        printf( "是实数字串\n" );
                else
                        printf( "不是实数字串\n" );
                return 0;
        }

/*3、把一个字符串按给定字符分割输出*/
#include <stdio.h>
void split_str( char *str,char chr )
        {
                while( *str!='\0' )
                        {
                                if( *str!=chr )
                                        printf( "%c",*str);
                                else
                                        printf( "\n" );
                                ++str;
                        }
        }

int main(  )
        {
                char str[ 50 ];
                char chr;  
                printf( "请输入一个字符串\n" );
                scanf( "%s",str );
                printf( "请输入一个分隔符\n" );
                scanf( "%*c%c",&chr );
                
                split_str( str,chr );
                printf( "\n" );
                return 0;
        }

/*4、寻找一个字符串中出现的最长子串*/
#include <stdio.h>
#include <string.h>

int find_max_str( const char* str,int size,const char** substr )
        {
                int i,j,p1,p2;
                int count=0,tmpcount=0;
                int star1,star2;
                int dest1,dest2;                    /*dest1为最长子串的第一个下标,dest2为其第二个下标地址*/
                for( i=0;i<size;++i )   /*str[ i ]当作每一个子串的开始*/
		{
			for( j=i+1;j<size;++j )   /*遍历i+1~size,找到以str[ i ]开头的最长子串*/
			{
				p1=i;p2=j;
				if( str[ p1 ]==str[ p2 ])
				{
					star1=p1;star2=p2;
					while( str[ p1 ] ==str[ p2 ] &&p1<star2)  /*预读取*/
					{     /*打桩查看变量*/
						++tmpcount;
						++p1;  ++p2;
					}
				}
				if( count<tmpcount )
				{
					count=tmpcount;
					dest1=star1;dest2=star2;
				}
				tmpcount=0;
			}
		}
                *substr=&str[ dest1 ];
                return count;
        }

int main(  )
{
                char str[ 50 ];
                int substr_len=0;
                const char* substr=NULL;
                printf( "请输入一个长度小于50的字符串\n" );
                fgets( str,49,stdin );
                
                substr_len=find_max_str( str,strlen( str ),&substr );
                printf( "最长的子串长度为%d\n",substr_len );
                for(int i=0;i<substr_len;++i  )
                        printf( "%c",substr[ i ] );
                printf( "\n" );
                
                return 0;
        }
