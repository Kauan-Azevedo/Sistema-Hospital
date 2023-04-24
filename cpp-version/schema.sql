-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
-- -----------------------------------------------------
-- Schema prontuario
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema prontuario
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `prontuario` ;
USE `prontuario` ;

-- -----------------------------------------------------
-- Table `prontuario`.`medicos`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `prontuario`.`medicos` ;

CREATE TABLE IF NOT EXISTS `prontuario`.`medicos` (
  `id` INT NOT NULL,
  `nome` VARCHAR(45) NOT NULL,
  `cpf` VARCHAR(45) NOT NULL,
  `telefone` VARCHAR(45) NOT NULL,
  `email` VARCHAR(45) NOT NULL,
  `especializacao` VARCHAR(45) NOT NULL,
  `historico_de_pacientes` VARCHAR(45) NOT NULL,
  `hospital_em_que_atua` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `prontuario`.`hospitais`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `prontuario`.`hospitais` ;

CREATE TABLE IF NOT EXISTS `prontuario`.`hospitais` (
  `id` INT NOT NULL,
  `nome` VARCHAR(45) NOT NULL,
  `bairro` VARCHAR(45) NOT NULL,
  `numero` VARCHAR(45) NOT NULL,
  `telefone` VARCHAR(45) NOT NULL,
  `lotacao` INT NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `prontuario`.`clinicas`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `prontuario`.`clinicas` ;

CREATE TABLE IF NOT EXISTS `prontuario`.`clinicas` (
  `id` INT NOT NULL,
  `nome` VARCHAR(45) NOT NULL,
  `bairro` VARCHAR(45) NOT NULL,
  `telefone` VARCHAR(45) NOT NULL,
  `numero` VARCHAR(45) NOT NULL,
  `lotacao` VARCHAR(45) NOT NULL,
  `especializacao` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `prontuario`.`doencas`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `prontuario`.`doencas` ;

CREATE TABLE IF NOT EXISTS `prontuario`.`doencas` (
  `id` INT NOT NULL,
  `nome` VARCHAR(45) NOT NULL,
  `tipo` VARCHAR(45) NOT NULL,
  `gravidade` VARCHAR(45) NOT NULL,
  `medicacao_recomendada` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `prontuario`.`pacientes`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `prontuario`.`pacientes` ;

CREATE TABLE IF NOT EXISTS `prontuario`.`pacientes` (
  `id` INT NOT NULL,
  `nome` VARCHAR(45) NOT NULL,
  `cpf` VARCHAR(45) NOT NULL,
  `telefone` VARCHAR(45) NOT NULL,
  `email` VARCHAR(45) NOT NULL,
  `prontuarios` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
