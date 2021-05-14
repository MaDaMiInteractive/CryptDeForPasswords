class Function
{
private:
	static const int sizebuff = 128;
	char buff[sizebuff];
public:
	/*Function() {
		//очистка буффера
		for (int i = 0; i < sizebuff; i++) {
			buff[i] = 0;
		}

	}*/
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
				std::stringstream temp;
				std::string tempch;
				while (output.getline(buff, sizebuff)) {
					for (int i = 0; i < sizebuff; i++) {
						if (buff[i] == ' ') {
							temp << tempch;
							temp >> s;
							if (id < s) {
								temp.str(std::string());
								temp.clear();
								tempch.clear();
								s--;
								temp << s;
								temp >> tempch;
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
							s = 0;
							temp.str(std::string());
							temp.clear();
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
		std::stringstream temp;
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
						
						temp << s;
						temp >> ggg;
						key = key + ggg + " ";
						temp.str(std::string());
						ggg.clear();
						temp.clear();
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
		int *numbers = new int[key.size()];
		std::stringstream temp;
		std::ofstream input("temp" + path);
		std::ifstream output(path);

		if (!input.is_open() || !output.is_open()) {
			std::cout << "Не удалось открыть файл!" << std::endl;
		}
		key = key + " ";
		for (int i = 0; i < key.size(); i++) {
			if (key[i] == ' ') {
				temp << tempd;
				temp >> numbers[g];
				g++;
				temp.str(std::string());
				temp.clear();
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
