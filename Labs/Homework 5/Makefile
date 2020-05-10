clean:
	rm -rf parser
	rm -rf lex.yy.c
	rm -rf y.tab.c
	rm -rf y.tab.c
	rm -rf y.tab.h
	rm -rf y.output

	lex parser.l 
	yacc -d -v parser.y
	gcc lex.yy.c y.tab.c -w -o parser
	./parser

remove:
	rm -rf parser
	rm -rf lex.yy.c
	rm -rf y.tab.c
	rm -rf y.tab.c
	rm -rf y.tab.h
	rm -rf y.output