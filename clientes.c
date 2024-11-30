#include <stdio.h>
#include <stdlib.h>


const int LIMITE_CLIENTES = 100;

typedef struct {

	char nome[51];
	int id;
	double carteira;

} registro;


void criarRegistro(registro *p_cliente, int tamanho);
void expandirRegistro(registro *cliente, int tamanhoAtual, int adicionado);
void reduzirRegistro(registro *cliente, int tamanhoAtual, int removido);
void editarRegistro(registro *cliente, int editado);
void mostrarRegistro(registro *p_cliente, int tamanho);


int main() {

	int tamanho;
	int opcao;
	int adicionado, removido, editado;

INICIO:

	printf("\nREGISTRO DE CLIENTES v1.0.4\n");

	printf("\n-----------------------------------------------------------------\n");

ENTRADA_TAMANHO:

	printf("\nDigite o tamanho inicial do registro: ");
	scanf("%d", &tamanho);

	while ( tamanho <= 0  || tamanho > LIMITE_CLIENTES) {

		printf("\nTamanho inválido!\n");
		goto ENTRADA_TAMANHO;

	}

	registro *cliente = (registro*)malloc(tamanho * sizeof(registro));

	printf("\n-----------------------------------------------------------------\n");

	criarRegistro(cliente, tamanho);
	system("cls");

	printf("\n-----------------------------------------------------------------\n");

	mostrarRegistro(cliente, tamanho);

	printf("\n-----------------------------------------------------------------\n");

MENU:

	printf("\nO que deseja fazer:\n");
	printf("\n1 - Adicionar cliente(s)\n2 - Remover cliente\n3 - Editar cliente"
			"\n4 - Visualizar registro\n5 - Resetar registro\n6 - Sair\n");

	printf("\nResposta: ");
	scanf("%d", &opcao);
	system("cls");

	printf("\n-----------------------------------------------------------------\n");

	switch ( opcao ) {

		case 1:

		ENTRADA_ADICIONADO:

			printf("\nDigite a quantidade de clientes que deseja adicionar: ");
			scanf("%d", &adicionado);

			while ( adicionado <= 0 || (tamanho + adicionado) > LIMITE_CLIENTES ) {

				printf("Quantidade inválida! Tente novamente.");
				goto ENTRADA_ADICIONADO;

			}

			printf("\n-----------------------------------------------------------------\n");

			expandirRegistro(cliente, tamanho, adicionado);
			tamanho += adicionado;

			printf("\n-----------------------------------------------------------------\n");

			goto MENU;

		case 2:

		ENTRADA_REMOVIDO:

			printf("\nDigite o cliente que deseja remover: ");
			scanf("%d", &removido);

			while ( removido <= 0 || removido >= tamanho ) {

				printf("Quantidade inválida! Tente novamente.");
				goto ENTRADA_REMOVIDO;

			}

			printf("\n-----------------------------------------------------------------\n");

			reduzirRegistro(cliente, tamanho, removido);
			tamanho -= 1;

			printf("\n-----------------------------------------------------------------\n");

			goto MENU;

		case 3:

		ENTRADA_EDITADO:

			printf("\nDigite o cliente que deseja editar: ");
			scanf("%d", &editado);

			while ( editado <= 0 || editado > tamanho ) {

				printf("Quantidade inválida! Tente novamente.");
				goto ENTRADA_EDITADO;

			}

			printf("\n-----------------------------------------------------------------\n");

			editarRegistro(cliente, editado);

			printf("\n-----------------------------------------------------------------\n");

			goto MENU;

		case 4:

			mostrarRegistro(cliente, tamanho);

			printf("\n-----------------------------------------------------------------\n");

			goto MENU;

		case 5:

			goto INICIO;

		case 6:

			break;

	}

	free(cliente);

	return 0;

}


void criarRegistro(registro *cliente, int tamanho) {

	for ( int i = 0; i < tamanho; i++ ) {

		printf("\nCliente %d\n", (i + 1));

		printf("\nDigite o nome: ");
		scanf("%50s", cliente[i].nome);

		printf("Digite o ID: ");
		scanf("%d", &cliente[i].id);

		printf("Digite o saldo: ");
		scanf("%lf", &cliente[i].carteira);

	}

}


void expandirRegistro(registro *cliente, int tamanhoAtual, int adicionado) {

	printf("\nAdicionar %d Cliente(s):\n", adicionado);

	int tamanhoNovo = (tamanhoAtual + adicionado);

	cliente = (registro*)realloc(cliente, tamanhoNovo * sizeof(registro));

	for ( int i = tamanhoAtual; i < tamanhoNovo; i++ ) {

		printf("\nCliente %d\n", (i + 1));

		printf("\nDigite o nome: ");
		scanf("%50s", cliente[i].nome);

		printf("Digite o ID: ");
		scanf("%d", &cliente[i].id);

		printf("Digite o saldo: ");
		scanf("%lf", &cliente[i].carteira);

	}

}


void reduzirRegistro(registro *cliente, int tamanhoAtual, int removido) {

	printf("\nRemover Cliente %d:\n", (removido));

	printf("\nNome: %s\n", cliente[removido - 1].nome);
	printf("ID: %02d\n", cliente[removido - 1].id);
	printf("Carteira: %.2lf\n", cliente[removido - 1].carteira);

	int tamanhoNovo= (tamanhoAtual - 1);

	registro temp;

	temp = cliente[tamanhoAtual - 1];
	cliente[tamanhoAtual - 1] = cliente[removido - 1];
	cliente[removido - 1] = temp;

	cliente = (registro*)realloc(cliente, tamanhoNovo * sizeof(registro));

}


void editarRegistro(registro *cliente, int editado) {

	printf("\nEditar Cliente %d:\n", (editado));

	printf("\nNome: %s\n", cliente[editado - 1].nome);
	printf("ID: %02d\n", cliente[editado - 1].id);
	printf("Carteira: %.2lf\n", cliente[editado - 1].carteira);

	printf("\nNovos dados:\n");

	printf("\nCliente %d\n", (editado));

	printf("\nDigite o nome: ");
	scanf("%50s", cliente[editado - 1].nome);

	printf("Digite o ID: ");
	scanf("%d", &cliente[editado - 1].id);

	printf("Digite o saldo: ");
	scanf("%lf", &cliente[editado - 1].carteira);

}


void mostrarRegistro(registro *cliente, int tamanho) {

	printf("\ntamanho = %d\n", tamanho);

	printf("\nRegistro atual:\n");

	for ( int i = 0; i < tamanho; i++ ) {

		printf("\nCliente %d\n", (i + 1));

		printf("\nNome: %s\n", cliente[i].nome);
		printf("ID: %02d\n", cliente[i].id);
		printf("Carteira: %.2lf\n", cliente[i].carteira);

	}

}
