#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // SE LINUX
// #include <windows.h> // SE WINDOWS
typedef struct
{
    int id;
    char nome[50];
    char endereco[100];
    char cep[50];
} Hospital;

typedef struct
{
    int id;
    char nome[50];
    char endereco[150];
    char cep[50];

    int id_hospital;
} Clinica;

typedef struct
{
    int id;
    char nome[150];
    char email[150];
    char cpf[50];
    char telefone[50];
    char endereco[150];
    char especialidade[50];

    int id_clinica;
} Medico;

typedef struct
{
    int id;
    char nome[150];
    char email[150];
    char cpf[50];
    char telefone[50];
    char endereco[150];

    int id_clinica;
    int id_medico;
    int id_doenca;
} Paciente;

typedef struct
{
    int id;
    char nome[50];
    char descricao[100];
    int gravidade;

    int id_paciente;
} Doenca;

void clear_message(char mensagem[])
{
    printf("%s", mensagem);
}

// void salvarHospital(Hospital hospital)
void salvarHospital(int id, char nome[], char endereco[], char cep[])
{
    FILE *arquivo = fopen("hospitais.csv", "a");
    fprintf(arquivo, "%d;%s;%s;%s\n", id, nome, endereco, cep);
    fclose(arquivo);
}

Hospital buscarHospital(int id)
{
    FILE *arquivo = fopen("hospitais.csv", "r");
    Hospital hospital;

    while (fscanf(arquivo, "%i;%[^;];%[^;];%s\n", &hospital.id, hospital.nome, hospital.endereco, hospital.cep) != EOF)
    {
        if (hospital.id == id)
        {
            fclose(arquivo);
            return hospital;
        }
    }
    fclose(arquivo);
    hospital.id = -1;
    return hospital;
}

int main()
{
    int escolha;
    char temp[1];
    printf("Bem-vindo,\nOque deseja fazer?\n");
    do
    {
        system("clear");
        printf("0 - Sair\n1 - Registrar Hospital\n2 - Buscar Hospital\n3 - Atualizar Hospital\n4 - Excluir Hospital\nEscolha: ");
        scanf("%i", &escolha);
        if (escolha == 0)
        {
            system("cls");
            printf("Saindo...");
        }
        else if (escolha == 1)
        {
            int id = 0;
            char nome[50];
            char endereco[100];
            char cep[50];

            system("clear");

            printf("(Hospital)Digite o ID:");
            scanf("%i", &id);
            printf("(Hospital)Digite o Nome:");
            scanf("%c", temp);
            scanf("%[^\n]", nome);
            printf("(Hospital)Digite o Endereco:");
            scanf("%c", temp);
            scanf("%[^\n]", endereco);
            printf("(Hospital)Digite o CEP:");
            scanf("%c", temp);
            scanf("%s", cep);

            clear_message("Salvando Hospital.");
            clear_message("Salvando Hospital..");
            clear_message("Salvando Hospital...");

            salvarHospital(id, nome, endereco, cep);
        }
        else if (escolha == 2)
        {
            int id = 0;

            printf("Digite o ID: ");
            scanf("%i", &id);

            Hospital h = buscarHospital(id);
            if (h.id == -1)
            {
                printf("\n\nHospital nao encontrado\n");
            }
            else
            {
                sleep(1);
                printf("Hospital encontrado");
                sleep(1);
                printf("\nHospital:\nId: %i\nNome: %s\nEndereco: %s\nCep: %s\n\n", h.id, h.nome, h.endereco, h.cep);
            }
            escolha = 0;
        }
    } while (escolha != 0);

    return 0;
}