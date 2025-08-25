-- ***********************
-- Name: Abdalla Abdelgadir
-- ID: 1137374198
-- Section: NEE
-- Date: 03/29/2024
-- Purpose: Lab 10 DBS211
-- ***********************

--Task 2.1
create table tremployees  as select * from dbs211_employees;
alter table tremployees add salary float;
select * from tremployees;

SET AUTOCOMMIT OFF:

-- Initial salary for everyone is 2000]
UPDATE tremployees SET salary = 2000; 
COMMIT;

-- Salaries
-- [Bondur: 2000 ]
-- [Kato: 2000 ]
-- [Gerard: 2000]


SET TRANSACTION NAME 'sal_update';

UPDATE tremployees
  SET salary = 7000 
  WHERE lastname = 'Bondur';

-- update salary and mention if Dirty data or not
-- [Bondur:   ]
-- [Kato:    ]
-- [Gerard:   ]

SAVEPOINT after_Bondur_sal;

-- update salary and mention if Dirty data or not
-- [Bondur:   ]
-- [Kato:    ]
-- [Gerard:   ]

UPDATE tremployees
  SET salary = 12000 
  WHERE lastname = 'Kato';

-- update salary and mention if Dirty data or not
-- [Bondur:   ]
-- [Kato:    ]
-- [Gerard:   ]

SAVEPOINT after_Kato_sal;  
ROLLBACK TO SAVEPOINT after_Bondur_sal;

-- update salary and mention if Dirty data or not
-- [Bondur:   ]
-- [Kato:    ]
-- [Gerard:   ]
