#include<stdio.h>
#include<string.h>

typedef struct {
	char nome[30];
	int idade;
}Registro;

void fexarPonteiros(FILE *txt, FILE *bin){

		fclose(txt);
		fclose(bin);


}

void ImprimirArquivoBin(FILE *arqBin){
	int qtdEspaco;
	Registro ler;
	
	arqBin =fopen("Data.bin","rb");
	if(!arqBin){
		printf("\nErro ao abrir arquivo:\n");
		fclose(arqBin);
		return;
	}else printf("\nArquivo aberto para a leitura");
	
	printf("\n\n+-------------------------+");
	  printf("\n|    NOME    |    IDADE   |");
	  printf("\n+-------------------------+");
	while(fread(&ler,sizeof(Registro),1,arqBin)==1){
		printf("\n| %s",ler.nome);
			qtdEspaco=11-strlen(ler.nome);
			while(qtdEspaco!=0){
				printf(" ");
				qtdEspaco--;
			}
		printf("| %d",ler.idade);
			if(ler.idade<10)qtdEspaco=11-1;
			else qtdEspaco=11-2;
			while(qtdEspaco!=0){
				printf(" ");
				qtdEspaco--;
			}
			printf("|");
	}
	printf("\n+-------------------------+");
	printf("\n\n");
	fclose(arqBin);
}

int main(){

	Registro regLido;
	char nomeTXT[15] ;
	
	FILE * arqTxt, *arqBin;
	
	//leitura do nome do arquivo txt que sera convertido em bin
	printf("\nInforme o nome do arquivo txt:\n");
	gets(nomeTXT);
	strcat(nomeTXT,".txt");
	printf("\nAbrindo Arquivo: %s",nomeTXT);
	
	
	arqTxt = fopen(nomeTXT,"r");
	if(!arqTxt){
		printf("\nErro ao abrir arquivo: %s\n",nomeTXT);
		fexarPonteiros(arqTxt,arqBin);
		return 0;
	}else printf("\nArquivo aberto");
	
	
	arqBin = fopen("Data.bin","wb");
	if(!arqBin){
		printf("\nErro ao criar arquivo!");
		fexarPonteiros(arqTxt,arqBin);
		return 0;
	} printf("\nArquivo criado");

	
	while(!feof(arqTxt)){
		fscanf(arqTxt,"%s",&regLido.nome);
		fflush(stdin);
		fscanf(arqTxt,"%d",&regLido.idade);
		
		fwrite(&regLido,sizeof(Registro),1,arqBin);
		
	}
	
	fexarPonteiros(arqTxt,arqBin);
	ImprimirArquivoBin(arqBin);
system("PAUSE");	
return 0;
}