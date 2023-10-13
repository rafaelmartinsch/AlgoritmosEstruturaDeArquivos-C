#include<stdio.h>

int main(){
    char var;
    FILE *arquivo;
	arquivo = fopen("nome_do_arquivo.bin","a+b");// abrir  arquivo logico
        /*http://homepages.dcc.ufmg.br/~joaoreis/Site%20de%20tutoriais/c_int/arquivos.htm
          "r" - abre um arquivo p/ ler
          "w" - abre para escrita
          "a" - abre ou cria pra a ANEXAÇÂO
          "r+" - abre ou cria leitura e escrita
          "w+" - abre ou cria leitura e escrita, apagando o arquivo já existente
          "a+" - abre ou cria para leitura ou excrita Anexando o conteudo

          "rb" - abre Arquivo Binario / leitura
          "wb" - abre Arquivo Binario / escrita
          "ab" - abre ou cria anexando binario

          "r+b" - abre ou cria leitura e escrita binario
          "w+b" - abre ou cria substituindo, para leitura e escrita
          "a+b" - acrescenta, abrindo ou criando, leitura ou escrita
          */

/**************** LER *********************/

    var = getc(arquivo);//retorna caracter e passa para o prox caracter

    do{
        var = fgetc(arquivo);//Metodo de ter consequententente
        printf("\n %c",var);
    }while(var != EOF);//eof indica o final do arquivo, para de ler

    fscanf(arquivo,"%c",&var); // ponteiro FILE e variavel que irá receber os dados
    //exemplo
    while(!feof(arquivo)){//retorna 0 se se o arquivo cregar ao final

        fscanf(arquivo,"%c",&var);

    }

/**************** Escrever ******************/

    putc('c',arquivo);//Escreve o caracter no arquivo
    fputc('d',arquivo);//Escreve o caracter no arquivo

        variavelString = "texto qualquer";
    fprintf(arquivo,"Este e um arquivo %s",variavelString); // ponteiro FILE e

/****************** busca *********************/

    fseek(arquivo,sizeof(char)*2,SEEK_SET);//move as posiçõe dadas
    //SEEK_SET = 0 - inicio do arquivo
    //seek_cur = 1 - ponto corrente
    //seek_end = 2 - final do arquivo



fclose(arquivo);//fechar arquivo logico

/********************* Arquivo Binario **************************/


    arq = fopen("ArquivoBin.dat","wb");



    /******* leitura ****/
    arq = fopen("ArquivoBin.dat","rb");
       int buffer;
    string ler = fread(&buffer,sizeof(int),1,arq);
    fclose(arq);
	
    /**** escrever ***/
    arq = fopen("ArquivoBin.dat","wb");
    string str;
    result = fwrite(&str,sizeof(string),1,arq);//endereço da variavel, tamanho, quantidade, e oi FILE
    fclose(arq);
 
    /**
    ferror

                int ferror (FILE *fp);
    A função ferror() se torna muito útil quando queremos verificar se cada acesso
    a um arquivo teve sucesso. Cada vez que uma função de arquivo é executada,
    a própria função registra numa variável especial se houve sucesso na operação
     ou não. Com ferror() podemos ter acesso ao conteúdo desta variável: ela retorna
    não zero se houve algum erro na última função de acesso ao arquivo.
    **/

    /**
    rewind
        A função rewind() de protótipo

                void rewind (FILE *fp);

        retorna a posição corrente do arquivo para o início.
    **/

    /**
        remove

                int remove (char *nome_do_arquivo);

        Desmancha um arquivo especificado.
    **/


system("PAUSE");
return 0;
}
/** Rafael Martins 2013 **/