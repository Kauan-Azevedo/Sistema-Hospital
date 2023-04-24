#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

void create(sql::Connection *con, int id, std::string nome, std::string cpf, std::string telefone, std::string email, std::string especializacao, std::string historico_de_pacientes, std::string hospital_em_que_atua) {
  sql::PreparedStatement *prep_stmt;
  prep_stmt = con->prepareStatement("INSERT INTO medicos (id, nome, cpf, telefone, email, especializacao, historico_de_pacientes, hospital_em_que_atua) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
  prep_stmt->setInt(1, id);
  prep_stmt->setString(2, nome);
  prep_stmt->setString(3, cpf);
  prep_stmt->setString(4, telefone);
  prep_stmt->setString(5, email);
  prep_stmt->setString(6, especializacao);
  prep_stmt->setString(7, historico_de_pacientes);
  prep_stmt->setString(8, hospital_em_que_atua);
  prep_stmt->execute();
  delete prep_stmt;
  std::cout << "Médico adicionado com sucesso!\n";
}

int main(void)
{
    // Cria uma conexão com o banco de dados
sql::Driver *driver;
sql::Connection *con;
driver = get_driver_instance();
con = driver->connect("tcp://127.0.0.1:3306", "root", "password");
con->setSchema("prontuario");

// Chama a função create para adicionar um novo médico
create(con, 1, "João Silva", "123.456.789-10", "(11) 1234-5678", "joao.silva@example.com", "Cardiologia", "Paciente A, Paciente B", "Hospital Santa Casa");

// Fecha a conexão com o banco de dados
delete con;

}