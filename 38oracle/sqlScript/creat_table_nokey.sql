create table stu_no_key(
		id number,
		name varchar(20),
		course number(5)
);

create sequence id_num;

insert into stu_test values(1,'wingling',00001);
insert into stu_test values(1,'wingling',00002);
insert into stu_test values(2,'wingling',00003);
insert into stu_test values(2,'wingling',00004);
insert into stu_test values(3,'liuhong' ,00001);
insert into stu_test values(3,'liuhong',00002);
insert into stu_test values(4,'liuhong',00003);
insert into stu_test values(4,'liuhong',00004);
insert into stu_test values(5,'zhangsan',00001);
insert into stu_test values(5,'zhangsan',00002);
insert into stu_test values(6,'zhangsan',00003);
insert into stu_test values(6,'zhangsan',00004);
insert into stu_test values(7,'lisi',00001);
insert into stu_test values(7,'lisi',00002);
insert into stu_test values(8,'lisi',00003);
insert into stu_test values(8,'lisi',00004);

--没有主键重复表的删除
--select id,name,min(course) from stu_test group by id,name;

--delete from stu_no_key where course not in (select min(course) from stu_no_key group by id,name);
