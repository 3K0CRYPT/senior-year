-- MySQL dump 10.13  Distrib 5.5.52, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: f17_mbartlet
-- ------------------------------------------------------
-- Server version	5.5.52-0ubuntu0.14.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `CUSTOMERS`
--

DROP TABLE IF EXISTS `CUSTOMERS`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CUSTOMERS` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `LastName` varchar(255) NOT NULL,
  `FirstName` varchar(255) DEFAULT NULL,
  `Email` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `LastName` (`LastName`,`FirstName`,`Email`)
) ENGINE=InnoDB AUTO_INCREMENT=61 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CUSTOMERS`
--

LOCK TABLES `CUSTOMERS` WRITE;
/*!40000 ALTER TABLE `CUSTOMERS` DISABLE KEYS */;
INSERT INTO `CUSTOMERS` VALUES (55,'Jam','Space','space@jam.wew'),(51,'Spergin','Johnny','t@t.com'),(53,'SperginN','Johnny','2t@t.com'),(47,'t','t','test@test.com');
/*!40000 ALTER TABLE `CUSTOMERS` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ORDERS`
--

DROP TABLE IF EXISTS `ORDERS`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ORDERS` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `CID` int(11) NOT NULL,
  `PID` int(11) NOT NULL,
  `Quantity` smallint(6) NOT NULL DEFAULT '0',
  `Tax` float DEFAULT NULL,
  `Donation` tinyint(1) DEFAULT '0',
  `Timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `CID` (`CID`,`PID`,`Timestamp`),
  KEY `PID` (`PID`),
  CONSTRAINT `ORDERS_ibfk_1` FOREIGN KEY (`CID`) REFERENCES `CUSTOMERS` (`ID`),
  CONSTRAINT `ORDERS_ibfk_2` FOREIGN KEY (`PID`) REFERENCES `PRODUCTS` (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=26 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ORDERS`
--

LOCK TABLES `ORDERS` WRITE;
/*!40000 ALTER TABLE `ORDERS` DISABLE KEYS */;
INSERT INTO `ORDERS` VALUES (13,47,1,3,1.07,1,'2017-11-28 19:11:58'),(14,47,5,1,1.07,0,'2017-11-28 19:12:24'),(16,47,1,3,1.07,0,'2017-11-28 19:13:08'),(17,51,4,11,1.07,1,'2017-11-28 19:57:05'),(19,53,5,7,1.07,0,'2017-11-28 19:58:08'),(20,47,4,5,1.07,1,'2017-11-28 21:15:46'),(21,55,5,20,1.07,1,'2017-11-29 03:13:41'),(22,55,5,20,1.07,0,'2017-11-29 03:13:59'),(23,55,5,20,1.07,1,'2017-11-29 03:14:05'),(24,55,4,20,1.07,1,'2017-11-29 03:14:16'),(25,55,4,20,1.07,1,'2017-11-29 03:14:27');
/*!40000 ALTER TABLE `ORDERS` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `PRODUCTS`
--

DROP TABLE IF EXISTS `PRODUCTS`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `PRODUCTS` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `Product` varchar(255) NOT NULL,
  `Price` float NOT NULL DEFAULT '0',
  `Quantity` smallint(6) DEFAULT '0',
  `Image` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `Product` (`Product`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PRODUCTS`
--

LOCK TABLES `PRODUCTS` WRITE;
/*!40000 ALTER TABLE `PRODUCTS` DISABLE KEYS */;
INSERT INTO `PRODUCTS` VALUES (1,'Snowboard',100,94,'Snowboard.jpg'),(2,'Skis & Poles',150,94,'Ski.jpg'),(3,'Boots',50,0,'Boots.jpg'),(4,'Coat',50,44,'Coat.jpg'),(5,'Hat',25,32,'Hat.jpg');
/*!40000 ALTER TABLE `PRODUCTS` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-11-28 20:19:30
