#include<stdio.h>

#define ORDER  3
#define NUM_CHAVES (ORDER - 1)

typedef struct no_arvore{
	int numChaves;
	int folha;
	int chaves[NUM_CHAVES];
	struct no_arvore *filhos[ORDER];
}No;

No *BuscarNoInserir(int *chave, No *no){
	
	if(no->folha==0){
		int i=0;
		while(*chave > no->chaves[i] && i < no->numChaves)
			i++;
		no=BuscarNoInserir(chave,no->filhos[i]);
	}
	
	return no;
}
void Inserir(int chave, No *Raiz){
	
	if(Raiz==NULL){
		No *novo;
		novo = (No *) malloc(sizeof(No));
		novo->folha=1;
		novo->chaves[0]=chave;
	}else{
		//encontrar um nó folha
		No *noIsere = BuscarNoInserir(&chave, Raiz);
	  }
}



int main(){
	No *Raiz=NULL;
	Inserir(3,Raiz);

system("PAUSE");
return 0;
}
