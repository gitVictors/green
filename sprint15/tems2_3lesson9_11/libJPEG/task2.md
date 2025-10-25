Задание 2
Не меняя библиотеку ImgLib, улучшите программу конвертации. Теперь она должна суметь сконвертировать изображение любого формата в любой. Поддерживаются пока только PPM и JPEG.
Используйте такой класс:

class ImageFormatInterface {
public:
    virtual bool SaveImage(const img_lib::Path& file, const img_lib::Image& image) const = 0;
    virtual img_lib::Image LoadImage(const img_lib::Path& file) const = 0;
}; 
Разработайте производные от него классы для поддержки PPM и JPEG.
Для определения формата файла используйте такую функцию:

Format GetFormatByExtension(const img_lib::Path& input_file) {
    const string ext = input_file.extension().string();
    if (ext == ".jpg"sv || ext == ".jpeg"sv) {
        return Format::JPEG;
    }

    if (ext == ".ppm"sv) {
        return Format::PPM;
    }

    return Format::UNKNOWN;
} 
Разработайте функцию ImageFormatInterface* GetFormatInterface(const img_lib::Path& path), которая будет возвращать указатель на интерфейс нужного формата или nullptr, если формат не удалось определить. Она должна использовать функцию GetFormatByExtension для определения формата файла.
В main добавьте определение форматов и замените функции чтения и записи изображений на универсальные.
Добавьте в main следующие коды возврата и сообщения об ошибках:
Неизвестный формат входного файла — Unknown format of the input file. Код возврата 2.
Неизвестный формат выходного файла — Unknown format of the output file. Код возврата 3.
Ограничения
Не меняйте библиотеку ImgLib и CMakeLists.txt
Функция GetFormatInterface должна быть реализована и работать корректно.
Используйте ImgLib для конвертации.
Пример
Тот же читающий пёсик. Чтобы вы смогли проверить конвертацию в обе стороны, теперь в архиве три файла:
исходный JPEG,
PPM-файл,
JPEG, полученный из PPM.
reading_dog_2.zip
Что отправлять на проверку
В файл main.cpp добавьте:
Класс ImageFormatInterface, приведённый в условии.
Производные от него для PPM и JPEG. Назовите их самостоятельно.
Функцию GetFormatByExtension, приведённую в условии.
Функцию GetFormatInterface, реализованную вами.
В функции main напишите код, определяющий форматы файлов функцией GetFormatInterface и выполняющий конвертацию универсальным образом.
Как будет тестироваться ваш код
Мы проверим, что:
Правильно выполняется конвертация из любого формата в любой.
Выводится правильное сообщение об ошибке, если не удалось определить формат.
Выводится правильный код возврата.
GetFormatInterface работает правильно и возвращает работающий интерфейс.
GetFormatInterface возвращает nullptr для неизвестного формата.