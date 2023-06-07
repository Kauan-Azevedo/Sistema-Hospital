#include <iostream>
#include <mysql/mysql.h>

using namespace std;

class Database
{
private:
    char *server;
    char *user;
    char *password;
    char *database;

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
    Hospital()
    {
    }

    void create()
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
};

int main()
{
    int escolha;
    char temp[1];

    while (escolha != 0)
    {
        printf("Bem-vindo,\no que deseja fazer?\n");
        scanf("%i", &escolha);

        if (escolha == 1)
        {
            char nome[150];
            char endereco[150];
            char cep[15];

            printf("(Hospital)Digite o Nome: ");
            scanf("%c", temp);
            scanf("%[^\n]", nome);
            printf("(Hospital)Digite o Endereco: ");
            scanf("%c", temp);
            scanf("%[^\n]", endereco);
            printf("(Hospital)Digite o CEP: ");
            scanf("%c", temp);
            scanf("%s", cep);

            Hospital hospital(nome, endereco, cep);
        }
    };

    return 0;
}