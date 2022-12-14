# DirectoryScanner

## Задание:

Требуется реализовать утилиту, работающую из командной строки, для Linux или macOS, выполняющую сканирование файлов в директории, с целью нахождение в ней “подозрительных” (suspicious) файлов.

## В рамках задачи определено 3 типа “подозрительного” содержимого в файле.

- JS suspicious: файл с расширением .js, содержащий строку: <script>evil_script()</script>
- Unix suspicious: любой файл, содержащий строку: rm -rf ~/Documents
- macOS suspicious: любой файл, содержащий строку: system("launchctl load /Library/LaunchAgents/com.malware.agent")

## После завершения выполнения утилиты пользователю должен быть выведен отчет о сканировании, в котором присутствует следующая информация:

- общее количество обработанных файлов;
- количество детектов на каждый тип “подозрительного” содержимого;
- количество ошибок анализа файлов (например, не хватает прав на чтение файла);
- время выполнения утилиты.

## Пример исполнения утилиты из командной строки:

$ ./scan_util /Users/user/Downloads

====== Scan result ======

Processed files: 150

JS detects: 5

Unix detects: 1

macOS detects: 2

Errors: 1

Exection time: 00:00:31 

=========================
