#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100

// Struct para itens
// Arthur
struct Itens {
  char nome[20];
  float preco_unit;
  int codigo;
  char marca[20];
  int quantidade_vendida;
  float preco_pago;
};

// Fun��o para registrar as informa��es no arquivo "loja_roupa.dat"
void registrarVendaNoArquivo(FILE *arquivo, struct Itens i) {
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }
  fwrite(&i, sizeof(struct Itens), 1, arquivo);
}

// Fun��o para identificar o item mais vendido
// Jansen
void MaisVendido(struct Itens *itens, int num_itens) {
  int i, mais_vendido_index = 0;
  int mais_vendido_quantidade = itens[0].quantidade_vendida;

  for (i = 1; i < num_itens; i++) {
    if (itens[i].quantidade_vendida > mais_vendido_quantidade) {
      mais_vendido_index = i;
      mais_vendido_quantidade = itens[i].quantidade_vendida;
    }
  }

  printf("O item mais vendido foi: %s da %s\n", itens[mais_vendido_index].nome,
         itens[mais_vendido_index].marca);
}

// Fun��o para identificar o item menos vendido
// Jansen
void MenosVendido(struct Itens *itens, int num_itens) {
  int i, menos_vendido_index = 0;
  int menos_vendido_quantidade = itens[0].quantidade_vendida;

  for (i = 1; i < num_itens; i++) {
    if (itens[i].quantidade_vendida < menos_vendido_quantidade) {
      menos_vendido_index = i;
      menos_vendido_quantidade = itens[i].quantidade_vendida;
    }
  }

  printf("O item menos vendido foi: %s da %s\n",
         itens[menos_vendido_index].nome, itens[menos_vendido_index].marca);
}

// Fun��o pra imprimir relat�rios puxando do .dat
// Arthur
void exibirRelatorio(int num_item) {
  FILE *arquivo;
  struct Itens itens[MAX_ITEMS];

  arquivo = fopen("loja_roupa.dat", "rb");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  printf("\nRelat�rio de Vendas:\n\n");

  int total_itens_vendidos = 0;
  int total_clientes = 0;
  float faturamento = 0;

  // L� e exibe os dados de cada venda no arquivo
  // Jansen e Arthur
  for (int i = 0; i < num_item; i++) {
    while (fread(&itens[i], sizeof(struct Itens), 1, arquivo) != 0) {
      printf("C�digo do Produto: %d\nNome do Produto: %s\nMarca do Produto: "
             "%s\nQuantidade vendida: %d\nPre�o unit�rio: %.2f\nPre�o pago: R$ "
             "%.2f\n\n",
             itens[i].codigo, itens[i].nome, itens[i].marca,
             itens[i].quantidade_vendida, itens[i].preco_unit,
             itens[i].preco_pago);
      total_itens_vendidos += itens[i].quantidade_vendida;
      faturamento += itens[i].preco_pago;
      total_clientes++;
    }
  }

  printf("\nQuantidade total de itens vendidos: %d\nQuantidade de clientes que "
         "realizaram compras: %d\nFaturamento bruto total da loja: R$ %.2f\n",
         total_itens_vendidos, total_clientes, faturamento);
  fclose(arquivo);
}

// Algoritmo de ordena��o por pre�o pago
// Miguel
int compareItens(const void *a, const void *b) {
  const struct Itens *item1 = (const struct Itens *)a;
  const struct Itens *item2 = (const struct Itens *)b;
  if (item1->preco_pago < item2->preco_pago) {
    return 1;
  } else if (item1->preco_pago > item2->preco_pago) {
    return -1;
  } else {
    return 0;
  }
}

// Fun��o para calcular pre�o pago
// Arthur
float precoPago(float b, float c) {
  if (c >= 3) {
    printf("Voc� ganhou um desconto de 10%% pois comprou 3 ou mais itens!\n");
    return b * c * 0.9; // Desconto de 10%
  } else {
    return b * c;
  }
}

// Formata��o
// Jansen
void capitalizeString(char *str) {
  if (str == NULL)
    return;

  int boolean = 1;
  for (int i = 0; str[i] != '\0'; i++) {
    if (boolean && islower(str[i])) {
      str[i] = toupper(str[i]);
      boolean = 0;
    } else if (boolean == 0) {
      str[i] = tolower(str[i]);
    } else if (str[i] == ' ') {
      boolean = 1;
    } else {
      boolean = 0;
    }
  }
}

// Fun��o principal e in�cio do programa
// Arthur
int main() {
  setlocale(LC_ALL, "portuguese");

  int escolha, opcao_item, i;
  struct Itens item[MAX_ITEMS];
  int num_item = 0;
  char nome[20], marca[20];
  float preco_unit, preco_pago;
  int codigo, quantidade_vendida;

  FILE *arquivo;
  arquivo = fopen("loja_roupa.dat", "w+b");

  while (num_item < MAX_ITEMS) {
    printf("\n* * * * * * Registro de Vendas* * * * * *\n\n");
    printf(
        "Digite 1 para registrar uma venda ou digite 2 para encerrar o dia: ");
    scanf("%d", &escolha);
    if (escolha == 1) {

      printf("Qual Item deseja cadastrar? ");
      scanf("%s", nome);
      capitalizeString(nome);
      printf("Qual a marca do item? ");
      scanf("%s", marca);
      capitalizeString(marca);
      printf("Qual o pre�o do item? R$ ");
      scanf("%f", &preco_unit);
      printf("Quantos itens foram vendidos? ");
      scanf("%d", &quantidade_vendida);
      printf("Qual o c�digo do item? ");
      scanf("%d", &codigo);
      preco_pago = precoPago(preco_unit, quantidade_vendida);

      printf("Pre�o pago: R$ %.2f\n", preco_pago);

      printf("\nVenda registrada.\n");

      // Dados armazenados por �ndice 
      strcpy(item[num_item].nome, nome);
      strcpy(item[num_item].marca, marca);
      item[num_item].preco_unit = preco_unit;
      item[num_item].preco_pago = preco_pago;
      item[num_item].quantidade_vendida = quantidade_vendida;
      item[num_item].codigo = codigo;

      num_item++;
    } else if (escolha == 2) {
      qsort(item, num_item, sizeof(struct Itens), compareItens);
      for (i = 0; i < num_item; i++) {
        registrarVendaNoArquivo(arquivo, item[i]);
      }
      printf("\n\n---------------Encerrando dia.---------------\n");
      fclose(arquivo);
      exibirRelatorio(num_item);
      MaisVendido(item, num_item);
      MenosVendido(item, num_item);
      break;
    } else {
      printf("\nOP��O INV�LIDA. DIGITE 1 OU 2.\n");
    }
  }
} 
