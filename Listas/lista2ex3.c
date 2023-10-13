#include<stdio.h>
typedef struct{
       float num;
       int pos;
}Registro;

//void gravar(Regitro registro, File *file){


int main(){
    Registro reg;
    int pos;

    FILE *arquivo;

    arquivo = fopen("Arquivo.bin","wb");
    if(!arquivo){
       printf("Erro ao abrir arquivo");
       exit(1);
    }


    reg.num = 3.3;
    reg.pos = 6;
    fwrite(&reg,sizeof(Registro),1,arquivo);

    reg.num = 2.6;
    reg.pos = -1;
    fwrite(&reg,sizeof(Registro),1,arquivo);

    reg.num = 7.4;
    reg.pos = 5;
    fwrite(&reg,sizeof(Registro),1,arquivo);

    reg.num = 21.3;
    reg.pos = 2;
    fwrite(&reg,sizeof(Registro),1,arquivo);

    reg.num = 1.11;
    reg.pos = 1;
    fwrite(&reg,sizeof(Registro),1,arquivo);

    reg.num = 90.5;
    reg.pos = 7;
    fwrite(&reg,sizeof(Registro),1,arquivo);

    reg.num = 5.8;
    reg.pos = 4;
    fwrite(&reg,sizeof(Registro),1,arquivo);

    reg.num = 5.4;
    reg.pos = 3;
    fwrite(&reg,sizeof(Registro),1,arquivo);

    fclose(arquivo);

/************************* ler ****************************/

    arquivo = fopen("Arquivo.bin","rb");

    //fseek(arquivo,sizeof(Registro)*(-1),SEEK_END);

    reg.pos=8;
    do{
        fseek(arquivo,sizeof(Registro)*(reg.pos-1),SEEK_SET);
        fread(&reg,sizeof(Registro),1,arquivo);
        printf("\n Dado lido: %f \n",reg.num);

    }while(reg.pos!=-1);

    fclose(arquivo);
    system("PAUSE");
    return 0;
}





