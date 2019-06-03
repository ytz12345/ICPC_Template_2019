while True:
	s = input()
	with open(s, 'r') as f:
		output = ''
		for line in f.readlines():
			if len(line) == 1 and line[0] == '\n':
				continue
			output += line
		f = open(s, 'w')
		f.write(output)