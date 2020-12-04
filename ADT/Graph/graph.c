#include "graph.h"
#include "stdio.h"


void CreateEmptyGraph(Graph *G)
/* I.S. sembarang             */
/* F.S. Terbentuk graph kosong */
{
    First(*G)=Nil;
}

boolean IsGraphEmpty(Graph G)
/* Mengirimkan true jika graph kosong */
{
    return (First(G)==Nil);
}

addressGraph AlokasiGraph(infotypeGraph X)
/* Mengirimkan addressGraph hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressGraph tidak nil, dan misalnya */
/* menghasilkan P, maka InfoGraph(P)=X, NextGraph(P)=NULL, dan Link(P) berisi list kosong */
/* Jika alokasi gagal, mengirimkan NULL */
{
    addressGraph P;
    P = (addressGraph)malloc(sizeof(ElmtGraph));
    if(P!=Nil){
        InfoGraph(P)=X;
        NextGraph(P)=Nil;
        CreateEmpty(&Link(P));
    }
    return P;
}

void initGraph(Graph *G, int n)
/* I. S. Graph G sembarang, n adalah jumlah titik elemen list
   F. S. Terbentuk Graph n elemen dan link tiap elemen berupa empty list */
{
    addressGraph P;
    CreateEmptyGraph(G);
    FirstGraph(*G) = AlokasiGraph(-1);
    P=FirstGraph(*G);
    for (int C=0;C<n;C++){
        NextGraph(P)=AlokasiGraph(C);
        P=NextGraph(P);
    }
    //Hubungin graph ke semua titik n, isi awal empty semua
}
void PrintGraph(Graph G)
/* I.S. Graph mungkin kosong */
/* F.S. Jika Graph tidak kosong, isi info Graph dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika Graph kosong : menulis [] */
{
    printf("[");
    if(!IsGraphEmpty(G)){
        addressGraph P=FirstGraph(G);
        printf("%d",InfoGraph(P));
        P=NextGraph(P);
        while(P!=Nil){
            printf(",%d",InfoGraph(P));
            P=NextGraph(P);
        }
    }
    printf("]\n");
}


void AddLink(Graph *G, infotypeGraph n, infotypeGraph p)
/* I. S. Graph G terdefinisi, n dan p pasti tidak lebih dari jumlah titik
   F. S. Link dari elemen n bertambah dengan p, dan sebaliknya (soalnya bolak balik)
*/
{
    addressGraph Adrn, Adrp;

    //Cari dulu n dimana
    Adrn = FirstGraph(*G);
    while(InfoGraph(Adrn)!=n){
        Adrn = NextGraph(Adrn);
    }
    if (Search(Link(Adrn),p)==Nil){ //ketika udah sampe di list yg seharusnya, search link ke p
        InsVLast(&Link(Adrn),p); //tambain p ke link n
    }

    //sekarang lakuin yg sama ke p karena bolak balik
    Adrp = FirstGraph(*G);
    while (InfoGraph(Adrp)!=p){
        Adrp=NextGraph(Adrp);
    }
    if (Search(Link(Adrp),n)==Nil){
        InsVLast(&Link(Adrp),n);
    }
    //Add element to list of links
}
void PrintLink(Graph G, infotypeGraph X)
/* Print X berkait ke mana aja */
{
    addressGraph P;
    ListLinier L;
    P=FirstGraph(G);
    while (InfoGraph(P)!=X){
        P=NextGraph(P);
    }
    //Found X,
    L=Link(P);
    PrintInfo(L);
}

boolean IsLinked(Graph G, infotypeGraph n, infotypeGraph p)
/* Mengembalikan true jika pada link n ada p */
{
    addressGraph Adrn;
    boolean cek=false;
    //cari n nya dulu pada graph
    Adrn = FirstGraph(G);
    while (InfoGraph(Adrn) != n){
        Adrn = NextGraph(Adrn);
    }

    //Pencarian pada daftar link n
    if (Search(Link(Adrn),p)!=Nil){
        cek=true;
    }
    return cek;
}

addressGraph SearchGraph(Graph G, infotypeGraph X)
{
    addressGraph P=FirstGraph(G);
    while (InfoGraph(P)!=X && NextGraph(P)!=Nil){
        P=NextGraph(P);
    }
    if(InfoGraph(P)!=X){
        P=Nil;
    }
    return P;
}
void Move(Graph G, int CurrentPos, int TargetPos, MATRIKS *M)
/* Memindahkan posisi pemain apabila target pemindahan valid */
{
    if (IsLinked(G, CurrentPos,TargetPos)){
        POINT P = SearchMatrix(*M,TargetPos);
        CurrentAbsis(*M)=Absis(P);
        CurrentOrdinat(*M)=Ordinat(P);
    }
    else{
        printf("That area is not accessible.\n");
    }
}

void ShowValidTargets (Graph G, int CurrentPos)
/* Menampilkan list titik-titik yang terhubung dengan posisi pemain saat ini */
{
    printf("Move to... \n");
    printf("\033[0;33m");
    printf("You are currently at ");
    printf("\033[0;32m");
    switch (CurrentPos){
        case -1:
        printf("Base\n");break;

        case 0:
        printf("Shop\n");break;

        default:
        printf("Customer %d\n",CurrentPos);
    }
    printf("\033[0;37m");
    printf("0. Cancel\n");
    int C=1;
    address P;
    addressGraph PGraph;
    //Cari dulu titiknya
    PGraph=FirstGraph(G);
    while(InfoGraph(PGraph)!=CurrentPos){
        PGraph=NextGraph(PGraph);
    }
    P=First(Link(PGraph));
    while (P!=Nil){
        printf("%d. ",C);
        switch(InfoLinier(P)){
            case -1:
            printf("Base\n");break;

            case 0:
            printf("Shop\n");break;

            default:
            printf("Customer %d\n",InfoLinier(P));
        }
        P=NextGraph(P);
        C++;
    }
}

void SaveLinks (MATRIKS GraphMatrix, Graph *G)
/* Membaca Adjacency Matrix dan menambahkan link-linknya pada Graph */
{
    for (int i=BrsMin;i<NBrsEff(GraphMatrix);i++){
        for (int j=KolMin;j<NKolEff(GraphMatrix);j++){
            if (ElmtMatrix(GraphMatrix,i,j)==1){
                AddLink(G,i-1,j-1);
            }
        }
    }
}
