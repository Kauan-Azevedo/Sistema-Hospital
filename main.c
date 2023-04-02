#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLINICS 150
#define MAX_EMPLOYEES 2000
#define MAX_DOCTORS 150
#define MAX_PATIENTS 10000
#define MAX_DISEASES 5000

typedef struct
{
    int id;
    char name[50];
} Clinic;

typedef struct
{
    int id;
    char name[50];
    char email[50];
    int clinic_id;
} Employee;

typedef struct
{
    int id;
    char name[50];
    char email[50];
    int clinic_id;
} Doctor;

typedef struct
{
    int id;
    char name[50];
    char email[50];
    char phone[20];
    char address[100];
} Patient;

typedef struct
{
    int id;
    char name[50];
    char description[200];
} Disease;

Clinic clinics[MAX_CLINICS];
int num_clinics = 0;

Employee employees[MAX_EMPLOYEES];
int num_employees = 0;

Doctor doctors[MAX_DOCTORS];
int num_doctors = 0;

Patient patients[MAX_PATIENTS];
int num_patients = 0;

Disease diseases[MAX_DISEASES];
int num_diseases = 0;

int procura_entidade_por_nome(int id, void *entities, int num_entities, int entity_size)
{
    for (int i = 0; i < num_entities; i++)
    {
        int *current_id = (int *)(entities + i * entity_size);
        if (*current_id == id)
        {
            return i;
        }
    }
    return -1;
}

void listar_entidades(void *entities, int num_entities, int entity_size, const char *entity_name)
{
    printf("%s\n Lista:\n", entity_name);
    printf("%-5s%-20s\n", "Id", "Nome");
    for (int i = 0; i < num_entities; i++)
    {
        int *current_id = (int *)(entities + i * entity_size);
        char *current_name = (char *)(entities + i * entity_size + sizeof(int));
        printf("%-5d%-20s\n", *current_id, current_name);
    }
}

void adicionar_entidade(void *entity, int *num_entities, void *entities, int entity_size, const char *entity_name)
{
    if (*num_entities >= MAX_EMPLOYEES)
    {
        printf("ERRO: %s a lista esta cheia\n", entity_name);
        return;
    }
    memcpy(entities + (*num_entities) * entity_size, entity, entity_size);
    (*num_entities)++;
    printf("%s Adicionado com sucesso\n", entity_name);
}

void remover_entidade(int id, int *num_entities, void *entities, int entity_size, const char *entity_name)
{
    int index = procura_entidade_por_nome(id, entities, *num_entities, entity_size);
    if (index == -1)
    {
        printf("ERRO: %s com o Id %d NAO encontrada!\n", entity_name, id);
        return;
    }
    memmove(entities + index * entity_size, entities + (index + 1) * entity_size, (*num_entities - index - 1) * entity_size);
    (*num_entities)--;
    printf("%s Com o Id %d foi REMOVIDA com sucesso!\n", entity_name, id);
}

void atualizar_entidade(int id, void *new_entity, int *num_entities, void *entities, int entity_size, const char *entity_name)
{
    int index = procura_entidade_por_nome(id, entities, *num_entities, entity_size);
    if (index == -1)
    {
        printf("ERRO: %s com o Id %d NAO encontada!\n", entity_name, id);
        return;
    }
    memcpy(entities + index * entity_size, new_entity, entity_size);
    printf("%s com o Id %d ATUALIZADA com sucesso!\n", entity_name, id);
}

void find_employees_by_clinic(int clinic_id)
{
    printf("Funcionarios na clinica %d:\n", clinic_id);
    printf("%-5s%-20s%-20s\n", "Id", "Nome", "Email");
    for (int i = 0; i < num_employees; i++)
    {
        Employee *current_employee = &employees[i];
        if (current_employee->clinic_id == clinic_id)
        {
            printf("%-5d%-20s%-20s\n", current_employee->id, current_employee->name, current_employee->email);
        }
    }
}

void find_doctors_by_clinic(int clinic_id)
{
    printf("Doutores na clinica %d:\n", clinic_id);
    printf("%-5s%-20s%-20s\n", "Id", "Nome", "Email");
    for (int i = 0; i < num_doctors; i++)
    {
        Doctor *current_doctor = &doctors[i];
        if (current_doctor->clinic_id == clinic_id)
        {
            printf("%-5d%-20s%-20s\n", current_doctor->id, current_doctor->name, current_doctor->email);
        }
    }
}

int main()
{
    while (1)
    {
        printf("Bem-vindo, Escolha uma opcao:\n");
        printf("1. Adicionar clinica\n");
        printf("2. Adicionar funcionario\n");
        printf("3. Adicionar doutor\n");
        printf("4. Adicionar paciente\n");
        printf("5. Adicionar doenca\n");
        printf("6. Remover clinica\n");
        printf("7. Remover funcionario\n");
        printf("8. Remover doutor\n");
        printf("9. Remover paciente\n");
        printf("10. Remover doenca\n");
        printf("11. Atualizar clinica\n");
        printf("12. Atualizar funcionario\n");
        printf("13. Atualizar doutor\n");
        printf("14. Atualizar paciente\n");
        printf("15. Atualizar doenca\n");
        printf("16. Listar clinicas\n");
        printf("17. Listar funcionarios\n");
        printf("18. Listar doutores\n");
        printf("19. Listar pacientes\n");
        printf("20. Listar doencas\n");
        printf("21. Listar funcionarios por ID da Clinica\n");
        printf("22. Listar doutores por ID da clinicaFind doutors by clinica ID\n");
        printf("23. Sair\n");

        int option;
        scanf("%d", &option);
        if (option == 1)
        {
            Clinic clinic;
            printf("Nome da clinica: ");
            scanf("%s", clinic.name);
            clinic.id = num_clinics + 1;
            adicionar_entidade(&clinic, &num_clinics, clinics, sizeof(Clinic), "Clinic");
        }
        else if (option == 2)
        {
            Employee employee;
            printf("Nome do funcionario: ");
            scanf("%s", employee.name);
            printf("Email do funcionario: ");
            scanf("%s", employee.email);
            printf("ID da clinica: ");
            scanf("%d", &employee.clinic_id);
            employee.id = num_employees + 1;
            adicionar_entidade(&employee, &num_employees, employees, sizeof(Employee), "Employee");
        }
        else if (option == 3)
        {
            Doctor doctor;
            printf("Nome do doutor: ");
            scanf("%s", doctor.name);
            printf("Email do doutor: ");
            scanf("%s", doctor.email);
            printf("ID da clinica: ");
            scanf("%d", &doctor.clinic_id);
            doctor.id = num_doctors + 1;
            adicionar_entidade(&doctor, &num_doctors, doctors, sizeof(Doctor), "Doctor");
        }
        else if (option == 4)
        {
            Patient patient;
            printf("Nome do paciente: ");
            scanf("%s", patient.name);
            printf("Email do paciente: ");
            scanf("%s", patient.email);
            patient.id = num_patients + 1;
            adicionar_entidade(&patient, &num_patients, patients, sizeof(Patient), "Patient");
        }
        else if (option == 5)
        {
            Disease disease;
            printf("Nome da doenca: ");
            scanf("%s", disease.name);
            disease.id = num_diseases + 1;
            adicionar_entidade(&disease, &num_diseases, diseases, sizeof(Disease), "Disease");
        }
        else if (option == 6)
        {
            int clinic_id;
            printf("ID da clinica: ");
            scanf("%d", &clinic_id);
            remover_entidade(clinic_id, &num_clinics, clinics, sizeof(Clinic), "Clinic");
        }
        else if (option == 7)
        {
            int employee_id;
            printf("ID do funcionario: ");
            scanf("%d", &employee_id);
            remover_entidade(employee_id, &num_employees, employees, sizeof(Employee), "Employee");
        }
        else if (option == 8)
        {
            int doctor_id;
            printf("ID do doutor: ");
            scanf("%d", &doctor_id);
            remover_entidade(doctor_id, &num_doctors, doctors, sizeof(Doctor), "Doctor");
        }
        else if (option == 9)
        {
            int patient_id;
            printf("ID do paciente: ");
            scanf("%d", &patient_id);
            remover_entidade(patient_id, &num_patients, patients, sizeof(Patient), "Patient");
        }
        else if (option == 10)
        {
            int disease_id;
            printf("ID da doenca: ");
            scanf("%d", &disease_id);
            remover_entidade(disease_id, &num_diseases, diseases, sizeof(Disease), "Disease");
        }
        else if (option == 11)
        {
            int clinic_id;
            printf("ID da clinica: ");
            scanf("%d", &clinic_id);
            Clinic clinic;
            printf("Nome da clinica: ");
            scanf("%s", clinic.name);
            atualizar_entidade(clinic_id, &clinic, &num_clinics, clinics, sizeof(Clinic), "Clinic");
        }
        else if (option == 12)
        {
            int employee_id;
            printf("ID do funcionario: ");
            scanf("%d", &employee_id);
            Employee employee;
            printf("Nome do funcionario: ");
            scanf("%s", employee.name);
            printf("Email do funcionario: ");
            scanf("%s", employee.email);
            printf("ID da clinica: ");
            scanf("%d", &employee.clinic_id);
            atualizar_entidade(employee_id, &employee, &num_employees, employees, sizeof(Employee), "Employee");
        }
        else if (option == 13)
        {
            int doctor_id;
            printf("ID do doutor: ");
            scanf("%d", &doctor_id);
            Doctor doctor;
            printf("Nome do doutor: ");
            scanf("%s", doctor.name);
            printf("Email do doutor: ");
            scanf("%s", doctor.email);
            printf("ID do doutor: ");
            scanf("%d", &doctor.clinic_id);
            atualizar_entidade(doctor_id, &doctor, &num_doctors, doctors, sizeof(Doctor), "Doctor");
        }
        else if (option == 14)
        {
            int patient_id;
            printf("ID do paciente: ");
            scanf("%d", &patient_id);
            Patient patient;
            printf("Nome do paciente: ");
            scanf("%s", patient.name);
            printf("Email do paciente: ");
            scanf("%s", patient.email);
            atualizar_entidade(patient_id, &patient, &num_patients, patients, sizeof(Patient), "Patient");
        }
        else if (option == 15)
        {
            int disease_id;
            printf("ID da doenca: ");
            scanf("%d", &disease_id);
            Disease disease;
            printf("Nome da doenca: ");
            scanf("%s", disease.name);
            atualizar_entidade(disease_id, &disease, &num_diseases, diseases, sizeof(Disease), "Disease");
        }
        else if (option == 16)
        {
            printf("Clinicas:\n");
            listar_entidades(num_clinics, clinics, sizeof(Clinic), "Clinic");
        }
        else if (option == 17)
        {
            printf("Funcionarios:\n");
            listar_entidades(num_employees, employees, sizeof(Employee), "Employee");
        }
        else if (option == 18)
        {
            printf("Doutores:\n");
            listar_entidades(num_doctors, doctors, sizeof(Doctor), "Doctor");
        }
        else if (option == 19)
        {
            printf("Pacientes:\n");
            listar_entidades(num_patients, patients, sizeof(Patient), "Patient");
        }
        else if (option == 20)
        {
            printf("Doencas:\n");
            listar_entidades(num_diseases, diseases, sizeof(Disease), "Disease");
        }
        else if (option == 21)
        {
            printf("Saindo...\n");
            break;
        }
        else
        {
            printf("Opcao INVALIDA, tente novamente.\n");
        }
    }
    return 0;
}
