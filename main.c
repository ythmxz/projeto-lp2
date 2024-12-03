#include <stdio.h>
#include <stdlib.h>

FILE *p_arquivo;

int flag = 0;

typedef struct {

	char categoria[31];
	double valor;
	int dia;

} registro;


void criarRegistro(registro *despesa);

void salvarDados(registro *despesa, int *p_tamanho);
void carregarDados(registro *despesa, int *p_tamanho);

void adicionarDespesa(registro **p_despesa, int *p_tamanho);
void removerDespesa(registro **p_despesa, int *p_tamanho, int remover);
void editarDespesa(registro *despesa, int *p_tamanho, int editar);
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
		printf("\033[1;31mErro de alocação! Encerrando programa.\033[0m");
		printf("\n-----------------------------------------------------------------\n");
		return 1;

	}

	registro **p_despesa = &despesa;

	printf("\n-----------------------------------------------------------------\n");
	printf("GERENCIADOR DE DESPESAS v1.0.5");
	printf("\n-----------------------------------------------------------------\n");

	carregarDados(despesa, p_tamanho);

	if ( flag == 1 ) {

		printf("\nOlá, seja bem-vindo(a) ao gerenciador de despesas! Para começar "
				"vamos criar sua primeira despesa.\n");

		criarRegistro(despesa);
		salvarDados(despesa, p_tamanho);

		flag = 0;

	}


	printf("\n-----------------------------------------------------------------\n");

	while ( menu != 0 ) {

		printf("\nO que você deseja fazer agora?\n");
		printf("\n0 - Encerrar programa\n1 - Adicionar despesa\n2 - Remover despesa"
				"\n3 - Editar despesa\n4 - Mostrar despesas\n");
		printf("\n\033[33mResposta:\033[0m ");
		scanf("%d", &menu);

		printf("\n-----------------------------------------------------------------\n");

		if ( menu == 1 ) {

			system("cls || clear");
			adicionarDespesa(p_despesa,p_tamanho);
			salvarDados(despesa, p_tamanho);
			printf("\n-----------------------------------------------------------------\n");

		}

		else if ( menu == 2 ) {

			system("cls || clear");
			removerDespesa(p_despesa, p_tamanho, remover);
			salvarDados(despesa, p_tamanho);
			printf("\n-----------------------------------------------------------------\n");

		}

		else if ( menu == 3 ) {

			system("cls || clear");
			editarDespesa(despesa, p_tamanho, editar);
			salvarDados(despesa, p_tamanho);
			printf("\n-----------------------------------------------------------------\n");

		}

		else if ( menu == 4 ) {

			system("cls || clear");
			mostrarDespesa(despesa, p_tamanho);
			printf("\n-----------------------------------------------------------------\n");

		}

	}

	free(despesa);

	return 0;

}

void salvarDados(registro *despesa, int *p_tamanho) {

	p_arquivo = fopen("despesas.bin", "wb");

	printf("\n\033[33mSalvando dados...\033[0m");

	fwrite(p_tamanho, sizeof(int), 1, p_arquivo);
	fwrite(despesa, sizeof(registro),*p_tamanho, p_arquivo);

	printf("\r\033[2K\033[32mDados salvos!\033[0m\n");

	fclose(p_arquivo);

}


void carregarDados(registro *despesa, int *p_tamanho) {

	p_arquivo = fopen("despesas.bin", "rb");

	if ( p_arquivo == NULL ) {

		printf("\n\033[33mCriando arquivo...\033[0m");
		p_arquivo = fopen("despesas.bin", "wb");
		printf("\r\033[2K\033[32mArquivo criado!\033[0m\n");

		flag = 1;

	}

	else {

		printf("\n\033[33mCarregando dados...\033[0m");

		fread(p_tamanho, sizeof(int), 1, p_arquivo);
		fread(despesa, sizeof(registro), *p_tamanho, p_arquivo);

		printf("\r\033[2K\033[32mDados carregados!\033[0m\n");

	}

	fclose(p_arquivo);

}


void criarRegistro(registro *despesa) {

	int i = 0;

	printf("\n\033[1;34mDESPESA %d:\033[0m\n", (i + 1));

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
		printf("\033[1;31mErro de realocação! Encerrando programa.\033[0m");
		printf("\n-----------------------------------------------------------------\n");
		return;

	}

	printf("\n\033[1;34mDESPESA %d\033[0m\n", (tamanhoAtual + 1));

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

	while ( remover <= 0 || remover > *p_tamanho ) {

		printf("\n-----------------------------------------------------------------\n");
		printf("\033[1;31mValor inválido! Tente novamente.\033[0m");
		printf("\n-----------------------------------------------------------------\n");
		goto ENTRADA_REMOVER;

	}

	int tamanhoAtual = *p_tamanho;
	int tamanhoNovo = (tamanhoAtual - 1);

	remover -= 1;

	printf("\n\033[1mREMOVENDO DESPESA %d:\033[0m\n", (remover + 1));

	printf("\nCategoria: %s", (*p_despesa)[remover].categoria);
	printf("\nValor: R$%.2lf", (*p_despesa)[remover].valor);
	printf("\nDia: %02d\n", (*p_despesa)[remover].dia);

	for( int i = remover; i < tamanhoNovo; i++ )
		(*p_despesa)[i] = (*p_despesa)[i + 1];

	*p_tamanho -= 1;

	*p_despesa = (registro*)realloc(*p_despesa, (tamanhoNovo * sizeof(registro)));

	if ( p_despesa == NULL ) {

		printf("\n-----------------------------------------------------------------\n");
		printf("\033[1;31mErro de realocação! Encerrando programa.\033[0m");
		printf("\n-----------------------------------------------------------------\n");
		return;

	}

}


void editarDespesa(registro *despesa, int *p_tamanho, int editar) {

ENTRADA_EDITAR:

	printf("\nInsira a despesa que deseja editar: ");
	scanf("%d", &editar);

	while ( editar <= 0 || editar > *p_tamanho ) {

		printf("\n-----------------------------------------------------------------\n");
		printf("\033[1;31mValor inválido! Tente novamente.\033[0m");
		printf("\n-----------------------------------------------------------------\n");
		goto ENTRADA_EDITAR;

	}

	editar -= 1;

	printf("\n\033[1mEDITANDO DESPESA %d:\033[0m\n", (editar + 1));

	printf("\nCategoria: %s", despesa[editar].categoria);
	printf("\nValor: \033[31mR$%.2lf\033[0m", despesa[editar].valor);
	printf("\nDia: %02d\n", despesa[editar].dia);

	printf("\n\033[1;34mDESPESA %d\033[0m\n", (editar + 1));

	printf("\nCategoria: ");
	scanf("%s", despesa[editar].categoria);

	printf("Valor: R$");
	scanf("%lf", &despesa[editar].valor);

	printf("Dia: ");
	scanf("%d", &despesa[editar].dia);

}


void mostrarDespesa(registro *despesa, int *p_tamanho) {

	for ( int i = 0; i < *p_tamanho; i++ ) {

		printf("\n\033[1;34mDESPESA %d\033[0m\n", (i + 1));

		printf("\nCategoria: %s", despesa[i].categoria);
		printf("\nValor: \033[31mR$%.2lf\033[0m", despesa[i].valor);
		printf("\nDia: %02d\n", despesa[i].dia);

	}

	printf("\nTotal gasto: \033[31mR$%.2lf\033[0m\n", somarGastos(despesa, p_tamanho));

}


double somarGastos(registro *despesa, int *p_tamanho) {

	double soma;

	for ( int i = 0; i < *p_tamanho; i++ )
		soma += despesa[i].valor;

	return soma;

}
