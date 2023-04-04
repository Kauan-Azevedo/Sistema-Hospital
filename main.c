#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int id;
    char nome[50];
    char endereco[100];
    char telefone[20];
    char email[50];
} Hospital;

typedef struct
{
    int id;
    char nome[50];
    int id_hospital;
} Clinica;

typedef struct
{
    int id;
    char nome[50];
    char especialidade[50];
    int id_clinica;
} Medico;

typedef struct
{
    int id;
    char nome[50];
    char descricao[100];
} Doenca;

typedef struct
{
    int id;
    char nome[50];
    char sobrenome[50];
    char cpf[20];
    char telefone[20];
    char email[50];
    int id_clinica;
} Funcionario;

// void salvarHospital(Hospital hospital)
void salvarHospital(int id, char nome[], char endereco[], char telefone[], char email[])
{
    FILE *arquivo = fopen("hospitais.csv", "a");
    fprintf(arquivo, "%d;%s;%s;%s;%s\n", id, nome, endereco, telefone, email);
    fclose(arquivo);
}

Hospital buscarHospital(int id)
{
    FILE *arquivo = fopen("hospitais.csv", "r");
    Hospital hospital;

    while (fscanf(arquivo, "%i;%[^;];%[^;];%[^;];%s\n", &hospital.id, hospital.nome, hospital.endereco, hospital.telefone, hospital.email) != EOF)
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

void atualizarHospital(Hospital hospital)
{
    FILE *arquivo = fopen("hospitais.csv", "r+");
    Hospital h;
    long int posicao;
    while (fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%s\n", &h.id, h.nome, h.endereco, h.telefone, h.email) != EOF)
    {
        if (h.id == hospital.id)
        {
            posicao = ftell(arquivo) - strlen(h.nome) - strlen(h.endereco) - strlen(h.telefone) - strlen(h.email) - 17;
            fseek(arquivo, posicao, SEEK_SET);
            fprintf(arquivo, "%d;%s;%s;%s;%s\n", hospital.id, hospital.nome, hospital.endereco, hospital.telefone, hospital.email);
            break;
        }
    }
    fclose(arquivo);
}

void excluirHospital(int id)
{
    FILE *arquivo = fopen("hospitais.csv", "r");
    FILE *arquivo_temp = fopen("hospitais_temp.txt", "w");
    Hospital hospital;
    while (fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%s\n", &hospital.id, hospital.nome, hospital.endereco, hospital.telefone, hospital.email) != EOF)
    {
        if (hospital.id != id)
        {
            fprintf(arquivo_temp, "%d;%s;%s;%s;%s\n", hospital.id, hospital.nome, hospital.endereco, hospital.telefone, hospital.email);
        }
    }
    fclose(arquivo);
    fclose(arquivo_temp);
    remove("hospitais.txt");
    rename("hospitais_temp.txt", "hospitais.txt");
}

int main()
{
    int escolha;
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
            char telefone[20];
            char email[50];

            system("clear");

            printf("Digite o ID:");
            scanf("%i", &id);
            printf("Digite o Nome:");
            scanf("%s", nome);
            printf("Digite o Endereco:");
            scanf("%s", endereco);
            printf("Digite o Telefone:");
            scanf("%s", telefone);
            printf("Digite o Email:");
            scanf("%s", email);

            salvarHospital(id, nome, endereco, telefone, email);
        }
        else if (escolha == 2)
        {
            int id = 0;

            printf("Digite o ID: ");
            scanf("%i", &id);

            Hospital h = buscarHospital(id);

            printf("%s", h);
            printf("ID: %i\n,Nome: %s\n,Endereco: %s\n,Telefone: %s\n,Email: %s\n", h.id, h.nome, h.endereco, h.telefone, h.email);
        }
    } while (escolha != 0);

    return 0;
}