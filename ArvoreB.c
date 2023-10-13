#include<stdio.h>
#include <ctype.h>//Biblioteca usada para converter letras minusculas em maiusculas
/// http://forum.clubedohardware.com.br/topic/453784-salvar-em-arquivo-em-uma-arvore-b/
const int ordem = 100000; //oderm cem mil
const char  NomeArquivo[]="DataArvoreB.bin";


typedef struct no_arvoreB ArvoreB;

struct no_arvoreB{
	int num_chaves; //quantidaddes já armazenadas
	int chaves[100000]; //ordem-1
	ArvoreB *filhos[100001]; //ordem
    int folha; //1=true e 0=false
};


void Inserir(){
	int num;
	FILE * arquivo;
	ArvoreB buffer;
	arquivo = fopen(NomeArquivo,"a+b");
	
	syetem("cls");
	printf("\n************* INSERIR ********************\n");
	printf("\n Digite o Numero que Deseja Armazenar:\n");
	scanf("%d",&num);
	
	
	fseek(arquivo,0,SEEK_END);
	
	if(ftell(arquivo)==0){
	  //vazio
	
	}
	else{
			fseek(arquivo,sizeof(ArvoreB)*(-1),SEEK_END);
			fread(&buffer,sizeof(ArvoreB),1,arquivo);//ler a raiz da arvore
			
			if(buffer.num_chaves<(ordem)){ //tem espaço no vetor?
			
					if(num > buffer.chaves[buffer.num_chaves]){// o numero à inserir é maior que o ultimo registro do vetor?
						buffer.chaves[buffer.(num_chaves+1)]=num; //insere
						num_chaves++; //acresenta o numero de chaves
					}
					//else
				
						
				
			
			}
			//else{
			//}
			
		}



}

ListarArquivo(){

	FILE * Arquivo;
	if( (Arquivo = fopen(NomeArquivo,"rb")) == NULL ){
		printf("Erro ao abrir arquivo");
		syetem("PAUSE");
		exit(1);
	}
	
	//while(fread()!=EOF);
	fclose(Arquivo);

}

void Listar(){
	char opc;
	 
	do{
		system("cls");
		printf("\nCONTROLE DE NUMEROS\n");
		printf("\n+------------------------------------------------------+");
		printf("\n|                      MENU LISTAR                     |");
		printf("\n+------------------------------------------------------+");
		printf("\n|                                                      |");
		printf("\n| [F] - Faixa, de numeros determinada pelo usuario     |");
		printf("\n| [C] - Completo, todos numeros em ordem crescente     |");
		printf("\n| [A] - Arquivo, dados na ordem que aparece no arquivo |");
		printf("\n| [M] - Munu principal                                 |");
		printf("\n|                                                      |");
		printf("\n+------------------------------------------------------+\n");
		printf("\nOpcao: ");
		fflush(stdin);
		scanf("%c",&opc);
		opc=toupper(opc);
		switch(opc){
			case 'F':
				 
				 break;
			case 'C':
				 
				 break;
			case 'A':
				 ListarArquivo();
				 break;
			case 'M':
				 break;
			default:
				 printf("\n Opcao Invalida Tente Novamente!\n");
				 system("PAUSE");
		}
		
	}while(opc!='M');
}

int main(){

	char opc;
	 
	do{
		system("cls");
		printf("\nCONTROLE DE NUMEROS\n");
		printf("\n+----------------------------+");
		printf("\n|       MENU PRINCIPAL       |");
		printf("\n+----------------------------+");
		printf("\n|                            |");
		printf("\n|  [I] - Inserir Numeros     |");
		printf("\n|  [L] - Listar              |");
		printf("\n|  [P] - Pesquisar Numeros   |");
		printf("\n|  [S] - Sair do Programa    |");
		printf("\n|                            |");
		printf("\n+----------------------------+\n");
		printf("\nOpcao: ");
		fflush(stdin);
		scanf("%c",&opc);
		//opc=toupper(opc);
		switch(opc){
			case 'I':
				 Inserir();
				 break;
			case 'L':
				 Listar();
				 break;
			case 'P':
				 //Pesquisar();
				 break;
			case 'S':
				 break;
			default:
				 printf("\n Opcao Invalida Tente Novamente!\n");
				 system("PAUSE");
		}
		
	}while(opc!='S');

system("PAUSE");
return 0;
}
