-- MariaDB dump 10.19  Distrib 10.4.21-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: file
-- ------------------------------------------------------
-- Server version	10.4.21-MariaDB-1:10.4.21+maria~buster

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `CCD`
--

DROP TABLE IF EXISTS `CCD`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CCD` (
  `iedName` varchar(65) NOT NULL,
  `time` datetime(3) DEFAULT NULL,
  `fileCrc` varchar(11) DEFAULT NULL,
  `crc` varchar(11) DEFAULT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`iedName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CCD`
--

LOCK TABLES `CCD` WRITE;
/*!40000 ALTER TABLE `CCD` DISABLE KEYS */;
INSERT INTO `CCD` VALUES ('P_L2201A','2022-01-05 10:27:52.037','314722FA','314722FA','/home/gdwy/WY909/data/CCD/P_L2201A');
/*!40000 ALTER TABLE `CCD` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `CID`
--

DROP TABLE IF EXISTS `CID`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CID` (
  `iedName` varchar(65) NOT NULL,
  `time` datetime(3) DEFAULT NULL,
  `crc` varchar(11) DEFAULT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`iedName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CID`
--

LOCK TABLES `CID` WRITE;
/*!40000 ALTER TABLE `CID` DISABLE KEYS */;
INSERT INTO `CID` VALUES ('P_L2201A','2022-01-05 10:27:53.341','314722FA','/home/gdwy/WY909/data/CID/P_L2201A'),('WY9D','2022-01-05 10:39:01.181','','/home/gdwy/WY909/data/CID/WY9D');
/*!40000 ALTER TABLE `CID` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `POWER_UPS`
--

DROP TABLE IF EXISTS `POWER_UPS`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `POWER_UPS` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `POWER_UPS`
--

LOCK TABLES `POWER_UPS` WRITE;
/*!40000 ALTER TABLE `POWER_UPS` DISABLE KEYS */;
/*!40000 ALTER TABLE `POWER_UPS` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `POWER_UPS_File`
--

DROP TABLE IF EXISTS `POWER_UPS_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `POWER_UPS_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `POWER_UPS_File`
--

LOCK TABLES `POWER_UPS_File` WRITE;
/*!40000 ALTER TABLE `POWER_UPS_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `POWER_UPS_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5021A`
--

DROP TABLE IF EXISTS `P_B5021A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5021A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5021A`
--

LOCK TABLES `P_B5021A` WRITE;
/*!40000 ALTER TABLE `P_B5021A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5021A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5021A_File`
--

DROP TABLE IF EXISTS `P_B5021A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5021A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5021A_File`
--

LOCK TABLES `P_B5021A_File` WRITE;
/*!40000 ALTER TABLE `P_B5021A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5021A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5021B`
--

DROP TABLE IF EXISTS `P_B5021B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5021B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5021B`
--

LOCK TABLES `P_B5021B` WRITE;
/*!40000 ALTER TABLE `P_B5021B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5021B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5021B_File`
--

DROP TABLE IF EXISTS `P_B5021B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5021B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5021B_File`
--

LOCK TABLES `P_B5021B_File` WRITE;
/*!40000 ALTER TABLE `P_B5021B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5021B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5022A`
--

DROP TABLE IF EXISTS `P_B5022A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5022A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5022A`
--

LOCK TABLES `P_B5022A` WRITE;
/*!40000 ALTER TABLE `P_B5022A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5022A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5022A_File`
--

DROP TABLE IF EXISTS `P_B5022A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5022A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5022A_File`
--

LOCK TABLES `P_B5022A_File` WRITE;
/*!40000 ALTER TABLE `P_B5022A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5022A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5022B`
--

DROP TABLE IF EXISTS `P_B5022B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5022B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5022B`
--

LOCK TABLES `P_B5022B` WRITE;
/*!40000 ALTER TABLE `P_B5022B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5022B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5022B_File`
--

DROP TABLE IF EXISTS `P_B5022B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5022B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5022B_File`
--

LOCK TABLES `P_B5022B_File` WRITE;
/*!40000 ALTER TABLE `P_B5022B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5022B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5023A`
--

DROP TABLE IF EXISTS `P_B5023A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5023A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5023A`
--

LOCK TABLES `P_B5023A` WRITE;
/*!40000 ALTER TABLE `P_B5023A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5023A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5023A_File`
--

DROP TABLE IF EXISTS `P_B5023A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5023A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5023A_File`
--

LOCK TABLES `P_B5023A_File` WRITE;
/*!40000 ALTER TABLE `P_B5023A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5023A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5023B`
--

DROP TABLE IF EXISTS `P_B5023B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5023B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5023B`
--

LOCK TABLES `P_B5023B` WRITE;
/*!40000 ALTER TABLE `P_B5023B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5023B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5023B_File`
--

DROP TABLE IF EXISTS `P_B5023B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5023B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5023B_File`
--

LOCK TABLES `P_B5023B_File` WRITE;
/*!40000 ALTER TABLE `P_B5023B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5023B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5031A`
--

DROP TABLE IF EXISTS `P_B5031A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5031A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5031A`
--

LOCK TABLES `P_B5031A` WRITE;
/*!40000 ALTER TABLE `P_B5031A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5031A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5031A_File`
--

DROP TABLE IF EXISTS `P_B5031A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5031A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5031A_File`
--

LOCK TABLES `P_B5031A_File` WRITE;
/*!40000 ALTER TABLE `P_B5031A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5031A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5031B`
--

DROP TABLE IF EXISTS `P_B5031B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5031B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5031B`
--

LOCK TABLES `P_B5031B` WRITE;
/*!40000 ALTER TABLE `P_B5031B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5031B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5031B_File`
--

DROP TABLE IF EXISTS `P_B5031B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5031B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5031B_File`
--

LOCK TABLES `P_B5031B_File` WRITE;
/*!40000 ALTER TABLE `P_B5031B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5031B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5032A`
--

DROP TABLE IF EXISTS `P_B5032A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5032A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5032A`
--

LOCK TABLES `P_B5032A` WRITE;
/*!40000 ALTER TABLE `P_B5032A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5032A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5032A_File`
--

DROP TABLE IF EXISTS `P_B5032A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5032A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5032A_File`
--

LOCK TABLES `P_B5032A_File` WRITE;
/*!40000 ALTER TABLE `P_B5032A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5032A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5032B`
--

DROP TABLE IF EXISTS `P_B5032B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5032B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5032B`
--

LOCK TABLES `P_B5032B` WRITE;
/*!40000 ALTER TABLE `P_B5032B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5032B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5032B_File`
--

DROP TABLE IF EXISTS `P_B5032B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5032B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5032B_File`
--

LOCK TABLES `P_B5032B_File` WRITE;
/*!40000 ALTER TABLE `P_B5032B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5032B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5033A`
--

DROP TABLE IF EXISTS `P_B5033A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5033A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5033A`
--

LOCK TABLES `P_B5033A` WRITE;
/*!40000 ALTER TABLE `P_B5033A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5033A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5033A_File`
--

DROP TABLE IF EXISTS `P_B5033A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5033A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5033A_File`
--

LOCK TABLES `P_B5033A_File` WRITE;
/*!40000 ALTER TABLE `P_B5033A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5033A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5033B`
--

DROP TABLE IF EXISTS `P_B5033B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5033B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5033B`
--

LOCK TABLES `P_B5033B` WRITE;
/*!40000 ALTER TABLE `P_B5033B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5033B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5033B_File`
--

DROP TABLE IF EXISTS `P_B5033B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5033B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5033B_File`
--

LOCK TABLES `P_B5033B_File` WRITE;
/*!40000 ALTER TABLE `P_B5033B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5033B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5051A`
--

DROP TABLE IF EXISTS `P_B5051A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5051A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5051A`
--

LOCK TABLES `P_B5051A` WRITE;
/*!40000 ALTER TABLE `P_B5051A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5051A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5051A_File`
--

DROP TABLE IF EXISTS `P_B5051A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5051A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5051A_File`
--

LOCK TABLES `P_B5051A_File` WRITE;
/*!40000 ALTER TABLE `P_B5051A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5051A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5051B`
--

DROP TABLE IF EXISTS `P_B5051B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5051B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5051B`
--

LOCK TABLES `P_B5051B` WRITE;
/*!40000 ALTER TABLE `P_B5051B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5051B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5051B_File`
--

DROP TABLE IF EXISTS `P_B5051B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5051B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5051B_File`
--

LOCK TABLES `P_B5051B_File` WRITE;
/*!40000 ALTER TABLE `P_B5051B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5051B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5052A`
--

DROP TABLE IF EXISTS `P_B5052A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5052A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5052A`
--

LOCK TABLES `P_B5052A` WRITE;
/*!40000 ALTER TABLE `P_B5052A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5052A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5052A_File`
--

DROP TABLE IF EXISTS `P_B5052A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5052A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5052A_File`
--

LOCK TABLES `P_B5052A_File` WRITE;
/*!40000 ALTER TABLE `P_B5052A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5052A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5052B`
--

DROP TABLE IF EXISTS `P_B5052B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5052B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5052B`
--

LOCK TABLES `P_B5052B` WRITE;
/*!40000 ALTER TABLE `P_B5052B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5052B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5052B_File`
--

DROP TABLE IF EXISTS `P_B5052B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5052B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5052B_File`
--

LOCK TABLES `P_B5052B_File` WRITE;
/*!40000 ALTER TABLE `P_B5052B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5052B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5053A`
--

DROP TABLE IF EXISTS `P_B5053A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5053A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5053A`
--

LOCK TABLES `P_B5053A` WRITE;
/*!40000 ALTER TABLE `P_B5053A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5053A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5053A_File`
--

DROP TABLE IF EXISTS `P_B5053A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5053A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5053A_File`
--

LOCK TABLES `P_B5053A_File` WRITE;
/*!40000 ALTER TABLE `P_B5053A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5053A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5053B`
--

DROP TABLE IF EXISTS `P_B5053B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5053B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5053B`
--

LOCK TABLES `P_B5053B` WRITE;
/*!40000 ALTER TABLE `P_B5053B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5053B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_B5053B_File`
--

DROP TABLE IF EXISTS `P_B5053B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_B5053B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_B5053B_File`
--

LOCK TABLES `P_B5053B_File` WRITE;
/*!40000 ALTER TABLE `P_B5053B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_B5053B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_C3501X`
--

DROP TABLE IF EXISTS `P_C3501X`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_C3501X` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_C3501X`
--

LOCK TABLES `P_C3501X` WRITE;
/*!40000 ALTER TABLE `P_C3501X` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_C3501X` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_C3501X_File`
--

DROP TABLE IF EXISTS `P_C3501X_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_C3501X_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_C3501X_File`
--

LOCK TABLES `P_C3501X_File` WRITE;
/*!40000 ALTER TABLE `P_C3501X_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_C3501X_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_C3502X`
--

DROP TABLE IF EXISTS `P_C3502X`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_C3502X` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_C3502X`
--

LOCK TABLES `P_C3502X` WRITE;
/*!40000 ALTER TABLE `P_C3502X` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_C3502X` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_C3502X_File`
--

DROP TABLE IF EXISTS `P_C3502X_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_C3502X_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_C3502X_File`
--

LOCK TABLES `P_C3502X_File` WRITE;
/*!40000 ALTER TABLE `P_C3502X_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_C3502X_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L1001`
--

DROP TABLE IF EXISTS `P_L1001`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L1001` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L1001`
--

LOCK TABLES `P_L1001` WRITE;
/*!40000 ALTER TABLE `P_L1001` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L1001` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L1001_File`
--

DROP TABLE IF EXISTS `P_L1001_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L1001_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L1001_File`
--

LOCK TABLES `P_L1001_File` WRITE;
/*!40000 ALTER TABLE `P_L1001_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L1001_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2201A`
--

DROP TABLE IF EXISTS `P_L2201A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2201A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2201A`
--

LOCK TABLES `P_L2201A` WRITE;
/*!40000 ALTER TABLE `P_L2201A` DISABLE KEYS */;
INSERT INTO `P_L2201A` VALUES ('WY9DG_RCD_3856_20190315_132549_194_F',1622769976,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3857_20190315_143043_124_F',1622767116,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3858_20190315_143807_539_S',1622767116,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3964_20190315_193350_635_F',1622767404,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3965_20190315_193444_663_F',1622767372,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3966_20190315_193514_908_F',1622767302,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3967_20190315_193545_858_F',1622767286,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3968_20190315_193616_281_F',1622767272,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3969_20190315_193642_223_F',1622767260,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3970_20190315_193709_243_F',1622767246,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3971_20190315_193752_084_F',1622767238,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3972_20190315_193830_597_F',1622767228,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3973_20190315_193856_740_F',1622767220,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3974_20190315_193924_991_F',1622767212,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3975_20190315_194008_555_F',1622767204,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3976_20190315_194036_416_F',1622767198,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3977_20190315_194101_811_F',1622767190,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3978_20190315_194129_877_F',1622767178,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3979_20190315_194156_307_F',1622767164,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3980_20190315_194222_312_F',1622767154,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3981_20190315_194252_116_F',1622767148,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3982_20190315_194328_264_F',1622767144,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3983_20190315_194356_646_F',1622767140,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3984_20190315_194421_403_F',1622767136,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3985_20190315_202835_017_F',1622767132,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A'),('WY9DG_RCD_3986_20190316_091420_528_F',1622769116,'P_L2201A','/home/gdwy/WY909/data/COMTRADE/P_L2201A');
/*!40000 ALTER TABLE `P_L2201A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2201A_File`
--

DROP TABLE IF EXISTS `P_L2201A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2201A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2201A_File`
--

LOCK TABLES `P_L2201A_File` WRITE;
/*!40000 ALTER TABLE `P_L2201A_File` DISABLE KEYS */;
INSERT INTO `P_L2201A_File` VALUES ('/COMTRADE/WY9DG_RCD_3856_20190315_132549_194_F.DAT',1622769976,10956000,'WY9DG_RCD_3856_20190315_132549_194_F'),('/COMTRADE/WY9DG_RCD_3857_20190315_143043_124_F.CFG',1622767116,22768,'WY9DG_RCD_3857_20190315_143043_124_F'),('/COMTRADE/WY9DG_RCD_3857_20190315_143043_124_F.DAT',1622770028,14429384,'WY9DG_RCD_3857_20190315_143043_124_F'),('/COMTRADE/WY9DG_RCD_3858_20190315_143807_539_S.DMF',1622767116,93306,'WY9DG_RCD_3858_20190315_143807_539_S'),('/COMTRADE/WY9DG_RCD_3858_20190315_143807_539_S.HDR',1622767116,43636,'WY9DG_RCD_3858_20190315_143807_539_S'),('/COMTRADE/WY9DG_RCD_3964_20190315_193350_635_F.CFG',1622767404,22744,'WY9DG_RCD_3964_20190315_193350_635_F'),('/COMTRADE/WY9DG_RCD_3964_20190315_193350_635_F.DAT',1622767426,1799900,'WY9DG_RCD_3964_20190315_193350_635_F'),('/COMTRADE/WY9DG_RCD_3965_20190315_193444_663_F.CFG',1622767372,22756,'WY9DG_RCD_3965_20190315_193444_663_F'),('/COMTRADE/WY9DG_RCD_3965_20190315_193444_663_F.DAT',1622767400,14394856,'WY9DG_RCD_3965_20190315_193444_663_F'),('/COMTRADE/WY9DG_RCD_3965_20190315_193444_663_F.DMF',1622767402,93306,'WY9DG_RCD_3965_20190315_193444_663_F'),('/COMTRADE/WY9DG_RCD_3965_20190315_193444_663_F.HDR',1622767404,45298,'WY9DG_RCD_3965_20190315_193444_663_F'),('/COMTRADE/WY9DG_RCD_3966_20190315_193514_908_F.CFG',1622767302,22756,'WY9DG_RCD_3966_20190315_193514_908_F'),('/COMTRADE/WY9DG_RCD_3966_20190315_193514_908_F.DAT',1622767366,14410128,'WY9DG_RCD_3966_20190315_193514_908_F'),('/COMTRADE/WY9DG_RCD_3966_20190315_193514_908_F.DMF',1622767370,93306,'WY9DG_RCD_3966_20190315_193514_908_F'),('/COMTRADE/WY9DG_RCD_3966_20190315_193514_908_F.HDR',1622767370,45299,'WY9DG_RCD_3966_20190315_193514_908_F'),('/COMTRADE/WY9DG_RCD_3967_20190315_193545_858_F.CFG',1622767286,22756,'WY9DG_RCD_3967_20190315_193545_858_F'),('/COMTRADE/WY9DG_RCD_3967_20190315_193545_858_F.DAT',1622767302,14407472,'WY9DG_RCD_3967_20190315_193545_858_F'),('/COMTRADE/WY9DG_RCD_3967_20190315_193545_858_F.DMF',1622767302,93306,'WY9DG_RCD_3967_20190315_193545_858_F'),('/COMTRADE/WY9DG_RCD_3967_20190315_193545_858_F.HDR',1622767302,45299,'WY9DG_RCD_3967_20190315_193545_858_F'),('/COMTRADE/WY9DG_RCD_3968_20190315_193616_281_F.CFG',1622767272,22744,'WY9DG_RCD_3968_20190315_193616_281_F'),('/COMTRADE/WY9DG_RCD_3968_20190315_193616_281_F.DAT',1622767286,14402824,'WY9DG_RCD_3968_20190315_193616_281_F'),('/COMTRADE/WY9DG_RCD_3968_20190315_193616_281_F.DMF',1622767286,93306,'WY9DG_RCD_3968_20190315_193616_281_F'),('/COMTRADE/WY9DG_RCD_3968_20190315_193616_281_F.HDR',1622767286,46169,'WY9DG_RCD_3968_20190315_193616_281_F'),('/COMTRADE/WY9DG_RCD_3969_20190315_193642_223_F.CFG',1622767260,22756,'WY9DG_RCD_3969_20190315_193642_223_F'),('/COMTRADE/WY9DG_RCD_3969_20190315_193642_223_F.DAT',1622767272,14400168,'WY9DG_RCD_3969_20190315_193642_223_F'),('/COMTRADE/WY9DG_RCD_3969_20190315_193642_223_F.DMF',1622767272,93306,'WY9DG_RCD_3969_20190315_193642_223_F'),('/COMTRADE/WY9DG_RCD_3969_20190315_193642_223_F.HDR',1622767272,46326,'WY9DG_RCD_3969_20190315_193642_223_F'),('/COMTRADE/WY9DG_RCD_3970_20190315_193709_243_F.CFG',1622767246,22744,'WY9DG_RCD_3970_20190315_193709_243_F'),('/COMTRADE/WY9DG_RCD_3970_20190315_193709_243_F.DAT',1622767258,14397512,'WY9DG_RCD_3970_20190315_193709_243_F'),('/COMTRADE/WY9DG_RCD_3970_20190315_193709_243_F.DMF',1622767258,93306,'WY9DG_RCD_3970_20190315_193709_243_F'),('/COMTRADE/WY9DG_RCD_3970_20190315_193709_243_F.HDR',1622767260,46170,'WY9DG_RCD_3970_20190315_193709_243_F'),('/COMTRADE/WY9DG_RCD_3971_20190315_193752_084_F.CFG',1622767238,22744,'WY9DG_RCD_3971_20190315_193752_084_F'),('/COMTRADE/WY9DG_RCD_3971_20190315_193752_084_F.DAT',1622767246,14405480,'WY9DG_RCD_3971_20190315_193752_084_F'),('/COMTRADE/WY9DG_RCD_3971_20190315_193752_084_F.DMF',1622767246,93306,'WY9DG_RCD_3971_20190315_193752_084_F'),('/COMTRADE/WY9DG_RCD_3971_20190315_193752_084_F.HDR',1622767246,46169,'WY9DG_RCD_3971_20190315_193752_084_F'),('/COMTRADE/WY9DG_RCD_3972_20190315_193830_597_F.CFG',1622767228,22744,'WY9DG_RCD_3972_20190315_193830_597_F'),('/COMTRADE/WY9DG_RCD_3972_20190315_193830_597_F.DAT',1622767236,14406144,'WY9DG_RCD_3972_20190315_193830_597_F'),('/COMTRADE/WY9DG_RCD_3972_20190315_193830_597_F.DMF',1622767236,93306,'WY9DG_RCD_3972_20190315_193830_597_F'),('/COMTRADE/WY9DG_RCD_3972_20190315_193830_597_F.HDR',1622767238,46175,'WY9DG_RCD_3972_20190315_193830_597_F'),('/COMTRADE/WY9DG_RCD_3973_20190315_193856_740_F.CFG',1622767220,22756,'WY9DG_RCD_3973_20190315_193856_740_F'),('/COMTRADE/WY9DG_RCD_3973_20190315_193856_740_F.DAT',1622767228,14403488,'WY9DG_RCD_3973_20190315_193856_740_F'),('/COMTRADE/WY9DG_RCD_3973_20190315_193856_740_F.DMF',1622767228,93306,'WY9DG_RCD_3973_20190315_193856_740_F'),('/COMTRADE/WY9DG_RCD_3973_20190315_193856_740_F.HDR',1622767228,46325,'WY9DG_RCD_3973_20190315_193856_740_F'),('/COMTRADE/WY9DG_RCD_3974_20190315_193924_991_F.CFG',1622767212,22744,'WY9DG_RCD_3974_20190315_193924_991_F'),('/COMTRADE/WY9DG_RCD_3974_20190315_193924_991_F.DAT',1622767218,14409464,'WY9DG_RCD_3974_20190315_193924_991_F'),('/COMTRADE/WY9DG_RCD_3974_20190315_193924_991_F.DMF',1622767220,93306,'WY9DG_RCD_3974_20190315_193924_991_F'),('/COMTRADE/WY9DG_RCD_3974_20190315_193924_991_F.HDR',1622767220,46173,'WY9DG_RCD_3974_20190315_193924_991_F'),('/COMTRADE/WY9DG_RCD_3975_20190315_194008_555_F.CFG',1622767204,22768,'WY9DG_RCD_3975_20190315_194008_555_F'),('/COMTRADE/WY9DG_RCD_3975_20190315_194008_555_F.DAT',1622767210,14400168,'WY9DG_RCD_3975_20190315_194008_555_F'),('/COMTRADE/WY9DG_RCD_3975_20190315_194008_555_F.DMF',1622767210,93306,'WY9DG_RCD_3975_20190315_194008_555_F'),('/COMTRADE/WY9DG_RCD_3975_20190315_194008_555_F.HDR',1622767210,45467,'WY9DG_RCD_3975_20190315_194008_555_F'),('/COMTRADE/WY9DG_RCD_3976_20190315_194036_416_F.CFG',1622767198,22768,'WY9DG_RCD_3976_20190315_194036_416_F'),('/COMTRADE/WY9DG_RCD_3976_20190315_194036_416_F.DAT',1622767204,14400168,'WY9DG_RCD_3976_20190315_194036_416_F'),('/COMTRADE/WY9DG_RCD_3976_20190315_194036_416_F.DMF',1622767204,93306,'WY9DG_RCD_3976_20190315_194036_416_F'),('/COMTRADE/WY9DG_RCD_3976_20190315_194036_416_F.HDR',1622767204,45467,'WY9DG_RCD_3976_20190315_194036_416_F'),('/COMTRADE/WY9DG_RCD_3977_20190315_194101_811_F.CFG',1622767190,22756,'WY9DG_RCD_3977_20190315_194101_811_F'),('/COMTRADE/WY9DG_RCD_3977_20190315_194101_811_F.DAT',1622767196,14408136,'WY9DG_RCD_3977_20190315_194101_811_F'),('/COMTRADE/WY9DG_RCD_3977_20190315_194101_811_F.DMF',1622767198,93306,'WY9DG_RCD_3977_20190315_194101_811_F'),('/COMTRADE/WY9DG_RCD_3977_20190315_194101_811_F.HDR',1622767198,45296,'WY9DG_RCD_3977_20190315_194101_811_F'),('/COMTRADE/WY9DG_RCD_3978_20190315_194129_877_F.CFG',1622767178,22756,'WY9DG_RCD_3978_20190315_194129_877_F'),('/COMTRADE/WY9DG_RCD_3978_20190315_194129_877_F.DAT',1622767190,14412120,'WY9DG_RCD_3978_20190315_194129_877_F'),('/COMTRADE/WY9DG_RCD_3978_20190315_194129_877_F.DMF',1622767190,93306,'WY9DG_RCD_3978_20190315_194129_877_F'),('/COMTRADE/WY9DG_RCD_3978_20190315_194129_877_F.HDR',1622767190,46344,'WY9DG_RCD_3978_20190315_194129_877_F'),('/COMTRADE/WY9DG_RCD_3979_20190315_194156_307_F.CFG',1622767164,22756,'WY9DG_RCD_3979_20190315_194156_307_F'),('/COMTRADE/WY9DG_RCD_3979_20190315_194156_307_F.DAT',1622767176,14408136,'WY9DG_RCD_3979_20190315_194156_307_F'),('/COMTRADE/WY9DG_RCD_3979_20190315_194156_307_F.DMF',1622767176,93306,'WY9DG_RCD_3979_20190315_194156_307_F'),('/COMTRADE/WY9DG_RCD_3979_20190315_194156_307_F.HDR',1622767176,46338,'WY9DG_RCD_3979_20190315_194156_307_F'),('/COMTRADE/WY9DG_RCD_3980_20190315_194222_312_F.CFG',1622767154,22756,'WY9DG_RCD_3980_20190315_194222_312_F'),('/COMTRADE/WY9DG_RCD_3980_20190315_194222_312_F.DAT',1622767162,14412784,'WY9DG_RCD_3980_20190315_194222_312_F'),('/COMTRADE/WY9DG_RCD_3980_20190315_194222_312_F.DMF',1622767162,93306,'WY9DG_RCD_3980_20190315_194222_312_F'),('/COMTRADE/WY9DG_RCD_3980_20190315_194222_312_F.HDR',1622767164,46344,'WY9DG_RCD_3980_20190315_194222_312_F'),('/COMTRADE/WY9DG_RCD_3981_20190315_194252_116_F.CFG',1622767148,22744,'WY9DG_RCD_3981_20190315_194252_116_F'),('/COMTRADE/WY9DG_RCD_3981_20190315_194252_116_F.DAT',1622767154,14403488,'WY9DG_RCD_3981_20190315_194252_116_F'),('/COMTRADE/WY9DG_RCD_3981_20190315_194252_116_F.DMF',1622767154,93306,'WY9DG_RCD_3981_20190315_194252_116_F'),('/COMTRADE/WY9DG_RCD_3981_20190315_194252_116_F.HDR',1622767154,46172,'WY9DG_RCD_3981_20190315_194252_116_F'),('/COMTRADE/WY9DG_RCD_3982_20190315_194328_264_F.CFG',1622767144,22768,'WY9DG_RCD_3982_20190315_194328_264_F'),('/COMTRADE/WY9DG_RCD_3982_20190315_194328_264_F.DAT',1622767148,14407472,'WY9DG_RCD_3982_20190315_194328_264_F'),('/COMTRADE/WY9DG_RCD_3982_20190315_194328_264_F.DMF',1622767148,93306,'WY9DG_RCD_3982_20190315_194328_264_F'),('/COMTRADE/WY9DG_RCD_3982_20190315_194328_264_F.HDR',1622767148,46497,'WY9DG_RCD_3982_20190315_194328_264_F'),('/COMTRADE/WY9DG_RCD_3983_20190315_194356_646_F.CFG',1622767140,22768,'WY9DG_RCD_3983_20190315_194356_646_F'),('/COMTRADE/WY9DG_RCD_3983_20190315_194356_646_F.DAT',1622767142,14411456,'WY9DG_RCD_3983_20190315_194356_646_F'),('/COMTRADE/WY9DG_RCD_3983_20190315_194356_646_F.DMF',1622767142,93306,'WY9DG_RCD_3983_20190315_194356_646_F'),('/COMTRADE/WY9DG_RCD_3983_20190315_194356_646_F.HDR',1622767142,46503,'WY9DG_RCD_3983_20190315_194356_646_F'),('/COMTRADE/WY9DG_RCD_3984_20190315_194421_403_F.CFG',1622767136,22756,'WY9DG_RCD_3984_20190315_194421_403_F'),('/COMTRADE/WY9DG_RCD_3984_20190315_194421_403_F.DAT',1622767138,14406144,'WY9DG_RCD_3984_20190315_194421_403_F'),('/COMTRADE/WY9DG_RCD_3984_20190315_194421_403_F.DMF',1622767138,93306,'WY9DG_RCD_3984_20190315_194421_403_F'),('/COMTRADE/WY9DG_RCD_3984_20190315_194421_403_F.HDR',1622767138,46340,'WY9DG_RCD_3984_20190315_194421_403_F'),('/COMTRADE/WY9DG_RCD_3985_20190315_202835_017_F.CFG',1622767132,22708,'WY9DG_RCD_3985_20190315_202835_017_F'),('/COMTRADE/WY9DG_RCD_3985_20190315_202835_017_F.DAT',1622767134,10956000,'WY9DG_RCD_3985_20190315_202835_017_F'),('/COMTRADE/WY9DG_RCD_3985_20190315_202835_017_F.DMF',1622767134,93306,'WY9DG_RCD_3985_20190315_202835_017_F'),('/COMTRADE/WY9DG_RCD_3985_20190315_202835_017_F.HDR',1622767136,43782,'WY9DG_RCD_3985_20190315_202835_017_F'),('/COMTRADE/WY9DG_RCD_3986_20190316_091420_528_F.CFG',1622769116,22720,'WY9DG_RCD_3986_20190316_091420_528_F'),('/COMTRADE/WY9DG_RCD_3986_20190316_091420_528_F.DAT',1622769192,11238200,'WY9DG_RCD_3986_20190316_091420_528_F'),('/COMTRADE/WY9DG_RCD_3986_20190316_091420_528_F.DMF',1622769116,93306,'WY9DG_RCD_3986_20190316_091420_528_F'),('/COMTRADE/WY9DG_RCD_3986_20190316_091420_528_F.HDR',1622767132,43951,'WY9DG_RCD_3986_20190316_091420_528_F');
/*!40000 ALTER TABLE `P_L2201A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2201B`
--

DROP TABLE IF EXISTS `P_L2201B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2201B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2201B`
--

LOCK TABLES `P_L2201B` WRITE;
/*!40000 ALTER TABLE `P_L2201B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2201B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2201B_File`
--

DROP TABLE IF EXISTS `P_L2201B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2201B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2201B_File`
--

LOCK TABLES `P_L2201B_File` WRITE;
/*!40000 ALTER TABLE `P_L2201B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2201B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2202A`
--

DROP TABLE IF EXISTS `P_L2202A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2202A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2202A`
--

LOCK TABLES `P_L2202A` WRITE;
/*!40000 ALTER TABLE `P_L2202A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2202A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2202A_File`
--

DROP TABLE IF EXISTS `P_L2202A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2202A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2202A_File`
--

LOCK TABLES `P_L2202A_File` WRITE;
/*!40000 ALTER TABLE `P_L2202A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2202A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2202B`
--

DROP TABLE IF EXISTS `P_L2202B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2202B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2202B`
--

LOCK TABLES `P_L2202B` WRITE;
/*!40000 ALTER TABLE `P_L2202B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2202B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2202B_File`
--

DROP TABLE IF EXISTS `P_L2202B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2202B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2202B_File`
--

LOCK TABLES `P_L2202B_File` WRITE;
/*!40000 ALTER TABLE `P_L2202B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2202B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2206A`
--

DROP TABLE IF EXISTS `P_L2206A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2206A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2206A`
--

LOCK TABLES `P_L2206A` WRITE;
/*!40000 ALTER TABLE `P_L2206A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2206A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2206A_File`
--

DROP TABLE IF EXISTS `P_L2206A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2206A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2206A_File`
--

LOCK TABLES `P_L2206A_File` WRITE;
/*!40000 ALTER TABLE `P_L2206A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2206A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2206B`
--

DROP TABLE IF EXISTS `P_L2206B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2206B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2206B`
--

LOCK TABLES `P_L2206B` WRITE;
/*!40000 ALTER TABLE `P_L2206B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2206B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2206B_File`
--

DROP TABLE IF EXISTS `P_L2206B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2206B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2206B_File`
--

LOCK TABLES `P_L2206B_File` WRITE;
/*!40000 ALTER TABLE `P_L2206B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2206B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2208A`
--

DROP TABLE IF EXISTS `P_L2208A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2208A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2208A`
--

LOCK TABLES `P_L2208A` WRITE;
/*!40000 ALTER TABLE `P_L2208A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2208A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2208A_File`
--

DROP TABLE IF EXISTS `P_L2208A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2208A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2208A_File`
--

LOCK TABLES `P_L2208A_File` WRITE;
/*!40000 ALTER TABLE `P_L2208A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2208A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2208B`
--

DROP TABLE IF EXISTS `P_L2208B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2208B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2208B`
--

LOCK TABLES `P_L2208B` WRITE;
/*!40000 ALTER TABLE `P_L2208B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2208B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2208B_File`
--

DROP TABLE IF EXISTS `P_L2208B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2208B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2208B_File`
--

LOCK TABLES `P_L2208B_File` WRITE;
/*!40000 ALTER TABLE `P_L2208B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2208B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2210A`
--

DROP TABLE IF EXISTS `P_L2210A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2210A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2210A`
--

LOCK TABLES `P_L2210A` WRITE;
/*!40000 ALTER TABLE `P_L2210A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2210A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2210A_File`
--

DROP TABLE IF EXISTS `P_L2210A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2210A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2210A_File`
--

LOCK TABLES `P_L2210A_File` WRITE;
/*!40000 ALTER TABLE `P_L2210A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2210A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2210B`
--

DROP TABLE IF EXISTS `P_L2210B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2210B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2210B`
--

LOCK TABLES `P_L2210B` WRITE;
/*!40000 ALTER TABLE `P_L2210B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2210B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2210B_File`
--

DROP TABLE IF EXISTS `P_L2210B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2210B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2210B_File`
--

LOCK TABLES `P_L2210B_File` WRITE;
/*!40000 ALTER TABLE `P_L2210B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2210B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2213A`
--

DROP TABLE IF EXISTS `P_L2213A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2213A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2213A`
--

LOCK TABLES `P_L2213A` WRITE;
/*!40000 ALTER TABLE `P_L2213A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2213A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2213A_File`
--

DROP TABLE IF EXISTS `P_L2213A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2213A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2213A_File`
--

LOCK TABLES `P_L2213A_File` WRITE;
/*!40000 ALTER TABLE `P_L2213A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2213A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2213B`
--

DROP TABLE IF EXISTS `P_L2213B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2213B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2213B`
--

LOCK TABLES `P_L2213B` WRITE;
/*!40000 ALTER TABLE `P_L2213B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2213B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2213B_File`
--

DROP TABLE IF EXISTS `P_L2213B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2213B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2213B_File`
--

LOCK TABLES `P_L2213B_File` WRITE;
/*!40000 ALTER TABLE `P_L2213B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2213B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2216A`
--

DROP TABLE IF EXISTS `P_L2216A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2216A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2216A`
--

LOCK TABLES `P_L2216A` WRITE;
/*!40000 ALTER TABLE `P_L2216A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2216A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2216A_File`
--

DROP TABLE IF EXISTS `P_L2216A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2216A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2216A_File`
--

LOCK TABLES `P_L2216A_File` WRITE;
/*!40000 ALTER TABLE `P_L2216A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2216A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2216B`
--

DROP TABLE IF EXISTS `P_L2216B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2216B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2216B`
--

LOCK TABLES `P_L2216B` WRITE;
/*!40000 ALTER TABLE `P_L2216B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2216B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2216B_File`
--

DROP TABLE IF EXISTS `P_L2216B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2216B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2216B_File`
--

LOCK TABLES `P_L2216B_File` WRITE;
/*!40000 ALTER TABLE `P_L2216B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2216B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2218A`
--

DROP TABLE IF EXISTS `P_L2218A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2218A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2218A`
--

LOCK TABLES `P_L2218A` WRITE;
/*!40000 ALTER TABLE `P_L2218A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2218A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2218A_File`
--

DROP TABLE IF EXISTS `P_L2218A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2218A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2218A_File`
--

LOCK TABLES `P_L2218A_File` WRITE;
/*!40000 ALTER TABLE `P_L2218A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2218A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2218B`
--

DROP TABLE IF EXISTS `P_L2218B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2218B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2218B`
--

LOCK TABLES `P_L2218B` WRITE;
/*!40000 ALTER TABLE `P_L2218B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2218B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2218B_File`
--

DROP TABLE IF EXISTS `P_L2218B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2218B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2218B_File`
--

LOCK TABLES `P_L2218B_File` WRITE;
/*!40000 ALTER TABLE `P_L2218B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2218B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2221A`
--

DROP TABLE IF EXISTS `P_L2221A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2221A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2221A`
--

LOCK TABLES `P_L2221A` WRITE;
/*!40000 ALTER TABLE `P_L2221A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2221A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2221A_File`
--

DROP TABLE IF EXISTS `P_L2221A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2221A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2221A_File`
--

LOCK TABLES `P_L2221A_File` WRITE;
/*!40000 ALTER TABLE `P_L2221A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2221A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2221B`
--

DROP TABLE IF EXISTS `P_L2221B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2221B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2221B`
--

LOCK TABLES `P_L2221B` WRITE;
/*!40000 ALTER TABLE `P_L2221B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2221B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2221B_File`
--

DROP TABLE IF EXISTS `P_L2221B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2221B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2221B_File`
--

LOCK TABLES `P_L2221B_File` WRITE;
/*!40000 ALTER TABLE `P_L2221B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2221B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2222A`
--

DROP TABLE IF EXISTS `P_L2222A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2222A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2222A`
--

LOCK TABLES `P_L2222A` WRITE;
/*!40000 ALTER TABLE `P_L2222A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2222A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2222A_File`
--

DROP TABLE IF EXISTS `P_L2222A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2222A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2222A_File`
--

LOCK TABLES `P_L2222A_File` WRITE;
/*!40000 ALTER TABLE `P_L2222A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2222A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2222B`
--

DROP TABLE IF EXISTS `P_L2222B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2222B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2222B`
--

LOCK TABLES `P_L2222B` WRITE;
/*!40000 ALTER TABLE `P_L2222B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2222B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L2222B_File`
--

DROP TABLE IF EXISTS `P_L2222B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L2222B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L2222B_File`
--

LOCK TABLES `P_L2222B_File` WRITE;
/*!40000 ALTER TABLE `P_L2222B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L2222B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5023A`
--

DROP TABLE IF EXISTS `P_L5023A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5023A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5023A`
--

LOCK TABLES `P_L5023A` WRITE;
/*!40000 ALTER TABLE `P_L5023A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5023A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5023A_File`
--

DROP TABLE IF EXISTS `P_L5023A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5023A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5023A_File`
--

LOCK TABLES `P_L5023A_File` WRITE;
/*!40000 ALTER TABLE `P_L5023A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5023A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5023B`
--

DROP TABLE IF EXISTS `P_L5023B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5023B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5023B`
--

LOCK TABLES `P_L5023B` WRITE;
/*!40000 ALTER TABLE `P_L5023B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5023B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5023B_File`
--

DROP TABLE IF EXISTS `P_L5023B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5023B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5023B_File`
--

LOCK TABLES `P_L5023B_File` WRITE;
/*!40000 ALTER TABLE `P_L5023B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5023B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5031A`
--

DROP TABLE IF EXISTS `P_L5031A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5031A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5031A`
--

LOCK TABLES `P_L5031A` WRITE;
/*!40000 ALTER TABLE `P_L5031A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5031A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5031A_File`
--

DROP TABLE IF EXISTS `P_L5031A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5031A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5031A_File`
--

LOCK TABLES `P_L5031A_File` WRITE;
/*!40000 ALTER TABLE `P_L5031A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5031A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5031B`
--

DROP TABLE IF EXISTS `P_L5031B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5031B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5031B`
--

LOCK TABLES `P_L5031B` WRITE;
/*!40000 ALTER TABLE `P_L5031B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5031B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5031B_File`
--

DROP TABLE IF EXISTS `P_L5031B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5031B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5031B_File`
--

LOCK TABLES `P_L5031B_File` WRITE;
/*!40000 ALTER TABLE `P_L5031B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5031B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5033A`
--

DROP TABLE IF EXISTS `P_L5033A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5033A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5033A`
--

LOCK TABLES `P_L5033A` WRITE;
/*!40000 ALTER TABLE `P_L5033A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5033A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5033A_File`
--

DROP TABLE IF EXISTS `P_L5033A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5033A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5033A_File`
--

LOCK TABLES `P_L5033A_File` WRITE;
/*!40000 ALTER TABLE `P_L5033A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5033A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5033B`
--

DROP TABLE IF EXISTS `P_L5033B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5033B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5033B`
--

LOCK TABLES `P_L5033B` WRITE;
/*!40000 ALTER TABLE `P_L5033B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5033B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5033B_File`
--

DROP TABLE IF EXISTS `P_L5033B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5033B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5033B_File`
--

LOCK TABLES `P_L5033B_File` WRITE;
/*!40000 ALTER TABLE `P_L5033B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5033B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5053A`
--

DROP TABLE IF EXISTS `P_L5053A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5053A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5053A`
--

LOCK TABLES `P_L5053A` WRITE;
/*!40000 ALTER TABLE `P_L5053A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5053A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5053A_File`
--

DROP TABLE IF EXISTS `P_L5053A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5053A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5053A_File`
--

LOCK TABLES `P_L5053A_File` WRITE;
/*!40000 ALTER TABLE `P_L5053A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5053A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5053B`
--

DROP TABLE IF EXISTS `P_L5053B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5053B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5053B`
--

LOCK TABLES `P_L5053B` WRITE;
/*!40000 ALTER TABLE `P_L5053B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5053B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_L5053B_File`
--

DROP TABLE IF EXISTS `P_L5053B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_L5053B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_L5053B_File`
--

LOCK TABLES `P_L5053B_File` WRITE;
/*!40000 ALTER TABLE `P_L5053B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_L5053B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M2212A`
--

DROP TABLE IF EXISTS `P_M2212A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M2212A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M2212A`
--

LOCK TABLES `P_M2212A` WRITE;
/*!40000 ALTER TABLE `P_M2212A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M2212A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M2212A_File`
--

DROP TABLE IF EXISTS `P_M2212A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M2212A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M2212A_File`
--

LOCK TABLES `P_M2212A_File` WRITE;
/*!40000 ALTER TABLE `P_M2212A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M2212A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M2212B`
--

DROP TABLE IF EXISTS `P_M2212B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M2212B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M2212B`
--

LOCK TABLES `P_M2212B` WRITE;
/*!40000 ALTER TABLE `P_M2212B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M2212B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M2212B_File`
--

DROP TABLE IF EXISTS `P_M2212B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M2212B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M2212B_File`
--

LOCK TABLES `P_M2212B_File` WRITE;
/*!40000 ALTER TABLE `P_M2212B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M2212B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M2256A`
--

DROP TABLE IF EXISTS `P_M2256A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M2256A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M2256A`
--

LOCK TABLES `P_M2256A` WRITE;
/*!40000 ALTER TABLE `P_M2256A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M2256A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M2256A_File`
--

DROP TABLE IF EXISTS `P_M2256A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M2256A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M2256A_File`
--

LOCK TABLES `P_M2256A_File` WRITE;
/*!40000 ALTER TABLE `P_M2256A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M2256A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M2256B`
--

DROP TABLE IF EXISTS `P_M2256B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M2256B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M2256B`
--

LOCK TABLES `P_M2256B` WRITE;
/*!40000 ALTER TABLE `P_M2256B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M2256B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M2256B_File`
--

DROP TABLE IF EXISTS `P_M2256B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M2256B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M2256B_File`
--

LOCK TABLES `P_M2256B_File` WRITE;
/*!40000 ALTER TABLE `P_M2256B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M2256B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M3502X`
--

DROP TABLE IF EXISTS `P_M3502X`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M3502X` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M3502X`
--

LOCK TABLES `P_M3502X` WRITE;
/*!40000 ALTER TABLE `P_M3502X` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M3502X` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M3502X_File`
--

DROP TABLE IF EXISTS `P_M3502X_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M3502X_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M3502X_File`
--

LOCK TABLES `P_M3502X_File` WRITE;
/*!40000 ALTER TABLE `P_M3502X_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M3502X_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M3503X`
--

DROP TABLE IF EXISTS `P_M3503X`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M3503X` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M3503X`
--

LOCK TABLES `P_M3503X` WRITE;
/*!40000 ALTER TABLE `P_M3503X` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M3503X` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M3503X_File`
--

DROP TABLE IF EXISTS `P_M3503X_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M3503X_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M3503X_File`
--

LOCK TABLES `P_M3503X_File` WRITE;
/*!40000 ALTER TABLE `P_M3503X_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M3503X_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M5001A`
--

DROP TABLE IF EXISTS `P_M5001A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M5001A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M5001A`
--

LOCK TABLES `P_M5001A` WRITE;
/*!40000 ALTER TABLE `P_M5001A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M5001A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M5001A_File`
--

DROP TABLE IF EXISTS `P_M5001A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M5001A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M5001A_File`
--

LOCK TABLES `P_M5001A_File` WRITE;
/*!40000 ALTER TABLE `P_M5001A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M5001A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M5001B`
--

DROP TABLE IF EXISTS `P_M5001B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M5001B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M5001B`
--

LOCK TABLES `P_M5001B` WRITE;
/*!40000 ALTER TABLE `P_M5001B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M5001B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M5001B_File`
--

DROP TABLE IF EXISTS `P_M5001B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M5001B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M5001B_File`
--

LOCK TABLES `P_M5001B_File` WRITE;
/*!40000 ALTER TABLE `P_M5001B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M5001B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M5002A`
--

DROP TABLE IF EXISTS `P_M5002A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M5002A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M5002A`
--

LOCK TABLES `P_M5002A` WRITE;
/*!40000 ALTER TABLE `P_M5002A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M5002A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M5002A_File`
--

DROP TABLE IF EXISTS `P_M5002A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M5002A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M5002A_File`
--

LOCK TABLES `P_M5002A_File` WRITE;
/*!40000 ALTER TABLE `P_M5002A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M5002A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M5002B`
--

DROP TABLE IF EXISTS `P_M5002B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M5002B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M5002B`
--

LOCK TABLES `P_M5002B` WRITE;
/*!40000 ALTER TABLE `P_M5002B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M5002B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_M5002B_File`
--

DROP TABLE IF EXISTS `P_M5002B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_M5002B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_M5002B_File`
--

LOCK TABLES `P_M5002B_File` WRITE;
/*!40000 ALTER TABLE `P_M5002B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_M5002B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_S1000X`
--

DROP TABLE IF EXISTS `P_S1000X`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_S1000X` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_S1000X`
--

LOCK TABLES `P_S1000X` WRITE;
/*!40000 ALTER TABLE `P_S1000X` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_S1000X` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_S1000X_File`
--

DROP TABLE IF EXISTS `P_S1000X_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_S1000X_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_S1000X_File`
--

LOCK TABLES `P_S1000X_File` WRITE;
/*!40000 ALTER TABLE `P_S1000X_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_S1000X_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_S3501X`
--

DROP TABLE IF EXISTS `P_S3501X`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_S3501X` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_S3501X`
--

LOCK TABLES `P_S3501X` WRITE;
/*!40000 ALTER TABLE `P_S3501X` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_S3501X` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_S3501X_File`
--

DROP TABLE IF EXISTS `P_S3501X_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_S3501X_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_S3501X_File`
--

LOCK TABLES `P_S3501X_File` WRITE;
/*!40000 ALTER TABLE `P_S3501X_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_S3501X_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_S3502X`
--

DROP TABLE IF EXISTS `P_S3502X`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_S3502X` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_S3502X`
--

LOCK TABLES `P_S3502X` WRITE;
/*!40000 ALTER TABLE `P_S3502X` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_S3502X` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_S3502X_File`
--

DROP TABLE IF EXISTS `P_S3502X_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_S3502X_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_S3502X_File`
--

LOCK TABLES `P_S3502X_File` WRITE;
/*!40000 ALTER TABLE `P_S3502X_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_S3502X_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_T5002A`
--

DROP TABLE IF EXISTS `P_T5002A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_T5002A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_T5002A`
--

LOCK TABLES `P_T5002A` WRITE;
/*!40000 ALTER TABLE `P_T5002A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_T5002A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_T5002A_File`
--

DROP TABLE IF EXISTS `P_T5002A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_T5002A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_T5002A_File`
--

LOCK TABLES `P_T5002A_File` WRITE;
/*!40000 ALTER TABLE `P_T5002A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_T5002A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_T5002B`
--

DROP TABLE IF EXISTS `P_T5002B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_T5002B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_T5002B`
--

LOCK TABLES `P_T5002B` WRITE;
/*!40000 ALTER TABLE `P_T5002B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_T5002B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_T5002B_File`
--

DROP TABLE IF EXISTS `P_T5002B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_T5002B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_T5002B_File`
--

LOCK TABLES `P_T5002B_File` WRITE;
/*!40000 ALTER TABLE `P_T5002B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_T5002B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_T5003A`
--

DROP TABLE IF EXISTS `P_T5003A`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_T5003A` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_T5003A`
--

LOCK TABLES `P_T5003A` WRITE;
/*!40000 ALTER TABLE `P_T5003A` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_T5003A` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_T5003A_File`
--

DROP TABLE IF EXISTS `P_T5003A_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_T5003A_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_T5003A_File`
--

LOCK TABLES `P_T5003A_File` WRITE;
/*!40000 ALTER TABLE `P_T5003A_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_T5003A_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_T5003B`
--

DROP TABLE IF EXISTS `P_T5003B`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_T5003B` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_T5003B`
--

LOCK TABLES `P_T5003B` WRITE;
/*!40000 ALTER TABLE `P_T5003B` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_T5003B` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_T5003B_File`
--

DROP TABLE IF EXISTS `P_T5003B_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_T5003B_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_T5003B_File`
--

LOCK TABLES `P_T5003B_File` WRITE;
/*!40000 ALTER TABLE `P_T5003B_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_T5003B_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_X3501X`
--

DROP TABLE IF EXISTS `P_X3501X`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_X3501X` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_X3501X`
--

LOCK TABLES `P_X3501X` WRITE;
/*!40000 ALTER TABLE `P_X3501X` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_X3501X` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_X3501X_File`
--

DROP TABLE IF EXISTS `P_X3501X_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_X3501X_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_X3501X_File`
--

LOCK TABLES `P_X3501X_File` WRITE;
/*!40000 ALTER TABLE `P_X3501X_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_X3501X_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_X3502X`
--

DROP TABLE IF EXISTS `P_X3502X`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_X3502X` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_X3502X`
--

LOCK TABLES `P_X3502X` WRITE;
/*!40000 ALTER TABLE `P_X3502X` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_X3502X` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_X3502X_File`
--

DROP TABLE IF EXISTS `P_X3502X_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_X3502X_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_X3502X_File`
--

LOCK TABLES `P_X3502X_File` WRITE;
/*!40000 ALTER TABLE `P_X3502X_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_X3502X_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_X3503X`
--

DROP TABLE IF EXISTS `P_X3503X`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_X3503X` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_X3503X`
--

LOCK TABLES `P_X3503X` WRITE;
/*!40000 ALTER TABLE `P_X3503X` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_X3503X` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_X3503X_File`
--

DROP TABLE IF EXISTS `P_X3503X_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_X3503X_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_X3503X_File`
--

LOCK TABLES `P_X3503X_File` WRITE;
/*!40000 ALTER TABLE `P_X3503X_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_X3503X_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_X3504X`
--

DROP TABLE IF EXISTS `P_X3504X`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_X3504X` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_X3504X`
--

LOCK TABLES `P_X3504X` WRITE;
/*!40000 ALTER TABLE `P_X3504X` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_X3504X` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P_X3504X_File`
--

DROP TABLE IF EXISTS `P_X3504X_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P_X3504X_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P_X3504X_File`
--

LOCK TABLES `P_X3504X_File` WRITE;
/*!40000 ALTER TABLE `P_X3504X_File` DISABLE KEYS */;
/*!40000 ALTER TABLE `P_X3504X_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TEMPLATE`
--

DROP TABLE IF EXISTS `TEMPLATE`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TEMPLATE` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TEMPLATE`
--

LOCK TABLES `TEMPLATE` WRITE;
/*!40000 ALTER TABLE `TEMPLATE` DISABLE KEYS */;
INSERT INTO `TEMPLATE` VALUES ('TEMPLATE_RCD_157_20210914_115054_930_S',1631591414,'TEMPLATE','/home/gdwy/WY909/data/COMTRADE/TEMPLATE'),('TEMPLATE_RCD_158_20210914_115058_030_S',1631591418,'TEMPLATE','/home/gdwy/WY909/data/COMTRADE/TEMPLATE'),('TEMPLATE_RCD_162_20211028_174341_211_S',1635414162,'TEMPLATE','/home/gdwy/WY909/data/COMTRADE/TEMPLATE'),('TEMPLATE_RCD_186_20211228_215212_009_S',1640699534,'TEMPLATE','/home/gdwy/WY909/data/COMTRADE/TEMPLATE'),('TEMPLATE_RCD_230_20211231_161647_983_F',1640938626,'TEMPLATE','/home/gdwy/WY909/data/COMTRADE/TEMPLATE'),('TEMPLATE_RCD_232_20211231_174720_292_S',1640944044,'TEMPLATE','/home/gdwy/WY909/data/COMTRADE/TEMPLATE'),('TEMPLATE_RCD_236_20220104_141855_960_F',1641277146,'TEMPLATE','/home/gdwy/WY909/data/COMTRADE/TEMPLATE'),('TEMPLATE_RCD_237_20220104_142059_443_F',1641277264,'TEMPLATE','/home/gdwy/WY909/data/COMTRADE/TEMPLATE'),('TEMPLATE_RCD_238_20220104_142131_084_F',1641277298,'TEMPLATE','/home/gdwy/WY909/data/COMTRADE/TEMPLATE'),('TEMPLATE_RCD_239_20220104_142402_234_F',1641277448,'TEMPLATE','/home/gdwy/WY909/data/COMTRADE/TEMPLATE'),('TEMPLATE_RCD_240_20220104_143641_669_F',1641278206,'TEMPLATE','/home/gdwy/WY909/data/COMTRADE/TEMPLATE'),('TEMPLATE_RCD_241_20220104_151246_176_F',1641280372,'TEMPLATE','/home/gdwy/WY909/data/COMTRADE/TEMPLATE'),('TEMPLATE_RCD_242_20220104_152505_967_F',1641281112,'TEMPLATE','/home/gdwy/WY909/data/COMTRADE/TEMPLATE');
/*!40000 ALTER TABLE `TEMPLATE` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TEMPLATE_File`
--

DROP TABLE IF EXISTS `TEMPLATE_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TEMPLATE_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TEMPLATE_File`
--

LOCK TABLES `TEMPLATE_File` WRITE;
/*!40000 ALTER TABLE `TEMPLATE_File` DISABLE KEYS */;
INSERT INTO `TEMPLATE_File` VALUES ('/COMTRADE/TEMPLATE_RCD_157_20210914_115054_930_S.cfg',1631591414,803,'TEMPLATE_RCD_157_20210914_115054_930_S'),('/COMTRADE/TEMPLATE_RCD_157_20210914_115054_930_S.dat',1631591416,9600,'TEMPLATE_RCD_157_20210914_115054_930_S'),('/COMTRADE/TEMPLATE_RCD_157_20210914_115054_930_S.des',1631591416,78,'TEMPLATE_RCD_157_20210914_115054_930_S'),('/COMTRADE/TEMPLATE_RCD_157_20210914_115054_930_S.hdr',1631591414,42,'TEMPLATE_RCD_157_20210914_115054_930_S'),('/COMTRADE/TEMPLATE_RCD_157_20210914_115054_930_S.mid',1631591416,0,'TEMPLATE_RCD_157_20210914_115054_930_S'),('/COMTRADE/TEMPLATE_RCD_158_20210914_115058_030_S.cfg',1631591418,803,'TEMPLATE_RCD_158_20210914_115058_030_S'),('/COMTRADE/TEMPLATE_RCD_158_20210914_115058_030_S.dat',1631591418,9600,'TEMPLATE_RCD_158_20210914_115058_030_S'),('/COMTRADE/TEMPLATE_RCD_158_20210914_115058_030_S.des',1631591418,78,'TEMPLATE_RCD_158_20210914_115058_030_S'),('/COMTRADE/TEMPLATE_RCD_158_20210914_115058_030_S.hdr',1631591418,42,'TEMPLATE_RCD_158_20210914_115058_030_S'),('/COMTRADE/TEMPLATE_RCD_158_20210914_115058_030_S.mid',1631591418,0,'TEMPLATE_RCD_158_20210914_115058_030_S'),('/COMTRADE/TEMPLATE_RCD_162_20211028_174341_211_S.cfg',1635414162,803,'TEMPLATE_RCD_162_20211028_174341_211_S'),('/COMTRADE/TEMPLATE_RCD_162_20211028_174341_211_S.dat',1635414162,9600,'TEMPLATE_RCD_162_20211028_174341_211_S'),('/COMTRADE/TEMPLATE_RCD_162_20211028_174341_211_S.des',1635414162,78,'TEMPLATE_RCD_162_20211028_174341_211_S'),('/COMTRADE/TEMPLATE_RCD_162_20211028_174341_211_S.hdr',1635414162,42,'TEMPLATE_RCD_162_20211028_174341_211_S'),('/COMTRADE/TEMPLATE_RCD_162_20211028_174341_211_S.mid',1635414162,0,'TEMPLATE_RCD_162_20211028_174341_211_S'),('/COMTRADE/TEMPLATE_RCD_186_20211228_215212_009_S.cfg',1640699534,803,'TEMPLATE_RCD_186_20211228_215212_009_S'),('/COMTRADE/TEMPLATE_RCD_186_20211228_215212_009_S.dat',1640699534,9600,'TEMPLATE_RCD_186_20211228_215212_009_S'),('/COMTRADE/TEMPLATE_RCD_186_20211228_215212_009_S.des',1640699534,78,'TEMPLATE_RCD_186_20211228_215212_009_S'),('/COMTRADE/TEMPLATE_RCD_186_20211228_215212_009_S.hdr',1640699534,42,'TEMPLATE_RCD_186_20211228_215212_009_S'),('/COMTRADE/TEMPLATE_RCD_186_20211228_215212_009_S.mid',1640699534,0,'TEMPLATE_RCD_186_20211228_215212_009_S'),('/COMTRADE/TEMPLATE_RCD_221_20211230_203732_400_F.cfg',1640867858,803,'TEMPLATE_RCD_221_20211230_203732_400_F'),('/COMTRADE/TEMPLATE_RCD_221_20211230_203732_400_F.dat',1640867860,19200,'TEMPLATE_RCD_221_20211230_203732_400_F'),('/COMTRADE/TEMPLATE_RCD_221_20211230_203732_400_F.des',1640867860,78,'TEMPLATE_RCD_221_20211230_203732_400_F'),('/COMTRADE/TEMPLATE_RCD_221_20211230_203732_400_F.hdr',1640867858,12627,'TEMPLATE_RCD_221_20211230_203732_400_F'),('/COMTRADE/TEMPLATE_RCD_221_20211230_203732_400_F.mid',1640867860,0,'TEMPLATE_RCD_221_20211230_203732_400_F'),('/COMTRADE/TEMPLATE_RCD_222_20211231_083710_059_F.cfg',1640911036,803,'TEMPLATE_RCD_222_20211231_083710_059_F'),('/COMTRADE/TEMPLATE_RCD_222_20211231_083710_059_F.dat',1640911036,19200,'TEMPLATE_RCD_222_20211231_083710_059_F'),('/COMTRADE/TEMPLATE_RCD_222_20211231_083710_059_F.des',1640911036,78,'TEMPLATE_RCD_222_20211231_083710_059_F'),('/COMTRADE/TEMPLATE_RCD_222_20211231_083710_059_F.hdr',1640911036,12627,'TEMPLATE_RCD_222_20211231_083710_059_F'),('/COMTRADE/TEMPLATE_RCD_222_20211231_083710_059_F.mid',1640911036,0,'TEMPLATE_RCD_222_20211231_083710_059_F'),('/COMTRADE/TEMPLATE_RCD_223_20211231_091231_453_F.cfg',1640913156,803,'TEMPLATE_RCD_223_20211231_091231_453_F'),('/COMTRADE/TEMPLATE_RCD_223_20211231_091231_453_F.dat',1640913158,19200,'TEMPLATE_RCD_223_20211231_091231_453_F'),('/COMTRADE/TEMPLATE_RCD_223_20211231_091231_453_F.des',1640913158,78,'TEMPLATE_RCD_223_20211231_091231_453_F'),('/COMTRADE/TEMPLATE_RCD_223_20211231_091231_453_F.hdr',1640913156,12627,'TEMPLATE_RCD_223_20211231_091231_453_F'),('/COMTRADE/TEMPLATE_RCD_223_20211231_091231_453_F.mid',1640913158,0,'TEMPLATE_RCD_223_20211231_091231_453_F'),('/COMTRADE/TEMPLATE_RCD_230_20211231_161647_983_F.cfg',1640938626,803,'TEMPLATE_RCD_230_20211231_161647_983_F'),('/COMTRADE/TEMPLATE_RCD_230_20211231_161647_983_F.dat',1640938626,19200,'TEMPLATE_RCD_230_20211231_161647_983_F'),('/COMTRADE/TEMPLATE_RCD_230_20211231_161647_983_F.des',1640938626,78,'TEMPLATE_RCD_230_20211231_161647_983_F'),('/COMTRADE/TEMPLATE_RCD_230_20211231_161647_983_F.hdr',1640938626,12629,'TEMPLATE_RCD_230_20211231_161647_983_F'),('/COMTRADE/TEMPLATE_RCD_230_20211231_161647_983_F.mid',1640938626,0,'TEMPLATE_RCD_230_20211231_161647_983_F'),('/COMTRADE/TEMPLATE_RCD_232_20211231_174720_292_S.cfg',1640944044,803,'TEMPLATE_RCD_232_20211231_174720_292_S'),('/COMTRADE/TEMPLATE_RCD_232_20211231_174720_292_S.dat',1640944044,9600,'TEMPLATE_RCD_232_20211231_174720_292_S'),('/COMTRADE/TEMPLATE_RCD_232_20211231_174720_292_S.des',1640944044,78,'TEMPLATE_RCD_232_20211231_174720_292_S'),('/COMTRADE/TEMPLATE_RCD_232_20211231_174720_292_S.hdr',1640944044,42,'TEMPLATE_RCD_232_20211231_174720_292_S'),('/COMTRADE/TEMPLATE_RCD_232_20211231_174720_292_S.mid',1640944044,0,'TEMPLATE_RCD_232_20211231_174720_292_S'),('/COMTRADE/TEMPLATE_RCD_236_20220104_141855_960_F.cfg',1641277146,803,'TEMPLATE_RCD_236_20220104_141855_960_F'),('/COMTRADE/TEMPLATE_RCD_236_20220104_141855_960_F.dat',1641277146,19200,'TEMPLATE_RCD_236_20220104_141855_960_F'),('/COMTRADE/TEMPLATE_RCD_236_20220104_141855_960_F.des',1641277146,78,'TEMPLATE_RCD_236_20220104_141855_960_F'),('/COMTRADE/TEMPLATE_RCD_236_20220104_141855_960_F.hdr',1641277146,12722,'TEMPLATE_RCD_236_20220104_141855_960_F'),('/COMTRADE/TEMPLATE_RCD_236_20220104_141855_960_F.mid',1641277146,0,'TEMPLATE_RCD_236_20220104_141855_960_F'),('/COMTRADE/TEMPLATE_RCD_237_20220104_142059_443_F.cfg',1641277264,803,'TEMPLATE_RCD_237_20220104_142059_443_F'),('/COMTRADE/TEMPLATE_RCD_237_20220104_142059_443_F.dat',1641277266,19200,'TEMPLATE_RCD_237_20220104_142059_443_F'),('/COMTRADE/TEMPLATE_RCD_237_20220104_142059_443_F.des',1641277266,78,'TEMPLATE_RCD_237_20220104_142059_443_F'),('/COMTRADE/TEMPLATE_RCD_237_20220104_142059_443_F.hdr',1641277264,12627,'TEMPLATE_RCD_237_20220104_142059_443_F'),('/COMTRADE/TEMPLATE_RCD_237_20220104_142059_443_F.mid',1641277266,0,'TEMPLATE_RCD_237_20220104_142059_443_F'),('/COMTRADE/TEMPLATE_RCD_238_20220104_142131_084_F.cfg',1641277298,803,'TEMPLATE_RCD_238_20220104_142131_084_F'),('/COMTRADE/TEMPLATE_RCD_238_20220104_142131_084_F.dat',1641277298,19200,'TEMPLATE_RCD_238_20220104_142131_084_F'),('/COMTRADE/TEMPLATE_RCD_238_20220104_142131_084_F.des',1641277298,78,'TEMPLATE_RCD_238_20220104_142131_084_F'),('/COMTRADE/TEMPLATE_RCD_238_20220104_142131_084_F.hdr',1641277298,12627,'TEMPLATE_RCD_238_20220104_142131_084_F'),('/COMTRADE/TEMPLATE_RCD_238_20220104_142131_084_F.mid',1641277298,0,'TEMPLATE_RCD_238_20220104_142131_084_F'),('/COMTRADE/TEMPLATE_RCD_239_20220104_142402_234_F.cfg',1641277448,803,'TEMPLATE_RCD_239_20220104_142402_234_F'),('/COMTRADE/TEMPLATE_RCD_239_20220104_142402_234_F.dat',1641277448,19200,'TEMPLATE_RCD_239_20220104_142402_234_F'),('/COMTRADE/TEMPLATE_RCD_239_20220104_142402_234_F.des',1641277448,78,'TEMPLATE_RCD_239_20220104_142402_234_F'),('/COMTRADE/TEMPLATE_RCD_239_20220104_142402_234_F.hdr',1641277448,12627,'TEMPLATE_RCD_239_20220104_142402_234_F'),('/COMTRADE/TEMPLATE_RCD_239_20220104_142402_234_F.mid',1641277448,0,'TEMPLATE_RCD_239_20220104_142402_234_F'),('/COMTRADE/TEMPLATE_RCD_240_20220104_143641_669_F.cfg',1641278208,803,'TEMPLATE_RCD_240_20220104_143641_669_F'),('/COMTRADE/TEMPLATE_RCD_240_20220104_143641_669_F.dat',1641278208,19200,'TEMPLATE_RCD_240_20220104_143641_669_F'),('/COMTRADE/TEMPLATE_RCD_240_20220104_143641_669_F.des',1641278208,78,'TEMPLATE_RCD_240_20220104_143641_669_F'),('/COMTRADE/TEMPLATE_RCD_240_20220104_143641_669_F.hdr',1641278206,12627,'TEMPLATE_RCD_240_20220104_143641_669_F'),('/COMTRADE/TEMPLATE_RCD_240_20220104_143641_669_F.mid',1641278208,0,'TEMPLATE_RCD_240_20220104_143641_669_F'),('/COMTRADE/TEMPLATE_RCD_241_20220104_151246_176_F.cfg',1641280372,803,'TEMPLATE_RCD_241_20220104_151246_176_F'),('/COMTRADE/TEMPLATE_RCD_241_20220104_151246_176_F.dat',1641280372,19200,'TEMPLATE_RCD_241_20220104_151246_176_F'),('/COMTRADE/TEMPLATE_RCD_241_20220104_151246_176_F.des',1641280372,78,'TEMPLATE_RCD_241_20220104_151246_176_F'),('/COMTRADE/TEMPLATE_RCD_241_20220104_151246_176_F.hdr',1641280372,12627,'TEMPLATE_RCD_241_20220104_151246_176_F'),('/COMTRADE/TEMPLATE_RCD_241_20220104_151246_176_F.mid',1641280372,0,'TEMPLATE_RCD_241_20220104_151246_176_F'),('/COMTRADE/TEMPLATE_RCD_242_20220104_152505_967_F.cfg',1641281112,803,'TEMPLATE_RCD_242_20220104_152505_967_F'),('/COMTRADE/TEMPLATE_RCD_242_20220104_152505_967_F.dat',1641281112,19200,'TEMPLATE_RCD_242_20220104_152505_967_F'),('/COMTRADE/TEMPLATE_RCD_242_20220104_152505_967_F.des',1641281112,78,'TEMPLATE_RCD_242_20220104_152505_967_F'),('/COMTRADE/TEMPLATE_RCD_242_20220104_152505_967_F.hdr',1641281112,12627,'TEMPLATE_RCD_242_20220104_152505_967_F'),('/COMTRADE/TEMPLATE_RCD_242_20220104_152505_967_F.mid',1641281112,0,'TEMPLATE_RCD_242_20220104_152505_967_F');
/*!40000 ALTER TABLE `TEMPLATE_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `WY9D`
--

DROP TABLE IF EXISTS `WY9D`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `WY9D` (
  `name` varchar(65) NOT NULL,
  `time` bigint(20) NOT NULL,
  `iedName` varchar(65) NOT NULL,
  `savePath` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `WY9D`
--

LOCK TABLES `WY9D` WRITE;
/*!40000 ALTER TABLE `WY9D` DISABLE KEYS */;
INSERT INTO `WY9D` VALUES ('WY9D_RCD_84840_20211230_200554_182_F',1640865954,'WY9D','/home/gdwy/WY909/data/COMTRADE/WY9D'),('WY9D_RCD_84841_20211230_203732_291_F',1640867852,'WY9D','/home/gdwy/WY909/data/COMTRADE/WY9D'),('WY9D_RCD_84847_20211231_091231_442_F',1640913151,'WY9D','/home/gdwy/WY909/data/COMTRADE/WY9D'),('WY9D_RCD_84858_20211231_163841_481_F',1640939921,'WY9D','/home/gdwy/WY909/data/COMTRADE/WY9D'),('WY9D_RCD_84859_20211231_163929_721_F',1640939969,'WY9D','/home/gdwy/WY909/data/COMTRADE/WY9D'),('WY9D_RCD_84865_20220104_142059_334_F',1641277259,'WY9D','/home/gdwy/WY909/data/COMTRADE/WY9D'),('WY9D_RCD_84866_20220104_142130_976_F',1641277290,'WY9D','/home/gdwy/WY909/data/COMTRADE/WY9D'),('WY9D_RCD_84867_20220104_142402_124_F',1641277442,'WY9D','/home/gdwy/WY909/data/COMTRADE/WY9D');
/*!40000 ALTER TABLE `WY9D` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `WY9D_File`
--

DROP TABLE IF EXISTS `WY9D_File`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `WY9D_File` (
  `filePath` varchar(255) NOT NULL,
  `time` bigint(20) NOT NULL,
  `size` int(11) NOT NULL,
  `name` varchar(65) NOT NULL,
  PRIMARY KEY (`filePath`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `WY9D_File`
--

LOCK TABLES `WY9D_File` WRITE;
/*!40000 ALTER TABLE `WY9D_File` DISABLE KEYS */;
INSERT INTO `WY9D_File` VALUES ('/COMTRADE/WY9D_RCD_84809_20211230_142159_724_F.cfg',1640845319,3800,'WY9D_RCD_84809_20211230_142159_724_F'),('/COMTRADE/WY9D_RCD_84809_20211230_142159_724_F.dat',1640845319,3706032,'WY9D_RCD_84809_20211230_142159_724_F'),('/COMTRADE/WY9D_RCD_84809_20211230_142159_724_F.dmf',1640845319,12752,'WY9D_RCD_84809_20211230_142159_724_F'),('/COMTRADE/WY9D_RCD_84809_20211230_142159_724_F.hdr',1640845319,10146,'WY9D_RCD_84809_20211230_142159_724_F'),('/COMTRADE/WY9D_RCD_84810_20211230_142207_426_F.cfg',1640845327,3800,'WY9D_RCD_84810_20211230_142207_426_F'),('/COMTRADE/WY9D_RCD_84810_20211230_142207_426_F.dat',1640845327,3706080,'WY9D_RCD_84810_20211230_142207_426_F'),('/COMTRADE/WY9D_RCD_84810_20211230_142207_426_F.dmf',1640845327,12752,'WY9D_RCD_84810_20211230_142207_426_F'),('/COMTRADE/WY9D_RCD_84810_20211230_142207_426_F.hdr',1640845327,10146,'WY9D_RCD_84810_20211230_142207_426_F'),('/COMTRADE/WY9D_RCD_84811_20211230_142215_143_F.cfg',1640845335,3800,'WY9D_RCD_84811_20211230_142215_143_F'),('/COMTRADE/WY9D_RCD_84811_20211230_142215_143_F.dat',1640845335,3691392,'WY9D_RCD_84811_20211230_142215_143_F'),('/COMTRADE/WY9D_RCD_84811_20211230_142215_143_F.dmf',1640845335,12752,'WY9D_RCD_84811_20211230_142215_143_F'),('/COMTRADE/WY9D_RCD_84811_20211230_142215_143_F.hdr',1640845335,10146,'WY9D_RCD_84811_20211230_142215_143_F'),('/COMTRADE/WY9D_RCD_84812_20211230_142222_829_F.cfg',1640845342,3800,'WY9D_RCD_84812_20211230_142222_829_F'),('/COMTRADE/WY9D_RCD_84812_20211230_142222_829_F.dat',1640845342,3698448,'WY9D_RCD_84812_20211230_142222_829_F'),('/COMTRADE/WY9D_RCD_84812_20211230_142222_829_F.dmf',1640845342,12752,'WY9D_RCD_84812_20211230_142222_829_F'),('/COMTRADE/WY9D_RCD_84812_20211230_142222_829_F.hdr',1640845342,10146,'WY9D_RCD_84812_20211230_142222_829_F'),('/COMTRADE/WY9D_RCD_84813_20211230_142230_530_F.cfg',1640845350,3800,'WY9D_RCD_84813_20211230_142230_530_F'),('/COMTRADE/WY9D_RCD_84813_20211230_142230_530_F.dat',1640845350,3705984,'WY9D_RCD_84813_20211230_142230_530_F'),('/COMTRADE/WY9D_RCD_84813_20211230_142230_530_F.dmf',1640845350,12752,'WY9D_RCD_84813_20211230_142230_530_F'),('/COMTRADE/WY9D_RCD_84813_20211230_142230_530_F.hdr',1640845350,10146,'WY9D_RCD_84813_20211230_142230_530_F'),('/COMTRADE/WY9D_RCD_84814_20211230_142238_247_F.cfg',1640845358,3800,'WY9D_RCD_84814_20211230_142238_247_F'),('/COMTRADE/WY9D_RCD_84814_20211230_142238_247_F.dat',1640845358,3698544,'WY9D_RCD_84814_20211230_142238_247_F'),('/COMTRADE/WY9D_RCD_84814_20211230_142238_247_F.dmf',1640845358,12752,'WY9D_RCD_84814_20211230_142238_247_F'),('/COMTRADE/WY9D_RCD_84814_20211230_142238_247_F.hdr',1640845358,10146,'WY9D_RCD_84814_20211230_142238_247_F'),('/COMTRADE/WY9D_RCD_84815_20211230_142245_949_F.cfg',1640845365,3800,'WY9D_RCD_84815_20211230_142245_949_F'),('/COMTRADE/WY9D_RCD_84815_20211230_142245_949_F.dat',1640845365,3706128,'WY9D_RCD_84815_20211230_142245_949_F'),('/COMTRADE/WY9D_RCD_84815_20211230_142245_949_F.dmf',1640845365,12752,'WY9D_RCD_84815_20211230_142245_949_F'),('/COMTRADE/WY9D_RCD_84815_20211230_142245_949_F.hdr',1640845365,10146,'WY9D_RCD_84815_20211230_142245_949_F'),('/COMTRADE/WY9D_RCD_84816_20211230_142253_651_F.cfg',1640845373,3800,'WY9D_RCD_84816_20211230_142253_651_F'),('/COMTRADE/WY9D_RCD_84816_20211230_142253_651_F.dat',1640845373,3691152,'WY9D_RCD_84816_20211230_142253_651_F'),('/COMTRADE/WY9D_RCD_84816_20211230_142253_651_F.dmf',1640845373,12752,'WY9D_RCD_84816_20211230_142253_651_F'),('/COMTRADE/WY9D_RCD_84816_20211230_142253_651_F.hdr',1640845373,10146,'WY9D_RCD_84816_20211230_142253_651_F'),('/COMTRADE/WY9D_RCD_84817_20211230_142301_337_F.cfg',1640845381,3800,'WY9D_RCD_84817_20211230_142301_337_F'),('/COMTRADE/WY9D_RCD_84817_20211230_142301_337_F.dat',1640845381,3706080,'WY9D_RCD_84817_20211230_142301_337_F'),('/COMTRADE/WY9D_RCD_84817_20211230_142301_337_F.dmf',1640845381,12752,'WY9D_RCD_84817_20211230_142301_337_F'),('/COMTRADE/WY9D_RCD_84817_20211230_142301_337_F.hdr',1640845381,10146,'WY9D_RCD_84817_20211230_142301_337_F'),('/COMTRADE/WY9D_RCD_84818_20211230_142309_039_F.cfg',1640845389,3800,'WY9D_RCD_84818_20211230_142309_039_F'),('/COMTRADE/WY9D_RCD_84818_20211230_142309_039_F.dat',1640845389,3706032,'WY9D_RCD_84818_20211230_142309_039_F'),('/COMTRADE/WY9D_RCD_84818_20211230_142309_039_F.dmf',1640845389,12752,'WY9D_RCD_84818_20211230_142309_039_F'),('/COMTRADE/WY9D_RCD_84818_20211230_142309_039_F.hdr',1640845389,10146,'WY9D_RCD_84818_20211230_142309_039_F'),('/COMTRADE/WY9D_RCD_84819_20211230_142316_756_F.cfg',1640845396,3800,'WY9D_RCD_84819_20211230_142316_756_F'),('/COMTRADE/WY9D_RCD_84819_20211230_142316_756_F.dat',1640845396,3705984,'WY9D_RCD_84819_20211230_142316_756_F'),('/COMTRADE/WY9D_RCD_84819_20211230_142316_756_F.dmf',1640845396,12752,'WY9D_RCD_84819_20211230_142316_756_F'),('/COMTRADE/WY9D_RCD_84819_20211230_142316_756_F.hdr',1640845396,10146,'WY9D_RCD_84819_20211230_142316_756_F'),('/COMTRADE/WY9D_RCD_84820_20211230_142324_488_F.cfg',1640845404,3800,'WY9D_RCD_84820_20211230_142324_488_F'),('/COMTRADE/WY9D_RCD_84820_20211230_142324_488_F.dat',1640845404,3706080,'WY9D_RCD_84820_20211230_142324_488_F'),('/COMTRADE/WY9D_RCD_84820_20211230_142324_488_F.dmf',1640845404,12752,'WY9D_RCD_84820_20211230_142324_488_F'),('/COMTRADE/WY9D_RCD_84820_20211230_142324_488_F.hdr',1640845404,10146,'WY9D_RCD_84820_20211230_142324_488_F'),('/COMTRADE/WY9D_RCD_84821_20211230_142332_205_F.cfg',1640845412,3800,'WY9D_RCD_84821_20211230_142332_205_F'),('/COMTRADE/WY9D_RCD_84821_20211230_142332_205_F.dat',1640845412,3698640,'WY9D_RCD_84821_20211230_142332_205_F'),('/COMTRADE/WY9D_RCD_84821_20211230_142332_205_F.dmf',1640845412,12752,'WY9D_RCD_84821_20211230_142332_205_F'),('/COMTRADE/WY9D_RCD_84821_20211230_142332_205_F.hdr',1640845412,10146,'WY9D_RCD_84821_20211230_142332_205_F'),('/COMTRADE/WY9D_RCD_84822_20211230_142339_891_F.cfg',1640845419,3800,'WY9D_RCD_84822_20211230_142339_891_F'),('/COMTRADE/WY9D_RCD_84822_20211230_142339_891_F.dat',1640845419,3698496,'WY9D_RCD_84822_20211230_142339_891_F'),('/COMTRADE/WY9D_RCD_84822_20211230_142339_891_F.dmf',1640845419,12752,'WY9D_RCD_84822_20211230_142339_891_F'),('/COMTRADE/WY9D_RCD_84822_20211230_142339_891_F.hdr',1640845419,10146,'WY9D_RCD_84822_20211230_142339_891_F'),('/COMTRADE/WY9D_RCD_84823_20211230_142347_608_F.cfg',1640845427,3800,'WY9D_RCD_84823_20211230_142347_608_F'),('/COMTRADE/WY9D_RCD_84823_20211230_142347_608_F.dat',1640845427,3705936,'WY9D_RCD_84823_20211230_142347_608_F'),('/COMTRADE/WY9D_RCD_84823_20211230_142347_608_F.dmf',1640845427,12752,'WY9D_RCD_84823_20211230_142347_608_F'),('/COMTRADE/WY9D_RCD_84823_20211230_142347_608_F.hdr',1640845427,10146,'WY9D_RCD_84823_20211230_142347_608_F'),('/COMTRADE/WY9D_RCD_84824_20211230_142355_325_F.cfg',1640845435,3800,'WY9D_RCD_84824_20211230_142355_325_F'),('/COMTRADE/WY9D_RCD_84824_20211230_142355_325_F.dat',1640845435,3698592,'WY9D_RCD_84824_20211230_142355_325_F'),('/COMTRADE/WY9D_RCD_84824_20211230_142355_325_F.dmf',1640845435,12752,'WY9D_RCD_84824_20211230_142355_325_F'),('/COMTRADE/WY9D_RCD_84824_20211230_142355_325_F.hdr',1640845435,10146,'WY9D_RCD_84824_20211230_142355_325_F'),('/COMTRADE/WY9D_RCD_84825_20211230_142403_026_F.cfg',1640845443,3800,'WY9D_RCD_84825_20211230_142403_026_F'),('/COMTRADE/WY9D_RCD_84825_20211230_142403_026_F.dat',1640845443,3705936,'WY9D_RCD_84825_20211230_142403_026_F'),('/COMTRADE/WY9D_RCD_84825_20211230_142403_026_F.dmf',1640845443,12752,'WY9D_RCD_84825_20211230_142403_026_F'),('/COMTRADE/WY9D_RCD_84825_20211230_142403_026_F.hdr',1640845443,10146,'WY9D_RCD_84825_20211230_142403_026_F'),('/COMTRADE/WY9D_RCD_84826_20211230_142410_743_F.cfg',1640845450,3800,'WY9D_RCD_84826_20211230_142410_743_F'),('/COMTRADE/WY9D_RCD_84826_20211230_142410_743_F.dat',1640845450,3706224,'WY9D_RCD_84826_20211230_142410_743_F'),('/COMTRADE/WY9D_RCD_84826_20211230_142410_743_F.dmf',1640845450,12752,'WY9D_RCD_84826_20211230_142410_743_F'),('/COMTRADE/WY9D_RCD_84826_20211230_142410_743_F.hdr',1640845450,10146,'WY9D_RCD_84826_20211230_142410_743_F'),('/COMTRADE/WY9D_RCD_84827_20211230_142418_445_F.cfg',1640845458,3800,'WY9D_RCD_84827_20211230_142418_445_F'),('/COMTRADE/WY9D_RCD_84827_20211230_142418_445_F.dat',1640845458,3713472,'WY9D_RCD_84827_20211230_142418_445_F'),('/COMTRADE/WY9D_RCD_84827_20211230_142418_445_F.dmf',1640845458,12752,'WY9D_RCD_84827_20211230_142418_445_F'),('/COMTRADE/WY9D_RCD_84827_20211230_142418_445_F.hdr',1640845458,10146,'WY9D_RCD_84827_20211230_142418_445_F'),('/COMTRADE/WY9D_RCD_84828_20211230_142426_162_F.cfg',1640845466,3801,'WY9D_RCD_84828_20211230_142426_162_F'),('/COMTRADE/WY9D_RCD_84828_20211230_142426_162_F.dat',1640845466,5820576,'WY9D_RCD_84828_20211230_142426_162_F'),('/COMTRADE/WY9D_RCD_84828_20211230_142426_162_F.dmf',1640845466,12752,'WY9D_RCD_84828_20211230_142426_162_F'),('/COMTRADE/WY9D_RCD_84828_20211230_142426_162_F.hdr',1640845466,8462,'WY9D_RCD_84828_20211230_142426_162_F'),('/COMTRADE/WY9D_RCD_84829_20211230_142503_901_F.cfg',1640845503,3800,'WY9D_RCD_84829_20211230_142503_901_F'),('/COMTRADE/WY9D_RCD_84829_20211230_142503_901_F.dat',1640845503,2063808,'WY9D_RCD_84829_20211230_142503_901_F'),('/COMTRADE/WY9D_RCD_84829_20211230_142503_901_F.dmf',1640845503,12752,'WY9D_RCD_84829_20211230_142503_901_F'),('/COMTRADE/WY9D_RCD_84829_20211230_142503_901_F.hdr',1640845503,8458,'WY9D_RCD_84829_20211230_142503_901_F'),('/COMTRADE/WY9D_RCD_84830_20211230_142623_018_F.cfg',1640845583,3800,'WY9D_RCD_84830_20211230_142623_018_F'),('/COMTRADE/WY9D_RCD_84830_20211230_142623_018_F.dat',1640845583,2063808,'WY9D_RCD_84830_20211230_142623_018_F'),('/COMTRADE/WY9D_RCD_84830_20211230_142623_018_F.dmf',1640845583,12752,'WY9D_RCD_84830_20211230_142623_018_F'),('/COMTRADE/WY9D_RCD_84830_20211230_142623_018_F.hdr',1640845583,8458,'WY9D_RCD_84830_20211230_142623_018_F'),('/COMTRADE/WY9D_RCD_84831_20211230_142901_136_F.cfg',1640845741,3800,'WY9D_RCD_84831_20211230_142901_136_F'),('/COMTRADE/WY9D_RCD_84831_20211230_142901_136_F.dat',1640845741,2063808,'WY9D_RCD_84831_20211230_142901_136_F'),('/COMTRADE/WY9D_RCD_84831_20211230_142901_136_F.dmf',1640845741,12752,'WY9D_RCD_84831_20211230_142901_136_F'),('/COMTRADE/WY9D_RCD_84831_20211230_142901_136_F.hdr',1640845741,8458,'WY9D_RCD_84831_20211230_142901_136_F'),('/COMTRADE/WY9D_RCD_84832_20211230_143038_709_F.cfg',1640845838,3800,'WY9D_RCD_84832_20211230_143038_709_F'),('/COMTRADE/WY9D_RCD_84832_20211230_143038_709_F.dat',1640845838,2063808,'WY9D_RCD_84832_20211230_143038_709_F'),('/COMTRADE/WY9D_RCD_84832_20211230_143038_709_F.dmf',1640845838,12752,'WY9D_RCD_84832_20211230_143038_709_F'),('/COMTRADE/WY9D_RCD_84832_20211230_143038_709_F.hdr',1640845838,8458,'WY9D_RCD_84832_20211230_143038_709_F'),('/COMTRADE/WY9D_RCD_84833_20211230_143355_131_F.cfg',1640846035,3800,'WY9D_RCD_84833_20211230_143355_131_F'),('/COMTRADE/WY9D_RCD_84833_20211230_143355_131_F.dat',1640846035,2063808,'WY9D_RCD_84833_20211230_143355_131_F'),('/COMTRADE/WY9D_RCD_84833_20211230_143355_131_F.dmf',1640846035,12752,'WY9D_RCD_84833_20211230_143355_131_F'),('/COMTRADE/WY9D_RCD_84833_20211230_143355_131_F.hdr',1640846035,8458,'WY9D_RCD_84833_20211230_143355_131_F'),('/COMTRADE/WY9D_RCD_84834_20211230_153004_522_F.cfg',1640849404,3800,'WY9D_RCD_84834_20211230_153004_522_F'),('/COMTRADE/WY9D_RCD_84834_20211230_153004_522_F.dat',1640849404,2063808,'WY9D_RCD_84834_20211230_153004_522_F'),('/COMTRADE/WY9D_RCD_84834_20211230_153004_522_F.dmf',1640849404,12752,'WY9D_RCD_84834_20211230_153004_522_F'),('/COMTRADE/WY9D_RCD_84834_20211230_153004_522_F.hdr',1640849404,8458,'WY9D_RCD_84834_20211230_153004_522_F'),('/COMTRADE/WY9D_RCD_84835_20211230_155759_264_F.cfg',1640851079,3800,'WY9D_RCD_84835_20211230_155759_264_F'),('/COMTRADE/WY9D_RCD_84835_20211230_155759_264_F.dat',1640851079,2063808,'WY9D_RCD_84835_20211230_155759_264_F'),('/COMTRADE/WY9D_RCD_84835_20211230_155759_264_F.dmf',1640851079,12752,'WY9D_RCD_84835_20211230_155759_264_F'),('/COMTRADE/WY9D_RCD_84835_20211230_155759_264_F.hdr',1640851079,8458,'WY9D_RCD_84835_20211230_155759_264_F'),('/COMTRADE/WY9D_RCD_84836_20211230_161240_205_F.cfg',1640851960,3800,'WY9D_RCD_84836_20211230_161240_205_F'),('/COMTRADE/WY9D_RCD_84836_20211230_161240_205_F.dat',1640851960,2063808,'WY9D_RCD_84836_20211230_161240_205_F'),('/COMTRADE/WY9D_RCD_84836_20211230_161240_205_F.dmf',1640851960,12752,'WY9D_RCD_84836_20211230_161240_205_F'),('/COMTRADE/WY9D_RCD_84836_20211230_161240_205_F.hdr',1640851960,8458,'WY9D_RCD_84836_20211230_161240_205_F'),('/COMTRADE/WY9D_RCD_84837_20211230_171934_454_F.cfg',1640855974,3800,'WY9D_RCD_84837_20211230_171934_454_F'),('/COMTRADE/WY9D_RCD_84837_20211230_171934_454_F.dat',1640855974,2063808,'WY9D_RCD_84837_20211230_171934_454_F'),('/COMTRADE/WY9D_RCD_84837_20211230_171934_454_F.dmf',1640855974,12752,'WY9D_RCD_84837_20211230_171934_454_F'),('/COMTRADE/WY9D_RCD_84837_20211230_171934_454_F.hdr',1640855974,8458,'WY9D_RCD_84837_20211230_171934_454_F'),('/COMTRADE/WY9D_RCD_84840_20211230_200554_182_F.cfg',1640865954,3800,'WY9D_RCD_84840_20211230_200554_182_F'),('/COMTRADE/WY9D_RCD_84840_20211230_200554_182_F.dat',1640865954,2063808,'WY9D_RCD_84840_20211230_200554_182_F'),('/COMTRADE/WY9D_RCD_84840_20211230_200554_182_F.dmf',1640865954,12752,'WY9D_RCD_84840_20211230_200554_182_F'),('/COMTRADE/WY9D_RCD_84840_20211230_200554_182_F.hdr',1640865954,8458,'WY9D_RCD_84840_20211230_200554_182_F'),('/COMTRADE/WY9D_RCD_84841_20211230_203732_291_F.cfg',1640867852,3800,'WY9D_RCD_84841_20211230_203732_291_F'),('/COMTRADE/WY9D_RCD_84841_20211230_203732_291_F.dat',1640867852,2111808,'WY9D_RCD_84841_20211230_203732_291_F'),('/COMTRADE/WY9D_RCD_84841_20211230_203732_291_F.dmf',1640867852,12752,'WY9D_RCD_84841_20211230_203732_291_F'),('/COMTRADE/WY9D_RCD_84841_20211230_203732_291_F.hdr',1640867852,8460,'WY9D_RCD_84841_20211230_203732_291_F'),('/COMTRADE/WY9D_RCD_84847_20211231_091231_442_F.cfg',1640913151,3800,'WY9D_RCD_84847_20211231_091231_442_F'),('/COMTRADE/WY9D_RCD_84847_20211231_091231_442_F.dat',1640913151,2143104,'WY9D_RCD_84847_20211231_091231_442_F'),('/COMTRADE/WY9D_RCD_84847_20211231_091231_442_F.dmf',1640913151,12752,'WY9D_RCD_84847_20211231_091231_442_F'),('/COMTRADE/WY9D_RCD_84847_20211231_091231_442_F.hdr',1640913151,8458,'WY9D_RCD_84847_20211231_091231_442_F'),('/COMTRADE/WY9D_RCD_84858_20211231_163841_481_F.cfg',1640939921,3800,'WY9D_RCD_84858_20211231_163841_481_F'),('/COMTRADE/WY9D_RCD_84858_20211231_163841_481_F.dat',1640939921,1584000,'WY9D_RCD_84858_20211231_163841_481_F'),('/COMTRADE/WY9D_RCD_84858_20211231_163841_481_F.dmf',1640939921,12752,'WY9D_RCD_84858_20211231_163841_481_F'),('/COMTRADE/WY9D_RCD_84858_20211231_163841_481_F.hdr',1640939921,9629,'WY9D_RCD_84858_20211231_163841_481_F'),('/COMTRADE/WY9D_RCD_84859_20211231_163929_721_F.cfg',1640939969,3800,'WY9D_RCD_84859_20211231_163929_721_F'),('/COMTRADE/WY9D_RCD_84859_20211231_163929_721_F.dat',1640939969,1584000,'WY9D_RCD_84859_20211231_163929_721_F'),('/COMTRADE/WY9D_RCD_84859_20211231_163929_721_F.dmf',1640939969,12752,'WY9D_RCD_84859_20211231_163929_721_F'),('/COMTRADE/WY9D_RCD_84859_20211231_163929_721_F.hdr',1640939969,9629,'WY9D_RCD_84859_20211231_163929_721_F'),('/COMTRADE/WY9D_RCD_84865_20220104_142059_334_F.cfg',1641277259,3800,'WY9D_RCD_84865_20220104_142059_334_F'),('/COMTRADE/WY9D_RCD_84865_20220104_142059_334_F.dat',1641277259,2111808,'WY9D_RCD_84865_20220104_142059_334_F'),('/COMTRADE/WY9D_RCD_84865_20220104_142059_334_F.dmf',1641277259,12752,'WY9D_RCD_84865_20220104_142059_334_F'),('/COMTRADE/WY9D_RCD_84865_20220104_142059_334_F.hdr',1641277259,8460,'WY9D_RCD_84865_20220104_142059_334_F'),('/COMTRADE/WY9D_RCD_84866_20220104_142130_976_F.cfg',1641277290,3800,'WY9D_RCD_84866_20220104_142130_976_F'),('/COMTRADE/WY9D_RCD_84866_20220104_142130_976_F.dat',1641277290,2310816,'WY9D_RCD_84866_20220104_142130_976_F'),('/COMTRADE/WY9D_RCD_84866_20220104_142130_976_F.dmf',1641277290,12752,'WY9D_RCD_84866_20220104_142130_976_F'),('/COMTRADE/WY9D_RCD_84866_20220104_142130_976_F.hdr',1641277290,8460,'WY9D_RCD_84866_20220104_142130_976_F'),('/COMTRADE/WY9D_RCD_84867_20220104_142402_124_F.cfg',1641277442,3800,'WY9D_RCD_84867_20220104_142402_124_F'),('/COMTRADE/WY9D_RCD_84867_20220104_142402_124_F.dat',1641277442,2111808,'WY9D_RCD_84867_20220104_142402_124_F'),('/COMTRADE/WY9D_RCD_84867_20220104_142402_124_F.dmf',1641277442,12752,'WY9D_RCD_84867_20220104_142402_124_F'),('/COMTRADE/WY9D_RCD_84867_20220104_142402_124_F.hdr',1641277442,8460,'WY9D_RCD_84867_20220104_142402_124_F');
/*!40000 ALTER TABLE `WY9D_File` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `intelligenttaskfile`
--

DROP TABLE IF EXISTS `intelligenttaskfile`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `intelligenttaskfile` (
  `FILENAME` varchar(255) NOT NULL,
  `FUNCTIONTYPE` varchar(255) NOT NULL,
  `RECORDTIME` varchar(255) NOT NULL DEFAULT current_timestamp(3),
  PRIMARY KEY (`FILENAME`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `intelligenttaskfile`
--

LOCK TABLES `intelligenttaskfile` WRITE;
/*!40000 ALTER TABLE `intelligenttaskfile` DISABLE KEYS */;
INSERT INTO `intelligenttaskfile` VALUES ('STAT_03_13_20211231_165723_633.xml','03','2021-12-31 16:57:23.647'),('STAT_03_14_20211231_165725_293.xml','03','2021-12-31 16:57:25.295'),('STAT_03_15_20211231_165807_282.xml','03','2021-12-31 16:58:07.283'),('STAT_03_16_20211231_165809_195.xml','03','2021-12-31 16:58:09.196'),('STAT_03_17_20211231_165830_303.xml','03','2021-12-31 16:58:30.303'),('STAT_03_18_20211231_165833_374.xml','03','2021-12-31 16:58:33.375'),('STAT_03_19_20211231_170048_497.xml','03','2021-12-31 17:00:48.500'),('STAT_03_20_20211231_170048_513.xml','03','2021-12-31 17:00:48.514'),('STAT_06_1_20220104_195815_684.xml','06','2022-01-04 19:56:46.262'),('STAT_06_2_20220104_200211_925.xml','06','2022-01-04 20:00:42.570'),('STAT_06_3_20220104_200454_282.xml','06','2022-01-04 20:03:24.928'),('STAT_06_4_20220105_102813_745.xml','06','2022-01-05 10:26:45.126');
/*!40000 ALTER TABLE `intelligenttaskfile` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `maintainlog`
--

DROP TABLE IF EXISTS `maintainlog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `maintainlog` (
  `GUID` int(11) NOT NULL AUTO_INCREMENT,
  `FILENAME` varchar(255) NOT NULL,
  `RECORDTIME` varchar(255) NOT NULL DEFAULT current_timestamp(3),
  PRIMARY KEY (`GUID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `maintainlog`
--

LOCK TABLES `maintainlog` WRITE;
/*!40000 ALTER TABLE `maintainlog` DISABLE KEYS */;
/*!40000 ALTER TABLE `maintainlog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `operationlog`
--

DROP TABLE IF EXISTS `operationlog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `operationlog` (
  `GUID` int(11) NOT NULL AUTO_INCREMENT,
  `FILENAME` varchar(255) NOT NULL,
  `RECORDTIME` varchar(255) NOT NULL DEFAULT current_timestamp(3),
  PRIMARY KEY (`GUID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `operationlog`
--

LOCK TABLES `operationlog` WRITE;
/*!40000 ALTER TABLE `operationlog` DISABLE KEYS */;
/*!40000 ALTER TABLE `operationlog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `patrolfile`
--

DROP TABLE IF EXISTS `patrolfile`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `patrolfile` (
  `FILENAME` varchar(255) NOT NULL,
  `TASKFINISHTIME` varchar(255) NOT NULL DEFAULT current_timestamp(3),
  `ACCESSDEVNUM` int(11) NOT NULL,
  `TASKDEVNUM` int(11) NOT NULL,
  `ABNORMALDEVNUM` int(11) NOT NULL,
  `SERIOUSDEVNUM` int(11) NOT NULL,
  PRIMARY KEY (`FILENAME`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `patrolfile`
--

LOCK TABLES `patrolfile` WRITE;
/*!40000 ALTER TABLE `patrolfile` DISABLE KEYS */;
INSERT INTO `patrolfile` VALUES ('checkreport_20220104090734.xml','2022-01-04 09:06:05.128',282,100,0,40),('checkreport_20220104090903.xml','2022-01-04 09:09:03.639',283,44,0,40),('checkreport_20220104091301.xml','2022-01-04 09:13:01.847',283,44,0,40),('checkreport_20220104092658.xml','2022-01-04 09:25:29.432',282,100,0,40),('checkreport_20220104092901.xml','2022-01-04 09:27:32.061',283,44,0,40),('checkreport_20220104093100.xml','2022-01-04 09:29:31.954',283,44,0,40),('checkreport_20220104094239.xml','2022-01-04 09:41:10.350',283,44,0,40),('checkreport_20220104094315.xml','2022-01-04 09:41:46.590',283,44,0,40),('checkreport_20220104113132.xml','2022-01-04 11:31:33.138',283,44,0,40),('checkreport_20220104194928.xml','2022-01-04 19:47:59.151',283,44,0,40),('checkreport_20220104195107.xml','2022-01-04 19:49:37.841',283,44,0,40),('checkreport_20220104195815.xml','2022-01-04 19:56:46.216',283,44,0,40),('checkreport_20220104200211.xml','2022-01-04 20:00:42.498',283,44,0,40),('checkreport_20220104200454.xml','2022-01-04 20:03:24.849',283,44,0,40),('checkreport_20220105083728.xml','2022-01-05 08:35:58.483',283,44,0,40),('checkreport_20220105102813.xml','2022-01-05 10:26:45.082',283,44,0,40);
/*!40000 ALTER TABLE `patrolfile` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `runninglog`
--

DROP TABLE IF EXISTS `runninglog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `runninglog` (
  `GUID` int(11) NOT NULL AUTO_INCREMENT,
  `FILENAME` varchar(255) NOT NULL,
  `RECORDTIME` varchar(255) NOT NULL DEFAULT current_timestamp(3),
  PRIMARY KEY (`GUID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `runninglog`
--

LOCK TABLES `runninglog` WRITE;
/*!40000 ALTER TABLE `runninglog` DISABLE KEYS */;
/*!40000 ALTER TABLE `runninglog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transienttaskfile`
--

DROP TABLE IF EXISTS `transienttaskfile`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `transienttaskfile` (
  `FILENAME` varchar(255) NOT NULL,
  `RECORDTIME` varchar(255) NOT NULL DEFAULT current_timestamp(3),
  PRIMARY KEY (`FILENAME`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transienttaskfile`
--

LOCK TABLES `transienttaskfile` WRITE;
/*!40000 ALTER TABLE `transienttaskfile` DISABLE KEYS */;
/*!40000 ALTER TABLE `transienttaskfile` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-01-05 10:58:26
