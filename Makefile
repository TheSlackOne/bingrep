all: 
	cd src/; make;
	@echo "\n> All Good! <\n"

dist: all
	mkdir -p bingrep;
	mv -f bin lib bingrep;
	tar cf bingrep.tar bingrep;
	gzip -9 bingrep.tar;
	rm -Rf *.o bin bingrep;
	@echo "\n> Done! <\n"

distclean:
	cd src/; rm -Rf *.o ../bin

clean:
	cd src/; rm -Rf *.o
