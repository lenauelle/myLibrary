--
-- Database:'Library'
--
-- -------------------------------------------------------------
--
-- Query view
--

CREATE VIEW lib_commonQuery AS
	SELECT DISTINCT i.ISBN, category, title, publisher, pub_year, 
		   author, price,(	SELECT COUNT(bno)
							FROM dbo.lib_book_list as k
							WHERE i.ISBN = k.ISBN) as total_num, 
					     (	SELECT COUNT(bno)
							FROM dbo.lib_book_list as k
							WHERE i.ISBN = k.ISBN and inStore = 1)as inventory
	FROM dbo.lib_book_info as i, dbo.lib_book_list as l
	WHERE i.ISBN = l.ISBN