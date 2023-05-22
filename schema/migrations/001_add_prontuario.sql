-- MySQL Workbench Synchronization
-- Generated: 2023-05-22 18:47
-- Model: New Model
-- Version: 1.0
-- Project: Name of the project
-- Author: kauan.azevedo

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

ALTER SCHEMA `sistema-hospital`  DEFAULT CHARACTER SET utf8  DEFAULT COLLATE utf8_general_ci ;

ALTER TABLE `sistema-hospital`.`Clinica` 
DROP FOREIGN KEY `fk_Clinica_Hospital`;

ALTER TABLE `sistema-hospital`.`Clinica_has_Doutor` 
DROP FOREIGN KEY `fk_Clinica_has_Doutor_Clinica1`,
DROP FOREIGN KEY `fk_Clinica_has_Doutor_Doutor1`;

ALTER TABLE `sistema-hospital`.`Paciente_has_Clinica` 
DROP FOREIGN KEY `fk_Paciente_has_Clinica_Clinica1`;

ALTER TABLE `sistema-hospital`.`Doenca_has_Paciente` 
DROP FOREIGN KEY `fk_Doenca_has_Paciente_Doenca1`,
DROP FOREIGN KEY `fk_Doenca_has_Paciente_Paciente1`;

ALTER TABLE `sistema-hospital`.`Hospital` 
CHARACTER SET = utf8 , COLLATE = utf8_general_ci ,
CHANGE COLUMN `id` `id` INT(11) NOT NULL AUTO_INCREMENT ,
CHANGE COLUMN `cep` `cep` VARCHAR(9) NOT NULL ;

ALTER TABLE `sistema-hospital`.`Clinica` 
CHARACTER SET = utf8 , COLLATE = utf8_general_ci ,
CHANGE COLUMN `cep` `cep` VARCHAR(9) NOT NULL ;

ALTER TABLE `sistema-hospital`.`Medico` 
CHARACTER SET = utf8 , COLLATE = utf8_general_ci ;

ALTER TABLE `sistema-hospital`.`Paciente` 
CHARACTER SET = utf8 , COLLATE = utf8_general_ci ;

ALTER TABLE `sistema-hospital`.`Doenca` 
CHARACTER SET = utf8 , COLLATE = utf8_general_ci ;

ALTER TABLE `sistema-hospital`.`Clinica_has_Doutor` 
CHARACTER SET = utf8 , COLLATE = utf8_general_ci ;

ALTER TABLE `sistema-hospital`.`Paciente_has_Clinica` 
CHARACTER SET = utf8 , COLLATE = utf8_general_ci ;

ALTER TABLE `sistema-hospital`.`Doenca_has_Paciente` 
CHARACTER SET = utf8 , COLLATE = utf8_general_ci ;

CREATE TABLE IF NOT EXISTS `sistema-hospital`.`Prontuario` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `data_visita` DATETIME NULL DEFAULT NULL,
  `situacao_paciente` VARCHAR(450) NULL DEFAULT NULL,
  `historico_familiar` VARCHAR(500) NULL DEFAULT NULL,
  `alergias` VARCHAR(400) NULL DEFAULT NULL,
  `medicacoes` VARCHAR(400) NULL DEFAULT NULL,
  `Clinica_id` INT(11) NOT NULL,
  `Clinica_Hospital_idHospital` INT(11) NOT NULL,
  `Medico_id` INT(11) NOT NULL,
  `Doenca_id` INT(11) NOT NULL,
  `Paciente_id` INT(11) NOT NULL,
  PRIMARY KEY (`id`, `Medico_id`, `Paciente_id`),
  UNIQUE INDEX `id_UNIQUE` (`id` ASC) VISIBLE,
  INDEX `fk_Prontuario_Clinica1_idx` (`Clinica_id` ASC, `Clinica_Hospital_idHospital` ASC) VISIBLE,
  INDEX `fk_Prontuario_Medico1_idx` (`Medico_id` ASC) VISIBLE,
  INDEX `fk_Prontuario_Doenca1_idx` (`Doenca_id` ASC) VISIBLE,
  INDEX `fk_Prontuario_Paciente1_idx` (`Paciente_id` ASC) VISIBLE,
  CONSTRAINT `fk_Prontuario_Clinica1`
    FOREIGN KEY (`Clinica_id` , `Clinica_Hospital_idHospital`)
    REFERENCES `sistema-hospital`.`Clinica` (`id` , `Hospital_idHospital`)
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
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;

DROP TABLE IF EXISTS `sistema-hospital`.`medico_has_paciente` ;

ALTER TABLE `sistema-hospital`.`Clinica` 
ADD CONSTRAINT `fk_Clinica_Hospital`
  FOREIGN KEY (`Hospital_idHospital`)
  REFERENCES `sistema-hospital`.`Hospital` (`id`)
  ON DELETE NO ACTION
  ON UPDATE NO ACTION;

ALTER TABLE `sistema-hospital`.`Clinica_has_Doutor` 
ADD CONSTRAINT `fk_Clinica_has_Doutor_Clinica1`
  FOREIGN KEY (`Clinica_idClinica` , `Clinica_Hospital_idHospital`)
  REFERENCES `sistema-hospital`.`Clinica` (`id` , `Hospital_idHospital`)
  ON DELETE NO ACTION
  ON UPDATE NO ACTION,
ADD CONSTRAINT `fk_Clinica_has_Doutor_Doutor1`
  FOREIGN KEY (`Doutor_idDoutor`)
  REFERENCES `sistema-hospital`.`Medico` (`id`)
  ON DELETE NO ACTION
  ON UPDATE NO ACTION;

ALTER TABLE `sistema-hospital`.`Paciente_has_Clinica` 
DROP FOREIGN KEY `fk_Paciente_has_Clinica_Paciente1`;

ALTER TABLE `sistema-hospital`.`Paciente_has_Clinica` ADD CONSTRAINT `fk_Paciente_has_Clinica_Paciente1`
  FOREIGN KEY (`Paciente_idPaciente`)
  REFERENCES `sistema-hospital`.`Paciente` (`id`)
  ON DELETE NO ACTION
  ON UPDATE NO ACTION,
ADD CONSTRAINT `fk_Paciente_has_Clinica_Clinica1`
  FOREIGN KEY (`Clinica_idClinica` , `Clinica_Hospital_idHospital`)
  REFERENCES `sistema-hospital`.`Clinica` (`id` , `Hospital_idHospital`)
  ON DELETE NO ACTION
  ON UPDATE NO ACTION;

ALTER TABLE `sistema-hospital`.`Doenca_has_Paciente` 
ADD CONSTRAINT `fk_Doenca_has_Paciente_Doenca1`
  FOREIGN KEY (`Doenca_idDoenca`)
  REFERENCES `sistema-hospital`.`Doenca` (`id`)
  ON DELETE NO ACTION
  ON UPDATE NO ACTION,
ADD CONSTRAINT `fk_Doenca_has_Paciente_Paciente1`
  FOREIGN KEY (`Paciente_idPaciente`)
  REFERENCES `sistema-hospital`.`Paciente` (`id`)
  ON DELETE NO ACTION
  ON UPDATE NO ACTION;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
