-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema sistema-hospital
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema sistema-hospital
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `sistema-hospital` DEFAULT CHARACTER SET utf8 ;
USE `sistema-hospital` ;

-- -----------------------------------------------------
-- Table `sistema-hospital`.`Hospital`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sistema-hospital`.`Hospital` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `nome` VARCHAR(45) NOT NULL,
  `endereco` VARCHAR(150) NOT NULL,
  `cep` VARCHAR(9) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `idHospital_UNIQUE` (`id` ASC) VISIBLE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `sistema-hospital`.`Clinica`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sistema-hospital`.`Clinica` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `nome` VARCHAR(45) NOT NULL,
  `endereco` VARCHAR(150) NOT NULL,
  `cep` VARCHAR(9) NOT NULL,
  `Hospital_idHospital` INT NOT NULL,
  PRIMARY KEY (`id`, `Hospital_idHospital`),
  UNIQUE INDEX `idClinica_UNIQUE` (`id` ASC) VISIBLE,
  INDEX `fk_Clinica_Hospital_idx` (`Hospital_idHospital` ASC) VISIBLE,
  CONSTRAINT `fk_Clinica_Hospital`
    FOREIGN KEY (`Hospital_idHospital`)
    REFERENCES `sistema-hospital`.`Hospital` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `sistema-hospital`.`Medico`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sistema-hospital`.`Medico` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `nome` VARCHAR(150) NOT NULL,
  `email` VARCHAR(150) NOT NULL,
  `cof` VARCHAR(11) NOT NULL,
  `telefone` VARCHAR(11) NOT NULL,
  `endereco` VARCHAR(150) NOT NULL,
  `especializacao` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `idDoutor_UNIQUE` (`id` ASC) VISIBLE,
  UNIQUE INDEX `cof_UNIQUE` (`cof` ASC) VISIBLE,
  UNIQUE INDEX `telefone_UNIQUE` (`telefone` ASC) VISIBLE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `sistema-hospital`.`Paciente`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sistema-hospital`.`Paciente` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `nome` VARCHAR(150) NOT NULL,
  `email` VARCHAR(150) NOT NULL,
  `cpf` VARCHAR(11) NOT NULL,
  `telefone` VARCHAR(45) NOT NULL,
  `endereco` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `idPaciente_UNIQUE` (`id` ASC) VISIBLE,
  UNIQUE INDEX `cpf_UNIQUE` (`cpf` ASC) VISIBLE,
  UNIQUE INDEX `telefone_UNIQUE` (`telefone` ASC) VISIBLE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `sistema-hospital`.`Doenca`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sistema-hospital`.`Doenca` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `nome` VARCHAR(45) NOT NULL,
  `descricao` VARCHAR(250) NOT NULL,
  `gravidade` INT NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `idDoenca_UNIQUE` (`id` ASC) VISIBLE,
  UNIQUE INDEX `nome_UNIQUE` (`nome` ASC) VISIBLE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `sistema-hospital`.`Clinica_has_Doutor`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sistema-hospital`.`Clinica_has_Doutor` (
  `Clinica_idClinica` INT NOT NULL,
  `Medico_idMedico` INT NOT NULL,
  PRIMARY KEY (`Clinica_idClinica`, `Medico_idMedico`),
  INDEX `fk_Clinica_has_Doutor_Doutor1_idx` (`Medico_idMedico` ASC) VISIBLE,
  INDEX `fk_Clinica_has_Doutor_Clinica1_idx` (`Clinica_idClinica` ASC) VISIBLE,
  CONSTRAINT `fk_Clinica_has_Doutor_Clinica1`
    FOREIGN KEY (`Clinica_idClinica`)
    REFERENCES `sistema-hospital`.`Clinica` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Clinica_has_Doutor_Doutor1`
    FOREIGN KEY (`Medico_idMedico`)
    REFERENCES `sistema-hospital`.`Medico` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `sistema-hospital`.`Paciente_has_Clinica`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sistema-hospital`.`Paciente_has_Clinica` (
  `Paciente_idPaciente` INT NOT NULL,
  `Clinica_idClinica` INT NOT NULL,
  PRIMARY KEY (`Paciente_idPaciente`, `Clinica_idClinica`),
  INDEX `fk_Paciente_has_Clinica_Clinica1_idx` (`Clinica_idClinica` ASC) VISIBLE,
  INDEX `fk_Paciente_has_Clinica_Paciente1_idx` (`Paciente_idPaciente` ASC) VISIBLE,
  CONSTRAINT `fk_Paciente_has_Clinica_Paciente1`
    FOREIGN KEY (`Paciente_idPaciente`)
    REFERENCES `sistema-hospital`.`Paciente` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Paciente_has_Clinica_Clinica1`
    FOREIGN KEY (`Clinica_idClinica`)
    REFERENCES `sistema-hospital`.`Clinica` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `sistema-hospital`.`Doenca_has_Paciente`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sistema-hospital`.`Doenca_has_Paciente` (
  `Doenca_idDoenca` INT NOT NULL,
  `Paciente_idPaciente` INT NOT NULL,
  PRIMARY KEY (`Doenca_idDoenca`, `Paciente_idPaciente`),
  INDEX `fk_Doenca_has_Paciente_Paciente1_idx` (`Paciente_idPaciente` ASC) VISIBLE,
  INDEX `fk_Doenca_has_Paciente_Doenca1_idx` (`Doenca_idDoenca` ASC) VISIBLE,
  CONSTRAINT `fk_Doenca_has_Paciente_Doenca1`
    FOREIGN KEY (`Doenca_idDoenca`)
    REFERENCES `sistema-hospital`.`Doenca` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Doenca_has_Paciente_Paciente1`
    FOREIGN KEY (`Paciente_idPaciente`)
    REFERENCES `sistema-hospital`.`Paciente` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `sistema-hospital`.`Prontuario`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sistema-hospital`.`Prontuario` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `data_visita` DATETIME NULL,
  `situacao_paciente` VARCHAR(450) NULL,
  `historico_familiar` VARCHAR(500) NULL,
  `alergias` VARCHAR(400) NULL,
  `medicacoes` VARCHAR(400) NULL,
  `Clinica_id` INT NOT NULL,
  `Medico_id` INT NOT NULL,
  `Doenca_id` INT NOT NULL,
  `Paciente_id` INT NOT NULL,
  PRIMARY KEY (`id`, `Medico_id`, `Paciente_id`),
  UNIQUE INDEX `id_UNIQUE` (`id` ASC) VISIBLE,
  INDEX `fk_Prontuario_Clinica1_idx` (`Clinica_id` ASC) VISIBLE,
  INDEX `fk_Prontuario_Medico1_idx` (`Medico_id` ASC) VISIBLE,
  INDEX `fk_Prontuario_Doenca1_idx` (`Doenca_id` ASC) VISIBLE,
  INDEX `fk_Prontuario_Paciente1_idx` (`Paciente_id` ASC) VISIBLE,
  CONSTRAINT `fk_Prontuario_Clinica1`
    FOREIGN KEY (`Clinica_id`)
    REFERENCES `sistema-hospital`.`Clinica` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Prontuario_Medico1`
    FOREIGN KEY (`Medico_id`)
    REFERENCES `sistema-hospital`.`Medico` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Prontuario_Doenca1`
    FOREIGN KEY (`Doenca_id`)
    REFERENCES `sistema-hospital`.`Doenca` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Prontuario_Paciente1`
    FOREIGN KEY (`Paciente_id`)
    REFERENCES `sistema-hospital`.`Paciente` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
