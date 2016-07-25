Some Trek Universe
------------------

Just for demo purposes...

Requirements
============

- HHVM (http://hhvm.com/)
- PostgreSQL (https://www.postgresql.org/)
- Flyway (https://flywaydb.org/) installed and available in $PATH
- Node.js (https://nodejs.org)

Creating the demo application
=============================

- Create your postgresql database somewhere
- Copy `config/flyway.properties.dist` to `config/flyway.properties` and fill in your database credentials
- Copy `STU/Database/Configuration.hh.dist` to `STU/Database/Configuration.hh`
  and fill in your database credentials
- `make init`
- `make update`
- `make dbmigration`
