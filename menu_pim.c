//Comentando o programa para o restante dos integrantes do grupo entender, favor ignorar os comentários

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#include <ctype.h>

#define CLEAN_BUFF                                  \
	do                                              \
	{                                               \
		int c;                                      \
		while ((c = getchar()) != '\n' && c != EOF) \
			;                                       \
	} while (0) //Limpa buffers do teclado

#define MAX_SENHA 14 //Definindo Max_Senha como 13
#define MAX_LOGIN 50 //Definindo Max_Login como 50

int Usuario(FILE *file, char *user, char *senha) //Verifica se é um usuario valido
{
	char tmpLogin[MAX_LOGIN];
	char tmpSenha[MAX_SENHA];

	fscanf(file, "%s", tmpLogin);

	while (!feof(file))
	{
		if (!strcmp(tmpLogin, user))
		{
			fscanf(file, "%s", tmpSenha);

			if (!strcmp(tmpSenha, senha))
				return 1;
		}
		else
		{
			fscanf(file, "%*s");
		}

		fscanf(file, "%s", tmpLogin);
	}

	return 0;
}

char *CriaSenha() //Alocando espaço para um bloco de bytes consecutivos na memoria ram e devolvendo indereço
{
	register int i;
	char digitado[50];

	char *senha = (char *)malloc(sizeof *senha * MAX_SENHA);

	if (senha == 8 && i)
	{
		digitado[i] = '\0';
		i--;
		printf("\b \b");
	}

	for (i = 0; i < MAX_SENHA; i++)
	{
		senha[i] = getche();
		if (senha[i] == '\r')
			break;
	}
	{
	}
	senha[i] = '\0';
	if (senha == 8 && i)
	{
		digitado[i] = '\0';
		i--;
		printf("\b \b");
	}

	return senha;
}

int main()
{									   //Definindo variaveis
	FILE *fpIN;						   //ponteiro para arquivo de entrada de clientes
	FILE *valores;					   //ponteiro para arquivo de relatório
	FILE *funcionarios;				   //ponteiro para arquivo de entrada de funcionários
	float num1, num2, num3, resultado; //resultado é o valor total do aluguel
	num2 = 10;						   // num2 é o valor do aluguel da maquina em horas, no caso 10 reais
	num3 = 60;						   // Num3 são os minutos pretendidos para o aluguel
	int opcao = 0;
	int opcao1 = 0;
	char *dia[10];
	char *user = (char *)malloc(sizeof *user * MAX_LOGIN);
	char *senha,
		*confirmaSenha;
	int i = 0;
	char digitado[50];
	do
	{
		setlocale(LC_ALL, "Portuguese");
		puts("\nEscolha uma opcao:");
		puts("\n 1- para login de funcionario\n 2- para cadastro de funcionario\n 3 - Para fechar o programa");
		scanf("%d", &opcao1);
		CLEAN_BUFF;
		switch (opcao1) //"Escolha caso"
		{
		case 1: /*Caso opcao1 for igual a 1, ele escolhe Login de funcionário. verificar se usuário existe na pasta funcionários;
			          */
			setlocale(LC_ALL, "Portuguese");
			printf("Usuario: ");
			gets(user);
			printf("Senha: ");
			senha = CriaSenha();

			funcionarios = fopen("funcionarios.txt", "a+");
			printf("\nUsuario %sconfirmado.\n", Usuario(funcionarios, user, senha) ? "" : "");
			fclose(funcionarios);

			free(senha);
			do
			{
				setlocale(LC_ALL, "Portuguese");
				puts("\nEscolha uma opcao:");
				puts("\n 1- para login de cliente\n 2- para cadastro de cliente\n 3- para relatorios\n 4- Para finalizar o programa");
				scanf("%d", &opcao);
				CLEAN_BUFF;
				switch (opcao) //"Escolha caso"
				{
				case 1: /*Caso opcao for igual a 1, ele escolhe Login de Cliente, ler informações para realizar Login e indentifica se o usuario é valor 
							 inicia conta para determinar valor do aluguel da maquina e armazena valor arrecadado em "relatorio.txt"*/
					setlocale(LC_ALL, "Portuguese");
					printf("Usuario: ");
					gets(user);
					printf("CPF: ");
					senha = CriaSenha();

					fpIN = fopen("usuarios.txt", "a+");
					printf("\nUsuario %sconfirmado.\n", Usuario(fpIN, user, senha) ? "" : "não ");
					fclose(fpIN);

					free(senha);
					//Calculo de valor do aluguel da maquina de lavar
					printf("Entre com a data de hoje:");
					scanf("%s", &dia);
					valores = fopen("relatorio.txt", "a+");
					fprintf(valores, "\n %s:\n", dia);
					fclose(valores);
					printf("\n Digite o tempo que vai usar a maquina em minutos:\n"); // minutos que vai usar
					scanf("%f", &num1);
					if (num1 > 0)
					{
						resultado = (num1 * num2) / num3;
						printf("\n O valor a pagar e : %.2f reais", resultado);
						valores = fopen("relatorio.txt", "a+");
						fprintf(valores, "\n%f\n", resultado);
						fclose(valores);
						getch();
					}
					else
					{
						printf("Erro!");
					};

					break;

				case 2: /*Caso opcao for igual a 2, ele escolhe cadastro, cadastra cliente armazenando dados em "usuario.txt".
					  Se o arquivo de texto não existir ele ira criar um*/
					setlocale(LC_ALL, "Portuguese");
					puts("Digite o usuario com limite de 50 caracteres");
					printf("Usuario: ");
					gets(user);

					do
					{
						puts("\n Digite o CPF do cliente! \n");
						printf("CPF: \n");
						senha = CriaSenha();
						printf("\nConfirmacao de CPF: ");
						confirmaSenha = CriaSenha();
						printf("\n");

						if (!strcmp(senha, confirmaSenha))
							break;
						else
							printf("Os Cpfs nao correspondem. Tente novamente.\n");
					} while (1);

					fpIN = fopen("usuarios.txt", "a+");
					fprintf(fpIN, "%s %s\n", user, senha);
					fclose(fpIN);

					free(senha);
					free(confirmaSenha);
					break;

				case 3: /*Caso opcao for igual a 3, ele esoclhe Relatórios, ele imprime na tela o relatório de ganhos puxando o arquivo "relatorio.txt"*/
					puts("Voce escolheu relatorios");
					puts("Relatorio de ganhos:");
					valores = fopen("relatorio.txt", "a+");
					system("type relatorio.txt");
					fclose(valores);

					break;
				case 4:
					exit(0);
					break;

					if (opcao != 1, 2, 3)
					default:
						puts("opcao invalida"); //Caso opcao seja diferente de 1, 2 ou 3, printa opção invalida

					getch();
					break;
				}
			} while (1);

		case 2: /*Caso opcao1 for igual a 2, ele escolhe cadastro, cadastra funcionario armazenando dados em "funcionarios.txt".
			  Se o arquivo de texto não existir ele ira criar um*/
			setlocale(LC_ALL, "Portuguese");
			puts("Digite o usuario com limite de 50 caracteres");
			printf("Usuario: ");
			gets(user);

			do
			{
				puts("Digite a senha com limite de 14 caracteres ");
				printf("Senha: ");
				senha = CriaSenha();
				if (CriaSenha == 8 && i)
				{
					digitado[i] = '\0';
					i--;
					printf("\b \b");
				}
				printf("\nConfirmacao de senha: ");
				confirmaSenha = CriaSenha();
				printf("\n");

				if (!strcmp(senha, confirmaSenha))
					break;
				else
					printf("As senhas nao sao iguais. Tente novamente.\n");
			} while (1);

			funcionarios = fopen("usuarios.txt", "a+");
			fprintf(funcionarios, "%s %s\n", user, senha);
			fclose(funcionarios);

			free(senha);
			free(confirmaSenha);

			break;

			puts("opcao invalida");

			;
		case 3: //Caso opcao1 for igual a 3 ele encerra o programa
			exit(0);
			break;
			if (opcao1 != 1, 2)
			default:
				printf("\nOpcao invalida!"); //Caso opcao1 for diferente de 1 ou 2, printa opção invalida
		}

	} while (1);
}
