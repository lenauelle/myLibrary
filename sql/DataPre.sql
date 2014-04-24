--
-- Database:'Library'
-- Data for tests
--
-- -------------------------------------------------------------
--
-- Data import to 'lib_book_info'
--

INSERT INTO lib_book_info VALUES
	('978-7-5426-3054-4', 'Fiction', 'Animal Farm', 'Shanghai Sanlian', 2009, 'George Orwell', 16.00)
INSERT INTO lib_book_info VALUES
	('978-7-5327-3997-4', 'Fiction', '1984', 'Shanghai Yiwen', 2006, 'George Orwell', 13.00)
INSERT INTO lib_book_info VALUES
	('978-0-345-39180-3', 'Science Fiction', 'The Hitchhikers Guide to the Galaxy','Ballantine Books', 2005, 'Douglas Adams', 49.00)

--
-- Data import to 'lib_book_list'
--

INSERT INTO lib_book_list VALUES (1, '978-7-5426-3054-4', 0)
INSERT INTO lib_book_list VALUES (2, '978-7-5426-3054-4', 0)
INSERT INTO lib_book_list VALUES (3, '978-7-5426-3054-4', 1)
INSERT INTO lib_book_list VALUES (4, '978-7-5327-3997-4', 1)
INSERT INTO lib_book_list VALUES (5, '978-7-5327-3997-4', 0)
INSERT INTO lib_book_list VALUES (6, '978-7-5327-3997-4', 0)
INSERT INTO lib_book_list VALUES (7, '978-7-5327-3997-4', 1)
INSERT INTO lib_book_list VALUES (8, '978-7-5327-3997-4', 1)
INSERT INTO lib_book_list VALUES (11, '978-0-345-39180-3', 0)
INSERT INTO lib_book_list VALUES (12, '978-0-345-39180-3', 1)

--
-- Data import to 'lib_user'
--

INSERT INTO lib_user VALUES (92, 'Pendleton','Literature Dept.', 1)
INSERT INTO lib_user VALUES (2, 'Brando', 'Law Dept.', 0)
INSERT INTO lib_user VALUES (301, 'Kujo', 'Biology Dept.', 1)

--
-- Data import to 'lib_admin'
--

INSERT INTO lib_admin VALUES (1, '123456', 'Joestar', 'jojo@asb.en')

--
-- Data import to 'lib_record'
--

INSERT INTO lib_record VALUES (1, 92, 1, 3, '2013-07-06 08:57:00', '2013-07-06 08:57:00', 1)
INSERT INTO lib_record VALUES (2, 92, 1, 12, '2013-07-06 08:57:00', '2013-07-06 08:57:00', 1)
INSERT INTO lib_record VALUES (3, 301, 1, 1, '2013-07-06 08:57:00', NULL, 0)

