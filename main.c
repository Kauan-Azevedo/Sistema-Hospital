#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>'

typedef struct
{
    char nome[150];
    char endereco[150];
    char cep[11];
} Hospital;

typedef struct
{
    char nome[150];
    char endereco[150];
    char cep[11];
    int Hospital_idHospital;
} Clinica;

typedef struct
{
    char nome[150];
    char email[150];
    char cpf[15];
    char telefone[15];
    char endereco[150];
    char especialidade[50];
} Medico;

typedef struct
{
    char nome[150];
    char email[150];
    char cpf[15];
    char telefone[15];
    char endereco[150];
} Paciente;

typedef struct
{
    char nome[150];
    char descricao[250];
    int gravidade;
} Doenca;

typedef struct
{
    char situacao_paciente[450];
    char historico_familiar[500];
    char alergias[400];
    char medicacoes[400];
    int Medico_id;
    int Doenca_id;
    int Paciente_id;
    int Clinica_id;
    int Clinica_Hospital_idHospital;
} Prontuario;

char *server = "localhost";
char *user = "root";
char *password = "root";
char *database = "sistema_hospital";

void salvarHospital(char nome[], char endereco[], char cep[])
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[1000];
    sprintf(query, "INSERT INTO Hospital (nome, endereco, cep) VALUES ('%s', '%s', '%s')", nome, endereco, cep);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    printf("Dados inseridos com sucesso!\n\n");

    mysql_close(conn);
}

void listarHospitais()
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_query(conn, "SELECT * FROM Hospital");

    res = mysql_store_result(conn);

    printf("\n+----- Hospitais -----+\n\n");
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("Id: %s,\nNome: %s,\nEndereco: %s,\nCEP: %s\n\n", row[0], row[1], row[2], row[3]);
    }
    printf("+----- Fim - Hospitais -----+\n");

    mysql_free_result(res);

    mysql_close(conn);
}

void atualizarHospital(char nomeAntigo[], char nomeNovo[], char endereco[], char cep[])
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    char query[1000];

    sprintf(query, "UPDATE Hospital SET nome = '%s', endereco = '%s', cep = '%s' WHERE nome = '%s'", nomeNovo, endereco, cep, nomeAntigo);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("\nDados alterados com sucesso!\n\n");
}

void excluirHospital(char nome[])
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    char query[1000];

    sprintf(query, "DELETE FROM Hospital WHERE nome = '%s'", nome);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("\nDados excluidos com sucesso!\n\n");
}

int main()
{
    int escolha;
    char temp[1];

    printf("Bem-vindo,\no que deseja fazer?\n");
inicio:
    // system("clear");
    printf("0 - Sair\n1 - Registrar Hospital\n2 - Listar Hospitais\n3 - Atualizar Hospital\n4 - Excluir Hospital\nEscolha: ");
    scanf("%i", &escolha);
    if (escolha == 0)
    {
        // system("clear");
        printf("\nSaindo...");
    }
    else if (escolha == 1)
    {
        char nome[50];
        char endereco[100];
        char cep[50];

        printf("(Hospital)Digite o Nome: ");
        scanf("%c", temp);
        scanf("%[^\n]", nome);
        printf("(Hospital)Digite o Endereco: ");
        scanf("%c", temp);
        scanf("%[^\n]", endereco);
        printf("(Hospital)Digite o CEP: ");
        scanf("%c", temp);
        scanf("%s", cep);

        salvarHospital(nome, endereco, cep);
        goto inicio;
    }
    else if (escolha == 2)
    {
        listarHospitais();
        goto inicio;
    }
    else if (escolha == 3)
    {
        char nomeAntigo[150];
        char nomeNovo[150];
        char endereco[100];
        char cep[50];

        printf("Nome do hospital: ");
        scanf("%c", temp);
        scanf("%[^\n]", nomeAntigo);
        printf("[UPDATE](Hospital)Novo nome: ");
        scanf("%c", temp);
        scanf("%[^\n]", nomeNovo);
        printf("[UPDATE](Hospital)Novo endereco: ");
        scanf("%c", temp);
        scanf("%[^\n]", endereco);
        printf("[UPDATE](Hospital)Novo cep: ");
        scanf("%c", temp);
        scanf("%[^\n]", cep);

        atualizarHospital(nomeAntigo, nomeNovo, endereco, cep);
        goto inicio;
    }
    else if (escolha == 4)
    {
        char nome[150];

        printf("Nome do hospital: ");
        scanf("%c", temp);
        scanf("%[^\n]", nome);

        excluirHospital(nome);
        goto inicio;
    }

    return 0;
}
