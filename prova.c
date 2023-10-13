#include<stdio.h>
//http://homepages.dcc.ufmg.br/~joaoreis/Site%20de%20tutoriais/c_int/arquivos.htm
#define m 4
 
typedef struct No{
	int numChaves;
	int folha;
	int chaves[m-1];
	int filhos[m];
}sNo;

void gravar(){	
	FILE * ptArq;
	sNo pagina;
	int i;

	ptArq = fopen("Data.bin","wb");
	
	if(ptArq==NULL){
		printf("\nErro ao abrir arquivo para escrita\n");
		return;;	
	}

	pagina.numChaves=3;
	pagina.folha=1;
	pagina.chaves[0]=2;
	pagina.chaves[1]=7;
	pagina.chaves[2]=9;
	for(i=0;i<5;i++){
		pagina.filhos[i]=-1;
	}
	//pagina.filhos[]={-1,-1,-1,-1};
	fwrite(&pagina,sizeof(sNo),1,ptArq);

	pagina.numChaves=2;
	pagina.folha=1;
	//pagina.chaves[22,30];
	pagina.chaves[0]=22;
	pagina.chaves[1]=30;
	for(i=0;i<5;i++){
		pagina.filhos[i]=-1;
	}
	//pagina.filhos[]={-1,-1,-1,-1};
	fwrite(&pagina,sizeof(sNo),1,ptArq);

	pagina.numChaves=2;
	pagina.folha=1;
	//pagina.chaves[11,12];
	pagina.chaves[0]=11;
	pagina.chaves[1]=12;
	for(i=0;i<5;i++){
		pagina.filhos[i]=-1;
	}
	//pagina.filhos[]={-1,-1,-1,-1};
	fwrite(&pagina,sizeof(sNo),1,ptArq);

	pagina.numChaves=2;
	pagina.folha=1;
	//pagina.chaves[45,57];
	pagina.chaves[0]=45;
	pagina.chaves[1]=57;
	for(i=0;i<5;i++){
		pagina.filhos[i]=-1;
	}
	//pagina.filhos[]={-1,-1,-1,-1};
	fwrite(&pagina,sizeof(sNo),1,ptArq);

	pagina.numChaves=2;
	pagina.folha=1;
	//pagina.chaves[18,19];
	pagina.chaves[0]=18;
	pagina.chaves[1]=19;
	for(i=0;i<5;i++){
		pagina.filhos[i]=-1;
	}
	//pagina.filhos[]={-1,-1,-1,-1};
	fwrite(&pagina,sizeof(sNo),1,ptArq);

	pagina.numChaves=2;
	pagina.folha=1;
	//pagina.chaves[100,111];
	pagina.chaves[0]=100;
	pagina.chaves[1]=111;
	for(i=0;i<5;i++){
		pagina.filhos[i]=-1;
	}
	//pagina.filhos[]={-1,-1,-1,-1};
	fwrite(&pagina,sizeof(sNo),1,ptArq);

	pagina.numChaves=2;
	pagina.folha=0;
	//pagina.chaves[10,15];
	pagina.chaves[0]=10;
	pagina.chaves[1]=15;

	pagina.filhos[0]=1;
	pagina.filhos[1]=3;
	pagina.filhos[2]=5;
	pagina.filhos[3]=-1;

	//pagina.filhos[1,3,5,-1,-1];
	fwrite(&pagina,sizeof(sNo),1,ptArq);

	pagina.numChaves=2;
	pagina.folha=0;
	//pagina.chaves[33,58];
	pagina.chaves[0]=33;
	pagina.chaves[1]=58;

	pagina.filhos[0]=2;
	pagina.filhos[1]=4;
	pagina.filhos[2]=6;
	pagina.filhos[3]=-1;
	//pagina.filhos[2,4,6,-1,-1];
	fwrite(&pagina,sizeof(sNo),1,ptArq);

	pagina.numChaves=1;
	pagina.folha=0;
	//pagina.chaves[17];
	pagina.chaves[0]=20;

	pagina.filhos[0]=7;
	pagina.filhos[1]=8;
	pagina.filhos[2]=-1;
	pagina.filhos[3]=-1;
	//pagina.filhos[7,8,-1,-1,-1];
	fwrite(&pagina,sizeof(sNo),1,ptArq);
	fclose(ptArq);
}

void listarSequencial(){
	int i,y;
	FILE * ptArq;
	sNo pagina;

	if((ptArq = fopen("Data.bin","rb"))==NULL){
		printf("\nErro ao abrir arquivo para leitura\n");
		return;	
	}
	
	while( (fread(&pagina, sizeof(sNo),1,ptArq)) ==1){
		printf("%d ",pagina.numChaves);
		printf("%d ",pagina.folha);
		for(i=0; i<m; i++)
			printf("%d ",pagina.filhos[i]);
		for(y=0; y<pagina.numChaves; y++)
			printf("%d ",pagina.chaves[y]);
		printf("\n");
	}
	
	fclose(ptArq);
}

void listar(int posPagina){
	sNo pagina;
	int i;
	FILE * ptArq=fopen("Data.bin","rb");
	if(ptArq==NULL){
		printf("Erro ao abrir arquivo para leitura");
		return;
	}

	if(posPagina==-1)//se for a raiz posiciona para ler a raiz
		fseek(ptArq,-1*sizeof(sNo),SEEK_END);
	else //se não for posiciona na posição passada no parametro da função
		fseek(ptArq,(posPagina-1)*sizeof(sNo),SEEK_SET);
	fread(&pagina,sizeof(sNo),1,ptArq);
	
	if(pagina.folha==0){//tem filhos
		for(i=0;i<=pagina.numChaves;i++){
			listar(pagina.filhos[i]);
			if(i<pagina.numChaves){ //o numero de chaves é menor que o de filhos
				printf("%d ",pagina.chaves[i]);
				printf("\n");
			}
		}
	}

	else{
		for(i=0; i<pagina.numChaves; i++)
			printf("%d ",pagina.chaves[i]);
		printf("\n");
	}
	fclose(ptArq);
}


int main(){

	//gravar();
	listarSequencial();
	listar(-1);
}
