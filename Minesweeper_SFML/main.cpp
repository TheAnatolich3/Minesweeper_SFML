#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int main()
{
	// Генератор случайных чисел
	srand(static_cast<unsigned int>(time(0)));
	RenderWindow app(VideoMode(400, 400), "Minesweeper!");

	// Ширина клетки
	int w = 32;
	int gridLogic[12][12];
	int gridView[12][12];

	// Загрузка текстуры и создание спрайта
	Texture t;
	t.loadFromFile("Images/tiles.jpg");
	Sprite s(t);

	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			gridView[i][j] = 10;

			if (rand() % 5 == 0) 
				gridLogic[i][j] = 9;
			else 
				gridLogic[i][j] = 0;
		}
	}

	// Подсчет мин вокруг каждой клетки	
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			int n = 0;
			if (gridLogic[i][j] == 9) 
				continue;
			if (gridLogic[i + 1][j] == 9)
				n++;
			if (gridLogic[i][j + 1] == 9) 
				n++;
			if (gridLogic[i - 1][j] == 9) 
				n++;
			if (gridLogic[i][j - 1] == 9) 
				n++;
			if (gridLogic[i + 1][j + 1] == 9) 
				n++;
			if (gridLogic[i - 1][j - 1] == 9) 
				n++;
			if (gridLogic[i - 1][j + 1] == 9) 
				n++;
			if (gridLogic[i + 1][j - 1] == 9) 
				n++;

			gridLogic[i][j] = n;
		}
	}

	while (app.isOpen())
	{
		// Получаем координаты курсора мышки относительно окна нашего приложения
		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / w;
		int y = pos.y / w;

		Event e;

		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			// Определяем, была ли нажата кнопка мыши?
			if (e.type == Event::MouseButtonPressed)
			{
				// Если была нажата левая кнопка мыши, то открываем клетку
				if (e.key.code == Mouse::Left)
				{
					if (gridLogic[x][y] == 9)
					{
						for (int i = 1; i <= 10; i++)
						{
							for (int j = 1; j <= 10; j++)
							{
								gridView[i][j] = gridLogic[i][j];
							}
						}
					}
					else {
						gridView[x][y] = gridLogic[x][y];
					}
				}
				// Если была нажата правая кнопка мыши, то отображаем флажок
				else if (e.key.code == Mouse::Right) 
					gridView[x][y] = 11;
			}
		}

		// Устанавливаем белый фон
		app.clear(Color::White);
		for (int i = 1; i <= 10; i++)
		{
			for (int j = 1; j <= 10; j++)
			{
				// Вырезаем из спрайта нужный нам квадратик текстуры
				s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));
				// Устанавливаем его в заданную позицию...
				s.setPosition(static_cast<float>(i * w), static_cast<float>(j * w));
				// ... и отрисовываем
				app.draw(s);
			}
		}

		// Отображаем всю композицию на экране
		app.display();
	}
	return 0;
}