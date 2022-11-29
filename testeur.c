#include "include/pipex.h"

int main()
{
    char    **infile;
    char    **outfile;
    char    **args;
    int     pid = 0;

    str = "carvlj /ls cat";
}

tests a realiser :

OK
./pipex bad_infile.txt carlvjs cat ls outfile.txt
< bad_infile.txt carlvjs | cat | ls > outfile.txt

OK
./pipex carlvjs /ls cat ls outfile.txt
< carlvjs /ls | cat | ls > outfile.txt

OK
./pipex infile.txt /ls ls pwd bad_outfile.txt
< infile.txt /ls | ls | pwd > bad_outfile.txt

OK mais pb parfois dans laffichage car command not found doit etre print
    avec putstr car pas de code derreur
./pipex infile.txt /ls cshko pwd outfile.txt
< infile.txt /ls | cshko | pwd > outfile.txt

OK
./pipex bad_infile.txt /ls cshko pwd bad_outfile.txt
< bad_infile.txt /ls | cshko | pwd > bad_outfile.txt

OK
./pipex bad_infile.txt /ls cshko pwd outfile.txt
< bad_infile.txt /ls | cshko | pwd > outfile.txt

OK
./pipex infile.txt ./bad_cmd pwd bad_outfile.txt
< infile.txt ./bad_cmd | pwd > bad_outfile.txt

OK
./pipex infile.txt ./bad_cmd pwd outfile.txt
< infile.txt ./bad_cmd | pwd > outfile.txt

OK
./pipex infile.txt bad_cmd pwd outfile.txt
< infile.txt bad_cmd | pwd > outfile.txt

OK
./pipex infile.txt bad_cmd bibi pwd outfile.txt
< infile.txt bad_cmd | bibi | pwd > outfile.txt

OK
./pipex infile.txt ./bad_cmd pwd ls bad_outfile.txt
< infile.txt ./bad_cmd | pwd | ls > bad_outfile.txt