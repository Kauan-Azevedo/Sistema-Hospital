#include <iostream>
#include <mysql/mysql.h>
#include <string.h>

using namespace std;

class Database
{
private:
    const char *server;
    const char *user;
    const char *password;
    const char *database;

public:
    Database()
    {
        server = "localhost";
        user = "root";
        password = "root";
        database = "sistema_hospital";
    }

    MYSQL *create_connection()
    {
        MYSQL *conn = mysql_init(NULL);

        if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
        {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }

        return conn;
    }

    void end_connection(MYSQL *conn)
    {
        mysql_close(conn);
    }
};

class Hospital : public Database
{
private:
    char nome[150];
    char endereco[150];
    char cep[11];

public:
    Hospital() {}
    Hospital(char nome[150], char endereco[150], char cep[11])
    {
        strcpy(this->nome, nome);
        strcpy(this->endereco, endereco);
        strcpy(this->cep, cep);
    }

    void create()
    {
        MYSQL *conn = this->create_connection();

        char query[1000];
        sprintf(query, "INSERT INTO Hospital(nome, endereco, cep) VALUES('%s', '%s', '%s')", this->nome, this->endereco, this->cep);

        if (mysql_query(conn, query))
        {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        printf("\nDados inseridos com sucesso!\n\n");
        this->end_connection(conn);
    }

    void read()
    {
        MYSQL *conn = this->create_connection();
        MYSQL_RES *res;
        MYSQL_ROW row;

        mysql_query(conn, "SELECT * FROM Hospital");

        res = mysql_store_result(conn);

        printf("\n+----- Hospitais -----+\n\n");
        while ((row = mysql_fetch_row(res)) != NULL)
        {
            printf("Id: %s,\nNome: %s,\nEndereco: %s,\nCEP: %s;\n\n", row[0], row[1], row[2], row[3]);
        }
        printf("+----- Fim - Hospitais -----+\n");
        mysql_free_result(res);

        this->end_connection(conn);
    }

    void update(char nomeAntigo[])
    {
        MYSQL *conn = this->create_connection();

        char query[1000];

        sprintf(query, "UPDATE Hospital SET nome='%s', endereco='%s', cep='%s' WHERE nome='%s'", this->nome, this->endereco, this->cep, nomeAntigo);
        if (mysql_query(conn, query))
        {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        printf("\nDados alterados com sucesso!\n\n");
        this->end_connection(conn);
    };

    void remove(char nome[150])
    {
        MYSQL *conn = this->create_connection();
        char query[1000];
        sprintf(query, "DELETE FROM Hospital WHERE nome = '%s'", nome);
        if (mysql_query(conn, query) != 0)
        {
            fprintf(stderr, "%s\n", mysql_error(conn));
        }
        printf("\nDados excluidos com sucesso!\n");
        this->end_connection(conn);
    }
};

int main()
{
    int escolha;
    char temp[1];

    printf("Bem-vindo, Ao gerenciador de Prontuarios \n");
    while (escolha != 0)
    {
        printf("0 - Sair\n1 - Adicionar Hospital\n2 - LIstar Hospitais\n3 - Atualizar Hospital\n4 - Excluir Hospital\nEscolha: ");
        scanf("%i", &escolha);

        if (escolha == 1)
        {
            char nome[150];
            char endereco[150];
            char cep[15];

            printf("[CREATE](Hospital)Digite o Nome: ");
            scanf("%c", temp);
            scanf("%[^\n]", nome);
            printf("[CREATE](Hospital)Digite o Endereco: ");
            scanf("%c", temp);
            scanf("%[^\n]", endereco);
            printf("[CREATE](Hospital)Digite o CEP: ");
            scanf("%c", temp);
            scanf("%s", cep);

            Hospital hospital(nome, endereco, cep);
            hospital.create();
        }
        else if (escolha == 2)
        {
            Hospital hospital;

            hospital.read();
        }
        else if (escolha == 3)
        {
            char nomeAntigo[150];
            char nome[150];
            char endereco[150];
            char cep[15];

            printf("[UPDATE](Hospital)Nome do hospital: ");
            scanf("%c", temp);
            scanf("%[^\n]", nomeAntigo);
            printf("[UPDATE](Hospital)Novo nome: ");
            scanf("%c", temp);
            scanf("%[^\n]", nome);
            printf("[UPDATE](Hospital)Novo endereco: ");
            scanf("%c", temp);
            scanf("%[^\n]", endereco);
            printf("[UPDATE](Hospital)Novo cep: ");
            scanf("%c", temp);
            scanf("%[^\n]", cep);

            Hospital hospital(nome, endereco, cep);
            hospital.update(nomeAntigo);
        }
        else if (escolha == 4)
        {
            char nome[150];

            printf("Nome do hospital: ");
            scanf("%c", temp);
            scanf("%[^\n]", nome);

            Hospital hospital;
            hospital.remove(nome);
        }
        else
        {
            printf("\nValor invalido!\n");
        }
    };

    return 0;
}