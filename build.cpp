/*
create view record as
select name, ISBN, author, publisher, category, year, month,
count(case when status = 'in' then 1 else null end),
count(case when status = 'out' then 1 else null end)
from book
group by ISBN

Create view borrowHistory as
select A.name, A.ISBN, A.author, A.publisher,
B.borrow_date, B.deadline, B.return_date, B.book_id, B.user_id
from borrow as B, book as A
where A.book_id = B.book_id

Create view manageHistory as select
A.name, A.ISBN, A.author, A.publisher, A.category,
A.year, A.month, A.status, C.username, A.book_id
from manage as B, book as A, user as C
where A.book_id = B.book_id and B.manager_id = C.user_id

*/