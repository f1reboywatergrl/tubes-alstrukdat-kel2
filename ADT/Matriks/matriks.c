#include "matriks.h"
#include <stdio.h>


void MakeMATRIKS (int NB, int NK, MATRIKS * M) 
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
{
    NBrsEff(*M)=NB;
    NKolEff(*M)=NK;
}

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j)
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
{
    return ((i>=BrsMin && i<=BrsMax) && (j>=BrsMin && j<=BrsMax));
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terkecil M */
{
    return BrsMin;
}
indeks GetFirstIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terkecil M */
{
    return KolMin;
}
indeks GetLastIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terbesar M */
{
    return BrsMax;
}
indeks GetLastIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terbesar M */
{
    return KolMax;
}
boolean IsIdxEff (MATRIKS M, indeks i, indeks j)
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
{
    return ((i<=NBrsEff(M) && j<=NKolEff(M)));
}
ElTypeMatriks GetElmtDiagonal (MATRIKS M, indeks i)
/* Mengirimkan elemen M(i,i) */
{
    return (ElmtMatrix(M,i,i));
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl)
/* Melakukan assignment MHsl  MIn */
{
    indeks TempI, TempJ;
    for(TempI=BrsMin;TempI<NBrsEff(MIn);TempI++){
        for(TempJ=KolMin;TempJ<NKolEff(MIn);TempJ++){
            ElmtMatrix(MIn,TempI,TempJ)=ElmtMatrix(*MHsl,TempI,TempJ);
        }
    }
    NBrsEff(MIn)=NBrsEff(*MHsl);
    NKolEff(MIn)=NKolEff(*MHsl);
}
/* ********** KELOMPOK BACA/TULIS ********** */ 
void BacaMATRIKS (MATRIKS * M, int NB, int NK)
/* I.S. IsIdxValid(NB,NK) */ 
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
{
    indeks i,j;
    MakeMATRIKS(NB,NK,M);
    NBrsEff(*M)=NB;
    NKolEff(*M)=NK;
    for(i=BrsMin;i<NB;i++){
        for(j=KolMin;j<NK;j++){
            int temp;
            if(j==NK-1){ //Kolom Terakhir, No space
                scanf("%d",&temp);
            }
            else{
                scanf("%d ",&temp); // Contoh -> %d %d %d
            }
            ElmtMatrix((*M),i,j)=temp;
        }
    }
}
void TulisMATRIKS (MATRIKS M)
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
    indeks i,j;
    for(i=BrsMin;i<NBrsEff(M);i++){
        for(j=KolMin;j<NKolEff(M);j++){
            if(j==NKolEff(M)-1){
                printf("%d",ElmtMatrix(M,i,j)); //No Space di akhir baris
            }
            else{
                printf("%d ",ElmtMatrix(M,i,j)); 
            }
        }
        if(i!=NBrsEff(M)-1){
            printf("\n"); //No Newline di akhir prog
        }
    }
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQMatriks (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 = M2, yaitu NBElmtMatrix(M1) = NBElmtMatrix(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQMatriks karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2) 
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
{
    boolean cek=false;
    indeks i=BrsMin;
    if(NBElmt(M1)==NBElmt(M2)){
        cek=true;
        while(cek && i<NBrsEff(M1)){
            indeks j=KolMin;
            while(cek && j<NKolEff(M1)){
                if(ElmtMatrix(M1,i,j)!=ElmtMatrix(M1,i,j)){
                    cek=false;
                }
                j++;               
            }
            i++;
        }
    }
    return cek;
}
boolean NEQMatriks (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 tidak sama dengan M2 */
{
    return (!EQMatriks(M1,M2));
}
boolean EQMatriksSize (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */
{
    return (NBrsEff(M1)==NBrsEff(M2) && NKolEff(M1)==NKolEff(M2));
}

/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M)
/* Mengirimkan banyaknya elemen M */
{
    return (NBrsEff(M)*NKolEff(M));
}
/* ********** KELOMPOK TEST TERHADAP MATRIKS ********** */

//Kemungkinan Primitif Tambahan Kepentingan Tubes

void EmptyMatrix (MATRIKS *M)
/* Mengosongkan Matriks peta, semua titik diisi dengan -3 */
{
    indeks i,j;
    for(i=BrsMin;i<NBrsEff(*M);i++){
        for(j=KolMin;j<NKolEff(*M);j++){
            ElmtMatrix((*M),i,j) = -3;
        }
    }
}

void IsiPoint (MATRIKS *M, POINT PointInput)
/* Mengisi Point baru letak customer */
{
    indeks i=Absis(PointInput);
    indeks j=Ordinat(PointInput);
    int custFileOrder = CustFileOrder(PointInput);
    char type = Type(PointInput);
    if (type=='S'){
        ElmtMatrix(*M,i,j) = 0;
    }
    else if (type == 'B'){
        ElmtMatrix(*M,i,j) = -1;
    }
    else if (type == 'C'){
        ElmtMatrix(*M,i,j) = custFileOrder;
    }
}
void PrintMap (MATRIKS M)
/* Mencetak Peta berikut koordinatnya yang sudah diisi */
{
    indeks i,j;
    for(i=BrsMin;i<NBrsEff(M);i++){
        for(j=KolMin;j<NKolEff(M);j++){
            if(i==BrsMin || i==NBrsEff(M)-1 || j==KolMin || j==NKolEff(M)-1){
                printf("*");
            }
            else if (i==CurrentAbsis(M) && j==CurrentOrdinat(M)){
                printf("P");
            }
            else if(ElmtMatrix(M,i,j)>0){
                printf("%d",ElmtMatrix(M,i,j));  
            }
            else if(ElmtMatrix(M,i,j)==0){
                printf("S");
            }
            else if(ElmtMatrix(M,i,j)==-1){
                printf("B");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Your position is marked by 'P'.\n");
    printf("B: Your base, S: The shop\n");
}
POINT SearchMatrix (MATRIKS M, int X)
/* Mencari letak X pada matriks M */
{
    POINT P;
    CustFileOrder(P)=-999;
    Type(P)='X';
    for (int i=BrsMin;i<NBrsEff(M);i++){
        for (int j=KolMin;j<NKolEff(M);j++){
            if (ElmtMatrix(M,i,j)==X){
                Absis(P)=i;
                Ordinat(P)=j;
                return P;
            }
        }
    }
}
void GenerateStaticAdjacency(MATRIKS *GraphMatrix){
    ElmtMatrix(*GraphMatrix,3,0)=1;
    ElmtMatrix(*GraphMatrix,0,3)=1;
    ElmtMatrix(*GraphMatrix,0,6)=1;
    ElmtMatrix(*GraphMatrix,6,0)=1;
    ElmtMatrix(*GraphMatrix,1,3)=1;
    ElmtMatrix(*GraphMatrix,3,1)=1;
    ElmtMatrix(*GraphMatrix,1,4)=1;
    ElmtMatrix(*GraphMatrix,4,1)=1;
    ElmtMatrix(*GraphMatrix,2,5)=1;
    ElmtMatrix(*GraphMatrix,5,2)=1;
    ElmtMatrix(*GraphMatrix,1,7)=1;
    ElmtMatrix(*GraphMatrix,7,1)=1;
    ElmtMatrix(*GraphMatrix,1,8)=1;
    ElmtMatrix(*GraphMatrix,8,1)=1;
    ElmtMatrix(*GraphMatrix,1,2)=1;
    ElmtMatrix(*GraphMatrix,2,1)=1;
    ElmtMatrix(*GraphMatrix,2,4)=1;
    ElmtMatrix(*GraphMatrix,4,2)=1;
    ElmtMatrix(*GraphMatrix,7,4)=1;
    ElmtMatrix(*GraphMatrix,4,7)=1;
    ElmtMatrix(*GraphMatrix,7,5)=1;
    ElmtMatrix(*GraphMatrix,5,7)=1;
    ElmtMatrix(*GraphMatrix,6,8)=1;
    ElmtMatrix(*GraphMatrix,8,6)=1;

    /* Tambahan buat debug */
    ElmtMatrix(*GraphMatrix,4,5)=1;
    ElmtMatrix(*GraphMatrix,5,4)=1;
    ElmtMatrix(*GraphMatrix,6,9)=1;
    ElmtMatrix(*GraphMatrix,9,6)=1;    
}

void MakeZeroMatrix (MATRIKS *M,int NB, int NK)
/* Membuat matrix berisi 0 semua dengan NBrsEff=NB, NKolEff=NK */
{
    MakeMATRIKS(NB,NK,M);
    for(int i=0;i<NBrsEff(*M);i++){
        for(int j=0;j<NKolEff(*M);j++){
            ElmtMatrix(*M,i,j)=0;
        }
    }
}