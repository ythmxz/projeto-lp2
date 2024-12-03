#include <stdio.h>
#include <stdlib.h>


FILE *p_arquivo;

const int LIMITE_DESPESA = 100;

int flag = 0;

typedef struct {

	char categoria[31];
	double valor;
	int dia;

} registro;


void criarRegistro(registro *despesa);

void salvarDados(registro *despesa, int tamanho);
void carregarDados(registro *despesa, int tamanho);

void adicionarDespesa(registro **p_despesa, int *p_tamanho);
void removerDespesa(registro **p_despesa, int *p_tamanho, int remover);
void editarDespesa(registro *despesa, int editar);
void mostrarDespesa(registro *despesa, int *p_tamanho);

double somarGastos(registro *despesa, int *p_tamanho);


int main() {

	int tamanho = 1;
	int *p_tamanho = &tamanho;

	int menu = 1;
	int remover = 0, editar = 0;

	registro *despesa = (registro*)malloc(*p_tamanho * sizeof(registro));

	if ( despesa == NULL ) {

		printf("\n-----------------------------------------------------------------\n");
		printf("Erro de alocação! Encerrando programa.");
		printf("\n-----------------------------------------------------------------\n");
		return 1;

	}

	registro **p_despesa = &despesa;

	printf("\n-----------------------------------------------------------------\n");
	printf("GERENCIADOR DE DESPESAS v1.0.0");
	printf("\n-----------------------------------------------------------------\n");

	carregarDados(despesa, *p_tamanho);

	if ( flag == 1 ) {

		criarRegistro(despesa);
		salvarDados(despesa, *p_tamanho);

		flag = 0;

	}


	printf("\n-----------------------------------------------------------------\n");

	while ( menu != 0 ) {

		printf("\nO que você deseja fazer agora?\n");
		printf("\n0 = Encerrar programa\n1 = Adicionar despesa\n2 = Remover despesa"
				"\n3 = Editar despesa\n4 = Mostrar despesas\n");
		printf("\nResposta: ");
		scanf("%d", &menu);

		printf("\n-----------------------------------------------------------------\n");

		if ( menu == 1 ) {

			adicionarDespesa(p_despesa,p_tamanho);
			salvarDados(despesa, *p_tamanho);

			printf("\n-----------------------------------------------------------------\n");

		}

		else if ( menu == 2 ) {

			removerDespesa(p_despesa, p_tamanho, remover);
			salvarDados(despesa, *p_tamanho);
			printf("\n-----------------------------------------------------------------\n");

		}

		else if ( menu == 3 ) {

			editarDespesa(despesa, editar);
			salvarDados(despesa, *p_tamanho);
			printf("\n-----------------------------------------------------------------\n");

		}

		else if ( menu == 4 ) {
			mostrarDespesa(despesa, p_tamanho);
			printf("\n-----------------------------------------------------------------\n");

		}

	}

	free(despesa);

	return 0;

}

void salvarDados(registro *despesa, int tamanho) {

	p_arquivo = fopen("despesas.bin", "wb");

	printf("\nSalvando dados...\n");

	fwrite(&tamanho, sizeof(int), 1, p_arquivo);
	fwrite(despesa, sizeof(registro),tamanho, p_arquivo);

	printf("\nDados salvos!\n");

	fclose(p_arquivo);

}


void carregarDados(registro *despesa, int tamanho) {

	p_arquivo = fopen("despesas.bin", "rb");

	if ( p_arquivo == NULL ) {

		printf("\nCriando arquivo...\n");
		p_arquivo = fopen("despesas.bin", "wb");
		printf("\nArquivo criado!\n");

		flag = 1;

	}

	else {

		printf("\nCarregando dados...\n");

		fread(&tamanho, sizeof(int), 1, p_arquivo);
		fread(despesa, sizeof(registro), tamanho, p_arquivo);

		printf("\nDados carregados!\n");

	}

	fclose(p_arquivo);

}


void criarRegistro(registro *despesa) {

	int i = 0;

	printf("\nDespesa %d\n", (i + 1));

	printf("\nCategoria: ");
	scanf("%s", despesa[i].categoria);

	printf("Valor: R$");
	scanf("%lf", &despesa[i].valor);

	printf("Dia: ");
	scanf("%d", &despesa[i].dia);

}


void adicionarDespesa(registro **p_despesa, int *p_tamanho) {

	int tamanhoAtual = *p_tamanho;
	int tamanhoNovo = (tamanhoAtual + 1);

	*p_despesa = (registro*)realloc(*p_despesa, (tamanhoNovo * sizeof(registro)));

	if ( p_despesa == NULL ) {

		printf("\n-----------------------------------------------------------------\n");
		printf("Erro de realocação! Encerrando programa.");
		printf("\n-----------------------------------------------------------------\n");
		return;

	}

	printf("\nDespesa %d\n", (tamanhoAtual + 1));

	printf("\nCategoria: ");
	scanf("%s", (*p_despesa)[tamanhoAtual].categoria);

	printf("Valor: R$");
	scanf("%lf", &(*p_despesa)[tamanhoAtual].valor);

	printf("Dia: ");
	scanf("%d", &(*p_despesa)[tamanhoAtual].dia);

	*p_tamanho += 1;

}


void removerDespesa(registro **p_despesa, int *p_tamanho, int remover) {

ENTRADA_REMOVER:

	printf("\nInsira a despesa que deseja remover: ");
	scanf("%d", &remover);

	while ( remover <= 0 || remover > LIMITE_DESPESA ) {

		printf("\n-----------------------------------------------------------------\n");
		printf("\nValor inválido! Tente novamente.\n");
		printf("\n-----------------------------------------------------------------\n");
		goto ENTRADA_REMOVER;

	}

	int tamanhoAtual = *p_tamanho;
	int tamanhoNovo = (tamanhoAtual - 1);

	remover -= 1;

	printf("\nRemovendo Despesa %d\n", (remover + 1));

	printf("\nCategoria: %s", (*p_despesa)[remover].categoria);
	printf("\nValor: R$%.2lf", (*p_despesa)[remover].valor);
	printf("\nDia: %02d\n", (*p_despesa)[remover].dia);

	for( int i = remover; i < tamanhoNovo; i++ )
		(*p_despesa)[i] = (*p_despesa)[i + 1];

	*p_tamanho -= 1;

	*p_despesa = (registro*)realloc(*p_despesa, (tamanhoNovo * sizeof(registro)));

	if ( p_despesa == NULL ) {

		printf("\n-----------------------------------------------------------------\n");
		printf("Erro de realocação! Encerrando programa.");
		printf("\n-----------------------------------------------------------------\n");
		return;

	}

}


void editarDespesa(registro *despesa, int editar) {

ENTRADA_EDITAR:

	printf("\nInsira a despesa que deseja editar: ");
	scanf("%d", &editar);

	while ( editar <= 0 || editar > LIMITE_DESPESA ) {

		printf("\n-----------------------------------------------------------------\n");
		printf("\nValor inválido! Tente novamente.\n");
		printf("\n-----------------------------------------------------------------\n");
		goto ENTRADA_EDITAR;

	}

	editar -= 1;

	printf("\nEditando Despesa %d\n", (editar + 1));

	printf("\nCategoria: %s", despesa[editar].categoria);
	printf("\nValor: R$%.2lf", despesa[editar].valor);
	printf("\nDia: %02d\n", despesa[editar].dia);

	printf("\nDespesa %d\n", (editar + 1));

	printf("\nCategoria: ");
	scanf("%s", despesa[editar].categoria);

	printf("Valor: R$");
	scanf("%lf", &despesa[editar].valor);

	printf("Dia: ");
	scanf("%d", &despesa[editar].dia);

}


void mostrarDespesa(registro *despesa, int *p_tamanho) {

	for ( int i = 0; i < *p_tamanho; i++ ) {

		printf("\nDespesa %d\n", (i + 1));

		printf("\nCategoria: %s", despesa[i].categoria);
		printf("\nValor: R$%.2lf", despesa[i].valor);
		printf("\nDia: %02d\n", despesa[i].dia);

	}

	printf("\nTotal gasto: R$%.2lf\n", somarGastos(despesa, p_tamanho));

}


double somarGastos(registro *despesa, int *p_tamanho) {

	double soma;

	for ( int i = 0; i < *p_tamanho; i++ )
		soma += despesa[i].valor;

	return soma;

}
