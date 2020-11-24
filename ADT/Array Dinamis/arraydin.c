#include <stdio.h>
#include <stdlib.h>
#include "arraydin.h"

void MakeEmpty(TabInt *T, int maxel)
{
    TI(*T) = (ElType *)malloc((maxel + 1) * sizeof(ElType));
    Neff(*T) = 0;
    MaxEl(*T) = maxel;
}

void Dealokasi(TabInt *T)
{
    free(TI(*T));
    T -> Neff = 0;
    T -> MaxEl = 0;
}
int NbElmt(TabInt T)
{
     return Neff(T);
}
int MaxElement(TabInt T)
{
    return MaxEl(T);
}
IdxType GetFirstIdx(TabInt T)
{
    return IdxMin;
}
IdxType GetLastIdx(TabInt T)
{
    return NbElmt(T) - GetFirstIdx(T) + 1;
}
boolean IsIdxValid(TabInt T, IdxType i)
{
    return ((i >= IdxMin) && (i <= MaxEl(T)));
}
boolean IsIdxEff(TabInt T, IdxType i)
{
    return ((i >= GetFirstIdx(T)) && (i <= GetLastIdx(T)));
}
boolean IsEmpty(TabInt T)
{
    return (Neff(T) == 0);
}
boolean IsFull(TabInt T)
{
    return (Neff(T) == MaxEl(T) - IdxMin + 1);
}
void BacaIsi(TabInt *T)
{
    int N;
    ElType inp;
    do
    {
        scanf("%d", &N);
    } while (!((N >= 0) && (N <= MaxElement(*T))));
    if (N == 0)
    {
        MakeEmpty(T, MaxEl(*T));
    }
    else
    {
        MakeEmpty(T, MaxEl(*T));
        Neff(*T) = N;
        for (IdxType i = GetFirstIdx(*T); i <= GetLastIdx(*T); i++)
        {
            scanf("%d", &inp);
            Elmt(*T, i) = inp;
        }
    }
}
void TulisIsiTab(TabInt T)
{
    if (IsEmpty(T))
    {
        printf("[]");
    }
    else
    {
        printf("[");
        for (IdxType i = GetFirstIdx(T); i < GetLastIdx(T); i++)
        {
            printf("%d,", Elmt(T, i));
        }
        printf("%d]", Elmt(T, GetLastIdx(T)));
    }
}
TabInt PlusMinusTab(TabInt T1, TabInt T2, boolean plus)
{
    TabInt T3;
    MakeEmpty(&T3, MaxEl(T1));
    Neff(T3) = Neff(T1);
    if (plus)
    {
        for (IdxType i = GetFirstIdx(T1); i <= GetLastIdx(T1); i++)
        {
            Elmt(T3, i) = Elmt(T1, i) + Elmt(T2, i);
        }
    }
    else
    {
        for (IdxType i = GetFirstIdx(T1); i <= GetLastIdx(T1); i++)
        {
            Elmt(T3, i) = Elmt(T1, i) - Elmt(T2, i);
        }
    }
    return T3;
}

boolean IsEQ(TabInt T1, TabInt T2)
{
    if (Neff(T1) == Neff(T2))
    {
        for (IdxType i = GetFirstIdx(T1); i <= GetLastIdx(T1); i++)
        {
            if (Elmt(T1, i) != Elmt(T2, i))
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}
IdxType Search1(TabInt T, ElType X)
{
    for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); i++)
    {
        if (Elmt(T, i) == X)
        {
            return i;
        }
    }
    return IdxUndef;
}
boolean SearchB(TabInt T, ElType X)
{
    boolean Found = false;
    IdxType i = GetFirstIdx(T);
    while ((!Found) && (i <= GetLastIdx(T)))
    {
        if (Elmt(T, i) == X)
        {
            Found = true;
        }
        else
        {
            i++;
        }
    }
    return Found;
}
void MaxMin(TabInt T, ElType *Max, ElType *Min)
{
    ElType MaxF = Elmt(T, GetFirstIdx(T));
    ElType MinF = Elmt(T, GetFirstIdx(T));
    for (IdxType i = GetFirstIdx(T) + 1; i <= GetLastIdx(T); i++)
    {
        if (Elmt(T, i) > MaxF)
        {
            MaxF = Elmt(T, i);
        }
        if (Elmt(T, i) < MinF)
        {
            MinF = Elmt(T, i);
        }
    }
    *Max = MaxF;
    *Min = MinF;
}
void CopyTab(TabInt Tin, TabInt *Tout)
{
    TabInt ToutT;
    MakeEmpty(&ToutT, MaxElement(Tin));
    Neff(ToutT) = Neff(Tin);
    for (IdxType i = GetFirstIdx(Tin); i <= GetLastIdx(Tin); i++)
    {
        Elmt(ToutT, i) = Elmt(Tin, i);
    }
    *Tout = ToutT;
}
ElType SumTab(TabInt T)
{
   ElType sumT = 0;
    if (IsEmpty(T))
    {
        return 0;
    }
    else
    {
        for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); i++)
        {
            sumT += Elmt(T, i);
        }
    }
    return sumT;
}
int CountX(TabInt T, ElType X)
{
    int count = 0;
    if (IsEmpty(T))
    {
        return 0;
    }
    else
    {
        for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); i++)
        {
            if (Elmt(T, i) == X)
            {
                count++;
            }
        }
    }
    return count;
}
boolean IsAllGenap(TabInt T)
{
    if (IsEmpty(T))
    {
        return false;
    }
    else
    {
        for (IdxType i = GetFirstIdx(T); i <= GetLastIdx(T); i++)
        {
            if ((Elmt(T, i) % 2) != 0)
            {
                return false;
            }
        }
        //
        return true;
    }
}
void Sort(TabInt *T, boolean asc)
{
    if (asc)
    {
        ElType key;
        IdxType j;
        for (IdxType i = GetFirstIdx(*T) + 1; i <= GetLastIdx(*T); i++)
        {
            key = Elmt(*T, i);
            j = i - 1;
            while ((j >= GetFirstIdx(*T)) && (Elmt(*T, j) > key))
            {
                Elmt(*T, j + 1) = Elmt(*T, j);
                j--;
            }
            Elmt(*T, j + 1) = key;
        }
    }
    else
    {
        IdxType iMax;
        ElType tmp;
        for (IdxType i = GetFirstIdx(*T); i < GetLastIdx(*T); i++)
        {
            iMax = i;
            //
            for (IdxType j = i + 1; j <= GetLastIdx(*T); j++)
            {
                if (Elmt(*T, j) > Elmt(*T, iMax))
                {
                    iMax = j;
                }
            }
            //
            tmp = Elmt(*T, iMax);
            Elmt(*T, iMax) = Elmt(*T, i);
            Elmt(*T, i) = tmp;
        }
    }
}
void AddAsLastEl(TabInt *T, ElType X)
{
    Neff(*T)++;
    Elmt(*T, GetLastIdx(*T)) = X;
}
void DelLastEl(TabInt *T, ElType *X)
{
    *X = Elmt(*T, GetLastIdx(*T));
    Neff(*T)--;
}

void GrowTab(TabInt *T, int num)
{
    TabInt Tc, Td;
    CopyTab(*T, &Tc);
    Dealokasi(T);
    MakeEmpty(T, MaxElement(Tc) + num);
    MakeEmpty(&Td, MaxElement(Tc) + num);
    for (IdxType i = GetFirstIdx(Tc); i <= (GetLastIdx(Tc)); i++)
    {
        Elmt(Td, i) = Elmt(Tc, i);
    }
    Neff(Td) = Neff(Tc);
    *T = Td;
}
void ShrinkTab(TabInt *T, int num)
{
    TabInt Tc, Td;
    CopyTab(*T, &Tc);
    Dealokasi(T);
    MakeEmpty(T, MaxElement(Tc) - num);
    MakeEmpty(&Td, MaxElement(Tc) - num);
    for (IdxType i = GetFirstIdx(Tc); i <= (GetLastIdx(Tc)); i++)
    {
        Elmt(Td, i) = Elmt(Tc, i);
    }
    Neff(Td) = Neff(Tc);
    if (MaxEl(Td) < Neff(Td))
    {
        Neff(Td) = MaxEl(Td);
    }
    *T = Td;
}
void CompactTab(TabInt *T)
{
    MaxEl(*T) = Neff(*T);
}