Необходимый код, который будет запускаться хранится в секции .upx и будет зашифрован.
Для запуска:
	make
	./elf.exe main.exe // смотрим начало и длину секции .upx
	./code main.exe start size // start и size начало и длина кода
теперь байт код в main.exe будет зашифрован, при этом будет адекватно запускаться.