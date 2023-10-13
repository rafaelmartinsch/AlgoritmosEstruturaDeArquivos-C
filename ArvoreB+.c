/***** Trabalho 2 de Estrutura de Arquivos e Programação ****
	Este programa irá armazenar números inteiros em uma arvore B+,
  permitindo inserir, pesquisar e listar os dados da arvore em ordem crescente, decrescente e sequencia do arquivo.
  
  Autor: Rafael Martins Chimenes
  RGA: 2011.1804.010-4
****/
// biliotécas usadas
#include<stdio.h>
//variaveis globais usadas
#define ARQUIVOINDICE "index.bin" //const char arquivoIndice[]="index.bin";
#define ARQUIVODATA "data.bin" //const char arquivoDados[]="data.bin";
#define ORDEM 5
#define QTD_CHAVES (ORDEM - 1) // constante que apontara a cquantidade maxima de chaves no nó
int fim; // fariavel saberá a posição do ultimo nó que foi inserido no arquivo de dados 
//estrutura dos nó dados ou pagina
typedef struct dataNo{
	int numChaves;
	int chaves[QTD_CHAVES];
	int proxNo;
}dNo;
//estrutura para os indices da arvore
typedef struct idexNo{
	int folha;
	int numChaves;
	int chaves[QTD_CHAVES];
	int filhos[ORDEM];
}iNo;

int posRaiz(){//retorna a posição da raiz no arquivo indice
	FILE * arq = fopen(ARQUIVOINDICE,"a+b");//se o arquivo indice não existir será criado
	fseek(arq,sizeof(iNo),SEEK_END);
	int i = ((ftell(arq))/ (sizeof(iNo))) -1; //retorna o tamanho do arquivo em bytes dividido pelo registro em byte 
	fclose(arq);
	return i;
}

void insertionSort(int *vetor, int tam) {
   int i, j, eleito;
   for (i = 1; i < tam; i++){
      eleito = vetor[i];
      j = i - 1;
      while ((j>=0) && (eleito < vetor[j])) {
         vetor[j+1] = vetor[j];
         j--;
      }
      vetor[j+1] = eleito;
   }
}

int InserirDados(int NoPos, int insere){
	FILE * arq;
	dNo pagina;
	
	arq=fopen(ARQUIVODATA,"r+b");
	
	fseek(arq,(NoPos-1)*sizeof(dNo),SEEK_SET);
	if(fread(&pagina,sizeof(dNo),1,arq)==1){//se retorna 1 foi lido algo
	
		//vereficar se tem espaço no nó de dados indicado
		if(pagina.numChaves<(ORDEM-1)){
			int aux,aux2, pos=0;
			while(pos<pagina.numChaves && insere>=pagina.chaves[pos])
				pos++;
				aux=insere;	
			for(;pos<=pagina.numChaves;pos++){
				aux2=pagina.chaves[pos];
				pagina.chaves[pos]=aux;
				aux=aux2;
			}	
			
			pagina.numChaves++;
			fseek(arq,(NoPos-1)*sizeof(dNo),SEEK_SET);
			fwrite(&pagina, sizeof(dNo),1,arq);
		}
		else{// não há espaço no nó de dados então criamos um outro e passamos o dado do meio para o indice e o meio  até o fim para o novo
			int proxNovo, i, vetorTemp[ORDEM];
			int aux,aux2, pos=0;
			dNo novo;
			
			/** operações no vetor temporario **/
			//farei uma copia do vetor, porém com uma posição a mais onde o numero que vou iserir sera incluido neste vetor
			for(i=0;i<pagina.numChaves;i++)
				vetorTemp[i]=pagina.chaves[i];	
			vetorTemp[i]=insere;
			insertionSort(vetorTemp,ORDEM);//odenar o vetor 
			
			/** operações no nó antigo **/
			//o antigo no apenas diminui a quantidade de dados e regrava na mesma posição
			int qtd=(int)((ORDEM)/2);
			pagina.numChaves=qtd;
			
			for(i=0;i<qtd;i++)
				pagina.chaves[i]=vetorTemp[i];
			
			//irá apontar para o novo nó que será criado e gravado no fim do arquivo, para isso preciso da posição do ultimo nó
			fseek(arq,sizeof(dNo),SEEK_END);
			fim = ((ftell(arq))/ (sizeof(dNo)));
			proxNovo=pagina.proxNo;
			pagina.proxNo=fim;
			
			//posiciona para regravar os dados do no antigos
			fseek(arq,(NoPos-1)*sizeof(dNo),SEEK_SET);
			fwrite(&pagina, sizeof(dNo),1,arq);
			
			/** operações no novo nó  **/
			int y=0;
			while(i<ORDEM){
				novo.chaves[y++]=vetorTemp[i++];
			}
			novo.numChaves=y;
			novo.proxNo=proxNovo;
			
			fseek(arq,sizeof(dNo)*(fim-1),SEEK_SET);
			fwrite(&novo,sizeof(dNo),1,arq);
			fclose(arq);
			return novo.chaves[0];
		}
	}// se o read não retornar 1 então o arquivo de dados está vazio ou não foi criado então criaremos o primeiro nó e o arquivo
	
	else{
		fclose(arq);//fexamos o ponteiro de leitura e gravação e abrimos como "a+b" para criar o arquivo caso ainda não esteja criado
		if((arq=fopen(ARQUIVODATA,"a+b"))==NULL ){
			printf("Ocorreu um erro ao criar  %s! \n",ARQUIVODATA);
			return;
		}
		dNo novo;
		novo.numChaves=1;
		novo.proxNo=-1;
		novo.chaves[0]=insere;
		fwrite(&novo, sizeof(dNo),1,arq);
	}
	fclose(arq);
	return -1;
}


int BuscaIndiceInserir(int insere, int NoPos){
	FILE * arq;
	iNo no;
	int retorno;
	
	if((arq=fopen(ARQUIVOINDICE,"r+b"))==NULL ){//o arquivo de indice deverá ser criado mesmo se ainda não tenha indices
		printf("Ocorreu em erro ao abrir %s para leitura!\n",ARQUIVOINDICE);
	}
	
	fseek(arq,(NoPos-1)*sizeof(iNo),SEEK_SET);
	if(fread(&no,sizeof(iNo),1,arq)==1){// a condicional verificara se foi lido algo no arquivo 
		int i = 0;
		while(i<no.numChaves && insere>=no.chaves[i])
			i++;

		if(no.folha!=1){//não é folha
			retorno=BuscaIndiceInserir(insere, no.filhos[i]); // pasa a posição do filho recursiva
			if(retorno!=-1){//isiro neste no de indice
					iNo auxNo;
				if(no.numChaves<(ORDEM-1)){
					int aux,aux2, pos=0,posFilho;
					
					while(pos<no.numChaves && retorno>=no.chaves[pos])//encontro a posição que sera inserdo no vetor de chaves
						pos++;
					//guardo esta posição em uma variavel auxilia pois no vetor de filho eu vou inserir na posição+1 do vetor o endereço do filho
					posFilho=pos;
					aux=retorno;
					for(;pos<=no.numChaves;pos++){
						aux2=no.chaves[pos];
						no.chaves[pos]=aux;
						aux=aux2;
					}	
					
					no.numChaves++;
					//tenho que gravar no vetor de filhos a posição do novo filho
					aux=fim-1;
					while(posFilho<=no.numChaves){//o vetor de filhos sempre tera 1 a mais do que o de chaves
						aux2=no.filhos[++posFilho];
						no.filhos[posFilho]=aux;
						aux=aux2;
					}
					
					//troca de posição para a raiz ficar na ultima posição
					fseek(arq,(NoPos)*sizeof(iNo),SEEK_SET);
					fread(&auxNo,sizeof(iNo),1,arq);
					
					fseek(arq,(NoPos)*sizeof(iNo),SEEK_SET);
					fwrite(&no, sizeof(iNo),1,arq);
					
					fseek(arq,(NoPos-1)*sizeof(iNo),SEEK_SET);
					fwrite(&auxNo, sizeof(iNo),1,arq);
				}
				else{//não tem espaço no nó 
					
					//variaveis temporavel usada na condicional
					int vetorTemp[ORDEM],tempFilhos[ORDEM+1];// para dividir o vetor de chaves e o de filhos guardo em um auxiliar os dados 
					int aux,aux2, pos=0, i=0;
					iNo novo;
					
				/** operações em vetor temporario **/
					//farei uma copia do vetor, porém com uma posição a mais onde o numero que vou iserir o indice que sera incluido neste vetor
					//no de chaves de indice temporario
					for(i=0;i<no.numChaves;i++)
						vetorTemp[i]=no.chaves[i];	
					vetorTemp[i]=retorno;
					insertionSort(vetorTemp,ORDEM);//odenar o vetor
					
					//vetor de filhos temporario
					for(i=0;i<=no.numChaves;i++)
						tempFilhos[i]=no.filhos[i];
					//no vetor de filhos, o novo filho sera inserido na posição do novo indice inserido (retorno)
					while(pos<=no.numChaves && retorno!=vetorTemp[pos])
						pos++;//posição onde sera inserido o novo filho no vetor de filhos
					aux=fim-1;//fim é o novo filho
					while(pos<=(no.numChaves+1)){//o vetor de filhos sempre tera 1 a mais do que o de chaves
						aux2=tempFilhos[++pos];
						tempFilhos[pos]=aux;
						aux=aux2;
					}
					
				/** operações no nó antigo **/
					//o antigo no apenas diminui a quantidade de dados e regrava na mesma posição
					int qtd=(int)((ORDEM)/2);
					no.folha=0;
					no.numChaves=qtd;
					
					//regravo as chaves no nó antigo
					for(i=0;i<qtd;i++)
						no.chaves[i]=vetorTemp[i];
					//regravo os filhos no nó antigo
					for(pos=0;pos<=qtd;pos++)
						no.filhos[pos]=tempFilhos[pos];
					
					//posiciona para regravar os dados do no antigos, na mesma posição de antes
					
					fseek(arq,(NoPos)*sizeof(iNo),SEEK_SET);
					fread(&auxNo,sizeof(iNo),1,arq);
					
					fseek(arq,(NoPos)*sizeof(iNo),SEEK_SET);
					fwrite(&no, sizeof(iNo),1,arq);
					
					fseek(arq,(NoPos-1)*sizeof(iNo),SEEK_SET);
					fwrite(&auxNo, sizeof(iNo),1,arq);
					
					
					//irá apontar para o novo nó que será criado e gravado no fim do arquivo, para isso preciso da posição do ultimo nó
					fseek(arq,sizeof(iNo),SEEK_END);
					fim = ((ftell(arq))/ (sizeof(iNo)));
					
				/** operações no novo nó  **/
					novo.folha=0;
					//grava valores no nó de chaves
					int y=0;
					while(i<ORDEM){
						novo.chaves[y++]=vetorTemp[++i];
					}
					
					y=0;
					//grava valores no nó de filhos
					while(pos<=ORDEM){
						novo.filhos[y++]=tempFilhos[pos++];
					}
					novo.numChaves=(y-1);
					fseek(arq,sizeof(iNo)*(fim-1),SEEK_SET);
					fwrite(&novo,sizeof(iNo),1,arq);
						
					if((fim-2)==NoPos){//se for a raiz que foi dividida tenho que criar uma nova raiz
						novo.folha=0;
						novo.numChaves=1;
						novo.chaves[0]=vetorTemp[qtd];
						novo.filhos[0]=fim-1;
						novo.filhos[1]=fim;
						fim++;
						fseek(arq,sizeof(iNo)*(fim-1),SEEK_SET);
						fwrite(&novo,sizeof(iNo),1,arq);
					}
					else{
						fclose(arq);
						return vetorTemp[qtd];
					}	
					
				}
			}
		}
		else{// se for folha ou raiz
			retorno=InserirDados(no.filhos[i], insere);
			if(retorno!=-1){//isiro neste no de indice
			
				if(no.numChaves<(ORDEM-1)){//tem espaço no vetor de chaves
					int aux,aux2, pos=0,posFilho;
					while(pos<no.numChaves && retorno>=no.chaves[pos])//encontro a posição que sera inserdo no vetor de chaves
						pos++;
					//guardo esta posição em uma variavel auxilia pois no vetor de filho eu vou inserir na posição+1 do vetor o endereço do filho
					posFilho=pos;
					aux=retorno;
					for(;pos<=no.numChaves;pos++){
						aux2=no.chaves[pos];
						no.chaves[pos]=aux;
						aux=aux2;
					}	
					
					no.numChaves++;
					//tenho que gravar no vetor de filhos a posição do novo filho
					aux=fim;
					while(posFilho<=no.numChaves){//o vetor de filhos sempre tera 1 a mais do que o de chaves
						aux2=no.filhos[++posFilho];
						no.filhos[posFilho]=aux;
						aux=aux2;
					}
					fseek(arq,(NoPos-1)*sizeof(iNo),SEEK_SET);
					fwrite(&no, sizeof(iNo),1,arq);
					
				}
				else{// no caso de não ter espaço no folha criamos um novo nó 
					
					//variaveis temporavel usada na condicional
					int vetorTemp[ORDEM],tempFilhos[ORDEM+1];// para dividir o vetor de chaves e o de filhos guardo em um auxiliar os dados 
					int aux,aux2, pos=0, i=0;
					iNo novo;
					
				/** operações em vetor temporario **/
					//farei uma copia do vetor, porém com uma posição a mais onde o numero que vou iserir o indice que sera incluido neste vetor
					//no de chaves de indice temporario
					for(i=0;i<no.numChaves;i++)
						vetorTemp[i]=no.chaves[i];	
					vetorTemp[i]=retorno;
					insertionSort(vetorTemp,ORDEM);//odenar o vetor
					
					//vetor de filhos temporario
					for(i=0;i<=no.numChaves;i++)
						tempFilhos[i]=no.filhos[i];
					//no vetor de filhos, o novo filho sera inserido na posição do novo indice inserido (retorno)
					while(pos<=no.numChaves && retorno!=vetorTemp[pos])
						pos++;//posição onde sera inserido o novo filho no vetor de filhos
					aux=fim;//fim é o novo filho
					while(pos<=(no.numChaves+1)){//o vetor de filhos sempre tera 1 a mais do que o de chaves
						aux2=tempFilhos[++pos];
						tempFilhos[pos]=aux;
						aux=aux2;
					}
					
				/** operações no nó antigo **/
					//o antigo no apenas diminui a quantidade de dados e regrava na mesma posição
					int qtd=(int)((ORDEM)/2);
					no.folha=1;
					no.numChaves=qtd;
					
					//regravo as chaves no nó antigo
					for(i=0;i<qtd;i++)
						no.chaves[i]=vetorTemp[i];
					//regravo os filhos no nó antigo
					for(pos=0;pos<=qtd;pos++)
						no.filhos[pos]=tempFilhos[pos];
					
					//posiciona para regravar os dados do no antigos, na mesma posição de antes
					fseek(arq,(NoPos-1)*sizeof(iNo),SEEK_SET);
					fwrite(&no, sizeof(iNo),1,arq);
					
					//irá apontar para o novo nó que será criado e gravado no fim do arquivo, para isso preciso da posição do ultimo nó
					fseek(arq,sizeof(iNo),SEEK_END);
					fim = ((ftell(arq))/ (sizeof(iNo)));
					
				/** operações no novo nó  **/
					novo.folha=1;
					//grava valores no nó de chaves
					int y=0;
					while(i<ORDEM){
						novo.chaves[y++]=vetorTemp[++i];
					}
					
					y=0;
					//grava valores no nó de filhos
					while(pos<=ORDEM){
						novo.filhos[y++]=tempFilhos[pos++];
					}
					novo.numChaves=(y-1);
					fseek(arq,sizeof(iNo)*(fim-1),SEEK_SET);
					fwrite(&novo,sizeof(iNo),1,arq);
					
					if(fim==2){//se for a raiz que foi dividida tenho que criar uma nova raiz
						novo.folha=0;
						novo.numChaves=1;
						novo.chaves[0]=vetorTemp[qtd];
						novo.filhos[0]=1;
						novo.filhos[1]=fim;
						fim++;
						fseek(arq,sizeof(iNo)*(fim-1),SEEK_SET);
						fwrite(&novo,sizeof(iNo),1,arq);
					}
					else{
						fclose(arq);
						return vetorTemp[qtd];
					}
				}
			}
		}
	}else{// se não for lido algo então existe uma unica chave de dados ainda sem indices, ou os dois arquivos estão vazios 
		retorno=InserirDados(1, insere);
		if(retorno!=-1){//crio o primeiro no de indices
			no.folha=1;
			no.numChaves=1;
			no.chaves[0]=retorno;
			no.filhos[0]=1;
			no.filhos[1]=2;
			fwrite(&no,sizeof(iNo),1,arq);
		}
	}
	
	fclose(arq);
	return -1;
}

void Inserir(){
	int insere, posinsere;
	iNo *no;
	
	system("cls");
	printf("\n               CONTROLE DE NUMEROS\n");
	printf("\n+---------------------------------------------------+");
	printf("\n|                 ISERIR NUMERO                     |");
	printf("\n+---------------------------------------------------+\n");
	printf("Informe o numero que deseja Inserir:\n ");
	scanf("%d", &insere);
	//inserir no aquivo de dados 
	
	BuscaIndiceInserir(insere,posRaiz());
	//system("PAUSE");
}

void InserirDireto(){ //ordem = 5
// esta função insere diretamente os dados no arquivo sem respeitar as regras
	system("cls");
	iNo i_novo;
	dNo d_novo;
	
	FILE * file;
	
	if( (file=fopen(ARQUIVOINDICE,"wb"))==NULL)
		printf("ERRo ao criar arquivo indice");
	else{
		
		i_novo.folha=1;
		i_novo.numChaves=2;
		i_novo.chaves[0]=350;
		i_novo.chaves[1]=600;
		i_novo.filhos[0]=1;
		i_novo.filhos[1]=3;
		i_novo.filhos[2]=4;
		fwrite(&i_novo,sizeof(iNo),1,file);
		
		i_novo.folha=1;
		i_novo.numChaves=2;
		i_novo.chaves[0]=780;
		i_novo.chaves[1]=800;
		i_novo.filhos[0]=6;
		i_novo.filhos[1]=10;
		i_novo.filhos[2]=11;
		fwrite(&i_novo,sizeof(iNo),1,file);
		
		i_novo.folha=1;
		i_novo.numChaves=2;
		i_novo.chaves[0]=1500;
		i_novo.chaves[1]=1600;
		i_novo.filhos[0]=9;
		i_novo.filhos[1]=2;
		i_novo.filhos[2]=14;
		fwrite(&i_novo,sizeof(iNo),1,file);
		
		i_novo.folha=1;
		i_novo.numChaves=2;
		i_novo.chaves[0]=850;
		i_novo.chaves[1]=900;
		i_novo.filhos[0]=12;
		i_novo.filhos[1]=7;
		i_novo.filhos[2]=8;
		fwrite(&i_novo,sizeof(iNo),1,file);
		
		
		i_novo.folha=1;
		i_novo.numChaves=4;
		i_novo.chaves[0]=1779;
		i_novo.chaves[1]=2000;
		i_novo.chaves[2]=4000;
		i_novo.chaves[3]=6000;
		i_novo.filhos[0]=15;
		i_novo.filhos[1]=17;
		i_novo.filhos[2]=5;
		i_novo.filhos[3]=13;
		i_novo.filhos[4]=16;
		fwrite(&i_novo,sizeof(iNo),1,file);
		
		
		i_novo.folha=0;
		i_novo.numChaves=4;
		i_novo.chaves[0]=750;
		i_novo.chaves[1]=810;
		i_novo.chaves[2]=970;
		i_novo.chaves[3]=1750;
		i_novo.filhos[0]=1;
		i_novo.filhos[1]=2;
		i_novo.filhos[2]=4;
		i_novo.filhos[3]=3;
		i_novo.filhos[4]=5;
		fwrite(&i_novo,sizeof(iNo),1,file);
		
		fclose(file);
	}
	
	if( (file=fopen(ARQUIVODATA,"wb"))==NULL)
		printf("ERRo ao criar arquivo data");
	else{
		d_novo.numChaves=2;
		d_novo.chaves[0]=50;
		d_novo.chaves[1]=250;
		d_novo.proxNo=3;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=2;
		d_novo.chaves[0]=1500;
		d_novo.chaves[1]=1555;
		d_novo.proxNo=14;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=2;
		d_novo.chaves[0]=350;
		d_novo.chaves[1]=500;
		d_novo.proxNo=4;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=2;
		d_novo.chaves[0]=600;
		d_novo.chaves[1]=700;
		d_novo.proxNo=6;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=2;
		d_novo.chaves[0]=2000;
		d_novo.chaves[1]=3000;
		d_novo.proxNo=13;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=2;
		d_novo.chaves[0]=750;
		d_novo.chaves[1]=777;
		d_novo.proxNo=10;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=2;
		d_novo.chaves[0]=850;
		d_novo.chaves[1]=855;
		d_novo.proxNo=8;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=2;
		d_novo.chaves[0]=900;
		d_novo.chaves[1]=955;
		d_novo.proxNo=9;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=3;
		d_novo.chaves[0]=970;
		d_novo.chaves[1]=1000;
		d_novo.chaves[2]=1350;
		d_novo.proxNo=2;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=2;
		d_novo.chaves[0]=780;
		d_novo.chaves[1]=790;
		d_novo.proxNo=11;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=2;
		d_novo.chaves[0]=800;
		d_novo.chaves[1]=808;
		d_novo.proxNo=12;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=3;
		d_novo.chaves[0]=810;
		d_novo.chaves[1]=818;
		d_novo.chaves[2]=845;
		d_novo.proxNo=7;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=2;
		d_novo.chaves[0]=4000;
		d_novo.chaves[1]=5000;
		d_novo.proxNo=16;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=2;
		d_novo.chaves[0]=1600;
		d_novo.chaves[1]=1700;
		d_novo.proxNo=15;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=2;
		d_novo.chaves[0]=1750;
		d_novo.chaves[1]=1777;
		d_novo.proxNo=17;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=3;
		d_novo.chaves[0]=6000;
		d_novo.chaves[1]=7000;
		d_novo.chaves[2]=9000;
		d_novo.proxNo=-1;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		d_novo.numChaves=3;
		d_novo.chaves[0]=1779;
		d_novo.chaves[1]=1900;
		d_novo.chaves[2]=1999;
		d_novo.proxNo=5;
		fwrite(&d_novo,sizeof(dNo),1,file);
		
		fclose(file);
	}
	system("PAUSE");
}

int BuscaBinaria(int *vetor,int busca, int tamanho){ //retorna a posição maior  ao busca
	int meio, i = 0, s= tamanho-1;
	
	while(i <= s){
		meio = i+(s - i)/2;
		if(vetor[meio] == busca)
			return meio;
		else if(vetor[meio]>busca)
			s = meio-1;
		else
			i = meio+1;
	}
	return -1;
}

int BuscaIndice(int busca, int NoPos){
	FILE * arq;
	iNo no;
	int retorno;
	
	if((arq=fopen(ARQUIVOINDICE,"rb"))==NULL ){//o arquivo de indice deverá ser criado mesmo se ainda não tenha indices
		printf("Ocorreu em erro ao abrir %s para leitura!\n",ARQUIVOINDICE);
		return -1;
	}
	
	fseek(arq,(NoPos-1)*sizeof(iNo),SEEK_SET);
	if(fread(&no,sizeof(iNo),1,arq)==1){// a condicional verificara se foi lido algo no arquivo 
		int i = 0;
		while(i<no.numChaves && busca>=no.chaves[i])
			i++;

		if(no.folha!=1)//não é folha
			retorno = BuscaIndice(busca, no.filhos[i]); // pasa a posição do filho recursiva
		else
			retorno = no.filhos[i]; // retorna a posição do arquivo de dados 
	}else retorno=1;// se não for lido algo então existe uma unica chave de dados ainda sem indices, ou os dois arquivos estão vazios 
	fclose(arq);
	return retorno;
}

void Pesquisar(){
	int busca, iNoPos;
	FILE * arqDados;
	dNo pagina;
	
	if((arqDados=fopen(ARQUIVODATA,"rb"))==NULL ){//o arquivo de indice deverá ser criado mesmo se ainda não tenha indices
			printf("Ocorreu em erro ao abrir %s para leitura!\n",ARQUIVODATA);
			system("PAUSE");
			return;
	}
	
	system("cls");
	printf("\n               CONTROLE DE NUMEROS\n");
	printf("\n+---------------------------------------------------+");
	printf("\n|                    PESQUISAR                      |");
	printf("\n+---------------------------------------------------+\n");
	printf("Informe o valor que deseja:\n ");
	scanf("%d", &busca);
	
	iNoPos = BuscaIndice(busca, posRaiz());

	if(iNoPos != -1 ){ //-1= erro ao abrir o arquivo de indices
		fseek(arqDados,(iNoPos-1)*sizeof(dNo),SEEK_SET);
		if(fread(&pagina,sizeof(dNo),1,arqDados)==1){
			int pos = BuscaBinaria(pagina.chaves, busca, pagina.numChaves);//busca binaria no arquivo de dados
			if(pos!=-1){
					printf("\n %d encontrado!\n\n no:",pagina.chaves[pos]);
					printf("Qtd | %d | ",pagina.numChaves);
					printf("Dados | ");
					int i;
					for(i=0; i<pagina.numChaves; i++)
							printf("%d ",pagina.chaves[i]);
					printf("|   Prox | %d |",pagina.proxNo);
					printf("\n");
					printf("\n");
			}else printf("\n %d NAO encontrado!\n",busca);
		}else printf("\n  Arquivo de Dados Vazio\n");
	}
	fclose(arqDados);
	system("PAUSE");
}

void ListarDadosFaixa(int pos,int fim){
	FILE * arqDados;
	dNo pagina;

	if((arqDados=fopen(ARQUIVODATA,"rb"))==NULL ){//o arquivo de indice deverá ser criado mesmo se ainda não tenha indices
			printf("Ocorreu em erro ao abrir %s para leitura!\n",ARQUIVODATA);
			return;
	}
	
	fseek(arqDados,(pos-1)*sizeof(dNo),SEEK_SET);
	if(fread(&pagina,sizeof(dNo),1,arqDados)==1){
	
		if(pagina.chaves[0]<fim){ //verifica se o primeiro é maior, se for a função retorna e finaliza a listagem
			int i=0;
			while(i<pagina.numChaves && pagina.chaves[i]<=fim){
				printf("%d ",pagina.chaves[i]);
				i++;
			}
			printf("\n");
				if(pagina.proxNo!=-1 && pagina.chaves[i-1]<fim)
					ListarDadosFaixa(pagina.proxNo, fim);
		}
	}
	fclose(arqDados);
}

void ListarFaixa(){
	FILE * arqDados;
	dNo pagina;
	int comeco,fim;
	int posIndComeco;	
	
	if((arqDados=fopen(ARQUIVODATA,"rb"))==NULL ){//o arquivo de indice deverá ser criado mesmo se ainda não tenha indices
			printf("Ocorreu em erro ao abrir %s para leitura!\n",ARQUIVODATA);
			system("PAUSE");
			return;
	}
	
	system("cls");
	printf("\n               CONTROLE DE NUMEROS\n");
	printf("\n+---------------------------------------------------+");
	printf("\n|                LISTAR FAIXA                       |");
	printf("\n+---------------------------------------------------+\n");
	printf("Informe a faixa que deseja\n ");
	printf(" De: ");
	scanf("%d",&comeco);
	printf(" Ate: ");
	scanf("%d",&fim);
	
	posIndComeco = BuscaIndice(comeco, posRaiz());
	
	if(posIndComeco != -1 ){ //-1= erro ao abrir o arquivo de indices
		
		fseek(arqDados,(posIndComeco-1)*sizeof(dNo),SEEK_SET);
		if(fread(&pagina,sizeof(dNo),1,arqDados)==1){
			int pos=0;
			while(pos<pagina.numChaves && comeco>pagina.chaves[pos])
				pos++;
					
			while(pos<pagina.numChaves && pagina.chaves[pos]<=fim){
					printf("%d ",pagina.chaves[pos]);
					pos++;
			}
			if(pagina.proxNo!=-1 && pagina.chaves[pos-1]<fim)
					ListarDadosFaixa(pagina.proxNo, fim);
					
		}else printf("\n  Arquivo de Dados Vazio\n");
		
	}
	fclose(arqDados);
	system("PAUSE");
}

void ListarDados(int pos){
	FILE * arq;
	dNo pagina;
	
	if((arq=fopen(ARQUIVODATA,"rb"))==NULL){
		printf("Ocorreu em erro ao abrir %s para leitura!\n",ARQUIVODATA);
	}
	
	else{
		fseek(arq,sizeof(dNo)*(pos-1),SEEK_SET);
		if(fread(&pagina,sizeof(dNo),1,arq)!=1) // a condicional verificara se foi lido algo no arquivo 
			printf("Nao contem dados no arquivo");
		else{
			int i;
			for(i=0; i<pagina.numChaves; i++)
				printf("%d ",pagina.chaves[i]);
			printf("\n");
			if(pagina.proxNo!=-1){
				ListarDados(pagina.proxNo);
				fclose(arq);
				return; // fexa arquivo e retorna para não entrar entrar no System pause
			}
		}
	}
	
	fclose(arq);
	system("PAUSE");
}

void ListarCompleto(int pos){ //pos recebe a posição da aiz na chamada da função 
	FILE * arq;
	iNo no;
	
	system("cls");
	printf("\n               CONTROLE DE NUMEROS\n");
	printf("\n+---------------------------------------------------+");
	printf("\n|                LISTAR EM ORDEM                    |");
	printf("\n+---------------------------------------------------+\n\n");
	
	if((arq=fopen(ARQUIVOINDICE,"rb"))==NULL ){//o arquivo de indice deverá ser criado mesmo se ainda não tenha indices
		printf("Ocorreu em erro ao abrir %s para leitura!\n",ARQUIVOINDICE);
		system("PAUSE");
		return;
	}
	
	fseek(arq,(pos-1)*sizeof(iNo),SEEK_SET);
	if(fread(&no,sizeof(iNo),1,arq)==1){// a condicional verificara se foi lido algo no arquivo 
		if(no.folha==1) //se for filho chama a função listar dados
			ListarDados(no.filhos[0]);
		else  // se não é filho chama-se recursivamente 
			ListarCompleto(no.filhos[0]);
		
	}else ListarDados(1);// se não for lido algo então apenas imprime a unica chave de dados ainda sem indices
	fclose(arq);
}

void ListarArquivo(){

	int i;
	FILE * arq;
	dNo pagina;
	iNo no;
	
	system("cls");
	printf("\n              CONTROLE DE NUMEROS\n");
	printf("\n+---------------------------------------------------+");
	printf("\n|                LISTAR ARQUIVO                     |");
	printf("\n+---------------------------------------------------+\n\n");
	
	//listar sequencia o arquivo de indices 
	if( (arq=fopen(ARQUIVOINDICE,"rb")) == NULL)
		printf("Ocorreu em erro ao abrir %s para leitura!\n",ARQUIVOINDICE);
		else{
			printf("Indices\n");
			while(fread(&no,sizeof(iNo),1,arq)==1){
				printf("Folha| %d | ",no.folha);
				printf("Qtd| %d | ",no.numChaves);
				printf("chaves | ");
				for(i=0; i<no.numChaves; i++)
						printf("%d ",no.chaves[i]);
				printf("|   Filhos | ");
				for(i=0; i<=no.numChaves; i++)
						printf("%d ",no.filhos[i]);
				printf("|");
				printf("\n");
			}
			fclose(arq);
		}
	//listar sequencial o arquivo de dados
	if( (arq=fopen(ARQUIVODATA,"rb")) ==NULL)
		printf("Ocorreu em erro ao abrir %s para leitura!\n",ARQUIVODATA);
		else{
			printf("\n\nDados\n");
			while(fread(&pagina,sizeof(dNo),1,arq)==1){ //a instrução retorna 1 enquanto tiver dados para ler
				printf("Qtd | %d | ",pagina.numChaves);
				printf("Dados | ");
				for(i=0; i<pagina.numChaves; i++)
						printf("%d ",pagina.chaves[i]);
				printf("|   Prox | %d |",pagina.proxNo);
				printf("\n");
			}
			fclose(arq);
		}
	system("PAUSE");
}

void Listar(){
	char opc; 
	do{
		system("cls");
		printf("\n                  CONTROLE DE NUMEROS\n");
		printf("\n+-------------------------------------------------------- +");
		printf("\n|                       MENU LISTAR                       |");
		printf("\n+---------------------------------------------------------+");
		printf("\n|                                                         |");
		printf("\n| [ F ] - Faixa, de numeros determinada pelo usuario      |");
		printf("\n| [ C ] - Completo, todos numeros em ordem crescente      |");
		printf("\n| [ A ] - Arquivo, dados na ordem que aparece no arquivo  |");
		printf("\n| [ M ] - Munu principal                                  |");
		printf("\n|                                                         |");
		printf("\n+---------------------------------------------------------+\n");
		printf("\nOpcao: ");
		fflush(stdin);
		opc=toupper(getch()); // pegarar o char digitado no teclado e convertera em maiúscula
		switch(opc){
			case 'F':
				 ListarFaixa();
				 break;
			case 'C':
				 ListarCompleto(posRaiz());
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
		printf("\n       CONTROLE DE NUMEROS\n");
		printf("\n+------------------------------+");
		printf("\n|        MENU PRINCIPAL        |");
		printf("\n+------------------------------+");
		printf("\n|                              |");
		printf("\n|  [ D ] - Inserir direto      |");
		printf("\n|  [ I ] - Inserir numeros     |");
		printf("\n|  [ L ] - Listar              |");
		printf("\n|  [ P ] - Pesquisar Numeros   |");
		printf("\n|  [ S ] - Sair do Programa    |");
		printf("\n|                              |");
		printf("\n+------------------------------+\n");
		printf("\nOpcao: ");
		fflush(stdin);
		opc=toupper(getch()); // pegarar o char digitado no teclado e convertera em maiúscula
		switch(opc){
			case 'D':
				 InserirDireto();//opc inserir direti insere os dados para testes de buscas e pesquisas ordem 5
				 break;
			case 'I':
				 Inserir();
				 break;
			case 'L':
				 Listar();
				 break;
			case 'P':
				 Pesquisar();
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
