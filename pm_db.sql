-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Apr 29, 2024 at 08:10 PM
-- Wersja serwera: 10.4.32-MariaDB
-- Wersja PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `pm_db`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `assigned_tasks`
--

CREATE TABLE `assigned_tasks` (
  `ID` int(11) NOT NULL,
  `task_id` int(11) DEFAULT NULL,
  `employee_id` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `assigned_tasks`
--

INSERT INTO `assigned_tasks` (`ID`, `task_id`, `employee_id`) VALUES
(1, 1, 1),
(2, 2, 2),
(3, 3, 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `employees`
--

CREATE TABLE `employees` (
  `ID` int(11) NOT NULL,
  `first_name` varchar(50) DEFAULT NULL,
  `last_name` varchar(50) DEFAULT NULL,
  `position` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `employees`
--

INSERT INTO `employees` (`ID`, `first_name`, `last_name`, `position`) VALUES
(1, 'John', 'Doe', 'Developer'),
(2, 'Jane', 'Smith', 'Manager');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `projects`
--

CREATE TABLE `projects` (
  `ID` int(11) NOT NULL,
  `name` varchar(255) DEFAULT NULL,
  `description` text DEFAULT NULL,
  `start_date` date DEFAULT NULL,
  `end_date` date DEFAULT NULL,
  `status` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `projects`
--

INSERT INTO `projects` (`ID`, `name`, `description`, `start_date`, `end_date`, `status`) VALUES
(1, 'Project 1', 'Description of project 1', '2024-05-01', '2024-06-30', 'Completed'),
(2, 'Project 2', 'Description of project 2', '2024-06-15', '2024-08-31', 'Planned');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `project_managers`
--

CREATE TABLE `project_managers` (
  `ID` int(11) NOT NULL,
  `first_name` varchar(50) DEFAULT NULL,
  `last_name` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `project_managers`
--

INSERT INTO `project_managers` (`ID`, `first_name`, `last_name`) VALUES
(1, 'Alice', 'Johnson'),
(2, 'Bob', 'Williams');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `project_manager_assignments`
--

CREATE TABLE `project_manager_assignments` (
  `ID` int(11) NOT NULL,
  `project_id` int(11) DEFAULT NULL,
  `manager_id` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `project_manager_assignments`
--

INSERT INTO `project_manager_assignments` (`ID`, `project_id`, `manager_id`) VALUES
(1, 1, 1),
(2, 2, 2);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `reports`
--

CREATE TABLE `reports` (
  `ID` int(11) NOT NULL,
  `project_id` int(11) DEFAULT NULL,
  `manager_id` int(11) DEFAULT NULL,
  `number_of_completed_tasks` int(11) DEFAULT NULL,
  `other_information` text DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `reports`
--

INSERT INTO `reports` (`ID`, `project_id`, `manager_id`, `number_of_completed_tasks`, `other_information`) VALUES
(1, 1, 1, 5, 'Some additional information for project 1'),
(2, 2, 2, 0, 'Some additional information for project 2');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `schedules`
--

CREATE TABLE `schedules` (
  `ID` int(11) NOT NULL,
  `project_id` int(11) DEFAULT NULL,
  `planned_end_date` date DEFAULT NULL,
  `actual_end_date` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `schedules`
--

INSERT INTO `schedules` (`ID`, `project_id`, `planned_end_date`, `actual_end_date`) VALUES
(1, 1, '2024-06-30', '2024-08-15'),
(2, 2, '2024-08-31', '0000-00-00');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `tasks`
--

CREATE TABLE `tasks` (
  `ID` int(11) NOT NULL,
  `name` varchar(255) DEFAULT NULL,
  `description` text DEFAULT NULL,
  `priority` varchar(50) DEFAULT NULL,
  `start_date` date DEFAULT NULL,
  `end_date` date DEFAULT NULL,
  `status` varchar(50) DEFAULT NULL,
  `project_id` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `tasks`
--

INSERT INTO `tasks` (`ID`, `name`, `description`, `priority`, `start_date`, `end_date`, `status`, `project_id`) VALUES
(1, 'Task 1', 'Description of task 1', 'High', '2024-05-01', '2024-05-15', 'In progress', 1),
(2, 'Task 2', 'Description of task 2', 'Low', '2024-06-01', '2024-06-30', 'Planned', 1),
(3, 'Task 3', 'Description of task 3', 'Medium', '2024-07-01', '2024-07-15', 'Planned', 1);

--
-- Indeksy dla zrzutów tabel
--

--
-- Indeksy dla tabeli `assigned_tasks`
--
ALTER TABLE `assigned_tasks`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `task_id` (`task_id`),
  ADD KEY `employee_id` (`employee_id`);

--
-- Indeksy dla tabeli `employees`
--
ALTER TABLE `employees`
  ADD PRIMARY KEY (`ID`);

--
-- Indeksy dla tabeli `projects`
--
ALTER TABLE `projects`
  ADD PRIMARY KEY (`ID`);

--
-- Indeksy dla tabeli `project_managers`
--
ALTER TABLE `project_managers`
  ADD PRIMARY KEY (`ID`);

--
-- Indeksy dla tabeli `project_manager_assignments`
--
ALTER TABLE `project_manager_assignments`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `project_id` (`project_id`),
  ADD KEY `manager_id` (`manager_id`);

--
-- Indeksy dla tabeli `reports`
--
ALTER TABLE `reports`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `project_id` (`project_id`),
  ADD KEY `manager_id` (`manager_id`);

--
-- Indeksy dla tabeli `schedules`
--
ALTER TABLE `schedules`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `project_id` (`project_id`);

--
-- Indeksy dla tabeli `tasks`
--
ALTER TABLE `tasks`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `project_id` (`project_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `assigned_tasks`
--
ALTER TABLE `assigned_tasks`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `employees`
--
ALTER TABLE `employees`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `projects`
--
ALTER TABLE `projects`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `project_managers`
--
ALTER TABLE `project_managers`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `project_manager_assignments`
--
ALTER TABLE `project_manager_assignments`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `reports`
--
ALTER TABLE `reports`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `schedules`
--
ALTER TABLE `schedules`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `tasks`
--
ALTER TABLE `tasks`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `assigned_tasks`
--
ALTER TABLE `assigned_tasks`
  ADD CONSTRAINT `assigned_tasks_ibfk_1` FOREIGN KEY (`task_id`) REFERENCES `tasks` (`ID`),
  ADD CONSTRAINT `assigned_tasks_ibfk_2` FOREIGN KEY (`employee_id`) REFERENCES `employees` (`ID`);

--
-- Constraints for table `project_manager_assignments`
--
ALTER TABLE `project_manager_assignments`
  ADD CONSTRAINT `project_manager_assignments_ibfk_1` FOREIGN KEY (`project_id`) REFERENCES `projects` (`ID`),
  ADD CONSTRAINT `project_manager_assignments_ibfk_2` FOREIGN KEY (`manager_id`) REFERENCES `project_managers` (`ID`);

--
-- Constraints for table `reports`
--
ALTER TABLE `reports`
  ADD CONSTRAINT `reports_ibfk_1` FOREIGN KEY (`project_id`) REFERENCES `projects` (`ID`),
  ADD CONSTRAINT `reports_ibfk_2` FOREIGN KEY (`manager_id`) REFERENCES `project_managers` (`ID`);

--
-- Constraints for table `schedules`
--
ALTER TABLE `schedules`
  ADD CONSTRAINT `schedules_ibfk_1` FOREIGN KEY (`project_id`) REFERENCES `projects` (`ID`);

--
-- Constraints for table `tasks`
--
ALTER TABLE `tasks`
  ADD CONSTRAINT `tasks_ibfk_1` FOREIGN KEY (`project_id`) REFERENCES `projects` (`ID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
