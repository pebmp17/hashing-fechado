#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define sizeHash 100
#define sizeRandom 50

struct tabela {
	int chaveCalc;
	int chaveRandom;
	char flag;
};

struct tabela tbl[sizeHash];

int randomNum[sizeRandom];

void insertRandom (int a[]) {
	srand(time(NULL));
	for (int i = 0; i < sizeRandom; ++i)
		a[i] = rand() % 1000;
}

void insertHash(int a[], struct tabela t[]) {
	int n;
	for (int i = 0; i < sizeRandom; i++)
	{
		n = a[i] % sizeHash - 1;
		for (int h = n; h < sizeHash; h++)
		{
			if ((t[h].flag == '0') || (t[h].flag == '1')) {
				t[h].chaveCalc = n;
				t[h].chaveRandom = a[i];
				t[h].flag = ' ';
				if (h != n) t[h].flag = '*';
				break;
			}
		}
	}
}

int proximoDeslocado (int pos, struct tabela tb[]) {
	for (int h = pos; h < sizeHash; ++h)
	{
		if ((tb[h].chaveCalc == pos) && (tb[h].flag == '*')) {
			tb[pos].chaveRandom = tb[h].chaveRandom;
			tb[pos].chaveCalc = tb[h].chaveCalc;
			tb[pos].flag = ' ';
			tb[h].chaveCalc = 0;
			tb[h].chaveRandom = 0;
			tb[h].flag = '1';
			return proximoDeslocado (h, tb);
		}
	}
	return 0;
}

void remover(struct tabela t[]) {
	int num, find;
	printf("Digite o numero a ser removido: ");
	scanf ("%d", &num);
	find = -1;
	for (int i = 0; i < sizeHash; ++i)
	{
		if (t[i].chaveRandom == num) {
			t[i].chaveCalc = 0;
			t[i].chaveRandom = 0;
			t[i].flag = '1';
			proximoDeslocado(i, t);
			find = i;
		}
	}
	if (find == -1) printf("Numero não encontrado\n");
	else printf("Numero removido com sucesso \n");
}

void exibirTabela(struct tabela t[]) {
	for (int i = 0; i < sizeHash; ++i)
	{
		if (i == 0) printf("----------------------------------- \n");
		printf("%d --- | %d | %d | %c |\n", i, t[i].chaveCalc, t[i].chaveRandom, t[i].flag);
		if (i == sizeHash - 1) printf("----------------------------------- \n");
	}
}

int main(void) {
	int menu = 0 ;
	insertRandom(randomNum);
	for (int i = 0; i < sizeHash; ++i) tbl[i].flag = '0';
	insertHash(randomNum, tbl);
	while (menu == 0) {
		int opt;
		printf ("1.Exibir tabela \n");
		printf ("2.Realizar uma exclusão \n");
		printf ("3.Sair \n");
		scanf ("%d", &opt);
		switch (opt) {
		case 1: exibirTabela(tbl); break;
		case 2: remover(tbl); break;
		case 3: menu = 1; break;
		}
	}
	return 0;
}
