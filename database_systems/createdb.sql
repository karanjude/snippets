CREATE TABLE ANIMALS (
    id number primary key,
    name varchar(32),
    shape SDO_GEOMETRY)
/

CREATE TABLE TRUCKS (
    id number primary key,
    name varchar(32),
    shape SDO_GEOMETRY)
/

CREATE TABLE VACCINES (
    id varchar(32) primary key,
    name varchar(32))
/

CREATE TABLE VACCINE_ANIMALS (
	id varchar(32),
	name varchar(32),
	primary key(id,name)
)
/

CREATE TABLE TRUCK_VACCINES (
	id number,
	vaccine_id varchar(32),
	primary key(id,vaccine_id)
)
/