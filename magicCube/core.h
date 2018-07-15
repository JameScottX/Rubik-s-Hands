#ifndef CORE_H
#define CORE_H

#include<QString>
#include <stdio.h>
#include <string.h>

extern int TEMP;

#define SWAP(a,b) TEMP=a;a=b;b=TEMP;
#define CHAROFFSET 65

class core
{
public:

    core();
    QString core_caculate(std::string get[]);

private:

    char *temp_corn = new char();
    char *faces = new char();
    char *order = new char();
    char *bithash = new char();
    char *perm = new char();

    void table_Init();

    void cycle(char*p, char*a);
    void twist(int i, int a);
    int permtonum(char* p);
    void numtoperm(char* p, int n, int o);

    void reset();
    int getposition(int t);
    void setposition(int t, int n);
    void domove(int m);
    void filltable(int ti);
    bool searchphase(int movesleft, int movesdone, int lastmove);
    int myfind(char a);
};


#endif // CORE_H
