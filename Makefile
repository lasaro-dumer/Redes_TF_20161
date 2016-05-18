JFLAGS = -g -d bin/
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = src/*.java \

default: classes

classes: $(CLASSES:.java=.class)

clean:
	find . -name \*.class -type f -delete

run: default
	java -cp bin Simulador topologia.txt
