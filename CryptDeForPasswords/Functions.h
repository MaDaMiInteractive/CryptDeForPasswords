class Function
{
private:
	static const int sizebuff = 128;
	char buff[sizebuff];
	
public:
	std::string IntToString(int VarInt) {
		int temp = VarInt, size = 0;
		int divisor = 1;

		while (temp) {
			temp /= 10;
			++size;
		}

		for (int i = 1; i < size; ++i) {
			divisor *= 10;
		}
		std::string output;
		output.push_back(0);
		for (int i = 0; i < size; ++i) {
			temp = VarInt / divisor % 10;
			switch (temp)
			{
			case 0:
				output[i] = '0';
				break;
			case 1:
				output[i] = '1';
				break;
			case 2:
				output[i] = '2';
				break;
			case 3:
				output[i] = '3';
				break;
			case 4:
				output[i] = '4';
				break;
			case 5:
				output[i] = '5';
				break;
			case 6:
				output[i] = '6';
				break;
			case 7:
				output[i] = '7';
				break;
			case 8:
				output[i] = '8';
				break;
			case 9:
				output[i] = '9';
				break;
			}
			divisor /= 10;
			output.push_back(0);
		}
		return output;
	}
	int StringToInt(std::string VarString) {
		int size = VarString.size();
		int VarOut = 0, multiplier = 1;
		for (int i = 0; i < size; ++i) {
			multiplier *= 10;
		}

		for (int i = 0; i < size; ++i) {
			switch (VarString[i])
			{
			case '1':
				VarOut += multiplier;
				break;
			case '2':
				VarOut += multiplier * 2;
				break;
			case '3':
				VarOut += multiplier * 3;
				break;
			case '4':
				VarOut += multiplier * 4;
				break;
			case '5':
				VarOut += multiplier * 5;
				break;
			case '6':
				VarOut += multiplier * 6;
				break;
			case '7':
				VarOut += multiplier * 7;
				break;
			case '8':
				VarOut += multiplier * 8;
				break;
			case '9':
				VarOut += multiplier * 9;
				break;
			case '0':
				VarOut += multiplier * 0;
				break;
			}
			multiplier /= 10;
		}
		return VarOut / 10;
	}
	//Параметры функции: (путь к файлу), ничего не возращает. Суть функции: вывод текста из файла
	void OutputFile(std::string path) {
		std::ifstream d;
		d.open(path);
		if (!d.is_open()) {
			std::cout << "Не удалось открыть файл!" << std::endl;
		}
		else {
			while (d.getline(buff, sizebuff)) {
				std::cout << buff << std::endl;
			}
			d.close();
		}
	}
	//Параметры функции: (путь к файлу, ид), ничего не возращает. Суть функции: добавляет пароль
	void AddPassword(std::string path, int id, std::string username, std::string password) {
		if (id == 0) {
			std::ofstream input(path);
			input << id << " " << username << " " << password;
			input.close();
		}
		else {
			std::ofstream input("temp" + path);
			std::ifstream output(path);
			if (!input.is_open() || !output.is_open()) {
				std::cout << "Не удалось открыть файл!" << std::endl;
			}
			else {
				while (output.getline(buff, sizebuff)) {
					input << buff << std::endl;
				}
				input << id << " " << username << " " << password;
				output.close();
				input.close();

				output.open("temp" + path);
				input.open(path);

				while (output.getline(buff, sizebuff)) {
					input << buff << std::endl;
				}

				output.close();
				input.close();
				std::string removefile = "temp" + path;
				remove(removefile.c_str());
			}
		}
	}
	//Параметры функции: (путь к файлу, ид), ничего не возращает. Суть функции: удаляет пароль
	void RemovePassword(std::string path, int id) {
		if (id == -1) {
			remove(path.c_str());
		}
		else {
			std::ofstream input("temp" + path);
			std::ifstream output(path);
			if (!input.is_open() || !output.is_open()) {
				std::cout << "Не удалось открыть файл!" << std::endl;
			}
			else {
				int s = 0;
				std::string tempch;
				while (output.getline(buff, sizebuff)) {
					for (int i = 0; i < sizebuff; i++) {
						if (buff[i] == ' ') {
							s = StringToInt(tempch);
							if (id < s) {
								tempch.clear();
								s--;
								tempch = IntToString(s);
								for (int g = 0; g < sizebuff; g++) {
									if (buff[g] == ' ') {
										break;
									}
									buff[g] = tempch[g];
								}
								input << buff << std::endl;
							}
							else if(s != id){
								input << buff << std::endl;
							}
							tempch.clear();
							break;
						}
						else {
							tempch = tempch + buff[i];
						}
					}
				}
				
				output.close();
				input.close();
				
 				output.open("temp" + path);
				input.open(path);
				while (output.getline(buff, sizebuff)) {
					input << buff << std::endl;
				}
				output.close();
				input.close();
				std::string removefile = "temp" + path;
				remove(removefile.c_str());
			}
		}
	}
	//Параметры функции: (путь к файлу, ид), возращает ключ. Суть функции: шифрует пароль
	std::string EncryptPassword(std::string path, int id) {
		srand(time(0));
		std::string key,ggg;
		int s = 0, g = 0;
		std::ofstream input("temp" + path);
		std::ifstream output(path);
		if (!input.is_open() || !output.is_open()) {
			std::cout << "Не удалось открыть файл!" << std::endl;
		}
		while (output.getline(buff, sizebuff)) {
			if (id == g) {
				for (int i = 0; i < sizebuff; i++) {
					if (s == 2) {
						if (buff[i] == 0) {
							break;
						}
						s = rand() % 98 + 1;
						buff[i] = buff[i] + s;
						ggg = IntToString(s);
						
						key = key + ggg + " ";
						ggg.clear();
						s = 2;
					}
					else if (buff[i] == ' ') {
						s++;
					}
				}
			}
			g++;
			input << buff << std::endl;
		}

		output.close();
		input.close();

		output.open("temp" + path);
		input.open(path);
		while (output.getline(buff, sizebuff)) {
			input << buff << std::endl;
		}
		output.close();
		input.close();
		std::string removefile = "temp" + path;
		remove(removefile.c_str());
		return key;
	}
	//Параметры функции: (путь к файлу, ид, ключ), ничего не возращает. Суть функции: дешифрует пароль
	void DecryptPassword(std::string path, int id, std::string key) {
		int s = 0, g = 0;
		std::string tempd;
		int* numbers = new int[key.size()];
		std::ofstream input("temp" + path);
		std::ifstream output(path);

		if (!input.is_open() || !output.is_open()) {
			std::cout << "Не удалось открыть файл!" << std::endl;
		}
		key = key + " ";
		for (int i = 0; i < key.size(); i++) {
			if (key[i] == ' ') {
				numbers[g] = StringToInt(tempd);
				g++;
				tempd.clear();
			}
			else {
				tempd += key[i];
			}
		}
		g = 0;
		while (output.getline(buff, sizebuff)) {
			if (g == id) {
				g = 0;
				for (int i = 0; i < sizebuff; i++) {
					if (s == 2) {
						if (buff[i] == 0) {
							break;
						}
						buff[i] = buff[i] - numbers[g];
						g++;
					}
					else if (buff[i] == ' ') {
						s++;
					}
				}
			}
			g++;
			input << buff << std::endl;
		}

		delete[] numbers;
		output.close();
		input.close();

		output.open("temp" + path);
		input.open(path);
		while (output.getline(buff, sizebuff)) {
			input << buff << std::endl;
		}
		output.close();
		input.close();
		std::string removefile = "temp" + path;
		remove(removefile.c_str());

	}
	//Параметры функции: (путь к файлу), возращает ид функции. Суть функции: находи максимальный ид пароля
	int MaxId(std::string path) {
		int id = 0;
		std::ifstream d;
		d.open(path);
		if (!d.is_open()) {
			std::cout << "Не удалось открыть файл!" << std::endl;
		}
		else {
			while (d.getline(buff, sizebuff)) {
				if (buff[0] != ' ') {
					++id;
				}
			}
		}
		d.close();
		return id;
	}
};
