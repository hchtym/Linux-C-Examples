
---------------------------------------------------------------------------

��ʼ��ʱ�����ǿ������ļ�һ��   ��������ϸ����־���ݲ��뵽һ�ű���
���ǵ����Ͽ���һ������ű��аѷ�����һ����������ϵ����  ÿһ����
��һ���µ��������ϵ��±�

�����Ļ����ǿ���ͨ��һ��sqlֱ�Ӱѷ��ϲ�ѯ�����ݲ��뵽��Ӧ�ı�
�漰�Ĵ洢�������£�
һ��ִ��һ�εĴ洢����
create or replace   procedure  day_zhenghe
as
begin
   execute immediate 'insert into  daydata'||to_char(sysdate,'dd')||  
        ' select max(id),max(username),max(logouttime),sum(durations) '||
	    'from  logdetailts  where  logouttime>='''||to_date(trunc(sysdate,'dd'))  
	       ||''' and  logouttime<'''||to_date(trunc(sysdate+1,'dd'))||
	       ''' group by username ';
    commit;
end;
һ����ִ��һ�εĴ洢����
create or replace   procedure  month_zhenghe
as
begin
    execute immediate 'insert into  monthdata'||to_char(sysdate+1,'mm')||  
        ' select max(id),max(username),max(logouttime),sum(durations) '||
	    'from  logdetails  where  logouttime>='''||to_date(trunc(sysdate,'mm'))  
	       ||''' and  logouttime<'''||to_date(trunc(add_months(sysdate,1),'mm'))||
	       ''' group by username ';
end;



---------------------------------------------------------------------------------
 ���ĸ���һЩ���£�
 �ȴ��� ���кͱ�
 create sequence  test_s;
 ����һ���洢���� ����31�ű� �����洢ÿ�����ϸ��Ϣ  
 ��1��1�ŵĺ�2��1�ŵĶ�����logdetailt1��
 create  or replace  procedure createlogtables 
 is
 begin 
    for  i in 1..31  loop
       execute immediate 'create table  logdetailt'||i||'(
      id  number primary key,
      username  varchar(30),
      logouttime  date,
      durations   number)';
    end loop;
 end;
 ɾ��31�ű�
 create  or replace  procedure droplogtables 
 is
 begin 
    for  i in 1..31  loop
       execute immediate 'drop table  logdetailt'||i;
    end loop;
 end;
 select trunc(dbms_random.value(0,20)) from dual;
 
 ͬʱ����31������ͳ�����ݵ������ݱ�
 create  or replace  procedure createdaydatatables 
 is
 begin 
    for  i in 1..31  loop
       execute immediate 'create table  daydata'||i||'(
      id  number primary key,
      username  varchar(30),
      logouttime  date,
      durations   number)';
    end loop;
 end;
 ɾ��31�ű�
 create  or replace  procedure dropdaydatatables 
 is
 begin 
    for  i in 1..31  loop
       execute immediate 'drop table  daydata'||i;
    end loop;
 end;

 ����12���µ������ݱ�
 create  or replace  procedure createmonthdatatables 
 is
 begin 
    for  i in 1..12  loop
       execute immediate 'create table  monthdata'||i||'(
      id  number primary key,
      username  varchar(30),
      logouttime  date,
      durations   number)';
    end loop;
 end;
 ɾ��12�ű�
 create  or replace  procedure dropdatatables 
 is
 begin 
    for  i in 1..12  loop
       execute immediate 'drop table  monthdata'||i;
    end loop;
 end;
 ģ������   5���Ӳ���һ������  ģ����ɺ���ͳ�Ƴ���ȥͳ����Щ����
 ���ݵ�ǰ������ѡ�������Ӧ�ı�  1�ŷ����1  2�ŵ����ݷ����2
 
 ģ��Ĵ洢�������£�
 create or replace procedure data_moni  
 is
    uname  varchar(30);
 begin    
     execute immediate 'insert into logdetailt'||to_char(sysdate,'dd')||'(id,username,logouttime,durations)' 
     ||'values(test_s.nextval,''test''||to_char(trunc(dbms_random.value(0,20)))
     ,sysdate,trunc(dbms_random.value(0,15)))';
     commit;
 end data_moni;
 ���һ��д����������ô��̬��  ������д��ôһ���򵥵��  Ȼ��д������Ĵ���
 create or replace procedure data_moni  
 is
    uname  varchar(30);
 begin    
     execute immediate 'insert into logdetailt'||to_char(sysdate,'dd')||'(id,username,logouttime,durations)' 
     ||'values(test_s.nextval,''test'',''1-AUG-11'',10)';
     commit;
 end data_moni;

 

�������ȳ���  ��ÿ5���ӵ���һ��ģ��������ݵĴ洢����  ����೤ʱ���Լ���������ĵ����������Ϳ�
��һ�������ǹ����� �ڶ����ǵ��õĴ洢����  �������ǿ�ʼʱ��  ���ĸ�����һ��ִ�е�ʱ��
 declare
   jobno  binary_integer;
 begin     
     dbms_job.submit(jobno,'data_moni;',sysdate,'sysdate+1/(24*12)'); 
     dbms_output.put_line(jobno);
     dbms_job.run(jobno);
     commit;
 end;
 
�ѳ������  

�����洢���� ����һ������һ�ε�ԭ�� ��ǰһ����������ϵ������
���ʱ��Ҫ����ȥ�����±� ��һ���µ�ʱ��Ҫ�������
�洢�������£�


create  sequence  test_s_s;
create or replace   procedure  day_zhenghe
as
begin
   execute immediate 'insert into  daydata'||to_char(sysdate-1,'dd')||  
        ' select test_s_s.nextval,u,t ,d from (select max(username) u,max(logouttime) t,sum(durations) d '||
	    'from  logdetailt'||to_char(sysdate-1,'dd')||'  where  logouttime>='''||to_date(trunc(sysdate,'dd'))  
	       ||''' and  logouttime<'''||to_date(trunc(sysdate+1,'dd'))||
	       ''' and username not in(select distinct username 
	       from  daydata'||to_char(sysdate-1,'dd')||') group by username)';
  
    commit;
end;


���ʱ�������ݱ����Ѿ���������  ������ȫ���Դ������ݱ���ȡ���ݷ��������ݱ���
����������п����е�����Ҫ���� �е������ǲ��� �������Ը���һЩ
create or replace   procedure  month_zhenghe
as
sqlstr  varchar2(200);
type  day_cur  is ref cursor;
data  monthdata2%rowtype;
begin
    /*
    1.�ȵõ��������� ����cursor��
    2.�������������ǲ��뻹�Ǹ���
    */
    sqlstr:='select max(username) u,max(logouttime) t,sum(durations) d '||
	    'from  logdetailt'||to_char(sysdate-1,'dd')||'  where  logouttime>='''||to_date(trunc(sysdate,'dd'))  
	       ||''' and  logouttime<'''||to_date(trunc(sysdate+1,'dd'))||
	       ''' group by username';
    open day_cur for sqlstr;
    fetch  day_cur into data;
    dbms_output.put_line(data.id);
    close day_cur;
end;

create or replace   procedure  month_zhenghe
as
sqlstr  varchar2(200);
type  data_cur  is ref cursor;
data  monthdata2%rowtype;
daycur  data_cur;
uname varchar2(30);
ucount number:=0;
begin
    sqlstr:='select max(id),max(username) u,max(logouttime) t,sum(durations) d '||
	    'from  logdetailt'||to_char(sysdate,'dd')||'  where  logouttime>='''||to_date(trunc(sysdate,'dd'))  
	       ||''' and  logouttime<'''||to_date(trunc(sysdate+1,'dd'))||
	       ''' group by username';
    open  daycur for sqlstr;
    loop
    fetch daycur into data;
    exit when daycur%notfound;
    dbms_output.put_line(data.username);
    sqlstr:='select count(*)  from monthdata'||to_char(trunc(sysdate,'mm')-1,'fmmm')||
    ' where username='''||data.username||'''';
    execute immediate  sqlstr into ucount;
    dbms_output.put_line(ucount);
    if  ucount=0 then
    execute immediate 'insert into monthdata'||to_char(trunc(sysdate,'mm')-1,'fmmm')||' values
    (test_s_s.nextval,'''||data.username||''','''||data.logouttime||''','||data.durations||')';
    else
    execute immediate 'update monthdata'||to_char(trunc(sysdate,'mm')-1,'fmmm') ||' set 
    logouttime='''||data.logouttime||''',durations=durations+'||data.durations||' where username='''||data.username
    ||'''';
    end if;
    end loop;
 close daycur;
end;

