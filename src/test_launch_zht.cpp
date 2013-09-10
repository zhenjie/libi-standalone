#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>

using namespace std;

int
CreateLocal( const std::string& cmd, const std::vector<std::string>& args )
{
    int ret = -1;

    // build a pipe we can use to tell us whether the 
    // child exec'd successfully
    int epipe[2];
    int pret = pipe( epipe );
    if( pret == -1 )
    {
        // we failed to create the "exec failed" pipe
        return -1;
    }

    // set the child's pipe endpoint to close automatically 
    // when it execs
    int fret = fcntl( epipe[1], F_GETFD );
    if( fret == -1 )
    {
        // we failed to retrieve the child endpoint descriptor flags 
        return -1;
    }
    fret = fcntl( epipe[1], F_SETFD, fret | FD_CLOEXEC );
    if( fret == -1 )
    {
        // we failed to set the child endpoint descriptor flags
        return -1;
    }

    // fork the child process
    pid_t pid = fork();
    if( pid > 0 )
    {
        // we're the parent

        // close the child's end of the "exec failed" pipe
        close( epipe[1] );

        // determine whether the child exec'd successfully
        int cval;
        int rret = read( epipe[0], &cval, sizeof(cval) );
        if( rret != sizeof(cval) )
        {
            // the child did not write on the "exec failed" pipe
            // so we know it exec'd OK
            ret = 0;
        }
        else
        {
            // the child wrote 'cval' on the "exec failed" pipe
            ret = cval;
        }
        close( epipe[0] );
    }
    else if( pid == 0 )
    {
        // we're the child

        // close the parent's end of the "exec failed" pipe
        close( epipe[0] );
        
        // build argument array
        
        char** argv = new char*[args.size() + 1];
	for( unsigned int i = 0; i < ( args.size() ); i++ )
	{
	    argv[i] = new char[args[i].length() + 1];
	    strcpy( argv[i], args[i].c_str() );
	}
	argv[args.size()] = NULL;

        // exec the command
        int eret = execvp( cmd.c_str(), argv );

        // the exec failed - tell our parent and bail
        write( epipe[1], (char*)&eret, sizeof(eret) );
        close( epipe[1] );
        delete[] argv;

        exit( -1 );
    }
    else
    {
        // the fork failed
        // cleanup the pipe
        close( epipe[0] );
        close( epipe[1] );
    }

    return ret;
}

int main(int argc, char *argv[])
{
   string kvs_exec_path = "./zhtserver";
   vector<string> kvs_args;
   kvs_args.push_back( kvs_exec_path );
   kvs_args.push_back( "-z" );
   kvs_args.push_back( "./zht.conf" );
   kvs_args.push_back( "-n" );
   kvs_args.push_back( "./neighbor.conf" );

   CreateLocal( kvs_exec_path, kvs_args );
   return 0;
}
