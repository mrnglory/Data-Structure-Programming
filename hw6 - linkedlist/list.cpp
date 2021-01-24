#include <iostream>
#include "list.h"

ostream& operator << (ostream& os, IntList& il)
{
    Node *ptr = il.first;

    while (ptr != NULL)
    {
        os << ptr -> data << " ";
        ptr = ptr -> link;
    }

    os << endl;

    return os;
}

void IntList::Push_Back(int e)
{
    if (!first)
        first = last = new Node(e);

    else
    {
        last -> link = new Node(e);
        last = last -> link;
    }
}

void IntList::Push_Front(int e)
{
    Node * newbie = new Node(e);
    newbie -> link = NULL;

    if (!first)
    {
        first = newbie;
        last = newbie;
    }

    else
    {
        newbie -> link = first;
        first = newbie;
    }
}



void IntList::Insert(int e)
{
    // Push_Front, Push_Back 사용할 것, 중복허용 안함
    if (!first)
    {
        // 빈 리스트인 경우
        Push_Front(e);
    }

    else if (first -> data > e)
    {
        // 리스트 맨 앞에 추가
        Push_Front(e);
    }

    else if (first -> data != e)
    {
        Node * a = first -> link;
        Node * b = first;

        while (a != NULL)
        {
            if (e > (a -> data))
            {
                b = a;
                a = a -> link;
            }

            else if (e < a -> data)
            {
                Node * newbie = new Node(e);
                newbie -> link = NULL;

                newbie -> link = b -> link;
                b -> link = newbie;

                break;
            }

            else if (e == a -> data)
            {
                break;
            }
        }

        if (a == NULL)
        {
            Push_Back(e);
        }
    }
}

void IntList::Delete(int e)
{
    if (first -> data == e)
    {
        // 첫 번째 데이터를 삭제할 경우
        Node * del_ptr = first;
        first = first -> link;
        delete del_ptr;
    }

    else
    {
        Node * a = first -> link;
        Node * b = first;

        while (a != NULL)
        {
            if (e == a -> data)
            {
                b -> link = a -> link;
                delete a;
                a = b;

                break;
            }

            b = a;
            a = a -> link;
        }

        if (a == NULL)
        {
            last = b;
        }
    }
}