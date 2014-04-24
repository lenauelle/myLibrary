--
-- Database:'Library'
--
-- -------------------------------------------------------------
--
-- Table structure for 'lib_book_info'
--

IF NOT EXISTS(
	SELECT [name]
	FROM [sys].tables
	WHERE [name] = 'lib_book_info')
CREATE TABLE lib_book_info(
	ISBN char(17) NOT NULL,
	category varchar(15) NOT NULL,
	title varchar(60) NOT NULL,
	publisher varchar(50) NOT NULL,
	pub_year int NOT NULL,
	author varchar(60) NOT NULL,
	price numeric(12,2) NOT NULL,
	PRIMARY KEY(ISBN))

--
-- Table structure for 'lib_book_list'
--

IF NOT EXISTS(
	SELECT [name]
	FROM [sys].tables
	WHERE [name] = 'lib_book_list')
CREATE TABLE lib_book_list(
	bno int NOT NULL,
	ISBN char(17) NOT NULL,
	inStore int NOT NULL,
	PRIMARY KEY (bno),
	FOREIGN KEY (ISBN) REFERENCES lib_book_info ON DELETE CASCADE ON UPDATE CASCADE)

--	
-- Table structure for 'user'
--

IF NOT EXISTS(
	SELECT [name]
	FROM [sys].tables
	WHERE [name] = 'lib_user')
CREATE TABLE lib_user(
	lib_uid int NOT NULL,
	name varchar(30) NOT NULL,
	organization varchar(30) NOT NULL,
	lib_uclass int NOT NULL,
	PRIMARY KEY (lib_uid))
	
--
-- Table structure for 'lib_admin'
--

IF NOT EXISTS(
	SELECT [name]
	FROM [sys].tables
	WHERE [name] = 'lib_admin')
CREATE TABLE lib_admin(
	lib_aid int NOT NULL,
	lib_psw varchar(32) NOT NULL,
	name varchar(30) NOT NULL,
	contact varchar(30) NOT NULL,
	PRIMARY KEY (lib_aid))

--
-- Table structure for 'lib_record'
--

IF NOT EXISTS(
	SELECT [name]
	FROM [sys].tables
	WHERE [name] = 'lib_record')
CREATE TABLE lib_record(
	rid int NOT NULL,
	lib_uid int NOT NULL,
	lib_aid int NOT NULL,
	bno int NOT NULL,
	date_borrow datetime default(NULL) NOT NULL,
	date_return datetime default(NULL),
	isReturned int default(0) NOT NULL,
	PRIMARY KEY (rid),
	FOREIGN KEY (bno) REFERENCES lib_book_list ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (lib_uid) REFERENCES lib_user ON DELETE NO ACTION ON UPDATE CASCADE,
	FOREIGN KEY (lib_aid) REFERENCES lib_admin ON DELETE NO ACTION ON UPDATE CASCADE)
	