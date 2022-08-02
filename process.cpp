#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <cstdlib>


int test_foo1()
{
	return rand()%30;
}

int test_foo2()
{

	return rand()%30;
}

int test_foo3()
{

	return rand()%30;
}

int test_foo4()
{

	int a=rand()%30;
	throw;
	return a;
}

int test_function(int (*fptr)(),int funt_number,pid_t parent_id)
{
	if(parent_id==getpid())
	{
		pid_t _process_=fork();
		if (_process_==-1)
		{
			std::cout<< "process failed"<<std::endl;
			return -1;
		}
		else if(_process_==0)
		{
			std::cout<<"Process ID: "<<getpid()<<std::endl;
			std::cout<<"Parent Process ID: "<<getppid()<<std::endl;
			std::cout<<"Function Number: "<<funt_number<<std::endl;
			int state= fptr();
			if (state>=0&&state<=10)
			{
				std::cout<<"STATUS: "<<"Unresolved"<<std::endl<<std::endl;
				return 1;
				
			}
			else if (state>=11&& state<=20)
			{
				std::cout<<"STATUS: "<<"Success"<<std::endl<<std::endl;
				return 1;
			}
			else 
			{
		    	std::cout<<"STATUS: "<<"Failure"<<std::endl<<std::endl;
				return 1;
			}
		}
		else if(_process_!=0)
		{
			waitpid( _process_, 0, 0 );
			return 1;
		}
	}
	else 
	{
		return -1;
	}
	
}



int main()
{
	srand(time(NULL));
	pid_t main_processId=getpid();
	std::cout<<"Main Process ID: "<<main_processId<<std::endl<<std::endl;
	int count=4;
	int(*ff_ptr[count])()={test_foo1,test_foo2,test_foo3,test_foo4};

	for (size_t i = 0; i < count; i++)
	{
		test_function(ff_ptr[i],i,main_processId);
	}
	return 0;
}
