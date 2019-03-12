-- phpMyAdmin SQL Dump
-- version 4.0.4.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Apr 21, 2017 at 01:50 AM
-- Server version: 5.5.32
-- PHP Version: 5.4.19

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `atmdb`
--
CREATE DATABASE IF NOT EXISTS `atmdb` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `atmdb`;

-- --------------------------------------------------------

--
-- Table structure for table `transection`
--

CREATE TABLE IF NOT EXISTS `transection` (
  `datetime1` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `type` varchar(10) NOT NULL,
  `act_no` int(6) NOT NULL,
  `trac_amt` int(7) NOT NULL,
  `final_balance` int(10) NOT NULL,
  UNIQUE KEY `datetime1` (`datetime1`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `transection`
--

INSERT INTO `transection` (`datetime1`, `type`, `act_no`, `trac_amt`, `final_balance`) VALUES
('2017-04-15 04:56:18', 'WITHDRAWAL', 123456, 200, 3300),
('2017-04-15 04:56:53', 'DEPOSITE', 123456, 500, 3800),
('2017-04-15 04:57:26', 'Transfer', 123456, 500, 3300),
('2017-04-15 04:57:54', 'Transfer', 123456, 100, 3200),
('2017-04-15 05:59:17', 'DEPOSITE', 123456, 100, 3300),
('2017-04-15 06:00:02', 'DEPOSITE', 123456, 500, 3800),
('2017-04-15 06:00:33', 'DEPOSITE', 123456, 200, 4000),
('2017-04-15 08:21:12', 'WITHDRAWAL', 123456, 500, 3500),
('2017-04-15 08:26:27', 'INSTANT', 654321, 100, 7600),
('2017-04-18 17:54:33', 'INSTANT', 123456, 100, 4900),
('2017-04-18 18:32:46', 'DEPOSITE', 123456, 100, 5000),
('2017-04-18 18:37:07', 'DEPOSITE', 123456, 100, 5100),
('2017-04-19 01:27:27', 'WITHDRAWAL', 123456, 200, 4900),
('2017-04-19 01:33:31', 'Tr', 123456, 200, 4700),
('2017-04-19 01:36:37', 'FAST CASH', 123456, 500, 4200),
('2017-04-19 01:44:52', 'WITHDRAWAL', 123456, 200, 4000),
('2017-04-19 01:47:15', 'DEPOSITE', 123456, 200, 4200),
('2017-04-19 01:48:22', 'DEPOSITE', 123456, 200, 4400),
('2017-04-19 01:53:45', 'WITHDRAWAL', 654321, 200, 5000),
('2017-04-19 02:00:03', 'WITHDRAWAL', 123456, 200, 4200),
('2017-04-19 02:04:12', 'INSTANT', 123456, 200, 4000),
('2017-04-19 17:37:46', 'WITHDRAWAL', 787462, 100, 49900),
('2017-04-19 17:38:28', 'DEPOSITE', 787462, 100, 50000),
('2017-04-19 17:39:09', 'Tr', 787462, 500, 49500),
('2017-04-19 17:43:59', 'FAST CASH', 787462, 1000, 48500),
('2017-04-19 17:46:55', 'INSTANT', 787462, 200, 48300),
('2017-04-19 18:29:47', 'INSTANT', 787462, 100, 48200),
('2017-04-19 18:39:50', 'INSTANT', 787462, 500, 47700),
('2017-04-19 18:48:40', 'INSTANT', 787462, 100, 47600),
('2017-04-19 22:06:05', 'INSTANT', 787462, 200, 47400),
('2017-04-20 21:10:57', 'TRANSFER', 123456, 200, 3800),
('2017-04-20 21:13:45', 'TRANSFER', 123456, 200, 3600),
('2017-04-20 21:15:29', 'TRANSFER', 123456, 2100, 1500),
('2017-04-20 21:51:12', 'WITHDRAWAL', 123456, 500, 1000),
('2017-04-20 21:53:33', 'TRANSFER', 123456, 200, 800),
('2017-04-20 21:59:38', 'INSTANT', 654321, 500, 7700),
('2017-04-20 23:31:49', 'WITHDRAWAL', 200300, 500, 4500),
('2017-04-20 23:35:28', 'TRANSFER', 200300, 500, 4000),
('2017-04-20 23:36:51', 'INSTANT', 200300, 500, 3500);

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE IF NOT EXISTS `user` (
  `act_no` int(6) NOT NULL,
  `pin_no` varchar(4) NOT NULL,
  `name` varchar(50) NOT NULL,
  `reg_mob_no` varchar(12) DEFAULT NULL,
  `balance` float NOT NULL,
  `act_type` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`act_no`, `pin_no`, `name`, `reg_mob_no`, `balance`, `act_type`) VALUES
(123456, '1234', 'Patel Margi', '7874062672', 1300, 'Saving'),
(654321, '7946', 'Patel Mayur', '8155881015', 7700, 'Current'),
(794646, '4646', 'Margi', '7854963215', 5000, 'Saving'),
(456895, '5632', 'Krupa', '9925288834', 50000, 'Current'),
(787462, '7887', 'Bharatkumar', '7874062672', 47400, 'Saving'),
(987654, '8888', 'Akshar', '7874062672', 5000, 'Saving'),
(200300, '1234', 'Suraj', '7284970941', 3500, 'Saving');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
