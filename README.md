<a name="readme-top"></a>
<!-- PROJECT HEADER -->
<br />
<div align="center">
  <h3 align="center">Geometric Bounces</h3>
  <p align="center">
    MD описание проекта
    <br />
  </p>
</div>

<!-- ABOUT THE PROJECT SECTION -->
## Краткое описание

Данный проект посвящен базовому ознакомлению с [SFML][SFML-url] и [ImGui][ImGui-url]

## Зависимости

* Библиотека SFML (2.6.1)

## Сборка и запуск

Вы можете открыть проект в среде разработки Visual Studio (на момент написания программы использовалась VS 2022), в корневой директории располагается файл проекта "GeometricBounces.vcxproj". Проект сконфигурирован как для Debug, так и для Release сборки.

После сборки исполняемый *.exe файл будет находится в директории "\*Корневая папка проекта\*/\*Имя проекта/.../bin/\*.exe\*"

## После запуска

На экране будут представлены геометрические фигуры (круги и прямоугольники) различных цветов, радиусов, наименований и значений скоростей по осям X и Y.

Все эти величины вы можете менять с помощью графического интерфейса, реализованного с помощью ImGui: 
- В верхней части конфигурационного окна находится выпадающий список с наименованием фигур, выберите необходимую вам фигуру 
- Измените какой-либо из упомянутых параметров (цвет, радиус, наименование или скорость)

Также для проекта создан config.txt файл, который расположен в папке configs. Вы можете редактировать его перед запуском, спецификация файла:

- Window W H: строка определяет размер окна приложения
  
| Смысл           | Имя в файле | Тип  |
|:----------------|:------------|:----:|
| Window width    | W           | int  |
| Window height   | H           | int  |

- Font F S R G B: строка определяет путь до файла шрифтов и соответствующие параметры

| Смысл       | Имя в файле | Тип             |
|:------------|:------------|:---------------:|
| Font file   | F           | std::string     |
| Font size   | S           | int             |
| RGB color   | (R,G,B)     | int, int, int   |

- Rectangle N X Y SX SY R G B W H: строка определяет параметры прямоугольников

| Смысл               | Имя в файле | Тип             |
|:--------------------|:------------|:---------------:|
| Shape name          | F           | std::string     |
| Initial position    | (X,Y)       | float, float    |
| Initial speed       | (SX,SY)     | float, float    |
| RGB color           | (R,G,B)     | int, int, int   |
| Size                | (W,H)       | float, float    |

- Circle N X Y SX SY R G B R: строка определяет параметры кругов

| Смысл               | Имя в файле | Тип             |
|:--------------------|:------------|:---------------:|
| Shape name          | F           | std::string     |
| Initial position    | (X,Y)       | float, float    |
| Initial speed       | (SX,SY)     | float, float    |
| RGB color           | (R,G,B)     | int, int, int   |
| Radius              | R           | float           |

# Demo

Вы можете ознакомиться с demo [видео](https://www.youtube.com/watch?v=90AFiiRwNOY) приложения, нажав на превью ниже:

<p align="center">
  <a href="https://www.youtube.com/watch?v=90AFiiRwNOY" target="_blank">
    <img src="https://img.youtube.com/vi/90AFiiRwNOY/maxresdefault.jpg" alt="Watch the video">
  </a>
</p>

<!-- RESOURCES LINKS -->
[SFML-url]: https://www.sfml-dev.org/
[ImGui-url]: https://github.com/ocornut/imgui
