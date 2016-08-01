CREATE TABLE stu_ship_storage (
	id serial PRIMARY KEY,
	ship_id int,
	commodity_id int,
	amount int
);
create index stu_ship_storage_ship_commodity_idx on stu_ship_storage(ship_id,commodity_id);
