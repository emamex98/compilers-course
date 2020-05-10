clean:
	rm -rf lexic_analyzer
	rm -rf lex.yy.c
	rm -rf example.ac
	rm -rf lex.out

	lex lexic_analyzer.l 
	gcc lex.yy.c -o lexical_scan -lfl
	python3 code_generator.py > example.ac
	./lexical_scan example.ac

stress:
	rm -rf lexic_analyzer
	rm -rf lex.yy.c
	rm -rf random_code.ac
	rm -rf lex.out

	lex lexic_analyzer.l 
	gcc lex.yy.c -o lexical_scan -lfl
	python3 code_generator.py --stress
	./lexical_scan random_code.ac

remove:
	rm -rf lexic_analyzer
	rm -rf lex.yy.c
	rm -rf example.ac
	rm -rf random_code.ac
	rm -rf lex.out