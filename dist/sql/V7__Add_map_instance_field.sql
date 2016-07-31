alter table stu_map add instance_id int default 0;
create index stu_map_coordinates_idx on stu_map(cx,cy,instance_id);
alter table stu_ship add map_instance_id int default 0;
