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
ElType GetElmtDiagonal (MATRIKS M, indeks i)
/* Mengirimkan elemen M(i,i) */
{
    return (Elmt(M,i,i));
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl)
/* Melakukan assignment MHsl  MIn */
{
    indeks TempI, TempJ;
    for(TempI=BrsMin;TempI<NBrsEff(MIn);TempI++){
        for(TempJ=KolMin;TempJ<NKolEff(MIn);TempJ++){
            Elmt(MIn,TempI,TempJ)=Elmt(*MHsl,TempI,TempJ);
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
            Elmt((*M),i,j)=temp;
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
                printf("%d",Elmt(M,i,j)); //No Space di akhir baris
            }
            else{
                printf("%d ",Elmt(M,i,j)); 
            }
        }
        if(i!=NBrsEff(M)-1){
            printf("\n"); //No Newline di akhir prog
        }
    }
}
/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */                                  
MATRIKS TambahMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : M1  berukuran sama dengan M2 */
/* Mengirim hasil penjumlahan matriks: M1 + M2 */
{
    MATRIKS M;
    NBrsEff(M)=NBrsEff(M1);
    NKolEff(M)=NKolEff(M1);
    CopyMATRIKS(M1,&M);
    indeks i,j;
    for(i=BrsMin;i<NBrsEff(M);i++){
        for(j=KolMin;j<NKolEff(M);j++){
            Elmt(M,i,j) += Elmt(M2,i,j);
        }
    }
    return M;
} 
MATRIKS KurangMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : M berukuran sama dengan M */
/* Mengirim hasil pengurangan matriks: salinan M1 – M2 */
{
    MATRIKS M;
    NBrsEff(M)=NBrsEff(M1);
    NKolEff(M)=NKolEff(M1);
    CopyMATRIKS(M1,&M);
    indeks i,j;
    for(i=BrsMin;i<NBrsEff(M);i++){
        for(j=KolMin;j<NKolEff(M);j++){
            Elmt(M,i,j) -= Elmt(M2,i,j);
        }
    }
    return M;        
} 
MATRIKS KaliMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : Ukuran kolom efektif M1 = ukuran baris efektif M2 */
/* Mengirim hasil perkalian matriks: salinan M1 * M2 */
{
    /*  Konsep Perkalian Matriks:
        Untuk setiap baris M1, dikali dengan setiap kolom M2
        Hasil perkalian matriks : Brs(M2), Kol(M1)
    */
    MATRIKS M;
    MakeMATRIKS(NBrsEff(M2),NKolEff(M1),&M);
    indeks i,j,k;
    for(i=BrsMin;i<NBrsEff(M);i++){
        for(j=KolMin;j<NKolEff(M);j++){
            int sum=0;
            for(k=KolMin;k<NKolEff(M);k++){
                sum += Elmt(M1,i,k) * Elmt(M2,k,j);
            }
            Elmt(M,i,j) = sum;
        }
    }
    return M;      
}
MATRIKS KaliKons (MATRIKS M, ElType X)
/* Mengirim hasil perkalian setiap elemen M dengan X */
{
    MATRIKS M1;
    NBrsEff(M1)=NBrsEff(M);
    NKolEff(M1)=NKolEff(M);
    CopyMATRIKS(M,&M1);
    indeks i,j;
    for(i=BrsMin;i<NBrsEff(M1);i++){
        for(j=KolMin;j<NKolEff(M1);j++){
            Elmt(M1,i,j) = Elmt(M1,i,j) * X;
        }
    }
    return M1;  
}
void PKaliKons (MATRIKS * M, ElType K)
/* I.S. M terdefinisi, K terdefinisi */
/* F.S. Mengalikan setiap elemen M dengan K */
{
    indeks i,j;
    for(i=BrsMin;i<NBrsEff(*M);i++){
        for(j=KolMin;j<NKolEff(*M);j++){
            Elmt(*M,i,j) = Elmt(*M,i,j) * K;
        }
    }    
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQ (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 = M2, yaitu NBElmt(M1) = NBElmt(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQ karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2) 
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
{
    boolean cek=false;
    indeks i=BrsMin;
    if(NBElmt(M1)==NBElmt(M2)){
        cek=true;
        while(cek && i<NBrsEff(M1)){
            indeks j=KolMin;
            while(cek && j<NKolEff(M1)){
                if(Elmt(M1,i,j)!=Elmt(M1,i,j)){
                    cek=false;
                }
                j++;               
            }
            i++;
        }
    }
    return cek;
}
boolean NEQ (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 tidak sama dengan M2 */
{
    return (!EQ(M1,M2));
}
boolean EQSize (MATRIKS M1, MATRIKS M2)
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
boolean IsBujurSangkar (MATRIKS M)
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
{
    return (NBrsEff(M)==NKolEff(M));
}
boolean IsSimetri (MATRIKS M)
/* Mengirimkan true jika M adalah matriks simetri : IsBujurSangkar(M) 
   dan untuk setiap elemen M, M(i,j)=M(j,i) */
{
    boolean cek=false;
    if(IsBujurSangkar(M)){
        cek=true;
        indeks i=BrsMin,j;
        while(cek && i<NBrsEff(M)){
            j=KolMin;
            while(cek && j<NBrsEff(M)){
                if(Elmt(M,i,j)!=Elmt(M,j,i)){
                    cek=false;
                }
                j++;
            }
            i++;
        }
    }
    return cek;
}
boolean IsSatuan (MATRIKS M)
/* Mengirimkan true jika M adalah matriks satuan: IsBujurSangkar(M) dan 
   setiap elemen diagonal M bernilai 1 dan elemen yang bukan diagonal bernilai 0 */ 
{
    boolean cek=false;
    if(IsBujurSangkar(M)){
        cek=true;
        indeks i=BrsMin;
        while(cek && i<NBrsEff(M)){
            if(GetElmtDiagonal(M,i)!=1){
                cek=false;
            }            
            indeks j=KolMin;
            while(cek && j<NKolEff(M)){
                if(Elmt(M,i,j)!=GetElmtDiagonal(M,i) && Elmt(M,i,j)!=0){
                    cek=false;
                }
                j++;
            }
            i++;
        }
    }
    return cek;
}
boolean IsSparse (MATRIKS M)
/* Mengirimkan true jika M adalah matriks sparse: mariks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */ 
{
    float threshold = 5*NBElmt(M)/100;
    int count = 0;
    boolean cek = true;
    indeks i = 0;
    indeks j;
    while(cek && i<NBrsEff(M)){
        j = 0;
        while(cek && j<NKolEff(M)){
            if(Elmt(M,i,j)!=0){
                count ++;
            }
            if(count>threshold){
                cek = false;
            }
            j++;
        }
        i++;
    }
    return cek;
}
MATRIKS Inverse1 (MATRIKS M)
/* Menghasilkan salinan M dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
{
    MATRIKS M1;
    MakeMATRIKS(NBrsEff(M),NKolEff(M),&M1);
    CopyMATRIKS(M,&M1); 
    KaliKons(M1,-1);
    return M1;
}
float Determinan (MATRIKS M)
/* Prekondisi: IsBujurSangkar(M) */
/* Menghitung nilai determinan M */
{
    indeks i,j,k;
    float ratio,det;
    float matriks[NBrsEff(M)][NKolEff(M)];
    for(i=0;i<NBrsEff(M);i++){
        for(j=0;j<NKolEff(M);j++){
            matriks[i][j] = Elmt(M,i,j);
        }
    }
    for(i=0;i<NBrsEff(M);i++){
        for(j=0;j<NKolEff(M);j++){
            if(j>i){
                ratio = matriks[j][i]/matriks[i][i];
                for(k=0;k<NBrsEff(M);k++){
                    matriks[j][k] -= ratio * matriks[i][k];
                }
            }
        }
    }
    det = matriks[0][0];
    for(i=1; i<NBrsEff(M);i++)
        det *= matriks[i][i];
    int d = (int)det;    
    return (float)d;
}
void PInverse1 (MATRIKS * M)
/* I.S. M terdefinisi */
/* F.S. M di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
{
    PKaliKons(M,-1);
}
void Transpose (MATRIKS * M)
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */
{
    //Bujur Sangkar
    MATRIKS temp;
    MakeMATRIKS(NBrsEff(*M),NKolEff(*M),&temp);
    CopyMATRIKS(*M,&temp);
    indeks i,j;
    for(i=BrsMin;i<NBrsEff(*M);i++){
        for(j=KolMin;j<NKolEff(*M);j++){
            Elmt(*M,i,j) = Elmt(temp,j,i);
        }
    }
}
/* Operasi berbasis baris dan per kolom */
float RataBrs (MATRIKS M, indeks i)
/* Menghasilkan rata-rata dari elemen pada baris ke-i */
/* Prekondisi: i adalah indeks baris efektif dari M */
{
    float sum=0;
    for(indeks j=KolMin;j<NKolEff(M);j++){
        sum += Elmt(M,i,j);
    }
    return sum/NKolEff(M);
}
float RataKol (MATRIKS M, indeks j)
/* Menghasilkan rata-rata dari elemen pada kolom ke-j */
/* Prekondisi: j adalah indeks kolom efektif dari M */
{
    float sum=0;
    for(indeks i=BrsMin;i<NBrsEff(M);i++){
        sum += Elmt(M,i,j);
    }
    return sum/NBrsEff(M);    
}
void MaxMinBrs (MATRIKS M, indeks i, ElType * max, ElType * min)
/* I.S. i adalah indeks baris efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada baris i dari M
           min berisi elemen minimum pada baris i dari M */
{
    ElType maksimum = Elmt(M,i,0);
    ElType minimum = Elmt(M,i,0);
    indeks j;
    for(j=1;j<NKolEff(M);j++){
        if(Elmt(M,i,j)>maksimum){
            maksimum = Elmt(M,i,j);
        }
        if(Elmt(M,i,j)<minimum){
            minimum = Elmt(M,i,j);
        }
    }
    *max = maksimum;
    *min = minimum;
}
void MaxMinKol (MATRIKS M, indeks j, ElType * max, ElType * min)
/* I.S. j adalah indeks kolom efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada kolom j dari M
           min berisi elemen minimum pada kolom j dari M */
{
    ElType maksimum = Elmt(M,0,j);
    ElType minimum = Elmt(M,0,j);
    indeks i;
    for(i=1;i<NBrsEff(M);i++){
        if(Elmt(M,i,j)>maksimum){
            maksimum = Elmt(M,i,j);
        }
        if(Elmt(M,i,j)<minimum){
            minimum = Elmt(M,i,j);
        }
    }
    *max = maksimum;
    *min = minimum;
}
int CountXBrs (MATRIKS M, indeks i, ElType X)
/* Menghasilkan banyaknya kemunculan X pada baris i dari M */
{
    int count = 0;
    indeks j;
    for(j=0;j<NKolEff(M);j++){
        if(Elmt(M,i,j)==X){
            count++;
        }
    }
    return count;    

}
int CountXKol (MATRIKS M, indeks j, ElType X)
/* Menghasilkan banyaknya kemunculan X pada kolom j dari M */
{
    int count = 0;
    indeks i;
    for(i=0;i<NKolEff(M);i++){
        if(Elmt(M,i,j)==X){
            count++;
        }
    }
    return count;
}


//Kemungkinan Primitif Tambahan Kepentingan Tubes

void ZeroMatrix (MATRIKS *M)
/* Mengisi semua nilai matriks dengan 0 */
{
    indeks i,j;
    for(i=BrsMin;i<BrsMax;i++){
        for(j=KolMin;j<KolMax;j++){
            Elmt(*M,i,j) = 0;
        }
    }
}

void IsiPoint (MATRIKS *M, indeks i, indeks j, char *Type, int *CustFileOrder)
/* Mengisi Point baru letak customer */
{
    if (Type=="S"){
        Elmt(*M,i,j) = -1;
    }
    else if (Type == "B"){
        Elmt(*M,i,j) = -2;
    }
    else if (Type == "C"){
        Elmt(*M,i,j) = *CustFileOrder;
        *CustFileOrder = *CustFileOrder+1;
    }
}
void PrintMap (MATRIKS M)
/* Mencetak Peta berikut koordinatnya yang sudah diisi */
{
    indeks i,j;
    for(i=BrsMin;i<BrsMax;i++){
        for(j=KolMin;j<KolMax;j++){
            if(i==BrsMin || i==BrsMax-1 || j==KolMin || j==KolMax-1){
                printf("*");
            }
            else if (i==CurrentAbsis(M) && j==CurrentOrdinat(M)){
                printf("P");
            }
            else if(Elmt(M,i,j)>0){
                printf("%d",Elmt(M,i,j));
            }
            else if(Elmt(M,i,j)==-1){
                printf("S");
            }
            else if(Elmt(M,i,j)==-2){
                printf("B");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
}