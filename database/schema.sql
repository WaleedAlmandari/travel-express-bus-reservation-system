-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 20, 2024 at 06:21 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `workshop1`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `admin_ID` varchar(25) NOT NULL,
  `admin_name` varchar(45) NOT NULL,
  `admin_email` varchar(45) NOT NULL,
  `admin_password` varchar(45) NOT NULL,
  `admin_phonenumber` varchar(20) NOT NULL,
  `admin_address` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`admin_ID`, `admin_name`, `admin_email`, `admin_password`, `admin_phonenumber`, `admin_address`) VALUES
('D74', 'AHMED', 'waleediss@outlook.com', '74', '01111602040', 'UG'),
('Deloo74', 'Waleed', 'delooo774@gmail.com', '12345678', '01111602030', 'Melaka - Bukit Beruang ');

-- --------------------------------------------------------

--
-- Table structure for table `booking`
--

CREATE TABLE `booking` (
  `booking_ID` varchar(50) NOT NULL,
  `customer_ID` varchar(25) NOT NULL,
  `trip_ID` varchar(25) NOT NULL,
  `booking_date` date NOT NULL,
  `seat_number` varchar(45) NOT NULL,
  `final_price` varchar(25) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `booking`
--

INSERT INTO `booking` (`booking_ID`, `customer_ID`, `trip_ID`, `booking_date`, `seat_number`, `final_price`) VALUES
('cr105595', 'n_izaah', 'TRIP041', '2024-06-09', '4B', '40.00'),
('cr114745', 'sopi_66', 'TRIP041', '2024-06-02', '5B', '32.00'),
('cr114846', 'aali01', 'TRIP002', '2024-01-05', '1A', '50.00'),
('cr114847', 'cwei09', 'TRIP005', '2024-04-20', '4D', '55.00'),
('cr114848', 'hasoon74', 'TRIP010', '2024-09-05', '7C', '65.00'),
('cr114849', 'mkumar03', 'TRIP013', '2024-01-20', '10C', '55.00'),
('cr114850', 'n_izaah', 'TRIP016', '2024-07-05', '6C', '55.00'),
('cr114851', 'saminah02', 'TRIP019', '2024-02-20', '4D', '65.00'),
('cr114852', 'aali01', 'TRIP001', '2024-01-10', '1A', '50.00'),
('cr114853', 'cwei09', 'TRIP004', '2024-04-25', '4D', '55.00'),
('cr114854', 'hasoon74', 'TRIP007', '2024-07-15', '7C', '65.00'),
('cr114855', 'mkumar03', 'TRIP010', '2024-10-30', '10B', '55.00'),
('cr114856', 'n_izaah', 'TRIP013', '2024-01-15', '3A', '55.00'),
('cr114857', 'saminah02', 'TRIP016', '2024-04-30', '6D', '65.00'),
('cr114858', 'yo_18', 'TRIP019', '2024-07-15', '9C', '80.00'),
('cr114859', 'aali01', 'TRIP021', '2024-01-05', '1A', '50.00'),
('cr114860', 'cwei09', 'TRIP024', '2024-04-20', '4D', '45.00'),
('cr114861', 'hasoon74', 'TRIP027', '2024-07-05', '7C', '60.00'),
('cr114862', 'mkumar03', 'TRIP030', '2024-10-20', '10B', '55.00'),
('cr114863', 'n_izaah', 'TRIP033', '2024-01-05', '3A', '50.00'),
('cr114864', 'saminah02', 'TRIP036', '2024-04-20', '6D', '45.00'),
('cr114865', 'yo_18', 'TRIP039', '2024-07-05', '9C', '60.00'),
('cr114866', 'aali10', 'TRIP042', '2024-10-20', '2B', '55.00'),
('cr114867', 'fatimah_97', 'TRIP045', '2024-01-10', '5A', '50.00'),
('cr114868', 'lwei04', 'TRIP048', '2024-04-25', '8D', '45.00'),
('db113814', 'aali10', 'TRIP003', '2024-02-10', '2B', '45.00'),
('db113815', 'fatimah_97', 'TRIP008', '2024-05-25', '5A', '60.00'),
('db113816', 'lwei04', 'TRIP011', '2024-11-10', '8B', '45.00'),
('db113817', 'mtan07', 'TRIP014', '2024-03-25', '10B', '40.00'),
('db113818', 'rajoo45', 'TRIP017', '2024-09-10', '6D', '45.00'),
('db113819', 'sopi_66', 'TRIP020', '2024-04-25', '4A', '70.00'),
('db113820', 'aali10', 'TRIP002', '2024-02-15', '2B', '45.00'),
('db113821', 'fatimah_97', 'TRIP005', '2024-05-30', '5A', '60.00'),
('db113822', 'lwei04', 'TRIP008', '2024-08-20', '8D', '45.00'),
('db113823', 'mtan07', 'TRIP011', '2024-11-05', '1C', '40.00'),
('db113824', 'rajoo45', 'TRIP014', '2024-02-20', '4B', '45.00'),
('db113825', 'sopi_66', 'TRIP017', '2024-05-05', '7A', '70.00'),
('db113826', 'zabidin08', 'TRIP020', '2024-08-20', '10D', '85.00'),
('db113827', 'aali10', 'TRIP022', '2024-02-10', '2B', '55.00'),
('db113828', 'fatimah_97', 'TRIP025', '2024-05-25', '5A', '50.00'),
('db113829', 'lwei04', 'TRIP028', '2024-08-10', '8D', '45.00'),
('db113830', 'mtan07', 'TRIP031', '2024-11-25', '1C', '60.00'),
('db113831', 'rajoo45', 'TRIP034', '2024-02-10', '4B', '55.00'),
('db113832', 'sopi_66', 'TRIP037', '2024-05-25', '7A', '50.00'),
('db113833', 'zabidin08', 'TRIP040', '2024-08-10', '10D', '45.00'),
('db113834', 'ali02', 'TRIP043', '2024-11-25', '3C', '60.00'),
('db113835', 'gkumar11', 'TRIP046', '2024-02-15', '6B', '55.00'),
('db113836', 'meian21', 'TRIP049', '2024-05-30', '9A', '50.00'),
('on115729', 'nfatimah05', 'TRIP049', '2024-10-20', '9C', '48.00'),
('on115790', 'ali02', 'TRIP004', '2024-03-15', '3C', '40.00'),
('on115791', 'gkumar11', 'TRIP009', '2024-07-30', '6D', '50.00'),
('on115792', 'meian21', 'TRIP012', '2024-12-15', '9A', '50.00'),
('on115793', 'nfatimah05', 'TRIP015', '2024-05-30', '7A', '50.00'),
('on115794', 'rpillai06', 'TRIP018', '2024-11-15', '2A', '60.00'),
('on115795', 'ali02', 'TRIP003', '2024-03-20', '3C', '40.00'),
('on115796', 'gkumar11', 'TRIP006', '2024-06-10', '6B', '50.00'),
('on115797', 'meian21', 'TRIP009', '2024-09-25', '9A', '50.00'),
('on115798', 'nfatimah05', 'TRIP012', '2024-12-10', '2D', '50.00'),
('on115799', 'rpillai06', 'TRIP015', '2024-03-25', '5C', '60.00'),
('on115800', 'wei_wei', 'TRIP018', '2024-06-10', '8B', '75.00'),
('on115801', 'ali02', 'TRIP023', '2024-03-15', '3C', '60.00'),
('on115802', 'gkumar11', 'TRIP026', '2024-06-30', '6B', '55.00'),
('on115803', 'meian21', 'TRIP029', '2024-09-15', '9A', '50.00'),
('on115804', 'nfatimah05', 'TRIP032', '2024-12-30', '2D', '45.00'),
('on115805', 'rpillai06', 'TRIP035', '2024-03-15', '5C', '60.00'),
('on115806', 'wei_wei', 'TRIP038', '2024-06-30', '8B', '55.00'),
('on115807', 'aali01', 'TRIP041', '2024-09-15', '1A', '50.00'),
('on115808', 'cwei09', 'TRIP044', '2024-12-30', '4D', '45.00'),
('on115809', 'hasoon74', 'TRIP047', '2024-03-20', '7C', '60.00'),
('on115810', 'mkumar03', 'TRIP050', '2024-06-10', '10B', '55.00');

-- --------------------------------------------------------

--
-- Table structure for table `bus`
--

CREATE TABLE `bus` (
  `number_plate` varchar(25) NOT NULL,
  `capacity` int(11) NOT NULL,
  `type` varchar(50) NOT NULL,
  `brand` varchar(45) NOT NULL,
  `condition` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `bus`
--

INSERT INTO `bus` (`number_plate`, `capacity`, `type`, `brand`, `condition`) VALUES
('ASD4567', 60, 'School Bus', 'MAN', 'IN SERVICE'),
('BHV1234', 80, 'Double-Decker', 'Volvo', 'IN SERVICE'),
('GHJ9012', 60, 'Coach', 'Mercedes-Benz', 'IN SERVICE'),
('IKJ5678', 60, 'Coach', 'Hino', 'IN SERVICE'),
('LKU5678', 50, 'Express', 'Scania', 'IN SERVICE'),
('MNB4321', 60, 'School Bus', 'Yutong', 'IN SERVICE'),
('PAV5939', 40, 'Standard City', 'Zhongtong', 'IN SERVICE'),
('PLM3456', 50, 'Express', 'Volvo', 'IN SERVICE'),
('QWE3456', 20, 'Mini Bus', 'Isuzu', 'IN SERVICE'),
('RFV6789', 150, 'Rapid Transit Bus (BRT)', 'Yutong', 'IN SERVICE'),
('SAJ6394', 60, 'Coach', 'Hino', 'IN SERVICE'),
('TGB6789', 20, 'Mini Bus', 'Zhongtong', 'IN SERVICE'),
('TYU7890', 40, 'Standard City', 'Hino', 'IN SERVICE'),
('VCX8765', 150, 'Rapid Transit Bus (BRT)', 'MAN', 'IN SERVICE'),
('YHN1234', 40, 'Standard City', 'Isuzu', 'IN SERVICE'),
('ZAS0987', 80, 'Double-Decker', 'Scania', 'IN SERVICE');

-- --------------------------------------------------------

--
-- Table structure for table `customer`
--

CREATE TABLE `customer` (
  `customer_ID` varchar(25) NOT NULL,
  `customer_name` varchar(45) NOT NULL,
  `customer_email` varchar(45) NOT NULL,
  `customer_password` varchar(45) NOT NULL,
  `customer_address` varchar(255) NOT NULL,
  `customer_phonenumber` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `customer`
--

INSERT INTO `customer` (`customer_ID`, `customer_name`, `customer_email`, `customer_password`, `customer_address`, `customer_phonenumber`) VALUES
('aali01', 'Ahmad Ali', 'sss2123@gmail.com', '123456', '123 Jalan Ampang, Kuala Lumpur', '01111405087'),
('aali10', 'Aisyah Binti Ali', 'aisyah.ali@hotmail.com', '01234', '707 Jalan Raja Chulan, Terengganu', '01234567981'),
('ali02', 'Ali Bin Abu', 'li32@outlook.com', '88990', '606 Jalan Loke Yew, Johor', '01234568061'),
('cwei09', 'Chong Wei', 'chong.wei@gmail.com', '90123', '606 Jalan Dang Wangi, Pahang', '01234567975'),
('fatimah_97', 'Fatimah Ahmad', 'fatimah.ahmad@icloud.com', '55667', '303 Jalan Kepong, Putrajaya', '01234568034'),
('gkumar11', 'Ganesh Kumar', 'ganesh.kumar@icloud.com', '11223', '808 Jalan Sultan, Negeri Sembilan', '01234567992'),
('hasoon74', 'Hassan Ali', 'hassan.ali@outlook.com', '66778', '404 Jalan Klang Lama, Labuan', '01234568042'),
('lwei04', 'Lim Wei', 'lim.wei@outlook.com', '45678', '101 Jalan Petaling, Perak', '01234567924'),
('meian21', 'Mei Tan', 'mei.tan@gmail.com', '77889', '505 Jalan Cheras, Selangor', '01234568055'),
('mkumar03', 'Muthu Kumar', 'muthu.kumar@icloud.com', '34567', '789 Jalan Bukit Bintang, Penang', '01234567919'),
('mtan07', 'Tan Mei Ling', 'tan.meiling@icloud.com', '78901', '404 Jalan Imbi, Malacca', '01234567951'),
('nfatimah05', 'Nur Fatimah', 'nur.fatimah@gmail.com', '56789', '202 Jalan Pudu, Johor', '01234567938'),
('n_izaah', 'Nurul Izzah', 'nurul.izzah@icloud.com', '99001', '707 Jalan Kuching, Sabah', '01234568074'),
('rajoo45', 'Mohan Raj', 'mohan.raj@outlook.com', '057107', '808 Jalan Setapak, Sarawak', '01234568082'),
('rpillai06', 'Ravi Pillai', 'ravi.pillai@hotmail.com', '67890', '303 Jalan Raja Laut, Kedah', '01234567941'),
('saminah02', 'Siti Aminah', 'siti.aminah@hotmail.com', '23456', '456 Jalan Tun Razak, Selangor', '01234567902'),
('Sar_9700', 'Sarah Ahmed', 'sar9700@gmail.com', '0571075822', '707 Jalan Raja Chulan, Terengganu', '01147385945'),
('sopi_66', 'Sophia Lim', 'sophia.lim@outlook.com', '22334', '909 Jalan TAR, Sabah', '01234568002'),
('wei_wei', 'Wei Ling', 'wei.ling@hotmail.com', '44556', '202 Jalan Ipoh, Perlis', '01234568027'),
('yo_18', 'Yusof Bin Osman', 'yusof.osman@gmail.com', '33445', '101 Jalan Gombak, Sarawak', '01234568019'),
('zabidin08', 'Zainal Abidin', 'zainal.abidin@outlook.com', '89012', '505 Jalan Sultan Ismail, Kelantan', '01234567962');

-- --------------------------------------------------------

--
-- Table structure for table `driver`
--

CREATE TABLE `driver` (
  `driver_ID` varchar(25) NOT NULL,
  `driver_name` varchar(45) NOT NULL,
  `driver_address` varchar(255) NOT NULL,
  `driver_phonenumber` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `driver`
--

INSERT INTO `driver` (`driver_ID`, `driver_name`, `driver_address`, `driver_phonenumber`) VALUES
('DR-ABC001', 'Ahmad', 'Kuala Lumpur', '01234567890'),
('DR-BCD010', 'Ganesh', 'Alor Setar', '01112345678'),
('DR-DEF002', 'Razaq', 'Melaka', '01147385943'),
('DR-EFG011', 'Aisyah', 'Miri', '01223456789'),
('DR-GHI003', 'Siti', 'Penang', '01345678901'),
('DR-HIJ012', 'Ravi', 'Sandakan', '01334567890'),
('DR-JKL004', 'Muthu', 'Johor Bahru', '01456789012'),
('DR-KLM013', 'Sophia', 'Sibu', '01445678901'),
('DR-MNO005', 'Lim', 'Ipoh', '01567890123'),
('DR-NOP014', 'Yusof', 'Batu Pahat', '01556789012'),
('DR-PQR006', 'Zainab', 'Shah Alam', '01678901234'),
('DR-QRS015', 'Wei', 'Tawau', '01667890123'),
('DR-STU007', 'Hassan', 'Kota Kinabalu', '01789012345'),
('DR-VWX008', 'Chong', 'Kuching', '01890123456'),
('DR-YZA009', 'Fatimah', 'Seremban', '01111394059');

-- --------------------------------------------------------

--
-- Table structure for table `payment`
--

CREATE TABLE `payment` (
  `payment_ID` varchar(25) NOT NULL,
  `booking_ID` varchar(50) NOT NULL,
  `payment_method` varchar(45) NOT NULL,
  `payment_date` date NOT NULL,
  `bank_name` varchar(50) DEFAULT NULL,
  `payment_amount` int(25) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `payment`
--

INSERT INTO `payment` (`payment_ID`, `booking_ID`, `payment_method`, `payment_date`, `bank_name`, `payment_amount`) VALUES
('cr105595y202469', 'cr105595', 'Credit Card', '2024-06-09', NULL, NULL),
('cr114845y20240602', 'cr114745', 'Credit Card', '2024-06-02', NULL, NULL),
('cr114846y20240105', 'cr114846', 'Credit Card', '2024-01-05', NULL, NULL),
('cr114847y20240420', 'cr114847', 'Credit Card', '2024-04-20', NULL, NULL),
('cr114848y20240905', 'cr114848', 'Credit Card', '2024-09-05', NULL, NULL),
('cr114849y20240120', 'cr114849', 'Credit Card', '2024-01-20', NULL, NULL),
('cr114850y20240705', 'cr114850', 'Credit Card', '2024-07-05', NULL, NULL),
('cr114851y20240220', 'cr114851', 'Credit Card', '2024-02-20', NULL, NULL),
('cr114852y20240110', 'cr114852', 'Credit Card', '2024-01-10', NULL, NULL),
('cr114853y20240425', 'cr114853', 'Credit Card', '2024-04-25', NULL, NULL),
('cr114854y20240715', 'cr114854', 'Credit Card', '2024-07-15', NULL, NULL),
('cr114855y20241030', 'cr114855', 'Credit Card', '2024-10-30', NULL, NULL),
('cr114856y20240115', 'cr114856', 'Credit Card', '2024-01-15', NULL, NULL),
('cr114857y20240430', 'cr114857', 'Credit Card', '2024-04-30', NULL, NULL),
('cr114858y20240715', 'cr114858', 'Credit Card', '2024-07-15', NULL, NULL),
('cr114859y20240105', 'cr114859', 'Credit Card', '2024-01-05', NULL, NULL),
('cr114860y20240420', 'cr114860', 'Credit Card', '2024-04-20', NULL, NULL),
('cr114861y20240705', 'cr114861', 'Credit Card', '2024-07-05', NULL, NULL),
('cr114862y20241020', 'cr114862', 'Credit Card', '2024-10-20', NULL, NULL),
('cr114863y20240105', 'cr114863', 'Credit Card', '2024-01-05', NULL, NULL),
('cr114864y20240420', 'cr114864', 'Credit Card', '2024-04-20', NULL, NULL),
('cr114865y20240705', 'cr114865', 'Credit Card', '2024-07-05', NULL, NULL),
('cr114866y20241020', 'cr114866', 'Credit Card', '2024-10-20', NULL, NULL),
('cr114867y20240110', 'cr114867', 'Credit Card', '2024-01-10', NULL, NULL),
('cr114868y20240425', 'cr114868', 'Credit Card', '2024-04-25', NULL, NULL),
('db113814y20240210', 'db113814', 'Debit Card', '2024-02-10', NULL, NULL),
('db113815y20240525', 'db113815', 'Debit Card', '2024-05-25', NULL, NULL),
('db113816y20241110', 'db113816', 'Debit Card', '2024-11-10', NULL, NULL),
('db113817y20240325', 'db113817', 'Debit Card', '2024-03-25', NULL, NULL),
('db113818y20240910', 'db113818', 'Debit Card', '2024-09-10', NULL, NULL),
('db113819y20240425', 'db113819', 'Debit Card', '2024-04-25', NULL, NULL),
('db113820y20240215', 'db113820', 'Debit Card', '2024-02-15', NULL, NULL),
('db113821y20240530', 'db113821', 'Debit Card', '2024-05-30', NULL, NULL),
('db113822y20240820', 'db113822', 'Debit Card', '2024-08-20', NULL, NULL),
('db113823y20241105', 'db113823', 'Debit Card', '2024-11-05', NULL, NULL),
('db113824y20240220', 'db113824', 'Debit Card', '2024-02-20', NULL, NULL),
('db113825y20240505', 'db113825', 'Debit Card', '2024-05-05', NULL, NULL),
('db113826y20240820', 'db113826', 'Debit Card', '2024-08-20', NULL, NULL),
('db113827y20240210', 'db113827', 'Debit Card', '2024-02-10', NULL, NULL),
('db113828y20240525', 'db113828', 'Debit Card', '2024-05-25', NULL, NULL),
('db113829y20240810', 'db113829', 'Debit Card', '2024-08-10', NULL, NULL),
('db113830y20241125', 'db113830', 'Debit Card', '2024-11-25', NULL, NULL),
('db113831y20240210', 'db113831', 'Debit Card', '2024-02-10', NULL, NULL),
('db113832y20240525', 'db113832', 'Debit Card', '2024-05-25', NULL, NULL),
('db113833y20240810', 'db113833', 'Debit Card', '2024-08-10', NULL, NULL),
('db113834y20241125', 'db113834', 'Debit Card', '2024-11-25', NULL, NULL),
('db113835y20240215', 'db113835', 'Debit Card', '2024-02-15', NULL, NULL),
('db113836y20240530', 'db113836', 'Debit Card', '2024-05-30', NULL, NULL),
('on115789y20241020', 'on115729', 'Online Banking', '2024-10-20', 'RHB', 48),
('on115790y20240315', 'on115790', 'Online Banking', '2024-03-15', 'Maybank', 40),
('on115791y20240730', 'on115791', 'Online Banking', '2024-07-30', 'BSN', 50),
('on115792y20241215', 'on115792', 'Online Banking', '2024-12-15', 'CIMB', 50),
('on115793y20240530', 'on115793', 'Online Banking', '2024-05-30', 'Public Bank  ', 50),
('on115794y20241115', 'on115794', 'Online Banking', '2024-11-15', 'Maybank', 60),
('on115795y20240320', 'on115795', 'Online Banking', '2024-03-20', 'Maybank', 40),
('on115796y20240610', 'on115796', 'Online Banking', '2024-06-10', 'Maybank', 50),
('on115797y20240925', 'on115797', 'Online Banking', '2024-09-25', 'Maybank', 50),
('on115798y20241210', 'on115798', 'Online Banking', '2024-12-10', 'Maybank', 50),
('on115799y20240325', 'on115799', 'Online Banking', '2024-03-25', 'Maybank', 60),
('on115800y20240610', 'on115800', 'Online Banking', '2024-06-10', 'Maybank', 75),
('on115801y20240315', 'on115801', 'Online Banking', '2024-03-15', 'Maybank', 60),
('on115802y20240630', 'on115802', 'Online Banking', '2024-06-30', 'Maybank', 55),
('on115803y20240915', 'on115803', 'Online Banking', '2024-09-15', 'Maybank', 50),
('on115804y20241230', 'on115804', 'Online Banking', '2024-12-30', 'Maybank', 45),
('on115805y20240315', 'on115805', 'Online Banking', '2024-03-15', 'Maybank', 60),
('on115806y20240630', 'on115806', 'Online Banking', '2024-06-30', 'Maybank', 55),
('on115807y20240915', 'on115807', 'Online Banking', '2024-09-15', 'Maybank', 50),
('on115808y20241230', 'on115808', 'Online Banking', '2024-12-30', 'Maybank', 45),
('on115809y20240320', 'on115809', 'Online Banking', '2024-03-20', 'Maybank', 60),
('on115810y20240610', 'on115810', 'Online Banking', '2024-06-10', 'Maybank', 55);

-- --------------------------------------------------------

--
-- Table structure for table `staff`
--

CREATE TABLE `staff` (
  `staff_ID` varchar(25) NOT NULL,
  `staff_name` varchar(45) NOT NULL,
  `staff_email` varchar(45) NOT NULL,
  `staff_password` varchar(45) NOT NULL,
  `staff_address` varchar(255) NOT NULL,
  `staff_phonenumber` varchar(20) NOT NULL,
  `staff_position` varchar(45) DEFAULT NULL,
  `staff_date_hire` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `staff`
--

INSERT INTO `staff` (`staff_ID`, `staff_name`, `staff_email`, `staff_password`, `staff_address`, `staff_phonenumber`, `staff_position`, `staff_date_hire`) VALUES
('aabu18', 'Ali Bin Abu', 'ali.abu@hotmail.com', '88990', '606 Jalan Loke Yew, Johor', '01234568067', 'Safety Officer', '2024-05-18'),
('aali10', 'Aisyah Binti Ali', 'aisyah.ali@hotmail.com', '01234', '707 Jalan Raja Chulan, Terengganu', '01111603040', 'Safety Officer', '2023-10-01'),
('ami_66', 'Amin', 'min212@gmail.com', '2233445', '750 Melaka, UG Apartments', '01748948341', 'Manager', '2024-06-02'),
('azainal01', 'Ahmad Zainal', 'ahmad.zainal@gmail.com', '12345', '123 Jalan Ampang, Kuala Lumpur', '01234567895', 'Operations Manager', '2023-01-15'),
('cwei09', 'Chong Wei', 'chong.wei@gmail.com', '90123', '606 Jalan Dang Wangi, Pahang', '01234567972', 'Bus Attendant', '2023-09-14'),
('fahmad15', 'Fatimah Ahmad', 'fatimah.ahmad@outlook.com', '55667', '303 Jalan Kepong, Putrajaya', '01234568034', 'Operations Manager', '2024-03-10'),
('gkumar11', 'Ganesh Kumar', 'ganesh.kumar@outlook.com', '11223', '808 Jalan Sultan, Negeri Sembilan', '01234567992', 'Human Resources Manager', '2023-11-05'),
('hali16', 'Hassan Ali', 'hassan.ali@icloud.com', '66778', '404 Jalan Klang Lama, Labuan', '01234568042', 'Fleet Manager', '2024-04-05'),
('hamed_32', 'Mohammed Ali', 'hamed32@gmail.com', '0987667890', '231 Jalan Sultan,Melaka ', '01147385943', 'Accountant', '2024-06-05'),
('lwei04', 'Lim Wei', 'lim.wei@icloud.com', '45678', '101 Jalan Petaling, Perak', '01234567922', 'Operations Manager', '2023-04-18'),
('mkumar03', 'Muthu Kumar', 'muthu.kumar@outlook.com', '34567', '789 Jalan Bukit Bintang, Penang', '01234567912', 'Customer Service Representative', '2023-03-10'),
('mraj20', 'Mohan Raj', 'mohan.raj@icloud.com', '10010', '808 Jalan Setapak, Sarawak', '01234568084', 'Scheduling Coordinator', '2024-07-01'),
('mtan07', 'Tan Mei Ling', 'tan.meiling@outlook.com', '78901', '404 Jalan Imbi, Malacca', '01234567957', 'IT Specialist', '2023-07-12'),
('mtan17', 'Mei Tan', 'mei.tan@gmail.com', '77889', '505 Jalan Cheras, Selangor', '01234568052', 'IT Specialist', '2024-05-01'),
('nfatimah05', 'Nur Fatimah', 'nur.fatimah@gmail.com', '56789', '202 Jalan Pudu, Johor', '01234567932', 'Fleet Manager', '2023-05-25'),
('nizzah19', 'Nurul Izzah', 'nurul.izzah@outlook.com', '99001', '707 Jalan Kuching, Sabah', '01234568075', 'Human Resources Manager', '2024-06-11'),
('rpillai06', 'Ravi Pillai', 'ravi.pillai@hotmail.com', '67890', '303 Jalan Raja Laut, Kedah', '01234567941', 'Marketing and Sales Manager', '2023-06-30'),
('saminah02', 'Siti Aminah', 'siti.aminah@hotmail.com', '23456', '456 Jalan Tun Razak, Selangor', '01234567909', 'Booking Agent', '2023-02-20'),
('slim12', 'Sophia Lim', 'sophia.lim@icloud.com', '22334', '909 Jalan TAR, Sabah', '01234568002', 'Scheduling Coordinator', '2023-12-19'),
('wling14', 'Wei Ling', 'wei.ling@hotmail.com', '44556', '202 Jalan Ipoh, Perlis', '01234568027', 'Booking Agent', '2024-02-15'),
('yosman13', 'Yusof Bin Osman', 'yusof.osman@gmail.com', '33445', '284 Jalan Bukit , Kuala Lumpur', '01234568019', 'Customer Service Representative', '2024-01-22'),
('zabidin08', 'Zainal Abidin', 'abin08@gmail.com', '89012', '505 Jalan Sultan Ismail, Kelantan', '01147385938', 'Accountant', '2024-05-01');

-- --------------------------------------------------------

--
-- Table structure for table `trip`
--

CREATE TABLE `trip` (
  `trip_ID` varchar(25) NOT NULL,
  `number_plate` varchar(25) NOT NULL,
  `driver_ID` varchar(45) NOT NULL,
  `destination` varchar(45) NOT NULL,
  `start_time` varchar(25) NOT NULL,
  `end_time` varchar(25) NOT NULL,
  `duration` varchar(45) NOT NULL,
  `start_date` date NOT NULL,
  `end_date` date NOT NULL,
  `ticket_price` int(11) NOT NULL,
  `seat_available` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `trip`
--

INSERT INTO `trip` (`trip_ID`, `number_plate`, `driver_ID`, `destination`, `start_time`, `end_time`, `duration`, `start_date`, `end_date`, `ticket_price`, `seat_available`) VALUES
('TRIP001', 'PAV5939', 'DR-DEF002', 'PENANG', '08:00', '12:00', '4h', '2024-01-15', '2024-01-15', 50, 40),
('TRIP002', 'BHV1234', 'DR-ABC001', 'JOHOR BAHRU', '09:00', '13:00', '4h', '2024-02-10', '2024-02-10', 45, 80),
('TRIP003', 'LKU5678', 'DR-GHI003', 'IPOH', '10:00', '14:00', '4h', '2024-03-05', '2024-03-05', 40, 50),
('TRIP004', 'GHJ9012', 'DR-JKL004', 'KUANTAN', '11:00', '15:00', '4h', '2024-04-18', '2024-04-18', 55, 60),
('TRIP005', 'QWE3456', 'DR-MNO005', 'KUALA LUMPUR', '12:00', '16:00', '4h', '2024-05-01', '2024-05-01', 60, 20),
('TRIP006', 'TYU7890', 'DR-PQR006', 'MELAKA', '13:00', '17:00', '4h', '2024-06-25', '2024-06-25', 50, 39),
('TRIP007', 'MNB4321', 'DR-STU007', 'KOTA BHARU', '14:00', '18:00', '4h', '2024-07-15', '2024-07-15', 65, 60),
('TRIP008', 'VCX8765', 'DR-VWX008', 'ALOR SETAR', '15:00', '19:00', '4h', '2024-08-20', '2024-08-20', 45, 150),
('TRIP009', 'ZAS0987', 'DR-YZA009', 'KANGAR', '16:00', '20:00', '4h', '2024-09-10', '2024-09-10', 50, 80),
('TRIP010', 'PLM3456', 'DR-BCD010', 'GEORGE TOWN', '17:00', '21:00', '4h', '2024-10-05', '2024-10-05', 55, 50),
('TRIP011', 'IKJ5678', 'DR-EFG011', 'TAIPING', '08:00', '12:00', '4h', '2024-11-01', '2024-11-01', 40, 60),
('TRIP012', 'TGB6789', 'DR-HIJ012', 'SEREMBAN', '09:00', '13:00', '4h', '2024-12-15', '2024-12-15', 50, 20),
('TRIP013', 'YHN1234', 'DR-KLM013', 'SHAH ALAM', '10:00', '14:00', '4h', '2024-01-25', '2024-01-25', 55, 40),
('TRIP014', 'ASD4567', 'DR-NOP014', 'PUTRAJAYA', '11:00', '15:00', '4h', '2024-02-12', '2024-02-12', 45, 60),
('TRIP015', 'RFV6789', 'DR-QRS015', 'CYBERJAYA', '12:00', '16:00', '4h', '2024-03-19', '2024-03-19', 60, 150),
('TRIP016', 'PAV5939', 'DR-DEF002', 'KOTA KINABALU', '13:00', '17:00', '4h', '2024-04-25', '2024-04-25', 65, 40),
('TRIP017', 'BHV1234', 'DR-ABC001', 'SANDAKAN', '14:00', '18:00', '4h', '2024-05-20', '2024-05-20', 50, 80),
('TRIP018', 'LKU5678', 'DR-GHI003', 'TAWAU', '15:00', '19:00', '4h', '2024-06-10', '2024-06-10', 45, 50),
('TRIP019', 'GHJ9012', 'DR-JKL004', 'KUCHING', '16:00', '20:00', '4h', '2024-07-30', '2024-07-30', 60, 60),
('TRIP020', 'QWE3456', 'DR-MNO005', 'MIRI', '17:00', '21:00', '4h', '2024-08-25', '2024-08-25', 55, 20),
('TRIP021', 'TYU7890', 'DR-PQR006', 'BINTULU', '08:00', '12:00', '4h', '2024-09-18', '2024-09-18', 45, 40),
('TRIP022', 'MNB4321', 'DR-STU007', 'SIBU', '09:00', '13:00', '4h', '2024-10-25', '2024-10-25', 50, 60),
('TRIP023', 'VCX8765', 'DR-VWX008', 'LABUAN', '10:00', '14:00', '4h', '2024-11-15', '2024-11-15', 55, 150),
('TRIP024', 'ZAS0987', 'DR-YZA009', 'BANDAR SERI BEGAWAN', '11:00', '15:00', '4h', '2024-12-20', '2024-12-20', 60, 80),
('TRIP025', 'PLM3456', 'DR-BCD010', 'LANGKAWI', '12:00', '16:00', '4h', '2024-01-10', '2024-01-10', 45, 50),
('TRIP026', 'IKJ5678', 'DR-EFG011', 'KUALA TERENGGANU', '13:00', '17:00', '4h', '2024-02-18', '2024-02-18', 50, 60),
('TRIP027', 'TGB6789', 'DR-HIJ012', 'RAUB', '14:00', '18:00', '4h', '2024-03-25', '2024-03-25', 55, 20),
('TRIP028', 'YHN1234', 'DR-KLM013', 'DUNGUN', '15:00', '19:00', '4h', '2024-04-30', '2024-04-30', 60, 40),
('TRIP029', 'ASD4567', 'DR-NOP014', 'BESUT', '16:00', '20:00', '4h', '2024-05-25', '2024-05-25', 45, 60),
('TRIP030', 'RFV6789', 'DR-QRS015', 'GUA MUSANG', '17:00', '21:00', '4h', '2024-06-18', '2024-06-18', 50, 150),
('TRIP031', 'PAV5939', 'DR-DEF002', 'KUALA LUMPUR', '09:00', '13:00', '4h', '2024-01-20', '2024-01-20', 50, 40),
('TRIP032', 'BHV1234', 'DR-ABC001', 'PENANG', '10:00', '14:00', '4h', '2024-02-15', '2024-02-15', 45, 80),
('TRIP033', 'LKU5678', 'DR-GHI003', 'JOHOR BAHRU', '11:00', '15:00', '4h', '2024-03-10', '2024-03-10', 40, 50),
('TRIP034', 'GHJ9012', 'DR-JKL004', 'IPOH', '12:00', '16:00', '4h', '2024-04-12', '2024-04-12', 55, 60),
('TRIP035', 'QWE3456', 'DR-MNO005', 'MELAKA', '13:00', '17:00', '4h', '2024-05-05', '2024-05-05', 60, 22),
('TRIP036', 'TYU7890', 'DR-PQR006', 'KUALA LUMPUR', '14:00', '18:00', '4h', '2024-06-15', '2024-06-15', 50, 40),
('TRIP037', 'MNB4321', 'DR-STU007', 'PENANG', '15:00', '19:00', '4h', '2024-07-10', '2024-07-10', 65, 60),
('TRIP038', 'VCX8765', 'DR-VWX008', 'JOHOR BAHRU', '16:00', '20:00', '4h', '2024-08-22', '2024-08-22', 45, 150),
('TRIP039', 'ZAS0987', 'DR-YZA009', 'IPOH', '17:00', '21:00', '4h', '2024-09-14', '2024-09-14', 50, 80),
('TRIP040', 'PLM3456', 'DR-BCD010', 'MELAKA', '08:00', '12:00', '4h', '2024-10-18', '2024-10-18', 55, 50),
('TRIP041', 'IKJ5678', 'DR-EFG011', 'KUALA LUMPUR', '09:00', '13:00', '4h', '2024-11-12', '2024-11-12', 40, 58),
('TRIP042', 'TGB6789', 'DR-HIJ012', 'PENANG', '10:00', '14:00', '4h', '2024-12-15', '2024-12-15', 50, 20),
('TRIP043', 'YHN1234', 'DR-KLM013', 'JOHOR BAHRU', '11:00', '15:00', '4h', '2024-01-30', '2024-01-30', 55, 40),
('TRIP044', 'ASD4567', 'DR-NOP014', 'IPOH', '12:00', '16:00', '4h', '2024-02-25', '2024-02-25', 45, 60),
('TRIP045', 'RFV6789', 'DR-QRS015', 'MELAKA', '13:00', '17:00', '4h', '2024-03-22', '2024-03-22', 60, 150),
('TRIP046', 'PAV5939', 'DR-DEF002', 'KUALA LUMPUR', '14:00', '18:00', '4h', '2024-04-15', '2024-04-15', 65, 40),
('TRIP047', 'BHV1234', 'DR-ABC001', 'PENANG', '15:00', '19:00', '4h', '2024-05-18', '2024-05-18', 50, 80),
('TRIP048', 'LKU5678', 'DR-GHI003', 'JOHOR BAHRU', '16:00', '20:00', '4h', '2024-06-12', '2024-06-12', 45, 50),
('TRIP049', 'GHJ9012', 'DR-JKL004', 'IPOH', '17:00', '21:00', '4h', '2024-07-30', '2024-07-30', 60, 60),
('TRIP050', 'QWE3456', 'DR-MNO005', 'MELAKA', '08:00', '12:00', '4h', '2024-08-18', '2024-08-18', 30, 20);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`admin_ID`),
  ADD UNIQUE KEY `admin_email` (`admin_email`);

--
-- Indexes for table `booking`
--
ALTER TABLE `booking`
  ADD PRIMARY KEY (`booking_ID`),
  ADD KEY `customer_ID` (`customer_ID`),
  ADD KEY `trip_ID` (`trip_ID`);

--
-- Indexes for table `bus`
--
ALTER TABLE `bus`
  ADD PRIMARY KEY (`number_plate`);

--
-- Indexes for table `customer`
--
ALTER TABLE `customer`
  ADD PRIMARY KEY (`customer_ID`),
  ADD UNIQUE KEY `cust_email` (`customer_email`);

--
-- Indexes for table `driver`
--
ALTER TABLE `driver`
  ADD PRIMARY KEY (`driver_ID`);

--
-- Indexes for table `payment`
--
ALTER TABLE `payment`
  ADD PRIMARY KEY (`payment_ID`),
  ADD KEY `booking_ID` (`booking_ID`);

--
-- Indexes for table `staff`
--
ALTER TABLE `staff`
  ADD PRIMARY KEY (`staff_ID`),
  ADD UNIQUE KEY `staff_email` (`staff_email`);

--
-- Indexes for table `trip`
--
ALTER TABLE `trip`
  ADD PRIMARY KEY (`trip_ID`),
  ADD KEY `number_plate` (`number_plate`),
  ADD KEY `driver_ID` (`driver_ID`);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `booking`
--
ALTER TABLE `booking`
  ADD CONSTRAINT `booking_ibfk_1` FOREIGN KEY (`customer_ID`) REFERENCES `customer` (`customer_ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `booking_ibfk_2` FOREIGN KEY (`trip_ID`) REFERENCES `trip` (`trip_ID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `payment`
--
ALTER TABLE `payment`
  ADD CONSTRAINT `payment_ibfk_1` FOREIGN KEY (`booking_ID`) REFERENCES `booking` (`booking_ID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `trip`
--
ALTER TABLE `trip`
  ADD CONSTRAINT `trip_ibfk_1` FOREIGN KEY (`number_plate`) REFERENCES `bus` (`number_plate`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `trip_ibfk_2` FOREIGN KEY (`driver_ID`) REFERENCES `driver` (`driver_ID`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
