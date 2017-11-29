//By Craciun Cristian-George
//Project: Walk in the minefield
//Version 1.0
//Overview: README.txt


#include "lib.h"
#include "ft.cpp"

using namespace std;

int main()
{
    ifstream fin("mine.txt");
    ifstream fcmd("commands.txt");
    ofstream fout("mine.out");

    solve(fout, fcmd, fin);

    //getch();
    return 0;
}
