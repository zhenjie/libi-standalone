LIBI Standalone
===============


How to Compile
--------------
  - ./configure
  - cd build/xxxx/
  - make 
  - make examples


Usage
-----
Go to *build/xxxx/bin* and follow the usage.

```
Usage: 
	./testmain [-r|-s|-8] [-f hostfile] [-c proc_count] [-p member_exec_path]
	--rsh or -r =>RSH launch mode 
	--slurm or -s  => SLURM launch mode 
	--8slurm or -8 => Full SLURM launch mode 
	--hostfile path or -f path => Specify host file
	--count COUNT or -c COUNT => Specify num of process in each host
	--process path or -p path => Spefic member executable
	--help or -h => Print out this help message

	Using -hostfile or -f will ignore --count/-c
	Run testmain without arguments is the same as ./testmain -r -c 2 -p testmember
```

A bit more
----------
The format of hostfile:
* Each line contains a hostname without surrounding space;
* Might use '\n' to split two hostnames;
* Last line cannot be empty;

Example:
```
spider1

spider2
```
