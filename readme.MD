# Projeto 🛠️

-   Projeto em C e C++ voltado para criação de um gerenciador de prontuários médicos de um hospital.

## Sobre 📚

-   <span style="color:rgb(255,0,0);font-weight:bold">O projeto desenvolvido usando WSL2 Ubuntu22.04.1</span>
-   Esse projeto tem como intuito de exercitar e entender o funcionamento dos paradigmas estruturado e orientado a objeto.Desenvolvido como atividade avaliativa N2 e N3 do curso de Análise e Desenvolvimento de Sistemas na faculdade Cesusc (ADS21 - Técnicas e Paradigmas da Programação II).

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
