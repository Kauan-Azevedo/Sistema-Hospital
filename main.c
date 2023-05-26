#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>

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

void adicionarHospital(char nome[], char endereco[], char cep[])
{
    MYSQL *conn;

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
        printf("Id: %s,\nNome: %s,\nEndereco: %s,\nCEP: %s;\n\n", row[0], row[1], row[2], row[3]);
    }
    printf("+----- Fim - Hospitais -----+\n");
    mysql_free_result(res);
    mysql_close(conn);
}

void atualizarHospital(char nomeAntigo[], char nomeNovo[], char endereco[], char cep[])
{
    MYSQL *conn;

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
    mysql_close(conn);
}

void excluirHospital(char nome[])
{
    MYSQL *conn;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char deleteClinicasQuery[1000];
    sprintf(deleteClinicasQuery, "DELETE FROM Clinica WHERE Hospital_idHospital = (SELECT id FROM Hospital WHERE nome = '%s')", nome);
    if (mysql_query(conn, deleteClinicasQuery) != 0)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char deleteHospitalQuery[1000];
    sprintf(deleteHospitalQuery, "DELETE FROM Hospital WHERE nome = '%s'", nome);
    if (mysql_query(conn, deleteHospitalQuery) != 0)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Dados excluídos com sucesso!\n\n");
    mysql_close(conn);
}

void adicionarClinica(char nome[], char endereco[], char cep[], char nomeHospital[])
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

    char selectQuery[1000];
    sprintf(selectQuery, "SELECT id FROM Hospital WHERE nome = '%s'", nomeHospital);

    if (mysql_query(conn, selectQuery) != 0)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    int idHospital = -1;

    if ((row = mysql_fetch_row(res)) != NULL)
    {
        idHospital = atoi(row[0]);
    }
    else
    {
        fprintf(stderr, "Hospital não encontrado\n");
        mysql_free_result(res);
        mysql_close(conn);
    }

    mysql_free_result(res);

    char query[1000];
    sprintf(query, "INSERT INTO Clinica (nome, endereco, cep, Hospital_idHospital) VALUES ('%s', '%s', '%s', '%i')", nome, endereco, cep, idHospital);

    if (mysql_query(conn, query) != 0)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Dados inseridos com sucesso!\n\n");
    mysql_close(conn);
}

void listarClinicas()
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

    mysql_query(conn, "SELECT * FROM Clinica");

    res = mysql_store_result(conn);

    printf("\n+----- Clinicas -----+\n\n");
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("Id: %s,\nNome: %s,\nEndereco: %s,\nCEP: %s,\nId do Hospital: %s;\n\n", row[0], row[1], row[2], row[3], row[4]);
    }
    printf("+----- Fim - Clinicas -----+\n");
    mysql_free_result(res);
    mysql_close(conn);
}

void atualizarClinica(char nomeAntigo[], char nomeNovo[], char endereco[], char cep[])
{
    MYSQL *conn;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    char query[1000];

    sprintf(query, "UPDATE Clinica SET nome = '%s', endereco = '%s', cep = '%s' Where nome = '%s'", nomeNovo, endereco, cep, nomeAntigo);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    printf("\nDados alterados com sucesso!\n\n");
    mysql_close(conn);
}

void excluirClinica(char nome[])
{
    MYSQL *conn;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char deleteQuery[1000];
    sprintf(deleteQuery, "DELETE FROM Clinica WHERE nome = '%s'", nome);
    if (mysql_query(conn, deleteQuery) != 0)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Dados excluídos com sucesso!\n\n");
    mysql_close(conn);
}

void adicionarMedico(Medico medico)
{
    MYSQL *conn;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    char query[1000];
    sprintf(query, "INSERT INTO Medico (nome, email, cpf, telefone, endereco, especializacao) VALUES ('%s', '%s', '%s', '%s', '%s', '%s')", medico.nome, medico.email, medico.cpf, medico.telefone, medico.endereco, medico.especialidade);

    if (mysql_query(conn, query) != 0)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    printf("Dados inseridos com sucesso!\n\n");
    mysql_close(conn);
}

void listarMedicos()
{
    MYSQL *conn;
    MYSQL_RES *res;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_query(conn, "SELECT * FROM Medico");
    res = mysql_store_result(conn);

    printf("\n+----- Medicos -----+\n\n");
    while ((res = mysql_fetch_row(res)) != NULL)
    {
        printf("Id: %s,\nNome: %s,\nEmail: %s,\nCPF: %s,\nTelefone: %s,\nEndereco: %s,\nEspecialidade: %s;\n\n", res[0], res[1], res[2], res[3], res[4], res[5], res[6]);
    }
    printf("+----- Fim - Medicos -----+\n");
    mysql_free_result(res);
    mysql_close(conn);
}

int main()
{
    int escolha;
    char temp[1];

    printf("Bem-vindo,\no que deseja fazer?\n");
inicio:
    printf("0 - Sair\n1 - Gerenciar Hospitais\n2 - Gerenciar Clinicas\n3 - Gerenciar Medicos\n4 - Gerenciar Pacientes\n5 - Gerenciar Doencas\n6 - Gerenciar Prontuarios\nEscolha: ");
    scanf("%i", &escolha);

    if (escolha == 0)
    {
        printf("Ate mais!");
        exit(0);
    }
    else if (escolha == 1)
    {
        goto gerenc_hospitais;
    }
    else if (escolha == 2)
    {
        goto gerenc_clinicas;
    }
    else if (escolha == 3)
    {
        goto gerenc_medicos;
    }
    else if (escolha == 4)
    {
        goto gerenc_pacientes;
    }
    else if (escolha == 5)
    {
        goto gerenc_doencas;
    }
    else if (escolha == 6)
    {
        goto gerenc_prontuarios;
    }
    else
    {
        printf("Valor invalido!!");
        goto inicio;
    }

gerenc_hospitais:
    printf("\n0 - Voltar\n1 - Registrar Hospital\n2 - Listar Hospitais\n3 - Procurar Hospital\n4 - Atualizar Hospital\n5 - Excluir Hospital\nEscolha: ");
    scanf("%i", &escolha);
    if (escolha == 0)
    {
        goto inicio;
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

        adicionarHospital(nome, endereco, cep);
        goto gerenc_hospitais;
    }
    else if (escolha == 2)
    {
        listarHospitais();
        goto gerenc_hospitais;
    }
    else if (escolha == 3)
    {
        printf("WIP");
        goto gerenc_hospitais;
    }
    else if (escolha == 4)
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
        goto gerenc_hospitais;
    }
    else if (escolha == 5)
    {
        char nome[150];

        printf("Nome do hospital: ");
        scanf("%c", temp);
        scanf("%[^\n]", nome);

        excluirHospital(nome);
        goto gerenc_hospitais;
    }
    else
    {
        printf("Valor invalido!!");
        goto gerenc_hospitais;
    }

gerenc_clinicas:
    printf("\n0 - Voltar\n1 - Registrar Clinica\n2 - Listar Clinicas\n3 - Procurar Clinica\n4 - Atualizar Clinica\n5 - Excluir Clinica\nEscolha: ");
    scanf("%i", &escolha);
    if (escolha == 0)
    {
        goto inicio;
    }
    else if (escolha == 1)
    {
        char nome[50];
        char endereco[100];
        char cep[50];
        char nomeHospital[150];

        printf("(Clinica)Digite o Nome: ");
        scanf("%c", temp);
        scanf("%[^\n]", nome);
        printf("(Clinica)Digite o Endereco: ");
        scanf("%c", temp);
        scanf("%[^\n]", endereco);
        printf("(Clinica)Digite o CEP: ");
        scanf("%c", temp);
        scanf("%s", cep);
        printf("(Clinica)Digite o Nome do Hospital: ");
        scanf("%c", temp);
        scanf("%[^\n]", nomeHospital);

        adicionarClinica(nome, endereco, cep, nomeHospital);
        goto gerenc_clinicas;
    }
    else if (escolha == 2)
    {
        listarClinicas();
        goto gerenc_clinicas;
    }
    else if (escolha == 3)
    {
        char nomeAntigo[150];
        char nomeNovo[150];
        char endereco[100];
        char cep[50];

        printf("Nome da Clinica: ");
        scanf("%c", temp);
        scanf("%[^\n]", nomeAntigo);
        printf("[UPDATE](Clinica)Novo nome: ");
        scanf("%c", temp);
        scanf("%[^\n]", nomeNovo);
        printf("[UPDATE](Clinica)Novo endereco: ");
        scanf("%c", temp);
        scanf("%[^\n]", endereco);
        printf("[UPDATE](Clinica)Novo cep: ");
        scanf("%c", temp);
        scanf("%[^\n]", cep);

        atualizarClinica(nomeAntigo, nomeNovo, endereco, cep);
        goto gerenc_clinicas;
    }
    else if (escolha == 4)
    {
        char nome[150];

        printf("Nome da clinica: ");
        scanf("%c", temp);
        scanf("%[^\n]", nome);

        excluirClinica(nome);
        goto gerenc_clinicas;
    }
    else
    {
        printf("Valor invalido!!");
        goto gerenc_clinicas;
    }

gerenc_medicos:
    printf("\n+----- Gerenciando Medicos -----+\n\n");
    printf("0 - Voltar\n1 - Registrar Medico\n2 - Listar Medicos\n3 - Procurar Medico\n4 - Atualizar Medico\n5 - Excluir Medico\nEscolha: ");
    scanf("%i", &escolha);
    if (escolha == 0)
    {
        goto inicio;
    }
    else if (escolha == 1)
    {
        Medico dados;

        printf("(Medico)Digite o Nome: ");
        scanf("%c", temp);
        scanf("%[^\n]", dados.nome);
        printf("(Medico)Digite o Email: ");
        scanf("%c", temp);
        scanf("%[^\n]", dados.email);
        printf("(Medico)Digite o CPF: ");
        scanf("%c", temp);
        scanf("%[^\n]", dados.cpf);
        printf("(Medico)Digite o telefone: ");
        scanf("%c", temp);
        scanf("%[^\n]", dados.telefone);
        printf("(Medico)Digite o endereco: ");
        scanf("%c", temp);
        scanf("%[^\n]", dados.endereco);
        printf("(Medico)Digite a especializacao: ");
        scanf("%c", temp);
        scanf("%[^\n]", dados.especialidade);

        adicionarMedico(dados);
        goto gerenc_medicos;
    }
    else if (escolha == 2)
    {
        printf("WIP");
        goto gerenc_medicos;
    }
    else if (escolha == 3)
    {
        printf("WIP");
        goto gerenc_medicos;
    }
    else if (escolha == 4)
    {
        printf("WIP");
        goto gerenc_medicos;
    }
    else
    {
        printf("Valor invalido!!");
        goto gerenc_medicos;
    }

gerenc_pacientes:
    printf("\n0 - Voltar\n1 - Registrar Paciente\n2 - Listar Pacientes\n3 - Procurar Paciente\n4 - Atualizar Paciente\n5 - Excluir Paciente\nEscolha: ");
    scanf("%i", &escolha);
    if (escolha == 0)
    {
        goto inicio;
    }
    else if (escolha == 1)
    {
        printf("WIP");
    }
    else if (escolha == 2)
    {
        printf("WIP");
    }
    else if (escolha == 3)
    {
        printf("WIP");
    }
    else if (escolha == 4)
    {
        printf("WIP");
    }
    else
    {
        printf("Valor invalido!!");
        goto gerenc_pacientes;
    }

gerenc_doencas:
    printf("\n0 - Voltar\n1 - Registrar Doenca\n2 - Listar Doencas\n3 - Procurar Doenca\n4 - Atualizar Doenca\n5 - Excluir Doenca\nEscolha: ");
    scanf("%i", &escolha);
    if (escolha == 0)
    {
        goto inicio;
    }
    else if (escolha == 1)
    {
        printf("WIP");
    }
    else if (escolha == 2)
    {
        printf("WIP");
    }
    else if (escolha == 3)
    {
        printf("WIP");
    }
    else if (escolha == 4)
    {
        printf("WIP");
    }
    else
    {
        printf("Valor invalido!!");
        goto gerenc_doencas;
    }

gerenc_prontuarios:
    printf("\n0 - Voltar\n1 - Registrar Prontuario\n2 - Listar Prontuarios\n3 - Procurar Prontuario\n4 - Atualizar Prontuario\n5 - Excluir Prontuario\nEscolha: ");
    scanf("%i", &escolha);
    if (escolha == 0)
    {
        goto inicio;
    }
    else if (escolha == 1)
    {
        printf("WIP");
    }
    else if (escolha == 2)
    {
        printf("WIP");
    }
    else if (escolha == 3)
    {
        printf("WIP");
    }
    else if (escolha == 4)
    {
        printf("WIP");
    }
    else
    {
        printf("Valor invalido!!");
        goto gerenc_prontuarios;
    }

    return 0;
}
