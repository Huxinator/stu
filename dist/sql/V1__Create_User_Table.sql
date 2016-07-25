CREATE TABLE stu_user (
			id serial PRIMARY KEY,
			email text,
state int,
faction_id int,
password text,
name text
			);

INSERT into stu_user (id, email, password, name, faction_id, state) VALUES (1,'sometrek@example.com','$2y$10$nHYF6VsYaw8ZTxom2hvh8uWfo1cJLys7EwjpUBDG8bfv3H06Z3NVe','Example-User',1,0);
