                    }
                    
                }
            }
            

            /* COMMAND 8 : SHOP */
            else if(strcmp(InputCommand,"SHOP")==0){
                if(CurrentPos(MapMatrix)==0){
                    int NoKomponen, JumlahKomponen, HitungTotal;
                    printf("Komponen yang tersedia:\n");
                    PrintStore(ListDummy);
                    printf("Komponen yang ingin dibeli: ");
                    scanf("%d",(&NoKomponen));
                    printf("Masukkan jumlah yang ingin dibeli: ");
                    scanf("%d",(&JumlahKomponen));
                    HitungTotal = (Harga(ListElmt(ListDummy,NoKomponen-1))*JumlahKomponen);
                    if (HitungTotal > UangPemain){
                        printf("Uang tidak cukup!\n");
                    }
             