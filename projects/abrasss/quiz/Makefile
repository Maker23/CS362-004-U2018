
quiz: testme.c
	cc -o quiz testme.c
	@time ./quiz > output &
	@echo 'Test is running in the background; "tail -f output" to see live results'

clean:
	rm quiz output
