#include <iostream>
#include <mysql/mysql.h>

using namespace std;

class Database
{
private:
    char *server = "localhost";
    char *user = "root";
    char *password = "root";
    char *database = "sistema_hospital";

public:
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

        this->end_connection();
    }
};

int main()
{
    int escolha;
    char temp[1];

    printf("Bem-vindo,\no que deseja fazer?\n");
    while (escolha != 0)
    {
    }

    return 0;
}