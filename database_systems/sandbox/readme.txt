name : karan singh
id : 5577894215
email : karans@usc.edu

List of files:

==java source files
./src/TruckRenderer.java
./src/QueryExecutior.java
./src/SqlReader.java
./src/hw2.java
./src/Vaccine.java
./src/ConnectionInfo.java
./src/AnimalRenderer.java
./src/MainUI.java
./src/SqlHelper.java
./src/Animals.java
./src/DbCreator.java
./src/Trucks.java
./src/Animal.java
./src/populate.java
./src/Truck.java
./src/TextFileReader.java

==java junit test cases

./tests/SqlReaderTest.java
./tests/DBTests.java
./tests/TextFileReaderTest.java
./tests/SqlHelperTest.java

==text files 

./readme.txt
./animals.txt
./config.txt
./trucks.txt
./vaccines.txt

==ant build file

./buildhw2.xml

==runnable jar files

./hw2.jar
./populate.jar

==sql files

./src/sql/dropdb.sql
./src/sql/createdb.sql
./src/create_user.sql

the best way to build the project is to use ant. Untar all the file and directories. Go to the base directory and type

 ant -buildfile buildhw2.xml

This will create all dirs and class files.

you can then run populate and hw2 via ant also , using the command 

 ant -buildfile buildhw2.xml populate
 ant -buildfile buildhw2.xml hw2

You can also choose the precompiled jar if that is easy for you. To run the programs use the following command

 java -jar populate.jar animals.txt trucks.txt vaccines.txt config.txt
 java -jar hw2.jar config.txt
