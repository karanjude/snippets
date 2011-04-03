insert into trucks values(1,'a',SDO_GEOMETRY(2001,NULL,SDO_POINT_TYPE(12,14,NULL),NULL,NULL));

select a.shape.sdo_point from animals a where rownum <= 2;

select a.id , a.name , a.shape.sdo_point from animals a where sdo_filter(a.shape, sdo_geometry(2003, NULL, NULL, sdo_elem_info_array(1,1003,3), sdo_ordinate_array(0,0,100,100))) = 'TRUE';

select t.id , t.name , t.shape.sdo_point from trucks t where sdo_filter(t.shape, sdo_geometry(2003, NULL, NULL, sdo_elem_info_array(1,1003,3), sdo_ordinate_array(0,0,100,100))) = 'TRUE';

select a.id , a.name , a.shape.sdo_point from animals a 
where sdo_filter(a.shape, sdo_geometry(2003, NULL, NULL, sdo_elem_info_array(1,1003,3), sdo_ordinate_array(0,0,100,100))) = 'TRUE'
and a.name in(
select va.name from vaccines v , vaccine_animals va where v.id=va.id and v.id in (select tv.vaccine_id from trucks t, truck_vaccines tv where tv.id = t.id and t.id = 3));

select count(*) from trucks t where sdo_filter(t.shape, sdo_geometry(2003, NULL, NULL, sdo_elem_info_array(1,1003,3), sdo_ordinate_array(0,0,100,100))) = 'TRUE';
select t.id, t.name from trucks t where sdo_nn(t.shape, sdo_geometry(2011,NULL,sdo_point_type(50,50,NULL),NULL,NULL), 'sdo_num_res=4') = 'TRUE';

select t.id, t.name,t.shape from trucks t, truck_vaccines tv where t.id=tv.id and
sdo_nn(t.shape, sdo_geometry(2011,NULL,sdo_point_type(50,50,NULL),NULL,NULL), 'sdo_num_res=4') = 'TRUE' and
tv.vaccine_id in (select v.id from vaccines v, vaccine_animals va where v.id=va.id and va.name='lion');


