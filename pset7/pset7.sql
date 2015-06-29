-- MySQL dump 10.14  Distrib 5.5.32-MariaDB, for Linux (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.32-MariaDB

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
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `transaction` varchar(6) COLLATE utf8_unicode_ci NOT NULL,
  `symbol` varchar(6) COLLATE utf8_unicode_ci NOT NULL,
  `shares` bigint(255) unsigned NOT NULL,
  `price` decimal(65,4) unsigned NOT NULL,
  `date` datetime NOT NULL,
  `id` int(10) unsigned NOT NULL,
  PRIMARY KEY (`date`),
  UNIQUE KEY `date` (`date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES ('buy','GOOG',2,511.1700,'2014-10-17 22:48:07',11),('buy','wmt',6,74.1000,'2014-10-17 23:03:41',11),('sell','GOOG',12,34.2340,'2014-10-17 23:17:53',11),('buy','F',30,14.0200,'2014-10-17 23:55:53',11),('sell','F',5,14.0200,'2014-10-18 00:21:16',11),('sell','F',9,14.0200,'2014-10-18 01:03:31',11),('sell','WMT',1,74.1000,'2014-10-18 01:05:40',11),('buy','MSFT',60,43.6300,'2014-10-18 01:06:27',11),('sell','MSFT',30,43.6300,'2014-10-18 01:07:10',11);
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portfolios`
--

DROP TABLE IF EXISTS `portfolios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `portfolios` (
  `id` int(10) unsigned NOT NULL,
  `symbol` varchar(6) COLLATE utf8_unicode_ci NOT NULL,
  `shares` bigint(20) unsigned NOT NULL,
  PRIMARY KEY (`id`,`symbol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portfolios`
--

LOCK TABLES `portfolios` WRITE;
/*!40000 ALTER TABLE `portfolios` DISABLE KEYS */;
INSERT INTO `portfolios` VALUES (6,'XONE',104),(11,'AAPL',2),(11,'BBRY',1),(11,'GOOG',3),(11,'MSFT',30);
/*!40000 ALTER TABLE `portfolios` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'caesar','$1$74bPDMYv$OkO6/D8DoYkVfyTi0kko9/',10000.0000),(2,'hirschhorn','$1$74bPDMYv$OkO6/D8DoYkVfyTi0kko9/',10000.0000),(3,'jharvard','$1$74bPDMYv$OkO6/D8DoYkVfyTi0kko9/',10000.0000),(4,'malan','$1$74bPDMYv$OkO6/D8DoYkVfyTi0kko9/',10000.0000),(5,'milo','$1$74bPDMYv$OkO6/D8DoYkVfyTi0kko9/',10000.0000),(6,'skroob','$1$74bPDMYv$OkO6/D8DoYkVfyTi0kko9/',0.0000),(7,'zamyla','$1$74bPDMYv$OkO6/D8DoYkVfyTi0kko9/',10000.0000),(8,'Mjones','$1$74bPDMYv$OkO6/D8DoYkVfyTi0kko9/',100000.0000),(11,'dude77','$1$74bPDMYv$OkO6/D8DoYkVfyTi0kko9/',80732.3300),(12,'cristina','$1$74bPDMYv$OkO6/D8DoYkVfyTi0kko9/',100000.0000),(13,'mike','$1$74bPDMYv$OkO6/D8DoYkVfyTi0kko9/',100000.0000);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-10-18  1:58:38
