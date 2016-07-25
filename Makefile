model:force
	rm -rf STU/Model/*.hh && ./STU/Model/generate_table_files

composer:force
	hhvm bin/composer.phar update

tests:force
	hhvm vendor/bin/phpunit -c phpunit.xml

compile:force
	node_modules/coffee-script/bin/coffee --compile --output assets/js/cmp assets/js

nodeinstall:force
	npm install coffee-script

coffeebuilder:force
	node_modules/coffee-script/bin/coffee -cw -o assets/js/cmp assets/js

dbmigration:force
	flyway -configFile=config/flyway.properties -locations=filesystem:dist/sql/ migrate

dbinfo:force
	flyway -configFile=config/flyway.properties -locations=filesystem:dist/sql/ info

init:composer model nodeinstall

update:model compile

force:
