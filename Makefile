all: countWords

countWords: countWords.c
	gcc countWords.c -o countWords

clean:
	rm -f countWords
