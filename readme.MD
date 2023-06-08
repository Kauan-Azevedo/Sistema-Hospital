# Projeto 🛠️

-   Projeto em C voltado para criação de um gerenciador de prontuários médicos de um hospital.

## Sobre 📚

-   Esse projeto tem como intuito de exercitar e aprender como funciona o paradigma estruturado. esenvolvido como atividade avaliativa do curso de Análise e Desenvolvimento de Sistemas na faculdade Cesusc (ADS21 - Técnicas e Paradigmas da Programação II).

### Compilar o arquivo 🌟

-   Pacotes Necessarios:

    ```bash
      libmysqlclient-dev
    ```

-   Compilar arquivo:

    ```bash
      gcc main.c -L/usr/lib64/mysql -lmysqlclient -o bin/main.exe
    ```

-   Executar programa compilado:

    ```bash
      ./bin/main.exe
    ```

-   (Ubuntu): Iniciar servico mysql:

    ```bash
      sudo service mysql start
    ```

-   (Ubuntu): Iniciar mysql:

    ```bash
      sudo mysql -p
    ```

-   Executar programa compilado:

    ```bash
      g++ main_cpp.cpp -o ./bin/main_cpp.exe -L/usr/lib64/mysql -lmysqlclient
    ```
