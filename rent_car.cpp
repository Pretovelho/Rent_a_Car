#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <ctime>


#define CARROS 1
#define CLIENTE 2
#define DIARIA 3
#define DEVOLVER 4
#define SAIR 9

#define DESC_IDOSO 10
#define DESC_EMPRESA 5
#define SEGUNDOS 3600;

typedef struct Cliente tbClientes;
struct Cliente {
   char nome[30] ;
   int idade;
   int cod;
   char doc[14];
   char telefone[14];
   int tpPessoa;
   tbClientes *prox;
};

static tbClientes * clientes;

typedef struct Carro tbCarros;
struct Carro {
	int cod;
   char nome[30] ;
   char placa[10];
   char cor[15];
   double vlrDiaria;
   bool disponivel;
   struct tm*dtDevolucao;
   tbCarros *prox;
};

static tbCarros * carros;

typedef struct Diaria tbDiarias;
struct Diaria {
   int qtdDiaria ;
   double valorTotal;
   Cliente cliente;
   Carro carro;
   struct tm dataRetirada;
   struct tm* dtDevolucao;
   bool devolvido;
   tbDiarias *prox;
};

static tbDiarias * diarias;

////////////////////////////////////////////////////////////////////////////////////


void iniciarTabelaCarros(){
	
	tbCarros *aux = (tbCarros*)malloc(sizeof (tbCarros)); // lista está no estilo pilha,primeiro que entra, ultimo a sair.
	aux->cod = 1;
	strcpy(aux->nome,"FORD FOCUS SEDAN");   
	strcpy(aux->placa, "DSF-4587");
	strcpy(aux->cor, "AZUL");
	aux->vlrDiaria = 90.00;
	aux->disponivel = true;  
	
	carros = aux;   	
	carros->prox = NULL;
	
	//Carro 2
	tbCarros *aux2 = (tbCarros*)malloc(sizeof (tbCarros)); // lista está no estilo pilha,primeiro que entra, ultimo a sair.
	aux2->cod = 2;
	strcpy(aux2->nome,"FIAT PUNTO");   
	strcpy(aux2->placa, "DST-5548");
	strcpy(aux2->cor, "CINZA");
	aux2->vlrDiaria = 90.00;
	aux2->disponivel = true;  	
	
	aux2->prox = carros;
	carros = aux2;
	
	//Carro 3
	tbCarros *aux3 = (tbCarros*)malloc(sizeof (tbCarros));
	aux3->cod = 3;
	strcpy(aux3->nome,"HB 20");   
	strcpy(aux3->placa, "HSR-5284");
	strcpy(aux3->cor, "PRATA");
	aux3->vlrDiaria = 100.00;
	aux3->disponivel = true;  	
	
	aux3->prox = carros;
	carros = aux3;
	
	//Carro 4
	tbCarros *aux4 = (tbCarros*)malloc(sizeof (tbCarros));
	aux4->cod = 4;
	strcpy(aux4->nome,"FOX");   
	strcpy(aux4->placa, "HGF-4007");
	strcpy(aux4->cor, "VERMELHO");
	aux4->vlrDiaria = 95.00;
	aux4->disponivel = true;  	
	
	aux4->prox = carros;
	carros = aux4;
	
	//Carro 5
	tbCarros *aux5 = (tbCarros*)malloc(sizeof (tbCarros));
	aux5->cod = 5;
	strcpy(aux5->nome,"HONDA CIVIC");   
	strcpy(aux5->placa, "DND-1574");
	strcpy(aux5->cor, "PRETO");
	aux5->vlrDiaria = 100.00;
	aux5->disponivel = true;  	
	
	aux5->prox = carros;
	carros = aux5;
	
	//Carro 6
	tbCarros *aux6 = (tbCarros*)malloc(sizeof (tbCarros));
	aux6->cod = 6;
	strcpy(aux6->nome,"CITROEN");   
	strcpy(aux6->placa, "YLF-2864");
	strcpy(aux6->cor, "AZUL");
	aux6->vlrDiaria = 95.00;
	aux6->disponivel = true;  	
	
	aux6->prox = carros;
	carros = aux6;
	
}

//////////////////////////////////////////////////////////////////////
struct tm * verificarData(int dias){
	time_t hoje, data;
	time(&hoje);
	struct tm *dataSomada;
	
	data = hoje + (86400 * dias);
	
	dataSomada = localtime(&data);
	return dataSomada; 
}

struct tm * getDataAtual(){
	time_t timer;
	struct tm *horarioLocal;
	
	time(&timer); 
	horarioLocal = localtime(&timer);
	
	return horarioLocal;
}

///////////////////////////////////////////////////////////////////////
int inicioAplicacao(){
	
	printf(">>>>>>>>>>>>> ***SISTEMA DE RESERVAS RENT CAR*** <<<<<<<<<<<<<<\n\n\n\n");
	
	printf("1- Listar carros\n");
	printf("2- Cadastrar Clientes.\n");
	printf("3- Reserva.\n");	
	printf("4- Devolver.\n");
	printf("9- Sair.\n");
	
	char opcao;

	scanf(" %c",&opcao); // espaço em branco entre a aspa e caractere %c para o scanf desconsiderar enter e espaços em branco.	

if(opcao!='1'&&opcao!='2'&&opcao!='3'&&opcao!='4'&&opcao!='9')  {
		printf("Opcao invalida.Tente novamente.\n\n");	//Caso o usuário digite letra o app não se perca no fluxo.
		return 0;
	}


	printf("\n\n");
		
	return opcao - 48; // Convertendo um caracter char para int	(subtraindo seu valor decimal por 48, chegamos no valor numerico.)
}


///////////////////////////funções de busca ///////////////////////

tbClientes* getCliente(int codCliente){
	
	tbClientes *aux;	
			
   	for (aux = clientes; aux != NULL; aux = aux->prox){      
	  
		if(aux->cod == codCliente){
	  		return aux;
	  	}  
  	}
  
  	return NULL;
}

tbCarros* getCarro(int codCarro){
	
	tbCarros *aux;		
	
   	for (aux = carros; aux != NULL; aux = aux->prox){
	  
	  	if(aux->cod == codCarro && aux->disponivel){
	  		return aux;
	  	}
  	}
  
  	return NULL;
}

void StatusCarro(int codCarro, bool status){
	
	tbCarros *aux;		
	
   	for (aux = carros; aux != NULL; aux = aux->prox){
	  
	  	if(aux->cod == codCarro){
	  		aux->disponivel = status;
	  		return;
	  	}  
  	}  
}

////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
tbClientes cadastrarCliente(){	
	
	tbClientes client;
	
	do{
		char auxNum[5];
	
		printf("Digite o codigo do Cliente.\n");
		scanf("%s",auxNum);
		
		client.cod = atoi(auxNum);
		
		if(client.cod == 0){
			printf("\nDigite um numero maior que zero.\n");
		}
		
	}while(client.cod <= 0);
	
	
	do{	
		char auxOpcao;
		
	    printf("Tipo Cliente\n1-Fisica\n2-Juridica\n");
	    scanf(" %c", &auxOpcao);
	    
		if(isdigit(auxOpcao)){	
	    	if(auxOpcao == '1'){
				client.tpPessoa = 1;
			}else if(auxOpcao == '2'){			
				client.tpPessoa = 2;
			}
		}
	    
	    if(client.tpPessoa != 1 && client.tpPessoa != 2){
	    	printf("Opçao invalida. Digite 1 ou 2\n\n");
		}
	    
	}while(client.tpPessoa != 1 && client.tpPessoa != 2);

	printf("Digite o nome do Cliente.\n");
	scanf(" %[^\n]s",&client.nome); // expresão utilizada para ler todo o nome , só para quando encontrar o \n.	
	
	
	if(client.tpPessoa == 1){
		do{
			char auxNum[5];
		
			printf("Digite a idade do cliente.\n");
			scanf("%s",auxNum);
			
			client.idade = atoi(auxNum);
			
			if(client.idade == 0 || client.idade > 200){
				printf("\nDigite um numero valido (18 a 200).\n");
			}
			
		}while(client.idade < 18 || client.idade > 200);
	}
	else{
		client.idade = 0;
	}
	
	
	printf("Digite o documento.\n");
	scanf("%s",&client.doc);
	
	printf("Digite o telefone.\n");
	scanf("%s",&client.telefone);   
    
    return client;
}
////////////////////// DIARIAS ////////////////////////////////////////

void mostrarHora(tm* hora){
	
	int _hora = hora->tm_hour;
	int min  = hora->tm_min;
	int sec  = hora->tm_sec;
	
	printf("%d:%d:%d\n",_hora,min,sec);
	
}

void mostrarHora(tm hora){
	
	int _hora = hora.tm_hour;
	int min  = hora.tm_min;
	int sec  = hora.tm_sec;
	
	printf("%d:%d:%d\n",_hora,min,sec);
  
}

   
void mostrarData(tm* data){
  
	int dia = data->tm_mday;
	int mes = data->tm_mon + 1;
	int ano = data->tm_year + 1900;  
	
	printf("%d\\%d\\%d\n",dia,mes,ano);  
  
}

void mostrarData(tm data){
  
	int dia = data.tm_mday;
	int mes = data.tm_mon + 1;
	int ano = data.tm_year + 1900;  
	
	printf("%d\\%d\\%d\n",dia,mes,ano);  
  
}

void imprimeDiaria(tbDiarias* diaria){
	
	printf("Data retirada: ");
	mostrarData(diaria->dataRetirada);
	printf("Hora retirada: ");
	mostrarHora(diaria->dataRetirada);
	printf("Placa do Carro: %s\n",diaria->carro.placa);
	printf("Cliente: %s\n",diaria->cliente.nome);
	printf("Data devolucao: ");
	mostrarData(diaria->dtDevolucao);
	printf("Hora devolucao: ");
	mostrarHora(diaria->dtDevolucao);
	printf("\n\n");     
	
}

tbDiarias cadastrarDiaria(){	
	
	tbDiarias diaria;
	tbClientes *auxCliente = NULL;
	tbCarros *auxCarro = NULL;
	int cod;
	
	do{
	
		printf("Digite o codigo do Cliente.\n");
		scanf("%d",&cod); 
		
		auxCliente = getCliente(cod);
	
		if(auxCliente == NULL){
			printf(">>>>>>>>>>Nenhum cliente encontrado..<<<<<<<<<<\n\n\n");
		}
		
	}while(auxCliente == NULL);

    diaria.cliente = *auxCliente;
    
	printf("Digite o total de diarias.\n");
	scanf("%d",&diaria.qtdDiaria);
    
    do{
		
		printf("Digite o codigo do carro.\n");
		scanf("%d",&cod); // expresão utilizada para ler todo o nome , só para quando encontrar o \n.	
		
		auxCarro = getCarro(cod);
		
		if(auxCarro == NULL){
			printf(">>>>>>>>>>Nenhum carro encontrado com esse codigo ou carro ja foi alugado..\n\n\n<<<<<<<<<<");
		}
	
	}while(auxCarro == NULL);
     
	auxCarro->disponivel =false;
	auxCarro->dtDevolucao = verificarData(diaria.qtdDiaria);
	diaria.carro = *auxCarro;
	
	double value = auxCarro->vlrDiaria;	
	diaria.valorTotal = value * diaria.qtdDiaria; ///calcular desconto.

	if(diaria.cliente.idade >=60){
		diaria.valorTotal = diaria.valorTotal - ((diaria.valorTotal * DESC_IDOSO)/100);
	}
	
	if(diaria.cliente.tpPessoa == 2){
		diaria.valorTotal = diaria.valorTotal - ((diaria.valorTotal * DESC_EMPRESA)/100);
	}
    
    return diaria;
	
}


void insereDiaria (tbDiarias diaria)
{   
	tbDiarias *aux = (tbDiarias*)malloc(sizeof (tbDiarias)); 
	
	aux->qtdDiaria = diaria.qtdDiaria;   
	aux->valorTotal = diaria.valorTotal;
	aux->cliente = diaria.cliente;
	aux->carro = diaria.carro;  
	
	
	aux->dataRetirada = *
	getDataAtual();
	aux->dtDevolucao = verificarData(diaria.qtdDiaria);   
	aux->devolvido = false;
	
	imprimeDiaria(aux);
	
	if(diarias == NULL){
		diarias = aux;   	
		diarias->prox = NULL;
		return;
	}   
	
	aux->prox = diarias;
	diarias = aux;
}

/////////////////////////////////////////////////////////////
//////////////////////////// CLIENTES ///////////////////////

void insereCliente (tbClientes client)
{   
	tbClientes *aux = (tbClientes*)malloc(sizeof (tbClientes)); 
	strcpy(aux->nome,client.nome);   
	strcpy(aux->doc, client.doc);
	strcpy(aux->telefone, client.telefone);  
	aux->cod = client.cod; 
	aux->idade = client.idade;
	aux->tpPessoa = client.tpPessoa;
   
	if(clientes == NULL){
		clientes = aux;   	
		clientes->prox = NULL;
		return;
	}   
	
	aux->prox = clientes;
	clientes = aux;
}
//////////////////////////////////////////////////////////////

void listarClientes(){
	
	int cont =0;
	tbClientes *aux;	
	
	for (aux = clientes; aux != NULL; aux = aux->prox){
		cont++;
		printf("Cod: %d\n",aux->cod);
		printf("Nome: %s\n",aux->nome);
		printf("Idade: %d\n",aux->idade);
		printf("CPF/CNPJ: %s\n",aux->doc);
		printf("Telefone: %s\n\n",aux->telefone);      
	}
  
	printf (">>>>>>>>>>> Total de clientes cadastrados = %d <<<<<<<<<<<\n\n", cont);
   
}

int countClientes(){
	int cont =0;
	tbClientes *aux;	
	
	for (aux = clientes; aux != NULL; aux = aux->prox){
		cont++;     
	}
  
	return cont;
}

//////////////////////////////////////////////////////////////////////////////////////
void subMenuCliente(){
	
	char opcao;
	
	do{
		printf("1- Cadastrar Cliente.\n");
		printf("2- Listar Clientes\n");
		printf("9- Voltar\n\n");	
		
		scanf(" %c",&opcao); 
		
		if(isdigit(opcao)!=1 && isdigit(opcao)!=2)  {
			printf(">>>>>>Opcao invalida.Tente novamente.<<<<<<<<\n\n\n");
		}
	
		switch(opcao - 48){
			case 1:
				insereCliente(cadastrarCliente());
				break;
			case 2:
				listarClientes();
				break;
		}
		
	}while((opcao-48)!= SAIR );
}

////////////////////////////////////////////////////////////////

void mostrarCarros(bool status){ 
	
	int cont =0;
	tbCarros *aux;	
	
	for (aux = carros; aux != NULL; aux = aux->prox){   
	
		if(aux->disponivel == status){
			cont++;
			printf("Cod: %d\n",aux->cod);
			printf("Modelo: %s\n",aux->nome);
		
			if(aux->disponivel == false){
				printf("Data prevista para entrega: ");
				mostrarData(aux->dtDevolucao);
				printf("Hora prevista para entrega: ");
				mostrarHora(aux->dtDevolucao);
			}
		
			printf("Placa: %s\n",aux->placa);
			printf("Cor: %s\n",aux->cor);
			printf("Valor diaria: %.2f\n\n\n",aux->vlrDiaria);           
		}      
  	} 
  
	if(status){
		printf (">>>>>>>>>>> Total de carros disponiveis = %d <<<<<<<<<<<\n\n", cont);
	}
	else{
		printf (">>>>>>>>>>> Total de carros alugados = %d <<<<<<<<<<<\n\n", cont);
	}
  
  
}


void subMenuCarros(){
	
	printf("1- Carros disponiveis.\n");
	printf("2- Carros Alugados\n");
	
	char opcao;
	scanf(" %c",&opcao); 
		
	if(isdigit(opcao)!=1 && isdigit(opcao)!=2)  {
		printf("Opcao invalida.Tente novamente.\n\n");	//Caso o usuário digite letra o app não se perca no fluxo.
		return ;
	}	
	
	switch(opcao - 48){
		case 1:
			mostrarCarros(true);
			break;
			case 2:
				mostrarCarros(false);
				break;
		
	}
		
	return ;	
}




void mostrarDiarias(){
	
	int cont =0;
	tbDiarias *aux;	
	
	for (aux = diarias; aux != NULL; aux = aux->prox){
	  
		if(aux->devolvido == false){
		  cont++;
		  printf("Cliente: %s\n",aux->cliente.nome);
		  printf("Carro: %s\n",aux->carro.nome);
		  printf("Total de diarias: %d\n",aux->qtdDiaria);
		  printf("Valor : %.2f\n\n",aux->valorTotal);    
		}
	}
  
   printf (">>>>>>>>>>> Total de reservas = %d <<<<<<<<<<<\n\n", cont);
}

time_t getData(){
	
	time_t hoje;
	time(&hoje);
	
	return hoje; 
}

void liberarCarro(){	
	tbDiarias *aux;	
	int codCliente=0;
	int cont =0;

	
	printf("Digite o codigo do Cliente\n");
	scanf(" %d",&codCliente); 
	
   	for (aux = diarias; aux != NULL; aux = aux->prox){      
	  	cont++;
	  
	  	if(aux->cliente.cod == codCliente && aux->carro.disponivel != true){
	  	
		  	aux->carro.disponivel = true;
		  	
		  	double atraso =  difftime(getData(),mktime(aux->dtDevolucao));
		  	
		  	if(atraso > 0){  		
		  		
		  		int horas = atraso / SEGUNDOS;
		  		int valordiariaHora  = aux->carro.vlrDiaria / 12;
		  		
		  		printf("Entrega em atraso!\nValor da multa = %d\n",valordiariaHora*horas);
		  		aux->valorTotal = aux->valorTotal + (valordiariaHora*horas);
			}	  
		  
			StatusCarro(aux->carro.cod,true);
		   
		  	aux->devolvido = true;
			printf("Cliente: %s\n",aux->cliente.nome);
			printf("Carro: %s\n",aux->carro.nome);
			printf("Total de diarias: %d\n",aux->qtdDiaria);
			printf("Valor a pagar : %.2f\n\n",aux->valorTotal);
			return;
		}
	}
  
  	if(cont >0){
   		printf (">>>>>>>>>>> Nenhum cliente encontrado <<<<<<<<<<<\n\n");
	}else{
		printf (">>>>>>>>>>> Sem reservas cadastradas. <<<<<<<<<<<\n\n");
	}
}

//////////////////////////////////////////////////////////////////

void subMenuDiarias(){
	
	char opcao;
	
	do{
		printf("1- Cadastrar diaria.\n");
		printf("2- Mostrar diarias\n");
		printf("9- Voltar\n\n");	
		
		scanf(" %c",&opcao); 
			
		if(isdigit(opcao)!=1 && isdigit(opcao)!=2)  {
			printf(">>>>>>Opcao invalida.Tente novamente.<<<<<<<<\n\n\n");
		}
		
		switch(opcao - 48){	
			case 1:
				if(countClientes() == 0){
					printf(">>>>>>Cadastre pelo menos um cliente para cadastrar uma diaria.<<<<<<<<\n\n\n");
					opcao = '0';
				}else{
					insereDiaria(cadastrarDiaria());	
				}
				
				break;
			case 2:
				mostrarDiarias();
				break;
			
		}
		
	}while((opcao-48)!= SAIR );
	
}

/*
*
*
*   *************** Main Application *****************************
*
*
*
*
*/

int main(int argc, char** argv) {
	
	iniciarTabelaCarros();
	int botao = 0;	
	
	do{
	
		botao = inicioAplicacao();
		switch(botao){
			case CARROS:
				subMenuCarros();
				break;
				
			case CLIENTE:
				subMenuCliente();
				break;
					
			case DIARIA:
				subMenuDiarias();
				break;
						
			case DEVOLVER:
				liberarCarro();
				break;					
				
		}
	
		
	}while(botao != SAIR);
		
	system("pause");
	return 0;
}
