#include "LIST.h"

Tlist LIST::getbegin()
{
    return begin;
}

Tlist LIST::getend()
{
    return end;
}

LIST::LIST(cord *x)
{
    Tlist Q = new Node;
    Q->info = x;
    Q->next = NULL;
    Q->prev = NULL;
    begin = Q;
    end = Q;
}

void LIST::AddAft(Tlist Q, cord *x)
{
    Tlist R = new Node;
    R->info = x;
    if (Q)
        R->next = Q->next;
    else
    {
        R->next = begin;
        begin = R;
    }
    R->prev = Q;
    if (R->next)
        R->next->prev = R;
    else
        end = R;
    if (R->prev)
        R->prev->next = R;
}

void LIST::Delete(Tlist Q)
{
    if (Q->next)
        Q->next->prev = Q->prev;
    else
        end = Q->prev;
    if (Q->prev)
        Q->prev->next = Q->next;
    else
        begin = Q->next;
    Q->next = Q->prev = NULL;
    delete Q->info;
    delete Q;
}

void LIST::Print()
{
    Tlist Q = begin;
    while (Q)
    {
        Q->info->Print();
        Q = Q->next;
    }
}

LIST::~LIST()
{
    while(begin)
        Delete(begin);
}
