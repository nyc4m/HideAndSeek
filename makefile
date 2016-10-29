FICHIER=hide
PROG=$(FICHIER)

$(PROG): $(FICHIER).o
	gcc -o $(PROG) $(FICHIER).o
$(FICHIER).o: $(FICHIER).c
	gcc -c $(FICHIER).c

clean:
	rm *.o $(FICHIER)
debug: $(FICHIER).c
	gcc -g $(FICHIER).c -o Debug
install:
	sudo cp hide /bin
uninstall:
	sudo rm /bin/hide
