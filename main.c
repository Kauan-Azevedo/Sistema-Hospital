#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
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

void salvarHospital(Hospital hospital)
{
    FILE *arquivo = fopen("hospitais.txt", "a");
    fprintf(arquivo, "%d;%s;%s;%s;%s\n", hospital.id, hospital.nome, hospital.endereco, hospital.telefone, hospital.email);
    fclose(arquivo);
}

Hospital buscarHospital(int id)
{
    FILE *arquivo = fopen("hospitais.txt", "r");
    Hospital hospital;
    while (fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%s\n", &hospital.id, hospital.nome, hospital.endereco, hospital.telefone, hospital.email) != EOF)
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
    FILE *arquivo = fopen("hospitais.txt", "r+");
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
    FILE *arquivo = fopen("hospitais.txt", "r");
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

    printf("Bem-vindo,\nOque deseja fazer?\n0 - Sair\n1 - Registrar Hospital\n2 - Buscar Hospital\n3 - Atualizar Hospital\n4 - Excluir Hospital\nEscolha: ");
    scanf("%i", &escolha);
    if (escolha == 0)
    {
        system("cls");
        printf("Saindo...");
    }
    else if (escolha == 1)
    {
        int id;
        char nome[50];
        char endereco[100];
        char telefone[20];
        char email[50];

        system("cls");
        printf("Digite os seguintes dados em ordem e separado por virgula[ id, nome, endereco, telefone, email ]: ");
        scanf("%i, %s, %s, %s, %s", &id, nome, endereco, telefone, email);
        Hospital hospital = {id, nome, endereco, telefone, email};
        salvarHospital(hospital);
    }

    return 0;
}