#include<stdio.h>
#include<string.h>

typedef struct{
       char nome[10];
       int idade;
       char formacao[20];
}Dados;

void Gravar(){
        FILE * arq;
        arq  = fopen("Dados_ex2_list2.bin","wb");
        
        Dados registro;
        
        strcpy(registro.nome,"Tadeu");
        registro.idade=10;
        strcpy(registro.formacao,"Mestre");
        fwrite(&registro,sizeof(Dados),1,arq);
        
        
        strcpy(registro.nome,"Cintia");
        registro.idade=40;
        strcpy(registro.formacao,"Doutorado");
        fwrite(&registro,sizeof(Dados),1,arq);
        
        strcpy(registro.nome,"Sergio");
        registro.idade=35;
        strcpy(registro.formacao,"Graduado");
        fwrite(&registro,sizeof(Dados),1,arq);
        
        strcpy(registro.nome,"Ana");
        registro.idade=5;
        strcpy(registro.formacao,"-");
        fwrite(&registro,sizeof(Dados),1,arq);
        
        strcpy(registro.nome,"Duda");
        registro.idade=18;
        strcpy(registro.formacao,"Ensino Medio");
        fwrite(&registro,sizeof(Dados),1,arq);
        
        strcpy(registro.nome,"Joana");
        registro.idade=25;
        strcpy(registro.formacao,"Graduada");
        fwrite(&registro,sizeof(Dados),1,arq);
        
        strcpy(registro.nome,"Betina");
        registro.idade=60;
        strcpy(registro.formacao,"Ensino Fundamental");
        fwrite(&registro,sizeof(Dados),1,arq);
        
        strcpy(registro.nome,"Beto");
        registro.idade=30;
        strcpy(registro.formacao,"Mestre");
        fwrite(&registro,sizeof(Dados),1,arq);
        
        strcpy(registro.nome,"Katia");
        registro.idade=80;
        strcpy(registro.formacao,"Doutora");
        fwrite(&registro,sizeof(Dados),1,arq);
        
        strcpy(registro.nome,"Abel");
        registro.idade=50;
        strcpy(registro.formacao,"Mestre");
        fwrite(&registro,sizeof(Dados),1,arq);
        
        fclose(arq);
}

void Ler(){
     FILE * arq;
     Dados reg;
     arq = fopen("Dados_ex2_list2.bin","rb");
     
     printf("\n\n");
     printf("\n+--------------------------------------------------+"); 
     printf("\n|     Nome      |     Idade     |      Formacao    |");
     printf("\n+--------------------------------------------------+\n");

     //fseek(arq,sizeof(Dados),SEEK_SET);

     //while(!feof(arq)){
     while(fread(&reg,sizeof(Dados),1,arq)==1){  
			
		  int quantidade_de_espaco;
			
		  //impressão em forma de tabela. 
		  quantidade_de_espaco = 15-strlen(reg.nome);// contara quantos espaços em branco terá que ser impresso para alinha as colunas que possui 15 espaços.
          printf("|%s",reg.nome);//sera impresso o conteudo da primeira coluna 
		  while(quantidade_de_espaco!=0){//imprime a quantidade de espaço necessarios na coluna dos nomes
				printf(" ");
				quantidade_de_espaco--;
		  }

		  //coluna da idade
		  if(reg.idade<10)quantidade_de_espaco = 14;// quantidade de espaços que alinhará a coluna, a idade possui 1,2 ou três caracteres
		  else if(reg.idade>=10)quantidade_de_espaco = 13;
		  else quantidade_de_espaco = 12;
          printf("|%d",reg.idade);
		  while(quantidade_de_espaco!=0){
				printf(" ");
				quantidade_de_espaco--;
		  }
		  
		  //coluna da formação
		  quantidade_de_espaco = 15-strlen(reg.formacao);
          printf("|%s",reg.formacao);
		  while(quantidade_de_espaco!=-3){ // neste caso uma das palavras tem 18 caracteres então a coluna terá mais tres espaços
				printf(" ");
				quantidade_de_espaco--;
		  }
		  printf("|\n");
		  
     }
     printf("+--------------------------------------------------+\n");
     
     fclose(arq);
}

void Inverter(){
	FILE * pi;
	FILE * pf;
	int i=0;
	Dados reg1,reg2,anterior;
	
	pi=fopen("Dados_ex2_list2.bin","r+b");
	pf=fopen("Dados_ex2_list2.bin","r+b");

	
	
	while(strcmp(anterior.nome,reg1.nome)!=0 ){
	
		
			
		fseek(pi,sizeof(Dados)*i,SEEK_SET);
		fseek(pf,sizeof(Dados)*(-(i+1)),SEEK_END);
		i++;
		fread(&reg1,sizeof(Dados),1,pi);	
		fread(&reg2,sizeof(Dados),1,pf);

		
		fseek(pi,sizeof(Dados)*(-1),SEEK_CUR);
		fwrite(&reg2,sizeof(Dados),1,pi);
		fseek(pf,sizeof(Dados)*(-1),SEEK_CUR);
		fwrite(&reg1,sizeof(Dados),1,pf);	

			anterior=reg1;
			
		
	}

	fclose(pi);
	fclose(pf);
}


int main(){
   
    
    Gravar();
    Ler();
    Inverter();
    Ler();
	
       
    system("PAUSE");
    return 0;     
}
