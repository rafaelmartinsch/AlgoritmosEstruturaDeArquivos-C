#include<stdio.h>

typedef struct{
    char nome[20];
	char endereco[20];
	char telefone[11];
	char email[20];

}Cadastro;

void NovoCadastro(FILE *data){

	Cadastro NovoCadastro;

	printf("\n-------- NOVO CADASTRO ----------");
	
	printf("\nNome: ");
	gets(NovoCadastro.nome);
	printf("Endereco: ");
	gets(NovoCadastro.endereco);
	printf("Telefone: ");
	gets(NovoCadastro.telefone);
	printf("E-Mail: ");
	gets(NovoCadastro.email);
	
	fprintf(data,"%s\n",NovoCadastro.nome);
	fprintf(data,"%s\n",NovoCadastro.endereco);
	fprintf(data,"%s\n",NovoCadastro.telefone);
	fprintf(data,"%s\n\n",NovoCadastro.email);

}


void ListarArquivo(FILE *data){

	Cadastro cadastro;

	//fseek(data,sizeof(Cadastro),SEEK_SET);
	rewind(data);
	
	while(fscanf(data,"%s %s %s %s",
	&cadastro.nome,&cadastro.endereco,&cadastro.telefone,&cadastro.email)!=EOF){//!feof(data)){
		
		/*fscanf(data,"%s",&cadastro.nome);
		fscanf(data,"%s",&cadastro.endereco);
		fscanf(data,"%s",&cadastro.telefone);
		fscanf(data,"%s",&cadastro.email);*/
		
			printf("\nNome: %s",cadastro.nome);
			printf("\nEndereco: %s",cadastro.endereco);
			printf("\nTelefone: %s",cadastro.telefone);
			printf("\nEndereco: %s",cadastro.email);
			printf("\n\n");
			
	}



}


int main(){
	
	FILE * data;
	int opc;
	
	data=fopen("form.txt", "a+");
	if(!data){
		printf("\n Erro ao abrir ou criar arquivo\n");
	}else printf("\nArquivo iniciado\n");
	
	do{
		printf("\nDigite a opcao ou 0 p/ encerrar:");
		printf("\nDigite 1 p/ Novo Cadastro");
		printf("\nDigite 2 p/ Listar\n");
		scanf("%d",&opc);
		fflush(stdin);
	
		switch(opc){
			case 1:
				NovoCadastro(data);
				break;
			case 2: 
				ListarArquivo(data);
				break;
			default:
				printf("Opcao invalida");
		}
	
	}while(opc!=0);
	
	fclose(data);


system("PAUSE");
return 0;
}